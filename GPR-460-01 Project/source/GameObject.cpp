#include "./headers/GameObject.h"
#include <iostream>
#include "../source/headers/System_Common.h"
#include "../source/headers/Components/ColliderColorChanger.h"
#include "../source/headers/Components/PlayerController.h"
#include "../source/headers/Components/RectangleCollider.h"
#include "../source/headers/Components/RectangleRenderer.h"

TurboHybrid::GameObject::GameObject() : 
	transform(),
	renderer(nullptr),
	collider(nullptr),
	player(nullptr),
	colorChanger(nullptr)
{
	
}

TurboHybrid::GameObject::~GameObject()
{
	delete renderer;
	delete collider;
	delete player;
	delete colorChanger;
}

TurboHybrid::RectangleRenderer* TurboHybrid::GameObject::CreateRenderer()
{
	delete renderer;
	renderer = DBG_NEW RectangleRenderer();
	return renderer;
}

TurboHybrid::RectangleCollider* TurboHybrid::GameObject::CreateCollider()
{
	delete collider;
	collider = DBG_NEW RectangleCollider(this);
	return collider;
}

TurboHybrid::PlayerController* TurboHybrid::GameObject::CreatePlayerController()
{
	delete player;
	player = DBG_NEW TurboHybrid::PlayerController(this);
	return player;
}

TurboHybrid::ColliderColorChanger* TurboHybrid::GameObject::CreateColliderColorChanger()
{
	delete colorChanger;
	colorChanger = DBG_NEW TurboHybrid::ColliderColorChanger(this, Color(0,1,0,1));
	return colorChanger;
}



void TurboHybrid::GameObject::CheckCollision(GameObject* other)
{
	if(collider && other->GetCollider())
		collider->CheckCollision(other->GetCollider());
}

void TurboHybrid::GameObject::Draw(SDL_Renderer* sdlRenderer)
{
	Rect rect = renderer->GetRect();
	Color color = renderer->GetColor();
	SDL_Rect r = {
		static_cast<int>(transform.GetLocation().x + rect.width * .5f),
		static_cast<int>(transform.GetLocation().y + rect.height * .5f),
		static_cast<int>(rect.width),
		static_cast<int>(rect.height)
	};

	SDL_SetRenderDrawColor(sdlRenderer, (Uint8)(color.r * 255), (Uint8)(color.g * 255), (Uint8)(color.b * 255), (Uint8)(color.a * SDL_ALPHA_OPAQUE));
	SDL_RenderDrawRect(sdlRenderer, &r);
	SDL_RenderFillRect(sdlRenderer, &r);
}

void TurboHybrid::GameObject::Update(const float& deltatime)
{
	if(player)
		player->update(deltatime);

	if (colorChanger)
		colorChanger->Update(deltatime);
}
