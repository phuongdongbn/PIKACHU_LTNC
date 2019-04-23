#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

using namespace std;

#ifndef MYVAR_
#define MYVAR_

// bien thuong
const int ROW = 11, COLUMN = 18;
const int pixelStartRow = 100, pixelStartColumn = 230;
vector< vector<int> > a;
int xs, ys, xf, yf;
int level_number = 1;
int score_number = 0;
int time_number = 180;
char chars[]={'0','1','2','3','4','5','6','7','8','9'};

//Cac bien SDL

SDL_Window* window;
SDL_Renderer* renderer;

SDL_Rect sourceRect[150], sRect_logo, sRect_level, sRect_time, sRect_score;
SDL_Rect desRect[150], dRect_logo, dRect_level, dRect_time, dRect_score;
SDL_Rect sRect_number_level, dRect_number_level, sRect_number_score, dRect_number_score, sRect_number_time, dRect_number_time;

SDL_Texture* texture[150];
SDL_Texture* texture_logo;
SDL_Texture* texture_level;
SDL_Texture* texture_score;
SDL_Texture* texture_time;
SDL_Texture* texture_number_level;
SDL_Texture* texture_number_time;
SDL_Texture* texture_number_score;

SDL_Surface* icon[150];
SDL_Event event;

TTF_Font* font_number = NULL;

#endif


