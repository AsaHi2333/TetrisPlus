
//��Ϸ�߼�ģ��

#include"callWin.h"
#include"data.h"
#include"game.h"
#include<time.h>
#include<conio.h>//_kebhit() _getch()

#include<iostream>
#include<iomanip>
#include<string>
#include<cstdlib>//��ʽת��
#include<fstream>//�ļ�����

#include<mmsystem.h>
#pragma comment(lib,"winmm.lib")//��������ͷ�ļ�
using namespace std;

//��ҵĲ����ṹ�壬����д��Ͷ�����Ϸ����
struct Gamer {

	int checkPoint = 0;//��¼�Ƿ�Ϊ�յ�
	string name="null";//���id
	int gamemode = 1;//��Ϸģʽ
	int favorMusic = 0;//��������ƫ��
	int favorWindowsColor =0x0f;//�߿���ɫƫ��
	int favorBottomColor = 0x0f;//��ط�����ɫƫ��
	int score = 0;//��Ϸ�÷�
	int highestScore = 0;//��Ϸ��ߵ÷�
	int one = 0, two = 0, three = 0, four = 0;//��ȥ������
	int ing = 1;//��¼�Ƿ����ڽ�����Ϸ

};

struct Game {
	
	int chess[30][30] = {0};//��¼��Ϸ��
	//��Ϸ��������23x14��Ϊ�˶�Ӧ�±꣬chess���鿪��һ��

	//��ǰ������Ϣ
	int curBlockPosX;
	int curBlockPosY;
	int curBlockShape;
	int curBlockStatus;
	int curBlockColor;

	//��һ��������Ϣ
	int nextBlockShape;
	int nextBlockStatus;
	int nextBlockColor;


};

//������Ҫ��¼����Ϸ����

int checkPoint = 0;//��¼�Ƿ�Ϊ�յ�
string name="null";//���id
int gamemode = 1;//��Ϸģʽ:
int favorMusic = 1;//��������ƫ��
int favorWindowsColor=0x00;//�߿���ɫƫ��
int favorBottomColor=0x00;//��ط�����ɫƫ��
int score = 0;//��Ϸ�÷�
int highestScore = 0;//��Ϸ��ߵ÷�
int one = 0, two = 0, three = 0, four = 0;//��ȥ������
int ing = 1;//��¼�Ƿ�������Ϸ


//��ұ��
int gamerNum = 1;


//�ṹ����������ڴ�ȡ�Ͷ�ȡ
Gamer aGamer;
Game aGame;

Windows thisGame;//��Ϸ���ڶ���
Windows t;//�м��������ں�thisGame��ز���
Block curBlock;//����������ڵķ���
Block nextBlock;//���������һ������


fstream GamerFile("gamer.txt", ios::out | ios::in | ios::binary);
fstream GameFile("game.txt", ios::out | ios::in | ios::binary);

//�����������Ʊ�����ʾ
string musicName[9] = {
	"NULL",
	"ROLLING GILR --MIKU",
	"�� distance --��������",
	"�չ⵾�� --�Ŵϴ�",
	"��;ǰ�� --���շ���HyperGryph",
	"Liebestraum --Franz Liszt",
	"Represent --DJ OKAWARI",
	"let him tell his story --�|���ɼ�",
	"����ңԶ����� --�д���",
};



//����

//0-��Ϸ����
void gameBody() {

	windowPrint(15, 0);//��ӡ��Ϸ�߿�

	creatFirstBlock();//���ɵ�һ������

	leftInfo();//��ӡ�Ҳ���Ϣ����

	rightInfo();//��ӡ�����Ϣ��;

	creatNextBlock();//���ɵ�һ������

	//��������
	switch (favorMusic) {

	case 1:mciSendString(L"open 1.mp3 alias a", NULL, 0, NULL); break;
	case 2:mciSendString(L"open 2.mp3 alias a", NULL, 0, NULL); break;
	case 3:mciSendString(L"open 3.mp3 alias a", NULL, 0, NULL); break;
	case 4:mciSendString(L"open 4.mp3 alias a", NULL, 0, NULL); break;
	case 5:mciSendString(L"open 5.mp3 alias a", NULL, 0, NULL); break;
	case 6:mciSendString(L"open 6.mp3 alias a", NULL, 0, NULL); break;
	case 7:mciSendString(L"open 7.mp3 alias a", NULL, 0, NULL); break;
	case 8:mciSendString(L"open 8.mp3 alias a", NULL, 0, NULL); break;

	}//�������ļ�
	mciSendString(TEXT("play a repeat"), NULL, 0, NULL);//����Ϊѭ������

	double speed = 0.60;
	gameModeSet(gamemode, speed);

	//��Ϸ����
	//�����￪ʼ�Ϳ�ʼ��һ����Ϸ���˳�whileѭ����һ����Ϸ�Ľ���
	//���ö�ʱ����
	clock_t time1, time2;
	time1 = clock();

	while (1) {


		//�������Ƿ�������
		//�����һ����Ϊ
		//char input = _getch();
		if (_kbhit()) {
			
			//��ͬ���������÷�����Ϊ
			switch (_getch()) {

				//��ת
			case'w':
			case'W':
			case 72://���ϼ�ͷ
				blockRotate();
				break;

				//����
			case'a':
			case'A':
			case 75://�����ͷ
				blockLeft();
				break;

				//����
			case'd':
			case'D':
			case 77:
				blockRight();
				break;

				//����
			case's':
			case'S':
			case 80:
				blockDown(1);
				break;

				//��ͣ
			case 32://�ո�
				pauseGame();
				break;

				//�س���
			case 13://Enter
				blockBottom(1);
				break;

			//��ת���浵ѡ�����
			case 'b':
			case'B':

				checkPoint = 1;//���浵��������Ϊ�ǿյ�
				ing = 1;//��Ϸ������

				dataConstruction();//���ݽṹ��
				writeFile(gamerNum);//�浵
				system("cls");
				mciSendString(TEXT("close a"), NULL, 0, NULL);//ֹͣ���ֲ���

				fileChoose();//��ת���浵ѡ�����
				return;
			
			}
		}
		time2 = clock();

		//0.65����������������Ϊ��Ϸ�Ѷȸ���
		if (time2 - time1 > speed * CLOCKS_PER_SEC) {

			if (blockDown(1) == 2) {
				//����if�������䣬�����Ƿ񰴼���������
				break;//��������˾���Ϸ����,break�˳�����Ϸѭ��

			}
			time1 = time2;//����ʱ����
		}
	}
	//���˴�����һ����Ϸ

	
	checkPoint = 1;//�浵��������Ϊ�ǿյ�
	ing = 0;//һ����Ϸ����
	thisGame.windowsReset();//��Ϸ������
	int exceed=setAgamerHscore();
	dataConstruction();//��Ϸ���ݽṹ��

	writeFile(gamerNum);//�浵


	printTailAnim();//��ӡ��Ϸ����ʱ����䶯��
	printTail(exceed);//��ӡ��������
}

//1-���ƽ���߿�
void windowPrint(int x, int y)
{
	for (int i = 0; i <= 24; i++) {
		for (int j = 0; j <= 25;j++) {
			if (thisGame.windowsShape[i][j] == 1) {
				setColor(favorWindowsColor);
				CursorJump(x + j, y + i);
				cout << "��";
			}

		}

	}


}

//2-����Ϸ��ʼ��
void newGameInit() {

	//��ʼ�����
	initHandle();

	//��Ϸ������
	thisGame.windowsReset();

	//��������
	scoreReset();

	//����Լ�����
	setName();


	gameModeChoose();//ѡ����Ϸģʽ

	musicChoose();//ѡ������

	favorWindowsColorChoose();//�߿���ɫƫ��ѡ��
	favorBottomColorChoose();//��ط�����ɫƫ��ѡ��


}

