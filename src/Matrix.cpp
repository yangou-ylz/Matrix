#include "Matrix.h"
#include <cmath>

// 构造函数
MyMatrix::MyMatrix() : rows(0), cols(0) {}

MyMatrix::MyMatrix(int r, int c, double value) : rows(r), cols(c) {
    if (r <= 0 || c <= 0) throw MatrixException("Invalid dimensions");
    data.resize(rows, std::vector<double>(cols, value));
}

MyMatrix::MyMatrix(const std::vector<std::vector<double>>& mat) {
    rows = mat.size();
    if (rows == 0) {
        cols = 0;
        return;
    }
    cols = mat[0].size();
    data = mat;
    for (int i = 1; i < rows; i++) {
        if (mat[i].size() != cols) {
            throw MatrixException("Inconsistent row lengths");
        }
    }
}

// (1) 初始化全零矩阵
void MyMatrix::initializeZero() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            data[i][j] = 0.0;
        }
    }
}

// (2) 置零和置一
void MyMatrix::setAllZeros() {
    initializeZero();
}

void MyMatrix::setAllOnes() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            data[i][j] = 1.0;
        }
    }
}

// (3) 取负值
MyMatrix MyMatrix::negative() const {
    MyMatrix result(rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result(i, j) = -(*this)(i, j);
        }
    }
    return result;
}

// (4) 数乘
MyMatrix MyMatrix::scalarMultiply(double scalar) const {
    MyMatrix result(rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result(i, j) = (*this)(i, j) * scalar;
        }
    }
    return result;
}

// (5) 矩阵运算
MyMatrix MyMatrix::operator+(const MyMatrix& other) const {
    if (rows != other.rows || cols != other.cols) {
        throw DimensionMismatchException("Addition dimension mismatch");
    }
    MyMatrix result(rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result(i, j) = (*this)(i, j) + other(i, j);
        }
    }
    return result;
}

MyMatrix MyMatrix::operator-(const MyMatrix& other) const {
    if (rows != other.rows || cols != other.cols) {
        throw DimensionMismatchException("Subtraction dimension mismatch");
    }
    MyMatrix result(rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result(i, j) = (*this)(i, j) - other(i, j);
        }
    }
    return result;
}

MyMatrix MyMatrix::operator*(const MyMatrix& other) const {
    if (cols != other.rows) {
        throw DimensionMismatchException("Multiplication dimension mismatch");
    }
    MyMatrix result(rows, other.cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < other.cols; j++) {
            double sum = 0.0;
            for (int k = 0; k < cols; k++) {
                sum += (*this)(i, k) * other(k, j);
            }
            result(i, j) = sum;
        }
    }
    return result;
}

MyMatrix MyMatrix::elementwiseDivide(const MyMatrix& other) const {
    if (rows != other.rows || cols != other.cols) {
        throw DimensionMismatchException("Division dimension mismatch");
    }
    MyMatrix result(rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (std::abs(other(i, j)) < 1e-10) {
                throw SingularMatrixException("Division by zero");
            }
            result(i, j) = (*this)(i, j) / other(i, j);
        }
    }
    return result;
}

// (6) 初等变换
void MyMatrix::rowSwap(int row1, int row2) {
    if (row1 < 0 || row1 >= rows || row2 < 0 || row2 >= rows) {
        throw MatrixException("Row index out of bounds");
    }
    std::swap(data[row1], data[row2]);
}

void MyMatrix::colSwap(int col1, int col2) {
    if (col1 < 0 || col1 >= cols || col2 < 0 || col2 >= cols) {
        throw MatrixException("Column index out of bounds");
    }
    for (int i = 0; i < rows; i++) {
        std::swap(data[i][col1], data[i][col2]);
    }
}

void MyMatrix::rowMultiply(int row, double scalar) {
    if (row < 0 || row >= rows) throw MatrixException("Row index out of bounds");
    for (int j = 0; j < cols; j++) {
        data[row][j] *= scalar;
    }
}

void MyMatrix::colMultiply(int col, double scalar) {
    if (col < 0 || col >= cols) throw MatrixException("Column index out of bounds");
    for (int i = 0; i < rows; i++) {
        data[i][col] *= scalar;
    }
}

void MyMatrix::rowAddMultiple(int targetRow, int sourceRow, double scalar) {
    if (targetRow < 0 || targetRow >= rows || sourceRow < 0 || sourceRow >= rows) {
        throw MatrixException("Row index out of bounds");
    }
    for (int j = 0; j < cols; j++) {
        data[targetRow][j] += scalar * data[sourceRow][j];
    }
}

