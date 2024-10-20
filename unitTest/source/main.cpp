#include <catch2/catch_session.hpp>

#include <vector>
#include <stdio.h>

// ======= Enable Unit Tests =======
#define ANGLE_UNIT_TEST				0
#define ARITHMETIC_UNIT_TEST		1
#define GEOMETRY_UNIT_TEST			0
#define MATRIX_UNIT_TEST			0
#define VECTOR_UNIT_TEST			0
#define TRIGONOMETRY_UNIT_TEST		0
//==================================

std::vector<const char*> SelectTests(void)
{
	std::vector<const char*> tests;
#if ANGLE_UNIT_TEST == 1
	tests.push_back("Angle");
#endif
#if ARITHMETIC_UNIT_TEST == 1
	tests.push_back("Arithmetic");
#endif
#if GEOMETRY_UNIT_TEST == 1
	tests.push_back("Geometry");
#endif
#if MATRIX_UNIT_TEST == 1
	tests.push_back("Matrix");
#endif
#if VECTOR_UNIT_TEST == 1
	tests.push_back("Vector");
#endif
#if TRIGONOMETRY_UNIT_TEST == 1
	tests.push_back("Trigonometry");
#endif

	return tests;
}

int main(void)
{

	std::vector<char const*> arguments = SelectTests();

	return Catch::Session().run((int) arguments.size(), &arguments[0]);
}