//3-��ӡ�Ҳ�˵��
void rightInfo(){
	CursorJump(33, 1);
	setColor(0x0f);
	cout << "��һ������";

	CursorJump(33, 9);
	cout << "�÷������";

	CursorJump(31, 11);
	cout << "��ȥһ�У�";
	CursorJump(37, 11);
	cout << 0;

	CursorJump(31, 13);
	cout << "��ȥ����:";
	CursorJump(37, 13);
	cout << 0;

	CursorJump(31, 15);
	cout << "��ȥ����:";
	CursorJump(37, 15);
	cout << 0;

	CursorJump(31, 17);
	cout << "��ȥ����:";
	CursorJump(37, 17);
	cout << 0;

	CursorJump(31, 19);
	cout << "�ܵ÷֣�";
	CursorJump(37, 19);
	cout << 0;



}

//4-��ӡ��Ϸ����
void printScore(){
	setColor(0x07);
	CursorJump(33, 9);
	//cout <<
	CursorJump(37, 11);
	cout << one;
	CursorJump(37, 13);
	cout << two;
	CursorJump(37, 15);
	cout <<three;
	CursorJump(37, 17);
	cout << four;
	//�÷�Ȩ�أ�һ�У�10�� ���У�30�� ���У�50�� 4�У�80��

	score = one * 10 + two * 30 + three * 50 + four * 80;

	CursorJump(37, 19);
	cout << score;


}

//5-��Ϸ����ѡ��
void musicChoose() {

	CursorJump(24, 4);
	setColor(0x0f);
	cout << "ѡ����ϲ������Ϸ�������֣�";

	CursorJump(18, 7);
	cout << "1 - ROLLING GILR --MIKU";

	CursorJump(18, 9);
	cout << "2 - �� distance --��������";

	CursorJump(18, 11);
	cout << "3 - �չ⵾�� --�Ŵϴ�";

	CursorJump(18, 13);
	cout << "4 - ��;ǰ�� --���շ���HyperGryph";

	CursorJump(18, 15);
	cout << "5 - Liebestraum --Franz Liszt";

	CursorJump(18, 17);
	cout << "6 - Represent --DJ OKAWARI";

	CursorJump(18, 19);
	cout << "7 - let him tell his story --�|���ɼ�";

	CursorJump(18, 21);
	cout << "8 - ����ңԶ����� --�д���";

	//��Ϸ��������
	while (1) {
		char c = _getch();
		if (c != 0) {
			if (c == '1'){favorMusic = 1; break; }
			if (c == '2') {favorMusic = 2; break; }
			if (c == '3') {favorMusic = 3; break; }
			if (c == '4')  {favorMusic = 4; break; }
			if (c == '5')  {favorMusic = 5; break; }
			if (c == '6')  {favorMusic = 6; break; }
			if (c == '7')  {favorMusic = 7; break; }
			if (c == '8') {favorMusic = 8; break; }
		}
	}
	system("cls");
	Sleep(300);

	CursorJump(24, 5);
	cout << "��ѡ��ı��������ǣ�";

	CursorJump(25, 12);
	Sleep(700);
	cout << musicName[favorMusic];

	CursorJump(25, 20);
	Sleep(700);
	cout <<"��������߿򷽿�ѡ��......";

	Sleep(700);
	system("cls");
}

//6-�����Ϣ��:��ʾ����˵���������Ϣ���浵��
void leftInfo() {

	//�����Ϣ��ӡ

	//չʾ��ѡ����
	setColor(favorWindowsColor);
	CursorJump(1, 1); cout << "������";
	CursorJump(1, 2); cout << "��";
	CursorJump(3, 2); cout << "��";
	CursorJump(1, 3); cout << "������";
	setColor(favorBottomColor);
	CursorJump(2, 2); cout << "��";
	//���id����Ϸģʽ������
	setColor(0x0f);

	CursorJump(3+(10-name.length()/2)/2, 2);
	cout << name;

	CursorJump(6, 5); 
	if (gamemode == 1)cout << "��ͨģʽ";
	if (gamemode == 2)cout << "����ģʽ";
	if (gamemode == 3)cout << "����ģʽ";
	if (gamemode == 4)cout << "����ģʽ";

	CursorJump(1, 6); cout << "BGM:";
	switch (favorMusic) {

	case 1:CursorJump(3, 8); cout << musicName[1]; break;
	case 2:CursorJump(2, 8); cout << musicName[2]; break;
	case 3:CursorJump(3, 8); cout << musicName[3]; break;
	case 4:CursorJump(5, 7);
			  cout << "��;ǰ��";
			  CursorJump(2, 9);
			  cout << "--���շ���HyperGryph";
			  break;
	case 5:CursorJump(1, 8); cout << musicName[5]; break;
	case 6:CursorJump(2, 8); cout << musicName[6]; break;
	case 7:CursorJump(2, 7);
		cout << "let him tell his story";
		CursorJump(4, 9);
		cout << "--�|���ɼ�"; 
		break;
		
	case 8:CursorJump(2, 8); cout << musicName[8]; break;
	}


	"��;ǰ�� --���շ���HyperGryph",
		"Liebestraum --Franz Liszt",
		"Represent --DJ OKAWARI",
		"let him tell his story --�|���ɼ�",



	//����˵����ӡ
	setColor(0x0f);
	CursorJump(3, 11);
	cout <<"a  A  ���ͷ  ����";
	CursorJump(3, 13);
	cout << "d  D  �Ҽ�ͷ  ����";
	CursorJump(3, 15);
	cout << "w  W  �ϼ�ͷ  ��ת";
	CursorJump(3, 17);
	cout << "s S �¼�ͷ  ����";
	CursorJump(3, 19);
	cout << "ENTER  ˲�����";
	CursorJump(3, 21);
	cout << "SPACE  ��ͣ/����";
	CursorJump(3, 23);
	cout << "b B  ���ش浵����";

	
}

