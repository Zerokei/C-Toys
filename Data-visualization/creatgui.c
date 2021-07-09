#include "Draw.h"
#include "conio.h"
#include "imgui.h"
#include "Table.h"
#include "simpio.h"
#include "genlib.h"
#include "graphics.h"
#include "extgraph.h"
#include "FileControl.h"

#include <ole2.h>
#include <ocidl.h>
#include <stdio.h>
#include <stdlib.h>
#include <olectl.h>
#include <wingdi.h>
#include <stddef.h>
#include <stdbool.h>
#include <windows.h>
#include <mmsystem.h>
#include <winuser.h>

#define GUI_MENU
#define GUI_BUTTON
#define GUI_Graphics

bool file_open;						/* file_open: �Ƿ���ļ�*/
FILE* file_ptr;						/* file_ptr: �򿪵��ļ�ָ��*/
int current_row;					/* current_row: ��ǰѡ����*/
int current_col;					/* current_col: ��ǰѡ����*/
Table* Mytable = NULL;				/* Mytable: �򿪵����ݱ�*/
static bool flag = false;			/* flag: xxx*/
static bool flag2 = false;			/* flag2:xxx*/
static bool is_clear = true;		/* is_clear: �����־*/
static bool is_change = false;		/* is_change: ѡ����ʾ����ͼ���Ǳ���ͼ*/
static bool is_changebutton = false;/* is_changebutton: xxx*/
static double winwidth, winheight;  /* ���ڳߴ� winwidth: ���ڿ��, winheight: ���ڸ߶�*/

/*��������*/
static void drawMenu();
static void display();
static void drawText();

/*
* Function:		Beautify
* ����:			xxx
* ����:			��
* ����ֵ:		��
* ������:		Ivan
*/
static void Beautify()
{
	/*��ɫϵ*/
	DefineColor("CuriousBlue", 0.20, 0.59, 0.86);
	DefineColor("HummingBird", 0.77, 0.94, 0.97);
	DefineColor("AliceBlue", 0.89, 0.945, 0.996);
	DefineColor("IrisBlue", 0.0, 0.71, 0.8);
	DefineColor("DodgerBlue", 0.13, 0.654, 0.94);
	/*��ɫϵ*/
	DefineColor("NYPink", 0.88, 0.51, 0.51);
	DefineColor("SoftColor", 0.925, 0.39, 0.29);
	DefineColor("Scarlet", 0.95, 0.15, 0.075);
	DefineColor("SunsetOrange", 0.964, 0.278, 0.278);
	/*��ɫϵ*/
	DefineColor("LightWisteria", 0.745, 0.564, 0.83);
	DefineColor("ElectricPurple", 0.647, 0.215, 0.992);
	/*��ɫϵ*/
	DefineColor("BrightTurquoise", 0.16, 0.945, 0.764);
	DefineColor("LightGreen", 0.48, 0.937, 0.70);
	DefineColor("Gossip", 0.53, 0.83, 0.486);
	/*��ɫϵ*/
	DefineColor("CapeHoney", 0.992, 0.929, 0.654);
	DefineColor("TahitiGold", 0.91, 0.494, 0.015);
	DefineColor("Turbo", 0.96, 0.90, 0.105);
	DefineColor("MoonGlow", 0.996, 0.98, 0.83);
}

/*
* Function:		clear_open_status
* ����:			������ļ���״̬
* ����:			��
* ����ֵ:		��
* ������:		Zerokei
*/
static void clear_open_status() {
	file_ptr = NULL;
	file_open = FALSE;
	Mytable = NULL;
	current_col = 0;
	current_row = 0;
}

/*
* Function:		to_open_file
* ����:			���ļ�
* ����:			��
* ����ֵ:		bool, �Ƿ�ɹ���
* ������:		Zerokei
*/
static bool to_open_file() {
	if (file_open)
		return FALSE;
	else {
		start_draw();
		file_ptr = Open_File();
		file_open = TRUE;
		Mytable = Generate_Table();
		bool flag = Table_input(Mytable, file_ptr);
		adapt_the_rate_y();
		draw_again();
		return flag;
	}
}

/*
* Function:		to_create_file
* ����:			�����ļ�
* ����:			��
* ����ֵ:		bool, �Ƿ�ɹ�����
* ������:		Zerokei
*/
static bool to_create_file() {
	if (file_open)
		return FALSE;
	else {
		start_draw();
		file_ptr = Create_File();
		file_open = TRUE;
		Mytable = Generate_Table();
		adapt_the_rate_y();
		draw_again();
		return TRUE;
	}
}

