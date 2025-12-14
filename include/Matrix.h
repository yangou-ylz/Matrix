#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <vector>
#include <stdexcept>
#include <iomanip>

class MyMatrix {
private:
    std::vector<std::vector<double>> data;
    int rows;
    int cols;

    // 辅助函数
    MyMatrix getSubMatrix(int excludeRow, int excludeCol) const;
    double calculateDeterminant(const MyMatrix& mat) const;
    MyMatrix getAdjointMatrix() const;

public:
    // 构造函数
    MyMatrix();
    MyMatrix(int r, int c, double value = 0.0);
    MyMatrix(const std::vector<std::vector<double>>& mat);

    // 基本功能
    int getRows() const { return rows; }
    int getCols() const { return cols; }
    bool isSquare() const { return rows == cols; }

    // (1) 初始化全零矩阵
    void initializeZero();

    // (2) 将所有元素置零或置一
    void setAllZeros();
    void setAllOnes();

    // (3) 将矩阵所有元素取负值
    MyMatrix negative() const;

    // (4) 矩阵数乘
    MyMatrix scalarMultiply(double scalar) const;

    // (5) 矩阵运算
    MyMatrix operator+(const MyMatrix& other) const;
    MyMatrix operator-(const MyMatrix& other) const;
    MyMatrix operator*(const MyMatrix& other) const;
    MyMatrix elementwiseDivide(const MyMatrix& other) const;

    // (6) 初等行/列变换
    void rowSwap(int row1, int row2);
    void colSwap(int col1, int col2);
    void rowMultiply(int row, double scalar);
    void colMultiply(int col, double scalar);
    void rowAddMultiple(int targetRow, int sourceRow, double scalar);
    void colAddMultiple(int targetCol, int sourceCol, double scalar);

    // (7) 转置
    MyMatrix transpose() const;

    // (8) 获取指定元素的余子式
    MyMatrix getMinor(int row, int col) const;

    // (9) 伴随矩阵和逆矩阵
    MyMatrix adjoint() const;
    MyMatrix inverse() const;

    // (10) 计算行列式
    double determinant() const;

    // (11) 判断是否为奇异矩阵
    bool isSingular() const;

    // (12) 输出矩阵
    void print() const;

    // 访问元素
    double& operator()(int row, int col);
    const double& operator()(int row, int col) const;

    // 异常类
    class MatrixException : public std::runtime_error {
    public:
        MatrixException(const std::string& msg) : std::runtime_error(msg) {}
    };

    class DimensionMismatchException : public MatrixException {
    public:
        DimensionMismatchException(const std::string& msg) : MatrixException(msg) {}
    };

    class SingularMatrixException : public MatrixException {
    public:
        SingularMatrixException(const std::string& msg) : MatrixException(msg) {}
    };
};

#endif