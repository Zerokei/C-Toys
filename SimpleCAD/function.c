/**************************
* written by Zerokei
* start date: 2021.4.19
* last date: 2021.4.21
***************************/

#include "type.h"
#include "graphics.h"
#include "extgraph.h"
#include "genlib.h"
#include "simpio.h"
#include "random.h"
#include "strlib.h"
#include "conio.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stddef.h>
#include <windows.h>
#include <olectl.h>
#include <mmsystem.h>
#include <wingdi.h>
#include <ole2.h>
#include <ocidl.h>
#include <winuser.h>
#include <time.h>
#include <string.h>

/*
*	generate
*/
extern double wide_num;
extern double height_num;

//	generate x, y, l, r
double generate_x() {
	srand((unsigned)time(NULL));
	return (rand() % 32 + 10) / 96.0 * wide_num;
}
double generate_y() {
	srand((unsigned)time(NULL));
	return (rand() % 32 + 10) / 96.0 * height_num;
}
double generate_l() {
	srand((unsigned)time(NULL));
	rand();
	return (rand() % 20 + 5) / 60.0 * wide_num;
}
double generate_r() {
	srand((unsigned)time(NULL));
	return (rand() % 20 + 5) / 60.0 * height_num;
}
//	generate rect circ line text
Rect* generate_rect(Rect_list* p) {
	Rect_list* q = (Rect_list*)malloc(sizeof (Rect_list));
	if(q!=NULL)q->nxt = NULL;
	Rect* node = (Rect*)malloc(sizeof(Rect));
	if (node != NULL)node->cx = generate_x(), node->cy = generate_y(), node->l = generate_l(), node->r = generate_r(), node->col = "Black";
	while (p->nxt) p = p->nxt;
	p->nxt = q;
	if(q!=NULL)q->value = node;
	return node;
}
Line* generate_line(Line_list* p) {
	Line_list* q = (Line_list*)malloc(sizeof(Line_list));
	if(q!=NULL)q->nxt = NULL;
	Line* node = (Line*)malloc(sizeof(Line));
	if(node!=NULL)node->cx = generate_x(), node->cy = generate_y(), node->l = generate_l(), node->r = generate_r(), node->col = "Black";
	while (p->nxt) p = p->nxt;
	p->nxt = q;
	if(q!=NULL)q->value = node;
	return node;
}
Circ* generate_circ(Circ_list* p) {
	Circ_list* q = (Circ_list*)malloc(sizeof(Circ_list));
	if(q!=NULL)q->nxt = NULL;
	Circ* node = (Circ *)malloc(sizeof(Circ));
	if(node!=NULL)node->cx = generate_x(), node->cy = generate_y(), node->l = generate_l(), node->r = generate_r(), node->col = "Black";
	while (p->nxt) p = p->nxt;
	p->nxt = q;
	if(q!=NULL)q->value = node;
	return node;
}
Text* generate_text(Text_list* p) {
	Text_list* q = (Text_list*)malloc(sizeof(Text_list));
	Text *node = (Text*)malloc(sizeof (Text));
	if(node!=NULL)node->cx = generate_x(),node->cy = generate_y(),node->len = 0,node->pos = 0,node->l = 0,node->r = 0,node->col = "Black";
	if(q!=NULL)q->nxt = NULL;
	while (p->nxt) p = p->nxt;
	p->nxt = q;
	if(q!=NULL)q->value = node;
	return node;
}
//	delete line rect circ text from list
void delete_list_circ(Circ_list* p, Circ* tar) {
	while ((p->nxt)->value != tar && p != NULL) p = p->nxt;
	if (p == NULL)return;
	p->nxt = p->nxt->nxt;
}
void delete_list_line(Line_list* p, Line* tar) {
	while ((p->nxt)->value != tar && p != NULL) p = p->nxt;
	if (p == NULL)return;
	p->nxt = p->nxt->nxt;
}
void delete_list_rect(Rect_list* p, Rect* tar) {
	while ((p->nxt)->value != tar && p != NULL) p = p->nxt;
	if (p == NULL)return;
	p->nxt = p->nxt->nxt;
}
void delete_list_text(Text_list* p, Text* tar) {
	while ((p->nxt)->value != tar && p != NULL) p = p->nxt;
	if (p == NULL)return;
	p->nxt = p->nxt->nxt;
}
// delete and draw circle
void d_circ(Circ *a) {
	double px = GetCurrentX();
	double py = GetCurrentY();
	MovePen(a->cx + a->l, a->cy);
	DrawEllipticalArc(a->l, a->r, 0.0, 360.0);
	MovePen(px, py);
}
void delete_circ(Circ* p) {
	SetPenColor("White");
	d_circ(p);
}
void draw_circ(Circ* p) {
	SetPenColor(p->col);
	d_circ(p);
}
// delete and draw line
void d_line(Line *a) {
	double px = GetCurrentX();
	double py = GetCurrentY();
	MovePen(a->cx, a->cy);
	DrawLine(a->l,a->r);
	MovePen(px, py);
}
void delete_line(Line* p) {
	SetPenColor("White");
	d_line(p);
}
void draw_line(Line* p) {
	SetPenColor(p->col);
	d_line(p);
}
// delete and draw rectangle
void d_rect(Rect *a) {
	MovePen(a->cx, a->cy);
	DrawLine(a->l, 0);
	DrawLine(0, a->r);
	DrawLine(-a->l, 0);
	DrawLine(0, -a->r);
}
void delete_rect(Rect* p) {
	SetPenColor("White");
	d_rect(p);
}
void draw_rect(Rect* p) {
	SetPenColor(p->col);
	d_rect(p);
}
// delete and draw text
void d_text(Text *a) {
	char c[2] = {0, 0};
	double px = GetCurrentX();
	double py = GetCurrentY();
	MovePen(a->cx, a->cy);
	int i;
	for (i = 0; i < a->len; ++i) {
		c[0] = a->str[i];
		DrawTextString(c);
	}
	MovePen(px, py);
}
void delete_text(Text* p) {
	SetPenColor("White");
	d_text(p);
}
void draw_text(Text* p) {
	SetPenColor(p->col);
	d_text(p);
}
void Rewrite(Line_list* p1, Rect_list* p2, Circ_list* p3, Text_list* p4) {
	for (p1 = p1->nxt; p1; p1 = p1->nxt) {
		draw_line(p1->value);
	}
	for (p2 = p2->nxt; p2; p2 = p2->nxt) {
		draw_rect(p2->value);
	}
	for (p3 = p3->nxt; p3; p3 = p3->nxt) {
		draw_circ(p3->value);
	}
	for (p4 = p4->nxt; p4; p4 = p4->nxt) {
		draw_text(p4->value);
	}
}
void ClearAll() {
	SetPenColor("White");
	double px = GetCurrentX(), py = GetCurrentY();
	MovePen(0, 0);
	StartFilledRegion(1); // ¿ªÊ¼
	DrawLine(0, height_num);
	DrawLine(wide_num, 0);
	DrawLine(0, -height_num);
	DrawLine(-wide_num, 0);
	EndFilledRegion();   // ½áÊø
	MovePen(px, py);
}
//	judge is cursor is in the things
double dist(double x1, double y1, double x2, double y2) {
	return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}
