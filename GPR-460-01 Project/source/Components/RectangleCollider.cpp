#include "headers/Components/RectangleCollider.h"
#include "headers/GameObject.h"
#include "headers/Components/RectangleRenderer.h"
#include "headers/Components/Transform.h"

TurboHybrid::RectangleCollider::RectangleCollider(GameObject* gm)
	: gameObject(gm),
	isColliding(false),
	OnCollision(nullptr)
{
}

TurboHybrid::RectangleCollider::RectangleCollider() :
	gameObject(nullptr),
	isColliding(false),
	OnCollision(nullptr)
{
}

void TurboHybrid::RectangleCollider::Update(const float& deltaTime)
{
}

bool TurboHybrid::RectangleCollider::CheckCollision(RectangleCollider* other)
{
	Vector3 position = gameObject->GetTransform()->GetLocation();
	Rect rect = gameObject->GetRenderer()->GetRect();
	Vector3 extentsPosition = Vector3(position.x + rect.width, position.y + rect.height, position.z);
	
	Vector3 otherPosition = other->gameObject->GetTransform()->GetLocation();
	Rect otherRect = gameObject->GetRenderer()->GetRect();
	Vector3 otherExtentsPosition = Vector3(otherPosition.x + otherRect.width, otherPosition.y + otherRect.height, position.z);

	if (   extentsPosition.x >= otherPosition.x + otherRect.width * .5f
		&& position.x + rect.width * .5f <= otherExtentsPosition.x
		&& extentsPosition.y >= otherPosition.y + otherRect.height * .5f
		&& position.y + rect.height * .5f <= otherExtentsPosition.y

		) 
	{	
		isColliding = true;
		return true;
	}
	isColliding = false;
	return false;
}

void TurboHybrid::RectangleCollider::SetOnCollision(void (*onCollisionCallback)())
{
	OnCollision = onCollisionCallback;
}

void TurboHybrid::RectangleCollider::OnCollisionWithOther(RectangleCollider* other)
{
	gameObject->OnCollisionWithOther(other);
}

