#ifndef LYCORIS_THREAD_POOL_H
#define LYCORIS_THREAD_POOL_H

#include <cstddef>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <queue>

namespace Lycoris
{

class ThreadPool
{
public:
    ThreadPool() noexcept;
    ThreadPool(size_t n) noexcept;
    ~ThreadPool() noexcept;
    ThreadPool(const ThreadPool& src) = delete;
    ThreadPool(ThreadPool&& src) = default;

    size_t threadNum() const noexcept;
    void addTask(std::function<void(void)> func) noexcept;
    void start() noexcept;
    void waitDone() noexcept;
    void stop() noexcept;
    size_t taskNum() noexcept;

private:
    // 线程数量
    size_t m_threadNum; 

    // 运行标识
    bool m_running;
    std::mutex m_runningMutex;
    bool _isRunning() noexcept;
    void _setRunning(bool v) noexcept;

    
    // 任务队列
    std::queue<std::function<void(void)>> m_taskQueue;
    std::mutex m_queueMutex;
    std::condition_variable m_queueNotifier;

    void _pushTask(std::function<void(void)>& func) noexcept;
    bool _popTask(std::function<void(void)>& func) noexcept;
    size_t _queueNum() noexcept;
    void _waitQueueNotEmpty() noexcept;
    
    // 剩余任务数量(不能读队列长度，因为可能取出了正在处理还没处理完)
    size_t m_taskNum;
    std::mutex m_taskNumMutex;
    std::condition_variable m_taskNumNotifier;

    size_t _taskNum() noexcept;
    void _taskNumAdd() noexcept;
    void _taskNumSub() noexcept;

    // 线程及处理函数
    std::vector<std::thread> m_threads;
    void _threadHandler() noexcept;
};

}; // namespace Lycoris

#endif // LYCORIS_THREAD_POOL_H