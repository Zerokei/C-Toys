#ifndef _Table_h_
#define _Table_h_

#include "graphics.h"
#include "genlib.h"
#include <stdlib.h>

#define display_bar 0	/*��ʾ����*/
#define display_line 1	/*��ʾ����*/
#define display_dot 2	/*��ʾ����*/

/*
* struct: Myelement
* ����:   ������ݱ���ÿ��Ԫ�ص���Ϣ
* ����:   num: ��ֵ
*		  num_string: ��ֵ���ַ���ʾ
* ������: Zerokei
*/
typedef struct Myelement {
	double num;
	char num_string[100];
}ele;

/*
* struct  Myele_list
* ����:   ����ṹ�����ڽ�ͬһ��(��)�ĵ�λ����������
* ����:   next: ָ����һ���ڵ�
*		  element: ��ŵĵ�λ����Ϣ
* ������: Zerokei
*/
typedef struct Myele_list {
	struct Myele_list* next;
	ele* element;
}ele_list;

/*
* struct  MyHead_ele_List
* ����:   ������(��)��Ϣ
* ����:   head: ָ���ŵ�λ����Ϣ������
*		  name: ��(��)��
*		  display_state: ��ʾ��ʽ ����/����/����
* ������: Zerokei
*/
typedef struct MyHead_ele_List {
	ele_list* head;
	char* name;	
	int display_state;
}head_ele_list;

/*
* struct  MyTable
* ����:   ���ݱ�
* ����:   col_size: ����
*		  row_size: ����
*		  col_head: ������ͷ��ͷָ��
*		  row_head: ������ͷ��ͷָ��
*		  data_name:���ݵ�����
* ������: Zerokei
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
* ����:			�������ݱ�
* ����:			��
* ����ֵ:		Table, ���ݱ�ָ��
* ������:		Zerokei
*/
Table* Generate_Table();

/*
* Function:		table
* ����:			��ѯ���ݱ�Ԫ����Ϣ
* ����:			p: ���ݱ�ָ�� 
				x: �ڼ���
				y: �ڼ���
* ����ֵ:		ele, ��Ԫ��
* ������:		Zerokei
*/
ele* table(Table* p, int x, int y);

/*
* Function:		table_row_swap
* ����:			�������ݱ��е�����
* ����:			p: ���ݱ�ָ��
				l: ��������
				r: ��������һ��
* ����ֵ:		bool, �Ƿ񽻻��ɹ�
* ������:		Zerokei
*/
bool table_row_swap(Table* p, int l, int r);

/*
* Function:		table_col_swap
* ����:			�������ݱ��е�����
* ����:			p: ���ݱ�ָ��
				l: ��������
				r: ��������һ��
* ����ֵ:		bool, �Ƿ񽻻��ɹ�
* ������:		Zerokei
*/
bool table_col_swap(Table* p, int l, int r);

/*
* Function:		table_del_row
* ����:			ɾ����
* ����:			p: ���ݱ�ָ��
				l: ��ɾ������
* ����ֵ:		bool, �Ƿ�ɾ���ɹ�
* ������:		Zerokei
*/
bool table_del_row(Table* p, int l);

/*
* Function:		table_del_col
* ����:			ɾ����
* ����:			p: ���ݱ�ָ��
				l: ��ɾ������
* ����ֵ:		bool, �Ƿ�ɾ���ɹ�
* ������:		Zerokei
*/
bool table_del_col(Table* p, int l);

/*
* Function:		table_add_row
* ����:			������
* ����:			p: ���ݱ�ָ��
				l: ����һ�к���������
* ����ֵ:		bool, �Ƿ������ɹ�
* ������:		Zerokei
*/
bool table_add_row(Table* p, int l, char* name);

/*
* Function:		table_add_col
* ����:			������
* ����:			p: ���ݱ�ָ��
				l: ����һ�к���������
* ����ֵ:		bool, �Ƿ������ɹ�
* ������:		Zerokei
*/
bool table_add_col(Table* p, int l, char* name);

/*
* Function:		query_row_name
* ����:			������
* ����:			p: ���ݱ�ָ��
				l: ����һ�к���������
* ����ֵ:		char*, �е����ֵ��ַ���ָ��, ���������Χ, ����NULL
* ������:		Zerokei
*/
char* query_row_name(Table* p, int l);

/*
* Function:		query_col_name
* ����:			������
* ����:			p: ���ݱ�ָ��
				l: ����һ�к���������
* ����ֵ:		char*, �е����ֵ��ַ���ָ��, ���������Χ, ����NULL
* ������:		Zerokei
*/
char* query_col_name(Table* p, int l);

/*
* Function:		change_row_name
* ����:			�ı�����
* ����:			p: ���ݱ�ָ��
				l: �ڼ���
				name: ��Ҫ�޸ĳɵ�����
* ����ֵ:		bool, �Ƿ��޸ĳɹ�
* ������:		Zerokei
*/
bool change_row_name(Table* p, int l, char* name);

