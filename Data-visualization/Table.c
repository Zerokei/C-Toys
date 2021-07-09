#include "Table.h"
#include "genlib.h" /*import bool*/
#include <string.h>
#include <stdio.h>

Table* Generate_Table() 
{
	Table* p; /*p: 新建一个数据表*/
	if ((p = (Table*)malloc(sizeof(Table))) == NULL)
		return NULL;
	p->row_size = 0;
	p->col_size = 0;
	p->data_name = "data";

	if ((p->row_head = (head_ele_list*)malloc(sizeof(head_ele_list))) == NULL)
		return NULL;
	if ((p->col_head = (head_ele_list*)malloc(sizeof(head_ele_list))) == NULL)
		return NULL;
	return p;
};

/*
* Function:		query_ele
* 功能:			找到某行(列)的第n个元素
* 参数:			p: 行(列)元素链表指针
*				n: 行(列)数
* 返回值:		ele, 元素指针
* 创建人:		Zerokei
*/
static ele* query_ele(ele_list* p, int n) 
{
	for (; n; n--, p = p->next);
	return p->element;
}

ele* table(Table* p, int x, int y) 
{
	if (p->row_size < x || x < 1)
		return NULL;
	if (p->col_size < y || y < 1)
		return NULL;
	return query_ele((p->row_head+x)->head, y);
}

bool table_row_swap(Table* p, int l, int r) 
{
	if (l < 1 || l > p->row_size)
		return FALSE;
	if (r < 1 || r > p->row_size)
		return FALSE;
	ele_list* temp; /* temp: 临时节点链表指针*/
	temp = (p->row_head+l)->head;
	(p->row_head+l)->head = (p->row_head+r)->head;
	(p->row_head+r)->head = temp;
	return TRUE;
}

bool table_col_swap(Table* p, int l, int r) 
{
	if (l < 1 || l > p ->col_size)
		return FALSE;
	if (r < 1 || r > p->col_size)
		return FALSE;
	ele_list* temp; /* temp: 临时节点链表指针*/
	temp = (p->col_head + l)->head;
	(p->col_head + l)->head = (p->col_head + r)->head;
	(p->col_head + r)->head = temp;
	return TRUE;
}

/*
* Function:		delete_nth_ele
* 功能:			找到某行(列)的第n个元素,并删除它
* 参数:			p: 行(列)元素链表指针
*				n: 行(列)数
* 返回值:		bool, 是否删除成功
* 创建人:		Zerokei
*/
static bool delete_nth_ele(ele_list* p, int n) 
{
	if (n <= 0)
		return FALSE;
	n--;
	for (; p != NULL && n; p = p->next, n--);

	if (p == NULL || p -> next == NULL)
		return FALSE;
	p->next = (p->next)->next;
	return TRUE;
}

/*
* Function:		delete_nth_ele
* 功能:			找到某行(列)的第n个元素,在其后添加一个新元素
* 参数:			p: 行(列)元素链表指针
*				n: 行(列)数
* 返回值:		bool, 是否添加成功
* 创建人:		Zerokei
*/
static bool add_nth_ele(ele_list* p, ele* element, int n) 
{
	if (n <= 0)
		return FALSE;
	n--;
	for (; p != NULL && n; p = p->next, n--);
	
	if (p == NULL)
		return FALSE;
	ele_list* q;
	if ((q = (ele_list*)malloc(sizeof(ele_list))) == NULL)
		return FALSE;
	q->element = element;
	q->next = p->next;
	p->next = q;
	return TRUE;
}

bool table_del_row(Table* p, int l) 
{
	if (l < 1 || l > p->row_size)
		return FALSE;
	head_ele_list* temp;
	if ((temp = (head_ele_list*)malloc(sizeof(head_ele_list) * (p->row_size))) == NULL)
		return FALSE;
	int i;
	for (i = 0; i < l; ++i) {
		temp[i] = p->row_head[i];
	}
	for (i = l; i < p->row_size; ++i) {
		temp[i] = p->row_head[i+1];
	}
	p->row_head = temp;
	p->row_size--;

	for (i = 1; i <= p->col_size; ++i) {
		if (delete_nth_ele((p->col_head + i)->head, l) == FALSE)
			return FALSE;
	}
	return TRUE;
}

bool table_del_col(Table* p, int l) 
{
	if (l < 1 || l > p->col_size)
		return FALSE;
	head_ele_list* temp;
	if ((temp = (head_ele_list*)malloc(sizeof(head_ele_list) * (p->col_size))) == NULL)
		return FALSE;
	int i;
	for (i = 0; i < l; ++i) {
		temp[i] = p->col_head[i];
	}
	for (i = l; i < p->col_size; ++i) {
		temp[i] = p->col_head[i + 1];
	}
	p->col_head = temp;
	p->col_size--;

	for (i = 1; i <= p->row_size; ++i) {
		if (delete_nth_ele((p->row_head + i)->head, l) == FALSE)
			return FALSE;
	}
	return TRUE;
}

