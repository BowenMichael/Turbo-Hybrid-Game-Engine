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
#include <SDL_syswm.h>
#include <assert.h>

// Add your System.h include file here
#include "headers/System.h"

//inculde game files
#include "headers/GameObject.h"

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif
#include "headers/Components/RectangleCollider.h"
#include "headers/Components/RectangleRenderer.h"
#include <vector>
#include <unordered_map>
#include "headers/Components/Component_System.h"
#include <headers/Allocators/StackAllocator.h>
#include <headers/Components/Transform.h>
#include "FileParser.h"
#include <bgfx/include/bgfx/platform.h>
#include "bgfx/include/bgfx/bgfx.h"

// math
#include <vec3.hpp>
#include <mat4x4.hpp>
#include <gtc/matrix_transform.hpp>

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
    TurboHybrid::StackAllocator* stack;

    Uint32 frameStart;
    bool quit;
    int frame;

};

void runMainLoop(EngineState* engine);
void frameStep(void* arg);
void RenderGame(EngineState* engine)
Uint32 GetTicks();
TurboHybrid::GameObject* player;
TurboHybrid::GameObject* collider;
TurboHybrid::GameObject* background;
const Uint32 MAX_GAME_OBJECTS = 500;
const uint32_t WIDTH = 640;
const uint32_t HEIGHT = 480;

TurboHybrid::GameObject* gameObjects[MAX_GAME_OBJECTS];
Uint32 numOfSpawnedObjects = 0;

int main(int argc, char* argv[])
{
    WIDTH = 640;
    HEIGHT = 480;
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;

    TurboHybrid::System* system = TurboHybrid::System::Create();
    system->Init();

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n",
            SDL_GetError());
    }
    else {
        //Create a window
        window = SDL_CreateWindow("BGFX Tutorial",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            WIDTH, HEIGHT,
            SDL_WINDOW_SHOWN);
        if (window == NULL) {
            printf("Window could not be created! SDL_Error: %s\n",
                SDL_GetError());
        }
    }

    SDL_SysWMinfo wmi;
    SDL_VERSION(&wmi.version);
    if (!SDL_GetWindowWMInfo(window, &wmi)) {
        return 1;
    }

    bgfx::Init init;
    init.type = bgfx::RendererType::Count;
    init.platformData.nwh = wmi.info.win.window;
    init.platformData.ndt = NULL;
    init.resolution.width = WIDTH;
    init.resolution.height = HEIGHT;
    init.resolution.reset = BGFX_RESET_VSYNC;
    bgfx::init(init);

    bgfx::reset(WIDTH, HEIGHT, BGFX_RESET_VSYNC);

    bgfx::setDebug(BGFX_DEBUG_TEXT /*| BGFX_DEBUG_STATS*/);

    bgfx::setViewRect(0, 0, 0, uint16_t(WIDTH), uint16_t(HEIGHT));

    bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x443355FF, 1.0f, 0);
    bgfx::touch(0);

    char* buffer = DBG_NEW char[1024 * 1024 * 32];
    TurboHybrid::StackAllocator* stack = DBG_NEW TurboHybrid::StackAllocator(1024 * 1024 * 32, buffer);

    TurboHybrid::ComponentSystem::InitInstance();
    TurboHybrid::ComponentSystem* world = TurboHybrid::ComponentSystem::GetComponentSystem();

    EngineState engine;
    engine.quit = false;
    engine.renderer = renderer;
    engine.frame = 0;
    engine.frameStart = GetTicks();
    engine.system = system;
    engine.window = window;
    engine.viewport = {};
    engine.stack = stack;

    /*
        init from file
    */
    Turbohybrid::FileParser* parser = DBG_NEW Turbohybrid::FileParser(L"data.json");

    int GameObjectsFromFile = (int)parser->GetNumOfGameObjects();
    TurboHybrid::GameObject* newGameObjects;

    for (int i = 0; i < GameObjectsFromFile && i < GameObjectsFromFile; i++) {
        ////check what components it has
        gameObjects[i] = DBG_NEW TurboHybrid::GameObject();

        //get gameobject components list
        parser->DeserializeGameobject(gameObjects[i], i, world);
        numOfSpawnedObjects++;

    }

    runMainLoop(&engine);

    SDL_DestroyWindow(window);
    SDL_Quit();

    delete player;
    delete collider;
    delete background;
    for (int i = 0; i < MAX_GAME_OBJECTS; i++) {
        if (gameObjects[i] != nullptr) {
            delete gameObjects[i];
        }
    }

    delete parser;
    
    stack->clear();
    delete stack;

    TurboHybrid::ComponentSystem::DeleteInstance();

    system->Shutdown();
    delete system;

    bgfx::shutdown();
    

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
            if (event.key.keysym.sym == SDLK_ESCAPE)
            {
                engine->quit = true;
            }
        }
    }

  
    //clear screen
    
    //SDL_SetRenderDrawColor(engine->renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    //SDL_RenderClear(engine->renderer);

    //TurboHybrid::ComponentSystem::GetComponentSystem()->render(engine->renderer);
    
    //Prep next frame?
    //SDL_RenderPresent(engine->renderer);

    // do rendering
    bgfx::touch(0);

    const glm::vec3 at = { 0.0f, 0.0f,  0.0f };
    const glm::vec3 eye = { 0.0f, 0.0f, -5.0f };
    const glm::vec3 up = { 0.0f, 1.0f, 0.0f };
    glm::mat4x4 view = glm::lookAt(eye, at, up);
    glm::mat4x4 proj = glm::perspective(60.0f, float(WIDTH) / float(HEIGHT), 0.1f, 100.0f);
    bgfx::setViewTransform(0, view, proj);

    bgfx::setVertexBuffer(0, vbh);
    bgfx::setIndexBuffer(ibh);

    bgfx::frame();

    // end rendering

    engine->stack->clear();

}

Uint32 GetTicks()
{
    return SDL_GetTicks();
}