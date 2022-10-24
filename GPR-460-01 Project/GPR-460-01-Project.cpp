// THIS IS WINDOWS-ONLY
#ifdef _WIN32
#define _CRT_SECURE_NO_WARNINGS
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif // ! __EMSCRIPTEN__

#include <stdlib.h>
#include <iostream>
#include <SDL.h>

// Add your System.h include file here
#include "headers/System.h"

//inculde game files
#include "headers/GameObject.h"

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif
#include "headers/Components/RectangleCollider.h"
#include "headers/Components/RectangleRenderer.h"
#include "headers/Components/Component_System.h"


#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
// allocations to be of _CLIENT_BLOCK type
#else
#define DBG_NEW new
#endif

struct EngineState
{
    SDL_Rect viewport{};
    SDL_Renderer* renderer;
    SDL_Window* window;
    TurboHybrid::System* system;

    Uint32 frameStart;
    bool quit;
    int frame;

};

void runMainLoop(EngineState* engine);
void frameStep(void* arg);
Uint32 GetTicks();
TurboHybrid::GameObject* player;
TurboHybrid::GameObject* collider;
TurboHybrid::GameObject* background;

int main(int argc, char* argv[])
{
    const int WIDTH = 640;
    const int HEIGHT = 480;
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;

    TurboHybrid::System* system = TurboHybrid::System::Create();
    system->Init();

    TurboHybrid::ComponentSystem::InitInstance();
    TurboHybrid::ComponentSystem* world = TurboHybrid::ComponentSystem::GetComponentSystem();


   

    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow("SDL2 Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    EngineState engine;
    engine.quit = false;
    engine.renderer = renderer;
    engine.frame = 0;
    engine.frameStart = GetTicks();
    engine.system = system;
    engine.window = window;
    engine.viewport = {};

    /*
        Player init
    */
    TurboHybrid::RectangleCollider* cPlayer = world->allocateRectangleCollider();
    cPlayer->SetOnCollision([]() {std::cout << "Player Collided\n"; });
    player = DBG_NEW TurboHybrid::GameObject(
        world->allocateTransform(), 
        world->allocateRectangleRenderer(), 
        cPlayer, 
        world->allocatePlayerController(), 
        world->allocateCollorChanger()
    );



    /*
        Collider init
    */
    TurboHybrid::RectangleRenderer* colliderRect = world->allocateRectangleRenderer();
    colliderRect->SetColor(Color(1, 0, 0, 1));
    TurboHybrid::Transform* colliderTransform = world->allocateTransform();
    colliderTransform->SetLocation(110, 0, 0);
    collider = DBG_NEW TurboHybrid::GameObject(colliderTransform, colliderRect, world->allocateRectangleCollider(), nullptr, world->allocateCollorChanger());
    //Old init
    /*collider->CreateRenderer();
    TurboHybrid::RectangleRenderer* colliderRect = collider->CreateRenderer();
    colliderRect->SetColor(Color(1, 0, 0, 1));
    collider->CreateColliderColorChanger();
    TurboHybrid::RectangleCollider* cCollider = collider->CreateCollider();
    cCollider->SetOnCollision([]() {std::cout << "Collider Collided\n"; });
    collider->GetTransform()->SetLocation(110, 0, 0);*/

    /*
        Background init
    */
    //Get Screen Size
    SDL_GetDisplayBounds(0, &engine.viewport);    
    SDL_GetWindowSize(engine.window, &engine.viewport.w, &engine.viewport.h);
    //Set up rectangle the size of the screen
    TurboHybrid::RectangleRenderer* backgroundRect = world->allocateRectangleRenderer();
    backgroundRect->SetColor(Color(.25f, .25f, .25f, 1));
    backgroundRect->SetRect(Rect(engine.viewport.w, engine.viewport.h));
    //set up transform in center of the screen
    TurboHybrid::Transform* backgroundTransform = world->allocateTransform();
    backgroundTransform->SetLocation(engine.viewport.w * -.5f, engine.viewport.h * -.5f, 0);
    background = DBG_NEW TurboHybrid::GameObject(backgroundTransform, backgroundRect);

    runMainLoop(&engine);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    delete player;
    delete collider;
    delete background;

    TurboHybrid::ComponentSystem::DeleteInstance();

    system->Shutdown();
    delete system;


    
    return 0;
}

void runMainLoop(EngineState* engine)
{
    while (!engine->quit)
    {
        Uint32 now = GetTicks();
        if (now - engine->frameStart >= 16)
        {
            
#ifdef __EMSCRIPTEN__
            emscripten_set_main_loop_arg(frameStep, (void*)engine, 0, true);
#else
            frameStep(engine);
#endif
        }

    }
}

//void run_main_loop() {
//#ifdef __EMSCRIPTEN__
//    emscripten_set_main_loop([]() { handle_events(); }, 0, true);
//#else
//    while (handle_events())
//        ;
//#endif
//}

void frameStep(void* arg)
{
    EngineState* engine = (EngineState*)arg;
    SDL_Event event;

    Uint32 now = GetTicks();

    engine->frame++;
    engine->frameStart = now;

    TurboHybrid::ComponentSystem::GetComponentSystem()->update(0);

    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            engine->quit = true;
        }

        if (event.type == SDL_KEYDOWN)
        {
            std::cout << "Key pressed!\n";
            if (event.key.keysym.sym == SDLK_k)
            {
                std::cout << "K pressed!\n";

                // TODO: Add calls to ErrorMessage and LogToErrorFile here
                engine->system->ShowError(TurboHybrid::ERROR_K);
                engine->system->LogToErrorFile(TurboHybrid::LOG_ERROR_K);
            }
            if (event.key.keysym.sym == SDLK_ESCAPE)
            {
                engine->quit = true;
            }
        }
    }

    int x = (SDL_sinf(engine->frame / 100.0f) * 100.0f) + 200.0;

    //clear screen
    SDL_SetRenderDrawColor(engine->renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(engine->renderer);

    TurboHybrid::ComponentSystem::GetComponentSystem()->render(engine->renderer);

    //Prep next frame?
    SDL_RenderPresent(engine->renderer);
}

