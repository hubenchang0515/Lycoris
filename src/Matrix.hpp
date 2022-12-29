#ifndef LYCORIS_MATRIX_HPP
#define LYCORIS_MATRIX_HPP

#include <iostream>
#include <cstddef>
#include <stdexcept>
#include <functional>
#include <string>
#include <vector>

namespace Lycoris
{

template<typename... T>
static std::string __strfmt__(const char* fmt, T... args) noexcept
{
    static char buffer[1024];
    sprintf(buffer, fmt, args...);
    return buffer;
}

template<typename T>
class Matrix;

template<typename T>
std::ostream& operator<< (std::ostream& stream, const Matrix<T>& mat);

// 标量运算
template<typename T>
Matrix<T> operator+ (const Matrix<T>& mat, const T& n) noexcept;
template<typename T>
Matrix<T> operator+ (const T& n, const Matrix<T>& mat) noexcept;
template<typename T>
Matrix<T> operator- (const Matrix<T>& mat, const T& n) noexcept;
template<typename T>
Matrix<T> operator- (const T& n, const Matrix<T>& mat) noexcept;
template<typename T>
Matrix<T> operator* (const Matrix<T>& mat, const T& n) noexcept;
template<typename T>
Matrix<T> operator* (const T& n, const Matrix<T>& mat) noexcept;
template<typename T>
Matrix<T> operator/ (const Matrix<T>& mat, const T& n) noexcept;
template<typename T>
Matrix<T> operator/ (const T& n, const Matrix<T>& mat) noexcept;

// 行向量运算
template<typename T>
Matrix<T> operator+ (const Matrix<T>& mat, const typename Matrix<T>::RowView& vec);
template<typename T>
Matrix<T> operator+ (const typename Matrix<T>::RowView& vec, const Matrix<T>& mat);
template<typename T>
Matrix<T> operator- (const Matrix<T>& mat, const typename Matrix<T>::RowView& vec);
template<typename T>
Matrix<T> operator- (const typename Matrix<T>::RowView& vec, const Matrix<T>& mat);
template<typename T>
Matrix<T> operator* (const Matrix<T>& mat, const typename Matrix<T>::RowView& vec);
template<typename T>
Matrix<T> operator* (const typename Matrix<T>::RowView& vec, const Matrix<T>& mat);
template<typename T>
Matrix<T> operator/ (const Matrix<T>& mat, const typename Matrix<T>::RowView& vec);
template<typename T>
Matrix<T> operator/ (const typename Matrix<T>::RowView& vec, const Matrix<T>& mat);

// 列向量运算
template<typename T>
Matrix<T> operator+ (const Matrix<T>& mat, const typename Matrix<T>::ColView& vec);
template<typename T>
Matrix<T> operator+ (const typename Matrix<T>::ColView& vec, const Matrix<T>& mat);
template<typename T>
Matrix<T> operator- (const Matrix<T>& mat, const typename Matrix<T>::ColView& vec);
template<typename T>
Matrix<T> operator- (const typename Matrix<T>::ColView& vec, const Matrix<T>& mat);
template<typename T>
Matrix<T> operator* (const Matrix<T>& mat, const typename Matrix<T>::ColView& vec);
template<typename T>
Matrix<T> operator* (const typename Matrix<T>::ColView& vec, const Matrix<T>& mat);
template<typename T>
Matrix<T> operator/ (const Matrix<T>& mat, const typename Matrix<T>::ColView& vec);
template<typename T>
Matrix<T> operator/ (const typename Matrix<T>::ColView& vec, const Matrix<T>& mat);

// 矩阵运算
template<typename T>
Matrix<T> operator+ (const Matrix<T>& left, const Matrix<T>& right);
template<typename T>
Matrix<T> operator- (const Matrix<T>& left, const Matrix<T>& right);
template<typename T>
Matrix<T> operator* (const Matrix<T>& left, const Matrix<T>& right);
template<typename T>
Matrix<T> scalarMul(const Matrix<T>& left, const Matrix<T>& right);
template<typename T>
Matrix<T> scalarDiv(const Matrix<T>& left, const Matrix<T>& right);


template<typename T>
class Matrix
{
public:
    class RowView;
    class ColView;

    friend std::ostream& operator<< <T> (std::ostream& stream, const Matrix<T>& mat);

