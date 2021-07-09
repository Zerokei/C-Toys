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
#define TIMER_BLINK500  1     /*500ms��ʱ���¼���־��*/
static const int mseconds500 = 500;

static char str[] = {0, 0};
static char text[100]; /*�ı�����*/
static int textlen = 0; /*�ı�����*/
static double Ix = 0.0, Iy = 0.0; // ð��λ�� 
static double nx = 0.0, ny = 0.0; // ���λ��
static int npos = 0; // �����ָ�����ĸ
static bool isDisplayText = 0;// �����˸��־ 
static const double initial_x = 0.5;//ð�ŵ�λ��: 
static const double initial_y = 5.0;//ð�ŵ�λ��: 
void KeyboardEventProcess(int key,int event);/*������Ϣ�ص�����*/
void CharEventProcess(char c);/*�ַ���Ϣ�ص�����*/
void eraseText(int sta);/*ɾ���ı������*/
void printText(char c);/*�����ǰ���֣��ƶ�nx,ny*/
void recoverSentence(int sta);/*�ָ�����յ��ı������*/
void fillRectangle(double x, double y, double w, double h);/*��䳤����*/
void TimerEventProcess(int timerID);/*��ʱ����Ϣ�ص�����*/
void del_npos();/*���λ�������ƶ�*/ 
void add_npos();/*���λ�������ƶ�*/
void EraseLine();/*�����˸������*/ 

void Main(){
    
    InitGraphics();        	
	
	/*�ص�*/
	registerKeyboardEvent(KeyboardEventProcess);/*ע�������Ϣ�ص�����*/
	registerCharEvent(CharEventProcess);/*ע���ַ���Ϣ�ص�����*/
	registerTimerEvent(TimerEventProcess);/*ע�ᶨʱ����Ϣ�ص�����*/
    startTimer(TIMER_BLINK500, mseconds500);/*500ms��ʱ������*/
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
                        /*�ƶ���� */
                    }
                    break;
                case VK_LEFT:
                    if(npos > 0){
                        str[0] = text[npos - 1];
                        del_npos();
                        nx = GetCurrentX() - TextStringWidth(str);/*�����ַ�������ʼ����*/
                        MovePen(nx, ny);
                    }
                    break;
                case VK_RIGHT:
                    if(npos < textlen){
                        str[0] = text[npos];
                        add_npos(); 
                        nx = GetCurrentX() + TextStringWidth(str);/*�����ַ�������ʼ����*/
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
    MovePen(Ix + TextStringWidth(text), Iy);/*�����ַ�������ʼ����*/
    
    SetEraseMode(TRUE);
    for(i = textlen - 1; i >= sta; --i){
        str[0] = text[i];
        textx = GetCurrentX() - TextStringWidth(str);/*�����ַ�������ʼ����*/
		texty = GetCurrentY();
		fillRectangle(textx, texty, TextStringWidth(str), 0.5);
    }
    
    SetEraseMode(FALSE);
}


void printText(char c){

    /*�����ַ�*/ 
    int i;
    for(i = textlen; i > npos; --i){
        text[i] = text[i-1];
    }
    /*����ַ�*/
    text[npos] = c;
    str[0] = text[npos];
    DrawTextString(str); 
    /*����ƶ�*/ 
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
    StartFilledRegion(1); // ��ʼ
        DrawLine(0, h);
        DrawLine(w, 0);
        DrawLine(0, -h);
        DrawLine(-w, 0);
    EndFilledRegion();   // ����
}

void EraseLine(){//�����˸������ 
    bool erasemode = GetEraseMode();
    double px = GetCurrentX(), py = GetCurrentY();
    SetEraseMode(TRUE);/*���ݵ�ǰ��ʾ��־����������ʾ���������ַ���*/
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
	    case TIMER_BLINK500: /*500ms�ı���˸��ʱ��*/
    	    erasemode = GetEraseMode();
    	    double px = GetCurrentX(), py = GetCurrentY();
            MovePen(nx + 0.005, ny - 0.01);/*��ʼλ��*/
            SetEraseMode(isDisplayText);/*���ݵ�ǰ��ʾ��־����������ʾ���������ַ���*/
    		DrawLine(0,0.13);
    		MovePen(px,py);
    	    SetEraseMode(erasemode);
    		isDisplayText = !isDisplayText;/*������ʾ/�����ַ�������*/
    		break;
	    default:
		    break;
	}
}

