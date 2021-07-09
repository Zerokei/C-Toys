/**************************
* written by Zerokei
* start date: 2021.4.19
* last date: 2021.4.21
* function: draw easy images like lines, circles, rectangles and strings
***************************/
#include "graphics.h"
#include "extgraph.h"
#include "genlib.h"
#include "simpio.h"
#include "random.h"
#include "strlib.h"
#include "conio.h"
#include "type.h"
#include "function.h"
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

#define isNone 0
#define isLine 1
#define isRectangle 2
#define isCircle 3
#define isText 4

#define TIME_BLINK500 1
const int mseconds500 = 500;

/*����ͼ��Ԫ�ص�����*/
static Line_list* line_list;
static Rect_list* rect_list;
static Circ_list* circ_list;
static Text_list* text_list;
/*����ͼ��Ԫ�ص���ʱָ�룬ָ�����´�����Ԫ�ػ�������ʹ�õ�Ԫ��*/
static Line* line_ptr;
static Rect* rect_ptr;
static Circ* circ_ptr;
static Text* text_ptr;
/*�жϴ�ʱ�Ƿ����ı�����״̬*/
static bool Write_Flag = FALSE;
/*�Ƿ�Ϊ����Ҽ�����*/
static bool right_button = FALSE;
/*�Ƿ�Ϊ����������*/
static bool left_button = FALSE;
/*�Ƿ���ʾ���*/
static bool isDisplaycursor = TRUE;
/*��ǰѡ�е�ͼ��Ԫ�ص�����*/
static int selected_type = 0;
/*��ǰ���λ���뵱ǰ���λ��*/
static double px, py, nx, ny; // to record the position
/*��������*/
double wide_num, height_num;

void KeyboardEventProcess(int key, int event);/*������Ϣ�ص�����*/
void CharEventProcess(char c);/*�ַ���Ϣ�ص�����*/
void MouseEventProcess(int x, int y, int button, int event);/*�����Ϣ�ص�����*/
void TimerEventProcess(int timerID);/*��ʱ����Ϣ�ص�����*/

void Main() {
	/*ʹ��˵��*/
	InitConsole();
	printf("F1:����ֱ��\nF2:���ɾ���\nF3:����Բ\nF4:�����ı��������ı����ݺ󰴻س�ȷ��\n���:ѡ��ͼ�Σ���ѡ�е�ͼ����ʾ��ɫ��\n��ס����϶�:�ƶ�ѡ��ͼ��\n��ס�Ҽ��϶�:�ı�ѡ��ͼ�δ�С(�ı�����)\nEsc:�˳�ѡ��\n*����˵��*��ѡ��ͼ��ʱ�޷������µ�ͼ��\n�������ȷ����ʼ");
	getchar();
	FreeConsole();

	/*��ʽ��ʼ*/
	InitGraphics();
	
	wide_num = GetWindowWidth();
	height_num = GetWindowHeight();
	registerKeyboardEvent(KeyboardEventProcess);/*ע�������Ϣ�ص�����*/
	registerCharEvent(CharEventProcess);/*ע���ַ���Ϣ�ص�����*/
	registerMouseEvent(MouseEventProcess);/*ע�������Ϣ�ص�����*/
	registerTimerEvent(TimerEventProcess);/*ע�ᶨʱ����Ϣ�ص�����*/
	startTimer(TIME_BLINK500, mseconds500);/*500ms��ʱ������*/

	/*��ʼ��ͼ��Ԫ��ָ��*/
	line_list = (Line_list*)malloc(sizeof(Line_list));
	if(line_list!=NULL)line_list->nxt = NULL;
	rect_list = (Rect_list*)malloc(sizeof(Rect_list));
	if(rect_list!=NULL)rect_list->nxt = NULL;
	circ_list = (Circ_list*)malloc(sizeof(Circ_list));
	if(circ_list!=NULL)circ_list->nxt = NULL;
	text_list = (Text_list*)malloc(sizeof(Text_list));
	if(text_list!=NULL)text_list->nxt = NULL;

	return;
}