//7-�߿���ɫƫ��ѡ��
void favorWindowsColorChoose(){

	CursorJump(24, 4);
	cout << "ѡ����ϲ���ı߿򷽿飺";
	int i = 8;
	int k = 5;
	//���У���μ�8
	// ���У���μ�5
	//1
	CursorJump(14, 8);
	setColor(0x0f);//����˵��Ϊ��ɫ
	cout << "0 - ɺ��";
	CursorJump(16, 10);
	setColor(0x1d);//������ɫչʾ
	cout << "��";
	//2
	CursorJump(14+i, 8);
	setColor(0x0f);
	cout << "1 - ��ʳ";
	CursorJump(16+i, 10);
	setColor(0xe0);
	cout << "��";
	//3
	CursorJump(14+2*i, 8);
	setColor(0x0f);
	cout << "2 - �ײ�";
	CursorJump(16+2*i, 10);
	setColor(0x4f);
	cout << "��";
	//4
	CursorJump(14+3*i, 8);
	setColor(0x0f);
	cout << "3 - ��";
	CursorJump(16+3*i, 10);
	setColor(0xfb);
	cout << "��";
	 
	//2��
	//5
	CursorJump(14, 8+k);
	setColor(0x0f);//����˵��Ϊ��ɫ
	cout << "4 - �칫��";
	CursorJump(16, 10+k);
	setColor(0x8f);//������ɫչʾ
	cout << "��";
	//6
	CursorJump(14+i, 8+k);
	setColor(0x0f);
	cout << "5 - ����";
	CursorJump(16+i, 10+k);
	setColor(0x4b);
	cout << "��";
	//7
	CursorJump(14+2*i, 8+k);
	setColor(0x0f);
	cout << "6 - ����";
	CursorJump(16+2*i, 10+k);
	setColor(0x4e);
	cout << "��";
	//8
	CursorJump(14+3*i, 8+k);
	setColor(0x0f);
	cout << "7 - ���";
	CursorJump(16+3*i, 10+k);
	setColor(0xdc);
	cout << "��";

	//3��
	//9
	CursorJump(14, 8 + 2*k);
	setColor(0x0f);//����˵��Ϊ��ɫ
	cout << "8 - ̫�ղ�";
	CursorJump(16, 10 + 2*k);
	setColor(0xf0);//������ɫչʾ
	cout << "��";
	//10
	CursorJump(14 + i, 8 +2* k);
	setColor(0x0f);
	cout << "9 - ϸ��";
	CursorJump(16 + i, 10 +2* k);
	setColor(0xa2);
	cout << "��";
	//11
	CursorJump(14 + 2 * i, 8 +2* k);
	setColor(0x0f);
	cout << "a - ��ɳ";
	CursorJump(16 + 2 * i, 10 +2* k);
	setColor(0x6e);
	cout << "��";
	//12
	CursorJump(14 + 3 * i, 8 +2* k);
	setColor(0x0f);
	cout << "b - ���";
	CursorJump(16 + 3 * i, 10 + 2*k);
	setColor(0x19);
	cout << "��";


	//4��
	//13
	CursorJump(14, 8 +3* k);
	setColor(0x0f);//����˵��Ϊ��ɫ
	cout << "c - ̽��";
	CursorJump(16, 10 + 3*k);
	setColor(0x8b);//������ɫչʾ
	cout << "��";
	//14
	CursorJump(14 + i, 8 +3* k);
	setColor(0x0f);
	cout << "d - ��ƺ";
	CursorJump(16 + i, 10 + 3*k);
	setColor(0xae);
	cout << "��";
	//15
	CursorJump(14 + 2 * i, 8 + 3*k);
	setColor(0x0f);
	cout << "e - ʯ��";
	CursorJump(16 + 2 * i, 10 +3* k);
	setColor(0xf7);
	cout << "��";
	//16
	CursorJump(14 + 3 * i, 8 +3* k);
	setColor(0x0f);
	cout << "f - ˮ��";
	CursorJump(16 + 3 * i, 10 +3* k);
	setColor(0x2a);
	cout << "��";

	CursorJump(22, 31);
	setColor(0x0f);
	cout << "�������¶�Ӧ�����ѡ�񡪡�";


		while (1) {

			//������ɫ
			char c;
			if ((c = _getch()) != 0) {
				if (c == '0') {
					favorWindowsColor = 0x9d;
					break;
				}
				if (c == '1') {

					favorWindowsColor = 0xe0;
					break;

				}
				if (c == '2') {

					favorWindowsColor = 0x4f;
					break;

				}
				if (c == '3') {

					favorWindowsColor = 0xfb;
					break;

				}
				if (c == '4') {

					favorWindowsColor = 0x8f;
					break;

				}
				if (c == '5') {

					favorWindowsColor = 0x4b;
					break;

				}
				if (c == '6') {

					favorWindowsColor = 0x4e;
					break;

				}
				if (c == '7') {

					favorWindowsColor = 0xdc;
					break;

				}
				if (c == '8') {

					favorWindowsColor = 0xf0;
					break;

				}
				if (c == '9') {

					favorWindowsColor = 0xa2;
					break;

				}
				if (c == 'a') {

					favorWindowsColor = 0x6e;
					break;

				}
				if (c == 'b') {

					favorWindowsColor = 0x19;
					break;

				}
				if (c == 'c') {

					favorWindowsColor = 0x8b;
					break;

				}
				if (c == 'd') {

					favorWindowsColor = 0xae;
					break;

				}
				if (c == 'e') {

					favorWindowsColor = 0xf7;
					break;

				}
				if (c == 'f') {

					favorWindowsColor = 0x2a;
					break;

				}
			}

		}

	system("cls");//����

	int wait = 700;//��ʾ���ּ��

	CursorJump(16, 3);
	setColor(0x0f);
	cout << "��ѡ���ˣ�";

	Sleep(wait);

	setColor(favorWindowsColor);
	for (int k = 1; k <= 3; k++) {

		for (int p = 1; p <= 3; p++) {
			CursorJump(25 + k, 9 + p);
			cout << "��";
		}

	}

	Sleep(wait);

	CursorJump(22, 20);
	setColor(0x0f);
	cout << "����������ط���ѡ��......";

	Sleep(wait);
	system("cls");
	Sleep(wait);
}

//8-��ط�����ɫƫ��ѡ��
void favorBottomColorChoose() {

	CursorJump(24, 4);
	cout << "ѡ����ϲ������ط��飺";
	int i = 8;
	int k = 5;
	//���У���μ�8
	// ���У���μ�5
	//1
	CursorJump(14, 8);
	setColor(0x0f);//����˵��Ϊ��ɫ
	cout << "0 - ����(���Ƽ�ѡ��)";
	CursorJump(16, 10);
	setColor(0x00);//������ɫչʾ
	cout << "��";
	//2
	CursorJump(14 + i, 8);
	setColor(0x0f);
	cout << "1 - ����";
	CursorJump(16 + i, 10);
	setColor(0x01);
	cout << "��";
	//3
	CursorJump(14 + 2 * i, 8);
	setColor(0x0f);
	cout << "2 - ����";
	CursorJump(16 + 2 * i, 10);
	setColor(0x02);
	cout << "��";
	//4
	CursorJump(14 + 3 * i, 8);
	setColor(0x0f);
	cout << "3 - ����";
	CursorJump(16 + 3 * i, 10);
	setColor(0x03);
	cout << "��";

	//2��
	//5
	CursorJump(14, 8 + k);
	setColor(0x0f);//����˵��Ϊ��ɫ
	cout << "4 - ����";
	CursorJump(16, 10 + k);
	setColor(0x04);//������ɫչʾ
	cout << "��";
	//6
	CursorJump(14 + i, 8 + k);
	setColor(0x0f);
	cout << "5 - ����";
	CursorJump(16 + i, 10 + k);
	setColor(0x05);
	cout << "��";
	//7
	CursorJump(14 + 2 * i, 8 + k);
	setColor(0x0f);
	cout << "6 - ����";
	CursorJump(16 + 2 * i, 10 + k);
	setColor(0x06);
	cout << "��";
	//8
	CursorJump(14 + 3 * i, 8 + k);
	setColor(0x0f);
	cout << "7 - ����";
	CursorJump(16 + 3 * i, 10 + k);
	setColor(0x07);
	cout << "��";

	//3��
	//9
	CursorJump(14, 8 + 2 * k);
	setColor(0x0f);//����˵��Ϊ��ɫ
	cout << "8 - ����";
	CursorJump(16, 10 + 2 * k);
	setColor(0x08);//������ɫչʾ
	cout << "��";
	//10
	CursorJump(14 + i, 8 + 2 * k);
	setColor(0x0f);
	cout << "9 - Ⱥ��";
	CursorJump(16 + i, 10 + 2 * k);
	setColor(0x09);
	cout << "��";
	//11
	CursorJump(14 + 2 * i, 8 + 2 * k);
	setColor(0x0f);
	cout << "a - ����";
	CursorJump(16 + 2 * i, 10 + 2 * k);
	setColor(0x0a);
	cout << "��";
	//12
	CursorJump(14 + 3 * i, 8 + 2 * k);
	setColor(0x0f);
	cout << "b - ����";
	CursorJump(16 + 3 * i, 10 + 2 * k);
	setColor(0x0b);
	cout << "��";


	//4��
	//13
	CursorJump(14, 8 + 3 * k);
	setColor(0x0f);//����˵��Ϊ��ɫ
	cout << "c - ����";
	CursorJump(16, 10 + 3 * k);
	setColor(0x0c);//������ɫչʾ
	cout << "��";
	//14
	CursorJump(14 + i, 8 + 3 * k);
	setColor(0x0f);
	cout << "d - ����";
	CursorJump(16 + i, 10 + 3 * k);
	setColor(0x0d);
	cout << "��";
	//15
	CursorJump(14 + 2 * i, 8 + 3 * k);
	setColor(0x0f);
	cout << "e - ����";
	CursorJump(16 + 2 * i, 10 + 3 * k);
	setColor(0x0e);
	cout << "��";
	//16
	CursorJump(14 + 3 * i, 8 + 3 * k);
	setColor(0x0f);
	cout << "f - ����";
	CursorJump(16 + 3 * i, 10 + 3 * k);
	setColor(0x0f);
	cout << "��";

	CursorJump(22, 31);
	setColor(0x0f);
	cout << "�������¶�Ӧ�����ѡ�񡪡�";


	while (1) {

		//������ɫ
		char c;
		if ((c = _getch()) != 0) {
			if (c == '0') {
				favorBottomColor = 0x00;
				break;
			}
			if (c == '1') {

				favorBottomColor = 0x01;
				break;

			}
			if (c == '2') {

				favorBottomColor = 0x02;
				break;

			}
			if (c == '3') {

				favorBottomColor = 0x03;
				break;

			}
			if (c == '4') {

				favorBottomColor = 0x04;
				break;

			}
			if (c == '5') {

				favorBottomColor = 0x05;
				break;

			}
			if (c == '6') {

				favorBottomColor = 0x06;
				break;

			}
			if (c == '7') {

				favorBottomColor = 0x07;
				break;

			}
			if (c == '8') {

				favorBottomColor = 0x08;
				break;

			}
			if (c == '9') {

				favorBottomColor = 0x09;
				break;

			}
			if (c == 'a') {

				favorBottomColor = 0x0a;
				break;

			}
			if (c == 'b') {

				favorBottomColor = 0x0b;
				break;

			}
			if (c == 'c') {

				favorBottomColor = 0x0c;
				break;

			}
			if (c == 'd') {

				favorBottomColor = 0x0d;
				break;

			}
			if (c == 'e') {

				favorBottomColor = 0x0e;
				break;

			}
			if (c == 'f') {

				favorBottomColor = 0x0f;
				break;

			}
		}

	}

	system("cls");//����


	int wait = 700;//��ʾ���ּ��

	CursorJump(16, 3);
	setColor(0x0f);
	cout << "��ѡ���ˣ�";

	Sleep(wait);

	setColor(favorBottomColor);
	for (int k = 1; k <= 3; k++) {

		for (int p = 1; p <= 3; p++) {
			CursorJump(25 + k, 9 + p);
			cout << "��";
		}

	}

	Sleep(wait);

	CursorJump(24, 20);
	setColor(0x0f);
	cout << "����������Ϸ......";

	Sleep(wait);
	system("cls");




}

