#pragma once

#include "VariableType.hpp"
#include "Macros.h"

#include <cmath>
/* 
*	------- Vector2 -------
*	Static Functions:
*	- Up			DONE
*	- Down			DONE
*	- Left			DONE
*	- Right			DONE
*	- Zero			DONE
* 
*	Functions:
*	- Distance		DONE
*	- Dot			DONE
*	- Magnitude		DONE
*	- Normalize		DONE
*	- Normal		DONE
*	- AngleFrom		DONE
*	- IsUnit		DONE
*	- Translate		DONE
*	- Rotate		DONE
*	- Reflect		
*	- Project		
*	- Scale			DONE
*
*	Operators:
*	- Add		(+, +=)				DONE
*	- Subtract	(-, -=)				DONE
*	- Multiply	(*, *=)				DONE
*	- Divide	(/, /=)				DONE
*	- Compare	(epsilon test)		
*	- Index		(index operator)	DONE
*
*	To Do:
*	- Unit tests - code is currently untested
*/

#define SPECIFIER inline constexpr

namespace math
{
	template<math::math_type::NumericType T>
	class Vector2
	{
	public:
		constexpr				Vector2(void) = default;
		constexpr				Vector2(T const& scalar);
		constexpr				Vector2(T const& x, T const& y);

		constexpr				~Vector2(void) = default;

		static Vector2<T>		Up(void) const noexcept;
		static Vector2<T>		Down(void) const noexcept;
		static Vector2<T>		Left(void) const noexcept;
		static Vector2<T>		Right(void) const noexcept;
		static Vector2<T>		Zero(void) const noexcept;

		SPECIFIER T				Cross(Vector2<T> const& vec2);
		SPECIFIER T				Dot(Vector2<T> const& vec2);
		SPECIFIER T				Magnitude(void);
		SPECIFIER Vector2<T>	Normalize(void);
		SPECIFIER Vector2<T>	Normal(void);
		SPECIFIER T				AngleFrom(Vector2<T> const& vec2);
		SPECIFIER bool			IsUnit(void);
		SPECIFIER Vector2<T>	Reflect(Vector2<T> const& vec2);
		SPECIFIER Vector2<T>	Project(Vector2<T> const& vec2);

		SPECIFIER void			Translate(Vector2<T> const& vec2);
		SPECIFIER void			Rotate(T const& deg);
		SPECIFIER void			Scale(Vector2<T> const& vec2);

		SPECIFIER Vector2<T>	operator+(Vector2<T> const& vec2);
		SPECIFIER Vector2<T>	operator-(Vector2<T> const& vec2);
		SPECIFIER Vector2<T>	operator*(Vector2<T> const& vec2);
		SPECIFIER Vector2<T>	operator/(Vector2<T> const& vec2);
		SPECIFIER Vector2<T>&	operator+=(Vector2<T> const& vec2);
		SPECIFIER Vector2<T>&	operator-=(Vector2<T> const& vec2);
		SPECIFIER Vector2<T>&	operator*=(Vector2<T> const& vec2);
		SPECIFIER Vector2<T>&	operator/=(Vector2<T> const& vec2);
		SPECIFIER bool			operator==(Vector2<T> const& vec2);
		SPECIFIER T				operator[](int const& index) const;
		SPECIFIER T&			operator[](int const& index);

	private:
		T m_x;
		T m_y;
	};

	// Constructors
	template<math_type::NumericType T>
	inline constexpr math::Vector2<T>::Vector2(T const& scalar)
		: m_x(scalar), m_y(scalar)
	{
	}

	template<math_type::NumericType T>
	inline constexpr math::Vector2<T>::Vector2(T const& x, T const& y)
		: m_x(x), m_y(y)
	{
	}

	// Static Functions
	template<math_type::NumericType T>
	inline math::Vector2<T> math::Vector2<T>::Up(void) noexcept
	{
		return Vector2(
			reinterpret_cast<T>(0.0f),
			reinterpret_cast<T>(1.0f)
		);
	}

	template<math_type::NumericType T>
	inline math::Vector2<T> math::Vector2<T>::Down(void) noexcept
	{
		return Vector2(
			reinterpret_cast<T>(0.0f),
			reinterpret_cast<T>(-1.0f)
		);
	}

	template<math_type::NumericType T>
	inline math::Vector2<T> math::Vector2<T>::Left(void) noexcept
	{
		return Vector2(
			reinterpret_cast<T>(-1.0f),
			reinterpret_cast<T>(0.0f)
		);
	}

	template<math_type::NumericType T>
	inline math::Vector2<T> math::Vector2<T>::Right(void) noexcept
	{
		return Vector2(
			reinterpret_cast<T>(1.0f),
			reinterpret_cast<T>(0.0f)
		);
	}

	template<math_type::NumericType T>
	inline math::Vector2<T> math::Vector2<T>::Zero(void) noexcept
	{
		return Vector2(
			reinterpret_cast<T>(0.0f),
			reinterpret_cast<T>(0.0f)
		);
	}

	template<math::math_type::NumericType T>
	SPECIFIER T math::Vector2<T>::Cross(math::Vector2<T> const& vec2)
	{
		return SPECIFIER (m_x * vec2.m_y) - (m_y * vec2.m_x);
	}

	template<math::math_type::NumericType T>
	SPECIFIER T math::Vector2<T>::Dot(math::Vector2<T> const& vec2)
	{	
		return SPECIFIER (m_x * vec2.m_x) + (m_y * vec2.m_y);
	}

