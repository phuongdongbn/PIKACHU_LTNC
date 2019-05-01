#include <bits/stdc++.h>
#include "var.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

using namespace std;

#ifndef MYCONSOLESDL_
#define MYCONSOLESDL_

void khoitao(){
    //them background
    background.createTextureIMG("image/image/1.jpg");

    //them logo
    logo.createTextureIMG("image/image/logo.png");
    logo.setSRect(198, 68);
    logo.setDRect(12, 10, 198, 68);

    //them level, score, time
    level.createTextureIMG("image/image/level.png");
    level.setSRect(91, 56);
    level.setDRect(70, pixelStartRow, 91, 56);

    score.createTextureIMG("image/image/score.png");
    score.setSRect(107, 57);
    score.setDRect(70, pixelStartRow+130, 107, 57);

    _time.createTextureIMG("image/image/time.png");
    _time.setSRect(95, 54);
    _time.setDRect(70, pixelStartRow+260, 95, 54);

    //icon
     string s;
     for (int i=1; i<=(ROW-2)*(COLUMN-2); i++){
        int x = (i-1)/(COLUMN-2)+1;
        int y = i-(x-1)*(COLUMN-2);
        if (a[x][y]>0){
            itos(a[x][y],s);
            s="image/icon/"+s+".jpg";
            icon[i].createTextureIMG(s.c_str());
            icon[i].setSRect(40, 45);
            icon[i].setDRect(pixelStartColumn + (y-1)*42, pixelStartRow + (x-1)*47, 40, 45);
        }
    }

    //draw text
    SDL_Color fg = {255, 102, 0};

    string level_string;
    itos(level_number, level_string);
    number_level.createTextureText("font/X-Files.ttf", level_string, 30, fg, 110, 160);
}

void updateScore(){
    score_number=0;
    for (int i=1; i<=(ROW-2)*(COLUMN-2); i++){
        int x = (i-1)/(COLUMN-2)+1;
        int y = i-(x-1)*(COLUMN-2);
        if (a[x][y]==0) score_number+=10;
            //SDL_DestroyTexture(texture[i]);
    }
    string score_string;
    itos(score_number, score_string);
    if (score_string.length()==0) score_string="0";

    SDL_Color fg = {255, 102, 0};
    number_score.createTextureText("font/X-Files.ttf", score_string, 30, fg, 100, 291);

    number_score.renderCopy();
}

void updateTime(){
    string t1, t2;
    itos(time_number/60, t1);
    itos(time_number%60, t2);
    while (t2.length()<2) t2='0'+t2;
    while (t1.length()<2) t1='0'+t1;
    string time_string = t1+" : "+t2;
    SDL_Color fg = {255, 102, 0};
    number_time.createTextureText("font/X-Files.ttf", time_string, 30, fg, 80, 418);

    number_time.renderCopy();
}

void renderCopyConsole(){
    background.renderCopyBackground();
    logo.renderCopy();
    level.renderCopy();
    score.renderCopy();
    _time.renderCopy();
    for (int i=1; i<=(ROW-2)*(COLUMN-2); i++){
        int x = (i-1)/(COLUMN-2)+1;
        int y = i-(x-1)*(COLUMN-2);
        if (a[x][y]>0) icon[i].renderCopy();
            //SDL_DestroyTexture(texture[i]);
    }
    number_level.renderCopy();
}

void render_game_over(){
    SDL_Rect fillRect;
    fillRect.x = 250;
    fillRect.y = 202;
    fillRect.w = 500;
    fillRect.h = 200;
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(renderer, &fillRect);

    SDL text_game_over;
    SDL_Color color1 = {255, 0, 0};

    text_game_over.createTextureText("font/Gameover.ttf", "Game over! ", 70, color1, 315, 220);
    text_game_over.renderCopy();

    //SDL text_replay;
    //SDL_Color color2 = {}
}

void levelUp(){
   // SDL_RenderClear(renderer);
    SDL level_up;
    bool up = false;
    while (!up){
        if ( SDL_WaitEvent(&event) == 0) continue;
        if (event.type == SDL_MOUSEBUTTONDOWN){
            if (event.button.x == 0 && event.button.y == 0) up=true;
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_Color color1 = {255, 0, 0};
        level_up.createTextureText("font/Gameover.ttf", "Congratulation!!!", 70, color1, 315, 220);
        level_up.renderCopy();
    }
    level_number++;
    readData();
}
#endif // MYCONSOLESDL_
