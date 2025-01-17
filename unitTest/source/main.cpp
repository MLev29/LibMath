#include <catch2/catch_session.hpp>

#include <vector>
#include <stdio.h>

// ======= Enable Unit Tests =======
#define ALL_UNIT_TEST				1
#define ANGLE_UNIT_TEST				0
#define ARITHMETIC_UNIT_TEST		0
#define GEOMETRY_UNIT_TEST			0
#define MATRIX_UNIT_TEST			0
#define VECTOR_UNIT_TEST			0
#define TRIGONOMETRY_UNIT_TEST		0
#define QUATERNION_UNIT_TEST		0
//==================================


// Enable Individual Unit Tests

// Angles
#define DEGREE_UNIT_TEST		0
#define RADIAN_UNIT_TEST		0

// Matrices
#define MATRIX2_UNIT_TEST		1
#define MATRIX3_UNIT_TEST		1
#define MATRIX4_UNIT_TEST		1

// Vectors
#define VECTOR2_UNIT_TEST		0
#define VECTOR3_UNIT_TEST		0
#define VECTOR4_UNIT_TEST		0

// Geometry

//==================================

int main(int argc, char* argv[])
{

	std::vector<char const*> arguments;
	for (int i = 0; i < argc; i++)
	{
		arguments.push_back(argv[i]);
	}

#if (DEGREE_UNIT_TEST == 1 || ANGLE_UNIT_TEST == 1 || ALL_UNIT_TEST == 1)
	arguments.push_back("[degree],");
#endif
#if (RADIAN_UNIT_TEST == 1 || ANGLE_UNIT_TEST == 1 || ALL_UNIT_TEST == 1)
	arguments.push_back("[radian],");
#endif
#if (MATRIX2_UNIT_TEST == 1 || MATRIX_UNIT_TEST == 1 || ALL_UNIT_TEST == 1)
	arguments.push_back("[matrix2],");
#endif
#if (MATRIX3_UNIT_TEST == 1 || MATRIX_UNIT_TEST == 1 || ALL_UNIT_TEST == 1)
	arguments.push_back("[matrix3],");
#endif
#if (MATRIX4_UNIT_TEST == 1 || MATRIX_UNIT_TEST == 1 || ALL_UNIT_TEST == 1)
	arguments.push_back("[matrix4],");
#endif
#if (VECTOR2_UNIT_TEST == 1 || VECTOR_UNIT_TEST == 1 || ALL_UNIT_TEST == 1)
	arguments.push_back("[Vector2],");
#endif
#if (VECTOR3_UNIT_TEST == 1 || VECTOR_UNIT_TEST == 1 || ALL_UNIT_TEST == 1)
	arguments.push_back("[Vector3],");
#endif
#if (VECTOR4_UNIT_TEST == 1 || VECTOR_UNIT_TEST == 1 || ALL_UNIT_TEST == 1)
	arguments.push_back("[Vector4],");
#endif

#if ARITHMETIC_UNIT_TEST == 1 || ALL_UNIT_TEST == 1
	arguments.push_back("Arithmetic");
#endif
#if GEOMETRY_UNIT_TEST == 1 || ALL_UNIT_TEST == 1
	arguments.push_back("Geometry");
#endif
#if TRIGONOMETRY_UNIT_TEST == 1 || ALL_UNIT_TEST == 1
	arguments.push_back("Trigonometry");
#endif
#if QUATERNION_UNIT_TEST == 1 || ALL_UNIT_TEST == 1
	arguments.push_back("Quaternion");
#endif

	return Catch::Session().run((int) arguments.size(), &arguments[0]);
}