/**2021-11-23，buaa算法作业-2：旅游线路规划问题(图算法单源最优路径--Dijkstra)**/

#include<iostream>

using namespace std;

const int INF = 1e7;//表示不连通节点的权值
const int MAXSIZE = 500;//节点最大数目

int route[MAXSIZE][MAXSIZE]; //存储路径权值邻接矩阵
int cost[MAXSIZE][MAXSIZE]; //存储消费权值邻接矩阵
int dis[MAXSIZE]; //存储到所有点的最小路径值
int costV[MAXSIZE]; //存储到所有点的最小费用值

bool sign[MAXSIZE] = { false };//标志位，记录该节点是否被加入已访问的节点集合中
int minV=INF;

void Dijkstra(int v0, int v, int d) {
	dis[v0] = 0;
	sign[v0] = true;
	for (int i = 0; i < v; i++) {
		minV = INF;
		for (int k = 0; k < v; k++) {
			//找出到当前点最小路径值
			if (!sign[k]) {
				if (dis[k] < minV) {
					minV = dis[k];
					v0 = k;
				}
			}
		}
		sign[v0] = true;
		for (int k = 0; k < v; k++) {
			//找出到当前点最小路径的最小费用值
			if (!sign[k] && minV + route[v0][k] < dis[k]) {
				dis[k] = minV + route[v0][k];
				costV[k] = costV[v0] + cost[v0][k];
			}
			else if (!sign[k] && minV + route[v0][k] == dis[k] && costV[k] > costV[v0] + cost[v0][k]) {
				costV[k] = costV[v0] + cost[v0][k];
			}
		}
	}
}
int main() {
	int v, e, s, d;
	cin>>v>>e>>s>>d;

	//初始化无向图
	for (int i = 0; i < v; i++)
		for (int j = 0; j < v; j++) {
			route[i][j] = route[j][i] = INF;
			cost[i][j] = cost[j][i] = INF;
		}

	//加载路径权值和费用权值
	for (int i = 0; i < e; i++) {
		int a, b, c, d;
		cin >> a >> b >> c >> d;
		route[a][b] = route[b][a] = c;
		cost[a][b] = cost[b][a] = d;

	}

	for (int i = 0; i < v; i++) {
		//route[i][s]为点i到起始点的距离
		dis[i] = route[i][s];
		costV[i] = cost[i][s];
	}
	Dijkstra(s, v, d);
	cout << dis[d] << " " << costV[d] << endl;
	system("pause");
	return 0;
}