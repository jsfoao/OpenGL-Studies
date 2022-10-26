#pragma once
#include "matrix.h"

namespace Nata
{
	Matrix4::Matrix4()
	{
		for (size_t i = 0; i < 16; i++)
		{
			elements[i] = 0.f;
		}
	}

	Matrix4::Matrix4(float diagonal)
	{
		for (size_t i = 0; i < 16; i++)
		{
			elements[i] = 0.f;
		}

		elements[0 + 0 * 4] = diagonal;
		elements[1 + 1 * 4] = diagonal;
		elements[2 + 2 * 4] = diagonal;
		elements[3 + 3 * 4] = diagonal;
	}

	Matrix4 Matrix4::Identity()
	{
		return Matrix4(1.0f);
	}

	Matrix4& Matrix4::Multiply(const Matrix4& other)
	{
		for (size_t y = 0; y < 4; y++)
		{
			for (size_t x = 0; x < 4; x++)
			{
				float sum = 0.f;
				for (size_t e = 0; e < 4; e++)
				{
					sum += elements[x + e * 4] * other.elements[e + y * 4];
				}
				elements[x + y * 4] = sum;
			}
		}
		return *this;
	}

	Matrix4& Matrix4::operator*=(const Matrix4& other)
	{
		return Multiply(other);
	}

	Matrix4 operator*(Matrix4 left, const Matrix4& right)
	{
		return left.Multiply(right);
	}

	Matrix4 Matrix4::Ortographic(float left, float right, float bottom, float top, float near, float far)
	{
		Matrix4 result(1.f);

		result.elements[0 + 0 * 4] = 2.0f / (right - left);
		result.elements[1 + 1 * 4] = 2.0f / (top - bottom);
		result.elements[2 + 2 * 4] = 2.0f / (near - far);

		result.elements[0 + 3 * 4] = (left + right) / (left - right);
		result.elements[1 + 3 * 4] = (bottom + top) / (bottom - top);
		result.elements[2 + 3 * 4] = (far + near) / (far - near);

		return result;
	}

	Matrix4 Matrix4::Perspective(float fov, float aspectRatio, float near, float far)
	{
		Matrix4 result(1.f);

		float q = 1.f / tan(ToRadians(0.5f * fov));
		float a = q / aspectRatio;

		float b = (near + far) / (near - far);
		float c = (2.f * near * far) / (near - far);

		result.elements[0 + 0 * 4] = a;
		result.elements[1 + 1 * 4] = q;
		result.elements[2 + 2 * 4] = b;
		result.elements[3 + 2 * 4] = -1.f;
		result.elements[2 + 3 * 4] = c;

		return result;
	}

	Matrix4 Matrix4::Translation(const Vector3& translation)
	{
		Matrix4 result(1.f);

		result.elements[0 + 3 * 4] = translation.x;
		result.elements[1 + 3 * 4] = translation.y;
		result.elements[2 + 3 * 4] = translation.z;

		return result;
	}

	Matrix4 Matrix4::Rotation(float angle, const Vector3& axis)
	{
		Matrix4 result(1.f);
		float r = ToRadians(angle);
		float c = cos(r);
		float s = sin(r);
		float omc = 1.f - c;

		float x = axis.x;
		float y = axis.y;
		float z = axis.z;

		result.elements[0 + 0 * 4] = x * omc + c;
		result.elements[1 + 0 * 4] = y * x * omc + z * s;
		result.elements[2 + 0 * 4] = x * z * omc - y * s;

		result.elements[0 + 1 * 4] = x * y * omc - z * s;
		result.elements[1 + 1 * 4] = y * omc + c;
		result.elements[2 + 1 * 4] = y * z * omc + x * s;

		result.elements[0 + 2 * 4] = x * z * omc + y * s;
		result.elements[1 + 2 * 4] = y * z * omc - x * s;
		result.elements[2 + 2 * 4] = z * omc + c;

		return result;
	}

	Matrix4 Matrix4::Scale(const Vector3& scale)
	{
		Matrix4 result(1.f);

		result.elements[0 + 0 * 4] = scale.x;
		result.elements[1 + 1 * 4] = scale.y;
		result.elements[2 + 2 * 4] = scale.z;

		return result;
	}

}
