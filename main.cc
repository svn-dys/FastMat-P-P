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
    size_t GetMatrixSize() const { return matrix_size_; }

    // Debugging
    void PrintMatrix() {
        LOG("Matrix:")
        LOG("------------------------------------------------------------------");
        for (size_t i = 0; i < GetRowsSize(); ++i) {
            std::cout << "{ ";
            for (size_t j = 0; j < GetColumnsSize(); ++j) {
                std::cout << this->operator()(i,j);
                if (j < columns_ - 1) {
                    std::cout << ", ";
                }
            }
            std::cout << " }" << std::endl;
        } 
        LOG("------------------------- EO Matrix ------------------------------")
    }

private:
    size_t rows_, columns_, matrix_size_;
    size_t* matrix_arr_;
};


int main()
{   
    Matrix2D matrix(5, 4);
    matrix(0, 2) = 7;
    matrix(1,2) = 7;
    matrix(2,2) = 7;
    matrix.PrintMatrix();
    return 0;
}