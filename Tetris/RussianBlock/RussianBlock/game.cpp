
//游戏逻辑模块

#include"callWin.h"
#include"data.h"
#include"game.h"
#include<time.h>
#include<conio.h>//_kebhit() _getch()

#include<iostream>
#include<iomanip>
#include<string>
#include<cstdlib>//格式转换
#include<fstream>//文件处理

#include<mmsystem.h>
#pragma comment(lib,"winmm.lib")//播放音乐头文件
using namespace std;

//玩家的参数结构体，用于写入和读入游戏参数
struct Gamer {

	int checkPoint = 0;//记录是否为空档
	string name="null";//玩家id
	int gamemode = 1;//游戏模式
	int favorMusic = 0;//背景音乐偏好
	int favorWindowsColor =0x0f;//边框颜色偏好
	int favorBottomColor = 0x0f;//落地方块颜色偏好
	int score = 0;//游戏得分
	int highestScore = 0;//游戏最高得分
	int one = 0, two = 0, three = 0, four = 0;//消去的行数
	int ing = 1;//记录是否正在进行游戏

};

struct Game {
	
	int chess[30][30] = {0};//记录游戏区
	//游戏区长度是23x14，为了对应下标，chess数组开大一点

	//当前方块信息
	int curBlockPosX;
	int curBlockPosY;
	int curBlockShape;
	int curBlockStatus;
	int curBlockColor;

	//下一个方块信息
	int nextBlockShape;
	int nextBlockStatus;
	int nextBlockColor;


};

//本次需要记录的游戏参数

int checkPoint = 0;//记录是否为空档
string name="null";//玩家id
int gamemode = 1;//游戏模式:
int favorMusic = 1;//背景音乐偏好
int favorWindowsColor=0x00;//边框颜色偏好
int favorBottomColor=0x00;//落地方块颜色偏好
int score = 0;//游戏得分
int highestScore = 0;//游戏最高得分
int one = 0, two = 0, three = 0, four = 0;//消去的行数
int ing = 1;//记录是否正在游戏


//玩家编号
int gamerNum = 1;


//结构体变量，便于存取和读取
Gamer aGamer;
Game aGame;

Windows thisGame;//游戏窗口对象
Windows t;//中间量，用于和thisGame相关操作
Block curBlock;//方块对象：现在的方块
Block nextBlock;//方块对象：下一个方块


fstream GamerFile("gamer.txt", ios::out | ios::in | ios::binary);
fstream GameFile("game.txt", ios::out | ios::in | ios::binary);

//储存音乐名称便于显示
string musicName[9] = {
	"NULL",
	"ROLLING GILR --MIKU",
	"烟 distance --丁真珍珠",
	"日光稻香 --张聪聪",
	"旅途前方 --明日方舟HyperGryph",
	"Liebestraum --Franz Liszt",
	"Represent --DJ OKAWARI",
	"let him tell his story --梶浦由记",
	"向着遥远的天空 --市川淳",
};



//函数

//0-游戏主体
void gameBody() {

	windowPrint(15, 0);//打印游戏边框

	creatFirstBlock();//生成第一个方块

	leftInfo();//打印右侧信息区；

	rightInfo();//打印左侧信息区;

	creatNextBlock();//生成第一个方块

	//播放音乐
	switch (favorMusic) {

	case 1:mciSendString(L"open 1.mp3 alias a", NULL, 0, NULL); break;
	case 2:mciSendString(L"open 2.mp3 alias a", NULL, 0, NULL); break;
	case 3:mciSendString(L"open 3.mp3 alias a", NULL, 0, NULL); break;
	case 4:mciSendString(L"open 4.mp3 alias a", NULL, 0, NULL); break;
	case 5:mciSendString(L"open 5.mp3 alias a", NULL, 0, NULL); break;
	case 6:mciSendString(L"open 6.mp3 alias a", NULL, 0, NULL); break;
	case 7:mciSendString(L"open 7.mp3 alias a", NULL, 0, NULL); break;
	case 8:mciSendString(L"open 8.mp3 alias a", NULL, 0, NULL); break;

	}//打开音乐文件
	mciSendString(TEXT("play a repeat"), NULL, 0, NULL);//设置为循环播放

	double speed = 0.60;
	gameModeSet(gamemode, speed);

	//游戏主体
	//从这里开始就开始了一次游戏，退出while循环算一次游戏的结束
	//设置定时器：
	clock_t time1, time2;
	time1 = clock();

	while (1) {


		//检测键盘是否有输入
		//方块的一次行为
		//char input = _getch();
		if (_kbhit()) {
			
			//不同按键来设置方块行为
			switch (_getch()) {

				//旋转
			case'w':
			case'W':
			case 72://向上箭头
				blockRotate();
				break;

				//左移
			case'a':
			case'A':
			case 75://向左箭头
				blockLeft();
				break;

				//右移
			case'd':
			case'D':
			case 77:
				blockRight();
				break;

				//下移
			case's':
			case'S':
			case 80:
				blockDown(1);
				break;

				//暂停
			case 32://空格
				pauseGame();
				break;

				//回车：
			case 13://Enter
				blockBottom(1);
				break;

			//跳转到存档选择界面
			case 'b':
			case'B':

				checkPoint = 1;//将存档属性设置为非空档
				ing = 1;//游戏进行中

				dataConstruction();//数据结构化
				writeFile(gamerNum);//存档
				system("cls");
				mciSendString(TEXT("close a"), NULL, 0, NULL);//停止音乐播放

				fileChoose();//跳转至存档选择界面
				return;
			
			}
		}
		time2 = clock();

		//0.65是下落间隔：可以作为游戏难度更改
		if (time2 - time1 > speed * CLOCKS_PER_SEC) {

			if (blockDown(1) == 2) {
				//由于if里面的语句，无论是否按键都会下落
				break;//如果堆满了就游戏结束,break退出了游戏循环

			}
			time1 = time2;//重置时间间隔
		}
	}
	//到此处结束一次游戏

	
	checkPoint = 1;//存档属性设置为非空档
	ing = 0;//一次游戏结束
	thisGame.windowsReset();//游戏区清零
	int exceed=setAgamerHscore();
	dataConstruction();//游戏数据结构化

	writeFile(gamerNum);//存档


	printTailAnim();//打印游戏结束时的填充动画
	printTail(exceed);//打印结束界面
}