//9-����Ϸ��������һ������
void creatFirstBlock() {

	srand((unsigned int)time(NULL));//������������ӣ�
	curBlock.x = 22;
	curBlock.y = 1;
	curBlock.shape = rand() %7;//�����ַ����Ӧ0-6���֣���˲���0-6�������
	curBlock.status = rand() % 4;//��ת״̬���
	curBlock.color = rand() % 0x10;//Ϊ���������������ɫ


	//�����Ǻ�ɫ�Ͳ��ɼ��ˣ��˴��ų���ɫ�������������ǵ���������ģʽ�Ͳ���ɾȥ�ڷ���
	if (curBlock.color == 0x00&&gamemode!=4) {

		curBlock.color = 0x0a;//���óɰ�ɫ��
	}


	//��ӡ����
	curBlock.Print(curBlock.x, curBlock.y, curBlock.shape, curBlock.status, curBlock.color);



}

//10-���Ҳ���Ϣ��������һ��������ʾ
void creatNextBlock() {

	srand((unsigned int)time(NULL)+111);//������������ӣ�
	nextBlock.x = 35;
	nextBlock.y = 3;

	nextBlock.Delete(nextBlock.x, nextBlock.y, nextBlock.shape, nextBlock.status, nextBlock.color);//����Ϣλ���ȸ��Ǻ��ӡ


	nextBlock.shape = rand() % 7;//�����ַ����Ӧ0-6���֣���˲���0-6�������
	nextBlock.status = rand() % 4;//��ת״̬���
	nextBlock.color = rand() % 0x10;//Ϊ���������������ɫ


	//�����Ǻ�ɫ�Ͳ��ɼ��ˣ��˴��ų���ɫ�����,4ģʽ����
	if (nextBlock.color == 0x00&&gamemode!=4) {

		nextBlock.color = 0x07;//���óɰ�ɫ��
	}


	//��ӡ
	nextBlock.Print(nextBlock.x, nextBlock.y, nextBlock.shape, nextBlock.status, nextBlock.color);

}

//11-��������:����Ϸ���ķ����Ϊ��һ������
void blockCopy() {

	curBlock = nextBlock;//ʹ�����غ�ĸ�ֵ�����
	curBlock.x = 22;//��������
	curBlock.y = 1;
	curBlock.Print(curBlock.x, curBlock.y, curBlock.shape, curBlock.status, curBlock.color);

	creatNextBlock();//��ǰ���鸴������һ���������Ϣ�����̸�����һ������

}

//12-��������
//ɾȥ��ǰ��ʾ�ķ��飬�������һ���������Ϸ����ٴδ�ӡ����
int blockDown(int n) {
	//���䷢������ײ��������
	if (crash(curBlock.x, curBlock.y+1, curBlock.shape, curBlock.status) == 1)
	{
		//���淽��>����>���´�ӡ��Ϸ��>�����µķ���
	blockSave();
	lineClear();
	updateGame(n);
	
	blockCopy();
	
	return 1;
	}
	//�������������һ���ɾͷ�����ײ����Ϸ����
	else if (crash(curBlock.x, curBlock.y+1, curBlock.shape, curBlock.status) == 2) {
		return 2;
	}
	//���Ǽ����������������
	else {

		curBlock.Delete(curBlock.x, curBlock.y, curBlock.shape, curBlock.status, curBlock.color);
		curBlock.y += 1;
		curBlock.Print(curBlock.x, curBlock.y, curBlock.shape, curBlock.status, curBlock.color);
		return 0;

	}
	
}

//13-��������
void blockLeft() {
	//������ڣ�ʲô������
	if (crash(curBlock.x-1, curBlock.y, curBlock.shape, curBlock.status)==1) {
		return ;
	}
	//û���ڣ�������
	curBlock.Delete(curBlock.x, curBlock.y, curBlock.shape, curBlock.status, curBlock.color);
	curBlock.x-= 1;
	curBlock.Print(curBlock.x, curBlock.y, curBlock.shape, curBlock.status, curBlock.color);
}

//14-��������
void blockRight() {
	//�����ұڣ�ʲô������
	if (crash(curBlock.x + 1, curBlock.y, curBlock.shape, curBlock.status) == 1) {
		return;
	}
	//û���ڣ�������
	curBlock.Delete(curBlock.x, curBlock.y, curBlock.shape, curBlock.status, curBlock.color);
	curBlock.x += 1;
	curBlock.Print(curBlock.x, curBlock.y, curBlock.shape, curBlock.status, curBlock.color);
}

