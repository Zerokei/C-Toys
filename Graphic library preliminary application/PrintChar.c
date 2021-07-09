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

#define debug() printf("%f %f\n", nx, ny)
#define TIMER_BLINK500  1     /*500ms定时器事件标志号*/
static const int mseconds500 = 500;

static char str[] = {0, 0};
static char text[100]; /*文本缓存*/
static int textlen = 0; /*文本长度*/
static double Ix = 0.0, Iy = 0.0; // 冒号位置 
static double nx = 0.0, ny = 0.0; // 光标位置
static int npos = 0; // 光标所指向的字母
static bool isDisplayText = 0;// 光标闪烁标志 
static const double initial_x = 0.5;//冒号的位置: 
static const double initial_y = 5.0;//冒号的位置: 
void KeyboardEventProcess(int key,int event);/*键盘消息回调函数*/
void CharEventProcess(char c);/*字符消息回调函数*/
void eraseText(int sta);/*删除文本，左闭*/
void printText(char c);/*输出当前文字，移动nx,ny*/
void recoverSentence(int sta);/*恢复被清空的文本，左闭*/
void fillRectangle(double x, double y, double w, double h);/*填充长方形*/
void TimerEventProcess(int timerID);/*定时器消息回调函数*/
void del_npos();/*光标位置向左移动*/ 
void add_npos();/*光标位置向右移动*/
void EraseLine();/*清除闪烁光标的线*/ 

void Main(){
    
    InitGraphics();        	
	
	/*回调*/
	registerKeyboardEvent(KeyboardEventProcess);/*注册键盘消息回调函数*/
	registerCharEvent(CharEventProcess);/*注册字符消息回调函数*/
	registerTimerEvent(TimerEventProcess);/*注册定时器消息回调函数*/
    startTimer(TIMER_BLINK500, mseconds500);/*500ms定时器触发*/
    MovePen(initial_x, initial_y);
	char initial_text[] = "Input: ";
	DrawTextString(initial_text);
	Ix = nx = GetCurrentX();
	Iy = ny = GetCurrentY();
	
    return;
}

void CharEventProcess(char c){
    if(c == VK_BACK) return;
    switch(c){
        case '\r':
            InitConsole();
            //FreeGraphics();
            int i; 
            for(i = 0; i < textlen; ++i){
                printf("%c", text[i]);
            }
            break;
        default :
            eraseText(npos);
            
            printText(c);
            
            recoverSentence(npos);
            break;
    }
}
void KeyboardEventProcess(int key,int event){
    switch(event){
        case KEY_DOWN:
            switch(key){
                case VK_DELETE:
                    if(npos < textlen){
                        eraseText(npos);
                        int i;
                        for(i = npos; i < textlen; ++i){
                            text[i] = text[i + 1];
                        }
                        textlen--;
                        recoverSentence(npos);
                    }
                    break;
                case VK_BACK:
                    if(npos > 0){
                        del_npos();
                        str[0] = text[npos - 1];
                        nx = nx - TextStringWidth(str);
                        eraseText(npos);
                        
                        int i;
                        for(i = npos; i < textlen; ++i){
                            text[i] = text[i + 1];
                        } 
                        textlen--;
                        
                        recoverSentence(npos);
                        /*移动光标 */
                    }
                    break;
                case VK_LEFT:
                    if(npos > 0){
                        str[0] = text[npos - 1];
                        del_npos();
                        nx = GetCurrentX() - TextStringWidth(str);/*设置字符串的起始坐标*/
                        MovePen(nx, ny);
                    }
                    break;
                case VK_RIGHT:
                    if(npos < textlen){
                        str[0] = text[npos];
                        add_npos(); 
                        nx = GetCurrentX() + TextStringWidth(str);/*设置字符串的起始坐标*/
                        MovePen(nx, ny);
                    }
                    break;
            }
        case KEY_UP:
            break; 
    }
}

void eraseText(int sta){ // erase [sta, textlen] 
    static double textx, texty;
    int i;
    text[textlen] = '\0';
    MovePen(Ix + TextStringWidth(text), Iy);/*设置字符串的起始坐标*/
    
    SetEraseMode(TRUE);
    for(i = textlen - 1; i >= sta; --i){
        str[0] = text[i];
        textx = GetCurrentX() - TextStringWidth(str);/*设置字符串的起始坐标*/
		texty = GetCurrentY();
		fillRectangle(textx, texty, TextStringWidth(str), 0.5);
    }
    
    SetEraseMode(FALSE);
}


void printText(char c){

    /*插入字符*/ 
    int i;
    for(i = textlen; i > npos; --i){
        text[i] = text[i-1];
    }
    /*输出字符*/
    text[npos] = c;
    str[0] = text[npos];
    DrawTextString(str); 
    /*光标移动*/ 
    add_npos();
    textlen++;
    nx = GetCurrentX();
    ny = GetCurrentY();
}

void recoverSentence(int sta){
    int i = 0;
    for(i = sta; i < textlen; ++i){
        str[0] = text[i];
        DrawTextString(str);    
    }
    MovePen(nx, ny);
}

void fillRectangle(double x, double y, double w, double h){
    MovePen(x, y);
    StartFilledRegion(1); // 开始
        DrawLine(0, h);
        DrawLine(w, 0);
        DrawLine(0, -h);
        DrawLine(-w, 0);
    EndFilledRegion();   // 结束
}

void EraseLine(){//清除闪烁光标的线 
    bool erasemode = GetEraseMode();
    double px = GetCurrentX(), py = GetCurrentY();
    SetEraseMode(TRUE);/*根据当前显示标志来决定是显示还是隐藏字符串*/
    MovePen(nx + 0.005,ny - 0.01);
    DrawLine(0,0.13);
    SetEraseMode(erasemode);
    MovePen(px,py);
}

void del_npos(){
    EraseLine();
    npos--;
}
void add_npos(){
    EraseLine();
    npos++;
}

void TimerEventProcess(int timerID){
    bool erasemode;
    switch (timerID) {
	    case TIMER_BLINK500: /*500ms文本闪烁定时器*/
    	    erasemode = GetEraseMode();
    	    double px = GetCurrentX(), py = GetCurrentY();
            MovePen(nx + 0.005, ny - 0.01);/*起始位置*/
            SetEraseMode(isDisplayText);/*根据当前显示标志来决定是显示还是隐藏字符串*/
    		DrawLine(0,0.13);
    		MovePen(px,py);
    	    SetEraseMode(erasemode);
    		isDisplayText = !isDisplayText;/*交替显示/隐藏字符串符号*/
    		break;
	    default:
		    break;
	}
}