    // 标量运算
    friend Matrix<T> operator+<T> (const T& n, const Matrix<T>& mat) noexcept;
    friend Matrix<T> operator+<T> (const Matrix<T>& mat, const T& n) noexcept;
    friend Matrix<T> operator-<T> (const T& n, const Matrix<T>& mat) noexcept;
    friend Matrix<T> operator-<T> (const Matrix<T>& mat, const T& n) noexcept;
    friend Matrix<T> operator*<T> (const T& n, const Matrix<T>& mat) noexcept;
    friend Matrix<T> operator*<T> (const Matrix<T>& mat, const T& n) noexcept;
    friend Matrix<T> operator/<T> (const T& n, const Matrix<T>& mat) noexcept;
    friend Matrix<T> operator/<T> (const Matrix<T>& mat, const T& n) noexcept;

    // 行向量运算
    friend Matrix<T> operator+<T> (const Matrix<T>& mat, const RowView& vec);
    friend Matrix<T> operator+<T> (const RowView& vec, const Matrix<T>& mat);
    friend Matrix<T> operator*<T> (const Matrix<T>& mat, const RowView& vec);
    friend Matrix<T> operator*<T> (const RowView& vec, const Matrix<T>& mat);
    friend Matrix<T> operator-<T> (const Matrix<T>& mat, const RowView& vec);
    friend Matrix<T> operator-<T> (const RowView& vec, const Matrix<T>& mat);
    friend Matrix<T> operator/<T> (const Matrix<T>& mat, const RowView& vec);
    friend Matrix<T> operator/<T> (const RowView& vec, const Matrix<T>& mat);

    // 列向量运算
    friend Matrix<T> operator+<T> (const Matrix<T>& mat, const ColView& vec);
    friend Matrix<T> operator+<T> (const ColView& vec, const Matrix<T>& mat);
    friend Matrix<T> operator*<T> (const Matrix<T>& mat, const ColView& vec);
    friend Matrix<T> operator*<T> (const ColView& vec, const Matrix& mat);
    friend Matrix<T> operator-<T> (const Matrix<T>& mat, const ColView& vec);
    friend Matrix<T> operator-<T> (const ColView& vec, const Matrix<T>& mat);
    friend Matrix<T> operator/<T> (const Matrix<T>& mat, const ColView& vec);
    friend Matrix<T> operator/<T> (const ColView& vec, const Matrix<T>& mat);

    // 矩阵运算
    friend Matrix<T> operator+<T> (const Matrix<T>& left, const Matrix<T>& right);
    friend Matrix<T> operator-<T> (const Matrix<T>& left, const Matrix<T>& right);
    friend Matrix<T> operator*<T> (const Matrix<T>& left, const Matrix<T>& right);  // 叉乘
    friend Matrix<T> scalarMul<T> (const Matrix<T>& left, const Matrix<T>& right);  // 数乘
    friend Matrix<T> scalarDiv<T> (const Matrix<T>& left, const Matrix<T>& right);

public:
    ~Matrix() noexcept
    {
        if (m_data != nullptr)
            delete[] m_data;
    }

    Matrix(const Matrix& src):
        m_width{src.m_width},
        m_height{src.m_height}
    {
        m_data = new T[m_width * m_height];
        if (m_data == nullptr)
        {
            throw std::bad_alloc{};
        }

        std::copy(src.m_data, src.m_data + m_width * m_height, m_data);
    }

    Matrix(Matrix&& src) noexcept:
        m_width{src.m_width},
        m_height{src.m_height},
        m_data{src.m_data}
    {
        src.m_data = nullptr;
        src.m_width = 0;
        src.m_height = 0;
    }

    Matrix() noexcept:
        m_width{0},
        m_height{0},
        m_data{nullptr}
    {

    }

    Matrix(size_t width, size_t height):
        m_width{width},
        m_height{height}
    {
        m_data = new T[width * height];
        if (m_data == nullptr)
            throw std::bad_alloc{};
    }

    Matrix(size_t width, size_t height, const T& value):
        m_width{width},
        m_height{height}
    {
        m_data = new T[width * height];
        if (m_data == nullptr)
            throw std::bad_alloc{};

        std::fill(m_data, m_data + width * height, value);
    }

    explicit Matrix(const std::vector<std::vector<T>>& values)
    {
        m_height = values.size();
        m_width = values.begin()->size();
        m_data = new T[m_width * m_height];
        if (m_data == nullptr)
        {
            throw std::bad_alloc{};
        }

        size_t y = 0;
        for (const auto& row : values)
        {
            size_t x = 0;
            for (const auto& v : row)
            {
                if (x < row.size())
                {
                    (*this)[y][x] = v;
                }
                else
                {
                    break;
                }
                x++;
            }
            y++;
        }
    }

    explicit Matrix(const std::vector<T>& values, bool row=true)
    {
        if (row)
        {
            m_width = values.size();
            m_height = 1;
        }
        else
        {
            m_width = 1;
            m_height = values.size();
        }

        m_data = new T[m_width * m_height];
        if (m_data == nullptr)
        {
            throw std::bad_alloc{};
        }

        size_t i = 0;
        for (const auto& v : values)
        {
            m_data[i] = v;
            i++;
        }
    }

