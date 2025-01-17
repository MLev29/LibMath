#include <LibMath/Vector.h>
#include <LibMath/Angle.h>

#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#define GLM_FORCE_SILENT_WARNINGS
#define GLM_FORCE_XYZW_ONLY
#include <glm/glm.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/projection.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/vector_angle.hpp>

//using namespace LibMath::Literal;

#define CHECK_VECTOR2(vector, vectorGlm) CHECK(vector[0] == Catch::Approx(vectorGlm.x)); CHECK(vector[1] == Catch::Approx(vectorGlm.y))
#define CHECK_VECTOR3(vector, vectorGlm) CHECK(vector[0] == Catch::Approx(vectorGlm.x)); CHECK(vector[1] == Catch::Approx(vectorGlm.y)); CHECK(vector[2] == Catch::Approx(vectorGlm.z))
#define CHECK_VECTOR4(vector, vectorGlm) CHECK(vector[0] == Catch::Approx(vectorGlm.x)); CHECK(vector[1] == Catch::Approx(vectorGlm.y)); CHECK(vector[2] == Catch::Approx(vectorGlm.z)); CHECK(vector[3] == Catch::Approx(vectorGlm.w))

TEST_CASE("Vector2", "[.all][vector][Vector2]")
{
	SECTION("Instantiation")
	{
		// destructor
		{
			LibMath::Vector2<float> temp;
			(void) temp;
		}

		// Default constructor
		LibMath::Vector2<float> empty;
		glm::vec2 emptyGlm{};
		CHECK_VECTOR2(empty, emptyGlm);

		// Basic constructor
		LibMath::Vector2 scalar{2.5f};
		glm::vec2 scalarGlm{2.5f};
		CHECK_VECTOR2(scalar, scalarGlm);

		LibMath::Vector2 multipleParam{2.5f, 0.5f};
		glm::vec2 multipleParamGlm{2.5f, 0.5f};
		CHECK_VECTOR2(multipleParam, multipleParamGlm);

		// Copy constructor
		LibMath::Vector2 copy{multipleParam};
		glm::vec2 copyGlm{multipleParamGlm};
		CHECK_VECTOR2(copy, copyGlm);

		// Assignment operator
		empty = multipleParam;
		emptyGlm = multipleParamGlm;
		CHECK_VECTOR2(empty, emptyGlm);

		// OpenGL compatibility
		CHECK(sizeof LibMath::Vector2<float>() == sizeof glm::vec2);
		CHECK(memcmp(&multipleParam, &multipleParamGlm, sizeof LibMath::Vector2<float>) == 0);
	}

	SECTION("Accessor")
	{
		const float values[2] = {2.5f, 0.5f};

		LibMath::Vector2 vector2{values[0], values[1]};

		// Index operator
		{
			LibMath::Vector2<float> const& vectorConst = vector2;
			CHECK(vectorConst[0] == values[0]); // X value
			CHECK(vectorConst[1] == values[1]); // Y value
		}
		{
			vector2[0] += 1.0f;
			vector2[1] += 1.0f;

			CHECK(vector2[0] == values[0] + 1.0f); // X value
			CHECK(vector2[1] == values[1] + 1.0f); // Y value
		}

		// Setter functions
		{
			vector2[0] = values[0];
			vector2[1] = values[1];
		}
	}

	SECTION("Comparator")
	{
		LibMath::Vector2 vector2{2.5f, 0.5f};

		// Check against self
		{
			CHECK(vector2 == vector2);
			CHECK_FALSE(vector2 != vector2);
		}

		// Testing different cases for equality operator
		{
			LibMath::Vector2 zero(0.0f, 0.0f);
			LibMath::Vector2 decimal(0.123f, 0.355f);
			LibMath::Vector2 largeFloat(10000.5f, -99999.0f);

			CHECK_FALSE(zero == decimal);
			CHECK(zero != decimal);
			CHECK_FALSE(zero != zero);
			CHECK_FALSE(decimal != decimal);
			CHECK(zero == zero);
			CHECK(decimal == decimal);
			CHECK_FALSE(LibMath::Vector2{0.5f, 2.5f} == zero);
			CHECK(LibMath::Vector2{0.5f, 2.5f} != zero);
			CHECK(LibMath::Vector2(10000.5f, -99999.0f) == largeFloat);
		}

		{
			// Testing comparison functionality
			LibMath::Vector2 vec2{2.5f, 0.5f};

			CHECK_FALSE(vec2.IsUnit());
			CHECK(LibMath::Vector2{0.6f, 0.8f}.IsUnit());
		}
	}

	SECTION("Constant")
	{
		CHECK_VECTOR2(LibMath::Vector2<float>::Zero(), glm::vec2(0.0f, 0.0f));
		CHECK_VECTOR2(LibMath::Vector2<float>::Up(), glm::vec2(0.0f, 1.0f));
		CHECK_VECTOR2(LibMath::Vector2<float>::Down(), glm::vec2(0.0f, -1.0f));
		CHECK_VECTOR2(LibMath::Vector2<float>::Right(), glm::vec2(1.0f, 0.0f));
		CHECK_VECTOR2(LibMath::Vector2<float>::Left(), glm::vec2(-1.0f, 0.0f));
	}

	SECTION("Arithmetic")
	{
		const float values1[2] = {5.0f, 3.0f};
		const float values2[2] = {8.0f, -2.0f};

		LibMath::Vector2 vec1(values1[0], values1[1]);
		LibMath::Vector2 vec2(values2[0], values2[1]);

		glm::vec2 vec1Glm(values1[0], values1[1]);
		glm::vec2 vec2Glm(values2[0], values2[1]);

		// Addition operator
		{
			CHECK_VECTOR2(LibMath::Vector2(vec1 + vec2), glm::vec2(vec1Glm + vec2Glm));
			CHECK_VECTOR2(LibMath::Vector2(vec1 + vec1), glm::vec2(vec1Glm + vec1Glm));
			CHECK_VECTOR2(LibMath::Vector2(vec1 + 1.0f), glm::vec2(vec1Glm + 1.0f));
			//CHECK_VECTOR2(LibMath::Vector2(-2.5f + vec2), glm::vec2(-2.5f + vec2Glm));
		}

		// Subtraction operator
		{
			CHECK_VECTOR2(LibMath::Vector2(vec1 - vec2), glm::vec2(vec1Glm - vec2Glm));
			CHECK_VECTOR2(LibMath::Vector2(vec1 - vec1), glm::vec2(vec1Glm - vec1Glm));
			CHECK_VECTOR2(LibMath::Vector2(vec1 - 1.0f), glm::vec2(vec1Glm - 1.0f));
			//CHECK_VECTOR2(LibMath::Vector2(-2.5f - vec2), glm::vec2(-2.5f - vec2Glm));
		}

		// Multiplication operator
		{
			CHECK_VECTOR2(LibMath::Vector2(vec1 * vec2), glm::vec2(vec1Glm * vec2Glm));
			CHECK_VECTOR2(LibMath::Vector2(vec1 * vec1), glm::vec2(vec1Glm * vec1Glm));
			CHECK_VECTOR2(LibMath::Vector2(vec1 * 1.0f), glm::vec2(vec1Glm * 1.0f));
			//CHECK_VECTOR2(LibMath::Vector2(-2.5f * vec2), glm::vec2(-2.5f * vec2Glm));
		}

		// Addition equal operator
		{
			vec1 += vec2;
			CHECK_VECTOR2(vec1, glm::vec2(vec1Glm + vec2Glm));
		}

		// Reset values
		vec1[0] = values1[0];
		vec1[1] = values1[1];

		// Subtraction equal operator
		{

			vec1 -= vec2;
			CHECK_VECTOR2(vec1, glm::vec2(vec1Glm - vec2Glm));
		}

		// Reset values
		vec1[0] = values1[0];
		vec1[1] = values1[1];

		// Multiplication equal operator
		{
			vec1 *= vec2;
			CHECK_VECTOR2(vec1, glm::vec2(vec1Glm * vec2Glm));
		}
	}

	SECTION("Transformation")
	{

		// Translate vector
		{
			constexpr float values[2] = {7.5f, -2.0f};
			constexpr float translateValues[2] = {2.5f, 4.0f};

			LibMath::Vector2 vector(values[0], values[1]);
			LibMath::Vector2 translationVector(translateValues[0], translateValues[1]);

			vector.Translate(translationVector);

			glm::vec2 vec2Glm(values[0], values[1]);
			glm::vec2 translateGlm(translateValues[0], translateValues[1]);

			CHECK_VECTOR2(vector, glm::vec2(vec2Glm + translateGlm));
		}

		// Scale vector
		{
			constexpr float values[2] = {7.5f, -2.0f};
			constexpr float scaleFactor[2] = {2.0f, 0.5f};

			LibMath::Vector2 vector(values[0], values[1]);
			LibMath::Vector2 scaleVec2(scaleFactor[0], scaleFactor[1]);

			glm::vec2 vec2Glm(values[0], values[1]);
			glm::vec2 scaleGlm(scaleFactor[0], scaleFactor[1]);

			vector.Scale(scaleVec2);

			CHECK_VECTOR2(vector, glm::vec2(vec2Glm * scaleGlm));
		}

		// Rotate
		{
			constexpr float values[2] = {2.0f, 0.0f};
			constexpr float angle = 45.0f * DEG2RAD;

			LibMath::Vector2 vector(values[0], values[1]);
			glm::vec2 vectorGlm(values[0], values[1]);
			glm::vec2 resultGlm = glm::rotate(vectorGlm, angle);

			vector.Rotate(angle);

			CHECK_VECTOR2(vector, resultGlm);
		}
	}

	SECTION("Functionality")
	{
		constexpr float values[2] = {2.5f, 1.0f};
		constexpr float valuesNegative[2] = {-3.0f, -5.0f};

		SECTION("Normalize")
		{
			LibMath::Vector2 vector(values[0], values[1]);
			glm::vec2 vectorGlm(values[0], values[1]);
			CHECK_VECTOR2(vector.Normalize(), glm::normalize(vectorGlm));

			vector = {valuesNegative[0], valuesNegative[1]};
			vectorGlm = {valuesNegative[0], valuesNegative[1]};
			CHECK_VECTOR2(vector.Normalize(), glm::normalize(vectorGlm));
		}

		SECTION("Dot")
		{
			LibMath::Vector2 vectorA(values[0], values[1]);
			LibMath::Vector2 vectorB(valuesNegative[0], valuesNegative[1]);
			glm::vec2 vectorGlmA(values[0], values[1]);
			glm::vec2 vectorGlmB(valuesNegative[0], valuesNegative[1]);

			CHECK(vectorA.Dot(vectorB) == glm::dot(vectorGlmA, vectorGlmB));
		}

		SECTION("Magnitude")
		{
			LibMath::Vector2 vectorA(values[0], values[1]);
			LibMath::Vector2 vectorB(valuesNegative[0], valuesNegative[1]);
			glm::vec2 vectorGlmA(values[0], values[1]);
			glm::vec2 vectorGlmB(valuesNegative[0], valuesNegative[1]);

			CHECK(vectorA.Magnitude() == glm::length(vectorGlmA));
			CHECK(vectorB.Magnitude() == glm::length(vectorGlmB));
		}

		SECTION("Angle")
		{
			LibMath::Vector2 vectorA(values[0], values[1]);
			LibMath::Vector2 vectorB(valuesNegative[0], valuesNegative[1]);
			glm::vec2 vectorGlmA(values[0], values[1]);
			glm::vec2 vectorGlmB(valuesNegative[0], valuesNegative[1]);

			float angleGlm = glm::angle(glm::normalize(vectorGlmA), glm::normalize(vectorGlmB));
			(void) angleGlm;
			CHECK(vectorA.AngleFrom(vectorB) == Catch::Approx(angleGlm));
		}

		SECTION("Project")
		{
			LibMath::Vector2 vectorA(values[0], values[1]);
			LibMath::Vector2 vectorB(valuesNegative[0], valuesNegative[1]);
			glm::vec2 vectorGlmA(values[0], values[1]);
			glm::vec2 vectorGlmB(valuesNegative[0], valuesNegative[1]);

			glm::vec2 resultGlm = glm::proj(vectorGlmA, vectorGlmB);

			CHECK_VECTOR2(vectorA.Project(vectorB), resultGlm);
		}

		SECTION("Reflection")
		{
			LibMath::Vector2 vectorA(values[0], values[1]);
			LibMath::Vector2 vectorB(valuesNegative[0], valuesNegative[1]);
			glm::vec2 vectorGlmA(values[0], values[1]);
			glm::vec2 vectorGlmB(valuesNegative[0], valuesNegative[1]);

			glm::vec2 resultGlm = glm::reflect(vectorGlmA, glm::normalize(vectorGlmB));
			LibMath::Vector2<float> result = vectorA.Reflect(vectorB);

			CHECK_VECTOR2(result, resultGlm);
		}
	}
}

