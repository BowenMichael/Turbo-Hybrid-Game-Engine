// THIS IS WINDOWS-ONLY
#define _CRT_SECURE_NO_WARNINGS
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <iostream>
#include <SDL.h>
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
// allocations to be of _CLIENT_BLOCK type
#else
#define DBG_NEW new
#endif

// Add your System.h include file here



int main(int argc, char* argv[])
{
    const int WIDTH = 640;
    const int HEIGHT = 480;
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;

 /*   gpr460::System system;
    system.Init();*/

    int* leak = DBG_NEW int[4096];

    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("SDL2 Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    int x = 0;
    int frame = 0;

    system("pause");

    /*SDL_Event event;
    bool quit = false;
    while (!quit)
    {
        frame++;
        Uint32 frameStart = SDL_GetTicks64();
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                quit = true;
            }

            if (event.type == SDL_KEYDOWN)
            {
                std::cout << "Key pressed!\n";
                if (event.key.keysym.sym == SDLK_k)
                {
                    std::cout << "K pressed!\n";
                    system.ErrorMessage(L"Do not press K!!!");
                    system.LogToErrorFile(L"Error: User pressed 'k'");
                }
                if (event.key.keysym.sym == SDLK_ESCAPE)
                {
                    quit = true;
                }
            }
        }

        x = (SDL_sinf(frame / 10.0f) * 100) + 200;

        SDL_Rect r = {
            x,
            100,
            50,
            50
        };

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderFillRect(renderer, &r);
        SDL_RenderPresent(renderer);

        while (SDL_GetTicks64() - frameStart < 16);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    system.Shutdown();*/
    return 0;
}