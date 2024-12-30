#pragma once

#include "VariableType.hpp"
#include "Macros.h"
#include "Arithmetic.h"
#include "angle/Radians.h"
#include "matrix/Matrix3.h"
#include "vector/Vector3.h"

#include <cmath>

/*
*	Matrix4
*
*	Constructor
*	- Void						DONE
*	- Scalar					DONE
*	- array						DONE
*
*	Functions
*	- Determinant				DONE
*	- Identity					DONE
*	- Transpose					DONE
*	- Minor						DONE
*	- Cofactor					DONE
*	- Adjugate					DONE
*	- Inverse					DONE
*
*	Transformation
*	- Scale						DONE
*	- Translation				DONE
*	- Rotation					
*
*	Operators
*	- Addition					DONE
*	- Subtraction				DONE
*	- Multiplication			DONE
*	- Equality					DONE
*	- Inverse equality			DONE
*	- Assignment with 1D array	DONE
*	- Assignment with 2D array	DONE
*/

namespace math
{
	template<math::math_type::NumericType T>
	class Matrix4
	{
	public:
								Matrix4(void);
								Matrix4(T scalar);
								Matrix4(T* arr);

								~Matrix4(void) = default;

				T				Determinant(void);
		static	Matrix4<T>		Identity(void);
				Matrix4<T>&		Transpose(void);
				Matrix4<T>&		Minor(void);
				Matrix4<T>&		Cofactor(void);
				Matrix4<T>&		Adjugate(void);
				Matrix4<T>&		Inverse(void);

				Matrix4<T>&		Scale(T scale);
				Matrix4<T>&		Translate(Vector3<T> const& vec3, bool rowMajor = false);
				Matrix4<T>&		Translate(T x, T y, T z, bool rowMajor = false);

				Matrix4<T>&		operator=(const T[16] arr);
				Matrix4<T>&		operator=(const T[][4] arr);
				Matrix4<T>		operator+(Matrix4<T> const& matrix);
				Matrix4<T>		operator-(Matrix4<T> const& matrix);
				Matrix4<T>		operator*(Matrix4<T> const& matrix);
				Matrix4<T>		operator*(T scalar);
				Matrix4<T>&		operator+=(Matrix4<T> const& matrix);
				Matrix4<T>&		operator-=(Matrix4<T> const& matrix);
				Matrix4<T>&		operator*=(Matrix4<T> const& matrix);
				Matrix4<T>&		operator*=(T scalar);

				bool			operator==(Matrix4<T> const& matrix);
				bool			operator!=(Matrix4<T> const& matrix);

		T m_matrix[4][4];
	};

	template<math::math_type::NumericType T>
	inline Matrix4<T>::Matrix4(void)
	{
		m_matrix =
		{
			{1, 0, 0, 0},
			{0, 1, 0, 0},
			{0, 0, 1, 0},
			{0, 0, 0, 1}
		}
	}

	template<math::math_type::NumericType T>
	inline Matrix4<T>::Matrix4(T scalar)
	{
		m_matrix =
		{
			{scalar, 0, 0, 0},
			{0, scalar, 0, 0},
			{0, 0, scalar, 0},
			{0, 0, 0, scalar}
		}
	}

	template<math::math_type::NumericType T>
	inline Matrix4<T>::Matrix4(T* arr)
	{
		m_matrix =
		{
			{arr[0][0], arr[0][1], arr[0][2], arr[0][3]},
			{arr[1][0], arr[1][1], arr[1][2], arr[1][3]},
			{arr[2][0], arr[2][1], arr[2][2], arr[2][3]},
			{arr[3][0], arr[3][1], arr[3][2], arr[3][3]}
		}
	}

	template<math::math_type::NumericType T>
	inline T Matrix4<T>::Determinant(void)
	{
		float determinant = 0.0f;

		for (int i = 0; i < 4; ++i)
		{
			// Create 3x3 matrix
			Matrix3<T> minor;

			// Iterate through 3x3 matrix
			for (int j = 0; j < 3; ++j)
			{
				for (int k = 0; k < 3; ++k)
				{
					// Initialize minor matrix's values & skip column containing coefficient
					minor.m_matrix[j][k] = (k < i) ? matrix.m_matrix[j + 1][k] : matrix.m_matrix[j + 1][k + 1];
				}
			}

			// Get the determinant of 3x3 matrix
			float minorDeterminant = minor.Determinant(minor);

			// Add or subtract minor's determinant depending if 'i' is even or odd
			determinant += (i % 2 == 0) ? matrix.m_matrix[0][i] * minorDeterminant : -matrix.m_matrix[0][i] * minorDeterminant;
		}

		return determinant;
	}

	template<math::math_type::NumericType T>
	inline Matrix4<T> Matrix4<T>::Identity(void)
	{
		return Matrix4<T>();
	}