TEST_CASE("Vector3", "[.all][vector][Vector3]")
{
	SECTION("Instantiation")
	{
		// destructor
		{
			LibMath::Vector3<float> temp;
			(void) temp;
		}

		// default constructor
		LibMath::Vector3<float> empty;
		glm::vec3 emptyGlm{};
		CHECK_VECTOR3(empty, emptyGlm);

		// basic constructor
		LibMath::Vector3 oneParam{2.5f};
		glm::vec3 oneParamGlm{2.5f};
		CHECK_VECTOR3(oneParam, oneParamGlm);

		LibMath::Vector3 allParam{2.5f, .5f, 2.f};
		glm::vec3 allParamGlm{2.5f, .5f, 2.f};
		CHECK_VECTOR3(allParam, allParamGlm);

		// copy constructor
		LibMath::Vector3 copy{allParam};
		glm::vec3 copyGlm{allParamGlm};
		CHECK_VECTOR3(copy, copyGlm);

		// assignment operator
		empty = allParam;
		emptyGlm = allParamGlm;
		CHECK_VECTOR3(empty, emptyGlm);

		// OpenGL compatibility
		CHECK(sizeof LibMath::Vector3<float> == sizeof glm::vec3);
		CHECK(memcmp(&allParam, &allParamGlm, sizeof LibMath::Vector3<float>) == 0);
	}

	SECTION("Accessor")
	{
		float const x = 2.5f;
		float const y = .5f;
		float const z = 2.f;
		LibMath::Vector3 vector{x, y, z};

		{
			LibMath::Vector3<float> const& vectorConst = vector;
			CHECK(vectorConst[0] == x);
			CHECK(vectorConst[1] == y);
			CHECK(vectorConst[2] == z);
		}

		{
			vector[0] += 1.f;
			vector[1] += 1.f;
			vector[2] += 1.f;
			CHECK(vector[0] == x + 1.f);
			CHECK(vector[1] == y + 1.f);
			CHECK(vector[2] == z + 1.f);
		}
	}

	SECTION("Comparator")
	{
		// compare with self
		LibMath::Vector3 self{2.5f, .5f, 2.f};
		CHECK(self == self);
		CHECK_FALSE(self != self);

		// compare with same
		CHECK(LibMath::Vector3{2.5f, .5f, 2.f} == LibMath::Vector3{2.5f, .5f, 2.f});
		CHECK_FALSE(LibMath::Vector3{2.5f, .5f, 2.f} != LibMath::Vector3{2.5f, .5f, 2.f});

		// trying to find copy/paste mistake
		LibMath::Vector3 twos{2.f, 2.f, 2.f};
		CHECK_FALSE(LibMath::Vector3{.5f, 2.f, 2.f} == twos);
		CHECK_FALSE(LibMath::Vector3{2.f, .5f, 2.f} == twos);
		CHECK_FALSE(LibMath::Vector3{2.f, 2.f, .5f} == twos);
		CHECK(LibMath::Vector3{.5f, 2.f, 2.f} != twos);
		CHECK(LibMath::Vector3{2.f, .5f, 2.f} != twos);
		CHECK(LibMath::Vector3{2.f, 2.f, .5f} != twos);
		CHECK_FALSE(twos == LibMath::Vector3{.5f, 2.f, 2.f});
		CHECK_FALSE(twos == LibMath::Vector3{2.f, .5f, 2.f});
		CHECK_FALSE(twos == LibMath::Vector3{2.f, 2.f, .5f});
		CHECK(twos != LibMath::Vector3{.5f, 2.f, 2.f});
		CHECK(twos != LibMath::Vector3{2.f, .5f, 2.f});
		CHECK(twos != LibMath::Vector3{2.f, 2.f, .5f});

		// testing comparison functionality
		LibMath::Vector3 small{2.5f, .5f, 2.f};
		LibMath::Vector3 big{3.75f, 3.f, .75f};

		CHECK(big.IsLongerThan(small));
		CHECK_FALSE(small.IsLongerThan(big));

		CHECK(small.IsShorterThan(big));
		CHECK_FALSE(big.IsShorterThan(small));

		CHECK_FALSE(big.IsLongerThan(big));
		CHECK_FALSE(big.IsShorterThan(big));

		CHECK_FALSE(self.IsUnit());
		CHECK(LibMath::Vector3{0.771516740f, 0.154303357f, 0.617213428f}.IsUnit());
	}

	SECTION("Constant")
	{
		CHECK_VECTOR3(LibMath::Vector3<float>::Backward(), glm::vec3(0.f, 0.f, -1.f));

		CHECK_VECTOR3(LibMath::Vector3<float>::Down(), glm::vec3(0.f, -1.f, 0.f));

		CHECK_VECTOR3(LibMath::Vector3<float>::Forward(), glm::vec3(0.f, 0.f, 1.f));

		CHECK_VECTOR3(LibMath::Vector3<float>::Left(), glm::vec3(-1.f, 0.f, 0.f));

		CHECK_VECTOR3(LibMath::Vector3<float>::Right(), glm::vec3(1.f, 0.f, 0.f));

		CHECK_VECTOR3(LibMath::Vector3<float>::Up(), glm::vec3(0.f, 1.f, 0.f));

		CHECK_VECTOR3(LibMath::Vector3<float>::Zero(), glm::vec3(0.f, 0.f, 0.f));
	}

	SECTION("Arithmetic")
	{
		LibMath::Vector3<float> const small{2.5f, .5f, 2.f};
		LibMath::Vector3<float> const big{3.75f, 3.f, .75f};

		glm::vec3 const smallGlm{2.5f, .5f, 2.f};
		glm::vec3 const bigGlm{3.75f, 3.f, .75f};

		SECTION("Addition")
		{
			{
				LibMath::Vector3<float> sumAssignment = big;
				sumAssignment += small;

				glm::vec3 sumAssignmentGlm = bigGlm;
				sumAssignmentGlm += smallGlm;

				CHECK_VECTOR3(sumAssignment, sumAssignmentGlm);
			}

			{
				LibMath::Vector3<float> sum = big + small;

				glm::vec3 sumGlm = bigGlm + smallGlm;

				CHECK_VECTOR3(sum, sumGlm);
			}
		}

		SECTION("Opposite")
		{
			LibMath::Vector3 opposite = -LibMath::Vector3{3.7f, 3.f, .7f};

			glm::vec3 oppositeGlm = -glm::vec3{3.7f, 3.f, .7f};

			CHECK_VECTOR3(opposite, oppositeGlm);
		}

		SECTION("Subtraction")
		{
			{
				LibMath::Vector3 differenceAssignment = big;
				differenceAssignment -= small;

				glm::vec3 differenceAssignmentGlm = bigGlm;
				differenceAssignmentGlm -= smallGlm;

				CHECK_VECTOR3(differenceAssignment, differenceAssignmentGlm);
			}

			{
				LibMath::Vector3 difference = big - small;

				glm::vec3 differenceGlm = bigGlm - smallGlm;

				CHECK_VECTOR3(difference, differenceGlm);
			}
		}

		SECTION("Multiplication")
		{
			{
				LibMath::Vector3 productAssignment = big;
				productAssignment *= small;

				glm::vec3 productAssignmentGlm = bigGlm;
				productAssignmentGlm *= smallGlm;

				CHECK_VECTOR3(productAssignment, productAssignmentGlm);
			}

			{
				LibMath::Vector3 product = big * small;

				glm::vec3 productGlm = bigGlm * smallGlm;

				CHECK_VECTOR3(product, productGlm);
			}
		}

		SECTION("Division")
		{
			{
				LibMath::Vector3 quotientAssignment = big;
				quotientAssignment /= small;

				glm::vec3 quotientAssignmentGlm = bigGlm;
				quotientAssignmentGlm /= smallGlm;

				CHECK_VECTOR3(quotientAssignment, quotientAssignmentGlm);
			}

			{
				LibMath::Vector3 quotient = big / small;

				glm::vec3 quotientGlm = bigGlm / smallGlm;

				CHECK_VECTOR3(quotient, quotientGlm);
			}
		}
	}

	SECTION("Transformation")
	{
		LibMath::Vector3 const origin{2.5f, .5f, 2.f};
		LibMath::Vector3 const transformation{-2.f, 0.f, 1.25f};

		glm::vec4 const originGlm{2.5f, .5f, 2.f, 1.f};
		glm::vec3 const transformationGlm{-2.f, 0.f, 1.25f};

		SECTION("Translation")
		{
			LibMath::Vector3 translate = origin;
			translate.Translate(transformation);

			glm::vec4 translateGlm = glm::translate(transformationGlm) * originGlm;

			CHECK_VECTOR3(translate, translateGlm);
		}

		SECTION("Scale")
		{
			LibMath::Vector3 scale = origin;
			scale.Scale(transformation);

			glm::vec4 scaleGlm = glm::scale(transformationGlm) * originGlm;

			CHECK_VECTOR3(scale, scaleGlm);
		}

		SECTION("Rotation")
		{
			//SECTION("Euler Angle")
			//{
			//	LibMath::Vector3 rotate = origin;
			//	rotate.Rotate(LibMath::Radian{transformation.m_x}, LibMath::Radian{transformation.m_y}, LibMath::Radian{transformation.m_z});
			//
			//	glm::vec4 rotateGlm = glm::orientate4(transformationGlm) * originGlm;
			//	auto glmMatrix = glm::orientate4(transformationGlm);
			//	CHECK_VECTOR3(rotate, rotateGlm);
			//}

			//SECTION("Axis")
			//{
			//	LibMath::Vector3 rotate = origin;
			//	rotate.Rotate(-3_rad, transformation);
			//
			//	glm::vec4 rotateGlm = glm::rotate(-3.f, transformationGlm) * originGlm;
			//
			//	CHECK_VECTOR3(rotate, rotateGlm);
			//}

			SECTION("Quaternion")
			{
				// todo
			}
		}
	}

	SECTION("Functionality")
	{
		LibMath::Vector3 const base{2.5f, .5f, 2.f};
		LibMath::Vector3 const other{3.75f, 3.f, .75f};

		glm::vec3 const baseGlm{2.5f, .5f, 2.f};
		glm::vec3 const otherGlm{3.75f, 3.f, .75f};

		SECTION("Angle")
		{
			LibMath::Radian angle = base.AngleFrom(other);
		
			float angleGlm = glm::angle(glm::normalize(baseGlm), glm::normalize(otherGlm));
		
			CHECK(angle.Value() == Catch::Approx(angleGlm));
		}

		SECTION("Cross")
		{
			LibMath::Vector3<float> cross = base.Cross(other);

			glm::vec3 crossGlm = glm::cross(baseGlm, otherGlm);

			CHECK_VECTOR3(cross, crossGlm);
		}

		SECTION("Dot")
		{
			float dot = base.Dot(other);

			float dotGlm = glm::dot(baseGlm, otherGlm);

			CHECK(dot == dotGlm);
		}

		SECTION("Distance")
		{
			//{
			//	float distance = base.DistanceFrom(other);
			//
			//	float distanceGlm = glm::distance(baseGlm, otherGlm);
			//
			//	CHECK(distance == Catch::Approx(distanceGlm));
			//}
			//
			//{
			//	float distanceSquare = base.DistanceSquaredFrom(other);
			//
			//	float distanceSquareGlm = glm::distance2(baseGlm, otherGlm);
			//
			//	CHECK(distanceSquare == Catch::Approx(distanceSquareGlm));
			//}
			//
			//{
			//	float distance2D = base.Distance2DFrom(other);
			//
			//	float distance2DGlm = glm::distance(glm::vec2(baseGlm), glm::vec2(otherGlm));
			//
			//	CHECK(distance2D == Catch::Approx(distance2DGlm));
			//}
			//
			//{
			//	float distance2DSquare = base.Distance2DSquaredFrom(other);
			//
			//	float distance2DSquareGlm = glm::distance2(glm::vec2(baseGlm), glm::vec2(otherGlm));
			//
			//	CHECK(distance2DSquare == Catch::Approx(distance2DSquareGlm));
			//}
		}

		SECTION("Magnitude")
		{
			{
				float magnitude = base.Magnitude();

				float magnitudeGlm = glm::length(baseGlm);

				CHECK(magnitude == Catch::Approx(magnitudeGlm));
			}

			{
				float magnitudeSquare = base.MagnitudeSquared();

				float magnitudeSquareGlm = glm::length2(baseGlm);

				CHECK(magnitudeSquare == Catch::Approx(magnitudeSquareGlm));
			}
		}

		SECTION("Normal")
		{
			LibMath::Vector3 normalize = base;
			normalize.Normalize();

			glm::vec3 normalizeGlm = glm::normalize(baseGlm);

			CHECK_VECTOR3(normalize, normalizeGlm);
		}

		SECTION("ProjectOnto")
		{
			LibMath::Vector3 project = base;
			project.Project(other);
		
			glm::vec3 projectGlm = glm::proj(baseGlm, otherGlm);
		
			CHECK_VECTOR3(project, projectGlm);
		}
		
		SECTION("ReflectOnto")
		{
			LibMath::Vector3 reflect = base;
			reflect.Reflect(other);
		
			glm::vec3 reflectGlm = glm::reflect(baseGlm, glm::normalize(otherGlm));
		
			CHECK_VECTOR3(reflect, reflectGlm);
		}
	}

	SECTION("Extra")
	{
		//LibMath::Vector3 const input{2.5f, -.5f, 2.f};
		//{
		//	std::stringstream buffer;
		//	buffer << input;
		//	CHECK(buffer.str() == "{2.5,-0.5,2}");
		//
		//	buffer << " extra";
		//
		//	LibMath::Vector3 output;
		//	buffer >> output;
		//	CHECK(output == input);
		//
		//	std::string extra;
		//	buffer >> extra;
		//	CHECK(extra == "extra");
		//}
		//
		//{
		//	CHECK(input.String() == "{2.5,-0.5,2}");
		//
		//	CHECK(input.StringLong() == "Vector3{ x:2.5, y:-0.5, z:2 }");
		//}
	}

	SECTION("Debug")
	{
#if (defined _DEBUG) || (! defined NDEBUG)
		LibMath::Vector3 vector{2.5f, .5f, 2.f};

		//CHECK_THROWS(vector[-1]);
		//CHECK_THROWS(vector[3]);
#endif // DEBUG
	}
}

