#pragma once

#include "VariableType.hpp"
#include "Macros.h"
#include "Arithmetic.h"

#include <cmath>

/*
*	================= Matrix 2D =================
*	Column / Row major
*
*	Constructor
*	- void				DONE
*	- Scalar			DONE
*	- X, Y, Z, W		DONE
*
*	Static Functions
*	- Zero				DONE
*	- One				DONE
*	
*	Functions
*	- Identity			DONE
*	- Transpose			DONE
*	- Determinant		DONE
*	- Minor				DONE
*	- Cofactor			DONE
*	- Adjugate			DONE
*	- Inverse			
*
*	Operators
*	- Addition			DONE
*	- Subtraction		DONE
*	- Multiplication	
*		->	Scalar		DONE
*		->	Matrix		DONE
*	=================================================
*/

/*
*	================= Matrix Config =================
*
*	The 2x2 matrix class supports both column & row major.
*	By default the class uses row major however this can be
*	overwritten by defining the 'COLUMN_MAJOR' macro.
*
*	Example:
*	#define COLUMN_MAJOR
*	=================================================
*/

namespace math
{
	// Forward decleration for matrix3 minor function
	template<math::math_type::NumericType T>
	class Matrix3;

	template<math::math_type::NumericType T>
	class Matrix2
	{
	public:
							Matrix2(void);
							Matrix2(T value);
							Matrix2(T x, T y, T z, T w);

							~Matrix2(void) = default;

		static Matrix2<T>	Zero(void);
		static Matrix2<T>	One(void);
		static Matrix2<T>	Identity(T scalar);

		Matrix2<T>&			GetMatrix2(Matrix3<T> matrix, int row, int column);
		Matrix2<T>&			Transpose(void);
		T					Determinant(void);
		Matrix2<T>&			Minor(void);
		Matrix2<T>&			Cofactor(void);
		Matrix2<T>&			Adjugate(void);
		Matrix2<T>&			Inverse(void);

		Matrix2<T>			operator+(Matrix2<T> const& matrix);
		Matrix2<T>			operator-(Matrix2<T> const& matrix);
		Matrix2<T>			operator*(Matrix2<T> const& matrix);
		Matrix2<T>			operator*(T const& scalar);
		Matrix2<T>&			operator+=(Matrix2<T> const& matrix);
		Matrix2<T>&			operator-=(Matrix2<T> const& matrix);
		Matrix2<T>&			operator*=(Matrix2<T> const& matrix);
		Matrix2<T>&			operator*=(T const& scalar);

		bool				operator==(Matrix2<T> const& matrix) const noexcept;
		bool				operator!=(Matrix2<T> const& matrix) const noexcept;

	private:
		T m_matrix[2][2];
	};

	template<math::math_type::NumericType T>
	inline math::Matrix2<T>::Matrix2(void)
	{
		m_matrix =
		{
			1, 0,
			0, 1
		};
	}

	template<math::math_type::NumericType T>
	inline math::Matrix2<T>::Matrix2(T value)
	{
		m_matrix =
		{
			value, 0,
			0, value
		};
	}

	template<math::math_type::NumericType T>
	inline math::Matrix2<T>::Matrix2(T x, T y, T z, T w)
	{
#ifdef COLUMN_MAJOR
		m_matrix =
		{
			x, z,
			y, w
		};
#else
		m_matrix =
		{
			x, y,
			z, w
		};
#endif
	}

	template<math::math_type::NumericType T>
	inline Matrix2<T> Matrix2<T>::Zero(void)
	{
		return Matrix2<T>(0, 0, 0, 0);
	}

	template<math::math_type::NumericType T>
	inline Matrix2<T> Matrix2<T>::One(void)
	{
		return Matrix2<T>(1, 1, 1, 1);
	}

	template<math::math_type::NumericType T>
	inline Matrix2<T> Matrix2<T>::Identity(T scalar)
	{
		return Matrix2<T>(scalar, 0, 0, scalar);
	}

	template<math::math_type::NumericType T>
	inline Matrix2<T>& Matrix2<T>::GetMatrix2(Matrix3<T> matrix, int row, int column)
	{
		int iOffset = 0;
		int jOffset = 0;

		for (int i = 0; i < 3; ++i)
		{
			if (i == row)
			{
				jOffset = -1;
				continue;
			}

			iOffset = 0;

			for (int j = 0; j < 3; ++j)
			{
				if (j == column)
				{
					iOffset = -1;
					continue;
				}

				m_matrix[i + iOffset][j + jOffset] = matrix.m_matrix[i][j];
			}
		}

		return *this;
	}

	template<math::math_type::NumericType T>
	inline math::Matrix2<T>& Matrix2<T>::Transpose(void)
	{
		T tmp = m_matrix[0][1];

		return Matrix2<T>(m_matrix[0][0], m_matrix[1][0], tmp, m_matrix[1][1]);
	}

	template<math::math_type::NumericType T>
	inline T Matrix2<T>::Determinant(void)
	{
		/*
		*	Determinant of 2x2 matrix
		*
		*	|a b|
		*	|c d|
		*
		*	formula:
		*	Determinant = (a * d) - (b * c)
		*/

		return (m_matrix[0][0] * m_matrix[1][1]) - (m_matrix[0][1] * m_matrix[1][0]);
	}

