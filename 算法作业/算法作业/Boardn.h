#pragma once
class Boardn
{
private:
	int** board; //棋盘数组指针
	int n; //棋盘规模为n by n,其中n=2^k
	int dx; //噪点横纵坐标
	int dy;
	Boardn& operator=(Boardn&);
public:
	Boardn();
	Boardn(int an);
	Boardn(const Boardn& bd);
	bool setGap(const int& x, const int& y); //设置噪点，值为-1表示该点为噪点
	int getN()const; //返回棋盘规模
	int getDx() const; //返回噪点横纵坐标
	int getDy() const; 
	void setvp(int x, int y, int v); //为棋盘格子填充值
	void show()const; //棋盘输出
	~Boardn();
};

