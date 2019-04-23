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
    SDL_Surface* background = IMG_Load("image/image/1.jpg");
    texture[0] = SDL_CreateTextureFromSurface(renderer, background);
    SDL_FreeSurface(background);

    //them logo
    SDL_Surface* logo = IMG_Load("image/image/logo.png");
    texture_logo = SDL_CreateTextureFromSurface(renderer, logo);
    SDL_FreeSurface(logo);
    dRect_logo.w = sRect_logo.w = 198;
    dRect_logo.h = sRect_logo.h = 68;
    sRect_logo.x = sRect_logo.y = 0;
    dRect_logo.x = 12;
    dRect_logo.y = 10;

    //them level, score, time
    SDL_Surface* level = IMG_Load("image/image/level.png");
    texture_level = SDL_CreateTextureFromSurface(renderer, level);
    SDL_FreeSurface(level);
    dRect_level.w = sRect_level.w = 91;
    dRect_level.h = sRect_level.h = 56;
    sRect_level.x = sRect_level.y = 0;
    dRect_level.x = 70 ;
    dRect_level.y = pixelStartRow;

    SDL_Surface* score = IMG_Load("image/image/score.png");
    texture_score = SDL_CreateTextureFromSurface(renderer, score);
    SDL_FreeSurface(score);
    dRect_score.w = sRect_score.w = 107;
    dRect_score.h = sRect_score.h = 57;
    sRect_score.x = sRect_score.y = 0;
    dRect_score.x = 70 ;
    dRect_score.y = pixelStartRow+130;

    SDL_Surface* time = IMG_Load("image/image/time.png");
    texture_time = SDL_CreateTextureFromSurface(renderer, time);
    SDL_FreeSurface(time);
    dRect_time.w = sRect_time.w = 95;
    dRect_time.h = sRect_time.h = 54;
    sRect_time.x = sRect_level.y = 0;
    dRect_time.x = 70 ;
    dRect_time.y = pixelStartRow + 260;

    //icon
     string s;
     for (int i=1; i<=(ROW-2)*(COLUMN-2); i++){
        int x = (i-1)/(COLUMN-2)+1;
        int y = i-(x-1)*(COLUMN-2);
        if (a[x][y]!=0){
            itos(a[x][y],s);
            s="image/icon/"+s+".jpg";
            icon[i] = IMG_Load(s.c_str());
            texture[i] = SDL_CreateTextureFromSurface(renderer, icon[i]);
            SDL_FreeSurface(icon[i]);
            desRect[i].w = sourceRect[i].w = 40;
            desRect[i].h = sourceRect[i].h = 45;
            sourceRect[i].x = sourceRect[i].y = 0;
            desRect[i].x = pixelStartColumn + (y-1)*42;
            desRect[i].y = pixelStartRow + (x-1)*47;
        }
    }

    //draw text
    font_number = TTF_OpenFont("X-Files.ttf", 30);
    SDL_Color fg = {255, 102, 0};

    string level_string;
    itos(level_number, level_string);

    SDL_Surface* sf_level = TTF_RenderText_Solid(font_number, level_string.c_str(), fg);
    texture_number_level = SDL_CreateTextureFromSurface(renderer, sf_level);
    SDL_FreeSurface(sf_level);


    TTF_SizeText(font_number, level_string.c_str(), &sRect_number_level.w, &sRect_number_level.h);
    sRect_number_level.x = sRect_number_level.y = 0;
    dRect_number_level.w = sRect_number_level.w;
    dRect_number_level.h = sRect_number_level.h;
    dRect_number_level.x = 110;
    dRect_number_level.y = 160;

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

    font_number = TTF_OpenFont("X-Files.ttf", 30);
    SDL_Color fg = {255, 102, 0};

    SDL_Surface* sf_score = TTF_RenderText_Solid(font_number, score_string.c_str(), fg);
    texture_number_score = SDL_CreateTextureFromSurface(renderer, sf_score);
    SDL_FreeSurface(sf_score);

    TTF_SizeText(font_number, score_string.c_str(), &sRect_number_score.w, &sRect_number_score.h);
    sRect_number_score.x = sRect_number_score.y = 0;
    dRect_number_score.w = sRect_number_score.w;
    dRect_number_score.h = sRect_number_score.h;
    dRect_number_score.x = 100;
    dRect_number_score.y = 291;

    SDL_RenderCopy(renderer, texture_number_score, &sRect_number_score, &dRect_number_score);
}

void updateTime(){
    string t1, t2;
    itos(time_number/60, t1);
    itos(time_number%60, t2);
    while (t2.length()<2) t2='0'+t2;
    while (t1.length()<2) t1='0'+t1;
    string time_string = t1+" : "+t2;
    font_number = TTF_OpenFont("X-Files.ttf", 30);
    SDL_Color fg = {255, 102, 0};
    SDL_Surface* sf_time = TTF_RenderText_Solid(font_number, time_string.c_str(), fg);
    texture_number_time = SDL_CreateTextureFromSurface(renderer, sf_time);
    SDL_FreeSurface(sf_time);

    TTF_SizeText(font_number, time_string.c_str(), &sRect_number_time.w, &sRect_number_time.h);
    sRect_number_time.x = sRect_number_time.y = 0;
    dRect_number_time.w = sRect_number_time.w;
    dRect_number_time.h = sRect_number_time.h;
    dRect_number_time.x = 80;
    dRect_number_time.y = 418;

     SDL_RenderCopy(renderer, texture_number_time, &sRect_number_time, &dRect_number_time);
}

void renderCopy(){
    SDL_RenderCopy(renderer, texture[0], NULL, NULL);
    SDL_RenderCopy(renderer, texture_logo, &sRect_logo, &dRect_logo);
    SDL_RenderCopy(renderer, texture_level, &sRect_level, &dRect_level);
    SDL_RenderCopy(renderer, texture_score, &sRect_score, &dRect_score);
    SDL_RenderCopy(renderer, texture_time, &sRect_time, &dRect_time);
    for (int i=1; i<=(ROW-2)*(COLUMN-2); i++){
        int x = (i-1)/(COLUMN-2)+1;
        int y = i-(x-1)*(COLUMN-2);
        if (a[x][y]!=0) SDL_RenderCopy(renderer, texture[i], &sourceRect[i], &desRect[i]);
            //SDL_DestroyTexture(texture[i]);
    }
    SDL_RenderCopy(renderer, texture_number_level, &sRect_number_level, &dRect_number_level);
}
#endif // MYCONSOLESDL_
