#include <bits/stdc++.h>
#include "var.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

using namespace std;

#ifndef MYCONSOLESDL_
#define MYCONSOLESDL_

void themBg(){
    //them background
    background.createTextureIMG("image/image/1.jpg");
    background.renderCopyBackground();

}

void khoitao(){

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

void renderReverse(){
    SDL rev;
    rev.createTextureIMG("image/image/chuyen-ban-do.jpg");
    rev.setDRect(850,27,45,46);
    rev.setSRect(45, 46);
    rev.renderCopy();

    SDL number_rev;
    string rev_string;
    itos(rev_number, rev_string);
    if (rev_number==0) rev_string="0";
    SDL_Color fg = {255, 102, 0};
    number_rev.createTextureText("font/X-Files.ttf", rev_string, 50, fg, 900, 30);
    number_rev.renderCopy();
}

//them Ranking
void renderRank(){
    SDL ranking;
    SDL score_rank;
    SDL name_rank;
    string s1, s2;
    SDL_Color fg = {255, 255, 255};
    SDL_Color fg2 = {201, 228, 214};
    ranking.createTextureText("font/Gameover.ttf", "#", 40, fg, 250, 200);
    score_rank.createTextureText("font/Gameover.ttf", "SCORE", 40, fg, 700, 200);
    name_rank.createTextureText("font/Gameover.ttf", "SCORE", 40, fg, 300, 200);
    score_rank.renderCopy();
    name_rank.renderCopy();
    bool check = false;
    for (int i=0; i<4; i++){
        if (i>=count_players) break;
        itos(i+1,s1);
        itos(list_score[i],s2);
        while (s2.length()<4) s2="0"+s2;
        if (list_name[i]==name && list_score[i]==score_number && !check){
            check = true;
            vt = i;
            ranking.createTextureText("font/Gameover.ttf", s1, 35, fg2, 250, 250+i*40);
            score_rank.createTextureText("font/Gameover.ttf", list_name[i], 35, fg2, 700, 250+i*40);
            name_rank.createTextureText("font/Gameover.ttf", s2, 35, fg2, 300, 250+i*40);
            score_rank.renderCopy();
            name_rank.renderCopy();
            ranking.renderCopy();
        } else {
            ranking.createTextureText("font/Gameover.ttf", s1, 35, fg, 250, 250+i*40);
            score_rank.createTextureText("font/Gameover.ttf", list_name[i], 35, fg, 700, 250+i*40);
            name_rank.createTextureText("font/Gameover.ttf", s2, 35, fg, 300, 250+i*40);
            score_rank.renderCopy();
            name_rank.renderCopy();
            ranking.renderCopy();
        }
    }
    ranking.createTextureText("font/Gameover.ttf", "...", 35, fg, 250, 410);
    ranking.renderCopy();
    if (!check){
        for (int i=4; i<count_players; i++){
            if (list_name[i]==name && list_score[i]==score_number){
                vt = i;
                itos(i+1,s1);
                itos(list_score[i],s2);
                while (s2.length()<4) s2="0"+s2;
                ranking.createTextureText("font/Gameover.ttf", s1, 35, fg2, 250, 450);
                score_rank.createTextureText("font/Gameover.ttf", list_name[i], 35, fg2, 700, 450);
                name_rank.createTextureText("font/Gameover.ttf", s2, 35, fg2, 300, 450);
                score_rank.renderCopy();
                name_rank.renderCopy();
                ranking.renderCopy();
            }
        }
    }
}

void renderSound(int tt){
    SDL sound;
    if (tt%2==1) sound.createTextureIMG("image/image/sound.jpg");
    else sound.createTextureIMG("image/image/non-sound.jpg");
    sound.setDRect(780,27,45,46);
    sound.setSRect(45, 46);
    sound.renderCopy();
}

void updateScore(){
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
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL text_game_over;
    SDL_Color color = {255, 0, 0};

    text_game_over.createTextureText("font/Gameover.ttf", "Game over! ", 70, color, 315, 100);
    text_game_over.renderCopy();

    if (list_score[vt]<score_number) list_score[vt]=score_number;
    else score_number = list_score[vt];
    writeNameAndScore();
    renderRank();

    SDL text_replay;

    text_replay.createTextureText("font/Gameover.ttf", "Play Again", 50, color, 330, 520);
    text_replay.renderCopy();
    //SDL_Color color2 = {}
}

void renderWin(){
    SDL_RenderClear(renderer);
    SDL textWin;
    SDL_Color color = {255, 0, 0};
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    textWin.createTextureText("font/Gameover.ttf", "YOU WIN! ", 70, color, 315, 100);
    textWin.renderCopy();

    list_score[vt]=7200;
    score_number = 7200;
    writeNameAndScore();
    renderRank();
    //SDL text_replay;
    //SDL_Color color2 = {}
}


void onOffSound(int tt){
    if (tt==1){
        //tao nhac nen
        if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1)
            {
                printf("%s", Mix_GetError());
                return;
            }
        music = Mix_LoadMUS("mp3/Hope_You.mp3");
        Mix_PlayMusic(music,-1);
        return;
    }
    if (tt%2==0) Mix_PauseMusic();
    else Mix_ResumeMusic();
}

void renderChooseRect(int x, int y){
    x = (x - pixelStartColumn)/42 + 1;
    y = (y - pixelStartRow)/47 + 1;

    SDL_Rect chooseRect;
    chooseRect.x = pixelStartColumn + (x-1)*42 -2;
    chooseRect.y = pixelStartRow + (y-1)*47 -2;
    chooseRect.w = 44;
    chooseRect.h = 49;

    SDL_RenderDrawRect(renderer, &chooseRect);
}

//nhap ten
bool sdlTextInput(){
    readNameAndScore();
    bool done = false;
    SDL_Event e;
    SDL_StartTextInput();

    SDL_Rect fillRect;
    fillRect.x = 350;
    fillRect.y = 300;
    fillRect.w = 300;
    fillRect.h = 40;
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &fillRect);

    SDL text_name;
    SDL text_p_name;
    SDL_Color color1 = {246, 178, 151};
    SDL_Color color2 = {0, 0, 0};
    text_p_name.createTextureText("font/Gameover.ttf", "Your name: ", 30, color1, 350, 260);

    while (!done){
        SDL_RenderClear(renderer);
        themBg();
        SDL_RenderFillRect(renderer, &fillRect);

        if ( SDL_WaitEvent(&e) == 0) continue;

        if (e.type == SDL_QUIT){
            done = true;
            return true;
        }

        if (e.type == SDL_KEYDOWN){
            if (e.key.keysym.sym == SDLK_BACKSPACE && name.length()>0) name.pop_back();
            if (e.key.keysym.sym == SDLK_RETURN || e.key.keysym.sym == SDLK_SPACE){
                if (name.length()>0){
                    done = true;
                    break;
                } else continue;
            }
        }
         if (e.type == SDL_TEXTINPUT && name.length()<20 && e.text.text[0]!=' '){
                name += e.text.text;
        }

        text_name.createTextureText("font/Gameover.ttf", name, 30, color2, 365, 310);
        text_p_name.renderCopy();
        text_name.renderCopy();
        SDL_RenderPresent(renderer);
    }
    count_players++;
    list_name.push_back(name);
    list_score.push_back(0);
    vt = count_players-1;
    SDL_StopTextInput();
    return false;
}

#endif // MYCONSOLESDL_