/*
* Function:		to_close_file
* ����:			�ر��ļ�
* ����:			��
* ����ֵ:		bool, �Ƿ�ɹ��ر�
* ������:		Zerokei
*/
static bool to_close_file() {
	if (!file_open) {
		return FALSE;
	}
	else {
		Close_File(file_ptr);
		clear_open_status();
		drawText();
		draw_again();
		return TRUE;
	}
}

/*
* Function:		to_save_file
* ����:			�����ļ�
* ����:			��
* ����ֵ:		bool, �Ƿ�ɹ�����
* ������:		Zerokei
*/
static  bool to_save_file() {
	bool flag = Save_File(file_ptr, Mytable);
	draw_again();
	return flag;
}

/*
* Function:		to_save_file_as
* ����:			���Ϊ�ļ�
* ����:			��
* ����ֵ:		bool, �Ƿ�ɹ����Ϊ
* ������:		Zerokei
*/
static bool to_save_file_as() {
	bool flag = Save_File_as(&file_ptr, Mytable);
	draw_again();
	return flag;
}

/*
* Function:		to_display_as_bar
* ����:			����ǰѡ�е��и�Ϊ������ʾ
* ����:			��
* ����ֵ:		bool, �Ƿ�ɹ��ı�
* ������:		Zerokei
*/
static bool to_display_as_bar() {
	bool rt = let_it_show_bar(Mytable, current_row);
	draw_again();
	return rt;
}

/*
* Function:		to_display_as_line
* ����:			����ǰѡ�е��и�Ϊ������ʾ
* ����:			��
* ����ֵ:		bool, �Ƿ�ɹ��ı�
* ������:		Zerokei
*/
static bool to_display_as_line() {
	bool rt = let_it_show_line(Mytable, current_row);
	draw_again();
	return rt;
}

/*
* Function:		to_display_as_dot
* ����:			����ǰѡ�е��и�Ϊ������ʾ
* ����:			��
* ����ֵ:		bool, �Ƿ�ɹ��ı�
* ������:		Zerokei
*/
static bool to_display_as_dot() {
	bool rt = let_it_show_dot(Mytable, current_row);
	draw_again();
	return rt;
}

/*
* Function:		to_show_bar
* ����:			������ʹ������ͼ��ʾ
* ����:			��
* ����ֵ:		bool, �Ƿ�ɹ���ʾ
* ������:		Zerokei
*/
static void to_show_bar() {
	show_axis = TRUE;
	show_pie = FALSE;
	table_show_bar(Mytable);
	draw_again();
}

/*
* Function:		to_show_line
* ����:			������ʹ������ͼ��ʾ
* ����:			��
* ����ֵ:		bool, �Ƿ�ɹ���ʾ
* ������:		Zerokei
*/
static void to_show_line() {
	show_axis = TRUE;
	show_pie = FALSE;
	table_show_line(Mytable);
	draw_again();
}

/*
* Function:		to_show_dot
* ����:			������ʹ�õ���ͼ��ʾ
* ����:			��
* ����ֵ:		bool, �Ƿ�ɹ���ʾ
* ������:		Zerokei
*/
static void to_show_dot() {
	show_axis = TRUE;
	show_pie = FALSE;
	table_show_dot(Mytable);
	draw_again();
}

/*
* Function:		to_show_pie
* ����:			������ʹ�ñ���ͼ��ʾ
* ����:			��
* ����ֵ:		bool, �Ƿ�ɹ���ʾ
* ������:		Zerokei
*/
static void to_show_pie() {
	show_axis = FALSE;
	show_pie = TRUE;
	draw_again();
}

/*
* Function:		to_change_row_name
* ����:			�ı�ѡ���е�����
* ����:			��
* ����ֵ:		bool, �Ƿ�ɹ��ı�
* ������:		Zerokei
*/
static bool to_change_row_name() {
	InitConsole();
	printf("��������Ҫ������: ");
	char buf[20]; /* buf: ���뻺��*/
	scanf("%s", buf); 
	bool flag = change_row_name(Mytable, current_row, buf);
	FreeConsole();
	draw_again();
	return flag;
}

/*
* Function:		to_change_col_name
* ����:			�ı�ѡ���е�����
* ����:			��
* ����ֵ:		bool, �Ƿ�ɹ��ı�
* ������:		Zerokei
*/
static bool to_change_col_name() {
	InitConsole();
	printf("��������Ҫ������: ");
	char buf[20]; /* buf: ���뻺��*/
	scanf("%s", buf); 
	bool flag = change_col_name(Mytable, current_col, buf);
	FreeConsole();
	draw_again();
	return flag;
}

