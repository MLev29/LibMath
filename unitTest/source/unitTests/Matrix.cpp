#define GLM_ENABLE_EXPERIMENTAL

#include "LibMath/Arithmetic.h"
#include "LibMath/Matrix.h"

#include <catch2/catch_test_macros.hpp>
#include <glm/common.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/matrix_operation.hpp>
#include <limits>

#define CHECK_MATRIX2(mat2, mat2Glm)\
CHECK(mat2.m_matrix[0][0] == mat2Glm[0][0]);\
CHECK(mat2.m_matrix[0][1] == mat2Glm[0][1]);\
CHECK(mat2.m_matrix[1][0] == mat2Glm[1][0]);\
CHECK(mat2.m_matrix[1][1] == mat2Glm[1][1]);\

#define CHECK_MATRIX3(mat3, mat3Glm)\
CHECK(mat3.m_matrix[0][0] == mat3Glm[0][0]);\
CHECK(mat3.m_matrix[0][1] == mat3Glm[0][1]);\
CHECK(mat3.m_matrix[0][2] == mat3Glm[0][2]);\
\
CHECK(mat3.m_matrix[1][0] == mat3Glm[1][0]);\
CHECK(mat3.m_matrix[1][1] == mat3Glm[1][1]);\
CHECK(mat3.m_matrix[1][2] == mat3Glm[1][2]);\
\
CHECK(mat3.m_matrix[2][0] == mat3Glm[2][0]);\
CHECK(mat3.m_matrix[2][1] == mat3Glm[2][1]);\
CHECK(mat3.m_matrix[2][2] == mat3Glm[2][2]);\

#define CHECK_MATRIX4(mat4, mat4Glm)\
CHECK(mat4.m_matrix[0][0] == mat4Glm[0][0]);\
CHECK(mat4.m_matrix[0][1] == mat4Glm[0][1]);\
CHECK(mat4.m_matrix[0][2] == mat4Glm[0][2]);\
CHECK(mat4.m_matrix[0][3] == mat4Glm[0][3]);\
\
CHECK(mat4.m_matrix[1][0] == mat4Glm[1][0]);\
CHECK(mat4.m_matrix[1][1] == mat4Glm[1][1]);\
CHECK(mat4.m_matrix[1][2] == mat4Glm[1][2]);\
CHECK(mat4.m_matrix[1][3] == mat4Glm[1][3]);\
\
CHECK(mat4.m_matrix[2][0] == mat4Glm[2][0]);\
CHECK(mat4.m_matrix[2][1] == mat4Glm[2][1]);\
CHECK(mat4.m_matrix[2][2] == mat4Glm[2][2]);\
CHECK(mat4.m_matrix[2][3] == mat4Glm[2][3]);\
\
CHECK(mat4.m_matrix[3][0] == mat4Glm[3][0]);\
CHECK(mat4.m_matrix[3][1] == mat4Glm[3][1]);\
CHECK(mat4.m_matrix[3][2] == mat4Glm[3][2]);\
CHECK(mat4.m_matrix[3][3] == mat4Glm[3][3]);

