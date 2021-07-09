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

bool file_open;						/* file_open: 是否打开文件*/
FILE* file_ptr;						/* file_ptr: 打开的文件指针*/
int current_row;					/* current_row: 当前选中行*/
int current_col;					/* current_col: 当前选中列*/
Table* Mytable = NULL;				/* Mytable: 打开的数据表*/
static bool flag = false;			/* flag: xxx*/
static bool flag2 = false;			/* flag2:xxx*/
static bool is_clear = true;		/* is_clear: 清除标志*/
static bool is_change = false;		/* is_change: 选择显示坐标图还是饼形图*/
static bool is_changebutton = false;/* is_changebutton: xxx*/
static double winwidth, winheight;  /* 窗口尺寸 winwidth: 窗口宽度, winheight: 窗口高度*/

/*声明函数*/
static void drawMenu();
static void display();
static void drawText();

/*
* Function:		Beautify
* 功能:			xxx
* 参数:			无
* 返回值:		无
* 创建人:		Ivan
*/
static void Beautify()
{
	/*蓝色系*/
	DefineColor("CuriousBlue", 0.20, 0.59, 0.86);
	DefineColor("HummingBird", 0.77, 0.94, 0.97);
	DefineColor("AliceBlue", 0.89, 0.945, 0.996);
	DefineColor("IrisBlue", 0.0, 0.71, 0.8);
	DefineColor("DodgerBlue", 0.13, 0.654, 0.94);
	/*红色系*/
	DefineColor("NYPink", 0.88, 0.51, 0.51);
	DefineColor("SoftColor", 0.925, 0.39, 0.29);
	DefineColor("Scarlet", 0.95, 0.15, 0.075);
	DefineColor("SunsetOrange", 0.964, 0.278, 0.278);
	/*紫色系*/
	DefineColor("LightWisteria", 0.745, 0.564, 0.83);
	DefineColor("ElectricPurple", 0.647, 0.215, 0.992);
	/*绿色系*/
	DefineColor("BrightTurquoise", 0.16, 0.945, 0.764);
	DefineColor("LightGreen", 0.48, 0.937, 0.70);
	DefineColor("Gossip", 0.53, 0.83, 0.486);
	/*橘色系*/
	DefineColor("CapeHoney", 0.992, 0.929, 0.654);
	DefineColor("TahitiGold", 0.91, 0.494, 0.015);
	DefineColor("Turbo", 0.96, 0.90, 0.105);
	DefineColor("MoonGlow", 0.996, 0.98, 0.83);
}

/*
* Function:		clear_open_status
* 功能:			清除打开文件的状态
* 参数:			无
* 返回值:		无
* 创建人:		Zerokei
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
* 功能:			打开文件
* 参数:			无
* 返回值:		bool, 是否成功打开
* 创建人:		Zerokei
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
* 功能:			创建文件
* 参数:			无
* 返回值:		bool, 是否成功创建
* 创建人:		Zerokei
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
* 功能:			关闭文件
* 参数:			无
* 返回值:		bool, 是否成功关闭
* 创建人:		Zerokei
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
* 功能:			保存文件
* 参数:			无
* 返回值:		bool, 是否成功保存
* 创建人:		Zerokei
*/
static  bool to_save_file() {
	bool flag = Save_File(file_ptr, Mytable);
	draw_again();
	return flag;
}

/*
* Function:		to_save_file_as
* 功能:			另存为文件
* 参数:			无
* 返回值:		bool, 是否成功另存为
* 创建人:		Zerokei
*/
static bool to_save_file_as() {
	bool flag = Save_File_as(&file_ptr, Mytable);
	draw_again();
	return flag;
}

/*
* Function:		to_display_as_bar
* 功能:			将当前选中的行改为柱形显示
* 参数:			无
* 返回值:		bool, 是否成功改变
* 创建人:		Zerokei
*/
static bool to_display_as_bar() {
	bool rt = let_it_show_bar(Mytable, current_row);
	draw_again();
	return rt;
}