/*
* Function:		to_change_data_name
* ����:			�ı����ݵ�����
* ����:			��
* ����ֵ:		bool, �Ƿ�ɹ��ı�
* ������:		Zerokei
*/
static bool to_change_data_name() {
	InitConsole();
	if (Mytable) {
		printf("ԭ��������: ");
		if (Mytable->data_name) {
			printf("%s", Mytable->data_name);
		}
		putchar('\n');
	}
	printf("��������Ҫ������: ");
	char buf[20]; /* buf: ���뻺��*/
	scanf("%s", buf);
	bool flag = change_data_name(Mytable, buf);
	FreeConsole();
	draw_again();
	return flag;
}

/*
* Function:		drawGraphics
* ����:			xxx
* ����:			��
* ����ֵ:		��
* ������:		Ivan
*/
static void drawGraphics()
{
	SetPenColor("HummingBird");
	drawRectangle(4.1, 2.5, 11.5, 6.0, 1);
}

/*
* Function:		drawButtons
* ����:			xxx
* ����:			��
* ����ֵ:		��
* ������:		Ivan
*/
static void drawButtons()
{
	SetPointSize(0.3);
	double fH = GetFontHeight(); /* fH:����߶�*/

	SetPenColor("SunsetOrange");
	MovePen(0.5, 7.8 + GetFontAscent());
	DrawTextString("�鿴");
	MovePen(0.5, 7.8);
	DrawLine(3.1, 0);

	/*�޸İ�ť��ɫ*/
	setButtonColors("AliceBlue", "DodgerBlue", "NYPink", "Scarlet", 1);

	double h = fH * 1.3;	/* h:�ؼ��߶� */
	double x = 2;			/* x:��ť��ʼx����*/
	double y = 7.9;			/* y:�ؼ���ʼy����*/
	double w = 1.6;			/* w:�ؼ����*/
	
	/*�л���ʾģʽ ������ or ����ͼ*/
	if (button(GenUIID(0), x, y, w, h, "������ģʽ"))
	{
		is_clear = true; 
		display();
		is_change = !is_change;
		draw_again();
	}

	/*�Ŵ�X�İ�ť*/
	h = fH * 1.3, x = 0.5, y = 7.2, w = 1.3;
	if (button(GenUIID(0), x, y, w, h, "�Ŵ�X"))
	{
		is_clear = true; 
		display();
		if (large_rate_x <= 3) 
			large_rate_x += 0.1;
		draw_again();
	}

	/*�Ŵ�Y�İ�ť*/
	y = 6.5;
	if (button(GenUIID(0), x, y, w, h, "�Ŵ�Y"))
	{
		is_clear = true; 
		display();
		if (large_rate_y <= 3) 
			large_rate_y += 0.1;
		draw_again();
	}

	/*���Ƶİ�ť*/
	y = 5.8;
	if (button(GenUIID(0), x, y, w, h, "����"))
	{
		is_clear = true; 
		display();
		double sum = width_x * query_col_num(Mytable);
		double temp_bar_width = ((double)(axis_end_x - axis_begin_x) / query_col_num(Mytable)) / (show_row_num() + 1);
		if ((draw_begin_x + sum) > axis_end_x) 
			draw_begin_x = draw_begin_x - temp_bar_width;
		draw_again();
	}

	/*���Ƶ�ͷ�İ�ť*/
	y = 5.1;
	if (button(GenUIID(0), x, y, w, h, "���Ƶ�ͷ"))
	{
		is_clear = true; 
		display();
		draw_begin_x = axis_begin_x;
		draw_again();
	}

	/*��СX�İ�ť*/
	x = 2.3, y = 7.2;
	if (button(GenUIID(0), x, y, w, h, "��СX"))
	{
		is_clear = true; 
		display();
		if (large_rate_x >= 0.2) 
			large_rate_x -= 0.1;
		if ((draw_begin_x + large_rate_x * (axis_end_x - axis_begin_x)) < axis_end_x) {
			if (draw_begin_x >= axis_begin_x) {
				draw_begin_x = axis_begin_x;
			}
			else {
				draw_begin_x = axis_end_x - large_rate_x * (axis_end_x - axis_begin_x);
			}
		}
			
		if (width_x / large_rate_x)
			draw_again();
	}

	/*��Сy�İ�ť*/
	y = 6.5;
	if (button(GenUIID(0), x, y, w, h, "��СY"))
	{
		is_clear = true; 
		display();
		if (large_rate_y >= 0.3)
			large_rate_y -= 0.1;
		draw_again();
	}

	/*���Ƶİ�ť*/
	y = 5.8;
	if (button(GenUIID(0), x, y, w, h, "����"))
	{
		is_clear = true; 
		display();
		each_bar_width = ((double)(axis_end_x - axis_begin_x) / query_col_num(Mytable)) / (show_row_num() + 1);
		if (draw_begin_x <= axis_end_x)
			draw_begin_x += each_bar_width;
		draw_again();
	}

	/*���Ƶ�ͷ�İ�ť*/
	y = 5.1;
	if (button(GenUIID(0), x, y, w, h, "���Ƶ�ͷ"))
	{
		is_clear = true; 
		display();
		double sum = width_x * query_col_num(Mytable);
		draw_begin_x = (axis_end_x - sum);
		draw_again();
	}

	/*��ʾѡ�е���Ϣ����Ϣ��*/
	SetPenColor("SunsetOrange");
	MovePen(0.5, 4.4 + GetFontAscent());
	DrawTextString("�༭");
	MovePen(0.5, 4.4);
	DrawLine(3.1, 0);

	/*�½��еİ�ť*/
	x = 0.5,y = 3.7;
	if (button(GenUIID(0), x, y, w, h, "�½���"))
	{
		is_clear = true; 
		display();

		InitConsole();
		printf("��������ݵ�����: ");
		char buf[20];
		scanf("%s", buf);
		table_add_row(Mytable, current_row, buf);
		FreeConsole();
		draw_again();
	}


	/*�½��еİ�ť*/
	y = 3;
	if (button(GenUIID(0), x, y, w, h, "�½���"))
	{
		is_clear = true; 
		display();
		InitConsole();
		printf("��������ݵ�����: ");
		char buf[20];
		scanf("%s", buf);
		table_add_col(Mytable, current_row, buf);
		FreeConsole();
		draw_again();
	}

	/*��ƽ���İ�ť*/
	y = 2.3;
	if (button(GenUIID(0), x, y, w, h, "��ƽ��"))
	{
		is_clear = true; 
		display();
		int i, mx = query_col_num(Mytable);
		double* temp = (double*)malloc(sizeof(double) * (mx + 1));
		for (i = 1; i <= mx; ++i) {
			temp[i] = query_col_average(Mytable, i);
		}
		table_add_row(Mytable, query_row_num(Mytable), "average");
		int j = query_row_num(Mytable);
		for (i = 1; i <= mx; ++i) {
			table(Mytable, j, i)->num = temp[i];
			sprintf(table(Mytable, j, i)->num_string, "%f", temp[i]);
		}

		draw_again();
	}

	/*ѡ����һ�еİ�ť*/
	y = 1.6;
	if (button(GenUIID(0), x, y, w, h, "ѡ��һ��"))
	{
		is_clear = true; 
		display();
		if (current_row == 1);
		else current_row--;
		draw_again();
	}

	/*ѡ��һ�еİ�ť*/
	y = 0.9;
	if (button(GenUIID(0), x, y, w, h, "ѡ��һ��"))
	{
		is_clear = true; 
		display();
		if (current_col == 1);
		else current_col--;
		draw_again();
	}

	/*ɾ���еİ�ť*/
	x = 2.2, y = 3.7;
	if (button(GenUIID(0), x, y, w, h, "ɾ����"))
	{
		is_clear = true; 
		display();
		table_del_row(Mytable, current_row);
		if (query_row_num(Mytable) == 0) {
			current_row = 0;
			current_col = 0;
		}
		else if (current_row <= query_row_num(Mytable));
		else current_row--;
		draw_again();
	}


	/*ɾ���еİ�ť*/
	y = 3;
	if (button(GenUIID(0), x, y, w, h, "ɾ����"))
	{
		is_clear = true; 
		display();
		table_del_col(Mytable, current_col);
		if (query_col_num(Mytable) == 0) {
			current_row = 0;
			current_col = 0;
		}
		else if (current_col <= query_col_num(Mytable));
		else current_col--;
		draw_again();
	}

	/*ͼ����Ӧ����İ�ť*/
	y = 2.3;
	if (button(GenUIID(0), x, y, w, h, "��Ӧ����"))
	{
		is_clear = true; 
		display();
		large_rate_y = 1;
		adapt_the_rate_y();
		draw_again();
	}

	/*ѡ����һ�еİ�ť*/
	y = 1.6;
	if (button(GenUIID(0), x, y, w, h, "ѡ��һ��"))
	{
		is_clear = true; 
		display();
		if (current_row == Mytable->row_size);
		else current_row++;
		draw_again();
	}

	/*ѡ����һ�еİ�ť*/
	y = 0.9;
	if (button(GenUIID(0), x, y, w, h, "ѡ��һ��"))
	{
		is_clear = true;
		display();
		if (current_col == query_col_num(Mytable));
		else current_col++;
		draw_again();
	}
}

