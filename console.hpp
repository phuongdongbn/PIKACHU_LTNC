#include <bits/stdc++.h>
#include "var.hpp"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>

using namespace std;

#ifndef MYCONSOLE_
#define MYCONSOLE_

//chuan hoa lai cot va hang
bool checkROW(int i){
    if (i<0 || i>=ROW) return false;
    for (int j=0; j<COLUMN; j++)
        if (a[i][j]>0) return false;
    return true;
}

bool checkCOLUMN(int i){
    if (i<0 || i>=COLUMN) return false;
    for (int j=0; j<ROW; j++)
        if (a[j][i]>0) return false;
    return true;
}

bool checkLimit(int i, int j){
    if (i<0 || i>=ROW) return false;
    if (j<0 || j>=COLUMN) return false;
    return true;
}

//cap nhat lai mang a
void update(){
    for (int i=0; i<ROW; i++){
        if (checkROW(i) && checkROW(i+1) && checkROW(i-1)){
            for (int j=0; j<COLUMN; j++) a[i][j]=-1;
        }
    }
    for (int i=0; i<COLUMN; i++){
        if (checkCOLUMN(i) && checkCOLUMN(i+1) && checkCOLUMN(i-1)){
            for (int j=0; j<ROW; j++) a[j][i]=-1;
        }
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
            update();
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
            update();
            return;
        }
}

//doc du lieu
void readData(){
    int x = rand()%5;
    string filepath_level = "bando/level";
    filepath_level+=chars[x];
    filepath_level+=".txt";
    ifstream fi("bando/level1.txt");
    a.resize(ROW);
    for (int i=0; i<ROW; i++){
        a[i].resize(COLUMN);
        for (int j=0; j<COLUMN; j++){
            fi >> a[i][j];
        }
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
#endif // MYCONSOLE_



