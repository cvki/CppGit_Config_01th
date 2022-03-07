/***2021-11-9.buaa算法作业——残缺棋盘覆盖问题
* 注明：控制台输出，无UI界面显示。
**/
#include<iostream>
#include<iomanip>
using namespace std;

//棋盘容量
const int MAXS = 1024;
const int MINX = 16;
int SIZE=MINX; //棋盘规模
int board[MAXS][MAXS];//棋盘
int xbd, ybd;//噪点坐标
int counts = 0; //基本操作计数

//棋盘覆盖操作
void setvp(int x,int y,int v) {
	board[x][y] = v;
}
//输入数据处理
bool input(int size, int x, int y) {//噪点坐标从0开始
	if (size > MINX && size <= MAXS)
		SIZE = size;
	if (x >= 0 && x < SIZE && y >= 0 && y < SIZE) {
		//board[x][y] = 0;  //值为0表示噪点
		xbd = x;
		ybd = y;
		return true;
	}
	cerr << "输入有误！" << endl;
	return false;
}
//输出棋盘内容
void show() {
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			if (j)
				cout <<setw(3) << board[i][j];
			else
				cout << setw(3) << board[i][j];
		}
		cout << endl;
	}
}

//覆盖棋盘功能主逻辑,a表示棋盘原点坐标（这里取左上方作为原点），d表示噪点坐标，step表示棋盘横纵长
void cover(int ax, int ay, int step, int dx, int dy) {
	//++counts;
	if (step == 1)
		return;
	else {//分治
		step /= 2; //划分棋盘
		int nextx = ax + step;
		int nexty = ay + step;
		//以噪点所在位置进行分类讨论
		if (dx < nextx && dy < nexty) {//左上
			//对其它三个子棋盘进设置伪噪点，该位置恰好能用一个单位填充
			setvp(nextx - 1, nexty, 1); //右上
			setvp(nextx, nexty - 1, 1); //左下
			setvp(nextx, nexty, 1);	//右下
			++counts;
			//递归子问题
			cover(ax, ay, step, dx, dy);//递归左上
			cover(ax, nexty, step, nextx - 1, nexty);//递归右上
			cover(nextx, ay, step, nextx, nexty - 1);//递归左下
			cover(nextx, nexty, step, nextx, nexty);//递归右下
		}
		else if (dx < nextx && dy >= nexty) {//右上
			//同理
			setvp(nextx - 1, nexty - 1, 2);
			setvp(nextx, nexty - 1, 2);
			setvp(nextx, nexty, 2);
			++counts;
			cover(ax, ay, step, nextx - 1, nexty - 1);
			cover(ax, nexty, step, dx, dy);
			cover(nextx, ay, step, nextx, nexty - 1);
			cover(nextx, nexty, step, nextx, nexty);
		}
		else if (dx >= nextx && dy < nexty) {//左下
			setvp(nextx - 1, nexty - 1, 3);
			setvp(nextx - 1, nexty, 3);
			setvp(nextx, nexty, 3);
			++counts;
			cover(ax, ay, step, nextx - 1, nexty - 1);
			cover(ax, nexty, step, nextx - 1, nexty);
			cover(nextx, ay, step, dx, dy);
			cover(nextx, nexty, step, nextx, nexty);
		}
		else {//右下
			setvp(nextx - 1, nexty - 1, 4);
			setvp(nextx - 1, nexty, 4);
			setvp(nextx, nexty - 1, 4);
			++counts;
			cover(ax, ay, step, nextx - 1, nexty - 1);
			cover(ax, nexty, step, nextx - 1, nexty);
			cover(nextx, ay, step, nextx, nexty - 1);
			cover(nextx, nexty, step, dx, dy);
		}
	}
}

int main() {
	int size,x,y;
	cout << "请输入棋盘规模和噪点坐标(size,x,y):" << endl;
	cin >> size >> x >> y;
	if (input(size, x, y)) {
		cover(0, 0, SIZE, xbd, ybd);
		show();
	}	
	cout << "counts=" << counts << endl;
	system("pause");
	return 0;
}