/*
* Function:		drawButtons2
* ����:			xxx
* ����:			��
* ����ֵ:		��
* ������:		Ivan
*/
static void drawButtons2()
{

	SetPointSize(0.3);
	double fH = GetFontHeight();/*fH: ����߶�*/

	SetPenColor("SunsetOrange");
	MovePen(0.5, 7.8 + GetFontAscent());
	DrawTextString("�鿴");
	MovePen(0.5, 7.8);
	DrawLine(3.1, 0);

	/*�޸İ�ť��ɫ*/
	setButtonColors("AliceBlue", "DodgerBlue", "NYPink", "Scarlet", 1);

	double h = fH * 1.3;	/* h:�ؼ��߶� */
	double x = 2;			/* x:��ť��ʼx����*/
	double y = 7.9;			/* y:�ؼ���ʼy����*/
	double w = 1.6;			/* w:�ؼ����*/
	
	/*�л���ʾģʽ ������ or ����ͼ*/
	if (button(GenUIID(0), x, y, w, h, "��״ͼģʽ"))
	{
		is_clear = true; 
		display();
		is_change = !is_change;
		draw_again();
	}

	if (is_change) {
		show_pie = TRUE;
	}
	else {
		show_pie = FALSE;
	}
	h = fH * 1.3, x = 0.5, y = 7.2, w = 1.3;			
	if (!is_changebutton)
	{
		/*ѡ���еİ�ť*/
		if (button(GenUIID(0), x, y, w, h, "ѡ����"))
		{

			is_clear = true; 
			display();
			is_changebutton = !is_changebutton;
			col_or_row = 0;
			draw_pie_num = current_col;
			draw_again();
		}
	}
	else
	{
		/*ѡ���еİ�ť*/
		if (button(GenUIID(0), x, y, w, h, "ѡ����"))
		{

			is_clear = true; 
			display();
			is_changebutton = !is_changebutton;
			col_or_row = 1;
			draw_pie_num = current_row;
			draw_again();
		}
	}
}