//15-������ת
void blockRotate() {
	//ͨ���ı䷽�������statusά�ȵ�ֵ���ʵ����ת
	//�ж���ת�Ƿ�Ϸ�
	if (crash(curBlock.x, curBlock.y, curBlock.shape, (curBlock.status + 1) % 4) == 1)//�¸�״̬ȡ����Ϊ�����±겻����3
	{
		//��ת�����ڣ�ʲô�� ����
		return;
	}
	//��ת�Ϸ���״̬�ı�
	curBlock.Delete(curBlock.x, curBlock.y, curBlock.shape, curBlock.status, curBlock.color);
	curBlock.status = (curBlock.status + 1) % 4;//��һ��״̬������ģ�0-3�����
	curBlock.Print(curBlock.x, curBlock.y, curBlock.shape, curBlock.status, curBlock.color);//��ӡ��ת��ķ���


}

//16-���鴥��:�Ƿ����������²�
void blockBottom(int b)//b����Ϸ���ĵײ�
{
	while (1) {
		//�䵽�ײ�������
		if (crash(curBlock.x, curBlock.y+1, curBlock.shape, curBlock.status)==1)
		{

			//������ײ-���淽��-�������-������Ϸ��-��������
			blockSave();
			lineClear();
			updateGame(b);
			blockCopy();
			return;

		}
		//
		else if (crash(curBlock.x, curBlock.y+1, curBlock.shape, curBlock.status) == 2) {
			//��Ϸ����
			return;
		}
		//
		else {
			curBlock.y++;
		}
	}


}

//17-��ײ�Ϸ��Լ��:ͨ�������һ��λ���Ƿ�Ϸ�������ֵ
//��������һ��λ�û�����һ����̬
//��ײ�������߼���������Ϊ�������ڷ���������������кͶ�Ӧ���̵��������������Ƿ���1���ص�
int crash(int x, int y, int shape, int status) {
	
	for (int i = 0; i <= 3; i++) {
		for (int j = 0; j <= 3; j++) {
			if (curBlock.block[shape][status][i][j] == 1) 
			{
				//��ȥʮ�壺���̺ͳ���ʵ��������������һ��ƫ����ƫ����������Ϸ����Ҫ���ĸ��ط���ʾ
				//��������ײ
				if (thisGame.windowsShape[i + y][j + x - 15] == 1) {
					//�ṩһ������ļ�⣺һ��ʼ���ɷ����λ�þͷ�������ײ����ô��Ϸ���޷�������
					//����һ�����ͷ�������ײ
					if (curBlock.x == 22 && curBlock.y == 1) {
						return 2;
					}
					//������ʽ����ײ
					return 1;
				}
			}
		}
	}
	return 0;//û�з����κ���ʽ����ײ
}

//18-���淽�飺�������ڵײ������ķ���
//�ѷ���������Ӧ�����̵����꣬�൱�ڸı��������Ϸ���Ĵ������
void blockSave(){
	for (int i = 0; i <= 3; i++) {
		for (int j = 0; j <= 3; j++) {

			if (curBlock.block[curBlock.shape][curBlock.status][i][j] == 1) {

				thisGame.windowsShape[i + curBlock.y][j + curBlock.x - 15] = 1;


			}
		}
	}
}

//19-ˢ����Ϸ��
void updateGame(int n) {

	//ֻ��Ҫ����Ϸ���ڲ����Ϳ����ˣ����Ա߿�
	//��i��23��ʼ�ݼ�����Ϊ�Ǵӵײ���ʼ��ӡ��
	for (int i =23; i >=1; i--) {
		for (int j = 1; j <= 14; j++) {
			
			switch (n) {
			case 1:
				if (thisGame.windowsShape[i][j] == 1) {
					//������ط������ɫ
					setColor(favorBottomColor);
					CursorJump(15 + j, i);
					cout << "��";

				}
				else {
					setColor(0x00);
					CursorJump(15 + j, i);
					cout << " ";
				}
				break;
			case 2:
				if (thisGame.windowsShape[i][j] == 1) {
					setColor(0x0e);
					CursorJump(15 + j, i);
					cout << " ";

				}
				else {
					setColor(0x00);
					CursorJump(15 + j, i);
					cout << " ";
				}
				break;
			}
		}
	}

}

//20-��Ϸ��ͣ
void pauseGame() {

	CursorJump(32, 21);
	setColor(0x0e);
	cout << "--��Ϸ��ͣ��--";
	while (1) {
		//���¿ո���ͣ���ո�ļ�����32
		if (_getch() == 32) {
			break;
		}
	}
	CursorJump(32, 21);
	setColor(0x0f);
	cout << "              ";

}

//21-���м��
//����ԭ����Ϸ��ĳһ��ȫ��Ϊһ�������Ӧ����ȥ
void lineClear() {
	//ͨ�������ж�ĳһ���Ƿ���������һ�еĺ�Ϊ��Ϸ������14
	 int number = 0;//��¼���е�����
	for (int i = 23; i >= 1; i -- ) {

		int total = 0;
		for (int j = 1; j <= 14; j++) {

			total += thisGame.windowsShape[i][j];

		}
		if (total == 14) {
			lineDown(i);//��һ�����ˣ�Ҫ�������Ʋ���:
			i += 1;//���������п����Ƿ񻹻��������
			number += 1;

		}

	}
	//��������һ����ʾ��ȥ�����ĺ���
	switch (number) {

	case 1:one++; break;
	case 2:two++; break;
	case 3:three++; break;
	case 4:four++; break;

	}
	printScore();
}

//22-��������
//����һ������:�ӵ�line�п�ʼ��������������ƽ��һ��
void lineDown(int line) {
//
	
	t = thisGame;


	for (int i = line; i > 1; i--) {
		for (int j = 1; j <= 14; j++) {

			thisGame.windowsShape[i][j] = t.windowsShape[i - 1][j];

		}
	}

}

//23-��Ϸ��������
void printTailAnim() {

	for (int i = 23; i >= 1; i--) {
		for (int j = 1; j <= 14; j++) {

			setColor(0x3b);
			CursorJump(j + 15, i);
			cout << "��";
			Sleep(5);//ͣ��һ��
		}
	}

	Sleep(700);//����ʱ��

	setColor(0x00);//������ɫ��ɺ�ɫ�Ļ������������ɫ
	system("cls");//����
}

//24-������Ϸ�÷�
void scoreReset() {
	one = 0;
	two = 0;
	three = 0;
	four = 0;
	score = 0;
}

//25-���¿�ʼ��Ϸ:ָ�����ڵ�ǰ�浵�Ĳ�����������Ϸ
void gameRestart(){


	thisGame.windowsReset();//������Ϸ��

	scoreReset();//���õ÷�

	gameBody();//���¿�ʼ��Ϸ

}

