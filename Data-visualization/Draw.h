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

#define axis_begin_x 5        /* 坐标轴起始位置左下x坐标*/
#define axis_begin_y 3        /* 坐标轴起始位置左下y坐标*/
#define axis_end_x 15         /* 坐标轴起始位置右上x坐标*/
#define axis_end_y 8          /* 坐标轴起始位置右上y坐标*/

#define color_menu_begin_x 5  /* 颜色信息栏起始位置坐左下x坐标*/
#define color_menu_begin_y 1  /* 颜色信息栏起始位置坐左下y坐标*/
#define color_menu_end_x 15   /* 颜色信息栏起始位置坐右上x坐标*/
#define color_menu_end_y 2    /* 颜色信息栏起始位置坐右上y坐标*/

#define dot_r 0.04            /* dot_r: 点阵里点的半径*/
#define click_dot_r 0.05      /* click_dot_r: 选中点响应半径*/
#define array_width 0.1       /* array_width: 坐标轴的宽度*/
#define head_height 0.4       /* head_height: 坐标轴箭头高度*/
#define head_width  1         /* head_width:  坐标轴箭头宽度*/
#define pie_r 2               /* pie_r: 饼形图半径*/
#define PI 3.1415926          /* PI: Π*/
#define color_box 0.2         /* color_box: 颜色格子的边长*/

#define min_height 0.05       /* min_height: 选中最小高度,防止值为0的点不能被选中*/

#define head_color "black"			   /* head_color: 头颜色*/
#define background_color "HummingBird" /* background_color: 可视化区域背景颜色*/
#define backgraph_color "white"        /* backgraph_color: 全图背景颜色*/


double draw_begin_x;          /* draw_begin_x: 画图起点x*/
double draw_begin_y;          /* draw_begin_y: 画图起点y*/

/*
*   x,y放大比率，比如
*   large_rate_x=2;
*   表示每个x坐标变为原来两倍
*/
double large_rate_x;          /* large_rate_x: x放大比率*/
double large_rate_y;          /* large_rate_y: y放大比率*/


bool show_axis;               /* show_axis: 展示坐标轴*/
bool show_pie;                /* show_pie:  展示饼形图*/

int col_or_row;               /* col_or_row: 用选中行还是列画饼形图 0 show col, 1 show row*/

double width_x;               /* width_x: 每一个区间的宽度*/
double each_bar_width;        /* each_bar_width: 每个区间内内一个柱状图宽度*/
int draw_pie_num;             /* draw_pie_num: 根据第几列/行画的饼形图*/

/*
* Function: adapt_the_rate_y
* 功能: 使显示在区域范围内的点的y坐标适应图像，都能在图中展示出来
* 参数: 无
* 返回值: 无
* 创建人: Zerokei
*/
void adapt_the_rate_y(); 

/*
* Function: draw_again
* 功能: 将可视化部分重新画一遍
* 参数: 无
* 返回值: 无
* 创建人: Parfait
*/
void draw_again();

/*
* Function: start_draw
* 功能: 画图初始化
* 参数: 无
* 返回值: 无
* 创建人: Parfait
*/
void start_draw();

/*
* Function: init_color
* 功能: 将显示的颜色初始化
* 参数: 无
* 返回值: 无
* 创建人: Parfait
*/
void init_color();

#endif 