/*
* Function:		drawText
* ����:			ѡ�е���Ϣ��ʾ����
* ����:			��
* ����ֵ:		��
* ������:		Ivan
*/
static void drawText()
{
	char s[50] = "��ѡ�е㣺��  �� �� ��  ��";	/*s: ѡ�е���Ϣ����Ϣ*/

	int prex = current_row;						/*prex: ��ǰѡ����*/
	int prey = current_col;						/*prey: ��ǰѡ����*/
	if (prex < 10)
	{
		s[12] = '0';
		s[13] = (char)(prex + 48);
	}
	else
	{
		s[12] = (char)(prex / 10 + 48);
		s[13] = (char)(prex % 10 + 48);
	}
	if (prey < 10)
	{
		s[22] = '0';
		s[23] = (char)(prey + 48);
	}
	else
	{
		s[22] = (char)(prey / 10 + 48);
		s[23] = (char)(prey % 10 + 48);
	}

	char text[20];								/* text: ��������ֵ*/
	memset(text, 0, sizeof text);

	char* color;								/* color: ������ɫ*/
	color = GetPenColor();
	SetPenColor("AliceBlue");
	drawBox(4.1, 2.2, 11.5, 0.3, 1, s, 'L', "Scarlet");
	SetPenColor(color);
	if (Mytable) {
		if (current_col && current_row)
			strcpy(text, table(Mytable, current_row, current_col)->num_string);
		else {
			strcpy(text, "NULL");
			return;
		}
	}
	if (textbox(GenUIID(0), 9.0, 2.2, 5.0, 0.3, text, 20))
	{
		if (Mytable && current_col && current_row) {
			table(Mytable, current_row, current_col)->num = atof(text);
			strcpy(table(Mytable, current_row, current_col)->num_string, text);

			is_clear = true; display();
			draw_again();
		}
	}
}