//26-��Ϸ���������ӡ
void printTail(int exceed) {


	//��ӡ�������涯����wasted.
	int w = 100;
	int t = 300;
	int x = 8;
	int y = 5;
	setColor(0x04);
	CursorJump(x, y);
	cout << "��      ��      ��      ��        ����������   ����������   ����������   ��������";
	Sleep(w);
	CursorJump(x, y+1);
	cout << " ��    ����    ��     ��  ��      ��               ��       ��           ��     ��";
	Sleep(w);
	CursorJump(x, y+2);
	cout << "  ��  ��  ��  ��     ��    ��     ����������       ��       ����������   ��     ��";
	Sleep(w); 
	CursorJump(x, y+3);
	cout << "   ����    ����     ����������            ��       ��       ��           ��     ��";
	Sleep(w);
	CursorJump(x, y+4);
	cout << "    ��      ��     ��        ��   ����������       ��       ����������   ��������     ��";
	Sleep(t);
	//��ӡ��Ϸ�ܽ᣺
	CursorJump(22, 13);
	setColor(0x0f);
	cout << "��ʷ��ߵ÷�:	" << highestScore;
	CursorJump(22, 15);
	cout << "������Ϸ�÷�:	" << score;
	if (exceed) { 
		Sleep(t+200);
		CursorJump(36, 15); 
		setColor(0x0e); 
		cout << "�¼�¼��"; 
	}
	Sleep(t+400);
	//����ѡ�����
	CursorJump(24, 21);
	setColor(0x0f);
	cout << "������ѡ��";
	CursorJump(18, 24);
	cout << "N-������Ϸ";
	CursorJump(30, 24);
	cout << "Y-���¿�ʼ��Ϸ";
	CursorJump(30, 26);
	cout << "B-���ش浵ѡ�����";
	CursorJump(18, 26);
	cout << "R-�鿴���а�";
	

	
	while (1) {

		char c = _getch();
		if (c == 'n' || c == 'N') {

			system("cls");
			mciSendString(TEXT("close a"), NULL, 0, NULL);//ֹͣ���ֲ���
			return;

		}
		if (c == 'y' || c == 'Y') {
			system("cls");
			mciSendString(TEXT("close a"), NULL, 0, NULL);//ֹͣ���ֲ���
			gameRestart();
			break;
		}

		if (c == 'b' || c == 'B') {
			system("cls");
			mciSendString(TEXT("close a"), NULL, 0, NULL);//ֹͣ���ֲ���
			scoreReset();
			fileChoose();
			break;
		}


		if (c == 'r' || c == 'R') {
			system("cls");
			showRankinglist(exceed);
			break;
		}



	}
	
	return;

}

//27-��Ϸ�����ӡ
void printStart(int x, int y) {

	//ͼ������ɫ�������
	int color = rand() % 0x10;
	if (color == 0x00) {
		color = 0x0f;
	}

	//���Ʒ���ͼ��
	setColor(color);
	CursorJump(x, y);
	cout<<"����������  ����������  ����������  ����������  ��  ����������";
	CursorJump(x, y + 1);
	cout<<"    ��      ��              ��      ��      ��  ��  ��";
	CursorJump(x, y + 2); 
	cout<<"    ��      ����������      ��      ����������  ��  ����������"; 
	CursorJump(x, y + 3); 
	cout<<"    ��      ��              ��      ��    ��    ��          ��"; 
	CursorJump(x, y + 4); 
	cout<<"    ��      ����������      ��      ��    ��    ��  ����������";
	//T E R I S

	//��Ϸ��ʼ������ӡ
	CursorJump(25, 25); 
	cout << "��ENTER����ʼ��Ϸ";


}

//28-��Ϸ�������
void deleteStart(int x, int y) {

	for (int i = y; i <= y + 5; i++) {

		for (int j = x; j < x + 32; j++) {

			CursorJump(j, i);
			cout << " ";

		}
	}
}

//29-��Ϸ���涯����ӡ
void printStartAnim() {
	CursorJump(3, 5);
	for (int k = 1; k <= 36; k++)
		cout << "�� ";
	for (int k = 6; k <= 19; k++) {

		CursorJump(3, k); cout << "�� ";
		CursorJump(55, k); cout << " �� ";

	}

	CursorJump(3, 20);
	for (int k = 1; k <= 36; k++)
		cout << "�� ";




	clock_t time1, time2;
	time1 = clock();
	int x = 5;
	int head = 1;//��¼�����������ƶ���һ��ʼ���ң�1
	printStart(x, 10);
	while (1) {
		
		time2 = clock();

		//ÿ200�������⶯һ��
		if (time2 - time1 > 200) {

			time1 = time2;//ʱ���ٴ���Ϊһ��
			if (head == 1) {

				deleteStart(x, 10);//ɾȥ���λ���
				printStart(++x, 10);//�������ԼӺ��ٴδ�ӡ����

			}

			if (head == 0) {

				deleteStart(x, 10);
				printStart(--x, 10);

			}

			//�������Ƶ�һ���޶��ֻ�����
			if (x == 22) {

				head = 0;
				deleteStart(x, 10);
				printStart(--x, 10);

			}

			//����������
			if (x == 5) {

				head = 1;
				deleteStart(x, 10);
				printStart(++x, 10);

			}

		}

		//�������������˳����濪ʼ��Ϸ
		if (_kbhit()) {

			//����س��˳�
			if (_getch() == 13)break;
		}
	}
	system("cls");//�˳���ʼ����֮��������׼����һ������Ĵ�ӡ


}

//30-��Ϸģʽ����
void gameModeSet(int Gamemode, double& Speed) {

	switch (Gamemode) {
	case 1:Speed = 0.60; break;
	case 2:Speed = 0.35; break;
	case 3:Speed = 0.25; break;
	case 4:Speed = 0.15; break;
	}
}

//31-��Ϸģʽѡ�����
void gameModeChoose() {

	
	CursorJump(24, 3);
	setColor(0x0f);
	cout << "ѡ�������Ϸģʽ:";
	CursorJump(6, 7);
	setColor(0x0a);
	cout << "1--��ͨģʽ ";
	CursorJump(20, 7);
	setColor(0x0e);
	cout << "2--����ģʽ ";
	CursorJump(34, 7);
	setColor(0x0c);
	cout << "3--����ģʽ ";
	CursorJump(48, 7);
	setColor(0x08);
	cout << "4--����ģʽ";

	setColor(0x0f);

	//��ͨģʽ˵��
	CursorJump(5, 11);
	cout << "��ͨ��Tetris�Ѷȡ�";
	CursorJump(5, 12);
	cout << "�㽫���������Ϸ";
	CursorJump(5, 13);
	cout<<"�򵥶���������������";

	//����ģʽ˵��
	CursorJump(19, 10);
	cout << "*���������ٶ���������";
	CursorJump(19, 12);
	cout << "�㽫��������Ϸ";
	CursorJump(19, 13);
	cout << "�������Ѷ���������������";

	//����ģʽ˵��
	CursorJump(33, 10);
	cout << "*���������ٶȼ�������";
	CursorJump(33, 12);
	cout << "�㽫���������Ϸ";
	CursorJump(33, 13);
	cout << "�̼���������ս�Ե�������";

	//����ģʽ˵��
	CursorJump(47, 10);
	cout << "*����������ٶ����˷�ָ";
	CursorJump(47, 11);
	cout << "*���ֲ��ɼ��ĺڷ���";
	CursorJump(47, 13);
	cout << "�㽫......";
	CursorJump(47, 14);
	cout << "ף����ˡ�";

	
	while (1) {
		char c;
		if ((c=_getch())!=0) {

			//��ͨ
			if (c == '1') {
				gamemode = 1;
				break;
			}

			//����
			if (c == '2') {
				gamemode = 2;
				break;
			}

			//����
			if (c== '3') {
				gamemode = 3;
				break;
			}

			//����
			if (c== '4') {
				gamemode = 4;
				break;
			}
		}
	}//������������

	system("cls");//����

}

