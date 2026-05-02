#include <Vector.h>
#include <gtest/gtest.h>
#include <cmath>

using namespace Stk;

class VectorTest : public ::testing::Test {
protected:
	void SetUp() override {
		v1 = { 1.0, 2.0, 3.0 };
		v2 = { 4.0, 5.0, 6.0 };
		v3 = { 1.0, 2.0, 3.0 };
	}

	void TearDown() override {
	}

	Vector<double> v1;
	Vector<double> v2;
	Vector<double> v3;
};

TEST(VectorConstructionTest, DefaultConstructor) {
	Vector<int> v;
	EXPECT_EQ(v.size(), 0);
}

TEST(VectorConstructionTest, SizeConstructor) {
	Vector<int> v(5);
	EXPECT_EQ(v.size(), 5);

	for (size_t i = 0; i < v.size(); ++i) {
		EXPECT_EQ(v[i], 0);
	}
}

TEST(VectorConstructionTest, InitializerListConstructor) {
	Vector<double> v = { 1.0, 2.0, 3.0 };

	EXPECT_EQ(v.size(), 3);
	EXPECT_DOUBLE_EQ(v[0], 1.0);
	EXPECT_DOUBLE_EQ(v[1], 2.0);
	EXPECT_DOUBLE_EQ(v[2], 3.0);
}

TEST(VectorConstructionTest, CopyConstructor) {
	Vector<double> original = { 1.0, 2.0, 3.0 };
	Vector<double> copy(original);

	EXPECT_EQ(copy.size(), original.size());
	for (size_t i = 0; i < original.size(); ++i) {
		EXPECT_DOUBLE_EQ(copy[i], original[i]);
	}
}

TEST(VectorConstructionTest, MoveConstructor) {
	Vector<double> original = { 1.0, 2.0, 3.0 };
	Vector<double> moved(std::move(original));

	EXPECT_EQ(moved.size(), 3);
	EXPECT_DOUBLE_EQ(moved[0], 1.0);
	EXPECT_DOUBLE_EQ(moved[1], 2.0);
	EXPECT_DOUBLE_EQ(moved[2], 3.0);

	EXPECT_EQ(original.size(), 0);
}

TEST(VectorAssignmentTest, CopyAssignment) {
	Vector<double> v1 = { 1.0, 2.0, 3.0 };
	Vector<double> v2;

	v2 = v1;

	EXPECT_EQ(v2.size(), v1.size());
	for (size_t i = 0; i < v1.size(); ++i) {
		EXPECT_DOUBLE_EQ(v2[i], v1[i]);
	}

	v1 = v1;
	EXPECT_EQ(v1.size(), 3);
	EXPECT_DOUBLE_EQ(v1[0], 1.0);
}

TEST(VectorAssignmentTest, MoveAssignment) {
	Vector<double> v1 = { 1.0, 2.0, 3.0 };
	Vector<double> v2;

	v2 = std::move(v1);

	EXPECT_EQ(v2.size(), 3);
	EXPECT_DOUBLE_EQ(v2[0], 1.0);
	EXPECT_DOUBLE_EQ(v2[1], 2.0);
	EXPECT_DOUBLE_EQ(v2[2], 3.0);

	EXPECT_EQ(v1.size(), 0);
}

TEST(VectorOperatorTest, Addition) {
	Vector<double> v1 = { 1.0, 2.0, 3.0 };
	Vector<double> v2 = { 4.0, 5.0, 6.0 };
	Vector<double> expected = { 5.0, 7.0, 9.0 };

	Vector<double> result = v1 + v2;

	for (size_t i = 0; i < result.size(); ++i) {
		EXPECT_DOUBLE_EQ(result[i], expected[i]);
	}
}

TEST(VectorOperatorTest, Subtraction) {
	Vector<double> v1 = { 5.0, 7.0, 9.0 };
	Vector<double> v2 = { 4.0, 5.0, 6.0 };
	Vector<double> expected = { 1.0, 2.0, 3.0 };

	Vector<double> result = v1 - v2;

	for (size_t i = 0; i < result.size(); ++i) {
		EXPECT_DOUBLE_EQ(result[i], expected[i]);
	}
}

TEST(VectorOperatorTest, ScalarMultiplication) {
	Vector<double> v = { 1.0, 2.0, 3.0 };
	double scalar = 2.5;
	Vector<double> expected = { 2.5, 5.0, 7.5 };

	Vector<double> result = v * scalar;

	for (size_t i = 0; i < result.size(); ++i) {
		EXPECT_DOUBLE_EQ(result[i], expected[i]);
	}
}

