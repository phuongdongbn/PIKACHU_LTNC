#include <bits/stdc++.h>
#include "console.hpp"
#include "console_sdl.hpp"
#include "var.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

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

    //tao nhac nen
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1)
	{
		printf("%s", Mix_GetError());
		return -1;
	}
	//chunk = Mix_LoadWAV("sound_effects.wav");
    music = Mix_LoadMUS("mp3/Hope_You.mp3");
    Mix_PlayMusic(music,-1);

    bool quit = false;
    bool level_check = false;
    bool choose = false;
    int tt=0;
    int ttSound=0;
    int xx,yy;

    // show
    clock_t start_time = clock();
    while (!quit)
    {
        SDL_RenderClear(renderer);
        //doi event
        if ( SDL_WaitEvent(&event) == 0) continue;

        // Thoat
        if (event.type == SDL_QUIT) quit = true;

        // xu ly click chuot
        if (event.type == SDL_MOUSEBUTTONDOWN && time_number>0 && !level_check){
            int x = event.button.x;
            int y = event.button.y;
            if (x>=pixelStartColumn && y>=pixelStartRow){
                tt++;
                tienxuly(tt,x,y);
                if (tt%2==1){
                    choose = true;
                    xx = x;
                    yy = y;
                } else choose = false;
            //updateScore();
            } else {
                if (x>=800 && x<=845 && y>=32 && y<=68) {
                    ttSound++;
                    onOffSound(ttSound);
                }
                if (x>=850 && x<=895 && y>=27 && y<=73) {
                    reverseMap();
                    khoitao();
                }
            }
        }
        caculateScore();
        if (!level_check) {
                renderCopyConsole();
                time_number = TimeLimited - (int)(clock()-start_time)/CLOCKS_PER_SEC;
                if (time_number<=0) {
                    render_game_over();
                    time_number = 0;
                }
            updateTime();
            updateScore();
        }
        renderReverse();
        if (choose) renderChooseRect(xx,yy);
        renderSound(ttSound);
        if (score_number%1440==0 && score_number>0) level_check=true;
        if (level_check) {
            readData();
            level_number++;
            khoitao();
            level_check=false;
            start_time = clock();
        }
        SDL_RenderPresent(renderer);
    }

    //thoat chuong trinh
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
