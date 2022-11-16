#include "headers/Components/Transform.h"
#include <headers/GameObject.h>
#include <headers/Components/Component_System.h>

TurboHybrid::Transform::Transform()
{
	Transform(0, 0, 0);
}

TurboHybrid::Transform::Transform(const float& x, const float& y, const float& z)
{
	SetLocation(x, y, z);
}

void TurboHybrid::Transform::CreateComponent(TurboHybrid::GameObject* gm, TurboHybrid::ComponentSystem* allocator)
{
	gm->SetTransform(allocator->allocateTransform());
}


void TurboHybrid::Transform::load(const TurboHybrid::Vector3& position)
{
	location = position;
}

TurboHybrid::Vector3 TurboHybrid::Transform::GetLocation()
{
	return location;
}

TurboHybrid::Vector3 TurboHybrid::Transform::SetLocation(const float& x, const float& y, const float& z)
{
	location.x = x;
	location.y = y;
	location.z = z;
	return location;
}

void TurboHybrid::Transform::TranslateRect(const Vector3& dir)
{
	location += dir;
}