TEST_CASE("Matrix2", "[.all][matrix][matrix2]")
{
	SECTION("Constructor")
	{
		CHECK_MATRIX2(math::Matrix2<float>(), glm::mat2(1.0f));
		CHECK_MATRIX2(math::Matrix2(2), glm::mat2(2));
		CHECK_MATRIX2(math::Matrix2(-3.0), glm::mat2(-3.0));
		CHECK_MATRIX2(math::Matrix2(1.8373628f), glm::mat2(1.8373628f));
		CHECK_MATRIX2(math::Matrix2(FLT_MAX), glm::mat2(FLT_MAX));
		CHECK_MATRIX2(math::Matrix2(1.0f, 2.0f, 3.0f, 4.0f), glm::mat2(1.0f, 2.0f, 3.0f, 4.0f));
	}

	SECTION("Functions")
	{
		// Zero
		CHECK_MATRIX2(math::Matrix2<float>::Zero(), glm::mat2(0.0f));

		// One
		CHECK_MATRIX2(math::Matrix2<float>::One(), glm::mat2(1.0f, 1.0f, 1.0f, 1.0f));

		// Identity
		CHECK_MATRIX2(math::Matrix2<float>::Identity(1.0f), glm::mat2(1.0f, 0.0f, 0.0f, 1.0f));
		CHECK_MATRIX2(math::Matrix2<float>::Identity(5.0f), glm::mat2(5.0f, 0.0f, 0.0f, 5.0f));

		// Transpose
		CHECK_MATRIX2(math::Matrix2<int>(2, 3, 7, -2).Transpose(), glm::transpose(glm::mat2(2, 3, 7, -2)));
		//CheckMatrix(math::Matrix2<double>(-3.48, 2.3, 7.00008, -2.1).Transpose(), glm::transpose(glm::mat2(-3.48, 2.3, 7.00008, -2.1))); // TODO: look into, glm not transposing matrix or column major?

		// Determinant
		CHECK(math::Matrix2<float>(2.5f, 1.0f, 1.5f, 3.0f).Determinant() == glm::determinant(glm::mat2(2.5f, 1.0f, 1.5f, 3.0f)));
		CHECK(math::Matrix2<float>(1.0, -2.0f, 3.0f, 4.5f).Determinant() == glm::determinant(glm::mat2(1.0, -2.0f, 3.0f, 4.5f)));

		// TODO: Minor
		//CheckMatrix(math::Matrix2<float>().Minor())

		// TODO: Cofactor


		// Adjugate
		CHECK_MATRIX2(math::Matrix2<float>(2.5f, 4.3f, 1.25f, 6.0f).Adjugate(), glm::adjugate(glm::mat2(2.5f, 4.3f, 1.25f, 6.0f)));

		// Inverse
		CHECK_MATRIX2(math::Matrix2<float>(1.0f, 2.0f , 3.0f, 4.0f).Inverse(), glm::inverse(glm::mat2(1.0f, 2.0f, 3.0f, 4.0f)));
	}

	SECTION("Operator")
	{
		math::Matrix2<float> Matrix1(1.0f, 2.0f, 3.0f, 4.0f);
		math::Matrix2<float> Matrix2(6.0f, 5.5f, 1.0f, 2.5f);

		glm::mat2 Matrix1GLM(1.0f, 2.0f, 3.0f, 4.0f);
		glm::mat2 Matrix2GLM(6.0f, 5.5f, 1.0f, 2.5f);

		// Operator +
		CHECK_MATRIX2((Matrix1 + Matrix2), (Matrix1GLM + Matrix2GLM));
		
		// Operator -
		CHECK_MATRIX2((Matrix1 - Matrix2), (Matrix1GLM - Matrix2GLM));

		// Operator * scalar
		const float scalar = 2.0f;
		CHECK_MATRIX2((Matrix1 * scalar), (Matrix1GLM * scalar));

		// Operator * matrix
		CHECK_MATRIX2((Matrix1 * Matrix2), (Matrix1GLM * Matrix2GLM));

		// Operator +=
		Matrix1 += Matrix2;
		Matrix1GLM += Matrix2GLM;

		CHECK_MATRIX2(Matrix1, Matrix1GLM);

		// Operator -=
		Matrix1 -= Matrix2;
		Matrix1GLM -= Matrix2GLM;

		CHECK_MATRIX2(Matrix1, Matrix1GLM);

		// Operator *= scalar
		Matrix1 *= scalar;
		Matrix1GLM *= scalar;

		CHECK_MATRIX2(Matrix1, Matrix1GLM);

		// Operator *= matrix
		Matrix1 *= Matrix2;
		Matrix1GLM *= Matrix2GLM;

		CHECK_MATRIX2(Matrix1, Matrix1GLM);

		// Operator ==
		CHECK(Matrix1 == Matrix1);
		CHECK_FALSE(Matrix1 == Matrix2);

		// Operator !=
		CHECK(Matrix1 != Matrix2);
		CHECK_FALSE(Matrix1 != Matrix1);
	}
}

