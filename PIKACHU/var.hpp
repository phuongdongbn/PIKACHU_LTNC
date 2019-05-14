#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

using namespace std;

#ifndef MYVAR_
#define MYVAR_

// bien thuong
const int ROW = 11, COLUMN = 18;
const int pixelStartRow = 100, pixelStartColumn = 230;
const int TimeLimited = 600;
vector< vector<int> > a;
int xs, ys, xf, yf;
int level_number = 1;
int score_number = 0;
int time_number = 0;
int rev_number = 10;
char chars[]={'0','1','2','3','4','5','6','7','8','9'};
vector <string> list_name;
vector <int> list_score;
int count_players;
string name = "";
bool again = false;
int vt;

//Cac bien SDL

SDL_Window* window;
SDL_Renderer* renderer;
Mix_Music* music;

class SDL{
    SDL_Rect sRect, dRect;
    SDL_Texture* texture;

public:

    void setSRect(int w, int h){
        sRect.x = sRect.y = 0;
        sRect.w = w;
        sRect.h = h;
    }

    void setDRect(int x, int y, int w, int h){
        dRect.x = x;
        dRect.y = y;
        dRect.w = w;
        dRect.h = h;
    }

    void createTextureIMG(string filepath){
        SDL_Surface* surface = IMG_Load(filepath.c_str());
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
    }

    void createTextureText(string filepath, string c_string, int font_size, SDL_Color color, int x, int y){
        TTF_Font* font = TTF_OpenFont(filepath.c_str(), font_size);
        SDL_Surface* surface = TTF_RenderText_Solid(font, c_string.c_str(), color);
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
        int w, h;
        TTF_SizeText(font, c_string.c_str(), &w, &h);
        setDRect(x, y, w, h);
        setSRect(w, h);
    }

    void renderCopyBackground(){
        SDL_RenderCopy(renderer, texture, NULL, NULL);
    }

    void renderCopy(){
        SDL_RenderCopy(renderer, texture, &sRect, &dRect);
    }
};

SDL background;
SDL icon[150];
SDL logo, level, _time, score;
SDL number_level, number_time, number_score;

SDL_Event event;

TTF_Font* font_number = NULL;

#endif


