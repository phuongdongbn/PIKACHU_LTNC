#include <iostream>
#include <fstream>
#include <vector>
#include <bits/stdc++.h>
#include "console.hpp"
#include "var.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

using namespace std;


int main(int argc, char* argv[])
{
    readData();
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Rect sourceRect[150];
    SDL_Rect desRect[150];
    SDL_Renderer* renderer;
    SDL_Texture* texture[150];
    SDL_Surface* icon[150];
    SDL_Event event;
    string s;
    SDL_Window* window = SDL_CreateWindow("Pikachu", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1000, 605, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_Surface* image = IMG_Load("image/image/1.jpg");
    texture[0] = SDL_CreateTextureFromSurface(renderer, image);
    for (int i=1; i<=(ROW-2)*(COLUMN-2); i++){
        int x = (i-1)/(COLUMN-2)+1;
        int y = i-(x-1)*(COLUMN-2);
        if (a[x][y]!=0){
            itos(a[x][y],s);
            s="image/icon/"+s+".jpg";
            icon[i] = IMG_Load(s.c_str());
            texture[i] = SDL_CreateTextureFromSurface(renderer, icon[i]);
            SDL_FreeSurface(icon[i]);
            desRect[i].w = sourceRect[i].w = 43;
            desRect[i].h = sourceRect[i].h = 45;
            sourceRect[i].x = sourceRect[i].y = 0;
            desRect[i].x = pixelStartColumn + (y-1)*44;
            desRect[i].y = pixelStartRow + (x-1)*46;
        }
    }
    bool quit = false;
    int tt=0;
    while (!quit)
    {
        if ( SDL_WaitEvent(&event) == 0) continue;
        if (event.type == SDL_QUIT) quit = true;
        if (event.type == SDL_MOUSEBUTTONDOWN){
            int x = event.button.x;
            int y = event.button.y;
            tt++;
            tienxuly(tt,x,y);
        }
        SDL_RenderCopy(renderer, texture[0], NULL, NULL);
        for (int i=1; i<=(ROW-2)*(COLUMN-2); i++){
            int x = (i-1)/(COLUMN-2)+1;
            int y = i-(x-1)*(COLUMN-2);
            if (a[x][y]!=0) SDL_RenderCopy(renderer, texture[i], &sourceRect[i], &desRect[i]);
            //SDL_DestroyTexture(texture[i]);
        }
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