/*
* Function:		display
* ����:			�û�����ʾ����
* ����:			��
* ����ֵ:		��
* ������:		Ivan
*/
static void display()
{
	/* ���� */
	if (is_clear)
		DisplayClear();
	if (is_clear)
		drawGraphics();

	/* ��ť */
	SetPenColor("White");
	drawRectangle(0.5, 8.0, 3.0, 1.0, 1);
	drawRectangle(0.5, 4.0, 3.0, 1.0, 1);
	
	drawText();

	/* ���ƺʹ���˵�*/
	drawMenu();
	if (!is_change)
		drawButtons();
	else 
		drawButtons2();
}

/*
* Function:		draw_statement
* ����:			��ӡʹ��˵��
* ����:			��
* ����ֵ:		��
* ������:		Ivan
*/
static void draw_statement() {
	mySetPenColor("white");
	drawRectangle(0, 0, 16, 9, 1);
	mySetPenColor("HummingBird");
	drawRectangle(2, 0.5, 12, 7.7, 1);
	double height = 0.4;/* height: �м��*/
	double head = 7.2;	/* head: ��ʼy����*/
	int hang = 1;		/* hang: ����*/
	SetFont("����");
	mySetPenColor("black");
	SetPointSize(0.9);
	MovePen(7, 7.5);
	DrawTextString("ʹ��˵��");
	SetPointSize(0.5);
	MovePen(3, head - (hang++) * height);
	mySetPenColor("Deep4");
	DrawTextString("(1) ����������");
	MovePen(3.6, head - (hang++) * height);
	mySetPenColor("Black");
	DrawTextString("��ʼ�����Ϊ�˵�������ͼ���ͱ༭��");
	MovePen(3, head - (hang++) * height);
	mySetPenColor("Deep4");
	DrawTextString("(2) ��ͼ������");
	MovePen(3.6, head - (hang++) * height);
	mySetPenColor("Black");
	DrawTextString("����ͼ��Ϊɢ��ͼ������ͼ����״ͼ����ͳ��ͼʾ�����ÿһ����");
	MovePen(3, head - (hang++) * height);
	DrawTextString("�ݿ�ѡ��ʹ����ʾ����ͼ������һ�֡���ѡ��ĳһ��������ʾ��״ͼ��");
	MovePen(3, head - (hang++) * height);
	DrawTextString("����޸ģ��ɵ����һ��/��/����������ʾ�������޸������ݡ�");
	MovePen(3, head - (hang++) * height);
	mySetPenColor("Deep4");
	DrawTextString("(3) �༭������");
	MovePen(3.6, head - (hang++) * height);
	mySetPenColor("Black");
	DrawTextString("��ѡ��Ŵ�x��,y������������ƶ�ͼ����в鿴ͼ��ı䶯����");
	MovePen(3, head - (hang++) * height);
	DrawTextString("����ť������޸�ѡ�е���Ϣ�������С������ݣ������С������ݵȲ�");
	MovePen(3, head - (hang++) * height);
	DrawTextString("����");
	MovePen(3, head - (hang++) * height);
	mySetPenColor("Deep4");
	DrawTextString("(4) �ļ�������");
	MovePen(3.6, head - (hang++) * height);
	mySetPenColor("Black");
	DrawTextString("��ͨ��csv��ʽ����excel����ڴ˳��������ͳ�����ݿ��ӻ�");
	MovePen(3, head - (hang++) * height);
	DrawTextString("�ڿ��ӻ���Ҳ������������ݡ��޸����ݵĲ������ڳ������н���ǰ");
	MovePen(3, head - (hang++) * height);
	DrawTextString("Ӧȷ���޸������ѱ��档");
	if (button(GenUIID(0), 7.0, 0.8, 2.0, 0.5, "����"))
	{
		flag = false;
		is_clear = true;
		display();
		drawText();
		draw_again();
	}
}

/*
* Function:		draw_about
* ����:			��ӡ����
* ����:			��
* ����ֵ:		��
* ������:		Ivan
*/
static void draw_about()
{
	mySetPenColor("white");
	drawRectangle(0, 0, 16, 9, 1);
	mySetPenColor("HummingBird");
	drawRectangle(2, 0.5, 12, 7.7, 1);
	SetFont("����");
	SetPenSize(10.0);
	mySetPenColor("black");
	MovePen(7.5, 6.0);
	DrawTextString("���ڱ���");
	MovePen(7.2, 5.5);
	DrawTextString("������ZJU2333��");
	MovePen(6.6, 5.0);
	DrawTextString("��Ա�� Zerokei��Parfait��Ivan");
	SetPenSize(1.0);
	if (button(GenUIID(0), 7.0, 0.8, 2.0, 0.5, "����"))
	{
		flag2 = false;
		is_clear = true;
		display();
		drawText();
		draw_again();
	}
}