TEST_CASE("Matrix3", "[.all][matrix][matrix3]")
{
	float arr[9] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f};
	float arr2[9] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 7.0f, 7.0f, 8.0f, 9.0f};

	SECTION("Constructor")
	{
		CHECK_MATRIX3(math::Matrix3<float>(), glm::mat3(1.0f));
		CHECK_MATRIX3(math::Matrix3<float>(5.0f), glm::mat3(5.0f));
		CHECK_MATRIX3(math::Matrix3<float>(-2.5f), glm::mat3(-2.5f));
		CHECK_MATRIX3(math::Matrix3<float>(arr), glm::mat3({1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f}));
	}

	SECTION("Function")
	{
		// Identity
		CHECK_MATRIX3(math::Matrix3<float>::Identity(), glm::mat3(1.0f));

		// Transpose
		CHECK_MATRIX3(math::Matrix3<float>(arr).Transpose(), glm::transpose(glm::mat3({1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f})));

		// Determinant
		CHECK(math::Matrix3<float>(arr).Determinant() == glm::determinant(glm::mat3({1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f})));

		// TODO: Minor
		//CHECK_MATRIX3(math::Matrix2<float>().Minor())

		// TODO: Cofactor


		// Adjugate
		CHECK_MATRIX3(math::Matrix3<float>(arr).Adjugate(), glm::adjugate(glm::mat3({1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f})));

		// Inverse
		CHECK_MATRIX3(math::Matrix3<float>(arr2).Inverse(), glm::inverse(glm::mat3({1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 7.0f, 7.0f, 8.0f, 9.0f})));
	}

	SECTION("Operators")
	{
		float scalar = 2.5f;
		float values1[9] = {1.3f, 2.0f, 5.8f, 8.2f, 7.2f, 2.1f, 0.0f, 1.0f, 9.0};
		float values2[9] = {9.2f, 4.0f, 3.1f, 8.0f, -2.2f, 1.1f, 0.5f, 1.0f, 7.7f};
		float values3[9] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f};
		float values4[9] = {9.0f, 8.0f, 7.0f, 6.0f, 5.0f, 4.0f, 3.0f, 2.0f, 1.0f};

		math::Matrix3<float> Matrix1(values1);
		math::Matrix3<float> Matrix2(values2);
		math::Matrix3<float> Matrix3(values3);
		math::Matrix3<float> Matrix4(values4);
		glm::mat3 Matrix1GLM({1.3f, 2.0f, 5.8f, 8.2f, 7.2f, 2.1f, 0.0f, 1.0f, 9.0});
		glm::mat3 Matrix2GLM({9.2f, 4.0f, 3.1f, 8.0f, -2.2f, 1.1f, 0.5f, 1.0f, 7.7f});
		glm::mat3 Matrix3GLM({1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f});
		glm::mat3 Matrix4GLM({9.0f, 8.0f, 7.0f, 6.0f, 5.0f, 4.0f, 3.0f, 2.0f, 1.0f});

		// Operator +
		CHECK_MATRIX3((Matrix1 + Matrix1), (Matrix1GLM + Matrix1GLM));
		CHECK_MATRIX3((Matrix1 + Matrix2), (Matrix1GLM + Matrix2GLM));
		CHECK_MATRIX3((Matrix2 + Matrix2), (Matrix2GLM + Matrix2GLM));
		
		// Operator -
		CHECK_MATRIX3((Matrix1 - Matrix1), (Matrix1GLM - Matrix1GLM));
		CHECK_MATRIX3((Matrix1 - Matrix2), (Matrix1GLM - Matrix2GLM));
		CHECK_MATRIX3((Matrix2 - Matrix2), (Matrix2GLM - Matrix2GLM));
		
		// Operator * scalar
		CHECK_MATRIX3((Matrix1 * scalar), (Matrix1GLM * scalar));
		CHECK_MATRIX3((Matrix2 * scalar), (Matrix2GLM * scalar));
	
		// Operator * matrix
		CHECK_MATRIX3((Matrix1 * Matrix1), (Matrix1GLM * Matrix1GLM));
		CHECK_MATRIX3((Matrix1 * Matrix2), (Matrix2GLM * Matrix1GLM));
		CHECK_MATRIX3((Matrix2 * Matrix2), (Matrix2GLM * Matrix2GLM));
		CHECK_MATRIX3((Matrix3 * Matrix4), (Matrix4GLM * Matrix3GLM));

		// Operator / scalar
		CHECK_MATRIX3((Matrix1 / scalar), (Matrix1GLM / scalar));
		CHECK_MATRIX3((Matrix2 / scalar), (Matrix2GLM / scalar));
		
		// Operator +=
		Matrix1 += Matrix2;
		Matrix1GLM += Matrix2GLM;
		
		CHECK_MATRIX3(Matrix1, Matrix1GLM);
		CHECK_MATRIX3(Matrix2, Matrix2GLM);
		
		// Operator -=
		Matrix1 -= Matrix2;
		Matrix1GLM -= Matrix2GLM;
		
		CHECK_MATRIX3(Matrix1, Matrix1GLM);
		CHECK_MATRIX3(Matrix2, Matrix2GLM);
		
		// Operator *= scalar
		Matrix1 *= scalar;
		Matrix1GLM *= scalar;
		
		CHECK_MATRIX3(Matrix1, Matrix1GLM);
		CHECK_MATRIX3(Matrix2, Matrix2GLM);


		// TODO: look into matrix 3x3 * operator may find an issue?
		// Operator *= matrix
		Matrix1 *= Matrix2;
		Matrix2GLM *= Matrix1GLM;
		
		CHECK_MATRIX3(Matrix1, Matrix2GLM);
		
		// Operator /= scalar
		Matrix1 = values1;
		Matrix1GLM = {1.3f, 2.0f, 5.8f, 8.2f, 7.2f, 2.1f, 0.0f, 1.0f, 9.0};
		Matrix1 /= scalar;
		Matrix1GLM /= scalar;
		CHECK_MATRIX3(Matrix1, Matrix1GLM);
		
		// Operator ==
		CHECK(Matrix1 == Matrix1);
		CHECK(Matrix2 == Matrix2);
		CHECK_FALSE(Matrix1 == Matrix2);
		
		// Operator !=
		CHECK(Matrix1 != Matrix2);
		CHECK_FALSE(Matrix1 != Matrix1);
		CHECK_FALSE(Matrix2 != Matrix2);
	}
}