void MyMatrix::colAddMultiple(int targetCol, int sourceCol, double scalar) {
    if (targetCol < 0 || targetCol >= cols || sourceCol < 0 || sourceCol >= cols) {
        throw MatrixException("Column index out of bounds");
    }
    for (int i = 0; i < rows; i++) {
        data[i][targetCol] += scalar * data[i][sourceCol];
    }
}

// (7) 转置
MyMatrix MyMatrix::transpose() const {
    MyMatrix result(cols, rows);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result(j, i) = (*this)(i, j);
        }
    }
    return result;
}

// (8) 余子式
MyMatrix MyMatrix::getMinor(int row, int col) const {
    if (!isSquare() || rows <= 1) {
        throw MatrixException("Minor requires square matrix of size >= 2");
    }
    if (row < 0 || row >= rows || col < 0 || col >= cols) {
        throw MatrixException("Invalid indices for minor");
    }

    MyMatrix result(rows - 1, cols - 1);
    int r = 0;
    for (int i = 0; i < rows; i++) {
        if (i == row) continue;
        int c = 0;
        for (int j = 0; j < cols; j++) {
            if (j == col) continue;
            result(r, c) = (*this)(i, j);
            c++;
        }
        r++;
    }
    return result;
}

// (9) 伴随矩阵和逆矩阵
MyMatrix MyMatrix::adjoint() const {
    if (!isSquare()) throw MatrixException("Adjoint requires square matrix");

    MyMatrix adj(rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            MyMatrix minor = getMinor(i, j);
            double cofactor = ((i + j) % 2 == 0 ? 1 : -1) * minor.determinant();
            adj(j, i) = cofactor;  // 注意转置
        }
    }
    return adj;
}

MyMatrix MyMatrix::inverse() const {
    if (!isSquare()) throw MatrixException("Inverse requires square matrix");

    double det = determinant();
    if (std::abs(det) < 1e-10) {
        throw SingularMatrixException("Matrix is singular");
    }

    return adjoint().scalarMultiply(1.0 / det);
}

// (10) 行列式
double MyMatrix::determinant() const {
    if (!isSquare()) throw MatrixException("Determinant requires square matrix");
    return calculateDeterminant(*this);
}

double MyMatrix::calculateDeterminant(const MyMatrix& mat) const {
    int n = mat.getRows();
    if (n == 1) return mat(0, 0);
    if (n == 2) return mat(0, 0) * mat(1, 1) - mat(0, 1) * mat(1, 0);

    double det = 0.0;
    int sign = 1;
    for (int j = 0; j < n; j++) {
        MyMatrix sub = mat.getSubMatrix(0, j);
        det += sign * mat(0, j) * calculateDeterminant(sub);
        sign = -sign;
    }
    return det;
}

// 获取子矩阵（辅助函数）
MyMatrix MyMatrix::getSubMatrix(int excludeRow, int excludeCol) const {
    MyMatrix sub(rows - 1, cols - 1);
    int r = 0;
    for (int i = 0; i < rows; i++) {
        if (i == excludeRow) continue;
        int c = 0;
        for (int j = 0; j < cols; j++) {
            if (j == excludeCol) continue;
            sub(r, c) = (*this)(i, j);
            c++;
        }
        r++;
    }
    return sub;
}

// (11) 判断奇异矩阵
bool MyMatrix::isSingular() const {
    if (!isSquare()) return false;
    try {
        double det = determinant();
        return std::abs(det) < 1e-10;
    }
    catch (...) {
        return true;
    }
}

// (12) 输出矩阵
void MyMatrix::print() const {
    std::cout << std::fixed << std::setprecision(4);
    for (int i = 0; i < rows; i++) {
        std::cout << "[ ";
        for (int j = 0; j < cols; j++) {
            std::cout << std::setw(8) << (*this)(i, j) << " ";
        }
        std::cout << "]" << std::endl;
    }
}

// 访问元素
double& MyMatrix::operator()(int row, int col) {
    if (row < 0 || row >= rows || col < 0 || col >= cols) {
        throw MatrixException("Index out of bounds");
    }
    return data[row][col];
}

const double& MyMatrix::operator()(int row, int col) const {
    if (row < 0 || row >= rows || col < 0 || col >= cols) {
        throw MatrixException("Index out of bounds");
    }
    return data[row][col];
}