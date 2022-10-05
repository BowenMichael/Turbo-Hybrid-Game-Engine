#include "../headers/Components/Transform.h"

TurboHybrid::Transform::Transform()
{
	Transform(0, 0, 0);
}

TurboHybrid::Transform::Transform(const float& x, const float& y, const float& z)
{
	SetLocation(x, y, z);
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
