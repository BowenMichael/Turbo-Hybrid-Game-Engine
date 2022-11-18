#pragma once
#include "headers/Components/ColliderColorChanger.h"
#include "headers/GameObject.h"
#include "headers/Components/RectangleCollider.h"
#include "headers/Components/RectangleRenderer.h"
#include "headers/Components/Component_System.h"

#include <assert.h>


TurboHybrid::ColliderColorChanger::ColliderColorChanger(GameObject* gameobject, const Color& color)
	:
	_collidedColor(color),
	_originalColor(color),
	gameObject(gameobject)
{
}

void TurboHybrid::ColliderColorChanger::CreateComponent(TurboHybrid::GameObject* gm, TurboHybrid::ComponentSystem* allocator)
{
	ColliderColorChanger* tmp = allocator->allocateCollorChanger();
	tmp->gameObject = gm;
	gm->SetColliderColorChanger(tmp);
}

void TurboHybrid::ColliderColorChanger::load(const Color& collidedColor)
{
	assert(gameObject->GetRenderer() != nullptr);
	setOriginalColor(gameObject->GetRenderer()->GetColor());
	setCollidedColor(collidedColor);	
}

void TurboHybrid::ColliderColorChanger::Update(const float& deltatime)
{
	if (gameObject) {
		gameObject->GetRenderer()->SetColor(_originalColor);
		/*if (gameobject->GetCollider()->GetIsColliding()) {
			gameobject->GetRenderer()->SetColor(collidedColor);
		}
		else {
			
		}*/
	}
}

TurboHybrid::ColliderColorChanger::ColliderColorChanger() :
	_collidedColor(Color(0.0f, 1.0f, 0.0f, 1.0f)),
	_originalColor(Color()),
	gameObject(nullptr)

{
}	
