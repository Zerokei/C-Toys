#include "graphics.h"
#include "extgraph.h"
#include "genlib.h"
#include "simpio.h"
#include "conio.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#include <windows.h>
#include <olectl.h>
#include <mmsystem.h>
#include <wingdi.h>
#include <ole2.h>
#include <ocidl.h>
#include <winuser.h>
#include <math.h>


void GetNewNode(double x1, double y1, double *x3, double *y3, double r, int theta);
void Draw(double x1, double y1, double x2, double y2, double r, int n, int theta);

void Main(){
    InitConsole();
    
    int n;
    double r;
    scanf("%d%lf", &n, &r);
    
    InitGraphics();
    
    double midx = GetWindowWidth()/2;
    double midy = GetWindowHeight()/2;
    double X1, Y1, X2, Y2, X3, Y3;
    GetNewNode(midx, midy, &X1, &Y1, r/sqrt(3), 90);
    GetNewNode(midx, midy, &X2, &Y2, r/sqrt(3), 210);
    GetNewNode(midx, midy, &X3, &Y3, r/sqrt(3), 330);
    Draw(X1, Y1, X2, Y2, r, n, 240);
    Draw(X2, Y2, X3, Y3, r, n, 0);
    Draw(X3, Y3, X1, Y1, r, n, 120);
    
    return;
}

void GetNewNode(double x1, double y1, double *x3, double *y3, double r, int theta){
    double radians = (double)theta / 180 * 3.1415926535;
    *x3 = x1 + r * cos(radians);
    *y3 = y1 + r * sin(radians);
}

void Draw(double x1, double y1, double x2, double y2, double r, int n, int theta){
    if(n == 1){
        MovePen(x1,y1);
        DrawLine(x2-x1,y2-y1);
        return;
    }

    double X1 = (x2+x1*2)/3; 
    double Y1 = (y2+y1*2)/3;
    double X2 = (x1+x2*2)/3;
    double Y2 = (y1+y2*2)/3;
    double X3;
    double Y3;
    GetNewNode(X1, Y1, &X3, &Y3, r / 3, theta - 60);

    Draw(x1, y1, X1, Y1, r / 3, n - 1, theta);
    Draw(X2, Y2, x2, y2, r / 3, n - 1, theta);
    Draw(X1, Y1, X3, Y3, r / 3, n - 1, theta - 60);
    Draw(X3, Y3, X2, Y2, r / 3, n - 1, theta + 60);
}
