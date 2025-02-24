//系统调用模块


#pragma once
#include<windows.h>

//1-初始化句柄
void initHandle();

//2-设置颜色
void setColor(int color);

//3-隐藏光标
void HideCursor();

//4-光标跳转
void CursorJump(int x, int y);
