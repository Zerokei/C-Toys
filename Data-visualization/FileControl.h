#ifndef _FileControl_h_
#define _FileControl_h_
#include "genlib.h"
#include "Table.h"
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>

/*
* Function: Open_File
* 功能 : 打开文件，默认已经关闭了前一个文件
* 参数 : 无
* 返回值 : FILE*, 打开的文件的指针
* 创建人 : Zerokei
*/
FILE* Open_File();
/*
* Function: Create_File
* 功能 : 新建文件，默认已经关闭了前一个文件
* 参数 : 无
* 返回值 : FILE*, 新建的文件的指针
* 创建人 : Zerokei
*/
FILE* Create_File();
/*
* Function: Close_File
* 功能 : 关闭文件
* 参数 : fp: 文件指针
* 返回值 : bool, 是否关闭成功
* 创建人 : Zerokei
*/
bool Close_File(FILE* fp);
/*
* Function: Save_File
* 功能 : 保存文件
* 参数 : fp: 文件指针
*		 p:  数据表指针
* 返回值 : bool, 是否保存成功
* 创建人 : Zerokei
*/
bool Save_File(FILE* fp, Table* p);
/*
* Function: Save_File_as
* 功能 : 另存文件
* 参数 : FP: 文件的二重指针，用于传递另存为的文件指针
         p: 数据表指针
* 返回值 : bool, 是否另存为成功
* 创建人 : Zerokei
*/
bool Save_File_as(FILE** FP, Table* p);
#endif