//数据模块

#pragma once
#include"game.h"
#include<iostream>


//抽象棋盘类
class Chess {

public:
	virtual void Print(int,int,int,int,int)=0 ;//定义棋盘抽象类，设置一个print函数为纯虚函数
	virtual void Delete(int, int, int, int, int) = 0;
	Chess();
	~Chess();

};


//界面类，包含有关界面打印的操作；
class Windows :public Chess
{
	//声明友元
	friend void windowPrint(int x, int y);
	friend int crash(int, int, int, int);
	friend void blockSave();
	friend void updateGame(int);
	friend void lineClear();
	friend void lineDown(int);
	friend void dataConstruction();


private:
	//int windowsShape[25][26] = {0};

public:
	//构造函数，初始化界面数组
	Windows();
	~Windows();
	void operator =(Windows&);//运算符重载：深复制
	void windowsReset();//重置游戏区：清空
	int windowsShape[25][26] = { 0 };
	virtual void Print(int x, int y, int shape, int status, int color);//重新定义纯虚函数
	virtual void Delete(int x, int y, int shape, int status, int color);


};


//方块类
class Block :public Chess
{
	//声明友元
	friend void creatFirstBlock();
	friend void creatNextBlock();
	friend void blockCopy();
	friend int blockDown(int n);
	friend void blockLeft();
	friend void blockRight();
	friend int crash(int ,int ,int ,int );
	friend void blockRotate();
	friend void blockBottom(int);
	friend void blockSave();
	friend void newGameInit();
	friend void dataConstruction();
	friend void dataDeconstruction();

private:
	//坐标：实际上是每个3X3方阵左上角的坐标
	int x;
	int y;
	//特征
	int shape;
	int status;
	int color;
	//数据
	int block[7][4][4][4] = {
{

		{   {1,1,0,0},{0,1,1,0},{0,0,0,0},{0,0,0,0}   },
		{   {0,1,0,0},{1,1,0,0},{1,0,0,0},{0,0,0,0}   },
		{   {1,1,0,0},{0,1,1,0},{0,0,0,0},{0,0,0,0}   },
		{   {0,1,0,0},{1,1,0,0},{1,0,0,0},{0,0,0,0}   }

},//Z型方块,从第一个状态开始储存每次顺时针旋转90度的状态

	{

		{   {0,1,1,0},{1,1,0,0},{0,0,0,0},{0,0,0,0}   },
		{   {1,0,0,0},{1,1,0,0},{0,1,0,0},{0,0,0,0}   },
		{   {0,1,1,0},{1,1,0,0},{0,0,0,0},{0,0,0,0}   },
		{   {1,0,0,0},{1,1,0,0},{0,1,0,0},{0,0,0,0}   }

},//S型方块
	{

		{   {1,0,0,0},{1,0,0,0},{1,1,0,0},{0,0,0,0}   },
		{   {1,1,1,0},{1,0,0,0},{0,0,0,0},{0,0,0,0}   },
		{   {1,1,0,0},{0,1,0,0},{0,1,0,0},{0,0,0,0}   },
		{   {0,0,1,0},{1,1,1,0},{0,0,0,0},{0,0,0,0}   }

},//L型方块
	{

		{   {0,1,0,0},{0,1,0,0},{1,1,0,0},{0,0,0,0}   },
		{   {1,0,0,0},{1,1,1,0},{0,0,0,0},{0,0,0,0}   },
		{   {1,1,0,0},{1,0,0,0},{1,0,0,0},{0,0,0,0}   },
		{   {1,1,1,0},{0,0,1,0},{0,0,0,0},{0,0,0,0}   }

},//J型方块
	{

		{   {1,1,1,1},{0,0,0,0},{0,0,0,0},{0,0,0,0}   },
		{   {1,0,0,0},{1,0,0,0},{1,0,0,0},{1,0,0,0}   },
		{   {1,1,1,1},{0,0,0,0},{0,0,0,0},{0,0,0,0}   },
		{   {1,0,0,0},{1,0,0,0},{1,0,0,0},{1,0,0,0}   }

},//I型方块
	{

		{   {1,1,1,0},{0,1,0,0},{0,0,0,0},{0,0,0,0}   },
		{   {0,1,0,0},{1,1,0,0},{0,1,0,0},{0,0,0,0}   },
		{   {0,1,0,0},{1,1,1,0},{0,0,0,0},{0,0,0,0}   },
		{   {1,0,0,0},{1,1,0,0},{1,0,0,0},{0,0,0,0}   }

},//T型方块
	{

		{   {1,1,0,0},{1,1,0,0},{0,0,0,0},{0,0,0,0}   },
		{   {1,1,0,0},{1,1,0,0},{0,0,0,0},{0,0,0,0}  },
		{   {1,1,0,0},{1,1,0,0},{0,0,0,0},{0,0,0,0}  },
		{    {1,1,0,0},{1,1,0,0},{0,0,0,0},{0,0,0,0} }

}//田型方块
	
	};//对应：7种方块，4种形态，4x4存方块数据

public:
	Block();
	~Block();
	 virtual void Print(int x, int y, int shape, int status, int color);//重新定义纯虚函数
	virtual void Delete(int x, int y, int shape, int status, int color);

	void operator =(Block&);//运算符重载：深复制




};