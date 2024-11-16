#include <iostream>
#include <cmath>
#include <stdexcept>
#include <random>
#include <ctime>

#define LOG(msg) std::cout << msg << std::endl;

class Matrix2D {
public:
    Matrix2D() 
        : rows_(0), columns_(0), matrix_size_(0),
          matrix_arr_(nullptr) { }

    Matrix2D(size_t rows, size_t columns) 
        : rows_(rows), columns_(columns), matrix_size_(rows * columns),
          matrix_arr_(new size_t[rows * columns]()) { }

    // Supplied array contructor
    Matrix2D(size_t rows, size_t columns, size_t* array[]) 
        : rows_(rows), columns_(columns), matrix_size_(rows * columns),
          matrix_arr_(*array) { }

    ~Matrix2D() {
        delete[] matrix_arr_;
    }

    // Copy Assignment Operator
    Matrix2D& operator=(const Matrix2D& rhs) noexcept {
        if (this != &rhs) {
            delete[] matrix_arr_;
            
            rows_ = rhs.rows_;
            columns_ = rhs.columns_;
            matrix_size_ = rhs.matrix_size_;
            matrix_arr_ = new size_t[rows_ * columns_];

            for (size_t i = 0; i < rows_ * columns_; i++) {
                matrix_arr_[i] = rhs.matrix_arr_[i]; // TODO: optimize 
            }
        }
        return *this;
    }

    // Return value at specified index
    size_t& operator()(size_t row_index, size_t col_index) {
        if (row_index >= rows_ || col_index >= columns_)
            throw std::invalid_argument("Out-of-bounds access on Matrix array.");
        return matrix_arr_[row_index * columns_ + col_index];
    }

    // Matrix multiplication
    Matrix2D operator*(Matrix2D& rhs) {
        if (columns_ != rhs.rows_)
            throw std::invalid_argument("Left hand matrix's columns length must equal right hand matrix's row length.");
        
        Matrix2D product_matrix(rows_, rhs.columns_);
        for (size_t row = 0; row < rows_; row++) {
            for (size_t col = 0; col < rhs.columns_; col++) {
                for (size_t k = 0; k < columns_; k++) {
                    product_matrix(row, col) += (*this)(row, k) * rhs(k, col);
                }
            }
        }
        return product_matrix;
    }

    // Getters
    size_t GetRowsSize() const { return rows_; }
    size_t GetColumnsSize() const { return columns_; }
    size_t GetMatrixSize() const { return matrix_size_; }

    // Print matrix contents
    void PrintMatrix() {
        LOG("Matrix:");
        LOG("------------------------------------------------------------------");
        for (size_t i = 0; i < rows_; ++i) {
            std::cout << "{ ";
            for (size_t j = 0; j < columns_; ++j) {
                std::cout << this->operator()(i, j);
                if (j < columns_ - 1) {
                    std::cout << ", ";
                }
            }
            std::cout << " }" << std::endl;
        } 
        LOG("------------------------- EO Matrix ------------------------------");
    }

    // Mock Matrix function for testing
    Matrix2D MockMatrix(size_t&& rows, size_t&& columns, std::pair<int, int>&& range) {
        std::mt19937 rng(static_cast<unsigned>(std::time(nullptr)));
        size_t min_value = 0;
        size_t max_value = 1000;
        std::uniform_int_distribution<size_t> size_t_dist(range.first, range.second);

        size_t* temp_matrix_arr = new size_t[rows * columns]();
        for (size_t i = 0; i < rows * columns; i++) {
            temp_matrix_arr[i] = size_t_dist(rng);
        }
        Matrix2D temp_matrix(rows, columns, &temp_matrix_arr);
        
        return temp_matrix;
    }

private:
    size_t rows_, columns_, matrix_size_;
    size_t* matrix_arr_;
};

int main() {           
    Matrix2D mock_matrix_1;
    mock_matrix_1 = mock_matrix_1.MockMatrix(1024, 1024, {0, 200});
    
    Matrix2D mock_matrix_2;
    mock_matrix_2 = mock_matrix_2.MockMatrix(1024, 1024, {0, 200});

    Matrix2D sum_mock_matrix = mock_matrix_1 * mock_matrix_2;
    sum_mock_matrix.PrintMatrix();

    return 0;
}
