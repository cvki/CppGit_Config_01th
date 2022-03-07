//21-12-07  buaa算法作业4—马踏棋盘问题

//不写文档了，简单写一下该问题和该问题的贪心策略
/**该问题类似迷宫问题，主要以递归和回溯法为主，这里改递归变成63次循环迭代。若单使用回溯法，效率非常低，大概为8^(N*N)复杂度，考虑使用贪心算法优化。
* 贪心策略在迭代回溯的基础上，对下次选择路径进行优化，而不是一般方法的按照坐标变化量的排列进行搜索。
* 贪心策略对下次搜索路径的下次可选择路径数目进行统计，也就是下下次出路数目，取它作为贪心权重，优先走权重小的选择路径。
* 因为该路径的权重小，意味着如果错过该路径，那下次再过来的概率就很小，也就是说很可能该位置在以后的遍历中都遍历不到或者需要回溯很长才能再过来，这就导致时间复杂度大大提升。
* 当然如果下次可选路径只有一条，则直接走，如果下次可选路径的权重有相等，则仍按初始化的坐标变化量排列顺序来走，这个影响不大。
***/
#include<iostream>
#include<iomanip>
using namespace std;

typedef struct coordinate { //方便记录坐标
    int x;
    int y;
}codnt;

int chessboard[8][8] = { 0 }; //棋盘，存储路径序号，最终输出

bool travel(codnt *start) {
    codnt move[8] = { {-2,-1},{-2,1},{2,-1},{2,1},{-1,-2},{-1,2},{1,-2},{1,2} }; //每个位置的下次坐标变化量
    codnt next[8] = { 0 };  //记录下次可走的路径
    int ways[8] = { 0 };   //记录下次可走路径的出路数
    codnt *tmp=new codnt;
    int count, counttmp, min, tmp1;     //count记录当前位置可走的出路数，min记录下下次路径中最少的路数下标，用于贪心选择
    chessboard[start->x][start->y] = 1;     //第一步为起始位置 
    for (int n = 2; n <= 64; n++) {     //循环2~64个位置 
        for (int m = 0; m < 8; m++) {
            ways[m] = 0;    //清空各位置的出路数 
        }
        counttmp = 0;
        for (int j = 0; j < 8; j++) {   //试探8个方向 
            tmp->x = start->x + move[j].x;
            tmp->y = start->y + move[j].y;
            if (tmp->x < 0 || tmp->y < 0 || tmp->x>7 || tmp->y>7)  continue; //该处无出口时
            if (chessboard[tmp->x][tmp->y] == 0) {
                next[counttmp] = *tmp;  //将可走的位置保存在next中 
                counttmp++;     //该位置出口数量 
            }
        }
        count = counttmp;
        if (count == 0) return false;  //无出路位置
        else if (count == 1) min = 0;   //下次只有一条路径可选
        else {   //下次有多条出路可选时
            for (int m = 0; m < count; m++) {
                for (int j = 0; j < 8; j++) {
                    tmp->x = next[m].x + move[j].x;
                    tmp->y = next[m].y + move[j].y;
                    if (tmp->x < 0 || tmp->y < 0 || tmp->x>7 || tmp->y>7)  continue;
                    if (chessboard[tmp->x][tmp->y] == 0)  ways[m]++;    //可走位置的出路数量 
                }
            }
            //以下下次出路数作为权重，进行贪心选择，选择最小权所对路径作为下次路径
            tmp1 = ways[0];
            min = 0;
            for (int m = 1; m < count; m++) {   //找出可走位置中出路数量最少的路径下标给min
                if (ways[m] < tmp1) {
                    tmp1 = ways[m];
                    min = m;
                }
            }
        }
        *start = next[min]; //马跳到出路数量最少的位置 
        chessboard[start->x][start->y] = n; //设置棋盘路径
    }
    delete tmp;
    return true;
}

int main() {
    codnt *start=new codnt;
    cout << "输入马的起始坐标位置(从1开始)：";
    cin >> start->x >> start->y;
    if (start->x < 1 || start->y < 1 || start->x>8 || start->y>8) {
        cout << "坐标输入错误，请重新输入！" << endl;
        exit(0);
    }
    start->x -= 1;
    start->y -= 1;
    if (travel(start)) {
        cout << "马按以下顺序走：" << endl;
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                cout << setw(3) << chessboard[i][j];
            }
            cout << endl;
        }
    }
    else {
        cout << "遍历失败" << endl;
    }
    delete start;
    system("pause");
    return 0;
}