//1-绘制界面边框
void windowPrint(int x, int y)
{
	for (int i = 0; i <= 24; i++) {
		for (int j = 0; j <= 25;j++) {
			if (thisGame.windowsShape[i][j] == 1) {
				setColor(favorWindowsColor);
				CursorJump(x + j, y + i);
				cout << "■";
			}

		}

	}


}

//2-新游戏初始化
void newGameInit() {

	//初始化句柄
	initHandle();

	//游戏区清零
	thisGame.windowsReset();

	//分数重置
	scoreReset();

	//玩家自己起名
	setName();


	gameModeChoose();//选择游戏模式

	musicChoose();//选择音乐

	favorWindowsColorChoose();//边框颜色偏好选择
	favorBottomColorChoose();//落地方块颜色偏好选择


}

//3-打印右侧说明
void rightInfo(){
	CursorJump(33, 1);
	setColor(0x0f);
	cout << "下一个方块";

	CursorJump(33, 9);
	cout << "得分情况：";

	CursorJump(31, 11);
	cout << "消去一行：";
	CursorJump(37, 11);
	cout << 0;

	CursorJump(31, 13);
	cout << "消去两行:";
	CursorJump(37, 13);
	cout << 0;

	CursorJump(31, 15);
	cout << "消去三行:";
	CursorJump(37, 15);
	cout << 0;

	CursorJump(31, 17);
	cout << "消去四行:";
	CursorJump(37, 17);
	cout << 0;

	CursorJump(31, 19);
	cout << "总得分：";
	CursorJump(37, 19);
	cout << 0;



}

//4-打印游戏分数
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
	//得分权重：一行：10分 两行：30分 三行：50分 4行：80分

	score = one * 10 + two * 30 + three * 50 + four * 80;

	CursorJump(37, 19);
	cout << score;


}

//5-游戏音乐选择：
void musicChoose() {

	CursorJump(24, 4);
	setColor(0x0f);
	cout << "选择你喜欢的游戏背景音乐：";

	CursorJump(18, 7);
	cout << "1 - ROLLING GILR --MIKU";

	CursorJump(18, 9);
	cout << "2 - 烟 distance --丁真珍珠";

	CursorJump(18, 11);
	cout << "3 - 日光稻香 --张聪聪";

	CursorJump(18, 13);
	cout << "4 - 旅途前方 --明日方舟HyperGryph";

	CursorJump(18, 15);
	cout << "5 - Liebestraum --Franz Liszt";

	CursorJump(18, 17);
	cout << "6 - Represent --DJ OKAWARI";

	CursorJump(18, 19);
	cout << "7 - let him tell his story --梶浦由记";

	CursorJump(18, 21);
	cout << "8 - 向着遥远的天空 --市川淳";

	//游戏音乐设置
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
	cout << "你选择的背景音乐是：";

	CursorJump(25, 12);
	Sleep(700);
	cout << musicName[favorMusic];

	CursorJump(25, 20);
	Sleep(700);
	cout <<"即将进入边框方块选择......";

	Sleep(700);
	system("cls");
}

//6-左侧信息区:显示操作说明、玩家信息、存档等
void leftInfo() {

	//玩家信息打印

	//展示所选方块
	setColor(favorWindowsColor);
	CursorJump(1, 1); cout << "■■■";
	CursorJump(1, 2); cout << "■";
	CursorJump(3, 2); cout << "■";
	CursorJump(1, 3); cout << "■■■";
	setColor(favorBottomColor);
	CursorJump(2, 2); cout << "■";
	//玩家id、游戏模式、音乐
	setColor(0x0f);

	CursorJump(3+(10-name.length()/2)/2, 2);
	cout << name;

	CursorJump(6, 5); 
	if (gamemode == 1)cout << "普通模式";
	if (gamemode == 2)cout << "困难模式";
	if (gamemode == 3)cout << "极限模式";
	if (gamemode == 4)cout << "梦魇模式";

	CursorJump(1, 6); cout << "BGM:";
	switch (favorMusic) {

	case 1:CursorJump(3, 8); cout << musicName[1]; break;
	case 2:CursorJump(2, 8); cout << musicName[2]; break;
	case 3:CursorJump(3, 8); cout << musicName[3]; break;
	case 4:CursorJump(5, 7);
			  cout << "旅途前方";
			  CursorJump(2, 9);
			  cout << "--明日方舟HyperGryph";
			  break;
	case 5:CursorJump(1, 8); cout << musicName[5]; break;
	case 6:CursorJump(2, 8); cout << musicName[6]; break;
	case 7:CursorJump(2, 7);
		cout << "let him tell his story";
		CursorJump(4, 9);
		cout << "--梶浦由记"; 
		break;
		
	case 8:CursorJump(2, 8); cout << musicName[8]; break;
	}


	"旅途前方 --明日方舟HyperGryph",
		"Liebestraum --Franz Liszt",
		"Represent --DJ OKAWARI",
		"let him tell his story --梶浦由记",



	//操作说明打印
	setColor(0x0f);
	CursorJump(3, 11);
	cout <<"a  A  左箭头  左移";
	CursorJump(3, 13);
	cout << "d  D  右箭头  右移";
	CursorJump(3, 15);
	cout << "w  W  上箭头  旋转";
	CursorJump(3, 17);
	cout << "s S 下箭头  加速";
	CursorJump(3, 19);
	cout << "ENTER  瞬间落地";
	CursorJump(3, 21);
	cout << "SPACE  暂停/继续";
	CursorJump(3, 23);
	cout << "b B  返回存档界面";

	
}