    size_t width() const noexcept
    {
        return m_width;
    }

    size_t height() const noexcept
    {
        return m_height;
    }

    void reshape(size_t width, size_t height=1)
    {
        if (width * height != m_width * m_height)
            throw std::range_error{__strfmt__("reshape %zu * %zu != %zu * %zu", 
                                                width, height, m_width, m_height)};

        m_width = width;
        m_height = height;
    }

    Matrix<T> transpose() const noexcept
    {
        Matrix<T> result{m_height, m_width};
        for (size_t row = 0; row < m_height; row++)
        {
            for (size_t col = 0; col < m_width; col++)
            {
                result[col][row] = (*this)[row][col];
            }
        }

        return result;
    }

    void map(std::function<void(T& e)> func) noexcept
    {
        for (size_t row = 0; row < m_height; row++)
        {
            for (size_t col = 0; col < m_width; col++)
            {
                func(m_data[row * m_width + col]);
            }
        }
    }

    void map(std::function<void(const T& e)> func) const noexcept
    {
        for (size_t row = 0; row < m_height; row++)
        {
            for (size_t col = 0; col < m_width; col++)
            {
                func(m_data[row * m_width + col]);
            }
        }
    }

    T reduce(std::function<T(const T& x, const T& y)> func) const noexcept
    {
        T value = func(m_data[0], m_data[1]);
        for (size_t i = 2; i < m_width*m_height; i++)
        {
            value = func(value, m_data[i]);
        }

        return value;
    }

    Matrix& operator= (const Matrix& src)
    {
        m_width = src.m_width;
        m_height = src.m_height;

        if (m_data != nullptr)
            delete[] m_data;

        m_data = new T[m_width * m_height];
        if (m_data == nullptr)
        {
            throw std::bad_alloc{};
        }

        std::copy(src.m_data, src.m_data + m_width * m_height, m_data);
        return *this;
    }

    Matrix& operator= (Matrix&& src) noexcept
    {
        if (m_data != nullptr)
            delete[] m_data;

        m_width = src.m_width;
        m_height = src.m_height;
        m_data = src.m_data;

        src.m_data = nullptr;
        src.m_width = 0;
        src.m_height = 0;

        return *this;
    }

    T item(size_t i=0) const
    {
        if (i >= m_width * m_height)
            throw std::out_of_range{__strfmt__("item index %zu is out of height %zu", 
                                                i, m_width * m_height)};
        return m_data[i];
    }

    RowView row(size_t r=0)
    {
        if (r >= m_height)
            throw std::out_of_range{__strfmt__("row index %zu is out of height %zu", 
                                                r, m_height)};

        return RowView(*this, r);
    }

    const RowView row(size_t r=0) const
    {
        if (r >= m_height)
            throw std::out_of_range{__strfmt__("row index %zu is out of height %zu", 
                                                r, m_height)};

        return RowView(*this, r);
    }

    ColView col(size_t c=0)
    {
        if (c >= m_width)
            throw std::out_of_range{__strfmt__("col index %zu is out of range %zu",
                                                c, m_width)};

        return ColView(*this, c);
    }

    const ColView col(size_t c=0) const
    {
        if (c >= m_width)
            throw std::out_of_range{__strfmt__("col index %zu is out of range %zu",
                                                c, m_width)};

        return ColView(*this, c);
    }
    
    RowView operator[] (size_t row)
    {
        if (row >= m_height)
            throw std::out_of_range{__strfmt__("row index %zu is out of height %zu", 
                                                row, m_height)};

        return RowView(*this, row);
    }

    const RowView operator[] (size_t row) const
    {
        if (row >= m_height)
            throw std::out_of_range{__strfmt__("row index %zu is out of height %zu", 
                                                row, m_height)};

        return RowView(*this, row);
    }

    // 加标量
    Matrix<T>& operator += (const T& n) noexcept
    {
        for (size_t row = 0; row < m_height; row++)
        {
            for (size_t col = 0; col < m_width; col++)
            {
                (*this)[row][col] += n;
            }
        }

        return *this;
    }

    // 减标量
    Matrix<T>& operator -= (const T& n) noexcept
    {
        for (size_t row = 0; row < m_height; row++)
        {
            for (size_t col = 0; col < m_width; col++)
            {
                (*this)[row][col] -= n;
            }
        }

        return *this;
    }