/*
* Function:		change_col_name
* ����:			�ı�����
* ����:			p: ���ݱ�ָ��
				l: �ڼ���
				name: ��Ҫ�޸ĳɵ�����
* ����ֵ:		bool, �Ƿ��޸ĳɹ�
* ������:		Zerokei
*/
bool change_col_name(Table* p, int l, char* name);

/*
* Function:		change_data_name
* ����:			�ı�������������ʾ��y������֣�
* ����:			p: ���ݱ�ָ��
				name: ��Ҫ�޸ĳɵ�����
* ����ֵ:		bool, �Ƿ��޸ĳɹ�
* ������:		Zerokei
*/
bool change_data_name(Table* p, char* name);

/*
* Function:		query_col_num
* ����:			ѯ������
* ����:			p: ���ݱ�ָ��
* ����ֵ:		int, ����
* ������:		Zerokei
*/
int query_col_num(Table* p);

/*
* Function:		query_row_num
* ����:			ѯ������
* ����:			p: ���ݱ�ָ��
* ����ֵ:		int, ����
* ������:		Zerokei
*/
int query_row_num(Table* p);

/*
* Function:		query_col_average
* ����:			ѯ��ĳһ�е�ƽ����
* ����:			p: ���ݱ�ָ��
*				l: �ڼ���
* ����ֵ:		double, ƽ����
* ������:		Zerokei
*/
double query_col_average(Table* p, int l);

/*
* Function:		query_if_show_bar
* ����:			ѯ��ĳһ�е������Ƿ�������չʾ
* ����:			p: ���ݱ�ָ��
*				l: �ڼ���
* ����ֵ:		bool, �Ƿ�չ������
* ������:		Zerokei
*/
bool query_if_show_bar(Table* p, int l);

/*
* Function:		query_if_show_line
* ����:			ѯ��ĳһ�е������Ƿ�������չʾ
* ����:			p: ���ݱ�ָ��
*				l: �ڼ���
* ����ֵ:		bool, �Ƿ�չ������
* ������:		Zerokei
*/
bool query_if_show_line(Table* p, int l);

/*
* Function:		query_if_show_dot
* ����:			ѯ��ĳһ�е������Ƿ��õ���չʾ
* ����:			p: ���ݱ�ָ��
*				l: �ڼ���
* ����ֵ:		bool, �Ƿ�չ�ֵ���
* ������:		Zerokei
*/
bool query_if_show_dot(Table* p, int l);

/*
* Function:		let_it_show_bar
* ����:			��ĳһ�е�����������չʾ
* ����:			p: ���ݱ�ָ��
*				l: �ڼ���
* ����ֵ:		bool, �Ƿ�ɹ�
* ������:		Zerokei
*/
bool let_it_show_bar(Table* p, int l);

/*
* Function:		let_it_show_line
* ����:			��ĳһ�е�����������չʾ
* ����:			p: ���ݱ�ָ��
*				l: �ڼ���
* ����ֵ:		bool, �Ƿ�ɹ�
* ������:		Zerokei
*/
bool let_it_show_line(Table* p, int l);

/*
* Function:		let_it_show_dot
* ����:			��ĳһ�е������õ���չʾ
* ����:			p: ���ݱ�ָ��
*				l: �ڼ���
* ����ֵ:		bool, �Ƿ�ɹ�
* ������:		Zerokei
*/
bool let_it_show_dot(Table* p, int l);

/*
* Function:		let_it_show_bar
* ����:			���ݱ������ȫ������Ϊ����ͼ��ʾ
* ����:			p: ���ݱ�ָ��
* ����ֵ:		bool, �Ƿ�ɹ�
* ������:		Zerokei
*/
bool table_show_bar(Table* p);

/*
* Function:		let_it_show_bar
* ����:			���ݱ������ȫ������Ϊ����ͼ��ʾ
* ����:			p: ���ݱ�ָ��
* ����ֵ:		bool, �Ƿ�ɹ�
* ������:		Zerokei
*/
bool table_show_line(Table* p);

/*
* Function:		let_it_show_bar
* ����:			���ݱ������ȫ������Ϊ����ͼ��ʾ
* ����:			p: ���ݱ�ָ��
* ����ֵ:		bool, �Ƿ�ɹ�
* ������:		Zerokei
*/
bool table_show_dot(Table* p);

/*
* Function:		Table_input
* ����:			���ļ��ж������ݱ���Ϣ
* ����:			p:  ���ݱ�ָ��
* ����ֵ:		fp: �ļ�ָ��
* ������:		Zerokei
*/
bool Table_input(Table* p, FILE* fp);

/*
* Function:		Table_output
* ����:			�����ݱ���Ϣ������ļ���
* ����:			p:  ���ݱ�ָ��
* ����ֵ:		fp: �ļ�ָ��
* ������:		Zerokei
*/bool Table_output(Table* p, FILE* fp);
#endif 