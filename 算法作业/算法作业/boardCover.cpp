#include<iostream>
#include"Boardn.h"
using namespace std;



void cover(Boardn& bd,int ax, int ay, int step, int dx, int dy) {
	//覆盖棋盘功能主逻辑,a表示棋盘原点坐标（这里取左上方作为原点），d表示噪点坐标，step表示棋盘横纵长
	if (step == 1)
		return;
	else {//分治
		step /= 2; //划分棋盘
		int nextx = ax + step;
		int nexty = ay + step;
		//以噪点所在位置进行分类讨论
		if (dx < nextx && dy < nexty) {//左上
			//对其它三个子棋盘进设置伪噪点，该位置恰好能用一个单位填充
			bd.setvp(nextx-1, nexty,1); //右上
			bd.setvp(nextx, nexty-1,1); //左下
			bd.setvp(nextx, nexty,1);	//右下
			//递归子问题
			cover(bd,ax, ay, step, dx, dy);//递归左上
			cover(bd,ax, nexty, step, nextx-1, nexty);//递归右上
			cover(bd, nextx, ay, step, nextx, nexty-1);//递归左下
			cover(bd, nextx, nexty, step, nextx, nexty);//递归右下
		}
		else if(dx>nextx&&dy<nexty){//右上
			//同理
			bd.setvp(nextx-1, nexty - 1,2); 
			bd.setvp(nextx, nexty-1,2); 
			bd.setvp(nextx, nexty,2);
			cover(bd, ax, ay, step, nextx - 1, nexty - 1);
			cover(bd, ax, nexty, step, dx, dy);
			cover(bd, nextx, ay, step, nextx, nexty-1);
			cover(bd, nextx, nexty, step, nextx, nexty);
		}
		else if (dx < nextx && dy > nexty) {//左下
			bd.setvp(nextx-1, nexty - 1,3);
			bd.setvp(nextx-1 , nexty,3);
			bd.setvp(nextx, nexty,3);
			cover(bd, ax, ay, step, nextx - 1, nexty - 1);
			cover(bd, ax, nexty, step, nextx-1, nexty);
			cover(bd, nextx, ay, step, dx, dy);
			cover(bd, nextx, nexty, step, nextx, nexty);
		}
		else {//右下
			bd.setvp(nextx-1, nexty - 1,4);
			bd.setvp(nextx-1 , nexty,4);
			bd.setvp(nextx, nexty-1,4);
			cover(bd, ax, ay, step, nextx - 1, nexty - 1);
			cover(bd, ax, nexty, step, nextx - 1, nexty);
			cover(bd, nextx, ay, step, nextx,nexty-1);
			cover(bd, nextx, nexty, step, dx,dy);
		}
	}
}