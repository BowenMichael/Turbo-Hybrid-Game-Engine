#include "../source/headers/Components/ColliderColorChanger.h"
#include "../source/headers/GameObject.h"
#include "../source/headers/Components/RectangleCollider.h"
#include "../source/headers/Components/RectangleRenderer.h"

TurboHybrid::ColliderColorChanger::ColliderColorChanger(GameObject* gameobject, const Color& color)
	:
	gameobject(gameobject),
	collidedColor(color)
{
}

void TurboHybrid::ColliderColorChanger::Update(const float& deltatime)
{
	if (gameobject->GetCollider()->GetIsColliding()) {
		gameobject->GetRenderer()->SetColor(collidedColor);
	}
	else {
		gameobject->GetRenderer()->SetColor(Color());
	}
}
