#include <gtest\gtest.h>
#include "Math\Matrix2D.h"

using Math::Matrix2D;

TEST(Matrix2D, Constructor)
{
	Matrix2D identity;
	EXPECT_FLOAT_EQ(identity.r0c0, 1.0f);
	EXPECT_FLOAT_EQ(identity.r0c1, 0.0f);
	EXPECT_FLOAT_EQ(identity.r1c0, 0.0f);
	EXPECT_FLOAT_EQ(identity.r1c1, 1.0f);
}
TEST(Matrix2D, MatrixVectorMultiply)
{

}