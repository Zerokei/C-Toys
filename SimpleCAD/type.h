/**************************
* written by Zerokei
* start date: 2021.4.19
* last date: 2021.4.21
***************************/
#include "genlib.h"
#ifndef TYPE_H
#define TYPE_H
/*
*			定义圆
* cx, cy	圆心坐标
* r			半径
*/
typedef struct New_Circle {
	double cx, cy;
	double l, r;
	string col;
}Circ, Circle;
/*
*			定义直线
* cx, cy	固定一点 
* l, r		另外一个点为 cx + l, cy + r
*/
typedef struct New_Line {
	double cx, cy;
	double l, r; 
	string col;
}Line;
/*
*			定义矩形
* cx, cy	固定一点（起始默认为左下角）
* l, r		长宽
*/
typedef struct New_Rectangle {
	double cx, cy;
	double l, r;
	string col;
}Rect;
/*
*			定义文本
* cx, cy	起始点位置
* str[]		文本内容，0到len - 1
* len		文本长度
* pos		光标位置，后一个文本的位置为pos
* l, r		文本的长宽
*/
typedef struct New_Text {
	double	cx, cy;
	char	str[100];
	int		len;
	int		pos;
	double  l, r;
	string col;
}Text;

/*
* definite List
*/
typedef struct New_List_of_Text {
	struct New_List_of_Text*	nxt;
	Text*		value;
}Text_list;
typedef struct New_List_of_Circ {
	struct New_List_of_Circ*	nxt;
	Circ*		value;
}Circ_list;
typedef struct New_List_of_Rect {
	struct New_List_of_Rect*	nxt;
	Rect*		value;
}Rect_list;
typedef struct New_List_of_Line {
	struct New_List_of_Line*	nxt;
	Line*		value;
}Line_list;
#endif // !TYPE_H