//32-�浵ѡ�����
void fileChoose(){

	CursorJump(29, 3);
	setColor(0x0f);
	cout << "ѡ��浵�Խ��в���";

	//�浵չʾ��ӡ
	int x = 17, y = 7;
	for (int i = 1; i <= 3; i++) {
		//һ���浵չʾ�Ĵ�ӡ
		
		//��ȡ��Ӧ�浵������
		readFile(i);

		//��ӡ���
		CursorJump(x - 3, y + 2);
		setColor(0x0f);
		cout << i<<"-----";//�����ӡ�ǰ�ɫ


		//�յ�չʾ
		if (aGamer.checkPoint == 0) {

			//�߿򣺰�ɫ
			CursorJump(x, y);
			setColor(0x0f);
			for (int k = 1; k <= 5; k++) {
				if (k!= 1 && k != 5) {
					CursorJump(x, y - 1 + k);
					cout << "��";
					CursorJump(x + 34, y - 1 + k);
					cout << "��";
				}
				else {
					CursorJump(x, y - 1 + k);
					for (int g= 1; g <= 35; g++)cout << "��";

				}
			}

			//��Ϣ:NULL
			CursorJump(x + 8, y + 2);
			cout << "NULL";

		}


		//�ǿյ�չʾ
		else {
			CursorJump(x, y);
			setColor(aGamer.favorWindowsColor);
			for (int i = 1; i <= 5; i++) {
				if (i != 1 && i != 5) {
					CursorJump(x, y - 1 + i);
					cout << "��";
					CursorJump(x + 34, y - 1 + i);
					cout << "��";
				}
				else {
					CursorJump(x, y - 1 + i);
					for (int j = 1; j <= 35; j++)cout << "��";

				}
			}

			//��ӡ�浵��Ϣ
			CursorJump(x + 2, y + 2);
			setColor(aGamer.favorBottomColor);
			cout << "��";//չʾ��ط�����ɫ

			CursorJump(x + 4, y + 2);
			setColor(0x0f);
			cout << aGamer.name;//���id

			CursorJump(x + 15, y + 2);
			switch (aGamer.gamemode) {
			case 1:setColor(0x0a); cout << "��ͨģʽ"; break;
			case 2:setColor(0x0e); cout << "����ģʽ"; break;
			case 3:setColor(0x0c); cout << "����ģʽ"; break;
			case 4:setColor(0x08); cout << "����ģʽ"; break;
			}

			CursorJump(x + 20, y + 2);
			if (aGamer.ing == 1) { setColor(0x0e);      cout << "  ��Ϸ��"; }
			if (aGamer.ing == 0) { setColor(0x0f); cout << "δ������Ϸ"; }

			CursorJump(x + 26, y + 1);
			setColor(0x0f);
			if (aGamer.ing == 1) { cout << "��ǰ�÷֣�" << aGamer.score; }
			if (aGamer.ing == 0) { cout << "�ϴε÷֣�" << aGamer.score; }

			CursorJump(x + 26, y + 3);
			setColor(0x0f);
			cout << "��ߵ÷֣�" <<aGamer.highestScore;
			
		}
		y += 8;
	}//�����浵չʾ


	//������ת:������ұ��
	while (1) {
		char c = _getch();
		if (c != 0) {
			if (c == '1') {
				gamerNum = 1;
				break;
			}
			if (c == '2') {
				gamerNum = 2;
				break;
			}
			if (c == '3') {
				gamerNum = 3;
				break;
			}
		}
	}

	//�浵��������
	
	system("cls");

	readFile(gamerNum);//��������

	CursorJump(24, 8);
	setColor(0x0f);
	cout << "ѡ��Դ浵" << gamerNum << "�Ĳ���";

	//�յ���ǿյ��в�ͬ����
	
	//�յ�
	if (aGamer.checkPoint == 0) {

		CursorJump(24, 16);
		cout << "1-�����´浵";
		CursorJump(24, 24);
		cout << "B-����";


		//�������
		while (1) {
			char c = _getch();
			if (c != 0) {
				switch (c) {

					//�����´浵
				case '1':
					system("cls");
					fileInit(gamerNum);
					//readFile(gamerNum);
					newGameInit(); 
					gameBody();
					return;//�����´浵����Ϸ��ʼ��

				case'b':
				case'B':
					system("cls");
					fileChoose();
					return;
				}

			}
		}
	}



	//�ǿյ�
	if (aGamer.checkPoint == 1) {

		CursorJump(12, 16);
		cout << "1-�����´浵���Ǵ˴浵";
		CursorJump(34, 16);
		cout << "2-��ȡ�ô浵";
		CursorJump(27, 24);
		cout << "B-����";


		//�������
		while (1) {
			char c = _getch();
			if (c != 0) {
				switch (c) {

				case '1':
					system("cls");
					fileInit(gamerNum);
					//readFile(gamerNum);
					//dataDeconstruction();
					newGameInit();
					gameBody();
					return;//�����´浵����Ϸ��ʼ��


				case '2':
					system("cls");
					dataDeconstruction();//���ݽ⹹
					if (ing == 0)scoreReset();
					gameBody();
					return;

				case'b':
				case'B':
					system("cls");
					fileChoose();
					return;
				}

			}
		}
	}


	}

//33-�浵
void writeFile(int num) {

	//�������д��

	GamerFile.seekp((num-1) * sizeof(Gamer));//��ת����num����ҵ�λ�ý���д��
	//cout << "д��ǰ������ļ�ָ���λ�ã�" << GamerFile.tellp() << endl;
	GamerFile.write(reinterpret_cast<const char*>(&aGamer), sizeof(Gamer));//д���������
	//cout << "д�������ļ�ָ���λ�ã�" << GamerFile.tellp() << endl;


	//��Ϸ������д��
	GameFile .seekp((num -1) * sizeof(Game));//�ļ�ָ����ת
	GameFile.write(reinterpret_cast<const char*>(&aGame), sizeof(Game));

}

//34-����
 void readFile(int num) {


	////������ݶ�ȡ
	//ifstream GamerRead;
	//GamerRead.open("gamer.txt", ios::in | ios::binary);
	//GamerRead.seekg((num - 1) * sizeof(Gamer));//��ת����num����ҵ�λ�ý���д��
	//GamerRead.read(reinterpret_cast<char*>(&aGamer), sizeof(Gamer));//д���������
	//GamerRead.close();//�ر��ļ�



	////��Ϸ�����ݶ�ȡ
	//ifstream GameRead;
	//GameRead.open("game.txt", ios::in | ios::binary);
	//GameRead.seekg((num - 1) * sizeof(Game));//��ת����num����ҵ�λ�ý���д��
	//GameRead.read(reinterpret_cast<char*>(&aGame), sizeof(Game));//д���������
	//GameRead.close();//�ر��ļ�


	//������ݶ�ȡ

	GamerFile.seekg((num-1 ) * sizeof(Gamer));//��ת����num����ҵ�λ�ý���д��
	//cout << "��ȡǰ������ļ�ָ���λ�ã�" << GamerFile.tellg() << endl;
	GamerFile.read(reinterpret_cast<char*>(&aGamer), sizeof(Gamer));//д���������
	//GamerFile.seekg(0);
	//cout << "��ȡ������ļ�ָ���λ��:" << GamerFile.tellg() << endl;
	//��Ϸ�����ݶ�ȡ

	GameFile.seekg((num-1 ) * sizeof(Game));//��ת����num����ҵ�λ�ý���д��
	GameFile.read(reinterpret_cast<char*>(&aGame), sizeof(Game));//д���������



}

//35-�����ݷ���ṹ�����
void dataConstruction(){

	//��Ҳ����ṹ��
	aGamer.checkPoint = checkPoint;
	aGamer.name = name;
	aGamer.gamemode = gamemode;
	aGamer.favorMusic = favorMusic;
	aGamer.favorWindowsColor = favorWindowsColor;
	aGamer.favorBottomColor = favorBottomColor;
	aGamer.score = score;
	aGamer.highestScore = highestScore;
	aGamer.one = one;
	aGamer.two = two;
	aGamer.three = three;
	aGamer.four = four;
	aGamer.ing = ing;

	//��Ϸ�� �����ṹ��
	for (int i = 1; i <= 23; i++) {
		for (int j = 1; j <= 14; j++)
			aGame.chess[i][j] = thisGame.windowsShape[i][j];
	}

	aGame.curBlockPosX = curBlock.x;
	aGame.curBlockPosY = curBlock.y;
	aGame.curBlockShape = curBlock.shape;
	aGame.curBlockStatus = curBlock.status;
	aGame.curBlockColor = curBlock.color;

	aGame.nextBlockShape = nextBlock.shape;
	aGame.nextBlockStatus = nextBlock.status;
	aGame.nextBlockColor = nextBlock.color;


}

