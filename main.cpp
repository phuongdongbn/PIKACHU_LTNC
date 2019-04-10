#include <iostream>
#include <fstream>
#include <vector>
#include <bits/stdc++.h>
#include <SDL.h>

using namespace std;

const int ROW = 9, COLUMN = 10;

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer){
}

bool checkROW(vector< vector<int> > &a, int i){
    if (i<0 || i>=ROW) return false;
    for (int j=0; j<COLUMN; j++)
        if (a[i][j]>0) return false;
    return true;
}

bool checkCOLUMN(vector< vector<int> > &a, int i){
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

void update(vector< vector<int> > &a){
    for (int i=0; i<ROW; i++){
        if (checkROW(a,i) && checkROW(a,i+1) && checkROW(a,i-1)){
            for (int j=0; j<COLUMN; j++) a[i][j]=-1;
        }
    }
    for (int i=0; i<COLUMN; i++){
        if (checkCOLUMN(a,i) && checkCOLUMN(a,i+1) && checkCOLUMN(a,i-1)){
            for (int j=0; j<ROW; j++) a[j][i]=-1;
        }
    }

}

void xuly(int xs, int ys, int xf, int yf, vector< vector<int> > &a){
    if (a[xs][ys]!=a[xf][yf]) return;
    int tx[] = {-1, 0, 1, 0};
    int ty[] = {0, 1, 0, -1};
    queue <int> x;
    queue <int> y;
    queue <int> h;
    int xd[ROW][COLUMN] = {};
    int l[ROW][COLUMN] = {};
    xd[xs][ys]=1;
    int xx, yy, dx, dy, dh;
    //loang 4 o lan can
    for (int i=0; i<4; i++){
        xx = xs+tx[i];
        yy = ys+ty[i];
        if (xx==xf && yy==yf){
            a[xs][ys]=0;
            a[xf][yf]=0;
            update(a);
            return;
        }
        else if (checkLimit(xx,yy) && a[xx][yy]==0){
            x.push(xx);
            y.push(yy);
            h.push(i);
            l[xx][yy]=0;
            xd[xx][yy]=1;
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
                    if (xd[xx][yy]==0){
                        if (i==dh) l[xx][yy]=l[dx][dy];
                        else l[xx][yy]=l[dx][dy]+1;
                        xd[xx][yy]=1;
                        x.push(xx); y.push(yy); h.push(i);
                    } else {
                        if (i==dh){
                            if (l[xx][yy]>l[dx][dy]) l[xx][yy]=l[dx][dy];
                        } else {
                            if (l[xx][yy]>l[dx][dy]+1) l[xx][yy]=l[dx][dy]+1;
                        }
                    }
                }
            }
        }
        if (l[xf][yf]<3 && xd[xf][yf]==1) {
            a[xf][yf]=0;
            a[xs][ys]=0;
            update(a);
        }
    }
}

int main()
{
    ifstream fi("level1.txt");
    vector< vector<int> > a;
    int x1, x2, y1, y2;

    //nhap du lieu
    a.resize(ROW);
    for (int i=0; i<ROW; i++){
        a[i].resize(COLUMN);
        for (int j=0; j<COLUMN; j++){
            fi >> a[i][j];
        }
    }
    for (int i=1; i<ROW-1; i++){
            for (int j=1; j<COLUMN-1; j++){
                cout << a[i][j] << " ";
            }
            cout << endl;
        }
    clock_t timeStart = clock();
    while ((double)(clock()-timeStart)/CLOCKS_PER_SEC <=30){
        cin >> x1 >> y1 >> x2 >> y2;
        xuly(x1,y1,x2,y2,a);
        for (int i=1; i<ROW-1; i++){
            for (int j=1; j<COLUMN-1; j++){
                cout << a[i][j] << " ";
            }
            cout << endl;
        }
    }
    return 0;
}