bool in_circ(double nx, double ny, Circ* a) {
	return ((nx - a->cx) * (nx - a->cx)) / (a->l * a->l) + ((ny - a->cy) * (ny - a->cy)) / (a->r * a->r) <= 1;
}
bool in_rect(double nx, double ny, Rect* a) {
	double x1 = a->cx, x2 = x1 + a->l, y1 = a->cy, y2 = y1 + a->r;
	return (nx - x1) * (nx - x2) <= 0 && (ny - y1) * (ny - y2) <= 0;
}
bool in_text(double nx, double ny, Text* a) {
	double x1 = a->cx, x2 = x1 + a->l, y1 = a->cy, y2 = y1 + a->r;
	return (nx - x1) * (nx - x2) <= 0 && (ny - y1) * (ny - y2) <= 0;
}
bool in_line(double nx, double ny, Line* a) {
	double x1 = a->cx, x2 = x1 + a->l, y1 = a->cy, y2 = y1 + a->r;
	return (nx - x1) * (nx - x2) <= 0 && (ny - y1) * (ny - y2) <= 0;
}
Circ* find_circ(double nx, double ny, Circ_list* p) {
	p = p->nxt;
	for (; p != NULL; p = p->nxt) {
		if (in_circ(nx, ny, p->value)) {
			return p->value;
		}
	}
	return NULL;
}
Text* find_text(double nx, double ny, Text_list* p) {
	p = p->nxt;
	for (; p != NULL; p = p->nxt) {
		if (in_text(nx, ny, p->value)) {
			return p->value;
		}
	}
	return NULL;
}
Line* find_line(double nx, double ny, Line_list* p) {
	p = p->nxt;
	for (; p != NULL; p = p->nxt) {
		if (in_line(nx, ny, p->value)) {
			return p->value;
		}
	}
	return NULL;
}
Rect* find_rect(double nx, double ny, Rect_list* p) {
	p = p->nxt;
	for (; p != NULL; p = p->nxt) {
		if (in_rect(nx, ny, p->value)) {
			return p->value;
		}
	}
	return NULL;
}
//	functions of text
double find_pos_of_cursor(Text* a) {
	char c[] = { 0, 0 };
	int i;
	double x = a->cx;
	char* s = a->str;
	for (i = 0; i < a->pos; ++i) {
		c[0] = s[i];
		x += TextStringWidth(c);
	}
	return x;
}
void draw_cursor(Text* a) {
	SetPenColor("Black");
	double nx = find_pos_of_cursor(a);
	double ny = a->cy;
	double px = GetCurrentX();
	double py = GetCurrentY();
	MovePen(nx, ny);
	DrawLine(0, 0.13);
	MovePen(px, py);
}
void clear_cursor(Text* a) {
	SetPenColor("White");
	double nx = find_pos_of_cursor(a);
	double ny = a->cy;
	double px = GetCurrentX();
	double py = GetCurrentY();
	MovePen(nx, ny);
	DrawLine(0, 0.13);
	MovePen(px, py);
}
void cursor_left(Text* a) {
	if (a->pos == 0)return;
	clear_cursor(a);
	a->pos--;
}
void cursor_right(Text* a) {
	if (a->pos == a->len)return;
	clear_cursor(a);
	a->pos++;
}
void calc_l_and_r(Text* a) {
	(a->str)[a->len] = '\0';
	a->l = TextStringWidth(a->str);
	a->r = 0.5;
}
void delete_c_after_cursor(Text* a) {
	if (a->pos == a->len)return;
	delete_text(a);
	char* c = a->str;
	int i;
	for (i = a->pos; i < (a->len); i++) c[i] = c[i + 1];
	(a->len)--;
	c[a->len] = '\0';
	draw_text(a);
}
void delete_c_before_cursor(Text* a) {
	if (a->pos == 0)return;
	clear_cursor(a);
	delete_text(a);
	char* c = a->str;
	int i;
	for (i = a->pos - 1; i < (a->len); i++) c[i] = c[i + 1];
	(a->len)--;
	c[a->len] = '\0';
	cursor_left(a);
	draw_text(a);
}
void insert_c_after_cursor(Text* a, char c) {
	clear_cursor(a);
	char* s = a->str;
	int i;
	for (i = a->len; i > (a->pos); i--) s[i] = s[i - 1];
	s[a->pos] = c;
	(a->len)++;
	s[a->len] = '\0';
	cursor_right(a);
}