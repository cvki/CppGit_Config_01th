#include<iostream>

using namespace std;

const int MAXSIZE = 500;
int route[MAXSIZE][MAXSIZE];//路径权值邻接矩阵
int cost[MAXSIZE][MAXSIZE];//费用权值邻接矩阵
int res[MAXSIZE][MAXSIZE];//最短路径结果邻接矩阵

int getMinRoute(int citysize,int begin,int end) {
	//返回最短路径数目

};

int getMinCost() {
	//返回最短路径中费用最少的解，即最优解

};

int main() {
	int begin, end;
	int citysize, routesize;
	//初始化输入
	cin >> citysize >> routesize >> begin >> end;
	for (int i = 0; i < routesize; i++) {
		int b1, e1, r1, c1;
		cin >> b1 >> e1 >> r1 >> c1;
		route[b1][e1] = r1;
		cost[r1][e1] = c1;
	}
	//得到最短路径
	int count=getMinRoute(citysize,begin,end);
	//得到最优解
	int cost=getMinCost();
	cout << endl;

	return 0;
}