Uint32 GetTicks()
{
    return SDL_GetTicks();
}

//SDL_Window* window;
//SDL_Renderer* renderer;
//
//SDL_Rect rect;
//
//TurboHybrid::System* system;
//
//void redraw() {
//    SDL_SetRenderDrawColor(renderer, /* RGBA: black */ 0x00, 0x00, 0x00, 0xFF);
//    SDL_RenderClear(renderer);
//    SDL_SetRenderDrawColor(renderer, /* RGBA: green */ 0x00, 0x80, 0x00, 0xFF);
//    SDL_RenderFillRect(renderer, &rect);
//    SDL_RenderPresent(renderer);
//}
//
//uint32_t ticksForNextKeyDown = 0;
//
//
//
//bool handle_events() {
//    SDL_Event event;
//
//    uint32_t ticksNow = SDL_GetTicks();
//    if (SDL_TICKS_PASSED(ticksNow, ticksForNextKeyDown)) {
//        SDL_PollEvent(&event);
//        if (event.type == SDL_QUIT) {
//            return false;
//        }
//        if (event.type == SDL_KEYDOWN) {
//            switch (event.key.keysym.sym) {
//            case SDLK_UP:
//                rect.y -= 1;
//                break;
//            case SDLK_DOWN:
//                rect.y += 1;
//                break;
//            case SDLK_RIGHT:
//                rect.x += 1;
//                break;
//            case SDLK_LEFT:
//                rect.x -= 1;
//                break;
//            case SDLK_k:
//                system->ShowError(TurboHybrid::ERROR_K);
//                system->LogToErrorFile(TurboHybrid::LOG_ERROR_K);
//                break;
//            }
//        }
//
//
//        // Throttle keydown events for 10ms.
//        ticksForNextKeyDown = ticksNow + 10;
//        redraw();
//    }
//    return true;
//}
//
//void run_main_loop() {
//#ifdef __EMSCRIPTEN__
//    emscripten_set_main_loop([]() { handle_events(); }, 0, true);
//#else
//    while (handle_events())
//        ;
//#endif
//}
//
//int main(int argc, char* argv[]) {
//    rect.x = 10;
//    rect.y = 10;
//    rect.w = 150;
//    rect.h = 100;
//    SDL_Init(SDL_INIT_VIDEO);
//
//    SDL_CreateWindowAndRenderer(300, 300, 0, &window, &renderer);
//
//    redraw();
//    run_main_loop();
//
//    SDL_DestroyRenderer(renderer);
//    SDL_DestroyWindow(window);
//
//    SDL_Quit();
//    return 0;
//}

//int main(int argc, char* argv[])
//{
//    const int WIDTH = 640;
//    const int HEIGHT = 480;
//    SDL_Window* window = NULL;
//    SDL_Renderer* renderer = NULL;
//
//    TurboHybrid::System* system = TurboHybrid::System::Create();
//    system->Init();
//
//    int* leak = DBG_NEW int[4096];
//
//    SDL_Init(SDL_INIT_VIDEO);
//    window = SDL_CreateWindow("SDL2 Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
//    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
//
//    int x = 0;
//    int frame = 0;
//
//    //system("pause");
//
//    SDL_Event event;
//    bool quit = false;
//    while (!quit)
//    {
//        frame++;
//        Uint32 frameStart = SDL_GetTicks64();
//        while (SDL_PollEvent(&event))
//        {
//            if (event.type == SDL_QUIT)
//            {
//                quit = true;
//            }
//
//            if (event.type == SDL_KEYDOWN)
//            {
//                std::cout << "Key pressed!\n";
//                if (event.key.keysym.sym == SDLK_k)
//                {
//                    std::cout << "K pressed!\n";
//                    system->ShowError(TurboHybrid::ERROR_K);
//                    system->LogToErrorFile(TurboHybrid::LOG_ERROR_K);
//                }
//                if (event.key.keysym.sym == SDLK_ESCAPE)
//                {
//                    quit = true;
//                }
//            }
//        }
//
//        x = (SDL_sinf(frame / 10.0f) * 100) + 200;
//
//        SDL_Rect r = {
//            x,
//            100,
//            50,
//            50
//        };
//
//        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
//        SDL_RenderClear(renderer);
//        SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
//        SDL_RenderFillRect(renderer, &r);
//        SDL_RenderPresent(renderer);
//
//        while (SDL_GetTicks64() - frameStart < 16);
//    }
//
//    SDL_DestroyRenderer(renderer);
//    SDL_DestroyWindow(window);
//    SDL_Quit();
//
//    system->Shutdown();
//    return 0;
//}