#define VALUES  {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f}
#define VALUES2 {9.0f, 2.5f, -3.0f, 1.0f, 3.0f, 10.0f, 7.2f, 8.4f, 6.0f, 10.0f, 3.0f, 2.0f, 15.0f, 12.0f, 5.0f, 1.0f}
#define VALUES3 {1.0f, 2.0f, 0.0f, 0.0f, 2.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 3.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f}

TEST_CASE("Matrix4", "[.all][matrix][matrix4]")
{
	SECTION("Constructor")
	{
		float values[16] = VALUES;
		CHECK_MATRIX4(LibMath::Matrix4<float>(), glm::mat4(1.0f));
		CHECK_MATRIX4(LibMath::Matrix4<float>(1.0f), glm::mat4(1.0f));
		CHECK_MATRIX4(LibMath::Matrix4<float>(values), glm::mat4(VALUES));
		CHECK_MATRIX4(LibMath::Matrix4<float>(-5.0f), glm::mat4(-5.0f));
	}

	SECTION("Functions")
	{
		float values[16] = VALUES;
		float values2[16] = VALUES3;

		// Transpose
		CHECK_MATRIX4(LibMath::Matrix4(values).Transpose(), glm::transpose(glm::mat4(VALUES)));

		// Identity
		CHECK_MATRIX4(LibMath::Matrix4<float>::Identity(), glm::mat4(1.0f));

		// Determinant
		CHECK(LibMath::Matrix4<float>(values).Determinant() == glm::determinant(glm::mat4(VALUES)));
		CHECK(LibMath::Matrix4<float>(1.0f).Determinant() == glm::determinant(glm::mat4(1.0f)));

		// Minor
		// Cofactor
		// Adjugate
		CHECK_MATRIX4(LibMath::Matrix4<float>(values).Adjugate(), glm::adjugate(glm::mat4(VALUES)));

		// Inverse
		CHECK_MATRIX4(LibMath::Matrix4<float>(values2).Inverse(), glm::inverse(glm::mat4(VALUES3)));
	}

	SECTION("Operator")
	{
		float values1[16] = VALUES;
		float values2[16] = VALUES2;
		float scalar = 2.5f;
		float scalar2 = -1.5f;

		LibMath::Matrix4<float> matrix1(values1);
		LibMath::Matrix4<float> matrix2(values2);

		glm::mat4 matrix1GLM(VALUES);
		glm::mat4 matrix2GLM(VALUES2);

		// Operator +
		CHECK_MATRIX4((matrix1 + matrix1), (matrix1GLM + matrix1GLM));
		CHECK_MATRIX4((matrix2 + matrix2), (matrix2GLM + matrix2GLM));
		CHECK_MATRIX4((matrix1 + matrix2), (matrix1GLM + matrix2GLM));

		// Operator -
		CHECK_MATRIX4((matrix1 - matrix1), (matrix1GLM - matrix1GLM));
		CHECK_MATRIX4((matrix2 - matrix2), (matrix2GLM - matrix2GLM));
		CHECK_MATRIX4((matrix1 - matrix2), (matrix1GLM - matrix2GLM));
		
		// Operator * scalar
		CHECK_MATRIX4((matrix1 * scalar), (matrix1GLM  * scalar));
		CHECK_MATRIX4((matrix2 * scalar), (matrix2GLM  * scalar));
		CHECK_MATRIX4((matrix1 * scalar2), (matrix1GLM * scalar2));

		// Operator * matrix
		CHECK_MATRIX4((matrix1 * matrix1), (matrix1GLM * matrix1GLM));
		CHECK_MATRIX4((matrix2 * matrix2), (matrix2GLM * matrix2GLM));
		CHECK_MATRIX4((matrix1 * matrix2), (matrix1GLM * matrix2GLM));

		// Operator / scalar
		CHECK_MATRIX4((matrix1 / scalar), (matrix1GLM / scalar));
		CHECK_MATRIX4((matrix2 / scalar), (matrix2GLM / scalar));
		CHECK_MATRIX4((matrix1 / scalar2), (matrix1GLM / scalar2));

		// Operator +=
		matrix1 += matrix2;
		matrix1GLM += matrix2GLM;

		CHECK_MATRIX4(matrix1, matrix1GLM);

		// Operator -=
		matrix1 -= matrix2;
		matrix1GLM -= matrix2GLM;

		CHECK_MATRIX4(matrix1, matrix1GLM);

		// Operator *= scalar
		matrix1 *= scalar;
		matrix1GLM *= scalar;

		CHECK_MATRIX4(matrix1, matrix1GLM);

		// Operator *= matrix
		matrix1 *= matrix2;
		matrix2GLM *= matrix1GLM; // glm does column * row

		CHECK_MATRIX4(matrix1, matrix2GLM);

		// Operator ==
		CHECK(matrix1 == matrix1);
		CHECK(matrix2 == matrix2);
		CHECK_FALSE(matrix1 == matrix2);

		// Operator !=
		CHECK(matrix1 != matrix2);
		CHECK_FALSE(matrix1 != matrix1);
		CHECK_FALSE(matrix2 != matrix2);
	}
}