/*
* Function:		display2
* ����:			xxx
* ����:			��
* ����ֵ:		��
* ������:		Ivan
*/
static void display2()
{
	if (flag) draw_statement();
}

/*
* Function:		display3
* ����:			xxx
* ����:			��
* ����ֵ:		��
* ������:		Ivan
*/
static void display3()
{
	if (flag2) draw_about();
}

/*
* Function:		CharEventProcess
* ����:			�û����ַ��¼���Ӧ����
* ����:			ch
* ����ֵ:		��
* ������:		Ivan
*/
void CharEventProcess(char ch)
{
	uiGetChar(ch); // GUI�ַ�����
	display(); //ˢ����ʾ
}

/*
* Function:		KeyboardEventProcess
* ����:			�û��ļ����¼���Ӧ����
* ����:			key, event
* ����ֵ:		��
* ������:		Ivan
*/
void KeyboardEventProcess(int key, int event)
{
	uiGetKeyboard(key, event); // GUI��ȡ����
	display(); // ˢ����ʾ
	if (!flag && !flag2) draw_again();
}

/*
* Function:		MouseEventProcess
* ����:			�û�������¼���Ӧ����
* ����:			x, y, button, event
* ����ֵ:		��
* ������:		Ivan
*/
void MouseEventProcess(int x, int y, int button, int event)
{
	double px, py;
	uiGetMouse(x, y, button, event); //GUI��ȡ���
	display(); // ˢ����ʾ
	display2();
	display3();
	if (!flag && !flag2) draw_again();
	drawMenu();
	if (Mytable == NULL)// δ���ļ�ʱ��ִ��
		return;
	switch (event) {
	case BUTTON_DOWN:
		px = ScaleXInches(x);
		py = ScaleYInches(y);
		if (button == LEFT_BUTTON) {
			double a, b;
			a = px, b = py;
			if (click(&a, &b) == TRUE) {
				current_row = (int)b;
				current_col = (int)a;
				is_clear = true;
				display();
				drawText();
				draw_again();
			}
		}
	}
}