    // 乘以标量
    Matrix<T>& operator *= (const T& n) noexcept
    {
        for (size_t row = 0; row < m_height; row++)
        {
            for (size_t col = 0; col < m_width; col++)
            {
                (*this)[row][col] += n;
            }
        }

        return *this;
    }

    // 除以标量
    Matrix<T>& operator /= (const T& n) noexcept
    {
        for (size_t row = 0; row < m_height; row++)
        {
            for (size_t col = 0; col < m_width; col++)
            {
                (*this)[row][col] /= n;
            }
        }

        return *this;
    }

    // 加行向量
    Matrix<T>& operator += (const RowView& vec)
    {
        if (m_width != vec.size())
        throw std::range_error{__strfmt__("matrix width %zu not equal to row width %zu",
                                            m_width, vec.size())};

        for (size_t row = 0; row < m_height; row++)
        {
            for (size_t col = 0; col < m_width; col++)
            {
                (*this)[row][col] += vec[col];
            }
        }

        return *this;
    }

    // 减行向量
    Matrix<T>& operator -= (const RowView& vec)
    {
        if (m_width != vec.size())
        throw std::range_error{__strfmt__("matrix width %zu not equal to row width %zu",
                                            m_width, vec.size())};

        for (size_t row = 0; row < m_height; row++)
        {
            for (size_t col = 0; col < m_width; col++)
            {
                (*this)[row][col] -= vec[col];
            }
        }

        return *this;
    }

    // 乘行向量
    Matrix<T>& operator *= (const RowView& vec)
    {
        if (m_width != vec.size())
        throw std::range_error{__strfmt__("matrix width %zu not equal to row width %zu",
                                            m_width, vec.size())};

        for (size_t row = 0; row < m_height; row++)
        {
            for (size_t col = 0; col < m_width; col++)
            {
                (*this)[row][col] *= vec[col];
            }
        }

        return *this;
    }

    // 除以行向量
    Matrix<T>& operator /= (const RowView& vec)
    {
        if (m_width != vec.size())
        throw std::range_error{__strfmt__("matrix width %zu not equal to row width %zu",
                                            m_width, vec.size())};

        for (size_t row = 0; row < m_height; row++)
        {
            for (size_t col = 0; col < m_width; col++)
            {
                (*this)[row][col] /= vec[col];
            }
        }

        return *this;
    }

    // 加列向量
    Matrix<T> operator += (const ColView& vec)
    {
        if (m_height != vec.size())
            throw std::range_error{__strfmt__("matrix height %zu not equal to row width %zu",
                                                m_height, vec.size())};

        for (size_t y = 0; y < m_height; y++)
        {
            for (size_t x = 0; x < m_width; x++)
            {
                (*this)[row][col] += vec[y];
            }
        }

        return *this;
    }

    // 减列向量
    Matrix<T> operator -= (const ColView& vec)
    {
        if (m_height != vec.size())
            throw std::range_error{__strfmt__("matrix height %zu not equal to row width %zu",
                                                m_height, vec.size())};

        for (size_t y = 0; y < m_height; y++)
        {
            for (size_t x = 0; x < m_width; x++)
            {
                (*this)[row][col] -= vec[y];
            }
        }

        return *this;
    }

    // 乘列向量
    Matrix<T> operator *= (const ColView& vec)
    {
        if (m_height != vec.size())
            throw std::range_error{__strfmt__("matrix height %zu not equal to row width %zu",
                                                m_height, vec.size())};

        for (size_t y = 0; y < m_height; y++)
        {
            for (size_t x = 0; x < m_width; x++)
            {
                (*this)[row][col] *= vec[y];
            }
        }

        return *this;
    }

    // 除以列向量
    Matrix<T> operator /= (const ColView& vec)
    {
        if (m_height != vec.size())
            throw std::range_error{__strfmt__("matrix height %zu not equal to row width %zu",
                                                m_height, vec.size())};

        for (size_t y = 0; y < m_height; y++)
        {
            for (size_t x = 0; x < m_width; x++)
            {
                (*this)[row][col] /= vec[y];
            }
        }

        return *this;
    }

    // 加矩阵
    Matrix<T>& operator += (const Matrix<T>& right)
    {
        if (m_width != right.m_width)
            throw std::range_error{__strfmt__("left matrix width %zu not equal to right matrix width %zu", 
                                                m_width, right.m_width)};
    
        if (m_height != right.m_height)
            throw std::range_error{__strfmt__("left matrix height %zu not equal to right matrix height %zu", 
                                                m_height, right.m_height)};

        for (size_t row = 0; row < m_height; row++)
        {
            for (size_t col = 0; col < m_width; col++)
            {
                (*this)[row][col] = (*this)[row][col] + right[row][col];
            }
        }

        return *this;
    }