void KeyboardEventProcess(int key, int event) {
	switch (event) {
	case KEY_DOWN:
		if (Write_Flag == TRUE) {
			switch (key) {
			case VK_DELETE:
				delete_c_after_cursor(text_ptr);
				break;
			case VK_BACK:
				delete_c_before_cursor(text_ptr);
				break;
			case VK_LEFT:
				cursor_left(text_ptr);
				break;
			case VK_RIGHT:
				cursor_right(text_ptr);
				break;
			case VK_RETURN:
				Write_Flag = FALSE;
				clear_cursor(text_ptr);
				if (text_ptr->len == 0)
					delete_list_text(text_list, text_ptr);
				else calc_l_and_r(text_ptr);
				break;
			}
		}
		else{// Write_Flag == FALSE
			switch (key) {
			case VK_F1://generate a line
				if (selected_type)break;
				ClearAll();
				line_ptr = generate_line(line_list);
				Rewrite(line_list, rect_list, circ_list, text_list);
				break;
			case VK_F2://generate a rectangle
				if (selected_type)break;
				ClearAll();
				rect_ptr = generate_rect(rect_list);
				Rewrite(line_list, rect_list, circ_list, text_list); 
				break;
			case VK_F3://generate a circle
				if (selected_type)break;
				ClearAll();
				circ_ptr = generate_circ(circ_list);
				Rewrite(line_list, rect_list, circ_list, text_list); 
				break;
			case VK_F4://generate a text
				if (selected_type)break;
				ClearAll();
				text_ptr = generate_text(text_list);
				Rewrite(line_list, rect_list, circ_list, text_list); 
				Write_Flag = TRUE;
				break;
			case VK_BACK:
			case VK_DELETE:
				switch (selected_type) {
				case isNone:
					break;
				case isLine:
					selected_type = isNone;
					ClearAll();
					delete_list_line(line_list,line_ptr);
					Rewrite(line_list, rect_list, circ_list, text_list);
					break;
				case isRectangle:
					selected_type = isNone;
					ClearAll();
					delete_list_rect(rect_list,rect_ptr);
					Rewrite(line_list, rect_list, circ_list, text_list);
					break;
				case isCircle:
					selected_type = isNone;
					ClearAll();
					delete_list_circ(circ_list,circ_ptr);
					Rewrite(line_list, rect_list, circ_list, text_list);
					break;
				case isText:
					selected_type = isNone;
					ClearAll();
					delete_list_text(text_list,text_ptr);
					Rewrite(line_list, rect_list, circ_list, text_list);
					break;
				}
				break;
			case VK_ESCAPE:
				switch (selected_type) {
				case isLine:
					ClearAll();
					line_ptr->col = "Black";
					Rewrite(line_list, rect_list, circ_list, text_list);
					break;
				case isRectangle:
					ClearAll();
					rect_ptr->col = "Black";
					Rewrite(line_list, rect_list, circ_list, text_list);
					break;
				case isCircle:
					ClearAll();
					circ_ptr->col = "Black";
					Rewrite(line_list, rect_list, circ_list, text_list);
					break;
				case isText:
					ClearAll();
					text_ptr->col = "Black";
					Rewrite(line_list, rect_list, circ_list, text_list);
					break;
				}
				selected_type = isNone;
				break;
			}
		}
	}
}
void CharEventProcess(char c) {
	if (Write_Flag == FALSE) {
		return;
	}
	switch (c) {
	case '\r':
		break;
	case VK_BACK:
		break;
	default:
		ClearAll();
		insert_c_after_cursor(text_ptr, c);
		Rewrite(line_list, rect_list, circ_list, text_list);
		break;
	}
}
void MouseEventProcess(int x, int y, int button, int event) {
	if (Write_Flag == TRUE) return;
	switch (event) {
	case BUTTON_DOWN:
		px = ScaleXInches(x);
		py = ScaleYInches(y);
		if (button == LEFT_BUTTON) {
			if (selected_type == isNone) {
				Line* p1 = find_line(ScaleXInches(x), ScaleYInches(y), line_list);
				if (p1 != NULL) {
					line_ptr = p1;
					ClearAll();
					line_ptr->col = "Blue";
					Rewrite(line_list, rect_list, circ_list, text_list);
					selected_type = isLine;
					break;
				}
				Circ* p2 = find_circ(ScaleXInches(x), ScaleYInches(y), circ_list);
				if (p2 != NULL) {
					circ_ptr = p2;
					ClearAll();
					circ_ptr->col = "Blue";
					Rewrite(line_list, rect_list, circ_list, text_list);
					selected_type = isCircle;
					break;
				}
				Rect* p3 = find_rect(ScaleXInches(x), ScaleYInches(y), rect_list);
				if (p3 != NULL) {
					rect_ptr = p3;
					ClearAll();
					rect_ptr->col = "Blue";
					Rewrite(line_list, rect_list, circ_list, text_list);
					selected_type = isRectangle;
					break;
				}
				Text* p4 = find_text(ScaleXInches(x), ScaleYInches(y), text_list);
				if (p4 != NULL) {
					text_ptr = p4;
					ClearAll();
					text_ptr->col = "Blue";
					Rewrite(line_list, rect_list, circ_list, text_list);
					selected_type = isText;
					break;
				}
			}
			left_button = TRUE;
		}
		else if (button == RIGHT_BUTTON) {
			right_button = TRUE;
		}
		break;
	case MOUSEMOVE:
		nx = ScaleXInches(x), ny = ScaleYInches(y);
		
		if (left_button == TRUE) {//�ƶ�
			switch (selected_type) {
			case isLine:
				ClearAll();
				line_ptr->cx += (nx - px);
				line_ptr->cy += (ny - py);
				Rewrite(line_list, rect_list, circ_list, text_list);
				break;
			case isRectangle:
				ClearAll();
				rect_ptr->cx += (nx - px);
				rect_ptr->cy += (ny - py);
				Rewrite(line_list, rect_list, circ_list, text_list);
				break;
			case isCircle:
				ClearAll();
				circ_ptr->cx += (nx - px);
				circ_ptr->cy += (ny - py);
				Rewrite(line_list, rect_list, circ_list, text_list);
				break;
			case isText:
				ClearAll();
				text_ptr->cx += (nx - px);
				text_ptr->cy += (ny - py);
				Rewrite(line_list, rect_list, circ_list, text_list);
				break;
			}
		}
		else if (right_button == TRUE) {
			switch (selected_type) {
			case isLine:
				ClearAll();
				line_ptr->l += (nx - px);
				line_ptr->r += (ny - py);
				Rewrite(line_list, rect_list, circ_list, text_list);
				break;
			case isRectangle:
				ClearAll();
				rect_ptr->l += (nx - px);
				rect_ptr->r += (ny - py);
				Rewrite(line_list, rect_list, circ_list, text_list);
				break;
			case isCircle:
				ClearAll();
				circ_ptr->l += (nx - px);
				circ_ptr->r += (ny - py);
				Rewrite(line_list, rect_list, circ_list, text_list);
				break;
			case isText:
				ClearAll();
				text_ptr->cx += (nx - px);
				text_ptr->cy += (ny - py);
				Rewrite(line_list, rect_list, circ_list, text_list);
				break;
			}
		}
		px = nx, py = ny;
		break;
	case BUTTON_UP:
		left_button = FALSE;
		right_button = FALSE;
	}
}
void TimerEventProcess(int timerID) {
	switch (timerID) {
	case TIME_BLINK500: /*500ms�ı���˸��ʱ��*/
		if (!Write_Flag)break;
		MovePen(nx + 0.005, ny - 0.01);/*��ʼλ��*/
		if (isDisplaycursor == TRUE)
			draw_cursor(text_ptr);
		else clear_cursor(text_ptr);
		isDisplaycursor = !isDisplaycursor;/*������ʾ/�����ַ�������*/
		break;
	}
}