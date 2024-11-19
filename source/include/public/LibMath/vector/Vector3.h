#pragma once

#include "VariableType.hpp"
#include "Arithmetic.h"

#include <cmath>
#include <limits>

#ifndef SPECIFIER
#define SPECIFIER inline constexpr
#endif // !SPECIFIER


/*
*	------- Vector3 -------
*	Static Functions:
*	- Up			DONE
*	- Down			DONE
*	- Left			DONE
*	- Right			DONE
*	- Forward		DONE
*	- Backward		DONE
*	- Zero			DONE
*	- One			DONE
*
*	Functions:
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
*	- Compare	(epsilon test)		DONE
*	- Index		(index operator)	DONE
*
*	To Do:
*	- Unit tests - code is currently untested
*/

namespace math
{
	template<math::math_type::NumericType T>
	class Vector3
	{
	public:
		// Constructors
		SPECIFIER				Vector3(void) = default;
		SPECIFIER				Vector3(T const& scalar);
		SPECIFIER				Vector3(T const& x, T const& y, T const& z);

								~Vector3(void) = default;

		static Vector3			Up(void) noexcept;
		static Vector3			Down(void) noexcept;
		static Vector3			Left(void) noexcept;
		static Vector3			Right(void) noexcept;
		static Vector3			Forward(void) noexcept;
		static Vector3			BackWard(void) noexcept;
		static Vector3			Zero(void) noexcept;
		static Vector3			One(void) noexcept;

		SPECIFIER Vector3<T>	Cross(Vector3<T> const& vec3);
		SPECIFIER T				Dot(Vector3<T> const& vec3);
		SPECIFIER T				Magnitude(void);
		SPECIFIER Vector3<T>	Normalize(void);
		SPECIFIER Vector3<T>	Normal(void);
		SPECIFIER T				AngleFrom(Vector3<T> vec3);
		SPECIFIER bool			IsUnit(void);
		SPECIFIER Vector3<T>	Reflect(Vector3<T> const& vec3);
		SPECIFIER Vector3<T>	Project(Vector3<T> const& vec3);

		SPECIFIER void			Translate(Vector3<T> const& vec3);
		SPECIFIER void			Rotate(T const& angle);
		SPECIFIER void			Scale(Vector3<T> const& vec3);

		// Operators
		Vector3					operator+(Vector3 const& vec3);
		Vector3					operator-(Vector3 const& vec3);
		Vector3					operator*(Vector3 const& vec3);
		Vector3					operator/(Vector3 const& vec3);
		Vector3&				operator+=(Vector3 const& vec3);
		Vector3&				operator-=(Vector3 const& vec3);
		Vector3&				operator*=(Vector3 const& vec3);
		Vector3&				operator/=(Vector3 const& vec3);
		bool					operator==(Vector3 const& vec3);
		T&						operator[](unsigned int const& index);
		T						operator[](unsigned int const& index) const;
	private:
		T m_x;
		T m_y;
		T m_z;
	};

	template<math::math_type::NumericType T>
	SPECIFIER Vector3<T>::Vector3(T const& scalar)
		: m_x(scalar), m_y(scalar), m_z(scalar)
	{
	}

	template<math::math_type::NumericType T>
	SPECIFIER Vector3<T>::Vector3(T const& x, T const& y, T const& z)
		: m_x(x), m_y(y), m_z(z)
	{
	}

	template<math::math_type::NumericType T>
	inline Vector3<T> Vector3<T>::Up(void) noexcept
	{
		return Vector3<T>(0.0f, 1.0f, 0.0f);
	}

	template<math::math_type::NumericType T>
	inline Vector3<T> Vector3<T>::Down(void) noexcept
	{
		return Vector3<T>(0.0f, -1.0f, 0.0f);
	}

	template<math::math_type::NumericType T>
	inline Vector3<T> Vector3<T>::Left(void) noexcept
	{
		return Vector3<T>(-1.0f, 0.0f, 0.0f);
	}

	template<math::math_type::NumericType T>
	inline Vector3<T> Vector3<T>::Right(void) noexcept
	{
		return Vector3<T>(1.0f, 0.0f, 0.0f);
	}

	template<math::math_type::NumericType T>
	inline Vector3<T> Vector3<T>::Forward(void) noexcept
	{
		return Vector3<T>(0.0f, 0.0f, 1.0f);
	}

	template<math::math_type::NumericType T>
	inline Vector3<T> Vector3<T>::BackWard(void) noexcept
	{
		return Vector3<T>(0.0f, 0.0f, -1.0f);
	}

	template<math::math_type::NumericType T>
	inline Vector3<T> Vector3<T>::Zero(void) noexcept
	{
		return Vector3<T>(0.0f, 0.0f, 0.0f);
	}

	template<math::math_type::NumericType T>
	inline Vector3<T> Vector3<T>::One(void) noexcept
	{
		return Vector3<T>(1.0f, 1.0f, 1.0f);
	}

	template<math::math_type::NumericType T>
	SPECIFIER Vector3<T> Vector3<T>::Cross(Vector3<T> const& vec3)
	{
		return Vector3<T>
		(
			(m_z * vec3.m_x) - (m_x * vec3.m_z),
			(m_y * vec3.m_z) - (m_z * vec3.m_y),
			(m_x * vec3.m_y) - (m_y * vec3.m_x)
		);
	}

