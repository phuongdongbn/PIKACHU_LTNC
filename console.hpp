#include <bits/stdc++.h>
#include "var.hpp"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

using namespace std;

#ifndef MYCONSOLE_
#define MYCONSOLE_

//chuan hoa lai cot va hang

bool checkLimit(int i, int j){
    if (i<0 || i>=ROW) return false;
    if (j<0 || j>=COLUMN) return false;
    return true;
}

// xuly di chuyen ban do
void update(int x, int y){
    if (level_number==1) return;
    int tg;
    switch(level_number){
        case 2:
            tg = a[ROW-2][y];
            for (int i=ROW-2; i>1; i--) a[i][y]=a[i-1][y];
            a[1][y]=tg;
            break;
        case 3:
            tg = a[x][COLUMN-2];
            for (int i=COLUMN-2; i>1; i--) a[x][i]=a[x][i-1];
            a[x][1]=tg;
        case 4:
            for (int i=ROW-3; i>0; i--)
                if (a[i][y]>0){
                    int j=i+1;
                    while (a[j][y]==0 && j<ROW-1){
                        swap(a[j-1][y],a[j][y]);
                        j++;
                    }
                }
            break;
        case 5:
            for (int i=COLUMN-3; i>0; i--)
                if (a[x][i]>0){
                    int j=i+1;
                    while (a[x][j]==0 && j<COLUMN-1){
                        swap(a[x][j-1],a[x][j]);
                        j++;
                    }
                }
            break;
    }
}

// tim duong di
void xuly(){
    if (a[xs][ys]!=a[xf][yf]) return;
    if (xs==xf && ys==yf) return;
    int tx[] = {-1, 0, 1, 0};
    int ty[] = {0, 1, 0, -1};
    queue <int> x;
    queue <int> y;
    queue <int> h;
    int xd[ROW][COLUMN][4] = {};
    int l[ROW][COLUMN][4] = {};
    for (int i=0; i<4; i++) xd[xs][ys][i]=1;
    int xx, yy, dx, dy, dh;
    //loang 4 o lan can
    for (int i=0; i<4; i++){
        xx = xs+tx[i];
        yy = ys+ty[i];
        if (xx==xf && yy==yf){
            a[xs][ys]=0;
            a[xf][yf]=0;
            update(xs,ys);
            update(xf,yf);
            return;
        }
        else if (checkLimit(xx,yy) && a[xx][yy]==0){
            x.push(xx);
            y.push(yy);
            h.push(i);
            l[xx][yy][i]=0;
            xd[xx][yy][i]=1;
        }
    }
    while (x.size()>0){
        dx = x.front(); x.pop();
        dy = y.front(); y.pop();
        dh = h.front(); h.pop();
        for (int i=0; i<4; i++){
            xx = dx + tx[i];
            yy = dy + ty[i];
            if (checkLimit(xx,yy)){
                if (a[xx][yy]==0 || (xx==xf && yy ==yf)){
                    if (xd[xx][yy][i]==0){
                        if (i==dh) l[xx][yy][i]=l[dx][dy][dh];
                        else l[xx][yy][i]=l[dx][dy][dh]+1;
                        xd[xx][yy][i]=1;
                        x.push(xx); y.push(yy);
                        h.push(i);
                    } else {
                        if (i==dh){
                            if (l[xx][yy][i]>l[dx][dy][dh]) l[xx][yy][i]=l[dx][dy][dh];
                        } else {
                            if (l[xx][yy][i]>l[dx][dy][dh]+1) l[xx][yy][i]=l[dx][dy][dh]+1;
                        }
                    }
                }
            }
        }
    }
    for (int i=0; i<4; i++)
        if (l[xf][yf][i]<3 && xd[xf][yf][i]==1) {
            a[xf][yf]=0;
            a[xs][ys]=0;
            update(xs,ys);
            update(xf,yf);
            return;
        }
}

//doc du lieu
void readData(){
    srand(time(0));
    int x = rand()%9 +1;
    string filepath_level = "bando/level";
    filepath_level+=chars[x];
    filepath_level+=".txt";
    ifstream fi(filepath_level.c_str());
    a.resize(ROW);
    for (int i=0; i<ROW; i++){
        a[i].resize(COLUMN);
        for (int j=0; j<COLUMN; j++){
            fi >> a[i][j];
        }
    }
}

void reverseMap(){
    srand(time(0));
    int x,y,dx,dy;
    for (int t=0; t<20; t++){
        do {
            x = rand()%(ROW-2) +1;
            y = rand()%(COLUMN-2) +1;
            dx = rand()%(ROW-2) +1;
            dy = rand()%(COLUMN-2) +1;
        } while (a[x][y]<=0 || a[dx][dy]<=0);
        swap(a[x][y], a[dx][dy]);
    }
}

//tien xu ly
void tienxuly(int tt, int x, int y){
    x = (x - pixelStartColumn)/42 + 1;
    y = (y - pixelStartRow)/47 + 1;

    if (tt%2==1){
        xs = y;
        ys = x;
    } else {
        xf = y;
        yf = x;
        xuly();
    }
}

// chuyen so sang xau
void itos(int x, string &s){
    s="";
    while (x>0){
        s=chars[x%10]+s;
        x/=10;
    }
}

void caculateScore(){
    score_number=(level_number-1)*1440;
    for (int i=1; i<=(ROW-2)*(COLUMN-2); i++){
        int x = (i-1)/(COLUMN-2)+1;
        int y = i-(x-1)*(COLUMN-2);
        if (a[x][y]<=0) score_number+=10;
            //SDL_DestroyTexture(texture[i]);
    }
}
#endif // MYCONSOLE_