/*
* Function:		to_display_as_line
* 功能:			将当前选中的行改为折线显示
* 参数:			无
* 返回值:		bool, 是否成功改变
* 创建人:		Zerokei
*/
static bool to_display_as_line() {
	bool rt = let_it_show_line(Mytable, current_row);
	draw_again();
	return rt;
}

/*
* Function:		to_display_as_dot
* 功能:			将当前选中的行改为点阵显示
* 参数:			无
* 返回值:		bool, 是否成功改变
* 创建人:		Zerokei
*/
static bool to_display_as_dot() {
	bool rt = let_it_show_dot(Mytable, current_row);
	draw_again();
	return rt;
}

/*
* Function:		to_show_bar
* 功能:			将数据使用柱形图显示
* 参数:			无
* 返回值:		bool, 是否成功显示
* 创建人:		Zerokei
*/
static void to_show_bar() {
	show_axis = TRUE;
	show_pie = FALSE;
	table_show_bar(Mytable);
	draw_again();
}

/*
* Function:		to_show_line
* 功能:			将数据使用折线图显示
* 参数:			无
* 返回值:		bool, 是否成功显示
* 创建人:		Zerokei
*/
static void to_show_line() {
	show_axis = TRUE;
	show_pie = FALSE;
	table_show_line(Mytable);
	draw_again();
}

/*
* Function:		to_show_dot
* 功能:			将数据使用点阵图显示
* 参数:			无
* 返回值:		bool, 是否成功显示
* 创建人:		Zerokei
*/
static void to_show_dot() {
	show_axis = TRUE;
	show_pie = FALSE;
	table_show_dot(Mytable);
	draw_again();
}

/*
* Function:		to_show_pie
* 功能:			将数据使用饼形图显示
* 参数:			无
* 返回值:		bool, 是否成功显示
* 创建人:		Zerokei
*/
static void to_show_pie() {
	show_axis = FALSE;
	show_pie = TRUE;
	draw_again();
}

/*
* Function:		to_change_row_name
* 功能:			改变选中行的名字
* 参数:			无
* 返回值:		bool, 是否成功改变
* 创建人:		Zerokei
*/
static bool to_change_row_name() {
	InitConsole();
	printf("输入你想要的名字: ");
	char buf[20]; /* buf: 读入缓冲*/
	scanf("%s", buf); 
	bool flag = change_row_name(Mytable, current_row, buf);
	FreeConsole();
	draw_again();
	return flag;
}

/*
* Function:		to_change_col_name
* 功能:			改变选中列的名字
* 参数:			无
* 返回值:		bool, 是否成功改变
* 创建人:		Zerokei
*/
static bool to_change_col_name() {
	InitConsole();
	printf("输入你想要的名字: ");
	char buf[20]; /* buf: 读入缓冲*/
	scanf("%s", buf); 
	bool flag = change_col_name(Mytable, current_col, buf);
	FreeConsole();
	draw_again();
	return flag;
}

/*
* Function:		to_change_data_name
* 功能:			改变数据的名字
* 参数:			无
* 返回值:		bool, 是否成功改变
* 创建人:		Zerokei
*/
static bool to_change_data_name() {
	InitConsole();
	if (Mytable) {
		printf("原来的名字: ");
		if (Mytable->data_name) {
			printf("%s", Mytable->data_name);
		}
		putchar('\n');
	}
	printf("输入你想要的名字: ");
	char buf[20]; /* buf: 读入缓冲*/
	scanf("%s", buf);
	bool flag = change_data_name(Mytable, buf);
	FreeConsole();
	draw_again();
	return flag;
}

/*
* Function:		drawGraphics
* 功能:			xxx
* 参数:			无
* 返回值:		无
* 创建人:		Ivan
*/
static void drawGraphics()
{
	SetPenColor("HummingBird");
	drawRectangle(4.1, 2.5, 11.5, 6.0, 1);
}

