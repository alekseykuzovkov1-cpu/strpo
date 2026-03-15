#include "matrix.hpp"
#include <iostream>
#include <stdexcept>
#include <cstring>
using namespace std;

// выделение памяти
void Matrix::allocate_memory() {
    data_ = new double*[rows_];
    for (int i = 0; i < rows_; i++) {
        data_[i] = new double[cols_];
    }
}

// освобождение памяти
void Matrix::deallocate_memory() {
    if (data_) {
        for (int i = 0; i < rows_; i++) {
            delete[] data_[i];
        }
        delete[] data_;
        data_ = nullptr;
    }
    rows_ = 0;
    cols_ = 0;
}

// копирование данных
void Matrix::copy_data(const Matrix& other) {
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            data_[i][j] = other.data_[i][j];
        }
    }
}

// единичная матрица nxn
Matrix::Matrix(int n) : rows_(n), cols_(n) {
    if (n <= 0) {
        throw invalid_argument("Размер матрицы должен быть положительным");
    }
    
    allocate_memory();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            data_[i][j] = 0.0;
        }
    }
    
    for (int i = 0; i < n; i++) {
        data_[i][i] = 1.0;
    }
}

// матрица mxn с fill_value
Matrix::Matrix(int m, int n, double fill_value) : rows_(m), cols_(n) {
    if (m <= 0 || n <= 0) {
        throw invalid_argument("Размеры матрицы должны быть положительными");
    }
    
    allocate_memory();
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            data_[i][j] = fill_value;
        }
    }
}

// конструктор копирования
Matrix::Matrix(const Matrix& other) : rows_(other.rows_), cols_(other.cols_) {
    allocate_memory();
    copy_data(other);
}

Matrix::~Matrix() {
    deallocate_memory();
}

// оператор присваивания
Matrix& Matrix::operator=(const Matrix& other) {
    if (this != &other) {
        deallocate_memory();
        rows_ = other.rows_;
        cols_ = other.cols_;
        allocate_memory();
        copy_data(other);
    }
    return *this;
}

// проверка индексов
void Matrix::check_index(int i, int j) const {
    if (i < 0 || i >= rows_ || j < 0 || j >= cols_) {
        throw out_of_range("Индекс выходит за границы матрицы");
    }
}

// получить значение элемента
double Matrix::get(int i, int j) const {
    check_index(i, j);
    return data_[i][j];
}

// установить значение элемента
void Matrix::set(int i, int j, double value) {
    check_index(i, j);
    data_[i][j] = value;
}

// -A
void Matrix::negate() {
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            data_[i][j] = -data_[i][j];
        }
    }
}

// this += other
void Matrix::add_in_place(Matrix& other) {
    if (rows_ != other.rows_ || cols_ != other.cols_) {
        throw invalid_argument("Размеры матриц не совпадают для сложения");
    }
    
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            data_[i][j] += other.data_[i][j];
        }
    }
}

// операция умножения матриц
Matrix Matrix::multiply(Matrix& other) const {
    if (cols_ != other.rows_) {
        throw invalid_argument("Несовместимые размеры для умножения матриц");
    }
    
    Matrix result(rows_, other.cols_, 0.0);
    
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < other.cols_; j++) {
            double sum = 0.0;
            for (int k = 0; k < cols_; k++) {
                sum += data_[i][k] * other.data_[k][j];
            }
            result.data_[i][j] = sum;
        }
    }
    
    return result;
}

// вывод матрицы
void Matrix::print() const {
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            cout << data_[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}