#define GLM_ENABLE_EXPERIMENTAL
#include "LibMath/Arithmetic.h"

#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark.hpp>
#include <glm/common.hpp>
#include <glm/gtx/integer.hpp>
#include <limits>

TEST_CASE("Arithmetic", ".[all][arithmetic]")
{
	SECTION("Absolute")
	{
		CHECK(math::Abs(-5)								== glm::abs(-5));
		CHECK(math::Abs(5.0f)							== glm::abs(5.0f));
		CHECK(math::Abs(0)								== glm::abs(0));
		CHECK(math::Abs(-0.0f)							== glm::abs(-0.0f));
		CHECK(math::Abs(-2.5123)						== glm::abs(-2.5123));
		CHECK(math::Abs(2999382719)						== glm::abs(2999382719));
		CHECK(math::Abs(-39482024.000020000003)			== glm::abs(-39482024.000020000003));
	}

	SECTION("Min")
	{
		CHECK(math::Min(0.0f, 5.0f)						== glm::min(0.0f, 5.0f));
		CHECK(math::Min(5.0f, 0.0f)						== glm::min(5.0f, 0.0f));
		CHECK(math::Min(-1.0f, 1.0f)					== glm::min(1.0f, -1.0f));
		CHECK(math::Min(0.0f, 0.0f)						== glm::min(0.0f, 0.0f));
		CHECK(math::Min(0.0f, -0.0000002f)				== glm::min(0.0f, -0.0000002f));
	}

	SECTION("Max")
	{
		CHECK(math::Max(0.0f, 5.0f)						== glm::max(0.0f, 5.0f));
		CHECK(math::Max(5.0f, 0.0f)						== glm::max(5.0f, 0.0f));
		CHECK(math::Max(-1.0f, 1.0f)					== glm::max(1.0f, -1.0f));
		CHECK(math::Max(0.0f, 0.0f)						== glm::max(0.0f, 0.0f));
		CHECK(math::Max(0.0f, -0.0000002f)				== glm::max(0.0f, -0.0000002f));
	}

	SECTION("Clamp")
	{
		CHECK(math::Clamp(2.5f, 0.0f, 5.0f)				== glm::clamp(2.5f, 0.0f, 5.0f));
		CHECK(math::Clamp(-2.5f, 0.0f, 5.0f)			== glm::clamp(-2.5f, 0.0f, 5.0f));
		CHECK(math::Clamp(7.5f, 0.0f, 5.0f)				== glm::clamp(7.5f, 0.0f, 5.0f));
		CHECK(math::Clamp(0.0000000001f, 0.0f, 5.0f)	== glm::clamp(0.0000000001f, 0.0f, 5.0f));
		CHECK(math::Clamp(-0.0000000001f, 0.0f, 5.0f)	== glm::clamp(-0.0000000001f, 0.0f, 5.0f));
	}

	SECTION("Wrap")
	{
		CHECK(math::Wrap(  2.5f, 0.0f, 5.0f)			== 2.5f);
		CHECK(math::Wrap( -2.5f, 0.0f, 5.0f)			== 2.5f);
		CHECK(math::Wrap( -1.5f, 0.0f, 5.0f)			== 3.5f);
		CHECK(math::Wrap(-10.0f, 0.0f, 5.0f)			== 5.0f);
		CHECK(math::Wrap( 28.0f, 0.0f, 5.0f)			== 3.0f);
	}

	SECTION("Floor")
	{
		CHECK(math::Floor(32.01)						== glm::floor(32.01));
		CHECK(math::Floor(-2.02)						== glm::floor(-2.02));
		CHECK(math::Floor(0.0f)							== glm::floor(0.0f));
		CHECK(math::Floor(5.0)							== glm::floor(5.0));
		CHECK(math::Floor(8.92)							== glm::floor(8.92));
	}

	SECTION("Ceiling")
	{
		CHECK(math::Ceiling(32.01)						== glm::ceil(32.01));
		CHECK(math::Ceiling(-2.02)						== glm::ceil(-2.02));
		CHECK(math::Ceiling(0.0f)						== glm::ceil(0.0f));
		CHECK(math::Ceiling(5.0)						== glm::ceil(5.0));
		CHECK(math::Ceiling(8.92)						== glm::ceil(8.92));
	}

	SECTION("Power")
	{
		CHECK(math::Power(2.0f, 2.0f)					== powf(2.0f, 2.0f));
		CHECK(math::Power(2.0f, 12.0f)					== powf(2.0f, 12.0f));
		CHECK(math::Power(-2.0f, 2.0f)					== powf(-2.0f, 2.0f));
		CHECK(math::Power(2.5f, 2.0f)					== powf(2.5f, 2.0f));
		CHECK(math::Power(10.0f, 10.0f)					== powf(10.0f, 10.0f));
		CHECK(math::Power(0.0f, 3.0f)					== powf(0.0f, 3.0f));
		CHECK(math::Power(7.0f, 0.0f)					== powf(7.0f, 0.0f));
	}

	SECTION("Root")
	{
		// TODO: add root function
	}

	SECTION("Factorial")
	{
		// GLM factorial can only do up to 12
		CHECK(math::Factorial(0.0f)						== glm::factorial(0.0f));
		CHECK(math::Factorial(5.0f)						== glm::factorial(5.0f));
		CHECK(math::Factorial(10.0f)					== glm::factorial(10.0f));
		CHECK(math::Factorial(-5.0f)					== -120.0f);
	}
}