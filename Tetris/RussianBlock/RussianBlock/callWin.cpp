#include"callWin.h"
#include<windows.h>


HANDLE handle;//���������ͱ���
//1-��ʼ�����
void initHandle()
{
	handle = GetStdHandle(STD_OUTPUT_HANDLE);//����Ϊ��׼������
	HideCursor();
}


//2-������ɫ
void setColor(int color) {

	HANDLE kkk;
	kkk = GetStdHandle(STD_OUTPUT_HANDLE);
	//SetConsoleTextAttribute(kkk, FOREGROUND_RED);
	SetConsoleTextAttribute(kkk, color);
}

//3-�������
void HideCursor()
{
	CONSOLE_CURSOR_INFO curInfo; //��������Ϣ�Ľṹ�����,curInfo��һ������й������
	curInfo.dwSize = 1;  //���ù���ȣ����û��ֵ�Ļ������ع����Ч
	curInfo.bVisible = FALSE; //���������Ϊ���ɼ�
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE); //��ȡ����̨���
	SetConsoleCursorInfo(handle, &curInfo); //���ù����Ϣ
}


//4-�����ת
void CursorJump(int x, int y)
{
	COORD pos; //������λ�õĽṹ�����
	pos.X = 2*x; //����������
	pos.Y = y; //����������
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE); //��ȡ����̨���
	SetConsoleCursorPosition(handle, pos); //���ù��λ��
}

