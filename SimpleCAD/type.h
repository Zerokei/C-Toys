/**************************
* written by Zerokei
* start date: 2021.4.19
* last date: 2021.4.21
***************************/
#include "genlib.h"
#ifndef TYPE_H
#define TYPE_H
/*
*			����Բ
* cx, cy	Բ������
* r			�뾶
*/
typedef struct New_Circle {
	double cx, cy;
	double l, r;
	string col;
}Circ, Circle;
/*
*			����ֱ��
* cx, cy	�̶�һ�� 
* l, r		����һ����Ϊ cx + l, cy + r
*/
typedef struct New_Line {
	double cx, cy;
	double l, r; 
	string col;
}Line;
/*
*			�������
* cx, cy	�̶�һ�㣨��ʼĬ��Ϊ���½ǣ�
* l, r		����
*/
typedef struct New_Rectangle {
	double cx, cy;
	double l, r;
	string col;
}Rect;
/*
*			�����ı�
* cx, cy	��ʼ��λ��
* str[]		�ı����ݣ�0��len - 1
* len		�ı�����
* pos		���λ�ã���һ���ı���λ��Ϊpos
* l, r		�ı��ĳ���
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