	template<math::math_type::NumericType T>
	SPECIFIER T Vector3<T>::Dot(Vector3<T> const& vec3)
	{
		// sqrt(x^2 + y^2 + z^2)
		return reinterpret_cast<T>(std::sqrt((m_x * vec3.m_x) + (m_y * vec3.m_y) + (m_z * vec3.m_z)));
	}

	template<math::math_type::NumericType T>
	SPECIFIER T Vector3<T>::Magnitude(void)
	{
		return Dot<T>(*this);
	}

	template<math::math_type::NumericType T>
	SPECIFIER Vector3<T> Vector3<T>::Normalize(void)
	{
		const T denom = Magnitude();

		return Vector3<T>(
			m_x * denom,
			m_y * denom,
			m_z * denom
		);
	}

	template<math::math_type::NumericType T>
	SPECIFIER Vector3<T> Vector3<T>::Normal(void)
	{
		// TODO: finish normal function
		return Vector3<T>();
	}

	template<math::math_type::NumericType T>
	SPECIFIER T Vector3<T>::AngleFrom(Vector3<T> vec3)
	{
		return T();
	}

	template<math::math_type::NumericType T>
	SPECIFIER bool Vector3<T>::IsUnit(void)
	{
		return (Magnitude<float>() == 1.0f);
	}

	template<math::math_type::NumericType T>
	SPECIFIER Vector3<T> Vector3<T>::Reflect(Vector3<T> const& vec3)
	{
		return Vector3<T>();
	}

	template<math::math_type::NumericType T>
	SPECIFIER Vector3<T> Vector3<T>::Project(Vector3<T> const& vec3)
	{
		return Vector3<T>();
	}

	template<math::math_type::NumericType T>
	SPECIFIER void Vector3<T>::Translate(Vector3<T> const& vec3)
	{
		return void();
	}

	template<math::math_type::NumericType T>
	SPECIFIER void Vector3<T>::Rotate(T const& angle)
	{
		return void();
	}

	template<math::math_type::NumericType T>
	SPECIFIER void Vector3<T>::Scale(Vector3<T> const& vec3)
	{
		return void();
	}

	template<math::math_type::NumericType T>
	inline Vector3<T> Vector3<T>::operator+(Vector3 const& vec3)
	{
		return Vector3(
			m_x + vec3.m_x,
			m_y + vec3.m_y,
			m_z + vec3.m_z
		);
	}

	template<math::math_type::NumericType T>
	inline Vector3<T> Vector3<T>::operator-(Vector3 const& vec3)
	{
		return Vector3(
			m_x - vec3.m_x,
			m_y - vec3.m_y,
			m_z - vec3.m_z
		);
	}

	template<math::math_type::NumericType T>
	inline Vector3<T> Vector3<T>::operator*(Vector3 const& vec3)
	{
		return Vector3(
			m_x * vec3.m_x,
			m_y * vec3.m_y,
			m_z * vec3.m_z
		);
	}

	template<math::math_type::NumericType T>
	inline Vector3<T> Vector3<T>::operator/(Vector3 const& vec3)
	{
		_ASSERT(vec3.m_x != 0.0f);
		_ASSERT(vec3.m_y != 0.0f);
		_ASSERT(vec3.m_z != 0.0f);

		return Vector3(
			m_x / vec3.m_x,
			m_y / vec3.m_y,
			m_z / vec3.m_z
		);
	}

	template<math::math_type::NumericType T>
	inline Vector3<T>& Vector3<T>::operator+=(Vector3 const& vec3)
	{
		*this = *this + vec3;

		return *this;
	}

	template<math::math_type::NumericType T>
	inline Vector3<T>& Vector3<T>::operator-=(Vector3 const& vec3)
	{
		*this = *this - vec3;

		return *this;
	}

	template<math::math_type::NumericType T>
	inline Vector3<T>& Vector3<T>::operator*=(Vector3 const& vec3)
	{
		*this = *this * vec3;

		return *this;
	}

	template<math::math_type::NumericType T>
	inline Vector3<T>& Vector3<T>::operator/=(Vector3 const& vec3)
	{
		*this = *this / vec3;

		return *this;
	}

	template<math::math_type::NumericType T>
	inline bool Vector3<T>::operator==(Vector3 const& vec3)
	{
		return
			math::AlmostEqual(m_x, vec2.m_x) &&
			math::AlmostEqual(m_y, vec2.m_y) &&
			math::AlmostEqual(m_z, vec2.m_z);
	}

	template<math::math_type::NumericType T>
	inline T& Vector3<T>::operator[](unsigned int const& index)
	{
		_ASSERT(index >= 0 && index <= 1);

		return reinterpret_cast<T*>(this)[index];
	}

	template<math::math_type::NumericType T>
	inline T Vector3<T>::operator[](unsigned int const& index) const
	{
		_ASSERT(index >= 0 && index <= 1);

		return reinterpret_cast<T*>(this)[index];
	}
}

namespace LibMath = math;