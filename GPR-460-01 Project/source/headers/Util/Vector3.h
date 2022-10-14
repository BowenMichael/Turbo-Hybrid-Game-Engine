#pragma once

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

		float x;
		float y;
		float z;
	};
}