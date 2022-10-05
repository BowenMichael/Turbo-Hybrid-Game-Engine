#pragma once
#include "../source/headers/Util/Vector3.h"

namespace TurboHybrid {
	
	class Transform
	{
	public:
		Transform();
		Transform(const float& x, const float& y, const float& z);

		Vector3 GetLocation();
		Vector3 SetLocation(const float& x, const float& y, const float& z);
	protected:
		Vector3 location;
	};
}


