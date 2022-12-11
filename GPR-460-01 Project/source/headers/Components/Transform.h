#pragma once
#include "headers/Util/Vector3.h"
#include "headers/System_Common.h"

namespace TurboHybrid {
	
	class GameObject;
	class ComponentSystem;
	class Transform
	{
	public:

		Transform();
		Transform(const float& x, const float& y, const float& z);

		static enum {kCompID = 'TRAN' };
		static void CreateComponent(TurboHybrid::GameObject* gm, TurboHybrid::ComponentSystem* allocator);
		void load(const Vector3& position);

		Vector3 GetLocation();
		Vector3 SetLocation(const float& x, const float& y, const float& z);

		/// <summary>
		/// Adds direction to location. doesn't normalize dir
		/// </summary>
		/// <param name="dir"></param>
		void TranslateRect(const Vector3& dir);
	protected:
		Vector3 location;
		Vector3 rotation;
		Vector3 size;
	};
}


