#include "headers/GameObject.h"
#include <iostream>
#include "headers/System_Common.h"
#include "headers/Components/ColliderColorChanger.h"
#include "headers/Components/PlayerController.h"
#include "headers/Components/RectangleCollider.h"
#include "headers/Components/RectangleRenderer.h"
#include "headers/Components/Transform.h"


TurboHybrid::GameObject::GameObject() : 
	mTransform(nullptr),
	mRenderer(nullptr),
	mCollider(nullptr),
	mPlayer(nullptr),
	mColorChanger(nullptr),
	mCubeRenderer(nullptr)
{
	
}

TurboHybrid::GameObject::GameObject(Transform* transform)
	:mTransform(transform),
	mRenderer(nullptr),
	mCollider(nullptr),
	mPlayer(nullptr),
	mColorChanger(nullptr),
	mCubeRenderer(nullptr)
{
}

TurboHybrid::GameObject::GameObject(Transform* transform, RectangleRenderer* rectRend, RectangleCollider* rectCol, PlayerController* plc, ColliderColorChanger* colorChanger)
	: 
	mTransform(transform),
	mRenderer(rectRend),
	mCollider(rectCol),
	mPlayer(plc),
	mColorChanger(colorChanger)
{
	if(mCollider)
		mCollider->gameObject = this;
	if(this->mColorChanger)
		this->mColorChanger->gameObject = this;
	if(mPlayer)
		mPlayer->gameObject = this;
	if (mRenderer)
		mRenderer->gameObject = this;
}

TurboHybrid::GameObject::~GameObject()
{
	/*delete renderer;
	delete collider;
	delete player;
	delete colorChanger;*/
}

//TurboHybrid::RectangleRenderer* TurboHybrid::GameObject::CreateRenderer()
//{
//	delete renderer;
//	renderer = DBG_NEW RectangleRenderer();
//	return renderer;
//}
//
//TurboHybrid::RectangleCollider* TurboHybrid::GameObject::CreateCollider()
//{
//	delete collider;
//	collider = DBG_NEW RectangleCollider(this);
//	return collider;
//}
//
//TurboHybrid::PlayerController* TurboHybrid::GameObject::CreatePlayerController()
//{
//	delete player;
//	player = DBG_NEW TurboHybrid::PlayerController(this);
//	return player;
//}
//
//TurboHybrid::ColliderColorChanger* TurboHybrid::GameObject::CreateColliderColorChanger()
//{
//	delete colorChanger;
//	colorChanger = DBG_NEW TurboHybrid::ColliderColorChanger(this, Color(0,1,0,1));
//	return colorChanger;
//}



bool TurboHybrid::GameObject::CheckCollision(GameObject* other)
{
	if(mCollider && other->GetCollider())
		return mCollider->CheckCollision(other->GetCollider());

	return false;
}

void TurboHybrid::GameObject::OnCollisionWithOther(RectangleCollider* other)
{
	if(mColorChanger)
		mRenderer->SetColor(mColorChanger->getCollidedColor());
	//std::cout << "Collision" << '\n';
}

void TurboHybrid::GameObject::Draw(SDL_Renderer* sdlRenderer)
{
	if (mCubeRenderer != nullptr) {

	}
	else {
		Rect rect = mRenderer->GetRect();
		Color color = mRenderer->GetColor();
		SDL_Rect r = {
			static_cast<int>(mTransform->GetLocation().x + rect.width * .5f),
			static_cast<int>(mTransform->GetLocation().y + rect.height * .5f),
			static_cast<int>(rect.width),
			static_cast<int>(rect.height)
		};

		SDL_SetRenderDrawColor(sdlRenderer, (Uint8)(color.r * 255), (Uint8)(color.g * 255), (Uint8)(color.b * 255), (Uint8)(color.a * SDL_ALPHA_OPAQUE));
		SDL_RenderDrawRect(sdlRenderer, &r);
		SDL_RenderFillRect(sdlRenderer, &r);
	}

}

//void TurboHybrid::GameObject::Update(const float& deltatime)
//{
//	//if(player)
//	//	player->update(deltatime);
//
//	//if (colorChanger)
//	//	colorChanger->Update(deltatime);
//}
