#include"callWin.h"
#include<windows.h>


HANDLE handle;//定义句柄类型变量
//1-初始化句柄
void initHandle()
{
	handle = GetStdHandle(STD_OUTPUT_HANDLE);//设置为标准输出句柄
	HideCursor();
}


//2-设置颜色
void setColor(int color) {

	HANDLE kkk;
	kkk = GetStdHandle(STD_OUTPUT_HANDLE);
	//SetConsoleTextAttribute(kkk, FOREGROUND_RED);
	SetConsoleTextAttribute(kkk, color);
}

//3-光标隐藏
void HideCursor()
{
	CONSOLE_CURSOR_INFO curInfo; //定义光标信息的结构体变量,curInfo是一个光标有关类对象
	curInfo.dwSize = 1;  //设置光标宽度，如果没赋值的话，隐藏光标无效
	curInfo.bVisible = FALSE; //将光标设置为不可见
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE); //获取控制台句柄
	SetConsoleCursorInfo(handle, &curInfo); //设置光标信息
}


//4-光标跳转
void CursorJump(int x, int y)
{
	COORD pos; //定义光标位置的结构体变量
	pos.X = 2*x; //横坐标设置
	pos.Y = y; //纵坐标设置
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE); //获取控制台句柄
	SetConsoleCursorPosition(handle, pos); //设置光标位置
}

