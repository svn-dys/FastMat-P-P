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
    
    // Copy Assignment Operator
    Matrix2D& operator=(const Matrix2D& rhs) noexcept {
        if (this != &rhs) {
            delete[] this->matrix_arr_;
            
            this->rows_ = rhs.rows_;
            this->columns_ = rhs.columns_;
            this->matrix_arr_ = new size_t[rows_ * columns_];

            for(size_t i = 0; i < rows_ * columns_; i++) 
            {
                this->matrix_arr_[i] = rhs.matrix_arr_[i]; // TODO: optimize 
            }
        }
        return *this;
    }

    // Return desired valued at specified index.
    size_t& operator()(size_t row_index, size_t col_index) {
        if (row_index >= rows_ || col_index >= columns_)
            throw std::invalid_argument("Out-of-bounds access on Matrix array.");

        return matrix_arr_[row_index * columns_ + col_index];
    }

    // Matrix multiplication.
    void operator*(Matrix2D& rhs) {
        if (this->GetColumnsSize() != rhs.GetRowsSize())
            throw std::invalid_argument("Left hand matrix's columns length must be equal to right hand matrix's row/s length.");
        
        Matrix2D product_matrix(this->GetRowsSize(), rhs.GetColumnsSize());
        for (size_t i = 0; i < this->GetRowsSize(); i++) {
            for (size_t j = 0; j < rhs.GetColumnsSize(); j++) {
                product_matrix(i,j) = this->operator()(i,j) * rhs(i, j);
            }
        }

        product_matrix.PrintMatrix();
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
    Matrix2D m_B(2,3);
    m_B(0,0) = 2; m_B(0,1) = 3; m_B(0,2) = 1; 
    m_B(1,0) = 3; m_B(1,1) = 5; m_B(1,2) = 6; 
    Matrix2D m_C(3,2);
    m_C(0,0) = 2; m_C(0,1) = 3; 
    m_C(1,0) = 3; m_C(1,1) = 5;

    m_B * m_C;
    return 0;
}