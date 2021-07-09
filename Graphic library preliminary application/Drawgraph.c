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
#include <math.h>

#define Print_Current printf("X = %f, Y = %f\n", GetCurrentX(), GetCurrentY())
#define CX GetCurrentX()
#define CY GetCurrentY()

static double Angle;
static double length = 1.0;
static double pi = 2*acos(0.0);
void forward(double distance);
void turn(double angle);
void move(double distance);
void Main(){
    InitGraphics();
    
    SetPenColor("Green"); 
    SetPenSize(2);

    
    MovePen(GetWindowWidth() / 2, GetWindowHeight() / 2);
    int i = 18;
    while(i){
        int j = 6;
        while(j){
            Angle -=60;
            forward(length); 
            j--;
        }
        Angle -= 20;
        i--;
    }
    
    return;
}

void forward(double distance){
    DrawLine(distance * cos(Angle/180*pi), distance * sin(Angle/180*pi)); 
}

void turn(double angle){
    Angle += angle;
}

void move(double distance){
    MovePen(CX + distance * cos(Angle/180*pi), CY + distance * sin(Angle/180*pi));
}
