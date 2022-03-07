// 2021-12-7.buaa算法作业3——最大和子数组问题

/**题目描述：给定一个整数数组nums，找到一个具有最大和的连续子数组，返回其最大和并输出该子序列下标***/
#include<iostream>
#include <vector>

using namespace std;

const int MAXS = 500;
int sum[MAXS][MAXS];

//3 5 -1 2 -7 -9 6 4		3 7 -2 -7 5 -1   1 -2 -4 2 -5
//-4 1 2 -5 3 4 -2 -1 4		2 -1 -1 -1 -1 3		-2 1 0

int getmSum1(int num[],const int len) {//len从1开始
	int begin = 0, end = 0;//记录最大子数组起止下标	
	if (len > 1) {
		for(int i=0;i<len;i++)//序列起点i
			for (int j = i+1; j < len; j++) {//序列终点j
				if (sum[i][j - 1] + num[j] < num[j]) {
					//从这里看出，其实只需要判断当前sum是否变负数即可
					sum[i][j] = num[j];
				}
				else
					sum[i][j] = sum[i][j - 1] + num[j];
			}
		//从建立好的表中找出最大值与最大序列和的下标
		int s=sum[0][0];
		for (int i = 0; i < len; i++)
			for (int j = i; j < len; j++) {
				if (s <= sum[i][j]) {//记录当前最大目标内容
					begin = i;
					end = j;
					s = sum[i][j];
				}
			}
	}
	//for (int i = 0; i < len; i++) {
	//	cout << endl;
	//	for (int j = i; j < len; j++) {
	//		cout << sum[i][j]<<"  ";
	//	}
	//}	
	cout << endl << "getmSum1最大子数组下标为：" << begin << "-->" << end << endl; 
	return sum[begin][end];
}

//优化
int getmSum2(int num[], const int len) {
	int sum=num[0];//记录当前局部最大和
	int	max = sum;//记录全局最大和
	bool has_pos = false;//表示num序列是否全部非正,初始默认全为负数或0
	for (int i = 1; i < len; i++) {
		if (sum > 0) {
			has_pos = true; //有正数，标识记为true
			sum += num[i];
		}
		else  //重新记录最大序列
			sum = num[i];
		if (max < sum) //修改最大值和序列
			max = sum;
	}
	if (!has_pos) {//没有正数
		for (int i = 0; i < len; i++) {//变为求最大值问题
			if (max < num[i]) 
				max = num[i];
		}
	}
	return max;
}


int main1() {
	int nums[MAXS];
	int len; //记录数组元素个数
	while (1) {
		cout << "输入序列长度(输入-1退出)：" << endl;
		cin >> len;
		if (len > 0) {
			cout << "输入整数序列：" << endl;

			//输入数据，同时初始化sum表(对角线为初始值，只用表的下三角部分)
			for (int i = 0; i < len; i++) {
				cin >> nums[i];
				sum[i][i] = nums[i];
			}
			//寻找最大子数组序列与和	
			int s1 = getmSum1(nums, len);
			int s2 = getmSum2(nums, len);
			cout << "getmSum1最大子数组和：" << s1 << endl;
			cout << "getmSum2最大子数组和：" << s2 << endl;
			//if (s1 == s2)
			//	cout << "TRUE" << endl;
			//else
			//	cout << "FALSE" << endl;
		}
		else
			break;
		cout <<"********************************************************************"<< endl;
	}
	return 0;
}


//2th

//testcase:
// //3,5,-1,2,-7,-9,6,4    	3,7,-2,-7,5,-1   1,-2,-4,2,-5
// //-4, 1, 2, -5, 3, 4, -2, -1, 4		 2, -1, -1, -1, -1, 3	 	-2, 1, 0
//method 1--3loop, 暴力法
int getSumij(int a[], int i, int j) {  //计算每个子列的和
	int sum = 0;
	while (i <= j) {
		sum += a[i++];
	}
	return sum;
}
int getmaxsum1(int a[], int len,int& left, int& right) {
	if (len < 1)
		return 0;
	int sum = a[0];
	for (int i = 0; i < len; i++) //i表示子列起点
		for (int j = i; j < len; j++) {  //j表示子列终点
			int tem = getSumij(a, i, j);  //计算该子列和
			if (tem > sum) {  //目前最大，则记录该和与子列下标
				sum = tem;
				left = i;
				right = j;
			}
		}
	return sum;
}

//method 2--DP，动态规划
int getmaxsum2(vector<int>& nums, int& left, int& right) {
	int len = nums.size();
	if (len < 1)
		return 0;
	vector<int> di(nums);	//di用于存储直到当前位置处的最大和，理顺设计思路

	/*vector<int> di;
	di.reserve(nums.size());*/	//或使用该方法预留di空间(此时未做任何赋值)，然后使用

	/*nums[3] = 465;	
	cout << di[3] <<" "<<nums[3] << endl;*/  //验证vector拷贝构造的深拷贝

	di.at(0) = nums.at(0);	//at函数和"[]"的区别
	for (int i = 1; i < len; i++) {
		di.at(i) = max(nums.at(i), nums.at(i) + di.at(i - 1)); //DP递归公式和思路 
		//从该句可以看出，只需要判断当前加和的正负，然后进行选择即可。
	}

	//找到结果最大和
	int maxsum = di[0];
	for(int i=0;i<len;i++)
		if (di.at(i) > maxsum) {
			maxsum = di.at(i);
			right = i;   //右端坐标
		}
	//回溯寻找左端坐标，左端第一个di[i]=nums[i]即为左端坐标
	for (int i = right; i >= 0; --i) {
		if (nums.at(i) == di.at(i)) {
			left = i;
			break;
		}
	}
	return maxsum;
}

//DP代码优化(只得到最大和结果)
int getmaxsum3(vector<int>& nums, int& left, int& right) {
	int sumk = 0, anssum = nums.at(0);
	//sumk记录当前位置的最大值，anssum记录全局最大值
	for (auto e : nums) {
		sumk = max(e, e + sumk);
		anssum = max(anssum, sumk);
	}
	return anssum;
}


int main() {

#if 0
	//2th,暴力法解数组最大和序列
	int a[] = { -2,1,0 };
	int left = 0, right = 0; //表示下标
	int len = sizeof(a) / sizeof(int);
	int sum= getmaxsum1(a, len, left, right);
	cout << "sum="<<sum<<"\t" << "[" << left << ", " << right << "]" << endl;

	vector<int> v { -4, 1, 2, -5, 3, 4, -2, -1, 4 };
	int left = 0, right = 0; //表示下标
	int sum=getmaxsum2(v, left, right);
	cout << "sum=" << sum << "\t" << "[" << left << ", " << right << "]" << endl;
	sum = getmaxsum3(v, left, right);
	cout << "sum=" << sum << "\t" << "[" << left << ", " << right << "]" << endl;
#endif





	return 0;
}
