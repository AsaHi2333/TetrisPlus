
//游戏逻辑模块

#pragma once


#include<time.h>
#include<iostream>
using namespace std;


//0-游戏主体
void gameBody();

//1-绘制游戏区边框
void windowPrint(int x, int y);//参数是需要打印的位置

//2-新游戏初始化
void newGameInit();

//3-打印操作说明
void rightInfo();

//4-打印游戏分数
void printScore();

//5-游戏音乐选择
void musicChoose();

//6-游戏区左侧信息区
void leftInfo();

//7-边框颜色偏好选择
void favorWindowsColorChoose();

//8-落地方块颜色偏好选择
void favorBottomColorChoose();

//9-产生游戏区第一个方块
void creatFirstBlock();//作为Block类的友元

//10-在信息区产生下一个方块的提示
void creatNextBlock();//Block类友元

//11-拷贝方块
void blockCopy();

//12-方块下移
int blockDown(int n);

//13-方块左移
void blockLeft();

//14-方块右移
void blockRight();

//15-方块旋转
void blockRotate();

//16-方块触底
void blockBottom(int b);//b是游戏区的底部

//17-碰撞合法性检测
int crash(int x, int y, int shape, int status);

//18-保存方块
void blockSave();

//19-刷新游戏区
void updateGame(int n);

//20-游戏暂停
void pauseGame();

//21-消行检测
void lineClear();

//22-消行下移
void lineDown(int line);

//23-游戏结束动画
void printTailAnim();

//24-重置游戏得分
void scoreReset();

//25-重新开始游戏
void gameRestart();

//26-游戏结束界面打印
void printTail(int exceed);

//27-游戏封面打印
void printStart(int x, int y);

//28-游戏封面动画清除
void deleteStart(int x, int y);

//29-游戏封面动画打印
void printStartAnim();

//30-游戏模式设置
void gameModeSet(int, double&);

//31-游戏模式选择界面
void gameModeChoose();

//32-存档选择界面
void fileChoose();

//33-存档
void writeFile(int);

//34-读档
void readFile(int);

//35-将数据放入结构体变量
void dataConstruction();

//36-将结构体变量的值赋值给当前游戏数据
void dataDeconstruction();

//37-所有存档初始化
void allFileInit();

//38-单个存档初始化
void fileInit(int);

//39-游戏运行
void play();

//测试文件读取
void exami(int);

//40-关闭文件
void closefile();

//41-玩家id设置
void setName();

//42-单个玩家最高分设置
int setAgamerHscore();

//43-展示排行榜
void showRankinglist(int);