#ifndef _Table_h_
#define _Table_h_

#include "graphics.h"
#include "genlib.h"
#include <stdlib.h>

#define display_bar 0	/*显示柱形*/
#define display_line 1	/*显示折线*/
#define display_dot 2	/*显示点阵*/

/*
* struct: Myelement
* 功能:   存放数据表中每格元素的信息
* 变量:   num: 数值
*		  num_string: 数值的字符表示
* 创建人: Zerokei
*/
typedef struct Myelement {
	double num;
	char num_string[100];
}ele;

/*
* struct  Myele_list
* 功能:   链表结构，用于将同一行(列)的单位格连接起来
* 变量:   next: 指向下一个节点
*		  element: 存放的单位格信息
* 创建人: Zerokei
*/
typedef struct Myele_list {
	struct Myele_list* next;
	ele* element;
}ele_list;

/*
* struct  MyHead_ele_List
* 功能:   保存行(列)信息
* 变量:   head: 指向存放单位格信息的链表
*		  name: 行(列)名
*		  display_state: 显示格式 柱形/点阵/折线
* 创建人: Zerokei
*/
typedef struct MyHead_ele_List {
	ele_list* head;
	char* name;	
	int display_state;
}head_ele_list;

/*
* struct  MyTable
* 功能:   数据表
* 变量:   col_size: 行数
*		  row_size: 列数
*		  col_head: 若干列头的头指针
*		  row_head: 若干行头的头指针
*		  data_name:数据的名称
* 创建人: Zerokei
*/
typedef struct MyTable {
	int	col_size;
	int	row_size;
	head_ele_list* col_head;
	head_ele_list* row_head;
	char* data_name;
}Table;

/*
* Function:		Generate_Table
* 功能:			创建数据表
* 参数:			无
* 返回值:		Table, 数据表指针
* 创建人:		Zerokei
*/
Table* Generate_Table();

/*
* Function:		table
* 功能:			查询数据表单元格信息
* 参数:			p: 数据表指针 
				x: 第几行
				y: 第几列
* 返回值:		ele, 单元格
* 创建人:		Zerokei
*/
ele* table(Table* p, int x, int y);

/*
* Function:		table_row_swap
* 功能:			交换数据表中的两行
* 参数:			p: 数据表指针
				l: 交换的行
				r: 交换的另一行
* 返回值:		bool, 是否交换成功
* 创建人:		Zerokei
*/
bool table_row_swap(Table* p, int l, int r);

/*
* Function:		table_col_swap
* 功能:			交换数据表中的两列
* 参数:			p: 数据表指针
				l: 交换的列
				r: 交换的另一列
* 返回值:		bool, 是否交换成功
* 创建人:		Zerokei
*/
bool table_col_swap(Table* p, int l, int r);

/*
* Function:		table_del_row
* 功能:			删除行
* 参数:			p: 数据表指针
				l: 被删除的行
* 返回值:		bool, 是否删除成功
* 创建人:		Zerokei
*/
bool table_del_row(Table* p, int l);

/*
* Function:		table_del_col
* 功能:			删除列
* 参数:			p: 数据表指针
				l: 被删除的列
* 返回值:		bool, 是否删除成功
* 创建人:		Zerokei
*/
bool table_del_col(Table* p, int l);

/*
* Function:		table_add_row
* 功能:			新增行
* 参数:			p: 数据表指针
				l: 在哪一行后面新增行
* 返回值:		bool, 是否新增成功
* 创建人:		Zerokei
*/
bool table_add_row(Table* p, int l, char* name);

/*
* Function:		table_add_col
* 功能:			新增列
* 参数:			p: 数据表指针
				l: 在哪一列后面新增列
* 返回值:		bool, 是否新增成功
* 创建人:		Zerokei
*/
bool table_add_col(Table* p, int l, char* name);

/*
* Function:		query_row_name
* 功能:			新增行
* 参数:			p: 数据表指针
				l: 在哪一行后面新增行
* 返回值:		char*, 行的名字的字符串指针, 如果超出范围, 返回NULL
* 创建人:		Zerokei
*/
char* query_row_name(Table* p, int l);

/*
* Function:		query_col_name
* 功能:			新增行
* 参数:			p: 数据表指针
				l: 在哪一列后面新增列
* 返回值:		char*, 列的名字的字符串指针, 如果超出范围, 返回NULL
* 创建人:		Zerokei
*/
char* query_col_name(Table* p, int l);