/*
* Function:		drawButtons
* 功能:			xxx
* 参数:			无
* 返回值:		无
* 创建人:		Ivan
*/
static void drawButtons()
{
	SetPointSize(0.3);
	double fH = GetFontHeight(); /* fH:字体高度*/

	SetPenColor("SunsetOrange");
	MovePen(0.5, 7.8 + GetFontAscent());
	DrawTextString("查看");
	MovePen(0.5, 7.8);
	DrawLine(3.1, 0);

	/*修改按钮颜色*/
	setButtonColors("AliceBlue", "DodgerBlue", "NYPink", "Scarlet", 1);

	double h = fH * 1.3;	/* h:控件高度 */
	double x = 2;			/* x:按钮起始x坐标*/
	double y = 7.9;			/* y:控件起始y坐标*/
	double w = 1.6;			/* w:控件宽度*/
	
	/*切换显示模式 坐标轴 or 饼形图*/
	if (button(GenUIID(0), x, y, w, h, "坐标轴模式"))
	{
		is_clear = true; 
		display();
		is_change = !is_change;
		draw_again();
	}

	/*放大X的按钮*/
	h = fH * 1.3, x = 0.5, y = 7.2, w = 1.3;
	if (button(GenUIID(0), x, y, w, h, "放大X"))
	{
		is_clear = true; 
		display();
		if (large_rate_x <= 3) 
			large_rate_x += 0.1;
		draw_again();
	}

	/*放大Y的按钮*/
	y = 6.5;
	if (button(GenUIID(0), x, y, w, h, "放大Y"))
	{
		is_clear = true; 
		display();
		if (large_rate_y <= 3) 
			large_rate_y += 0.1;
		draw_again();
	}

	/*左移的按钮*/
	y = 5.8;
	if (button(GenUIID(0), x, y, w, h, "左移"))
	{
		is_clear = true; 
		display();
		double sum = width_x * query_col_num(Mytable);
		double temp_bar_width = ((double)(axis_end_x - axis_begin_x) / query_col_num(Mytable)) / (show_row_num() + 1);
		if ((draw_begin_x + sum) > axis_end_x) 
			draw_begin_x = draw_begin_x - temp_bar_width;
		draw_again();
	}

	/*左移到头的按钮*/
	y = 5.1;
	if (button(GenUIID(0), x, y, w, h, "左移到头"))
	{
		is_clear = true; 
		display();
		draw_begin_x = axis_begin_x;
		draw_again();
	}

	/*缩小X的按钮*/
	x = 2.3, y = 7.2;
	if (button(GenUIID(0), x, y, w, h, "缩小X"))
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

	/*缩小y的按钮*/
	y = 6.5;
	if (button(GenUIID(0), x, y, w, h, "缩小Y"))
	{
		is_clear = true; 
		display();
		if (large_rate_y >= 0.3)
			large_rate_y -= 0.1;
		draw_again();
	}

	/*右移的按钮*/
	y = 5.8;
	if (button(GenUIID(0), x, y, w, h, "右移"))
	{
		is_clear = true; 
		display();
		each_bar_width = ((double)(axis_end_x - axis_begin_x) / query_col_num(Mytable)) / (show_row_num() + 1);
		if (draw_begin_x <= axis_end_x)
			draw_begin_x += each_bar_width;
		draw_again();
	}

	/*右移到头的按钮*/
	y = 5.1;
	if (button(GenUIID(0), x, y, w, h, "右移到头"))
	{
		is_clear = true; 
		display();
		double sum = width_x * query_col_num(Mytable);
		draw_begin_x = (axis_end_x - sum);
		draw_again();
	}

	/*显示选中点信息的信息栏*/
	SetPenColor("SunsetOrange");
	MovePen(0.5, 4.4 + GetFontAscent());
	DrawTextString("编辑");
	MovePen(0.5, 4.4);
	DrawLine(3.1, 0);

	/*新建行的按钮*/
	x = 0.5,y = 3.7;
	if (button(GenUIID(0), x, y, w, h, "新建行"))
	{
		is_clear = true; 
		display();

		InitConsole();
		printf("输入该数据的名字: ");
		char buf[20];
		scanf("%s", buf);
		table_add_row(Mytable, current_row, buf);
		FreeConsole();
		draw_again();
	}


	/*新建列的按钮*/
	y = 3;
	if (button(GenUIID(0), x, y, w, h, "新建列"))
	{
		is_clear = true; 
		display();
		InitConsole();
		printf("输入该数据的名字: ");
		char buf[20];
		scanf("%s", buf);
		table_add_col(Mytable, current_row, buf);
		FreeConsole();
		draw_again();
	}

	/*求平均的按钮*/
	y = 2.3;
	if (button(GenUIID(0), x, y, w, h, "求平均"))
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

	/*选中下一行的按钮*/
	y = 1.6;
	if (button(GenUIID(0), x, y, w, h, "选上一行"))
	{
		is_clear = true; 
		display();
		if (current_row == 1);
		else current_row--;
		draw_again();
	}

	/*选上一列的按钮*/
	y = 0.9;
	if (button(GenUIID(0), x, y, w, h, "选上一列"))
	{
		is_clear = true; 
		display();
		if (current_col == 1);
		else current_col--;
		draw_again();
	}

	/*删除行的按钮*/
	x = 2.2, y = 3.7;
	if (button(GenUIID(0), x, y, w, h, "删除行"))
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


	/*删除列的按钮*/
	y = 3;
	if (button(GenUIID(0), x, y, w, h, "删除列"))
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

	/*图像适应坐标的按钮*/
	y = 2.3;
	if (button(GenUIID(0), x, y, w, h, "适应坐标"))
	{
		is_clear = true; 
		display();
		large_rate_y = 1;
		adapt_the_rate_y();
		draw_again();
	}

	/*选中下一行的按钮*/
	y = 1.6;
	if (button(GenUIID(0), x, y, w, h, "选下一行"))
	{
		is_clear = true; 
		display();
		if (current_row == Mytable->row_size);
		else current_row++;
		draw_again();
	}

	/*选中下一列的按钮*/
	y = 0.9;
	if (button(GenUIID(0), x, y, w, h, "选下一列"))
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
* 功能:			xxx
* 参数:			无
* 返回值:		无
* 创建人:		Ivan
*/
static void drawButtons2()
{

	SetPointSize(0.3);
	double fH = GetFontHeight();/*fH: 字体高度*/

	SetPenColor("SunsetOrange");
	MovePen(0.5, 7.8 + GetFontAscent());
	DrawTextString("查看");
	MovePen(0.5, 7.8);
	DrawLine(3.1, 0);

	/*修改按钮颜色*/
	setButtonColors("AliceBlue", "DodgerBlue", "NYPink", "Scarlet", 1);

	double h = fH * 1.3;	/* h:控件高度 */
	double x = 2;			/* x:按钮起始x坐标*/
	double y = 7.9;			/* y:控件起始y坐标*/
	double w = 1.6;			/* w:控件宽度*/
	
	/*切换显示模式 坐标轴 or 饼形图*/
	if (button(GenUIID(0), x, y, w, h, "饼状图模式"))
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
		/*选中列的按钮*/
		if (button(GenUIID(0), x, y, w, h, "选中列"))
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
		/*选中行的按钮*/
		if (button(GenUIID(0), x, y, w, h, "选中行"))
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
* 功能:			选中点信息显示函数
* 参数:			无
* 返回值:		无
* 创建人:		Ivan
*/
static void drawText()
{
	char s[50] = "被选中点：第  行 ， 第  列";	/*s: 选中点信息栏信息*/

	int prex = current_row;						/*prex: 当前选中行*/
	int prey = current_col;						/*prey: 当前选中列*/
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

	char text[20];								/* text: 存放输入的值*/
	memset(text, 0, sizeof text);

	char* color;								/* color: 画笔颜色*/
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
* 功能:			用户的显示函数
* 参数:			无
* 返回值:		无
* 创建人:		Ivan
*/
static void display()
{
	/* 清屏 */
	if (is_clear)
		DisplayClear();
	if (is_clear)
		drawGraphics();

	/* 按钮 */
	SetPenColor("White");
	drawRectangle(0.5, 8.0, 3.0, 1.0, 1);
	drawRectangle(0.5, 4.0, 3.0, 1.0, 1);
	
	drawText();

	/* 绘制和处理菜单*/
	drawMenu();
	if (!is_change)
		drawButtons();
	else 
		drawButtons2();
}

/*
* Function:		draw_statement
* 功能:			打印使用说明
* 参数:			无
* 返回值:		无
* 创建人:		Ivan
*/
static void draw_statement() {
	mySetPenColor("white");
	drawRectangle(0, 0, 16, 9, 1);
	mySetPenColor("HummingBird");
	drawRectangle(2, 0.5, 12, 7.7, 1);
	double height = 0.4;/* height: 行间距*/
	double head = 7.2;	/* head: 起始y坐标*/
	int hang = 1;		/* hang: 行数*/
	SetFont("仿宋");
	mySetPenColor("black");
	SetPointSize(0.9);
	MovePen(7, 7.5);
	DrawTextString("使用说明");
	SetPointSize(0.5);
	MovePen(3, head - (hang++) * height);
	mySetPenColor("Deep4");
	DrawTextString("(1) 基本分区：");
	MovePen(3.6, head - (hang++) * height);
	mySetPenColor("Black");
	DrawTextString("初始界面分为菜单栏，绘图区和编辑区");
	MovePen(3, head - (hang++) * height);
	mySetPenColor("Deep4");
	DrawTextString("(2) 绘图操作：");
	MovePen(3.6, head - (hang++) * height);
	mySetPenColor("Black");
	DrawTextString("坐标图分为散点图、折线图、柱状图三种统计图示，针对每一个数");
	MovePen(3, head - (hang++) * height);
	DrawTextString("据可选择使其显示三种图像其中一种。可选中某一列数据显示饼状图。");
	MovePen(3, head - (hang++) * height);
	DrawTextString("点击修改：可点击任一点/柱/饼，在其显示高亮后修改其数据。");
	MovePen(3, head - (hang++) * height);
	mySetPenColor("Deep4");
	DrawTextString("(3) 编辑操作：");
	MovePen(3.6, head - (hang++) * height);
	mySetPenColor("Black");
	DrawTextString("可选择放大x轴,y轴比例，左右移动图像进行查看图像的变动。点");
	MovePen(3, head - (hang++) * height);
	DrawTextString("击按钮可完成修改选中点信息，新增行、列数据，交换行、列数据等操");
	MovePen(3, head - (hang++) * height);
	DrawTextString("作。");
	MovePen(3, head - (hang++) * height);
	mySetPenColor("Deep4");
	DrawTextString("(4) 文件操作：");
	MovePen(3.6, head - (hang++) * height);
	mySetPenColor("Black");
	DrawTextString("可通过csv格式保存excel表格并在此程序中完成统计数据可视化");
	MovePen(3, head - (hang++) * height);
	DrawTextString("在可视化中也能完成新增数据、修改数据的操作，在程序运行结束前");
	MovePen(3, head - (hang++) * height);
	DrawTextString("应确认修改数据已保存。");
	if (button(GenUIID(0), 7.0, 0.8, 2.0, 0.5, "返回"))
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
* 功能:			打印关于
* 参数:			无
* 返回值:		无
* 创建人:		Ivan
*/
static void draw_about()
{
	mySetPenColor("white");
	drawRectangle(0, 0, 16, 9, 1);
	mySetPenColor("HummingBird");
	drawRectangle(2, 0.5, 12, 7.7, 1);
	SetFont("仿宋");
	SetPenSize(10.0);
	mySetPenColor("black");
	MovePen(7.5, 6.0);
	DrawTextString("关于本组");
	MovePen(7.2, 5.5);
	DrawTextString("组名：ZJU2333队");
	MovePen(6.6, 5.0);
	DrawTextString("组员： Zerokei、Parfait、Ivan");
	SetPenSize(1.0);
	if (button(GenUIID(0), 7.0, 0.8, 2.0, 0.5, "返回"))
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
* 功能:			xxx
* 参数:			无
* 返回值:		无
* 创建人:		Ivan
*/
static void display2()
{
	if (flag) draw_statement();
}

/*
* Function:		display3
* 功能:			xxx
* 参数:			无
* 返回值:		无
* 创建人:		Ivan
*/
static void display3()
{
	if (flag2) draw_about();
}

/*
* Function:		CharEventProcess
* 功能:			用户的字符事件响应函数
* 参数:			ch
* 返回值:		无
* 创建人:		Ivan
*/
void CharEventProcess(char ch)
{
	uiGetChar(ch); // GUI字符输入
	display(); //刷新显示
}

/*
* Function:		KeyboardEventProcess
* 功能:			用户的键盘事件响应函数
* 参数:			key, event
* 返回值:		无
* 创建人:		Ivan
*/
void KeyboardEventProcess(int key, int event)
{
	uiGetKeyboard(key, event); // GUI获取键盘
	display(); // 刷新显示
	if (!flag && !flag2) draw_again();
}

/*
* Function:		MouseEventProcess
* 功能:			用户的鼠标事件响应函数
* 参数:			x, y, button, event
* 返回值:		无
* 创建人:		Ivan
*/
void MouseEventProcess(int x, int y, int button, int event)
{
	double px, py;
	uiGetMouse(x, y, button, event); //GUI获取鼠标
	display(); // 刷新显示
	display2();
	display3();
	if (!flag && !flag2) draw_again();
	drawMenu();
	if (Mytable == NULL)// 未打开文件时不执行
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
* 功能:			绘制菜单
* 参数:			无
* 返回值:		无
* 创建人:		Ivan
*/
static void drawMenu()
{
	static char* menuListFile[] = { "     文件",
		"新建 | Ctrl-N", 
		"打开 | Ctrl-O",
		"关闭",
		"保存 | Ctrl-S",
		"另存为",
		"退出 | Ctrl-E" };
	static char* menuListEdit[] = { "     编辑",
		"折线显示",
		"点阵显示",
		"柱形显示",
		"修改行名",
		"修改列名",
		"修改数据名"
	};
	static char* menuListDraw[] = { "     绘图",
		"点图",
		"折线图",
		"柱状图",
		"饼状图"
	};
	static char* menuListHelp[] = { "     帮助",
		"使用说明",
		"关于" };

	/*设置菜单字体格式*/
	SetFont("仿宋");
	SetPointSize(0.5);
	/*
	使用DefineColor()自定义颜色
	菜单和按钮的颜色无法通过更改画笔颜色更改
	使用setMenuColors setButtonColors 修改
	其中setMenuColors从左到右依次为 未点击时框架颜色 文字颜色 点击后框架颜色 文字颜色 fillflag为是否填充背景
	*/

	double fH = GetFontHeight()*0.8;						/* fH:        字体高度		*/
	double x = 0;											/* x:         起始x坐标		*/
	double y = winheight;									/* y:         起始y坐标		*/
	double h = fH * 1.5;									/* h:         控件高度		*/
	double wlist = TextStringWidth(menuListFile[6]) * 1.2;	/* wlist:     菜单栏宽度	*/
	double w = wlist;										/* w:         宽度			*/
	double xindent = winheight / 20;						/* xindent:   缩进			*/
	int    selection;										/* selection: 选中控件序号	*/
	
	/*画菜单栏*/
	drawMenuBar(0, y - h, winwidth, h);
	/*修改菜单颜色*/
	setMenuColors("AliceBlue", "DodgerBlue", "NYPink", "Scarlet", 1);


	/*画文件菜单*/
	selection = menuList(GenUIID(0), x, y - h, w, wlist, h, menuListFile, sizeof(menuListFile) / sizeof(menuListFile[0]));
	switch (selection)
	{
	case 1: /*新建文件函数*/
		is_clear = true; 
		display(); 
		to_create_file(); 
		draw_again(); 
		break;
	case 2: /*打开文件函数*/
		is_clear = true; 
		display(); 
		to_open_file(); 
		draw_again(); 
		break;
	case 3:	
		is_clear = true; 
		display(); 
		to_close_file(); /*关闭文件函数*/ 
		draw_again(); 
		break;
	case 4: is_clear = true; 
		display(); 
		to_save_file();/*保存文件函数*/ 
		draw_again();
		break;
	case 5: 
		is_clear = true; 
		display(); 
		to_save_file_as();/*另存为文件函数*/ 
		draw_again(); 
		break;
	case 6: 
		exit(-1); 
		break;
	}

	/*画编辑菜单*/
	selection = menuList(GenUIID(0), x+w, y - h, w, wlist, h, menuListEdit, sizeof(menuListEdit) / sizeof(menuListEdit[0]));
	switch (selection)
	{
	case 1: /*折线显示函数*/
		is_clear = true; 
		display(); 
		to_display_as_line(); 
		draw_again();
		break;
	case 2: /*点阵显示函数*/
		is_clear = true; 
		display(); 
		to_display_as_dot(); 
		draw_again(); 
		break;
	case 3: /*柱形显示函数*/ 
		is_clear = true; 
		display(); 
		to_display_as_bar();
		draw_again(); 
		break;
	case 4: /*行名修改函数*/ 
		is_clear = true; 
		display(); 
		to_change_row_name();
		draw_again(); 
		break;
	case 5: /*列名修改函数*/ 
		is_clear = true; 
		display(); 
		to_change_col_name();
		draw_again(); 
		break;
	case 6: /*数据名修改函数*/ 
		is_clear = true; 
		display(); 
		to_change_data_name();
		draw_again(); 
		break;
	}

	/*画绘图菜单*/
	selection = menuList(GenUIID(0), x + 2 * w, y - h, w, wlist, h, menuListDraw, sizeof(menuListDraw) / sizeof(menuListDraw[0]));
	switch (selection)
	{
	case 1: /*绘制点图函数*/ 
		is_clear = true; 
		is_change = 0;
		display(); 
		to_show_dot();
		draw_again();
		break;
	case 2: /*绘制折线图函数*/ 
		is_clear = true; 
		is_change = 0;
		display();
		to_show_line();
		draw_again();
		break;
	case 3: /*绘制柱状图函数*/
		is_clear = true; 
		is_change = 0;
		display();
		to_show_bar();
		draw_again();
		break;
	case 4: /*绘制饼状图函数*/ 
		is_clear = true; 
		is_change = 1;
		display();
		to_show_pie();
		draw_again(); 
		break;
	}
	/*画帮助菜单*/
	selection = menuList(GenUIID(0), x + 3 * w, y - h, w, wlist, h, menuListHelp, sizeof(menuListHelp) / sizeof(menuListHelp[0]));
	switch (selection)
	{
	case 1: /*使用说明函数*/  
		is_clear = true; 
		display(); 
		flag = true; 
		draw_statement(); 
		draw_again();
		break;
	case 2: /*关于函数*/  
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
* 功能:			用户主程序入口, 仅初始化执行一次
* 参数:			无
* 返回值:		无
* 创建人:		Ivan
*/
void CreateGUI()
{
	char text[20];
	// 初始化窗口和图形系统
	SetWindowTitle("数据可视化工具");
	// 获得窗口尺寸
	winwidth = GetWindowWidth();
	winheight = GetWindowHeight();

	registerCharEvent(CharEventProcess); // 字符
	registerKeyboardEvent(KeyboardEventProcess);// 键盘
	registerMouseEvent(MouseEventProcess);      // 鼠标
	Beautify();
	init_color();
	memset(text, 0, sizeof(text));
}
