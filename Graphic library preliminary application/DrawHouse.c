#include <stdlib.h>
#include <stddef.h>
#include "graphics.h"
#include "genlib.h"
#include "conio.h"
#include <windows.h>
#include <olectl.h>
#include <stdio.h>
#include <mmsystem.h>
#include <wingdi.h>
#include <ole2.h>
#include <ocidl.h>
#include <winuser.h>

#define Print_Current printf("X = %f, Y = %f\n", GetCurrentX(), GetCurrentY())

void drawRectangle(double x, double y, double w, double h);
void Main(){
    InitGraphics();
    
    //Print_Current;
    const double X = 3, Y = 3;
    drawRectangle(X, Y, 1.72, 1.97);
    
    drawRectangle(X + 0.86, Y, 0.42, 1.48);
    
    drawRectangle(X + 0.32, Y + 1.07, 0.35, 0.39);
    
    drawTriangle(X, Y + 1.97, X + 0.87, Y + 3.66, X + 1.72, Y + 1.97);
        
    MovePen(X + 0.19, Y + 2.33);
    DrawLine(0, 0.73);
    
    MovePen(X + 0.45, Y + 2.81);
    DrawLine(0, 0.25);
    
    drawRectangle(X + 0.1, X + 3.06, 0.43, 0.20);
    
    return;
}

void drawTriangle(double x1, double y1, double x2, double y2, double x3, double y3){
    MovePen(x1, y1);
    DrawLine(x2 - x1, y2 - y1);
    DrawLine(x3 - x2, y3 - y2);
    DrawLine(x1 - x3, y1 - y3);
}
void drawRectangle(double x, double y, double w, double h){
    MovePen(x, y);
    DrawLine(w, 0);
    DrawLine(0,h);
    DrawLine(-w, 0);
    DrawLine(0,-h);
}

