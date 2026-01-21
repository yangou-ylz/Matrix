#include "Matrix.h"
#include <iostream>

void testAllFunctions()
{
    std::cout << "=== 测试矩阵类所有12个功能 ===" << std::endl
              << std::endl;

    try
    {
        // 功能1：创建矩阵
        std::cout << "1. 创建3x3矩阵：" << std::endl;
        MyMatrix A(3, 3);
        A(0, 0) = 1;
        A(0, 1) = 2;
        A(0, 2) = 3;
        A(1, 0) = 0;
        A(1, 1) = 4;
        A(1, 2) = 5;
        A(2, 0) = 1;
        A(2, 1) = 0;
        A(2, 2) = 6;
        A.print();

        // 功能2：置零和置一
        std::cout << "\n2. 置一测试（2x2矩阵）：" << std::endl;
        MyMatrix ones(2, 2);
        ones.setAllOnes();
        ones.print();

        std::cout << "置零测试（2x2矩阵）：" << std::endl;
        ones.setAllZeros();
        ones.print();

        // 再测试一个3x3的置一
        std::cout << "置一测试（3x3矩阵）：" << std::endl;
        MyMatrix ones3x3(3, 3);
        ones3x3.setAllOnes();
        ones3x3.print();

        // 功能3：取负值
        std::cout << "\n3. 取负值测试：" << std::endl;
        MyMatrix negA = A.negative();
        negA.print();

        // 功能4：数乘
        std::cout << "\n4. 数乘测试（乘以2）：" << std::endl;
        MyMatrix scaled = A.scalarMultiply(2.0);
        scaled.print();

        // 功能5：矩阵运算
        std::cout << "\n5. 矩阵运算测试：" << std::endl;
        MyMatrix B(3, 3);
        B(0, 0) = 2;
        B(0, 1) = 0;
        B(0, 2) = 1;
        B(1, 0) = 3;
        B(1, 1) = 2;
        B(1, 2) = 4;
        B(2, 0) = 1;
        B(2, 1) = 1;
        B(2, 2) = 2;

        std::cout << "矩阵B：" << std::endl;
        B.print();

        std::cout << "A + B：" << std::endl;
        (A + B).print();

        std::cout << "A - B：" << std::endl;
        (A - B).print();

        std::cout << "A * B：" << std::endl;
        (A * B).print();

        // 功能6：初等变换（修正行列编号表述为1-based）
        std::cout << "\n6. 初等变换测试：" << std::endl;
        MyMatrix C = A;
        std::cout << "原始矩阵：" << std::endl;
        C.print();

        std::cout << "交换第1行和第2行（内部索引0和1）：" << std::endl;
        C.rowSwap(0, 1);
        C.print();

        std::cout << "第3行乘以2（内部索引2）：" << std::endl;
        C.rowMultiply(2, 2.0);
        C.print();

        std::cout << "第1行加上第2行的3倍（内部索引0加上索引1的3倍）：" << std::endl;
        C.rowAddMultiple(0, 1, 3.0);
        C.print();

        // 功能7：转置
        std::cout << "\n7. 转置测试：" << std::endl;
        std::cout << "A的转置：" << std::endl;
        A.transpose().print();

        // 功能8：余子式
        std::cout << "\n8. 余子式测试：" << std::endl;
        std::cout << "A关于第1行第1列元素(1,1)的余子式：" << std::endl;
        MyMatrix minor = A.getMinor(0, 0);
        minor.print();

        // 功能9：伴随矩阵和逆矩阵
        std::cout << "\n9. 伴随矩阵和逆矩阵测试：" << std::endl;
        if (!A.isSingular())
        {
            std::cout << "A的伴随矩阵：" << std::endl;
            A.adjoint().print();

            std::cout << "A的逆矩阵：" << std::endl;
            A.inverse().print();

            std::cout << "验证 A * A⁻¹ = I：" << std::endl;
            (A * A.inverse()).print();
        }
        else
        {
            std::cout << "A是奇异矩阵，不可逆" << std::endl;
        }

        // 功能10：行列式
        std::cout << "\n10. 行列式测试：" << std::endl;
        std::cout << "det(A) = " << A.determinant() << std::endl;

        // 功能11：奇异矩阵判断
        std::cout << "\n11. 奇异矩阵判断测试：" << std::endl;
        std::cout << "A是奇异矩阵：" << (A.isSingular() ? "是" : "否") << std::endl;

        // 测试奇异矩阵（3x3矩阵）
        std::cout << "\n测试3x3奇异矩阵：" << std::endl;
        MyMatrix singular3x3(3, 3);
        singular3x3(0, 0) = 1;
        singular3x3(0, 1) = 2;
        singular3x3(0, 2) = 3;
        singular3x3(1, 0) = 4;
        singular3x3(1, 1) = 5;
        singular3x3(1, 2) = 6;
        singular3x3(2, 0) = 7;
        singular3x3(2, 1) = 8;
        singular3x3(2, 2) = 9;
        std::cout << "奇异矩阵（3x3）：" << std::endl;
        singular3x3.print();
        std::cout << "是奇异矩阵：" << (singular3x3.isSingular() ? "是" : "否") << std::endl;
        std::cout << "行列式 = " << singular3x3.determinant() << std::endl;

        // 测试错误处理
        std::cout << "\n12. 错误处理测试：" << std::endl;
        try
        {
            MyMatrix M1(2, 3);
            MyMatrix M2(3, 2);
            MyMatrix M3 = M1 + M2; // 维度不匹配
        }
        catch (const MyMatrix::MatrixException &e)
        {
            std::cout << "捕获异常（加法维度不匹配）：" << e.what() << std::endl;
        }

        try
        {
            singular3x3.inverse(); // 奇异矩阵求逆
        }
        catch (const MyMatrix::MatrixException &e)
        {
            std::cout << "捕获异常（奇异矩阵求逆）：" << e.what() << std::endl;
        }

        // 测试更多功能
        std::cout << "\n=== 额外测试：列变换 ===" << std::endl;
        MyMatrix D = A;
        std::cout << "原始矩阵：" << std::endl;
        D.print();

        std::cout << "交换第1列和第2列：" << std::endl;
        D.colSwap(0, 1);
        D.print();

        std::cout << "第3列乘以2：" << std::endl;
        D.colMultiply(2, 2.0);
        D.print();
    }
    catch (const MyMatrix::MatrixException &e)
    {
        std::cout << "矩阵异常：" << e.what() << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cout << "标准异常：" << e.what() << std::endl;
    }
}

int main()
{
    std::cout << "矩阵类完整功能测试" << std::endl;
    std::cout << "==================" << std::endl;
    std::cout << "注意：内部使用0-based索引，但用户界面显示为1-based" << std::endl;
    std::cout << std::endl;

    testAllFunctions();

    return 0;
}