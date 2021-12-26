#include "matrix/matrix.hpp"

#include "gtest/gtest.h"

class ZeroMatricies: public ::testing::Test
{
        protected:
                ZeroMatricies()
                {

                }

                math::Matrixd<1> singleton;
                math::Vectord<2> vector;
                math::Matrixd<2,2> matrix;
};


TEST_F(ZeroMatricies, Zeros)
{
        ASSERT_EQ(vector(0), 0.0);
}

TEST(Vector, Ones)
{
        auto vector = math::Vector<int, 3>(1);
        ASSERT_EQ(vector(0), 1);
}

TEST_F(ZeroMatricies, AccessElement)
{
        ASSERT_EQ(matrix(0), vector);
}

TEST_F(ZeroMatricies, AccessElement2)
{
        auto ans = math::Vector<double, 2>(1.0);
        ASSERT_NE(matrix(0), ans);
}

TEST(Multiply, MatrixVector)
{
        auto matrix = math::Matrix<int, 2, 2>(1.0);
        auto vector = math::Vector<int, 2>(1.0);
        auto result = matrix*vector;
        ASSERT_EQ(result(0), 2.0);
}

TEST(Multiply, MatrixMatrix)
{
        auto A = math::Matrix<int, 2, 2>(1.0);
        auto B = math::Matrix<int, 2, 2>(1.0);
        auto result = A*B;
        auto answer = math::Matrix<int, 2, 2>(2.0);
        ASSERT_EQ(result, answer);
}

class MultiDimensional: public ::testing::Test
{
        protected:
                MultiDimensional()
                {

                }
                math::Vectori<2> vector{{1, 2}};
                math::Matrixi<2, 2> matrix{{
                        {1, 2},
                        {3, 4}
                }};
                math::Matrixi<2, 2, 2> tensor{{
                        {
                                {1, 2},
                                {3, 4}
                        },
                        {
                                {5, 6},
                                {7, 8}
                        }
                }};
};

TEST_F(MultiDimensional, CreateVector)
{
        ASSERT_EQ(vector(0), 1);
        ASSERT_EQ(vector(1), 2);
}

TEST_F(MultiDimensional, CreateMatrix)
{
        ASSERT_EQ(matrix(0,0), 1);
        ASSERT_EQ(matrix(0,1), 2);
        ASSERT_EQ(matrix(1,0), 3);
        ASSERT_EQ(matrix(1,1), 4);
        ASSERT_EQ(matrix(0), vector);
}

TEST_F(MultiDimensional, AssignElement)
{
        matrix(0,0) = 6;
        ASSERT_EQ(matrix(0,0), 6);
}

TEST_F(MultiDimensional, AssignTensorElement)
{
        tensor(0,0,0) = 0;
        ASSERT_EQ(tensor(0,0,0), 0);
}

TEST_F(MultiDimensional, GetFirstTensorMatrix)
{
        ASSERT_EQ(tensor(0), matrix);
}

TEST_F(MultiDimensional, GetFirstTensorVector)
{
        ASSERT_EQ(tensor(0,0), vector);
}

TEST_F(MultiDimensional, SetFirstTensorVector)
{
        math::Vectori<2> new_vector = {{100, 101}};
        ASSERT_NE(tensor(0,0), new_vector);
        tensor(0,0) = new_vector;
        ASSERT_EQ(tensor(0,0), new_vector);
}