//7-边框颜色偏好选择
void favorWindowsColorChoose(){

	CursorJump(24, 4);
	cout << "选择你喜欢的边框方块：";
	int i = 8;
	int k = 5;
	//横行：逐次加8
	// 竖行：逐次加5
	//1
	CursorJump(14, 8);
	setColor(0x0f);//字体说明为白色
	cout << "0 - 珊瑚";
	CursorJump(16, 10);
	setColor(0x1d);//方块颜色展示
	cout << "■";
	//2
	CursorJump(14+i, 8);
	setColor(0x0f);
	cout << "1 - 月食";
	CursorJump(16+i, 10);
	setColor(0xe0);
	cout << "■";
	//3
	CursorJump(14+2*i, 8);
	setColor(0x0f);
	cout << "2 - 底层";
	CursorJump(16+2*i, 10);
	setColor(0x4f);
	cout << "■";
	//4
	CursorJump(14+3*i, 8);
	setColor(0x0f);
	cout << "3 - 祈祷";
	CursorJump(16+3*i, 10);
	setColor(0xfb);
	cout << "■";
	 
	//2行
	//5
	CursorJump(14, 8+k);
	setColor(0x0f);//字体说明为白色
	cout << "4 - 办公室";
	CursorJump(16, 10+k);
	setColor(0x8f);//方块颜色展示
	cout << "■";
	//6
	CursorJump(14+i, 8+k);
	setColor(0x0f);
	cout << "5 - 蓝月";
	CursorJump(16+i, 10+k);
	setColor(0x4b);
	cout << "■";
	//7
	CursorJump(14+2*i, 8+k);
	setColor(0x0f);
	cout << "6 - 充能";
	CursorJump(16+2*i, 10+k);
	setColor(0x4e);
	cout << "■";
	//8
	CursorJump(14+3*i, 8+k);
	setColor(0x0f);
	cout << "7 - 斑斓";
	CursorJump(16+3*i, 10+k);
	setColor(0xdc);
	cout << "■";

	//3行
	//9
	CursorJump(14, 8 + 2*k);
	setColor(0x0f);//字体说明为白色
	cout << "8 - 太空舱";
	CursorJump(16, 10 + 2*k);
	setColor(0xf0);//方块颜色展示
	cout << "■";
	//10
	CursorJump(14 + i, 8 +2* k);
	setColor(0x0f);
	cout << "9 - 细菌";
	CursorJump(16 + i, 10 +2* k);
	setColor(0xa2);
	cout << "■";
	//11
	CursorJump(14 + 2 * i, 8 +2* k);
	setColor(0x0f);
	cout << "a - 黄沙";
	CursorJump(16 + 2 * i, 10 +2* k);
	setColor(0x6e);
	cout << "■";
	//12
	CursorJump(14 + 3 * i, 8 +2* k);
	setColor(0x0f);
	cout << "b - 深空";
	CursorJump(16 + 3 * i, 10 + 2*k);
	setColor(0x19);
	cout << "■";


	//4行
	//13
	CursorJump(14, 8 +3* k);
	setColor(0x0f);//字体说明为白色
	cout << "c - 探照";
	CursorJump(16, 10 + 3*k);
	setColor(0x8b);//方块颜色展示
	cout << "■";
	//14
	CursorJump(14 + i, 8 +3* k);
	setColor(0x0f);
	cout << "d - 草坪";
	CursorJump(16 + i, 10 + 3*k);
	setColor(0xae);
	cout << "■";
	//15
	CursorJump(14 + 2 * i, 8 + 3*k);
	setColor(0x0f);
	cout << "e - 石灰";
	CursorJump(16 + 2 * i, 10 +3* k);
	setColor(0xf7);
	cout << "■";
	//16
	CursorJump(14 + 3 * i, 8 +3* k);
	setColor(0x0f);
	cout << "f - 水草";
	CursorJump(16 + 3 * i, 10 +3* k);
	setColor(0x2a);
	cout << "■";

	CursorJump(22, 31);
	setColor(0x0f);
	cout << "——按下对应编号以选择——";


		while (1) {

			//设置颜色
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

	system("cls");//清屏

	int wait = 700;//提示出现间隔

	CursorJump(16, 3);
	setColor(0x0f);
	cout << "你选择了：";

	Sleep(wait);

	setColor(favorWindowsColor);
	for (int k = 1; k <= 3; k++) {

		for (int p = 1; p <= 3; p++) {
			CursorJump(25 + k, 9 + p);
			cout << "■";
		}

	}

	Sleep(wait);

	CursorJump(22, 20);
	setColor(0x0f);
	cout << "即将进入落地方块选择......";

	Sleep(wait);
	system("cls");
	Sleep(wait);
}

//8-落地方块颜色偏好选择
void favorBottomColorChoose() {

	CursorJump(24, 4);
	cout << "选择你喜欢的落地方块：";
	int i = 8;
	int k = 5;
	//横行：逐次加8
	// 竖行：逐次加5
	//1
	CursorJump(14, 8);
	setColor(0x0f);//字体说明为白色
	cout << "0 - 纯黑(非推荐选项)";
	CursorJump(16, 10);
	setColor(0x00);//方块颜色展示
	cout << "■";
	//2
	CursorJump(14 + i, 8);
	setColor(0x0f);
	cout << "1 - 深蓝";
	CursorJump(16 + i, 10);
	setColor(0x01);
	cout << "■";
	//3
	CursorJump(14 + 2 * i, 8);
	setColor(0x0f);
	cout << "2 - 暗绿";
	CursorJump(16 + 2 * i, 10);
	setColor(0x02);
	cout << "■";
	//4
	CursorJump(14 + 3 * i, 8);
	setColor(0x0f);
	cout << "3 - 暗青";
	CursorJump(16 + 3 * i, 10);
	setColor(0x03);
	cout << "■";

	//2行
	//5
	CursorJump(14, 8 + k);
	setColor(0x0f);//字体说明为白色
	cout << "4 - 暗红";
	CursorJump(16, 10 + k);
	setColor(0x04);//方块颜色展示
	cout << "■";
	//6
	CursorJump(14 + i, 8 + k);
	setColor(0x0f);
	cout << "5 - 暗粉";
	CursorJump(16 + i, 10 + k);
	setColor(0x05);
	cout << "■";
	//7
	CursorJump(14 + 2 * i, 8 + k);
	setColor(0x0f);
	cout << "6 - 暗黄";
	CursorJump(16 + 2 * i, 10 + k);
	setColor(0x06);
	cout << "■";
	//8
	CursorJump(14 + 3 * i, 8 + k);
	setColor(0x0f);
	cout << "7 - 暗灰";
	CursorJump(16 + 3 * i, 10 + k);
	setColor(0x07);
	cout << "■";

	//3行
	//9
	CursorJump(14, 8 + 2 * k);
	setColor(0x0f);//字体说明为白色
	cout << "8 - 亮灰";
	CursorJump(16, 10 + 2 * k);
	setColor(0x08);//方块颜色展示
	cout << "■";
	//10
	CursorJump(14 + i, 8 + 2 * k);
	setColor(0x0f);
	cout << "9 - 群青";
	CursorJump(16 + i, 10 + 2 * k);
	setColor(0x09);
	cout << "■";
	//11
	CursorJump(14 + 2 * i, 8 + 2 * k);
	setColor(0x0f);
	cout << "a - 亮绿";
	CursorJump(16 + 2 * i, 10 + 2 * k);
	setColor(0x0a);
	cout << "■";
	//12
	CursorJump(14 + 3 * i, 8 + 2 * k);
	setColor(0x0f);
	cout << "b - 亮蓝";
	CursorJump(16 + 3 * i, 10 + 2 * k);
	setColor(0x0b);
	cout << "■";


	//4行
	//13
	CursorJump(14, 8 + 3 * k);
	setColor(0x0f);//字体说明为白色
	cout << "c - 亮红";
	CursorJump(16, 10 + 3 * k);
	setColor(0x0c);//方块颜色展示
	cout << "■";
	//14
	CursorJump(14 + i, 8 + 3 * k);
	setColor(0x0f);
	cout << "d - 亮粉";
	CursorJump(16 + i, 10 + 3 * k);
	setColor(0x0d);
	cout << "■";
	//15
	CursorJump(14 + 2 * i, 8 + 3 * k);
	setColor(0x0f);
	cout << "e - 亮黄";
	CursorJump(16 + 2 * i, 10 + 3 * k);
	setColor(0x0e);
	cout << "■";
	//16
	CursorJump(14 + 3 * i, 8 + 3 * k);
	setColor(0x0f);
	cout << "f - 纯白";
	CursorJump(16 + 3 * i, 10 + 3 * k);
	setColor(0x0f);
	cout << "■";

	CursorJump(22, 31);
	setColor(0x0f);
	cout << "——按下对应编号以选择——";


	while (1) {

		//设置颜色
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

	system("cls");//清屏


	int wait = 700;//提示出现间隔

	CursorJump(16, 3);
	setColor(0x0f);
	cout << "你选择了：";

	Sleep(wait);

	setColor(favorBottomColor);
	for (int k = 1; k <= 3; k++) {

		for (int p = 1; p <= 3; p++) {
			CursorJump(25 + k, 9 + p);
			cout << "■";
		}

	}

	Sleep(wait);

	CursorJump(24, 20);
	setColor(0x0f);
	cout << "即将进入游戏......";

	Sleep(wait);
	system("cls");




}

//9-在游戏区产生第一个方块
void creatFirstBlock() {

	srand((unsigned int)time(NULL));//设置随机数种子；
	curBlock.x = 22;
	curBlock.y = 1;
	curBlock.shape = rand() %7;//有七种方块对应0-6数字，因此产生0-6的随机数
	curBlock.status = rand() % 4;//旋转状态随机
	curBlock.color = rand() % 0x10;//为方块设置随机的颜色


	//方块是黑色就不可见了，此处排除黑色的情况，但如果是第四种梦魇模式就不会删去黑方块
	if (curBlock.color == 0x00&&gamemode!=4) {

		curBlock.color = 0x0a;//设置成白色的
	}


	//打印方块
	curBlock.Print(curBlock.x, curBlock.y, curBlock.shape, curBlock.status, curBlock.color);



}

//10-在右侧信息区产生下一个方块提示
void creatNextBlock() {

	srand((unsigned int)time(NULL)+111);//设置随机数种子；
	nextBlock.x = 35;
	nextBlock.y = 3;

	nextBlock.Delete(nextBlock.x, nextBlock.y, nextBlock.shape, nextBlock.status, nextBlock.color);//在信息位置先覆盖后打印


	nextBlock.shape = rand() % 7;//有七种方块对应0-6数字，因此产生0-6的随机数
	nextBlock.status = rand() % 4;//旋转状态随机
	nextBlock.color = rand() % 0x10;//为方块设置随机的颜色


	//方块是黑色就不可见了，此处排除黑色的情况,4模式除外
	if (nextBlock.color == 0x00&&gamemode!=4) {

		nextBlock.color = 0x07;//设置成白色的
	}


	//打印
	nextBlock.Print(nextBlock.x, nextBlock.y, nextBlock.shape, nextBlock.status, nextBlock.color);

}

//11-拷贝方块:让游戏区的方块变为下一个方块
void blockCopy() {

	curBlock = nextBlock;//使用重载后的赋值运算符
	curBlock.x = 22;//重置坐标
	curBlock.y = 1;
	curBlock.Print(curBlock.x, curBlock.y, curBlock.shape, curBlock.status, curBlock.color);

	creatNextBlock();//当前方块复制了下一个方块的信息后，立刻更新下一个方块

}

//12-方块下移
//删去当前显示的方块，纵坐标加一，如果下落合法就再次打印出来
int blockDown(int n) {
	//下落发生了碰撞：到底了
	if (crash(curBlock.x, curBlock.y+1, curBlock.shape, curBlock.status) == 1)
	{
		//保存方块>消行>重新打印游戏区>产生新的方块
	blockSave();
	lineClear();
	updateGame(n);
	
	blockCopy();
	
	return 1;
	}
	//极端情况：方块一生成就发生碰撞：游戏结束
	else if (crash(curBlock.x, curBlock.y+1, curBlock.shape, curBlock.status) == 2) {
		return 2;
	}
	//不是极端情况，正常下落
	else {

		curBlock.Delete(curBlock.x, curBlock.y, curBlock.shape, curBlock.status, curBlock.color);
		curBlock.y += 1;
		curBlock.Print(curBlock.x, curBlock.y, curBlock.shape, curBlock.status, curBlock.color);
		return 0;

	}
	
}

//13-方块左移
void blockLeft() {
	//碰到左壁：什么都不做
	if (crash(curBlock.x-1, curBlock.y, curBlock.shape, curBlock.status)==1) {
		return ;
	}
	//没碰壁：往左移
	curBlock.Delete(curBlock.x, curBlock.y, curBlock.shape, curBlock.status, curBlock.color);
	curBlock.x-= 1;
	curBlock.Print(curBlock.x, curBlock.y, curBlock.shape, curBlock.status, curBlock.color);
}

//14-方块右移
void blockRight() {
	//碰到右壁：什么都不做
	if (crash(curBlock.x + 1, curBlock.y, curBlock.shape, curBlock.status) == 1) {
		return;
	}
	//没碰壁：往右移
	curBlock.Delete(curBlock.x, curBlock.y, curBlock.shape, curBlock.status, curBlock.color);
	curBlock.x += 1;
	curBlock.Print(curBlock.x, curBlock.y, curBlock.shape, curBlock.status, curBlock.color);
}

//15-方块旋转
void blockRotate() {
	//通过改变方块数组的status维度的值便可实现旋转
	//判断旋转是否合法
	if (crash(curBlock.x, curBlock.y, curBlock.shape, (curBlock.status + 1) % 4) == 1)//下个状态取余是为了让下标不超过3
	{
		//旋转会碰壁，什么都 不做
		return;
	}
	//旋转合法：状态改变
	curBlock.Delete(curBlock.x, curBlock.y, curBlock.shape, curBlock.status, curBlock.color);
	curBlock.status = (curBlock.status + 1) % 4;//下一个状态是随机的：0-3随机数
	curBlock.Print(curBlock.x, curBlock.y, curBlock.shape, curBlock.status, curBlock.color);//打印旋转后的方块


}

//16-方块触底:是否碰到了最下层
void blockBottom(int b)//b是游戏区的底部
{
	while (1) {
		//落到底部且消行
		if (crash(curBlock.x, curBlock.y+1, curBlock.shape, curBlock.status)==1)
		{

			//发生碰撞-保存方块-检测消行-更新游戏区-拷贝方块
			blockSave();
			lineClear();
			updateGame(b);
			blockCopy();
			return;

		}
		//
		else if (crash(curBlock.x, curBlock.y+1, curBlock.shape, curBlock.status) == 2) {
			//游戏结束
			return;
		}
		//
		else {
			curBlock.y++;
		}
	}


}

//17-碰撞合法性检测:通过检测下一个位置是否合法来返回值
//参数是下一个位置或者下一个形态
//碰撞函数的逻辑是以坐标为基点检测在方块的三乘三方阵中和对应棋盘的三乘三方阵中是否有1的重叠
int crash(int x, int y, int shape, int status) {
	
	for (int i = 0; i <= 3; i++) {
		for (int j = 0; j <= 3; j++) {
			if (curBlock.block[shape][status][i][j] == 1) 
			{
				//减去十五：棋盘和程序实际坐标设置是有一个偏差，这个偏差体现在游戏界面要在哪个地方显示
				//发生了碰撞
				if (thisGame.windowsShape[i + y][j + x - 15] == 1) {
					//提供一个额外的检测：一开始生成方块的位置就发生了碰撞：那么游戏就无法进行了
					//方块一产生就发生了碰撞
					if (curBlock.x == 22 && curBlock.y == 1) {
						return 2;
					}
					//其他形式的碰撞
					return 1;
				}
			}
		}
	}
	return 0;//没有发生任何形式的碰撞
}

//18-保存方块：保存落在底部不动的方块
//把方块的坐标对应到棋盘的坐标，相当于改变了棋盘上方块的存在情况
void blockSave(){
	for (int i = 0; i <= 3; i++) {
		for (int j = 0; j <= 3; j++) {

			if (curBlock.block[curBlock.shape][curBlock.status][i][j] == 1) {

				thisGame.windowsShape[i + curBlock.y][j + curBlock.x - 15] = 1;


			}
		}
	}
}

//19-刷新游戏区
void updateGame(int n) {

	//只需要在游戏区内操作就可以了，忽略边框
	//将i从23开始递减，因为是从底部开始打印的
	for (int i =23; i >=1; i--) {
		for (int j = 1; j <= 14; j++) {
			
			switch (n) {
			case 1:
				if (thisGame.windowsShape[i][j] == 1) {
					//设置落地方块的颜色
					setColor(favorBottomColor);
					CursorJump(15 + j, i);
					cout << "■";

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

//20-游戏暂停
void pauseGame() {

	CursorJump(32, 21);
	setColor(0x0e);
	cout << "--游戏暂停中--";
	while (1) {
		//按下空格暂停，空格的键码是32
		if (_getch() == 32) {
			break;
		}
	}
	CursorJump(32, 21);
	setColor(0x0f);
	cout << "              ";

}

//21-消行检测
//消行原理：游戏区某一行全部为一，则此行应该消去
void lineClear() {
	//通过遍历判断某一行是否满：数组一行的和为游戏区长度14
	 int number = 0;//记录消行的数量
	for (int i = 23; i >= 1; i -- ) {

		int total = 0;
		for (int j = 1; j <= 14; j++) {

			total += thisGame.windowsShape[i][j];

		}
		if (total == 14) {
			lineDown(i);//这一行满了，要进行下移操作:
			i += 1;//继续在这行看，是否还会产生消行
			number += 1;

		}

	}
	//可以设置一个显示消去行数的函数
	switch (number) {

	case 1:one++; break;
	case 2:two++; break;
	case 3:three++; break;
	case 4:four++; break;

	}
	printScore();
}

//22-消行下移
//传入一个参数:从第line行开始往上所有行向下平移一格
void lineDown(int line) {
//
	
	t = thisGame;


	for (int i = line; i > 1; i--) {
		for (int j = 1; j <= 14; j++) {

			thisGame.windowsShape[i][j] = t.windowsShape[i - 1][j];

		}
	}

}

//23-游戏结束动画
void printTailAnim() {

	for (int i = 23; i >= 1; i--) {
		for (int j = 1; j <= 14; j++) {

			setColor(0x3b);
			CursorJump(j + 15, i);
			cout << "■";
			Sleep(5);//停顿一下
		}
	}

	Sleep(700);//暂留时间

	setColor(0x00);//不把颜色设成黑色的话清屏会带有颜色
	system("cls");//清屏
}

//24-重置游戏得分
void scoreReset() {
	one = 0;
	two = 0;
	three = 0;
	four = 0;
	score = 0;
}

//25-重新开始游戏:指的是在当前存档的参数下重新游戏
void gameRestart(){


	thisGame.windowsReset();//重置游戏区

	scoreReset();//重置得分

	gameBody();//重新开始游戏

}

//26-游戏结束界面打印
void printTail(int exceed) {


	//打印结束界面动画：wasted.
	int w = 100;
	int t = 300;
	int x = 8;
	int y = 5;
	setColor(0x04);
	CursorJump(x, y);
	cout << "■      ■      ■      ■        ■■■■■   ■■■■■   ■■■■■   ■■■■";
	Sleep(w);
	CursorJump(x, y+1);
	cout << " ■    ■■    ■     ■  ■      ■               ■       ■           ■     ■";
	Sleep(w);
	CursorJump(x, y+2);
	cout << "  ■  ■  ■  ■     ■    ■     ■■■■■       ■       ■■■■■   ■     ■";
	Sleep(w); 
	CursorJump(x, y+3);
	cout << "   ■■    ■■     ■■■■■            ■       ■       ■           ■     ■";
	Sleep(w);
	CursorJump(x, y+4);
	cout << "    ■      ■     ■        ■   ■■■■■       ■       ■■■■■   ■■■■     ■";
	Sleep(t);
	//打印游戏总结：
	CursorJump(22, 13);
	setColor(0x0f);
	cout << "历史最高得分:	" << highestScore;
	CursorJump(22, 15);
	cout << "本次游戏得分:	" << score;
	if (exceed) { 
		Sleep(t+200);
		CursorJump(36, 15); 
		setColor(0x0e); 
		cout << "新纪录！"; 
	}
	Sleep(t+400);
	//进行选择操作
	CursorJump(24, 21);
	setColor(0x0f);
	cout << "按键以选择：";
	CursorJump(18, 24);
	cout << "N-结束游戏";
	CursorJump(30, 24);
	cout << "Y-重新开始游戏";
	CursorJump(30, 26);
	cout << "B-返回存档选择界面";
	CursorJump(18, 26);
	cout << "R-查看排行榜";
	

	
	while (1) {

		char c = _getch();
		if (c == 'n' || c == 'N') {

			system("cls");
			mciSendString(TEXT("close a"), NULL, 0, NULL);//停止音乐播放
			return;

		}
		if (c == 'y' || c == 'Y') {
			system("cls");
			mciSendString(TEXT("close a"), NULL, 0, NULL);//停止音乐播放
			gameRestart();
			break;
		}

		if (c == 'b' || c == 'B') {
			system("cls");
			mciSendString(TEXT("close a"), NULL, 0, NULL);//停止音乐播放
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

//27-游戏封面打印
void printStart(int x, int y) {

	//图案的颜色是随机的
	int color = rand() % 0x10;
	if (color == 0x00) {
		color = 0x0f;
	}

	//绘制封面图案
	setColor(color);
	CursorJump(x, y);
	cout<<"■■■■■  ■■■■■  ■■■■■  ■■■■■  ■  ■■■■■";
	CursorJump(x, y + 1);
	cout<<"    ■      ■              ■      ■      ■  ■  ■";
	CursorJump(x, y + 2); 
	cout<<"    ■      ■■■■■      ■      ■■■■■  ■  ■■■■■"; 
	CursorJump(x, y + 3); 
	cout<<"    ■      ■              ■      ■    ■    ■          ■"; 
	CursorJump(x, y + 4); 
	cout<<"    ■      ■■■■■      ■      ■    ■    ■  ■■■■■";
	//T E R I S

	//游戏开始操作打印
	CursorJump(25, 25); 
	cout << "按ENTER键开始游戏";


}

//28-游戏封面清除
void deleteStart(int x, int y) {

	for (int i = y; i <= y + 5; i++) {

		for (int j = x; j < x + 32; j++) {

			CursorJump(j, i);
			cout << " ";

		}
	}
}

//29-游戏封面动画打印
void printStartAnim() {
	CursorJump(3, 5);
	for (int k = 1; k <= 36; k++)
		cout << "☆ ";
	for (int k = 6; k <= 19; k++) {

		CursorJump(3, k); cout << "☆ ";
		CursorJump(55, k); cout << " ☆ ";

	}

	CursorJump(3, 20);
	for (int k = 1; k <= 36; k++)
		cout << "☆ ";




	clock_t time1, time2;
	time1 = clock();
	int x = 5;
	int head = 1;//记录标题向哪里移动：一开始往右：1
	printStart(x, 10);
	while (1) {
		
		time2 = clock();

		//每200毫秒大标题动一次
		if (time2 - time1 > 200) {

			time1 = time2;//时间再次设为一样
			if (head == 1) {

				deleteStart(x, 10);//删去本次画面
				printStart(++x, 10);//横坐标自加后再次打印画面

			}

			if (head == 0) {

				deleteStart(x, 10);
				printStart(--x, 10);

			}

			//标题右移到一定限度又会向左动
			if (x == 22) {

				head = 0;
				deleteStart(x, 10);
				printStart(--x, 10);

			}

			//向右又向左
			if (x == 5) {

				head = 1;
				deleteStart(x, 10);
				printStart(++x, 10);

			}

		}

		//检测键盘输入以退出封面开始游戏
		if (_kbhit()) {

			//输入回车退出
			if (_getch() == 13)break;
		}
	}
	system("cls");//退出开始动画之后，清屏以准备下一个界面的打印


}

//30-游戏模式设置
void gameModeSet(int Gamemode, double& Speed) {

	switch (Gamemode) {
	case 1:Speed = 0.60; break;
	case 2:Speed = 0.35; break;
	case 3:Speed = 0.25; break;
	case 4:Speed = 0.15; break;
	}
}

//31-游戏模式选择界面
void gameModeChoose() {

	
	CursorJump(24, 3);
	setColor(0x0f);
	cout << "选择你的游戏模式:";
	CursorJump(6, 7);
	setColor(0x0a);
	cout << "1--普通模式 ";
	CursorJump(20, 7);
	setColor(0x0e);
	cout << "2--困难模式 ";
	CursorJump(34, 7);
	setColor(0x0c);
	cout << "3--极限模式 ";
	CursorJump(48, 7);
	setColor(0x08);
	cout << "4--梦魇模式";

	setColor(0x0f);

	//普通模式说明
	CursorJump(5, 11);
	cout << "普通的Tetris难度。";
	CursorJump(5, 12);
	cout << "你将体验这个游戏";
	CursorJump(5, 13);
	cout<<"简单而令人上瘾的魅力。";

	//困难模式说明
	CursorJump(19, 10);
	cout << "*方块下落速度稍有增加";
	CursorJump(19, 12);
	cout << "你将领会这个游戏";
	CursorJump(19, 13);
	cout << "稍有困难而令人上瘾的魅力。";

	//极限模式说明
	CursorJump(33, 10);
	cout << "*方块下落速度急剧增加";
	CursorJump(33, 12);
	cout << "你将感受这个游戏";
	CursorJump(33, 13);
	cout << "刺激而具有挑战性的魅力。";

	//梦魇模式说明
	CursorJump(47, 10);
	cout << "*方块的下落速度令人发指";
	CursorJump(47, 11);
	cout << "*出现不可见的黑方块";
	CursorJump(47, 13);
	cout << "你将......";
	CursorJump(47, 14);
	cout << "祝你好运。";

	
	while (1) {
		char c;
		if ((c=_getch())!=0) {

			//普通
			if (c == '1') {
				gamemode = 1;
				break;
			}

			//困难
			if (c == '2') {
				gamemode = 2;
				break;
			}

			//极限
			if (c== '3') {
				gamemode = 3;
				break;
			}

			//梦魇
			if (c== '4') {
				gamemode = 4;
				break;
			}
		}
	}//结束进程阻塞

	system("cls");//清屏

}

//32-存档选择界面
void fileChoose(){

	CursorJump(29, 3);
	setColor(0x0f);
	cout << "选择存档以进行操作";

	//存档展示打印
	int x = 17, y = 7;
	for (int i = 1; i <= 3; i++) {
		//一个存档展示的打印
		
		//读取相应存档的数据
		readFile(i);

		//打印序号
		CursorJump(x - 3, y + 2);
		setColor(0x0f);
		cout << i<<"-----";//字体打印是白色


		//空档展示
		if (aGamer.checkPoint == 0) {

			//边框：白色
			CursorJump(x, y);
			setColor(0x0f);
			for (int k = 1; k <= 5; k++) {
				if (k!= 1 && k != 5) {
					CursorJump(x, y - 1 + k);
					cout << "■";
					CursorJump(x + 34, y - 1 + k);
					cout << "■";
				}
				else {
					CursorJump(x, y - 1 + k);
					for (int g= 1; g <= 35; g++)cout << "■";

				}
			}

			//信息:NULL
			CursorJump(x + 8, y + 2);
			cout << "NULL";

		}


		//非空档展示
		else {
			CursorJump(x, y);
			setColor(aGamer.favorWindowsColor);
			for (int i = 1; i <= 5; i++) {
				if (i != 1 && i != 5) {
					CursorJump(x, y - 1 + i);
					cout << "■";
					CursorJump(x + 34, y - 1 + i);
					cout << "■";
				}
				else {
					CursorJump(x, y - 1 + i);
					for (int j = 1; j <= 35; j++)cout << "■";

				}
			}

			//打印存档信息
			CursorJump(x + 2, y + 2);
			setColor(aGamer.favorBottomColor);
			cout << "■";//展示落地方块颜色

			CursorJump(x + 4, y + 2);
			setColor(0x0f);
			cout << aGamer.name;//玩家id

			CursorJump(x + 15, y + 2);
			switch (aGamer.gamemode) {
			case 1:setColor(0x0a); cout << "普通模式"; break;
			case 2:setColor(0x0e); cout << "困难模式"; break;
			case 3:setColor(0x0c); cout << "极限模式"; break;
			case 4:setColor(0x08); cout << "梦魇模式"; break;
			}

			CursorJump(x + 20, y + 2);
			if (aGamer.ing == 1) { setColor(0x0e);      cout << "  游戏中"; }
			if (aGamer.ing == 0) { setColor(0x0f); cout << "未进行游戏"; }

			CursorJump(x + 26, y + 1);
			setColor(0x0f);
			if (aGamer.ing == 1) { cout << "当前得分：" << aGamer.score; }
			if (aGamer.ing == 0) { cout << "上次得分：" << aGamer.score; }

			CursorJump(x + 26, y + 3);
			setColor(0x0f);
			cout << "最高得分：" <<aGamer.highestScore;
			
		}
		y += 8;
	}//结束存档展示


	//按键跳转:设置玩家编号
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

	//存档操作界面
	
	system("cls");

	readFile(gamerNum);//读入数据

	CursorJump(24, 8);
	setColor(0x0f);
	cout << "选择对存档" << gamerNum << "的操作";

	//空档与非空档有不同操作
	
	//空档
	if (aGamer.checkPoint == 0) {

		CursorJump(24, 16);
		cout << "1-建立新存档";
		CursorJump(24, 24);
		cout << "B-返回";


		//操作检测
		while (1) {
			char c = _getch();
			if (c != 0) {
				switch (c) {

					//建立新存档
				case '1':
					system("cls");
					fileInit(gamerNum);
					//readFile(gamerNum);
					newGameInit(); 
					gameBody();
					return;//建立新存档：游戏初始化

				case'b':
				case'B':
					system("cls");
					fileChoose();
					return;
				}

			}
		}
	}



	//非空档
	if (aGamer.checkPoint == 1) {

		CursorJump(12, 16);
		cout << "1-创建新存档覆盖此存档";
		CursorJump(34, 16);
		cout << "2-读取该存档";
		CursorJump(27, 24);
		cout << "B-返回";


		//操作检测
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
					return;//建立新存档：游戏初始化


				case '2':
					system("cls");
					dataDeconstruction();//数据解构
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

//33-存档
void writeFile(int num) {

	//玩家数据写入

	GamerFile.seekp((num-1) * sizeof(Gamer));//跳转到第num个玩家的位置进行写入
	//cout << "写入前，玩家文件指针的位置：" << GamerFile.tellp() << endl;
	GamerFile.write(reinterpret_cast<const char*>(&aGamer), sizeof(Gamer));//写入玩家数据
	//cout << "写入后，玩家文件指针的位置：" << GamerFile.tellp() << endl;


	//游戏区数据写入
	GameFile .seekp((num -1) * sizeof(Game));//文件指针跳转
	GameFile.write(reinterpret_cast<const char*>(&aGame), sizeof(Game));

}

//34-读档
 void readFile(int num) {


	////玩家数据读取
	//ifstream GamerRead;
	//GamerRead.open("gamer.txt", ios::in | ios::binary);
	//GamerRead.seekg((num - 1) * sizeof(Gamer));//跳转到第num个玩家的位置进行写入
	//GamerRead.read(reinterpret_cast<char*>(&aGamer), sizeof(Gamer));//写入玩家数据
	//GamerRead.close();//关闭文件



	////游戏区数据读取
	//ifstream GameRead;
	//GameRead.open("game.txt", ios::in | ios::binary);
	//GameRead.seekg((num - 1) * sizeof(Game));//跳转到第num个玩家的位置进行写入
	//GameRead.read(reinterpret_cast<char*>(&aGame), sizeof(Game));//写入玩家数据
	//GameRead.close();//关闭文件


	//玩家数据读取

	GamerFile.seekg((num-1 ) * sizeof(Gamer));//跳转到第num个玩家的位置进行写入
	//cout << "读取前，玩家文件指针的位置：" << GamerFile.tellg() << endl;
	GamerFile.read(reinterpret_cast<char*>(&aGamer), sizeof(Gamer));//写入玩家数据
	//GamerFile.seekg(0);
	//cout << "读取后，玩家文件指针的位置:" << GamerFile.tellg() << endl;
	//游戏区数据读取

	GameFile.seekg((num-1 ) * sizeof(Game));//跳转到第num个玩家的位置进行写入
	GameFile.read(reinterpret_cast<char*>(&aGame), sizeof(Game));//写入玩家数据



}

//35-将数据放入结构体变量
void dataConstruction(){

	//玩家参数结构化
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

	//游戏区 参数结构化
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

//36-将结构体变量的值赋值给当前游戏数据
void dataDeconstruction(){

	//玩家参数结构化
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

	//游戏区 参数结构化
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

//37-所有存档初始化
//把最开始三个存档设置为空档
//第一次开始游戏需要调用一次
void allFileInit() {


	for (int i = 1; i <= 3; i++) {

		fileInit(i);

	}


}

//38-单个存档初始化：用于存档覆盖
void fileInit(int num) {


	//玩家参数

	Gamer nullGamer;//空玩家

	GamerFile.seekp((num - 1) * sizeof(Gamer));
	GamerFile.write(reinterpret_cast<const char*>(&nullGamer), sizeof(Gamer));

	//游戏区数据
	Game nullGame;//空游戏

	GameFile.seekp((num - 1) * sizeof(Game));//文件指针跳转
	GameFile.write(reinterpret_cast<const char*>(&nullGame), sizeof(Game));




}

//39-游戏运行
void play() {


	HideCursor();
	printStartAnim();
	//allFileInit();
	fileChoose();

	//关闭文件
	GamerFile.close();
	GameFile.close();
}

//文件数据监测
void exami(int num) {

	if (!GamerFile||!GameFile) {
		cout << "打开文件错误" << endl;
			return;
	}

	readFile(num);
	//cout << "玩家文件指针的位置:" << GamerFile.tellg() << endl;
	cout << "玩家" << num << endl;
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

//40-关闭文件
void closefile() {

	GamerFile.close();
	GameFile.close();
}

//41-玩家id设置
void setName() {

	int ss = 600;

	CursorJump(24, 8);
	setColor(0x0f);
	cout << "你的名字是？";

	//输入id
	while (1) {

		CursorJump(24, 12);
		getline(cin,name);
		//合法性检测：size长度不能超过14
		//不合法：提示并重新输入
		if (name.length() > 14) {
			CursorJump(24, 12);
			for (int j = 1; j <= name.length(); j++)cout << " ";//清空输入
			CursorJump(22, 16);
			cout << "这个名字有点太长了哦......";
			continue;
		}

		//合法，跳出循环
		break;

	}

	Sleep(ss);
	system("cls");

	CursorJump(24, 8);
	cout << name << ",";

	Sleep(ss);
	CursorJump(24, 12);
	cout << "欢迎";

	Sleep(ss);
	system("cls");

}

//42-单个玩家最高分设置
int setAgamerHscore() {

	if (score >= highestScore) {

		highestScore = score;

		return 1;
	}

	else { return 0; }
}

//43-展示排行榜
void showRankinglist(int exceed) {

	string id[4] = { "0" };
	double actualScore[4] = { 0 };//实际得分数组
	int rank[4] = { 0,1,2,3 };//排名

	for (int i = 1; i <= 3; i++) {

		//读取玩家信息
		readFile(i);

		//得分比率设置
		double ratio = 1;
		switch (aGamer.gamemode) {
		case 1:ratio = 0.8; break;
		case 2:ratio = 1; break;
		case 3:ratio = 1.2; break;
		case 4:ratio = 1.5; break;

		}
		//记录玩家id
		id[i] = aGamer.name;
		//记录存档实际得分
		actualScore[i] = aGamer.highestScore * ratio;
	}

	//排序
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

	//得分计算显示
	int k = 4;
	CursorJump(k+2, 4);
	setColor(0x0f);
	cout << "得分倍率";
	CursorJump(k, 6);
	cout << "普通模式：  X0.8";
	CursorJump(k, 8);
	cout << "困难模式：  X1.0";
	CursorJump(k, 10);
	cout << "极限模式：  X1.2";
	CursorJump(k, 12);
	cout << "梦魇模式：  X1.5";





	//排行榜展示
	CursorJump(25, 5);
	setColor(0x0f);
	cout << "排 行 榜";

	CursorJump(21, 5);
	setColor(0x05);
	cout << "☆☆☆";
	CursorJump(30, 5);
	setColor(0x0b);
	cout<< "☆☆☆";

	setColor(0x0f);
	CursorJump(19, 8);
	cout << "排名" << setw(14) << "玩家" << setw(15) << "分数" << setw(14);
	for (int i = 1; i <= 3; i++) {
		CursorJump(13, 10 + 2 * (i - 1));
		cout << i << setw(18) << id[rank[i]] << setw(13) << actualScore[rank[i]] << setw(14);
	}

	CursorJump(22, 18);
	setColor(0x0f);
	cout << "-按B返回-";
	//返回操作
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