TEST(VectorOperatorTest, ScalarMultiplicationLeft) {
	Vector<double> v = { 1.0, 2.0, 3.0 };
	double scalar = 2.5;
	Vector<double> expected = { 2.5, 5.0, 7.5 };

	Vector<double> result = scalar * v;

	for (size_t i = 0; i < result.size(); ++i) {
		EXPECT_DOUBLE_EQ(result[i], expected[i]);
	}
}

TEST(VectorOperatorTest, IndexOperator) {
	Vector<double> v = { 1.0, 2.0, 3.0 };

	EXPECT_DOUBLE_EQ(v[0], 1.0);
	EXPECT_DOUBLE_EQ(v[1], 2.0);
	EXPECT_DOUBLE_EQ(v[2], 3.0);

	v[1] = 10.0;
	EXPECT_DOUBLE_EQ(v[1], 10.0);
}

TEST(VectorOperatorTest, CompoundAddition) {
	Vector<double> v1 = { 1.0, 2.0, 3.0 };
	Vector<double> v2 = { 4.0, 5.0, 6.0 };
	Vector<double> expected = { 5.0, 7.0, 9.0 };

	v1 += v2;

	for (size_t i = 0; i < v1.size(); ++i) {
		EXPECT_DOUBLE_EQ(v1[i], expected[i]);
	}
}

TEST(VectorOperatorTest, CompoundSubtraction) {
	Vector<double> v1 = { 5.0, 7.0, 9.0 };
	Vector<double> v2 = { 4.0, 5.0, 6.0 };
	Vector<double> expected = { 1.0, 2.0, 3.0 };

	v1 -= v2;

	for (size_t i = 0; i < v1.size(); ++i) {
		EXPECT_DOUBLE_EQ(v1[i], expected[i]);
	}
}

TEST(VectorOperatorTest, CompoundScalarMultiplication) {
	Vector<double> v = { 1.0, 2.0, 3.0 };
	Vector<double> expected = { 2.5, 5.0, 7.5 };

	v *= 2.5;

	for (size_t i = 0; i < v.size(); ++i) {
		EXPECT_DOUBLE_EQ(v[i], expected[i]);
	}
}

TEST(VectorMathTest, DotProduct) {
	Vector<double> v1 = { 1.0, 2.0, 3.0 };
	Vector<double> v2 = { 4.0, 5.0, 6.0 };
	double expected = 32.0;  // 1*4 + 2*5 + 3*6 = 4 + 10 + 18 = 32

	double result = v1.dot(v2);

	EXPECT_DOUBLE_EQ(result, expected);
}

TEST(VectorMathTest, Norm) {
	Vector<double> v = { 3.0, 4.0 };
	double expected = 5.0;

	double result = v.norm();

	EXPECT_DOUBLE_EQ(result, expected);
}

TEST(VectorMathTest, Normalize) {
	Vector<double> v = { 3.0, 4.0 };
	v.normalize();

	EXPECT_NEAR(v.norm(), 1.0, 1e-10);
}

TEST(VectorMathTest, EmptyVectorNorm) {
	Vector<double> v;
	EXPECT_DOUBLE_EQ(v.norm(), 0.0);
}

TEST(VectorFactoryTest, Zeros) {
	Vector<double> v = Vector<double>::zeros(5);

	EXPECT_EQ(v.size(), 5);
	for (size_t i = 0; i < v.size(); ++i) {
		EXPECT_DOUBLE_EQ(v[i], 0.0);
	}
}

TEST(VectorFactoryTest, Ones) {
	Vector<double> v = Vector<double>::ones(5);

	EXPECT_EQ(v.size(), 5);
	for (size_t i = 0; i < v.size(); ++i) {
		EXPECT_DOUBLE_EQ(v[i], 1.0);
	}
}

TEST(VectorFactoryTest, Random) {
	Vector<double> v = Vector<double>::random(100, -10.0, 10.0);

	EXPECT_EQ(v.size(), 100);
	for (size_t i = 0; i < v.size(); ++i) {
		EXPECT_GE(v[i], -10.0);
		EXPECT_LE(v[i], 10.0);
	}
}

TEST(VectorResizeTest, ResizeLarger) {
	Vector<double> v = { 1.0, 2.0, 3.0 };
	v.resize(5);

	EXPECT_EQ(v.size(), 5);
	EXPECT_DOUBLE_EQ(v[0], 1.0);
	EXPECT_DOUBLE_EQ(v[1], 2.0);
	EXPECT_DOUBLE_EQ(v[2], 3.0);
	EXPECT_DOUBLE_EQ(v[3], 0.0);
	EXPECT_DOUBLE_EQ(v[4], 0.0);
}