/*
* Function:		create_line
* 功能:			创建长度为l的新行(列)
* 参数:			p: 行(列)元素链表头指针
*				l: 长度
*				name: 新行(列)的名字
* 返回值:		bool, 是否添加成功
* 创建人:		Zerokei
*/
static bool create_line(head_ele_list *p, int l, char* name) 
{
	if ((p->name = (char*)malloc(sizeof(name))) == NULL)
		return FALSE;
	strcpy(p->name, name);
	if ((p->head = (ele_list *)malloc(sizeof (ele_list))) == NULL)
		return FALSE;
	int i;
	ele_list* pp = p->head;// 创建一个空的头
	pp->next = NULL;
	for (i = 0; i < l; i++) {
		ele_list* qq;
		if ((qq= (ele_list*)malloc(sizeof(ele_list))) == NULL)
			return FALSE;
		qq->next = NULL;
		if ((qq->element = (ele*)malloc(sizeof(ele))) == NULL)
			return FALSE;
		(qq->element)->num = 0; // default = 0
		sprintf((qq->element)->num_string, "%f", 0);
		pp->next = qq;
		qq->next = NULL;
		pp = qq;
	}
	return TRUE;
}

bool table_add_row(Table* p, int l, char *name) 
{
	if (l < 0 || l > p->row_size)
		return FALSE;
	head_ele_list* temp;
	if ((temp = (head_ele_list*)malloc(sizeof(head_ele_list) * (p->row_size + 2))) == NULL)
		return FALSE;
	int i;
	for (i = 0; i <= l; ++i) {
		temp[i] = p->row_head[i];
	}
	if (create_line(temp + (l + 1), p->col_size, name) == FALSE)
		return FALSE;
	for (i = l + 1; i <= p->row_size; ++i) {
		temp[i + 1] = p->row_head[i];
	}
	(temp+(l+1))->display_state = display_bar;//默认显示柱子
	p->row_head = temp;
	p->row_size++;

	for (i = 1; i <= p->col_size; ++i) {
		add_nth_ele((p->col_head + i)->head, query_ele((p->row_head + l + 1)->head, i), l + 1);
	}
	return TRUE;
}

bool table_add_col(Table* p, int l, char* name) 
{
	if (l < 0 || l > p->col_size)
		return FALSE;
	head_ele_list* temp;
	if ((temp = (head_ele_list*)malloc(sizeof(head_ele_list) * (p->col_size + 2))) == NULL)
		return FALSE;
	int i;
	for (i = 0; i <= l; ++i) {
		temp[i] = p->col_head[i];
	}
	if (create_line(temp + (l + 1), p->row_size, name) == FALSE)
		return FALSE;
	for (i = l + 1; i <= p->col_size; ++i) {
		temp[i + 1] = p->col_head[i];
	}
	(temp + (l+1))->display_state = display_bar;//默认显示柱子
	p->col_head = temp;
	p->col_size++;

	for (i = 1; i <= p->row_size; ++i) {
		add_nth_ele((p->row_head + i)->head, query_ele((p->col_head + l+1)->head, i), l+1);
	}
	return TRUE;
}

char* query_row_name(Table* p, int l) 
{
	if (l < 1 || l > p->row_size)
		return NULL;
	return (p->row_head + l)->name;
}

char* query_col_name(Table* p, int l) 
{
	if (l < 1 || l > p->col_size)
		return NULL;
	return (p->col_head + l)->name;
}

bool change_row_name(Table* p, int l, char* name) 
{
	if (l < 1 || l > p->row_size) {
		return FALSE;
	}
	(p->row_head + l)->name = (char*)malloc(sizeof(name));
	if ((p->row_head + l)->name == NULL)
		return FALSE;
	strcpy((p->row_head + l)->name, name);
	return TRUE;
}

bool change_col_name(Table* p, int l, char* name) 
{
	if (l < 1 || l > p->col_size) {
		return FALSE;
	}
	(p->col_head + l)->name = (char *)malloc(sizeof (name));
	if ((p->col_head + l)->name == NULL)
		return FALSE;
	strcpy((p->col_head + l)->name, name);
	return TRUE;
}

bool change_data_name(Table* p, char* name) 
{
	p->data_name = (char*)malloc(sizeof(name));
	if (p->data_name == NULL)
		return FALSE;
	strcpy(p->data_name, name);
	return TRUE;
}

int query_col_num(Table* p) 
{
	return p->col_size;
}

int query_row_num(Table* p) 
{
	return p->row_size;
}

double query_col_average(Table* p, int l) 
{
	if (l < 0 || l > p->col_size) return -1;
	double sum = 0.0;
	ele_list* lp = (p->col_head + l)->head;
	for (lp = lp->next; lp; lp = lp->next)
		sum += (lp->element)->num;
	return sum / p->row_size;
}