/*
* Function:		change_row_name
* 功能:			改变行名
* 参数:			p: 数据表指针
				l: 第几行
				name: 想要修改成的名字
* 返回值:		bool, 是否修改成功
* 创建人:		Zerokei
*/
bool change_row_name(Table* p, int l, char* name);

/*
* Function:		change_col_name
* 功能:			改变列名
* 参数:			p: 数据表指针
				l: 第几列
				name: 想要修改成的名字
* 返回值:		bool, 是否修改成功
* 创建人:		Zerokei
*/
bool change_col_name(Table* p, int l, char* name);

/*
* Function:		change_data_name
* 功能:			改变数据名（即显示在y轴的文字）
* 参数:			p: 数据表指针
				name: 想要修改成的名字
* 返回值:		bool, 是否修改成功
* 创建人:		Zerokei
*/
bool change_data_name(Table* p, char* name);

/*
* Function:		query_col_num
* 功能:			询问列数
* 参数:			p: 数据表指针
* 返回值:		int, 列数
* 创建人:		Zerokei
*/
int query_col_num(Table* p);

/*
* Function:		query_row_num
* 功能:			询问行数
* 参数:			p: 数据表指针
* 返回值:		int, 行数
* 创建人:		Zerokei
*/
int query_row_num(Table* p);

/*
* Function:		query_col_average
* 功能:			询问某一列的平均数
* 参数:			p: 数据表指针
*				l: 第几列
* 返回值:		double, 平均数
* 创建人:		Zerokei
*/
double query_col_average(Table* p, int l);

/*
* Function:		query_if_show_bar
* 功能:			询问某一行的数据是否用柱形展示
* 参数:			p: 数据表指针
*				l: 第几行
* 返回值:		bool, 是否展现柱形
* 创建人:		Zerokei
*/
bool query_if_show_bar(Table* p, int l);

/*
* Function:		query_if_show_line
* 功能:			询问某一行的数据是否用折线展示
* 参数:			p: 数据表指针
*				l: 第几行
* 返回值:		bool, 是否展现折线
* 创建人:		Zerokei
*/
bool query_if_show_line(Table* p, int l);

/*
* Function:		query_if_show_dot
* 功能:			询问某一行的数据是否用点阵展示
* 参数:			p: 数据表指针
*				l: 第几行
* 返回值:		bool, 是否展现点阵
* 创建人:		Zerokei
*/
bool query_if_show_dot(Table* p, int l);

/*
* Function:		let_it_show_bar
* 功能:			让某一行的数据用柱形展示
* 参数:			p: 数据表指针
*				l: 第几行
* 返回值:		bool, 是否成功
* 创建人:		Zerokei
*/
bool let_it_show_bar(Table* p, int l);

/*
* Function:		let_it_show_line
* 功能:			让某一行的数据用折线展示
* 参数:			p: 数据表指针
*				l: 第几行
* 返回值:		bool, 是否成功
* 创建人:		Zerokei
*/
bool let_it_show_line(Table* p, int l);

/*
* Function:		let_it_show_dot
* 功能:			让某一行的数据用点阵展示
* 参数:			p: 数据表指针
*				l: 第几行
* 返回值:		bool, 是否成功
* 创建人:		Zerokei
*/
bool let_it_show_dot(Table* p, int l);

/*
* Function:		let_it_show_bar
* 功能:			数据表的数据全部设置为柱形图显示
* 参数:			p: 数据表指针
* 返回值:		bool, 是否成功
* 创建人:		Zerokei
*/
bool table_show_bar(Table* p);

/*
* Function:		let_it_show_bar
* 功能:			数据表的数据全部设置为折线图显示
* 参数:			p: 数据表指针
* 返回值:		bool, 是否成功
* 创建人:		Zerokei
*/
bool table_show_line(Table* p);

/*
* Function:		let_it_show_bar
* 功能:			数据表的数据全部设置为点阵图显示
* 参数:			p: 数据表指针
* 返回值:		bool, 是否成功
* 创建人:		Zerokei
*/
bool table_show_dot(Table* p);

/*
* Function:		Table_input
* 功能:			从文件中读入数据表信息
* 参数:			p:  数据表指针
* 返回值:		fp: 文件指针
* 创建人:		Zerokei
*/
bool Table_input(Table* p, FILE* fp);

/*
* Function:		Table_output
* 功能:			将数据表信息输出到文件中
* 参数:			p:  数据表指针
* 返回值:		fp: 文件指针
* 创建人:		Zerokei
*/bool Table_output(Table* p, FILE* fp);
#endif 