#include"callWin.h"
#include"data.h"
#include<iostream>
#include<conio.h>


//Chess
Chess::Chess() {
	//empty
}
Chess::~Chess() {
	//empty
}


//定义Windows类下的成员函数
Windows::Windows() {
	for (int i = 0; i <= 24; i++) {
		for (int j = 0; j <= 25; j++) {
			if (i == 7) {
				if (j >= 15||j==0)windowsShape[i][j] = 1;
			}

			else {
				if (i == 0 || i == 24)windowsShape[i][j] = 1;
				else {
					if (j == 0 || j == 15 || j == 25) {
						windowsShape[i][j] = 1;
						continue;
					}
				}

			}

		}
	}
}
Windows::~Windows(){}
 void Windows:: operator=(Windows& A) {

	 for (int i = 0; i <= 24; i++) {
		 for (int j = 0; j <= 25; j++)
			 windowsShape[i][j] = A.windowsShape[i][j];


	 }



}
 void Windows::windowsReset() {

	 for (int i = 1; i <= 23; i++)
		 for (int j = 1; j <= 14; j++)
			 windowsShape[i][j] = 0;

 }
 void Windows::Print(int x, int y, int shape, int status, int color){}
 void Windows::Delete(int x, int y, int shape, int status, int color){}


//定义Block类下的成员函数
 Block::Block()
	 :x(0), y(0), shape(0), status(0), color(0)
 {}
 Block::~Block(){}
void Block::Print(int x, int y, int shape, int status, int color) {
	for (int i = 0; i <=3; i++) {
		for (int j = 0; j<=3; j++) {

			if (block[shape][status][i][j] == 1) {
				setColor(color);
				CursorJump(x + j, y + i);
				cout << "■";//"■

		}




		}


	}


}
void Block:: Delete(int x, int y, int shape, int status, int color) {
	for (int i = 0; i <= 3; i++) {
		for (int j = 0; j <= 3; j++) {

			if (block[shape][status][i][j] == 1) {
				setColor(color);
				CursorJump(x + j, y + i);
				cout << " ";//相当于空格覆盖

			}




		}


	}



}
void Block::operator =(Block& a) {

	this->x = a.x;
	this->y = a.y;
	this->shape = a.shape;
	this->status = a.status;
	this->color = a.color;


}