TEST(VectorResizeTest, ResizeSmaller) {
	Vector<double> v = { 1.0, 2.0, 3.0, 4.0, 5.0 };
	v.resize(3);

	EXPECT_EQ(v.size(), 3);
	EXPECT_DOUBLE_EQ(v[0], 1.0);
	EXPECT_DOUBLE_EQ(v[1], 2.0);
	EXPECT_DOUBLE_EQ(v[2], 3.0);
}

TEST(VectorResizeTest, ResizeSame) {
	Vector<double> v = { 1.0, 2.0, 3.0 };
	v.resize(3);

	EXPECT_EQ(v.size(), 3);
	EXPECT_DOUBLE_EQ(v[0], 1.0);
	EXPECT_DOUBLE_EQ(v[1], 2.0);
	EXPECT_DOUBLE_EQ(v[2], 3.0);
}

TEST(VectorFillTest, FillAllElements) {
	Vector<double> v(5);
	v.fill(3.14);

	for (size_t i = 0; i < v.size(); ++i) {
		EXPECT_DOUBLE_EQ(v[i], 3.14);
	}
}

TEST(VectorDataTest, DataPointer) {
	Vector<double> v = { 1.0, 2.0, 3.0 };
	const double* ptr = v.data();

	EXPECT_DOUBLE_EQ(ptr[0], 1.0);
	EXPECT_DOUBLE_EQ(ptr[1], 2.0);
	EXPECT_DOUBLE_EQ(ptr[2], 3.0);
}

TEST(VectorEdgeTest, EmptyVector) {
	Vector<double> v;
	EXPECT_EQ(v.size(), 0);
}

TEST(VectorEdgeTest, SingleElement) {
	Vector<double> v = { 42.0 };

	EXPECT_EQ(v.size(), 1);
	EXPECT_DOUBLE_EQ(v[0], 42.0);
}

TEST(VectorEdgeTest, OutOfRangeAccess) {
	Vector<double> v = { 1.0, 2.0, 3.0 };

	EXPECT_THROW(v[3], std::out_of_range);
	EXPECT_THROW(v[100], std::out_of_range);
}

TEST(VectorEdgeTest, ConstOutOfRangeAccess) {
	const Vector<double> v = { 1.0, 2.0, 3.0 };

	EXPECT_THROW(v[3], std::out_of_range);
}

TEST(VectorEdgeTest, DifferentSizesAddition) {
	Vector<double> v1 = { 1.0, 2.0, 3.0 };
	Vector<double> v2 = { 4.0, 5.0 };

	EXPECT_THROW(v1 + v2, std::invalid_argument);
}

TEST(VectorEdgeTest, DifferentSizesDotProduct) {
	Vector<double> v1 = { 1.0, 2.0, 3.0 };
	Vector<double> v2 = { 4.0, 5.0 };

	EXPECT_THROW(v1.dot(v2), std::invalid_argument);
}

TEST(VectorTypeTest, IntVector) {
	Vector<int> v = { 1, 2, 3 };

	EXPECT_EQ(v.size(), 3);
	EXPECT_EQ(v[0], 1);
	EXPECT_EQ(v[1], 2);
	EXPECT_EQ(v[2], 3);
}

TEST(VectorTypeTest, FloatVector) {
	Vector<float> v = { 1.0f, 2.0f, 3.0f };

	EXPECT_EQ(v.size(), 3);
	EXPECT_FLOAT_EQ(v[0], 1.0f);
	EXPECT_FLOAT_EQ(v[1], 2.0f);
	EXPECT_FLOAT_EQ(v[2], 3.0f);
}

TEST(VectorChainTest, MultipleOperations) {
	Vector<double> v1 = { 1.0, 2.0, 3.0 };
	Vector<double> v2 = { 4.0, 5.0, 6.0 };

	Vector<double> result = (v1 + v2) * 2.0 - v1;
	// (5,7,9) * 2 = (10,14,18) - (1,2,3) = (9,12,15)

	EXPECT_DOUBLE_EQ(result[0], 9.0);
	EXPECT_DOUBLE_EQ(result[1], 12.0);
	EXPECT_DOUBLE_EQ(result[2], 15.0);
}

TEST(VectorPerformanceTest, LargeVector) {
	const size_t size = 10000;
	Vector<double> v1 = Vector<double>::random(size, -100.0, 100.0);
	Vector<double> v2 = Vector<double>::random(size, -100.0, 100.0);

	Vector<double> result = v1 + v2;

	EXPECT_EQ(result.size(), size);
}

int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
