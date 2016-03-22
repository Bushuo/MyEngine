#include <gtest\gtest.h>

void main(int argc, char* argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	::testing::GTEST_FLAG(filter) = "Matrix2D*";
	RUN_ALL_TESTS();
}