	template<math::math_type::NumericType T>
	inline Matrix4<T>& Matrix4<T>::Transpose(void)
	{
		T tmp[4][4] = m_matrix;

		m_matrix =
		{
			{tmp[0][0], tmp[1][0], tmp[2][0], tmp[3][0]},
			{tmp[0][1], tmp[1][1], tmp[2][1], tmp[3][1]},
			{tmp[0][2], tmp[1][2], tmp[2][2], tmp[3][2]},
			{tmp[0][3], tmp[1][3], tmp[2][3], tmp[3][3]}
		};

		return *this;
	}

	template<math::math_type::NumericType T>
	inline Matrix4<T>& Matrix4<T>::Minor(void)
	{
		/*
		*	Minor: set each value in the given 4x4 matrix equal to the determinant
		*	of a 3x3 matrix
		*/

		Matrix3<T> matrix3;
		Matrix4<T> tmp(*this);

		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				matrix3.GetMatrix3(tmp, i, j);

				T determinant = matrix3.Determinant();

				m_matrix[i][j] = determinant;
			}
		}

		return *this;
	}

	template<math::math_type::NumericType T>
	inline Matrix4<T>& Matrix4<T>::Cofactor(void)
	{
		/*
		*	The cofactor of a matrix is the determinant when eliminating
		*	a row & column from the matrix & multiplying by -1 or +1
		*/

		this->Minor();

		m_matrix =
		{
			{ m_matrix[0][0], -m_matrix[0][1],  m_matrix[0][2], -m_matrix[0][3]},
			{-m_matrix[1][0],  m_matrix[1][1], -m_matrix[1][2],  m_matrix[1][3]},
			{ m_matrix[2][0], -m_matrix[2][1],  m_matrix[2][2], -m_matrix[2][3]},
			{-m_matrix[3][0],  m_matrix[3][1], -m_matrix[3][2],  m_matrix[3][3]}
		};

		return *this;
	}

	template<math::math_type::NumericType T>
	inline Matrix4<T>& Matrix4<T>::Adjugate(void)
	{
		// An adjugate matrix is the transpose of the cofactor of a matrix
		this->Cofactor();
		this->Transpose();

		return *this;
	}

	template<math::math_type::NumericType T>
	inline Matrix4<T>& Matrix4<T>::Inverse(void)
	{
		/*
		*	The inverse of a matrix is equal to the adjugate of the matrix
		*	divided by the determinant
		*/
		
		T determinant = this->Determinant();

		if (determinant == 0)
			return Matrix4<T>::Identity();

		*this = *this->Adjugate() / determinant;

		return *this;
	}

	template<math::math_type::NumericType T>
	inline Matrix4<T>& Matrix4<T>::Scale(T scale)
	{
		m_matrix[0][0] *= scale;
		m_matrix[1][1] *= scale;
		m_matrix[2][2] *= scale;

		return *this;
	}

	template<math::math_type::NumericType T>
	inline Matrix4<T>& Matrix4<T>::Translate(Vector3<T> const& vec3, bool rowMajor)
	{
		if (rowMajor)
		{
			m_matrix[0][3] += vec3[0];
			m_matrix[1][3] += vec3[1];
			m_matrix[2][3] += vec3[2];
		}
		else
		{
			m_matrix[3][0] += vec3[0];
			m_matrix[3][1] += vec3[1];
			m_matrix[3][2] += vec3[2];
		}

		return *this;
	}

	template<math::math_type::NumericType T>
	inline Matrix4<T>& Matrix4<T>::Translate(T x, T y, T z, bool rowMajor)
	{
		if (rowMajor)
		{
			m_matrix[0][3] += x;
			m_matrix[1][3] += y;
			m_matrix[2][3] += z;
		}
		else
		{
			m_matrix[3][0] += x;
			m_matrix[3][1] += y;
			m_matrix[3][2] += z;
		}

		return *this;
	}

	template<math::math_type::NumericType T>
	inline Matrix4<T>& math::Matrix4<T>::operator=(const T arr[16])
	{
		m_matrix =
		{
			{arr[0], arr[1], arr[2], arr[3]},
			{arr[4], arr[5], arr[6], arr[7]},
			{arr[8], arr[9], arr[10], arr[11]},
			{arr[12], arr[13], arr[14], arr[15]}
		};

		return *this;
	}

	template<math::math_type::NumericType T>
	inline Matrix4<T>& Matrix4<T>::operator=(const T arr[][4])
	{
		m_matrix =
		{
			{arr[0][0], arr[0][1], arr[0][2], arr[0][3]},
			{arr[1][0], arr[1][1], arr[1][2], arr[1][3]},
			{arr[2][0], arr[2][1], arr[2][2], arr[2][3]},
			{arr[3][0], arr[3][1], arr[3][2], arr[3][3]}
		};

		return *this;
	}

	template<math::math_type::NumericType T>
	inline Matrix4<T> Matrix4<T>::operator+(Matrix4<T> const& matrix)
	{
		Matrix4<T> result;

		result.m_matrix =
		{
			{m_matrix[0][0] + matrix.m_matrix[0][0], m_matrix[0][1] + matrix.m_matrix[0][1], m_matrix[0][2] + matrix.m_matrix[0][2], m_matrix[0][3] + matrix.m_matrix[0][3]},
			{m_matrix[1][0] + matrix.m_matrix[1][0], m_matrix[1][1] + matrix.m_matrix[1][1], m_matrix[1][2] + matrix.m_matrix[1][2], m_matrix[1][3] + matrix.m_matrix[1][3]},
			{m_matrix[2][0] + matrix.m_matrix[2][0], m_matrix[2][1] + matrix.m_matrix[2][1], m_matrix[2][2] + matrix.m_matrix[2][2], m_matrix[2][3] + matrix.m_matrix[2][3]},
			{m_matrix[3][0] + matrix.m_matrix[3][0], m_matrix[3][1] + matrix.m_matrix[3][1], m_matrix[3][2] + matrix.m_matrix[3][2], m_matrix[3][3] + matrix.m_matrix[3][3]}
		};

		return result;
	}

	template<math::math_type::NumericType T>
	inline Matrix4<T> Matrix4<T>::operator-(Matrix4<T> const& matrix)
	{
		Matrix4<T> result;

		result.m_matrix =
		{
			{m_matrix[0][0] - matrix.m_matrix[0][0], m_matrix[0][1] - matrix.m_matrix[0][1], m_matrix[0][2] - matrix.m_matrix[0][2], m_matrix[0][3] - matrix.m_matrix[0][3]},
			{m_matrix[1][0] - matrix.m_matrix[1][0], m_matrix[1][1] - matrix.m_matrix[1][1], m_matrix[1][2] - matrix.m_matrix[1][2], m_matrix[1][3] - matrix.m_matrix[1][3]},
			{m_matrix[2][0] - matrix.m_matrix[2][0], m_matrix[2][1] - matrix.m_matrix[2][1], m_matrix[2][2] - matrix.m_matrix[2][2], m_matrix[2][3] - matrix.m_matrix[2][3]},
			{m_matrix[3][0] - matrix.m_matrix[3][0], m_matrix[3][1] - matrix.m_matrix[3][1], m_matrix[3][2] - matrix.m_matrix[3][2], m_matrix[3][3] - matrix.m_matrix[3][3]}
		};

		return result;
	}

	template<math::math_type::NumericType T>
	inline Matrix4<T> Matrix4<T>::operator*(Matrix4<T> const& matrix)
	{
		// Create a null 4x4 matrix
		Matrix4<T> result(0.0f);

		// Iterate through matrix to set the result matrix equal to the result of the 2 matrices multiplied
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				for (int k = 0; k < 4; ++k)
				{
					// Add the value obtained from multiplying the 2 matrices row * column
					result.m_matrix[i][j] += m_matrix[i][k] * matrix.m_matrix[k][j];
				}
			}
		}

		return result;
	}

	template<math::math_type::NumericType T>
	inline Matrix4<T> Matrix4<T>::operator*(T scalar)
	{
		Matrix4<T> result;

		result.m_matrix =
		{
			{m_matrix[0][0] * scalar, m_matrix[0][1] * scalar, m_matrix[0][2] * scalar, m_matrix[0][3] * scalar},
			{m_matrix[1][0] * scalar, m_matrix[1][1] * scalar, m_matrix[1][2] * scalar, m_matrix[1][3] * scalar},
			{m_matrix[2][0] * scalar, m_matrix[2][1] * scalar, m_matrix[2][2] * scalar, m_matrix[2][3] * scalar},
			{m_matrix[3][0] * scalar, m_matrix[3][1] * scalar, m_matrix[3][2] * scalar, m_matrix[3][3] * scalar}
		};

		return result;
	}

	template<math::math_type::NumericType T>
	inline Matrix4<T>& Matrix4<T>::operator+=(Matrix4<T> const& matrix)
	{
		*this = *this + matrix;

		return *this;
	}

	template<math::math_type::NumericType T>
	inline Matrix4<T>& Matrix4<T>::operator-=(Matrix4<T> const& matrix)
	{
		*this = *this - matrix;

		return *this;
	}

	template<math::math_type::NumericType T>
	inline Matrix4<T>& Matrix4<T>::operator*=(Matrix4<T> const& matrix)
	{
		*this = *this * matrix;

		return *this;
	}

	template<math::math_type::NumericType T>
	inline Matrix4<T>& Matrix4<T>::operator*=(T scalar)
	{
		*this = *this * scalar;

		return *this;
	}

	template<math::math_type::NumericType T>
	inline bool Matrix4<T>::operator==(Matrix4<T> const& matrix)
	{
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				if (!AlmostEqual(m_matrix[i][j], matrix.m_matrix[i][j]))
					return false;
			}
		}

		return true;
	}

	template<math::math_type::NumericType T>
	inline bool Matrix4<T>::operator!=(Matrix4<T> const& matrix)
	{
		return !(*this == matrix);
	}
}

namespace LibMath = math;