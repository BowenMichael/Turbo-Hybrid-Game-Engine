#pragma once
#include "headers/Components/ColliderColorChanger.h"
#include "headers/GameObject.h"
#include "headers/Components/RectangleCollider.h"
#include "headers/Components/RectangleRenderer.h"

//TurboHybrid::ColliderColorChanger::ColliderColorChanger(GameObject* gameobject, const Color& color)
//	:
//	collidedColor(color),
//	originalColor(color),
//	gameobject(gameobject)
//{
//}
//
//void TurboHybrid::ColliderColorChanger::Update(const float& deltatime)
//{
//	if (gameobject) {
//		if (gameobject->GetCollider()->GetIsColliding()) {
//			gameobject->GetRenderer()->SetColor(collidedColor);
//		}
//		else {
//			gameobject->GetRenderer()->SetColor(originalColor);
//		}
//	}
//}
//
//TurboHybrid::ColliderColorChanger::ColliderColorChanger() :
//	collidedColor(Color(0.0f, 1.0f, 0.0f, 1.0f)),
//	originalColor(Color()),
//	gameobject(nullptr)
//
//{
//}