	template<math::math_type::NumericType T>
	inline Matrix2<T>& Matrix2<T>::Minor(void)
	{
		Matrix2<T> tmp(*this);

		m_matrix =
		{
			tmp.m_matrix[1][1], tmp.m_matrix[1][0],
			tmp.m_matrix[0][1], tmp.m_matrix[0][0]
		};

		return *this;
	}

	template<math::math_type::NumericType T>
	inline Matrix2<T>& Matrix2<T>::Cofactor(void)
	{
		this->Minor();

		m_matrix =
		{
			 m_matrix[0][0], -m_matrix[0][1],
			-m_matrix[1][0],  m_matrix[1][1]
		};

		return *this;
	}

	template<math::math_type::NumericType T>
	inline Matrix2<T>& Matrix2<T>::Adjugate(void)
	{
		this->Cofactor();
		this->Transpose();

		return *this;
	}

	template<math::math_type::NumericType T>
	inline Matrix2<T>& Matrix2<T>::Inverse(void)
	{
		Matrix2<T> tmp(*this);
		Matrix2<T> result;

		T determinant = Determinant;

		if (determinant == 0)
			return result;

		*this = Adjugate() / determinant;

		return result;
	}

	template<math::math_type::NumericType T>
	inline Matrix2<T> Matrix2<T>::operator+(Matrix2<T> const& matrix)
	{
		return Matrix2<T>(
			m_matrix[0][0] + matrix.m_matrix[0][0], m_matrix[0][1] + matrix.m_matrix[0][1],
			m_matrix[1][0] + matrix.m_matrix[1][0], m_matrix[1][1] + matrix.m_matrix[1][1]
		);
	}

	template<math::math_type::NumericType T>
	inline Matrix2<T> Matrix2<T>::operator-(Matrix2<T> const& matrix)
	{
		return Matrix2<T>(
			m_matrix[0][0] - matrix.m_matrix[0][0], m_matrix[0][1] - matrix.m_matrix[0][1],
			m_matrix[1][0] - matrix.m_matrix[1][0], m_matrix[1][1] - matrix.m_matrix[1][1]
		);
	}

	template<math::math_type::NumericType T>
	inline Matrix2<T> Matrix2<T>::operator*(Matrix2<T> const& matrix)
	{
		return Matrix2<T>(
			m_matrix[0][0] * matrix.m_matrix[0][0] + m_matrix[1][0] * matrix.m_matrix[0][1],
			m_matrix[0][1] * matrix.m_matrix[0][0] + m_matrix[1][1] * matrix.m_matrix[0][1],
			m_matrix[0][0] * matrix.m_matrix[1][0] + m_matrix[1][0] * matrix.m_matrix[1][1],
			m_matrix[0][1] * matrix.m_matrix[1][0] + m_matrix[1][1] * matrix.m_matrix[1][1]
		);
	}

	template<math::math_type::NumericType T>
	inline Matrix2<T> Matrix2<T>::operator*(T const& scalar)
	{
		return Matrix2<T>(
			m_matrix[0][0] * scalar, m_matrix[0][1] * scalar,
			m_matrix[1][0] * scalar, m_matrix[1][1] * scalar
		);
	}

	template<math::math_type::NumericType T>
	inline Matrix2<T>& Matrix2<T>::operator+=(Matrix2<T> const& matrix)
	{
		*this = *this + matrix;

		return *this;
	}

	template<math::math_type::NumericType T>
	inline Matrix2<T>& Matrix2<T>::operator-=(Matrix2<T> const& matrix)
	{
		*this = *this - matrix;

		return *this;
	}

	template<math::math_type::NumericType T>
	inline Matrix2<T>& Matrix2<T>::operator*=(Matrix2<T> const& matrix)
	{
		*this = *this * matrix;

		return *this;
	}

	template<math::math_type::NumericType T>
	inline Matrix2<T>& Matrix2<T>::operator*=(T const& scalar)
	{
		*this = *this * scalar;

		return *this;
	}

	template<math::math_type::NumericType T>
	inline bool Matrix2<T>::operator==(Matrix2<T> const& matrix) const noexcept
	{
		return
			AlmostEqual(m_matrix[0][0], matrix.m_matrix[0][0]) &&
			AlmostEqual(m_matrix[0][1], matrix.m_matrix[0][1]) &&
			AlmostEqual(m_matrix[1][0], matrix.m_matrix[1][0]) &&
			AlmostEqual(m_matrix[1][1], matrix.m_matrix[1][1]);
	}

	template<math::math_type::NumericType T>
	inline bool Matrix2<T>::operator!=(Matrix2<T> const& matrix) const noexcept
	{
		return
			!(	AlmostEqual(m_matrix[0][0], matrix.m_matrix[0][0]) &&
				AlmostEqual(m_matrix[0][1], matrix.m_matrix[0][1]) &&
				AlmostEqual(m_matrix[1][0], matrix.m_matrix[1][0]) &&
				AlmostEqual(m_matrix[1][1], matrix.m_matrix[1][1]));
	}
}

namespace LibMath = math;