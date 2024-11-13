#include <iostream>
#include <cmath>
#include <stdexcept>
#include <iterator>

#define LOG(msg) std::cout << msg << std::endl;

class Matrix2D {
public:
    Matrix2D (size_t rows, size_t columns) 
        : rows_(rows),
          columns_(columns),
          matrix_size_(columns * rows),
          /* The below is extremely slow. */
          matrix_arr_(new size_t[rows_ * columns_]()) { }

    ~Matrix2D() 
    {
        delete[] matrix_arr_;
    }
    
    Matrix2D& operator=(const Matrix2D& rhs) noexcept {
        if (this != &rhs) {
            delete[] this->matrix_arr_;
            
            this->rows_ = rhs.rows_;
            this->columns_ = rhs.columns_;
            this->matrix_arr_ = new size_t[rows_ * columns_];

            for(size_t i = 0; i < rows_ * columns_; i++) 
            {
                // TODO optimize 
                this->matrix_arr_[i] = rhs.matrix_arr_[i];
            }
        }

        // Returning *this will allow assignment chainging e.g. m_A = m_B = m_C;
        return *this;
    }

    // Return desired valued at specified index.
    size_t& operator()(size_t row_index, size_t col_index) {
        if (row_index >= rows_ || col_index >= columns_)
            throw std::invalid_argument("Out-of-bounds access on Matrix array.");

        return matrix_arr_[row_index * columns_ + col_index];
    }

    // Getters & Setters
    size_t GetRowsSize() const { return rows_; }
    size_t GetColumnsSize() const { return columns_; }

private:
    size_t rows_, columns_, matrix_size_;
    size_t* matrix_arr_;
};


int main()
{   
    Matrix2D matrix(7, 9);
    matrix(0, 2) = 3;
    LOG("Rows: " << matrix.GetRowsSize() << " Columns: " 
              << matrix.GetColumnsSize())
    LOG("Val: " << matrix(3, 4));
    LOG("Val: " << matrix(0, 2));

    Matrix2D matrix_A(10000, 20000);
    Matrix2D matrix_B(300, 400);
    Matrix2D matrix_C(300, 400);
    matrix_A = matrix_B = matrix_C;

    return 0;
}