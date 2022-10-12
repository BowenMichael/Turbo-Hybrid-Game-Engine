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

		/// <summary>
		/// Adds direction to location. doesn't normalize dir
		/// </summary>
		/// <param name="dir"></param>
		void TranslateRect(const Vector3& dir);
	protected:
		Vector3 location;
	};
}