TEST_CASE("Vector4", "[.all][vector][Vector4]")
{
	SECTION("Instantiation")
	{
		// Constructor with 0 arguments
		{
			LibMath::Vector4<float> vector4;
			glm::vec4 vector4Glm(0.0f, 0.0f, 0.0f, 0.0f);

			CHECK_VECTOR4(vector4, vector4Glm);
		}

		// Constructor with 1 argument (scalar)
		{
			float scalar = 5.0f;
			LibMath::Vector4 vector4(scalar);
			glm::vec4 vector4Glm(scalar);

			CHECK_VECTOR4(vector4, vector4Glm);
		}

		// Constructor taking 4 arguments (x, y, z, w)
		{
			float values[4] = {1.0f, 2.0f, 3.0f, 4.0f};

			LibMath::Vector4 vector4(values[0], values[1], values[2], values[3]);
			glm::vec4 vector4Glm(values[0], values[1], values[2], values[3]);

			CHECK_VECTOR4(vector4, vector4Glm);
		}

		// Setters & Getters
		{
			const float values[4] = {1.0f, 2.0f, 3.0f, 4.0f};

			LibMath::Vector4<float> vector4;
			glm::vec4 vector4Glm(0.0f, 0.0f, 0.0f, 0.0f);

			// Both vectors all components initialized to 0
			CHECK_VECTOR2(vector4, vector4Glm);

			vector4[0] = values[0];
			vector4[1] = values[1];
			vector4[2] = values[2];
			vector4[3] = values[3];

			vector4Glm = {values[0], values[1], values[2], values[3]};

			CHECK(vector4[0] == vector4Glm.x);
			CHECK(vector4[1] == vector4Glm.y);
			CHECK(vector4[2] == vector4Glm.z);
			CHECK(vector4[3] == vector4Glm.w);
		}
	}

	SECTION("Accessor")
	{
		const float x = 2.5f;
		const float y = 0.5f;
		const float z = 2.0f;
		const float w = 1.0f;

		LibMath::Vector4 vector{x, y, z, w};

		{
			LibMath::Vector4<float> const& vectorConst = vector;
			CHECK(vectorConst[0] == x);
			CHECK(vectorConst[1] == y);
			CHECK(vectorConst[2] == z);
			CHECK(vectorConst[3] == w);
		}

		{
			vector[0] += 1.f;
			vector[1] += 1.f;
			vector[2] += 1.f;
			vector[3] += 1.f;
			CHECK(vector[0] == x + 1.f);
			CHECK(vector[1] == y + 1.f);
			CHECK(vector[2] == z + 1.f);
			CHECK(vector[3] == w + 1.f);
		}
	}

	SECTION("Comparator")
	{
		// Equality & not equal operators
		{
			const float values[4] = {1.5f, -2.0f, 4.1287128f, 0.0f};
			const float values2[4] = {4.25f, 3.0f, -2.9739f, 0.0f};

			LibMath::Vector4 vector4A(values[0], values[1], values[2], values[3]);
			LibMath::Vector4 vector4B(values2[0], values2[1], values2[2], values2[3]);

			CHECK(vector4A == vector4A);
			CHECK(vector4B == vector4B);
			CHECK_FALSE(vector4A == vector4B);
			CHECK(vector4A != vector4B);
			CHECK_FALSE(vector4A != vector4A);
			CHECK_FALSE(vector4B != vector4B);

		}

	}

	SECTION("Arithmetic")
	{
		const float valuesA[4] = {2.32f, -5.0f, 0.0f, 1.0f};
		const float valuesB[4] = {-3.2f, 2.1f, -2.0f, 0.0f};

		LibMath::Vector4 vector4A(valuesA[0], valuesA[1], valuesA[2], valuesA[3]);
		LibMath::Vector4 vector4B(valuesB[0], valuesB[1], valuesB[2], valuesB[3]);

		glm::vec4 vector4AGlm(valuesA[0], valuesA[1], valuesA[2], valuesA[3]);
		glm::vec4 vector4BGlm(valuesB[0], valuesB[1], valuesB[2], valuesB[3]);

		SECTION("Addition")
		{
			// Vector + vector
			{
				CHECK_VECTOR4(LibMath::Vector4(vector4A + vector4A), glm::vec4(vector4AGlm + vector4AGlm));
				CHECK_VECTOR4(LibMath::Vector4(vector4B + vector4B), glm::vec4(vector4BGlm + vector4BGlm));
				CHECK_VECTOR4(LibMath::Vector4(vector4A + vector4B), glm::vec4(vector4AGlm + vector4BGlm));
			}

			// Vector + scalar
			{
				const float scalarA = 5.0f;
				const float scalarB = -2.5f;

				CHECK_VECTOR4(LibMath::Vector4(vector4A + scalarA), glm::vec4(vector4AGlm + scalarA));
				CHECK_VECTOR4(LibMath::Vector4(vector4A + scalarB), glm::vec4(vector4AGlm + scalarB));
			}

			// Vector += vector
			{
				vector4A += vector4A;
				vector4AGlm += vector4AGlm;
				CHECK_VECTOR4(vector4A, vector4AGlm);

				vector4A += vector4B;
				vector4AGlm += vector4BGlm;
				CHECK_VECTOR4(vector4A, vector4AGlm);
			}

			// Vector += scalar
			{
				const float scalarA = 5.0f;
				const float scalarB = -2.5f;

				vector4A += scalarA;
				vector4AGlm += scalarA;
				CHECK_VECTOR4(vector4A, vector4AGlm);

				vector4A += scalarB;
				vector4AGlm += scalarB;
				CHECK_VECTOR4(vector4A, vector4AGlm);
			}
		}

		SECTION("Subtraction")
		{
			// Vector - vector
			{
				CHECK_VECTOR4(LibMath::Vector4(vector4A - vector4A), glm::vec4(vector4AGlm - vector4AGlm));
				CHECK_VECTOR4(LibMath::Vector4(vector4B - vector4B), glm::vec4(vector4BGlm - vector4BGlm));
				CHECK_VECTOR4(LibMath::Vector4(vector4A - vector4B), glm::vec4(vector4AGlm - vector4BGlm));
			}

			// Vector - scalar
			{
				const float scalarA = 5.0f;
				const float scalarB = -2.5f;

				CHECK_VECTOR4(LibMath::Vector4(vector4A - scalarA), glm::vec4(vector4AGlm - scalarA));
				CHECK_VECTOR4(LibMath::Vector4(vector4A - scalarB), glm::vec4(vector4AGlm - scalarB));
			}

			// Vector -= vector
			{
				vector4A -= vector4A;
				vector4AGlm -= vector4AGlm;
				CHECK_VECTOR4(vector4A, vector4AGlm);

				vector4A -= vector4B;
				vector4AGlm -= vector4BGlm;
				CHECK_VECTOR4(vector4A, vector4AGlm);
			}

			// Vector -= scalar
			{
				const float scalarA = 5.0f;
				const float scalarB = -2.5f;

				vector4A -= scalarA;
				vector4AGlm -= scalarA;
				CHECK_VECTOR4(vector4A, vector4AGlm);

				vector4A -= scalarB;
				vector4AGlm -= scalarB;
				CHECK_VECTOR4(vector4A, vector4AGlm);
			}
		}

		SECTION("Multiplication")
		{
			// Vector * vector
			{
				CHECK_VECTOR4(LibMath::Vector4(vector4A * vector4A), glm::vec4(vector4AGlm * vector4AGlm));
				CHECK_VECTOR4(LibMath::Vector4(vector4B * vector4B), glm::vec4(vector4BGlm * vector4BGlm));
				CHECK_VECTOR4(LibMath::Vector4(vector4A * vector4B), glm::vec4(vector4AGlm * vector4BGlm));
			}

			// Vector * scalar
			{
				const float scalarA = 5.0f;
				const float scalarB = -2.5f;

				CHECK_VECTOR4(LibMath::Vector4(vector4A * scalarA), glm::vec4(vector4AGlm * scalarA));
				CHECK_VECTOR4(LibMath::Vector4(vector4A * scalarB), glm::vec4(vector4AGlm * scalarB));
			}

			// Vector *= vector
			{
				vector4A *= vector4A;
				vector4AGlm *= vector4AGlm;
				CHECK_VECTOR4(vector4A, vector4AGlm);

				vector4A *= vector4B;
				vector4AGlm *= vector4BGlm;
				CHECK_VECTOR4(vector4A, vector4AGlm);
			}

			// Vector *= scalar
			{
				const float scalarA = 5.0f;
				const float scalarB = -2.5f;

				vector4A *= scalarA;
				vector4AGlm *= scalarA;
				CHECK_VECTOR4(vector4A, vector4AGlm);

				vector4A *= scalarB;
				vector4AGlm *= scalarB;
				CHECK_VECTOR4(vector4A, vector4AGlm);
			}
		}

		SECTION("Division")
		{
			// Vector / scalar
			{
				const float scalar = 5.0f;
				const float zero = 0.0f;
				(void) zero;

				CHECK_VECTOR4(LibMath::Vector4(vector4A / scalar), glm::vec4(vector4AGlm / scalar));
				CHECK_VECTOR4(LibMath::Vector4(vector4B / scalar), glm::vec4(vector4BGlm / scalar));

				// Check for exception when dividing by 0
				//CHECK_THROWS(vector4A / zero);
			}

			// Vector /= scalar
			{
				const float scalarA = 5.0f;
				const float scalarB = -2.5f;
				const float zero = 0.0f;
				(void) zero;

				vector4A /= scalarA;
				vector4AGlm /= scalarA;
				CHECK_VECTOR4(vector4A, vector4AGlm);

				vector4A /= scalarB;
				vector4AGlm /= scalarB;
				CHECK_VECTOR4(vector4A, vector4AGlm);

				// Check for exception when dividing by 0
				//CHECK_THROWS(vector4A /= zero);
			}
		}
	}

	SECTION("Transformation")
	{
		constexpr float values[4] = {3.2f, 2.0f, -2.0f, 4.5f};

		LibMath::Vector4 vector4(values[0], values[1], values[2], values[3]);
		glm::vec4 vector4Glm(values[0], values[1], values[2], values[3]);

		SECTION("Translation")
		{
			const float translateValues[4] = {1.0f, 2.5f, -1.8f, 3.0f};

			LibMath::Vector4 translateVector(translateValues[0], translateValues[1], translateValues[2], translateValues[3]);
			glm::vec4 translateVectorGlm(translateValues[0], translateValues[1], translateValues[2], translateValues[3]);

			vector4.Translate(translateVector);
			glm::vec4 resultGlm = vector4Glm + translateVectorGlm;

			CHECK_VECTOR4(vector4, resultGlm);
		}

		SECTION("Scale")
		{
			const float scaleValues[4] = {1.0f, 2.5f, 2.38f, 0.0f};

			LibMath::Vector4 scaleVector(scaleValues[0], scaleValues[1], scaleValues[2], scaleValues[3]);
			glm::vec4 scaleVectorGlm(scaleValues[0], scaleValues[1], scaleValues[2], scaleValues[3]);

			vector4.Scale(scaleVector);
			glm::vec4 resultGlm = vector4Glm * scaleVectorGlm;

			CHECK_VECTOR4(vector4, resultGlm);
		}
	}

	SECTION("Functionality")
	{
		constexpr float valuesA[4] = {2.3f, 1.0f, 3.0f, -2.0f};
		constexpr float valuesB[4] = {-5.7f, 0.0f, 1.483f, 2.89f};

		LibMath::Vector4 vectorA(valuesA[0], valuesA[1], valuesA[2], valuesA[3]);
		LibMath::Vector4 vectorB(valuesB[0], valuesB[1], valuesB[2], valuesB[3]);
		LibMath::Vector4<float> vectorZero;
		(void) vectorZero;

		glm::vec4 vectorAGlm(valuesA[0], valuesA[1], valuesA[2], valuesA[3]);
		glm::vec4 vectorBGlm(valuesB[0], valuesB[1], valuesB[2], valuesB[3]);
		glm::vec4 vectorZeroGlm(0.0f);

		SECTION("Magnitude")
		{
			float magnitudeA = vectorA.Magnitude();
			float magnitudeB = vectorB.Magnitude();

			float magnitudeAGlm = glm::length(vectorAGlm);
			float magnitudeBGlm = glm::length(vectorBGlm);

			CHECK(magnitudeA == Catch::Approx(magnitudeAGlm));
			CHECK(magnitudeB == Catch::Approx(magnitudeBGlm));
			CHECK_FALSE(magnitudeA == Catch::Approx(magnitudeBGlm));
		}

		SECTION("Dot")
		{
			CHECK(vectorA.Dot(vectorA) == Catch::Approx(glm::dot(vectorAGlm, vectorAGlm)));
			CHECK(vectorB.Dot(vectorB) == Catch::Approx(glm::dot(vectorBGlm, vectorBGlm)));
			CHECK(vectorA.Dot(vectorB) == Catch::Approx(glm::dot(vectorAGlm, vectorBGlm)));
		}

		SECTION("Normalize")
		{
			vectorA.Normalize();
			vectorB.Normalize();

			CHECK_VECTOR4(vectorA, glm::normalize(vectorAGlm));
			CHECK_VECTOR4(vectorB, glm::normalize(vectorBGlm));
		}
	}
}