//36-���ṹ�������ֵ��ֵ����ǰ��Ϸ����
void dataDeconstruction(){

	//��Ҳ����ṹ��
	checkPoint =aGamer. checkPoint;
	name = aGamer.name;
	gamemode=aGamer.gamemode;
	favorMusic=aGamer.favorMusic ;
	favorWindowsColor=aGamer.favorWindowsColor ;
	favorBottomColor=aGamer.favorBottomColor ;
	score=aGamer.score;
	highestScore = aGamer.highestScore;
	one=aGamer.one;
	two=aGamer.two;
	three=aGamer.three;
	four=aGamer.four;
	ing = aGamer.ing;

	//��Ϸ�� �����ṹ��
	for (int i = 1; i <= 23; i++) {
		for (int j = 1; j <= 14; j++)
			thisGame.windowsShape[i][j]=aGame.chess[i][j];
	}

	curBlock.x=aGame.curBlockPosX ;
	curBlock.y=aGame.curBlockPosY;
	curBlock.shape=aGame.curBlockShape ;
	curBlock.status=aGame.curBlockStatus ;
	curBlock.color=aGame.curBlockColor ;

	nextBlock.shape=aGame.nextBlockShape ;
	nextBlock.status=aGame.nextBlockStatus;
	nextBlock.color=aGame.nextBlockColor ;




}

//37-���д浵��ʼ��
//���ʼ�����浵����Ϊ�յ�
//��һ�ο�ʼ��Ϸ��Ҫ����һ��
void allFileInit() {


	for (int i = 1; i <= 3; i++) {

		fileInit(i);

	}


}

//38-�����浵��ʼ�������ڴ浵����
void fileInit(int num) {


	//��Ҳ���

	Gamer nullGamer;//�����

	GamerFile.seekp((num - 1) * sizeof(Gamer));
	GamerFile.write(reinterpret_cast<const char*>(&nullGamer), sizeof(Gamer));

	//��Ϸ������
	Game nullGame;//����Ϸ

	GameFile.seekp((num - 1) * sizeof(Game));//�ļ�ָ����ת
	GameFile.write(reinterpret_cast<const char*>(&nullGame), sizeof(Game));




}

//39-��Ϸ����
void play() {


	HideCursor();
	printStartAnim();
	//allFileInit();
	fileChoose();

	//�ر��ļ�
	GamerFile.close();
	GameFile.close();
}

//�ļ����ݼ��
void exami(int num) {

	if (!GamerFile||!GameFile) {
		cout << "���ļ�����" << endl;
			return;
	}

	readFile(num);
	//cout << "����ļ�ָ���λ��:" << GamerFile.tellg() << endl;
	cout << "���" << num << endl;
	cout << "checkpoint:" << aGamer.checkPoint << endl;
	cout << "name:" << aGamer.name << endl;
	cout << "gamemode:" << aGamer.gamemode << endl;
	cout << "favormusic:" << aGamer.favorMusic << endl;
	cout << "favorwin:" << aGamer.favorWindowsColor << endl;
	cout << "favorbo:" << aGamer.favorBottomColor << endl;
	cout << "score:" << aGamer.score << endl;
	cout << aGamer.one << " " << aGamer.two << " " << aGamer.three << " " << aGamer.four
		<< endl;
	cout << "ing:" << aGamer.ing << endl;


}

//40-�ر��ļ�
void closefile() {

	GamerFile.close();
	GameFile.close();
}

//41-���id����
void setName() {

	int ss = 600;

	CursorJump(24, 8);
	setColor(0x0f);
	cout << "��������ǣ�";

	//����id
	while (1) {

		CursorJump(24, 12);
		getline(cin,name);
		//�Ϸ��Լ�⣺size���Ȳ��ܳ���14
		//���Ϸ�����ʾ����������
		if (name.length() > 14) {
			CursorJump(24, 12);
			for (int j = 1; j <= name.length(); j++)cout << " ";//�������
			CursorJump(22, 16);
			cout << "��������е�̫����Ŷ......";
			continue;
		}

		//�Ϸ�������ѭ��
		break;

	}

	Sleep(ss);
	system("cls");

	CursorJump(24, 8);
	cout << name << ",";

	Sleep(ss);
	CursorJump(24, 12);
	cout << "��ӭ";

	Sleep(ss);
	system("cls");

}

//42-���������߷�����
int setAgamerHscore() {

	if (score >= highestScore) {

		highestScore = score;

		return 1;
	}

	else { return 0; }
}

//43-չʾ���а�
void showRankinglist(int exceed) {

	string id[4] = { "0" };
	double actualScore[4] = { 0 };//ʵ�ʵ÷�����
	int rank[4] = { 0,1,2,3 };//����

	for (int i = 1; i <= 3; i++) {

		//��ȡ�����Ϣ
		readFile(i);

		//�÷ֱ�������
		double ratio = 1;
		switch (aGamer.gamemode) {
		case 1:ratio = 0.8; break;
		case 2:ratio = 1; break;
		case 3:ratio = 1.2; break;
		case 4:ratio = 1.5; break;

		}
		//��¼���id
		id[i] = aGamer.name;
		//��¼�浵ʵ�ʵ÷�
		actualScore[i] = aGamer.highestScore * ratio;
	}

	//����
	if (actualScore[1] >= actualScore[2]) {
		if (actualScore[1] >= actualScore[3]) {
			if (actualScore[2] >= actualScore[3]) {
				rank[1] = 1; rank[2] = 2; rank[3] = 3;
			}
			else { rank[1] = 1; rank[2] = 3; rank[3] = 2; }
		}
		else { rank[1] = 3; rank[2] = 1; rank[3] = 2; }
	}
	else {
		if (actualScore[2] >= actualScore[3]) {
			if (actualScore[1] >= actualScore[3]) {
				rank[1] = 2; rank[2] = 1; rank[3] = 3;
			}
			else {
				rank[1] = 2; rank[2] = 3; rank[3] = 1;
			}

		}
		if (actualScore[3] > actualScore[2])
		{
			rank[1] = 3; rank[2] = 2; rank[3] = 1;
		}



	}

	//�÷ּ�����ʾ
	int k = 4;
	CursorJump(k+2, 4);
	setColor(0x0f);
	cout << "�÷ֱ���";
	CursorJump(k, 6);
	cout << "��ͨģʽ��  X0.8";
	CursorJump(k, 8);
	cout << "����ģʽ��  X1.0";
	CursorJump(k, 10);
	cout << "����ģʽ��  X1.2";
	CursorJump(k, 12);
	cout << "����ģʽ��  X1.5";





	//���а�չʾ
	CursorJump(25, 5);
	setColor(0x0f);
	cout << "�� �� ��";

	CursorJump(21, 5);
	setColor(0x05);
	cout << "����";
	CursorJump(30, 5);
	setColor(0x0b);
	cout<< "����";

	setColor(0x0f);
	CursorJump(19, 8);
	cout << "����" << setw(14) << "���" << setw(15) << "����" << setw(14);
	for (int i = 1; i <= 3; i++) {
		CursorJump(13, 10 + 2 * (i - 1));
		cout << i << setw(18) << id[rank[i]] << setw(13) << actualScore[rank[i]] << setw(14);
	}

	CursorJump(22, 18);
	setColor(0x0f);
	cout << "-��B����-";
	//���ز���
	while (1) {
		char c = _getch();
		if (c != 0) {

			if (c == 'b' || c == 'B') {
				system("cls");
				printTail(exceed);
				return;
			}

		}




	}

}