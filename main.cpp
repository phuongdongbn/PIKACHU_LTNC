#include <bits/stdc++.h>
#include "console.hpp"
#include "console_sdl.hpp"
#include "var.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

using namespace std;


int main(int argc, char* argv[])
{
    readData(); // doc du lieu

    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    // tao cua so
    window = SDL_CreateWindow("Pikachu", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1000, 605, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    khoitao();

    bool quit = false;
    int tt=0;

    // show
    clock_t start_time = clock();
    while (!quit)
    {
        //doi event
        if ( SDL_WaitEvent(&event) == 0) continue;

        // Thoat
        if (event.type == SDL_QUIT) quit = true;

        // xu ly click chuot
        if (event.type == SDL_MOUSEBUTTONDOWN){
            int x = event.button.x;
            int y = event.button.y;
            tt++;
            tienxuly(tt,x,y);
            //updateScore();
        }

        renderCopy();
        time_number=180 - (int)(clock()-start_time)/CLOCKS_PER_SEC;
        //if (time_number<=0) reder_game_over();
        updateTime();
        updateScore();
        SDL_RenderPresent(renderer);
    }

    //thoat chuong trinh
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
