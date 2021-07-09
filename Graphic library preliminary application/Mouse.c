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


void MouseEventProcess(int x, int y, int button, int event);/*鼠标消息回调函数*/
void Main(){
    InitGraphics();
    registerMouseEvent(MouseEventProcess);/*注册鼠标消息回调函数*/
	SetPenSize(1);       
    return;
} 
void MouseEventProcess(int x, int y, int button, int event){
    double mx = ScaleXInches(x);/*pixels --> inches*/
 	double my = ScaleYInches(y);/*pixels --> inches*/
 	static double omx = 0.0, omy = 0.0; 
    static bool isLEFT = FALSE;
    switch(event){
        case BUTTON_DOWN:
            if(button == LEFT_BUTTON){
                MovePen(mx, my); 
                isLEFT = TRUE;
            }
            omx = mx;
            omy = my;
            break;
        case MOUSEMOVE:
            if(isLEFT == TRUE){    
                DrawLine(mx - omx, my - omy);
            }
            omx = mx,omy = my;
            break;
        case BUTTON_UP:
            omx = mx,omy = my;
            isLEFT = FALSE;
            break;
        default:
            omx = mx,omy = my;
            break;
    }
}
