#include "ThreadPool.h"

ThreadPool::ThreadPool() noexcept:
    m_threadNum{std::thread::hardware_concurrency()},
    m_taskNum{0}
{

}

ThreadPool::ThreadPool(size_t n) noexcept:
    m_threadNum{n},
    m_taskNum{0}
{

}

ThreadPool::~ThreadPool() noexcept
{
    stop();
}

size_t ThreadPool::threadNum() const noexcept
{
    return m_threadNum;
}

void ThreadPool::addTask(std::function<void(void)> func) noexcept
{
    _pushTask(func);
    _taskNumAdd();
}

void ThreadPool::start() noexcept
{
    _setRunning(true);
    for (size_t i = 0; i < m_threadNum; i++)
        m_threads.emplace_back(&ThreadPool::_threadHandler, this);
}

void ThreadPool::waitDone() noexcept
{
    std::unique_lock<std::mutex> lock{m_taskNumMutex};
    while (m_taskNum > 0)
    {
        m_taskNumNotifier.wait(lock);
    }
}

void ThreadPool::stop() noexcept
{
    m_queueMutex.lock();
    _setRunning(false);
    m_queueNotifier.notify_all();
    m_queueMutex.unlock();

    for (auto& thread : m_threads)
        thread.join();
    m_threads.clear();
}

size_t ThreadPool::taskNum() noexcept
{
    return m_taskNum;
}

bool ThreadPool::_isRunning() noexcept
{
    std::lock_guard<std::mutex> lock{m_runningMutex};
    return m_running;
}

void ThreadPool::_setRunning(bool v) noexcept
{
    std::lock_guard<std::mutex> lock{m_runningMutex};
    m_running = v;
}



// 任务队列
void ThreadPool::_pushTask(std::function<void(void)>& func) noexcept
{
    std::lock_guard<std::mutex> lock{m_queueMutex};
    m_taskQueue.push(func);
    m_queueNotifier.notify_all();
}


bool ThreadPool::_popTask(std::function<void(void)>& func) noexcept
{
    std::lock_guard<std::mutex> lock{m_queueMutex};
    if (m_taskQueue.empty())
        return false;

    func = m_taskQueue.front();
    m_taskQueue.pop();
    return true;
}

size_t ThreadPool::_queueNum() noexcept
{
    std::lock_guard<std::mutex> lock{m_queueMutex};
    return m_taskQueue.size();
}

void ThreadPool::_waitQueueNotEmpty() noexcept
{
    std::unique_lock<std::mutex> lock{m_queueMutex};
    m_queueNotifier.wait(lock, [this](){
        return !m_taskQueue.empty() || !_isRunning();
    });
}

// 剩余任务数量(不能读队列长度，因为可能取出了正在处理还没处理完)
size_t ThreadPool::_taskNum() noexcept
{
    std::lock_guard<std::mutex> lock{m_taskNumMutex};
    return m_taskNum;
}

void ThreadPool::_taskNumAdd() noexcept
{
    std::lock_guard<std::mutex> lock{m_taskNumMutex};
    m_taskNum += 1;
    m_taskNumNotifier.notify_all();
}

void ThreadPool::_taskNumSub() noexcept
{
    std::lock_guard<std::mutex> lock{m_taskNumMutex};
    m_taskNum -= 1;
    m_taskNumNotifier.notify_all();
}

// static 
void ThreadPool::_threadHandler() noexcept
{
    std::function<void(void)> func;
    while (_isRunning())
    {
        if (_popTask(func))
        {
            func();
            _taskNumSub();
        }
        else
        {
            _waitQueueNotEmpty();
        }
    }
}