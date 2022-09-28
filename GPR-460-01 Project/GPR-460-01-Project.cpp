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
#include "./source/headers/System.h"

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

SDL_Window* window;
SDL_Renderer* renderer;

SDL_Rect rect;

struct EngineState
{
    SDL_Renderer* renderer;
    TurboHybrid::System* system;
    Uint32 frameStart;
    bool quit;
    int frame;
};

void runMainLoop(EngineState* engine);
void frameStep(void* arg);
Uint32 GetTicks();

int main(int argc, char* argv[])
{
    const int WIDTH = 640;
    const int HEIGHT = 480;
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;

    TurboHybrid::System* system = TurboHybrid::System::Create();
    system->Init();

    int* leak = DBG_NEW int[4096];

    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow("SDL2 Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    EngineState engine;
    engine.quit = false;
    engine.renderer = renderer;
    engine.frame = 0;
    engine.frameStart = GetTicks();
    engine.system = system;

    runMainLoop(&engine);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    system->Shutdown();
    return 0;
}

void runMainLoop(EngineState* engine)
{
    #ifdef __EMSCRIPTEN__
        emscripten_set_main_loop_arg(frameStep, engine, 0, true);
    #else
  
    while (!engine->quit)
    {
        Uint32 now = GetTicks();
        if (now - engine->frameStart >= 16)
        {
            frameStep(engine);
        }
    }
    #endif
}

void frameStep(void* arg)
{
    EngineState* engine = (EngineState*)arg;
    SDL_Event event;

    Uint32 now = GetTicks();

    engine->frame++;
    engine->frameStart = now;

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
            }
            if (event.key.keysym.sym == SDLK_ESCAPE)
            {
                engine->quit = true;
            }
        }
    }

    int x = (SDL_sinf(engine->frame / 100.0f) * 100.0f) + 200;

    SDL_Rect r = {
        x,
        100,
        50,
        50
    };

    SDL_SetRenderDrawColor(engine->renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);

    SDL_RenderClear(engine->renderer);
    SDL_SetRenderDrawColor(engine->renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(engine->renderer, &r);
    SDL_RenderPresent(engine->renderer);
}

Uint32 GetTicks()
{
    return SDL_GetTicks();
}
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
//            }
//        }
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