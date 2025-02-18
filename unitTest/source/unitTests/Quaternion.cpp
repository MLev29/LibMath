#include "LibMath/Quaternion.h"

#define GLM_ENABLE_EXPERIMENTAL
#define GLM_FORCE_QUAT_DATA_WXYZ
#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include <glm/common.hpp>
#include <glm/gtx/quaternion.hpp>

#define CHECK_QUAT(quat, quatGlm) CHECK(quat[1] == Catch::Approx(quatGlm.x)); CHECK(quat[2] == Catch::Approx(quatGlm.y)); CHECK(quat[3] == Catch::Approx(quatGlm.z)); CHECK(quat[0] == Catch::Approx(quatGlm.w))

TEST_CASE("Quaternion", "[.all][Quaternion]")
{
	SECTION("Constructor")
	{
		math::Vector3<float> vec3(1.0f, 2.0f, 3.0f);
		CHECK_QUAT(math::Quaternion<float>(), glm::quat());
		CHECK_QUAT(math::Quaternion<float>(1.0f, 2.0f, 3.0f, 4.0f), glm::quat(1.0f, 2.0f, 3.0f, 4.0f));
		CHECK_QUAT(math::Quaternion<float>(4.0f, vec3), glm::quat(4.0f, 1.0f, 2.0f, 3.0f));
	}

	SECTION("Functions")
	{
		// IsPure quaternion
		CHECK(math::Quaternion<float>(0.0f, 1.0f, 2.0f, 3.0f).IsPure());
		CHECK_FALSE(math::Quaternion<float>(0.01f, 1.0f, 2.0f, 3.0f).IsPure());
		CHECK_FALSE(math::Quaternion<float>(1.0f, 1.0f, 2.0f, 3.0f).IsPure());

		// Conjugate
		CHECK_QUAT(math::Quaternion<float>(1.0f, 2.0f, 3.0f, 4.0f).Conjugate(), glm::conjugate(glm::quat(1.0f, 2.0f, 3.0f, 4.0f)));
		CHECK_QUAT(math::Quaternion<float>(1.0f, -2.0f, -3.5f, 0.0f).Conjugate(), glm::conjugate(glm::quat(1.0f, -2.0f, -3.5f, 0.0f)));

		// Magnitude Squared
		CHECK(math::Quaternion<float>(1.0f, 2.0f, 3.0f, 4.0f).Dot(math::Quaternion<float>(1.0f, 2.0f, 3.0f, 4.0f)) == glm::dot(glm::quat(1.0f, 2.0f, 3.0f, 4.0f), glm::quat(1.0f, 2.0f, 3.0f, 4.0f)));

		// Magnitude
		CHECK(math::Quaternion<float>(1.0f, 2.0f, 3.0f, 4.0f).Magnitude() == glm::length(glm::quat(1.0f, 2.0f, 3.0f, 4.0f)));
		CHECK(math::Quaternion<float>(-5.0f, 2.3f, -10.0f, 4.0f).Magnitude() == glm::length(glm::quat(-5.0f, 2.3f, -10.0f, 4.0f)));

		// Normalize
		CHECK_QUAT(math::Quaternion(1.0f, 2.0f, 3.0f, 4.0f).Normalize(), glm::normalize(glm::quat(1.0f, 2.0f, 3.0f, 4.0f)));
		CHECK_QUAT(math::Quaternion(-5.0f, 2.3f, -10.0f, 4.0f).Normalize(), glm::normalize(glm::quat(-5.0f, 2.3f, -10.0f, 4.0f)));

		// Inverse
		CHECK_QUAT(math::Quaternion(1.0f, 2.0f, 3.0f, 4.0f).Inverse(), glm::inverse(glm::quat(1.0f, 2.0f, 3.0f, 4.0f)));
		CHECK_QUAT(math::Quaternion(-5.0f, 2.3f, -10.0f, 4.0f).Inverse(), glm::inverse(glm::quat(-5.0f, 2.3f, -10.0f, 4.0f)));

		// Rotate via an angle & axis
		CHECK_QUAT(math::Quaternion<float>::AngleAxis(45.0f * DEG2RAD, math::Vector3(0.0f, 1.0f, 0.0f)), glm::angleAxis(45.0f * DEG2RAD, glm::vec3(0.0f, 1.0f, 0.0f)));
	}

	SECTION("Operators")
	{
		math::Quaternion<float> quat1(1.0f, 2.0f, 3.0f, 4.0f);
		math::Quaternion<float> quat2(2.5f, -5.0f, 1.0f, -3.2f);
		glm::quat quat1Glm(1.0f, 2.0f, 3.0f, 4.0f);
		glm::quat quat2Glm(2.5f, -5.0f, 1.0f, -3.2f);
		const float scalar = 5.0f;

		// Operator +
		CHECK_QUAT((quat1 + quat2), (quat1Glm + quat2Glm));

		// Operator -
		CHECK_QUAT((quat1 - quat2), (quat1Glm - quat2Glm));

		// Operator * value
		CHECK_QUAT((quat1 * scalar), (quat1Glm * scalar));

		// Operator / value
		CHECK_QUAT((quat1 / scalar), (quat1Glm / scalar));

		// Operator * quaternion
		CHECK_QUAT((quat1 * quat2), (quat1Glm * quat2Glm));

		// Operator / quaternion
		//CHECK_QUAT((quat1 / quat2), (quat1Glm / quat2Glm));

		// Operator +=
		quat1 += quat2;
		quat1Glm += quat2Glm;
		CHECK_QUAT(quat1, quat1Glm);

		// Operator -=
		quat1 -= quat2;
		quat1Glm -= quat2Glm;
		CHECK_QUAT(quat1, quat1Glm);

		// Operator *= value
		quat1 *= scalar;
		quat1Glm *= scalar;
		CHECK_QUAT(quat1, quat1Glm);

		// Operator /= value
		quat1 /= scalar;
		quat1Glm /= scalar;
		CHECK_QUAT(quat1, quat1Glm);

		// Operator *= quaternion
		quat1 *= quat2;
		quat1Glm *= quat2Glm;
		CHECK_QUAT(quat1, quat1Glm);

		// Operator ==
		CHECK(quat1 == quat1);
		CHECK_FALSE(quat1 == quat2);

		// Operator !=
		CHECK(quat1 != quat2);
		CHECK_FALSE(quat1 != quat1);
	}
}