    // 减矩阵
    Matrix<T>& operator -= (const Matrix<T>& right)
    {
        if (m_width != right.m_width)
            throw std::range_error{__strfmt__("left matrix width %zu not equal to right matrix width %zu", 
                                                m_width, right.m_width)};
    
        if (m_height != right.m_height)
            throw std::range_error{__strfmt__("left matrix height %zu not equal to right matrix height %zu", 
                                                m_height, right.m_height)};

        for (size_t row = 0; row < m_height; row++)
        {
            for (size_t col = 0; col < m_width; col++)
            {
                (*this)[row][col] = (*this)[row][col] - right[row][col];
            }
        }

        return *this;
    }

    // 数乘矩阵
    Matrix<T>& scalarMul(const Matrix<T>& right)
    {
        if (m_width != right.m_width)
            throw std::range_error{__strfmt__("left matrix width %zu not equal to right matrix width %zu", 
                                                m_width, right.m_width)};
    
        if (m_height != right.m_height)
            throw std::range_error{__strfmt__("left matrix height %zu not equal to right matrix height %zu", 
                                                m_height, right.m_height)};

        for (size_t row = 0; row < m_height; row++)
        {
            for (size_t col = 0; col < m_width; col++)
            {
                (*this)[row][col] = (*this)[row][col] * right[row][col];
            }
        }

        return *this;
    }

    // 数乘矩阵
    Matrix<T>& scalarDiv(const Matrix<T>& right)
    {
        if (m_width != right.m_width)
            throw std::range_error{__strfmt__("left matrix width %zu not equal to right matrix width %zu", 
                                                m_width, right.m_width)};
    
        if (m_height != right.m_height)
            throw std::range_error{__strfmt__("left matrix height %zu not equal to right matrix height %zu", 
                                                m_height, right.m_height)};

        for (size_t row = 0; row < m_height; row++)
        {
            for (size_t col = 0; col < m_width; col++)
            {
                (*this)[row][col] = (*this)[row][col] / right[row][col];
            }
        }

        return *this;
    }

private:
    size_t m_width;
    size_t m_height;
    T* m_data;
};


template<typename T>
class Matrix<T>::RowView
{
public:
    ~RowView() noexcept = default;

    RowView(const Matrix<T>& mat, size_t row) noexcept:
        m_matrix{mat},
        m_row{row}    
    {}

    size_t size() const noexcept
    {
        return m_matrix.m_width;
    }

    T& operator[] (size_t i)
    {
        if (i >= m_matrix.m_width)
            throw std::out_of_range{__strfmt__("col index %zu is out of width %zu", 
                                                i, m_matrix.m_width)};

        return m_matrix.m_data[m_row * m_matrix.m_width + i];
    }

    const T& operator[] (size_t i) const
    {
        if (i >= m_matrix.m_width)
            throw std::out_of_range{__strfmt__("col index %zu is out of width %zu", 
                                                i, m_matrix.m_width)};

        return m_matrix.m_data[m_row * m_matrix.m_width + i];
    }

private:
    const Matrix<T>& m_matrix;
    size_t m_row;
};

template<typename T>
class Matrix<T>::ColView
{
public:
    ~ColView() noexcept = default;

    ColView(const Matrix<T>& mat, size_t col) noexcept:
        m_matrix{mat},
        m_col{col}    
    {}

    size_t size() const noexcept
    {
        return m_matrix.m_height;
    }

    T& operator[] (size_t i)
    {
        if (i >= m_matrix.m_height)
            throw std::out_of_range{__strfmt__("row index %zu is out of height %zu", 
                                                i, m_matrix.m_height)};

        return m_matrix.m_data[i * m_matrix.m_width + m_col];
    }

