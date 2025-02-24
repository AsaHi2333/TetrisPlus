
//��Ϸ�߼�ģ��

#pragma once


#include<time.h>
#include<iostream>
using namespace std;


//0-��Ϸ����
void gameBody();

//1-������Ϸ���߿�
void windowPrint(int x, int y);//��������Ҫ��ӡ��λ��

//2-����Ϸ��ʼ��
void newGameInit();

//3-��ӡ����˵��
void rightInfo();

//4-��ӡ��Ϸ����
void printScore();

//5-��Ϸ����ѡ��
void musicChoose();

//6-��Ϸ�������Ϣ��
void leftInfo();

//7-�߿���ɫƫ��ѡ��
void favorWindowsColorChoose();

//8-��ط�����ɫƫ��ѡ��
void favorBottomColorChoose();

//9-������Ϸ����һ������
void creatFirstBlock();//��ΪBlock�����Ԫ

//10-����Ϣ��������һ���������ʾ
void creatNextBlock();//Block����Ԫ

//11-��������
void blockCopy();

//12-��������
int blockDown(int n);

//13-��������
void blockLeft();

//14-��������
void blockRight();

//15-������ת
void blockRotate();

//16-���鴥��
void blockBottom(int b);//b����Ϸ���ĵײ�

//17-��ײ�Ϸ��Լ��
int crash(int x, int y, int shape, int status);

//18-���淽��
void blockSave();

//19-ˢ����Ϸ��
void updateGame(int n);

//20-��Ϸ��ͣ
void pauseGame();

//21-���м��
void lineClear();

//22-��������
void lineDown(int line);

//23-��Ϸ��������
void printTailAnim();

//24-������Ϸ�÷�
void scoreReset();

//25-���¿�ʼ��Ϸ
void gameRestart();

//26-��Ϸ���������ӡ
void printTail(int exceed);

//27-��Ϸ�����ӡ
void printStart(int x, int y);

//28-��Ϸ���涯�����
void deleteStart(int x, int y);

//29-��Ϸ���涯����ӡ
void printStartAnim();

//30-��Ϸģʽ����
void gameModeSet(int, double&);

//31-��Ϸģʽѡ�����
void gameModeChoose();

//32-�浵ѡ�����
void fileChoose();

//33-�浵
void writeFile(int);

//34-����
void readFile(int);

//35-�����ݷ���ṹ�����
void dataConstruction();

//36-���ṹ�������ֵ��ֵ����ǰ��Ϸ����
void dataDeconstruction();

//37-���д浵��ʼ��
void allFileInit();

//38-�����浵��ʼ��
void fileInit(int);

//39-��Ϸ����
void play();

//�����ļ���ȡ
void exami(int);

//40-�ر��ļ�
void closefile();

//41-���id����
void setName();

//42-���������߷�����
int setAgamerHscore();

//43-չʾ���а�
void showRankinglist(int);