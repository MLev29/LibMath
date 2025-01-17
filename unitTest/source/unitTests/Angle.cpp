#include "LibMath/Angle.h"

#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark.hpp>
#include <glm/common.hpp>
#include <glm/glm.hpp>
#include <limits>

/*
	Angle Tests
	- Basics			DONE
	- Different types	DONE
	- Edge cases
*/


TEST_CASE("Degree", "[.all][angle][degree]")
{
	SECTION("Constructor")
	{
		// Void constructor
		math::Degree<int>		myVoidIntConstructor;
		math::Degree<float>		myVoidFloatConstructor;
		math::Degree<double>	myVoidDblConstructor;

		CHECK(myVoidIntConstructor.Value() == 0);
		CHECK(myVoidFloatConstructor.Value() == 0.0f);
		CHECK(myVoidDblConstructor.Value() == 0.0);

		// 1 value constructor
		math::Degree<int>		myValIntConstructor(5);
		math::Degree<float>		myValFloatConstructor(-192.42f);
		math::Degree<double>	myValDblConstructor(23.959999);

		CHECK(myValIntConstructor.Value() == 5);
		CHECK(myValFloatConstructor.Value() == -192.42f);
		CHECK(myValDblConstructor.Value() == 23.959999);
	}

	SECTION("Equality")
	{
		REQUIRE(math::Degree(340.0) == math::Degree(340.0));
		REQUIRE_FALSE(math::Degree(340.0) == math::Degree(-20.0));
		REQUIRE_FALSE(math::Degree(340.00009) == math::Degree(340.0));

		REQUIRE_FALSE(math::Degree(45.0) != math::Degree(45.0));
		REQUIRE(math::Degree(89.0) != math::Degree(160.0));
		REQUIRE(math::Degree(29.99998) != math::Degree(30.0));
	}

	SECTION("Functions")
	{
		CHECK(math::Degree(340.0).Wrap() == math::Degree(340.0));
		CHECK(math::Degree(340.0).Wrap().Value() == 340.0);
		CHECK(math::Degree(340.0).Wrap() == math::Degree(-20.0).Wrap());
	}

	float angleValues[] = {45.0f, 90.0f, 120.0f, -150.0f, 49.0f};
	SECTION("Addition")
	{
		CHECK((math::Degree(angleValues[0]) + math::Degree(angleValues[1])).Value() == (angleValues[0] + angleValues[1]));
		CHECK((math::Degree(angleValues[0]) + angleValues[3]).Value() == (angleValues[0] + angleValues[3]));
	}

	SECTION("Subtraction")
	{
		CHECK((math::Degree(angleValues[0]) - math::Degree(angleValues[1])).Value() == (angleValues[0] - angleValues[1]));
		CHECK((math::Degree(angleValues[0]) - angleValues[3]).Value() == (angleValues[0] - angleValues[3]));
		CHECK((math::Degree(angleValues[2]) - angleValues[4]).Value() == (angleValues[2] - angleValues[4]));
	}

	SECTION("Multiplication")
	{
		CHECK((math::Degree(angleValues[3]) * 5.0f).Value() == angleValues[3] * 5.0f);
		CHECK((math::Degree(angleValues[0]) * 0.0f).Value() == angleValues[0] * 0.0f);
		CHECK((math::Degree(angleValues[2]) * -2.45f).Value() == angleValues[2] * -2.45f);
	}

	SECTION("Division")
	{
		CHECK((math::Degree(angleValues[3]) / 5.0f).Value() == angleValues[3] / 5.0f);
		CHECK((math::Degree(angleValues[2]) / -2.45f).Value() == angleValues[2] / -2.45f);
	}

}

TEST_CASE("Radian", "[.all][angle][radian]")
{
	SECTION("Constructor")
	{
		// Void constructor
		math::Radian<int>		myVoidIntConstructor;
		math::Radian<float>		myVoidFloatConstructor;
		math::Radian<double>	myVoidDblConstructor;

		CHECK(myVoidIntConstructor.Value() == 0);
		CHECK(myVoidFloatConstructor.Value() == 0.0f);
		CHECK(myVoidDblConstructor.Value() == 0.0);

		// 1 value constructor
		math::Radian<int>		myValIntConstructor(1);
		math::Radian<float>		myValFloatConstructor(-PI);
		math::Radian<double>	myValDblConstructor(23.959999 * DEG2RAD);

		CHECK(myValIntConstructor.Value() == 1);
		CHECK(myValFloatConstructor.Value() == -PI);
		CHECK(myValDblConstructor.Value() == 23.959999 * DEG2RAD);
	}

	SECTION("Equality")
	{
		REQUIRE(math::Radian(PI) == math::Radian(PI));
		REQUIRE(math::Radian(-PI / 2.0f) == math::Radian(-PI / 2.0f));
		REQUIRE(math::Radian(0.27352) == math::Radian(0.27354));

		REQUIRE_FALSE(math::Radian(45.0) != math::Radian(45.0));
		REQUIRE(math::Radian(89.0) != math::Radian(160.0));
		REQUIRE(math::Radian(29.99998) != math::Radian(30.0));
	}

	SECTION("Functions")
	{
		CHECK(math::Radian(5.93412).Wrap() == math::Radian(5.93412));
		CHECK(math::Radian(5.93412).Wrap().Value() == 5.93412);
		CHECK(math::Radian(5.934119).Wrap() == math::Radian(-0.349066).Wrap());
	}

	float angleValues[] = {PI / 4.0f, PI / 2.0f, 2.0944f, -2.61799f, 0.855211f};
	SECTION("Addition")
	{
		CHECK((math::Radian(angleValues[0]) + math::Radian(angleValues[1])).Value() == (angleValues[0] + angleValues[1]));
		CHECK((math::Radian(angleValues[0]) + angleValues[3]).Value() == (angleValues[0] + angleValues[3]));
	}

	SECTION("Subtraction")
	{
		CHECK((math::Radian(angleValues[0]) - math::Radian(angleValues[1])).Value() == (angleValues[0] - angleValues[1]));
		CHECK((math::Radian(angleValues[0]) - angleValues[3]).Value() == (angleValues[0] - angleValues[3]));
		CHECK((math::Radian(angleValues[2]) - angleValues[4]).Value() == (angleValues[2] - angleValues[4]));
	}

	SECTION("Multiplication")
	{
		CHECK((math::Radian(angleValues[3]) * 5.0f).Value() == angleValues[3] * 5.0f);
		CHECK((math::Radian(angleValues[0]) * 0.0f).Value() == angleValues[0] * 0.0f);
		CHECK((math::Radian(angleValues[2]) * -2.45f).Value() == angleValues[2] * -2.45f);
	}

	SECTION("Division")
	{
		CHECK((math::Radian(angleValues[3]) / 5.0f).Value() == angleValues[3] / 5.0f);
		CHECK((math::Radian(angleValues[2]) / -2.45f).Value() == angleValues[2] / -2.45f);
	}
}