#include "Draw.h"
#include "Table.h"
#include "FileControl.h"

extern void CreateGUI();

void Main() {
	SetWindowSize(16.0, 9.0); /*设置窗口大小*/
	InitGraphics();			  /*初始化窗口*/
	CreateGUI();			  /*创建GUI*/
	return;
}