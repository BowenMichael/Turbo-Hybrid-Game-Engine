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
#include <fstream>


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
Uint32 GetTicks();
TurboHybrid::GameObject* player;
TurboHybrid::GameObject* collider;
TurboHybrid::GameObject* background;
const Uint32 MAX_GAME_OBJECTS = 500;
TurboHybrid::GameObject* gameObjects[MAX_GAME_OBJECTS];
Uint32 numOfSpawnedObjects = 0;

struct PosColorVertex
{
    float x;
    float y;
    float z;
    uint32_t abgr;
};

static PosColorVertex cubeVertices[] =
{
    {-1.0f,  1.0f,  1.0f, 0xff000000 },
    { 1.0f,  1.0f,  1.0f, 0xff0000ff },
    {-1.0f, -1.0f,  1.0f, 0xff00ff00 },
    { 1.0f, -1.0f,  1.0f, 0xff00ffff },
    {-1.0f,  1.0f, -1.0f, 0xffff0000 },
    { 1.0f,  1.0f, -1.0f, 0xffff00ff },
    {-1.0f, -1.0f, -1.0f, 0xffffff00 },
    { 1.0f, -1.0f, -1.0f, 0xffffffff },
};

static const uint16_t cubeTriList[] =
{
    2, 1, 0, // 0
    2, 3, 1,
    5, 6, 4, // 2
    7, 6, 5,
    4, 2, 0, // 4
    6, 2, 4,
    3, 5, 1, // 6
    3, 7, 5,
    1, 4, 0, // 8
    1, 5, 4,
    6, 3, 2, // 10
    7, 3, 6,
};


bgfx::ProgramHandle m_program;
void render(EngineState* engine);
bgfx::ShaderHandle loadShader(const char* FILENAME);

bgfx::VertexBufferHandle m_vbh;
bgfx::IndexBufferHandle m_ibh[1];
const uint32_t WIDTH = 640;
const uint32_t HEIGHT = 480;
bgfx::ShaderHandle vsh;
bgfx::ShaderHandle fsh;
bgfx::VertexBufferHandle vbh; 
bgfx::IndexBufferHandle ibh;

int main(int argc, char* argv[])
{
    /*
        System init
    */

    TurboHybrid::System* system = TurboHybrid::System::Create();
    system->Init();

    /*
        SDL init
    */

    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n",
            SDL_GetError());
    }
    else {
        //Create a window
        window = SDL_CreateWindow("TurboHybrid Engine",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            WIDTH, HEIGHT,
            SDL_WINDOW_SHOWN);
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if (window == NULL) {
            printf("Window could not be created! SDL_Error: %s\n",
                SDL_GetError());
        }
    }

    //get window information to pass along to bgfx
    SDL_SysWMinfo wmi;
    SDL_VERSION(&wmi.version);
    if (!SDL_GetWindowWMInfo(window, &wmi)) {
        return 1;
    }

    /*
        BGFX init
    */

    bgfx::Init init;
    init.type = bgfx::RendererType::Count;
    init.platformData.nwh = wmi.info.win.window;
    init.platformData.ndt = NULL;
    init.resolution.width = WIDTH;
    init.resolution.height = HEIGHT;
    init.resolution.reset = BGFX_RESET_VSYNC;
    bgfx::init(init);

    //clear buffers
    bgfx::reset(WIDTH, HEIGHT, BGFX_RESET_VSYNC);
    bgfx::setDebug(BGFX_DEBUG_TEXT /*| BGFX_DEBUG_STATS*/);

    //init view window
    bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x443355FF, 1.0f, 0);
    bgfx::setViewRect(0, 0, 0, uint16_t(WIDTH), uint16_t(HEIGHT));

    //load bufferes
    bgfx::VertexLayout pcvDecl;
    pcvDecl
        .begin()
        .add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
        .add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8, true)
        .end();
    vbh = bgfx::createVertexBuffer(bgfx::makeRef(cubeVertices, sizeof(cubeVertices)), pcvDecl);
    ibh = bgfx::createIndexBuffer(bgfx::makeRef(cubeTriList, sizeof(cubeTriList)));


    //load shaders
    vsh = loadShader("vs_cubes.bin");
    fsh = loadShader("fs_cubes.bin");
    m_program = bgfx::createProgram(vsh, fsh, true);

    bgfx::touch(0);

    /*
        Engine init
    */

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

    TurboHybrid::ComponentSystem::assignCubeBuffers(vbh, ibh, m_program);

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

      SDL_DestroyRenderer(renderer);
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
    bgfx::shutdown();

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

    TurboHybrid::ComponentSystem::GetComponentSystem()->update(engine->frame);

    render(engine);

    engine->stack->clear();

}

void render(EngineState* engine) {
    
    /*
        SDL Render
    */
    SDL_SetRenderDrawColor(engine->renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(engine->renderer);

    TurboHybrid::ComponentSystem::GetComponentSystem()->render(engine->renderer);

    //Prep next frame?
    SDL_RenderPresent(engine->renderer);

    /*
        Set up view projection matrix
    */

    // construct view matrix
    const glm::vec3 at = gameObjects[0]->GetTransform()->GetLocation().Vec3();              // reference point for the center of the scene
    const glm::vec3 eye = { 0.0f, 0.0f, -5.0f };        // location of the eye/camera
    const glm::vec3 up = { 0.0f, 1.0f, 0.0f };          // reference for up vector
    glm::mat4x4 view = glm::lookAt(eye, at, up);        // view matrix is created

    // create projection matrix using a perspective projection
    glm::mat4x4 proj = glm::perspective(80.0f, float(WIDTH) / float(HEIGHT), 0.1f, 100.0f);

    // set view and projection matrix
    bgfx::setViewTransform(0, &view, &proj);

    /*
        Render Cube components
    */

    TurboHybrid::ComponentSystem::GetComponentSystem()->renderCubes(engine->frame);

    /*
        Other mesh rendering
    */

    //render your other mesh

    /*
        Render next frame
    */

    bgfx::frame();


    

}

Uint32 GetTicks()
{
    return SDL_GetTicks();
}

bgfx::ShaderHandle loadShader(const char* FILENAME)
{
    const char* shaderPath = "???";

    switch (bgfx::getRendererType()) {
    case bgfx::RendererType::Noop:
    case bgfx::RendererType::Direct3D9:  shaderPath = "shaders/dx9/";   break;
    case bgfx::RendererType::Direct3D11:
    case bgfx::RendererType::Direct3D12: shaderPath = "shaders/dx11/";  break;
    case bgfx::RendererType::Gnm:        shaderPath = "shaders/pssl/";  break;
    case bgfx::RendererType::Metal:      shaderPath = "shaders/metal/"; break;
    case bgfx::RendererType::OpenGL:     shaderPath = "shaders/glsl/";  break;
    case bgfx::RendererType::OpenGLES:   shaderPath = "shaders/essl/";  break;
    case bgfx::RendererType::Vulkan:     shaderPath = "shaders/spirv/"; break;
    }

    size_t shaderLen = strlen(shaderPath);
    size_t fileLen = strlen(FILENAME);
    char* filePath = (char*)malloc(shaderLen + fileLen);
    memcpy(filePath, shaderPath, shaderLen);
    memcpy(&filePath[shaderLen], FILENAME, fileLen);

    FILE* file = fopen(FILENAME, "rb");
    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    const bgfx::Memory* mem = bgfx::alloc(fileSize + 1);
    fread(mem->data, 1, fileSize, file);
    mem->data[mem->size - 1] = '\0';
    fclose(file);

    return bgfx::createShader(mem);
}