#include "./headers/GameObject.h"
#include <iostream>

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
	renderer = new RectangleRenderer();
	return renderer;
}

void TurboHybrid::GameObject::Draw(SDL_Renderer* sdlRenderer)
{
	Rect rect = renderer->GetRect();
	Color color = renderer->GetColor();
	SDL_Rect r = {
		transform.GetLocation().x + rect.width * .5f,
		transform.GetLocation().y + rect.height * .5f,
		rect.width,
		rect.height
	};

	SDL_SetRenderDrawColor(sdlRenderer, (Uint8)(color.r * 255), (Uint8)(color.r * 255), (Uint8)(color.r * 255), (Uint8)(color.r * SDL_ALPHA_OPAQUE));
	SDL_RenderDrawRect(sdlRenderer, &r);
	SDL_RenderFillRect(sdlRenderer, &r);
}

void TurboHybrid::GameObject::Update()
{
	const Uint8* keystate = SDL_GetKeyboardState(NULL);

	if(keystate[SDL_SCANCODE_W])
		std::cout << "w pressed\n";
}
