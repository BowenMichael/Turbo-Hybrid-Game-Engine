#include "../source/headers/Components/RectangleCollider.h"
#include "../source/headers/GameObject.h"
#include "../source/headers/Components/RectangleRenderer.h"

TurboHybrid::RectangleCollider::RectangleCollider(GameObject* gm)
	: gameObject(gm)
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

	if (   extentsPosition.x >= otherPosition.x 
		&& position.x <= otherExtentsPosition.x
		&& extentsPosition.y >= otherPosition.y
		&& position.y <= otherExtentsPosition.y

		) {
		//colliding		
		OnCollision();
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
