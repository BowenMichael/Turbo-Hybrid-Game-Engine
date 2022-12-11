#pragma once
// math
#include <vec3.hpp>
#include <mat4x4.hpp>
#include <gtc/matrix_transform.hpp>

namespace TurboHybrid {
	struct Vector3 {
		Vector3()
			:
			x(0),
			y(0),
			z(0)
		{
		}

		Vector3(const float& x, const float& y, const float& z)
			:x(x),
			y(y),
			z(z)
		{
		}

		Vector3& operator+=(const Vector3& rhs) {
			this->x += rhs.x;
			this->y += rhs.y;
			this->z += rhs.z;
			return *this;
		}

		Vector3& operator*(const float& rhs) {
			this->x *= rhs;
			this->y *= rhs;
			this->z *= rhs;
			return *this;
		}

		glm::vec3 Vec3() {
			return glm::vec3(x, y, z);
		}

		float x;
		float y;
		float z;
	};
}