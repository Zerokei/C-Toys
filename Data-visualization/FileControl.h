#ifndef _FileControl_h_
#define _FileControl_h_
#include "genlib.h"
#include "Table.h"
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>

/*
* Function: Open_File
* ���� : ���ļ���Ĭ���Ѿ��ر���ǰһ���ļ�
* ���� : ��
* ����ֵ : FILE*, �򿪵��ļ���ָ��
* ������ : Zerokei
*/
FILE* Open_File();
/*
* Function: Create_File
* ���� : �½��ļ���Ĭ���Ѿ��ر���ǰһ���ļ�
* ���� : ��
* ����ֵ : FILE*, �½����ļ���ָ��
* ������ : Zerokei
*/
FILE* Create_File();
/*
* Function: Close_File
* ���� : �ر��ļ�
* ���� : fp: �ļ�ָ��
* ����ֵ : bool, �Ƿ�رճɹ�
* ������ : Zerokei
*/
bool Close_File(FILE* fp);
/*
* Function: Save_File
* ���� : �����ļ�
* ���� : fp: �ļ�ָ��
*		 p:  ���ݱ�ָ��
* ����ֵ : bool, �Ƿ񱣴�ɹ�
* ������ : Zerokei
*/
bool Save_File(FILE* fp, Table* p);
/*
* Function: Save_File_as
* ���� : ����ļ�
* ���� : FP: �ļ��Ķ���ָ�룬���ڴ������Ϊ���ļ�ָ��
         p: ���ݱ�ָ��
* ����ֵ : bool, �Ƿ����Ϊ�ɹ�
* ������ : Zerokei
*/
bool Save_File_as(FILE** FP, Table* p);
#endif