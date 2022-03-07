/**该算法是针对给定了起点，得到其
它所有点到该起点的最短路径**/
#include<iostream>

using namespace std;

template<typename T1, typename T2>
void showDk(T1** graph, T1*& dist, T2*& pre, int* sign, int vnum) {
	for (int i = 0; i < vnum; i++)
		cout << "dist: " << dist[i] << " ";
	cout << endl;
	for (int i = 0; i < vnum; i++)
		cout << "pre: " << pre[i] << " ";
	cout << endl;
	for (int i = 0; i < vnum; i++)
		cout << "sign: " << sign[i] << " ";
	cout << endl << "********************************************************************" << endl;
}

template<typename T1, typename T2>
void dijsktra(T1** graph, T1*& dist, T2*& pre, T2 begin, int* sign, int vnum) {
	for (int i = 0; i < vnum; i++) {
		for (int j = 0; j < vnum && !sign[i]; j++) {
			if (dist[j] > dist[i] + graph[i][j]) {
				dist[j] = dist[i] + graph[i][j];
				pre[j] = i;
			}
			//show(graph, dist, pre, sign, vnum);
		}
		sign[i] = 1;
	}
}

//floyd算法，用于多源起点到其它点的最短路径。时间复杂度:O(n^3)；空间复杂度:O(n^2)。
//适用于稠密图，在稠密图中的效率要高于V次的Dijkstra算法，其中V为节点数目
template<typename T1>

void floyd(T1** graph, int vnum) {
	//开辟两个二维数组，分别存储当前最短路径和最短路径经过的节点
	T1 **gph=new T1*[vnum];//存储节点间的距离
	int **pre = new int* [vnum];//存储前驱节点

	//初始化
	for (int i = 0; i < vnum; i++) {
		gph[i] = new T1[vnum];
		pre[i] = new int[vnum];
		for (int j = 0; j < vnum; j++) {
			gph[i][j] = graph[i][j];
			pre[i][j] = -1;
			
		}
	}
	for (int k = 0; k < vnum; k++) {
		for (int i = 0; i < vnum; i++)
			for (int j = 0; j < vnum; j++)
			{//动态规划，以k作为中间节点，试探是否能通过k截出i到j的最短路径
				if (gph[i][j] > gph[i][k] + gph[k][j]) {
					gph[i][j] = gph[i][k] + gph[k][j];//更新最短路径
					pre[i][j] = k;//更新前驱节点
				}
			}
	}	

	//输出
	for (int i = 0; i < vnum; i++) {
		for (int j = 0; j < vnum; j++) {
			cout << gph[i][j]<<" ";
		}
		cout <<endl;
	}
	for (int i = 0; i < vnum; i++) {
		for (int j = 0; j < vnum; j++) {
			if (pre[i][j] != -1)
				cout << pre[i][j] << " ";
			else
				cout << "X" << " ";
		}
		cout << endl;
	}
}

int test_1() {//main函数
	int vnum;//节点数
	cout << "输入结点数目：" << endl;
	cin >> vnum;
	float** graph = new float* [vnum];;//邻接矩阵
	cout << "输入邻接矩阵(无路径请输入999)：" << endl;
	for (int i = 0; i < vnum; i++) {
		graph[i] = new float[vnum];
		for (int j = 0; j < vnum; j++) {
			cin >> graph[i][j];
		}
	}

	float* dist = new float[vnum];//存储每个节点的最短路径值
	int* pre = new int[vnum];//存储每个节点的上一个节点
	int* sign = new int[vnum]();//记录当前节点是否已被访问加入
	int begin;// 起始节点

	cout << "输入起点序号(从0开始)：" << endl;
	cin >> begin;

	//初始化 
	pre[begin] = -1;
	for (int i = 0; i < vnum; i++) {
		if (i != begin)
			pre[i] = begin;
		sign[i] = 0;
		dist[i] = graph[begin][i];
	}
	//dist[begin] = 0;//起点到起点的距离为0
	//sign[begin] = 1;//表示起点已经被访问加入

	dijsktra(graph, dist, pre, begin, sign, vnum);

	//输出
	showDk(graph, dist, pre, sign, vnum);

	floyd(graph, vnum);

	return 0;
}

