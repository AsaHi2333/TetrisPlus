//����ģ��

#pragma once
#include"game.h"
#include<iostream>


//����������
class Chess {

public:
	virtual void Print(int,int,int,int,int)=0 ;//�������̳����࣬����һ��print����Ϊ���麯��
	virtual void Delete(int, int, int, int, int) = 0;
	Chess();
	~Chess();

};


//�����࣬�����йؽ����ӡ�Ĳ�����
class Windows :public Chess
{
	//������Ԫ
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
	//���캯������ʼ����������
	Windows();
	~Windows();
	void operator =(Windows&);//��������أ����
	void windowsReset();//������Ϸ�������
	int windowsShape[25][26] = { 0 };
	virtual void Print(int x, int y, int shape, int status, int color);//���¶��崿�麯��
	virtual void Delete(int x, int y, int shape, int status, int color);


};


//������
class Block :public Chess
{
	//������Ԫ
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
	//���꣺ʵ������ÿ��3X3�������Ͻǵ�����
	int x;
	int y;
	//����
	int shape;
	int status;
	int color;
	//����
	int block[7][4][4][4] = {
{

		{   {1,1,0,0},{0,1,1,0},{0,0,0,0},{0,0,0,0}   },
		{   {0,1,0,0},{1,1,0,0},{1,0,0,0},{0,0,0,0}   },
		{   {1,1,0,0},{0,1,1,0},{0,0,0,0},{0,0,0,0}   },
		{   {0,1,0,0},{1,1,0,0},{1,0,0,0},{0,0,0,0}   }

},//Z�ͷ���,�ӵ�һ��״̬��ʼ����ÿ��˳ʱ����ת90�ȵ�״̬

	{

		{   {0,1,1,0},{1,1,0,0},{0,0,0,0},{0,0,0,0}   },
		{   {1,0,0,0},{1,1,0,0},{0,1,0,0},{0,0,0,0}   },
		{   {0,1,1,0},{1,1,0,0},{0,0,0,0},{0,0,0,0}   },
		{   {1,0,0,0},{1,1,0,0},{0,1,0,0},{0,0,0,0}   }

},//S�ͷ���
	{

		{   {1,0,0,0},{1,0,0,0},{1,1,0,0},{0,0,0,0}   },
		{   {1,1,1,0},{1,0,0,0},{0,0,0,0},{0,0,0,0}   },
		{   {1,1,0,0},{0,1,0,0},{0,1,0,0},{0,0,0,0}   },
		{   {0,0,1,0},{1,1,1,0},{0,0,0,0},{0,0,0,0}   }

},//L�ͷ���
	{

		{   {0,1,0,0},{0,1,0,0},{1,1,0,0},{0,0,0,0}   },
		{   {1,0,0,0},{1,1,1,0},{0,0,0,0},{0,0,0,0}   },
		{   {1,1,0,0},{1,0,0,0},{1,0,0,0},{0,0,0,0}   },
		{   {1,1,1,0},{0,0,1,0},{0,0,0,0},{0,0,0,0}   }

},//J�ͷ���
	{

		{   {1,1,1,1},{0,0,0,0},{0,0,0,0},{0,0,0,0}   },
		{   {1,0,0,0},{1,0,0,0},{1,0,0,0},{1,0,0,0}   },
		{   {1,1,1,1},{0,0,0,0},{0,0,0,0},{0,0,0,0}   },
		{   {1,0,0,0},{1,0,0,0},{1,0,0,0},{1,0,0,0}   }

},//I�ͷ���
	{

		{   {1,1,1,0},{0,1,0,0},{0,0,0,0},{0,0,0,0}   },
		{   {0,1,0,0},{1,1,0,0},{0,1,0,0},{0,0,0,0}   },
		{   {0,1,0,0},{1,1,1,0},{0,0,0,0},{0,0,0,0}   },
		{   {1,0,0,0},{1,1,0,0},{1,0,0,0},{0,0,0,0}   }

},//T�ͷ���
	{

		{   {1,1,0,0},{1,1,0,0},{0,0,0,0},{0,0,0,0}   },
		{   {1,1,0,0},{1,1,0,0},{0,0,0,0},{0,0,0,0}  },
		{   {1,1,0,0},{1,1,0,0},{0,0,0,0},{0,0,0,0}  },
		{    {1,1,0,0},{1,1,0,0},{0,0,0,0},{0,0,0,0} }

}//���ͷ���
	
	};//��Ӧ��7�ַ��飬4����̬��4x4�淽������

public:
	Block();
	~Block();
	 virtual void Print(int x, int y, int shape, int status, int color);//���¶��崿�麯��
	virtual void Delete(int x, int y, int shape, int status, int color);

	void operator =(Block&);//��������أ����




};