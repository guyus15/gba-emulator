#include <stdio.h>

#include <SDL2/SDL.h>

#define SCREEN_WIDTH  240
#define SCREEN_HEIGHT 160
#define REFRESH_RATE  60

typedef struct
{
    SDL_Window *window;
    SDL_Renderer *renderer;
} SDLapp;

SDLapp app;

int main(int argc, char *argv[])
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        printf("There has been an error initialising SDL.\n%s\n", SDL_GetError());
        return -1;
    }

    app.window = SDL_CreateWindow(
                    "Game Boy Advance Emulator",
                    SDL_WINDOWPOS_UNDEFINED,
                    SDL_WINDOWPOS_UNDEFINED,
                    SCREEN_WIDTH,
                    SCREEN_HEIGHT,
                    0
                 );
    
    if (!app.window)
    {
        printf("There has been an error creating the window.\n%s\n", SDL_GetError());
        return -1;
    }

    app.renderer = SDL_CreateRenderer(
                      app.window,
                      -1,
                      SDL_RENDERER_SOFTWARE
                   );

    if (!app.renderer)
    {
        printf("There has been an error creating the renderer.\n%s\n", SDL_GetError());
        return -1;
    }

    SDL_Event e;

    char quit = 0;
    while (!quit)
    {
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                quit = 1;
            }
        }

        SDL_RenderPresent(app.renderer);

        // Enforce FPS
        SDL_Delay(1000/REFRESH_RATE);
    }

    return 0;
}