/*
* Function:		drawMenu
* ����:			���Ʋ˵�
* ����:			��
* ����ֵ:		��
* ������:		Ivan
*/
static void drawMenu()
{
	static char* menuListFile[] = { "     �ļ�",
		"�½� | Ctrl-N", 
		"�� | Ctrl-O",
		"�ر�",
		"���� | Ctrl-S",
		"���Ϊ",
		"�˳� | Ctrl-E" };
	static char* menuListEdit[] = { "     �༭",
		"������ʾ",
		"������ʾ",
		"������ʾ",
		"�޸�����",
		"�޸�����",
		"�޸�������"
	};
	static char* menuListDraw[] = { "     ��ͼ",
		"��ͼ",
		"����ͼ",
		"��״ͼ",
		"��״ͼ"
	};
	static char* menuListHelp[] = { "     ����",
		"ʹ��˵��",
		"����" };

	/*���ò˵������ʽ*/
	SetFont("����");
	SetPointSize(0.5);
	/*
	ʹ��DefineColor()�Զ�����ɫ
	�˵��Ͱ�ť����ɫ�޷�ͨ�����Ļ�����ɫ����
	ʹ��setMenuColors setButtonColors �޸�
	����setMenuColors����������Ϊ δ���ʱ�����ɫ ������ɫ ���������ɫ ������ɫ fillflagΪ�Ƿ���䱳��
	*/

	double fH = GetFontHeight()*0.8;						/* fH:        ����߶�		*/
	double x = 0;											/* x:         ��ʼx����		*/
	double y = winheight;									/* y:         ��ʼy����		*/
	double h = fH * 1.5;									/* h:         �ؼ��߶�		*/
	double wlist = TextStringWidth(menuListFile[6]) * 1.2;	/* wlist:     �˵������	*/
	double w = wlist;										/* w:         ���			*/
	double xindent = winheight / 20;						/* xindent:   ����			*/
	int    selection;										/* selection: ѡ�пؼ����	*/
	
	/*���˵���*/
	drawMenuBar(0, y - h, winwidth, h);
	/*�޸Ĳ˵���ɫ*/
	setMenuColors("AliceBlue", "DodgerBlue", "NYPink", "Scarlet", 1);


	/*���ļ��˵�*/
	selection = menuList(GenUIID(0), x, y - h, w, wlist, h, menuListFile, sizeof(menuListFile) / sizeof(menuListFile[0]));
	switch (selection)
	{
	case 1: /*�½��ļ�����*/
		is_clear = true; 
		display(); 
		to_create_file(); 
		draw_again(); 
		break;
	case 2: /*���ļ�����*/
		is_clear = true; 
		display(); 
		to_open_file(); 
		draw_again(); 
		break;
	case 3:	
		is_clear = true; 
		display(); 
		to_close_file(); /*�ر��ļ�����*/ 
		draw_again(); 
		break;
	case 4: is_clear = true; 
		display(); 
		to_save_file();/*�����ļ�����*/ 
		draw_again();
		break;
	case 5: 
		is_clear = true; 
		display(); 
		to_save_file_as();/*���Ϊ�ļ�����*/ 
		draw_again(); 
		break;
	case 6: 
		exit(-1); 
		break;
	}

	/*���༭�˵�*/
	selection = menuList(GenUIID(0), x+w, y - h, w, wlist, h, menuListEdit, sizeof(menuListEdit) / sizeof(menuListEdit[0]));
	switch (selection)
	{
	case 1: /*������ʾ����*/
		is_clear = true; 
		display(); 
		to_display_as_line(); 
		draw_again();
		break;
	case 2: /*������ʾ����*/
		is_clear = true; 
		display(); 
		to_display_as_dot(); 
		draw_again(); 
		break;
	case 3: /*������ʾ����*/ 
		is_clear = true; 
		display(); 
		to_display_as_bar();
		draw_again(); 
		break;
	case 4: /*�����޸ĺ���*/ 
		is_clear = true; 
		display(); 
		to_change_row_name();
		draw_again(); 
		break;
	case 5: /*�����޸ĺ���*/ 
		is_clear = true; 
		display(); 
		to_change_col_name();
		draw_again(); 
		break;
	case 6: /*�������޸ĺ���*/ 
		is_clear = true; 
		display(); 
		to_change_data_name();
		draw_again(); 
		break;
	}

	/*����ͼ�˵�*/
	selection = menuList(GenUIID(0), x + 2 * w, y - h, w, wlist, h, menuListDraw, sizeof(menuListDraw) / sizeof(menuListDraw[0]));
	switch (selection)
	{
	case 1: /*���Ƶ�ͼ����*/ 
		is_clear = true; 
		is_change = 0;
		display(); 
		to_show_dot();
		draw_again();
		break;
	case 2: /*��������ͼ����*/ 
		is_clear = true; 
		is_change = 0;
		display();
		to_show_line();
		draw_again();
		break;
	case 3: /*������״ͼ����*/
		is_clear = true; 
		is_change = 0;
		display();
		to_show_bar();
		draw_again();
		break;
	case 4: /*���Ʊ�״ͼ����*/ 
		is_clear = true; 
		is_change = 1;
		display();
		to_show_pie();
		draw_again(); 
		break;
	}
	/*�������˵�*/
	selection = menuList(GenUIID(0), x + 3 * w, y - h, w, wlist, h, menuListHelp, sizeof(menuListHelp) / sizeof(menuListHelp[0]));
	switch (selection)
	{
	case 1: /*ʹ��˵������*/  
		is_clear = true; 
		display(); 
		flag = true; 
		draw_statement(); 
		draw_again();
		break;
	case 2: /*���ں���*/  
		is_clear = true; 
		display(); 
		flag2 = true;  
		draw_about(); 
		draw_again(); 
		break;
	}

}

/*
* Function:		CreateGUI
* ����:			�û����������, ����ʼ��ִ��һ��
* ����:			��
* ����ֵ:		��
* ������:		Ivan
*/
void CreateGUI()
{
	char text[20];
	// ��ʼ�����ں�ͼ��ϵͳ
	SetWindowTitle("���ݿ��ӻ�����");
	// ��ô��ڳߴ�
	winwidth = GetWindowWidth();
	winheight = GetWindowHeight();

	registerCharEvent(CharEventProcess); // �ַ�
	registerKeyboardEvent(KeyboardEventProcess);// ����
	registerMouseEvent(MouseEventProcess);      // ���
	Beautify();
	init_color();
	memset(text, 0, sizeof(text));
}