    const T& operator[] (size_t i) const
    {
        if (i >= m_matrix.m_height)
            throw std::out_of_range{__strfmt__("row index %zu is out of height %zu", 
                                                i, m_matrix.m_height)};

        return m_matrix.m_data[i * m_matrix.m_width + m_col];
    }

private:
    const Matrix<T>& m_matrix;
    size_t m_col;
};

template<typename T>
std::ostream& operator<< (std::ostream& stream, const Matrix<T>& mat)
{
    stream << "[\n";
    for (size_t y = 0; y < mat.m_height; y++)
    {
        stream << "  [ ";
        for (size_t x = 0; x < mat.m_width; x++)
        {
            stream << mat[y][x] << " ";

            if (mat.m_width > 6 && x == 2) 
            {
                stream << "... ";
                x = mat.m_width - 4;
            }
        }
        stream << " ]\n";
    }
    stream << "]\n";
    return stream;
}

template<typename T>
Matrix<T> operator+ (const T& n, const Matrix<T>& mat) noexcept
{
    Matrix<T> result{mat.m_width, mat.m_height};
    for (size_t row = 0; row < result.m_height; row++)
    {
        for (size_t col = 0; col < result.m_width; col++)
        {
            result[row][col] = n + mat[row][col];
        }
    }

    return result;
}

template<typename T>
Matrix<T> operator+ (const Matrix<T>& mat, const T& n) noexcept
{
    return n + mat;
}

template<typename T>
Matrix<T> operator- (const T& n, const Matrix<T>& mat) noexcept
{
    Matrix<T> result{mat.m_width, mat.m_height};
    for (size_t row = 0; row < result.m_height; row++)
    {
        for (size_t col = 0; col < result.m_width; col++)
        {
            result[row][col] = n - mat[row][col];
        }
    }

    return result;
}

template<typename T>
Matrix<T> operator- (const Matrix<T>& mat, const T& n) noexcept
{
    Matrix<T> result{mat.m_width, mat.m_height};
    for (size_t row = 0; row < result.m_height; row++)
    {
        for (size_t col = 0; col < result.m_width; col++)
        {
            result[row][col] = mat[row][col] - n;
        }
    }

    return result;
}

template<typename T>
Matrix<T> operator* (const T& n, const Matrix<T>& mat) noexcept
{
    Matrix<T> result{mat.m_width, mat.m_height};
    for (size_t row = 0; row < result.m_height; row++)
    {
        for (size_t col = 0; col < result.m_width; col++)
        {
            result[row][col] = n * mat[row][col];
        }
    }

    return result;
}

template<typename T>
Matrix<T> operator* (const Matrix<T>& mat, const T& n) noexcept
{
    return n * mat;
}

template<typename T>
Matrix<T> operator/ (const T& n, const Matrix<T>& mat) noexcept
{
    Matrix<T> result{mat.m_width, mat.m_height};
    for (size_t row = 0; row < result.m_height; row++)
    {
        for (size_t col = 0; col < result.m_width; col++)
        {
            result[row][col] = n / mat[row][col];
        }
    }

    return result;
}

template<typename T>
Matrix<T> operator/ (const Matrix<T>& mat, const T& n) noexcept
{
    Matrix<T> result{mat.m_width, mat.m_height};
    for (size_t row = 0; row < result.m_height; row++)
    {
        for (size_t col = 0; col < result.m_width; col++)
        {
            result[row][col] = mat[row][col] / n;
        }
    }

    return result;
}

template<typename T>
Matrix<T> operator+ (const Matrix<T>& mat, const typename Matrix<T>::RowView& vec)
{
    if (mat.m_width != vec.size())
        throw std::range_error{__strfmt__("matrix width %zu not equal to row width %zu",
                                            mat.m_width, vec.size())};

    Matrix<T> result{mat.m_width, mat.m_height};
    for (size_t y = 0; y < mat.m_height; y++)
    {
        for (size_t x = 0; x < mat.m_width; x++)
        {
            result[y][x] = mat[y][x] + vec[x];
        }
    }

    return result;
}

template<typename T>
Matrix<T> operator+ (const typename Matrix<T>::RowView& vec, const Matrix<T>& mat)
{
    return mat + vec;
}

template<typename T>
Matrix<T> operator* (const Matrix<T>& mat, const typename Matrix<T>::RowView& vec)
{
    if (mat.m_width != vec.size())
        throw std::range_error{__strfmt__("matrix width %zu not equal to row width %zu",
                                            mat.m_width, vec.size())};

    Matrix<T> result{mat.m_width, mat.m_height};
    for (size_t y = 0; y < mat.m_height; y++)
    {
        for (size_t x = 0; x < mat.m_width; x++)
        {
            result[y][x] = mat[y][x] * vec[x];
        }
    }

    return result;
}

template<typename T>
Matrix<T> operator* (const typename Matrix<T>::RowView& vec, const Matrix<T>& mat)
{
    return mat * vec;
}

template<typename T>
Matrix<T> operator- (const Matrix<T>& mat, const typename Matrix<T>::RowView& vec)
{
    if (mat.m_width != vec.size())
        throw std::range_error{__strfmt__("matrix width %zu not equal to row width %zu",
                                            mat.m_width, vec.size())};

    Matrix<T> result{mat.m_width, mat.m_height};
    for (size_t y = 0; y < mat.m_height; y++)
    {
        for (size_t x = 0; x < mat.m_width; x++)
        {
            result[y][x] = mat[y][x] - vec[x];
        }
    }

    return result;
}

template<typename T>
Matrix<T> operator- (const typename Matrix<T>::RowView& vec, const Matrix<T>& mat)
{
    if (mat.m_width != vec.size())
        throw std::range_error{__strfmt__("matrix width %zu not equal to row width %zu",
                                            mat.m_width, vec.size())};

    Matrix<T> result{mat.m_width, mat.m_height};
    for (size_t y = 0; y < mat.m_height; y++)
    {
        for (size_t x = 0; x < mat.m_width; x++)
        {
            result[y][x] = vec[x] - mat[y][x];
        }
    }

    return result;
}

template<typename T>
Matrix<T> operator/ (const Matrix<T>& mat, const typename Matrix<T>::RowView& vec)
{
    if (mat.m_width != vec.size())
        throw std::range_error{__strfmt__("matrix width %zu not equal to row width %zu",
                                            mat.m_width, vec.size())};

    Matrix<T> result{mat.m_width, mat.m_height};
    for (size_t y = 0; y < mat.m_height; y++)
    {
        for (size_t x = 0; x < mat.m_width; x++)
        {
            result[y][x] = mat[y][x] / vec[x];
        }
    }

    return result;
}

template<typename T>
Matrix<T> operator/ (const typename Matrix<T>::RowView& vec, const Matrix<T>& mat)
{
    if (mat.m_width != vec.size())
        throw std::range_error{__strfmt__("matrix width %zu not equal to row width %zu",
                                            mat.m_width, vec.size())};

    Matrix<T> result{mat.m_width, mat.m_height};
    for (size_t y = 0; y < mat.m_height; y++)
    {
        for (size_t x = 0; x < mat.m_width; x++)
        {
            result[y][x] = vec[x] / mat[y][x];
        }
    }

    return result;
}

template<typename T>
Matrix<T> operator+ (const Matrix<T>& mat, const typename Matrix<T>::ColView& vec)
{
    if (mat.m_height != vec.size())
        throw std::range_error{__strfmt__("matrix height %zu not equal to row width %zu",
                                            mat.m_height, vec.size())};

    Matrix<T> result{mat.m_width, mat.m_height};
    for (size_t y = 0; y < mat.m_height; y++)
    {
        for (size_t x = 0; x < mat.m_width; x++)
        {
            result[y][x] = mat[y][x] + vec[y];
        }
    }

    return result;
}

template<typename T>
Matrix<T> operator+ (const typename Matrix<T>::ColView& vec, const Matrix<T>& mat)
{
    return mat + vec;
}

template<typename T>
Matrix<T> operator* (const Matrix<T>& mat, const typename Matrix<T>::ColView& vec)
{
    if (mat.m_height != vec.size())
        throw std::range_error{__strfmt__("matrix height %zu not equal to row width %zu",
                                            mat.m_height, vec.size())};

    Matrix<T> result{mat.m_width, mat.m_height};
    for (size_t y = 0; y < mat.m_height; y++)
    {
        for (size_t x = 0; x < mat.m_width; x++)
        {
            result[y][x] = mat[y][x] * vec[y];
        }
    }

    return result;
}

template<typename T>
Matrix<T> operator* (const typename Matrix<T>::ColView& vec, const Matrix<T>& mat)
{
    return mat * vec;
}

template<typename T>
Matrix<T> operator- (const Matrix<T>& mat, const typename Matrix<T>::ColView& vec)
{
    if (mat.m_height != vec.size())
        throw std::range_error{__strfmt__("matrix height %zu not equal to row width %zu",
                                            mat.m_height, vec.size())};

    Matrix<T> result{mat.m_width, mat.m_height};
    for (size_t y = 0; y < mat.m_height; y++)
    {
        for (size_t x = 0; x < mat.m_width; x++)
        {
            result[y][x] = mat[y][x] - vec[y];
        }
    }

    return result;
}

template<typename T>
Matrix<T> operator- (const typename Matrix<T>::ColView& vec, const Matrix<T>& mat)
{
    if (mat.m_height != vec.size())
        throw std::range_error{__strfmt__("matrix height %zu not equal to row width %zu",
                                            mat.m_height, vec.size())};

    Matrix<T> result{mat.m_width, mat.m_height};
    for (size_t y = 0; y < mat.m_height; y++)
    {
        for (size_t x = 0; x < mat.m_width; x++)
        {
            result[y][x] = vec[y] - mat[y][x];
        }
    }

    return result;
}

template<typename T>
Matrix<T> operator/ (const Matrix<T>& mat, const typename Matrix<T>::ColView& vec)
{
    if (mat.m_height != vec.size())
        throw std::range_error{__strfmt__("matrix height %zu not equal to row width %zu",
                                            mat.m_height, vec.size())};

    Matrix<T> result{mat.m_width, mat.m_height};
    for (size_t y = 0; y < mat.m_height; y++)
    {
        for (size_t x = 0; x < mat.m_width; x++)
        {
            result[y][x] = mat[y][x] / vec[y];
        }
    }

    return result;
}

template<typename T>
Matrix<T> operator/ (const typename Matrix<T>::ColView& vec, const Matrix<T>& mat)
{
    if (mat.m_height != vec.size())
        throw std::range_error{__strfmt__("matrix height %zu not equal to row width %zu",
                                            mat.m_height, vec.size())};

    Matrix<T> result{mat.m_width, mat.m_height};
    for (size_t y = 0; y < mat.m_height; y++)
    {
        for (size_t x = 0; x < mat.m_width; x++)
        {
            result[y][x] = vec[y] / mat[y][x];
        }
    }

    return result;
}

template<typename T>
Matrix<T> operator+ (const Matrix<T>& left, const Matrix<T>& right)
{
    if (left.m_width != right.m_width)
        throw std::range_error{__strfmt__("left matrix width %zu not equal to right matrix width %zu", 
                                            left.m_width, right.m_width)};
    
    if (left.m_height != right.m_height)
        throw std::range_error{__strfmt__("left matrix height %zu not equal to right matrix height %zu", 
                                            left.m_height, right.m_height)};

    Matrix<T> result{left.m_width, left.m_height};
    for (size_t row = 0; row < result.m_height; row++)
    {
        for (size_t col = 0; col < result.m_width; col++)
        {
            result[row][col] = left[row][col] + right[row][col];
        }
    }

    return result;
}

template<typename T>
Matrix<T> operator- (const Matrix<T>& left, const Matrix<T>& right)
{
    if (left.m_width != right.m_width)
        throw std::range_error{__strfmt__("left matrix width %zu not equal to right matrix width %zu", 
                                            left.m_width, right.m_width)};
    
    if (left.m_height != right.m_height)
        throw std::range_error{__strfmt__("left matrix height %zu not equal to right matrix height %zu", 
                                            left.m_height, right.m_height)};

    Matrix<T> result{left.m_width, left.m_height};
    for (size_t row = 0; row < result.m_height; row++)
    {
        for (size_t col = 0; col < result.m_width; col++)
        {
            result[row][col] = left[row][col] - right[row][col];
        }
    }

    return result;
}

template<typename T>
Matrix<T> operator* (const Matrix<T>& left, const Matrix<T>& right)
{
    if (left.m_width != right.m_height)
        throw std::range_error{__strfmt__("left matrix width %zu not equal to right matrix height %zu", 
                                            left.m_width, right.m_height)};

    auto transpose = right.transpose();
    Matrix<T> result{right.m_width, left.m_height, T{}};
    for (size_t row = 0; row < result.m_height; row++)
    {
        for (size_t col = 0; col < result.m_width; col++)
        {
            for (size_t i = 0; i < left.m_width; i++)
            {
                result[row][col] += left[row][i] * transpose[col][i];
            }
        }
    }

    return result;
}

template<typename T>
Matrix<T> scalarMul(const Matrix<T>& left, const Matrix<T>& right)
{
    if (left.m_width != right.m_width)
        throw std::range_error{__strfmt__("left matrix width %zu not equal to right matrix width %zu", 
                                            left.m_width, right.m_width)};
    
    if (left.m_height != right.m_height)
        throw std::range_error{__strfmt__("left matrix height %zu not equal to right matrix height %zu", 
                                            left.m_height, right.m_height)};

    Matrix<T> result{left.m_width, left.m_height};
    for (size_t row = 0; row < result.m_height; row++)
    {
        for (size_t col = 0; col < result.m_width; col++)
        {
            result[row][col] = left[row][col] * right[row][col];
        }
    }

    return result;
}

template<typename T>
Matrix<T> scalarDiv(const Matrix<T>& left, const Matrix<T>& right)
{
    if (left.m_width != right.m_width)
        throw std::range_error{__strfmt__("left matrix width %zu not equal to right matrix width %zu", 
                                            left.m_width, right.m_width)};
    
    if (left.m_height != right.m_height)
        throw std::range_error{__strfmt__("left matrix height %zu not equal to right matrix height %zu", 
                                            left.m_height, right.m_height)};

    Matrix<T> result{left.m_width, left.m_height};
    for (size_t row = 0; row < result.m_height; row++)
    {
        for (size_t col = 0; col < result.m_width; col++)
        {
            result[row][col] = left[row][col] / right[row][col];
        }
    }

    return result;
}

}; // namespace Lycoris

#endif // LYCORIS_MATRIX_HPP