	template<math::math_type::NumericType T>
	SPECIFIER T math::Vector2<T>::Magnitude(void)
	{
		return SPECIFIER T(sqrtf(Dot(*this));
	}

	template<math::math_type::NumericType T>
	SPECIFIER math::Vector2<T> Vector2<T>::Normalize(void)
	{
		const T denominator = 1.0f / Dot(*this);

		return SPECIFIER Vector2<T>(
			m_x * denominator,
			m_y * denominator
		);
	}

	template<math::math_type::NumericType T>
	SPECIFIER math::Vector2<T> math::Vector2<T>::Normal(void)
	{
		return SPECIFIER Vector2<T>(-m_y, m_x);
	}

	template<math::math_type::NumericType T>
	SPECIFIER T math::Vector2<T>::AngleFrom(Vector2<T> const& vec2)
	{
		/*
			*	Get the angle between two vectors
			*
			*	Formula:
			*	angle = acos((a dot b) / (magA * magB))
			*
			*	a	 -> VectorA (this)
			*	b	 -> VectorB (other)
			*	magA -> Magnitude of vector A
			*	magB -> Magnitude of vector B
		*/

			// Get the magnitude for both vectors
		const float magnitude1 = Magnitude();
		const float magnitude2 = vec2.Magnitude();

		// Calculate angle
		return acosf(Dot(vec2) / (magnitude1 * magnitude2));
	}

	template<math::math_type::NumericType T>
	SPECIFIER bool math::Vector2<T>::IsUnit(void)
	{
		return SPECIFIER (static_cast<float>(Magnitude()) == 1.0f);
	}

	template<math::math_type::NumericType T>
	SPECIFIER Vector2<T> Vector2<T>::Reflect(Vector2<T> const& vec2)
	{
		// TODO: finish reflect
		return SPECIFIER Vector2<T>();
	}

	template<math::math_type::NumericType T>
	SPECIFIER Vector2<T> Vector2<T>::Project(Vector2<T> const& vec2)
	{
		// TODO: Finish project
		return SPECIFIER Vector2<T>();
	}

	template<math::math_type::NumericType T>
	SPECIFIER void math::Vector2<T>::Translate(Vector2<T> const& vec2)
	{
		*this += vec2;
	}

	template<math::math_type::NumericType T>
	SPECIFIER void Vector2<T>::Rotate(T const& deg)
	{
		const float angleRad = reinterpret_cast<float>(deg) * DEG2RAD;

		// Calculate cos & sin angle value
		const float sinAngle = sinf(angleRad);
		const float cosAngle = cosf(angleRad);

		// Store current x value in order for y rotation calculation to be correct
		const float tmpX = m_x;

		// Calculate rotated vector
		m_x = reinterpret_cast<T>(m_x * cosAngle - m_y * sinAngle);
		m_y = reinterpret_cast<T>(tmpX * sinAngle + m_y * cosAngle);
	}

	template<math::math_type::NumericType T>
	SPECIFIER void Vector2<T>::Scale(Vector2<T> const& vec2)
	{
		*this *= vec2;
	}

	template<math::math_type::NumericType T>
	SPECIFIER math::Vector2<T> math::Vector2<T>::operator+(Vector2<T> const& vec2)
	{
		return SPECIFIER Vector2<T>(
			m_x + vec2.m_x,
			m_y + vec2.m_y
		);
	}

	template<math::math_type::NumericType T>
	SPECIFIER math::Vector2<T> math::Vector2<T>::operator-(Vector2<T> const& vec2)
	{
		return SPECIFIER Vector2<T>(
			m_x - vec2.m_x,
			m_y - vec2.m_y
		);
	}

	template<math::math_type::NumericType T>
	SPECIFIER Vector2<T> Vector2<T>::operator*(Vector2<T> const& vec2)
	{
		return SPECIFIER Vector2<T>(
			m_x * vec2.m_x,
			m_y * vec2.m_y
		);
	}

	template<math::math_type::NumericType T>
	SPECIFIER math::Vector2<T> math::Vector2<T>::operator/(Vector2<T> const& vec2)
	{
		_ASSERT(vec2.m_x != 0);
		_ASSERT(vec2.m_y != 0);

		return SPECIFIER Vector2<T>(
			m_x / vec2.m_x,
			m_y / vec2.m_y
		);
	}

	template<math::math_type::NumericType T>
	SPECIFIER Vector2<T>& Vector2<T>::operator+=(Vector2<T> const& vec2)
	{
		*this = *this + vec2;

		return SPECIFIER *this;
	}
	template<math::math_type::NumericType T>
	SPECIFIER Vector2<T>& Vector2<T>::operator-=(Vector2<T> const& vec2)
	{
		*this = *this - vec2;

		return SPECIFIER *this;
	}

	template<math::math_type::NumericType T>
	SPECIFIER Vector2<T>& Vector2<T>::operator*=(Vector2<T> const& vec2)
	{
		*this = *this * vec2;

		return SPECIFIER *this;
	}

	template<math::math_type::NumericType T>
	SPECIFIER Vector2<T>& Vector2<T>::operator/=(Vector2<T> const& vec2)
	{
		*this = *this / vec2;

		return SPECIFIER * this;
	}

	template<math::math_type::NumericType T>
	SPECIFIER bool Vector2<T>::operator==(Vector2<T> const& vec2)
	{
		// TODO: add epsilon test
		return SPECIFIER bool(false);
	}

	template<math::math_type::NumericType T>
	SPECIFIER T Vector2<T>::operator[](int const& index) const
	{
		_ASSERT(index >= 0 && index <= 1);

		return SPECIFIER reinterpret_cast<const T*>(this)[index];
	}

	template<math::math_type::NumericType T>
	SPECIFIER T& Vector2<T>::operator[](int const& index)
	{
		_ASSERT(index >= 0 && index <= 1);

		return SPECIFIER reinterpret_cast<T*>(this)[index];
	}
}



namespace LibMath = math;