#include <bits/stdc++.h>
#include "console.hpp"
#include "sdl.hpp"
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

    //them ten
    bool quit = sdlTextInput();

    khoitao();

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

        if (again){
            level_number=1;
            readData();
            rev_number = 10;
            score_number=0;
            again = false;
            khoitao();
            start_time = clock();
            tt=0;
        }

        // win
        if (level_number>5){
            renderWin();
            SDL_RenderPresent(renderer);
            continue;
        }

        // xu ly click chuot
        if (event.type == SDL_MOUSEBUTTONDOWN){
            int x = event.button.x;
            int y = event.button.y;
            if (time_number>0 && !level_check){
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
                    if (x>=780 && x<=825 && y>=32 && y<=68) {
                        ttSound++;
                        onOffSound(ttSound);
                    }
                    if (x>=850 && x<=895 && y>=27 && y<=73 && rev_number>0) {
                        rev_number--;
                        reverseMap();
                        khoitao();
                    }
                }
            }
            if (time_number<=0 && !level_check){
                if (x>=330 && x<=450 && y>=520 && y<=570){
                    again = true;
                    continue;
                }
            }
        }
        caculateScore();
        if (!level_check) {
                time_number = TimeLimited - (int)(clock()-start_time)/CLOCKS_PER_SEC;
                if (time_number<=0 && !again) {
                    render_game_over();
                    SDL_RenderPresent(renderer);
                    continue;
                }
            renderCopyConsole();
            updateTime();
            updateScore();
        }
        renderReverse();
        if (choose) renderChooseRect(xx,yy);
        renderSound(ttSound);
        if (score_number==1440*level_number) level_check=true;
        if (level_check) {
            level_number++;
            tt = 0;
            rev_number = rev_number+ (time_number-1)/180 +1;
            readData();
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
