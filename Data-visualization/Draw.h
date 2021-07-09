#include "conio.h"
#include "imgui.h"
#include "imgui.h"
#include "genlib.h"
#include "genlib.h"
#include "simpio.h"
#include "graphics.h"
#include "extgraph.h"
#include "graphics.h"

#include <math.h>
#include <ole2.h>
#include <ocidl.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <wingdi.h>
#include <olectl.h>
#include <winuser.h>
#include <windows.h>
#include <mmsystem.h>


#ifndef DRAW_H
#define DRAW_H

#define axis_begin_x 5        /* ��������ʼλ������x����*/
#define axis_begin_y 3        /* ��������ʼλ������y����*/
#define axis_end_x 15         /* ��������ʼλ������x����*/
#define axis_end_y 8          /* ��������ʼλ������y����*/

#define color_menu_begin_x 5  /* ��ɫ��Ϣ����ʼλ��������x����*/
#define color_menu_begin_y 1  /* ��ɫ��Ϣ����ʼλ��������y����*/
#define color_menu_end_x 15   /* ��ɫ��Ϣ����ʼλ��������x����*/
#define color_menu_end_y 2    /* ��ɫ��Ϣ����ʼλ��������y����*/

#define dot_r 0.04            /* dot_r: �������İ뾶*/
#define click_dot_r 0.05      /* click_dot_r: ѡ�е���Ӧ�뾶*/
#define array_width 0.1       /* array_width: ������Ŀ��*/
#define head_height 0.4       /* head_height: �������ͷ�߶�*/
#define head_width  1         /* head_width:  �������ͷ���*/
#define pie_r 2               /* pie_r: ����ͼ�뾶*/
#define PI 3.1415926          /* PI: ��*/
#define color_box 0.2         /* color_box: ��ɫ���ӵı߳�*/

#define min_height 0.05       /* min_height: ѡ����С�߶�,��ֵֹΪ0�ĵ㲻�ܱ�ѡ��*/

#define head_color "black"			   /* head_color: ͷ��ɫ*/
#define background_color "HummingBird" /* background_color: ���ӻ����򱳾���ɫ*/
#define backgraph_color "white"        /* backgraph_color: ȫͼ������ɫ*/


double draw_begin_x;          /* draw_begin_x: ��ͼ���x*/
double draw_begin_y;          /* draw_begin_y: ��ͼ���y*/

/*
*   x,y�Ŵ���ʣ�����
*   large_rate_x=2;
*   ��ʾÿ��x�����Ϊԭ������
*/
double large_rate_x;          /* large_rate_x: x�Ŵ����*/
double large_rate_y;          /* large_rate_y: y�Ŵ����*/


bool show_axis;               /* show_axis: չʾ������*/
bool show_pie;                /* show_pie:  չʾ����ͼ*/

int col_or_row;               /* col_or_row: ��ѡ���л����л�����ͼ 0 show col, 1 show row*/

double width_x;               /* width_x: ÿһ������Ŀ��*/
double each_bar_width;        /* each_bar_width: ÿ����������һ����״ͼ���*/
int draw_pie_num;             /* draw_pie_num: ���ݵڼ���/�л��ı���ͼ*/

/*
* Function: adapt_the_rate_y
* ����: ʹ��ʾ������Χ�ڵĵ��y������Ӧͼ�񣬶�����ͼ��չʾ����
* ����: ��
* ����ֵ: ��
* ������: Zerokei
*/
void adapt_the_rate_y(); 

/*
* Function: draw_again
* ����: �����ӻ��������»�һ��
* ����: ��
* ����ֵ: ��
* ������: Parfait
*/
void draw_again();

/*
* Function: start_draw
* ����: ��ͼ��ʼ��
* ����: ��
* ����ֵ: ��
* ������: Parfait
*/
void start_draw();

/*
* Function: init_color
* ����: ����ʾ����ɫ��ʼ��
* ����: ��
* ����ֵ: ��
* ������: Parfait
*/
void init_color();

#endif 