bool query_if_show_bar(Table* p, int l) 
{
	if (l < 1 || l > p->row_size) 
		return FALSE;
	return (((p->row_head) + l)->display_state == display_bar);
}

bool query_if_show_line(Table* p, int l) 
{
	if (l < 1 || l > p->row_size) 
		return FALSE;
	return (((p->row_head) + l)->display_state == display_line);
}

bool query_if_show_dot(Table* p, int l) 
{
	if (l < 1 || l > p->row_size) 
		return FALSE;
	return (((p->row_head) + l)->display_state == display_dot);
}

bool let_it_show_bar(Table* p, int l) 
{
	if (l < 1 || l > p->row_size) 
		return FALSE;
	((p->row_head) + l)->display_state = display_bar;
	return TRUE;
}

bool let_it_show_line(Table* p, int l) 
{
	if (l < 1 || l > p->row_size) 
		return FALSE;
	((p->row_head) + l)->display_state = display_line;
	return TRUE;
}

bool let_it_show_dot(Table* p, int l) 
{
	if (l < 1 || l > p->row_size) 
		return FALSE;
	((p->row_head) + l)->display_state = display_dot;
	return TRUE;
}

bool table_show_bar(Table* p) 
{
	if (p == NULL)
		return FALSE;
	int i;
	for (i = 1; i <= query_row_num(p); ++i) {
		let_it_show_bar(p, i);
	}
	return TRUE;
}
bool table_show_line(Table* p) 
{
	if (p == NULL)
		return FALSE;
	int i;
	for (i = 1; i <= query_row_num(p); ++i) {
		let_it_show_line(p, i);
	}
	return TRUE;
}
bool table_show_dot(Table* p) 
{
	if (p == NULL)
		return FALSE;
	int i;
	for (i = 1; i <= query_row_num(p); ++i) {
		let_it_show_dot(p, i);
	}
	return TRUE;
}

/*
* Function:		Max
* 功能:			最大值函数
* 参数:			a: 第一个数
*				b: 第二个数
* 返回值:		int, 最大值
* 创建人:		Zerokei
*/
static int Max(int a, int b) 
{
	return b < a ? a : b;
}
bool Table_input(Table* p, FILE* fp) 
{

	int i = 0, j = 0;	
	char buf[21][21][20];	/* buf:      缓冲区,将文件读入的字符串分割*/
	char ch;				
	int index = 0;			/* index:    指向当前元素的末尾			 */
	int col_size = 0;		/* col_size: 列数						 */
	int row_size = 0;		/* row_size: 行数                         */

	while ((ch = fgetc(fp)) != EOF) {
		row_size = Max(row_size, i);
		col_size = Max(col_size, j);
		switch (ch) {
		case ',':
			buf[i][j][index] = 0;
			index = 0;
			j++;
			break;
		case '\r':
			buf[i][j][index] = 0;
			index = 0;
			i++, j = 0;
			break;
		case '\n':
			buf[i][j][index] = 0;
			index = 0;
			i++, j = 0;
			break;
		default:
			buf[i][j][index++] = ch;
			break;
		}
	}
	if (i == 0 && j == 0) {// 空文件
		p->data_name = NULL;
		return TRUE; 
	}

	p->data_name = (char*)malloc(sizeof(buf[0][0]));
	strcpy(p->data_name, buf[0][0]);

	p->row_size = row_size;
	p->row_head = (head_ele_list*)malloc(sizeof(head_ele_list) * (p->row_size + 1));

	for (i = 1; i <= p->row_size; ++i) {
		head_ele_list* hd = p->row_head + i;
		hd->head = (ele_list*)malloc(sizeof(ele_list));
		hd->name = (char*)malloc(sizeof(buf[i][0]));
		strcpy(hd->name, buf[i][0]);
	}

	for (j = 1; j <= col_size; ++j) {
		table_add_col(p, j - 1, buf[0][j]);
	}

	for (i = 1; i <= row_size; ++i) {
		let_it_show_bar(p, i);
		for (j = 1; j <= col_size; ++j) {
			table(p, i, j)->num = atof(buf[i][j]);
			strcpy(table(p, i, j)->num_string, buf[i][j]);
		}
	}
	return TRUE;
}

bool Table_output(Table* p, FILE* fp) 
{
	if (fp == NULL) return FALSE; /*如果文件是空的，返回失败*/

	fprintf(fp, "%s,", p->data_name);

	int i, j;
	for (j = 1; j <= p->col_size; ++j) {
		fprintf(fp, "%s%c", query_col_name(p, j), (j == p->col_size) ? '\r' : ',');
		if (j == p->col_size) putchar('\n');
	}

	for (i = 1; i <= p->row_size; ++i) {
		fprintf(fp, "%s,", query_row_name(p, i));
		for (j = 1; j <= p->col_size; ++j) {
			fprintf(fp, "%.6f%c", table(p, i, j)->num, (j == p->col_size) ? '\r' : ',');
			if (j == p->col_size) putchar('\n');
		}
	}

	return TRUE;
}