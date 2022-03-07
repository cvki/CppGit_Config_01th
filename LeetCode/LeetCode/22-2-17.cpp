#include<iostream>
#include<vector>
#include<algorithm>
#include<map>
#include<list>
//#include<hash_map>  //不能使用，否则报错，使用unordered_map代替
#include <unordered_map>


using namespace std;

//1. 只出现一次的数字
/**给定一个非空整数数组，除了某个元素只出现一次以外，其余每个元素均出现两次。找出那个只出现了一次的元素。
说明：
你的算法应该具有线性时间复杂度。 你可以不使用额外空间来实现吗？
示例 1:
输入: [2,2,1]
输出: 1
示例 2:
输入: [4,1,2,1,2]
输出: 4
来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/single-number  **/

//法1: 排序后查找(垃圾答案)
int singleNumber1(vector<int>& nums) {
	sort(nums.begin(), nums.end());
	if (nums.size() == 1)
		return nums[0];
	int i = 0;
	//for (; i < nums.size() && nums[i] != nums[j]; i += 2, j += 2) {};
	while (i < nums.size() && nums[i] == nums[i+1]) {
		i += 2; 
	}
	return nums[i];
}
//法2：使用异或(优秀答案)
int singleNumber2(vector<int>& nums) {
	int res = 0;	//初值为0才不影响最后结果，因为0异或any=any
	for (auto e : nums)
		res^=e;  //异或运算^=
	return res;
}


int main1() {

	//1. 只出现一次的数字
	vector<int>	v1 = {1,5,3,4,3,2,5,1,2};
	cout<<singleNumber2(v1)<<endl;
	/*for (auto e : v1)
		cout << e << " ";*/
	return 0;
}

/****2. 两数相加
给你两个 非空 的链表，表示两个 非负 的整数。它们每位数字都是按照 逆序 的方式存储的，并且每个节点只能存储 一位 数字。
请你将两个数相加，并以相同形式返回一个表示和的链表。
你可以假设除了数字 0 之外，这两个数都不会以 0 开头。

示例 1：
输入：l1 = [2,4,3], l2 = [5,6,4]
输出：[7,0,8]
解释：342 + 465 = 807

示例 2：
输入：l1 = [0], l2 = [0]
输出：[0]
示例 3：
输入：l1 = [9,9,9,9,9,9,9], l2 = [9,9,9,9]
输出：[8,9,9,9,0,0,0,1]

提示：
每个链表中的节点数在范围 [1, 100] 内
0 <= Node.val <= 9
题目数据保证列表表示的数字不含前导零****/


 // Definition for singly-linked list.
  struct ListNode { //不带头结点
      int val;
      ListNode *next;
      ListNode() : val(0), next(nullptr) {}
      ListNode(int x) : val(x), next(nullptr) {}
      ListNode(int x, ListNode *next) : val(x), next(next) {} //浅拷贝
  };

//思路：表头为低位，输出为倒序输出。因此直接从表头开始相加，短表末位补0，加完的数尾插至结果表，注意进位

  ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
	  //为方便操作，将链表加头结点
	  ListNode* res, * p, * q;
	  res = new ListNode;
	  //res->next = nullptr;
	  p = new ListNode;
	  p->next = l1;
	  l1 = p;
	  p = new ListNode;
	  p->next = l2;
	  l2 = p;

	  p = res;
	  int cr = 0;
	  while (l1 && l2) {
		  int num = l1->val + l2->val + cr;
		  if (num > 9) {
			  num -= 10;
			  cr = 1;
		  }
		  else
			  cr = 0;
		  q = new ListNode;
		  q->val = num;
		  p->next = q;
		  p = q;
		  l1 = l1->next;
		  l2 = l2->next;
	  }
	  while (l1) {
		  int num = l1->val + cr;
		  if (num > 9) {
			  num -= 10;
			  cr = 1;
		  }
		  else
			  cr = 0;
		  q = new ListNode;
		  q->val = num;
		  p->next = q;
		  p = q;
		  l1 = l1->next;
	  }
	  while (l2) {
		  int num = l2->val + cr;
		  if (num > 9) {
			  num -= 10;
			  cr = 1;
		  }
		  else
			  cr = 0;
		  q = new ListNode;
		  q->val = num;
		  p->next = q;
		  p = q;
		  l2 = l2->next;
	  }
	  if (cr) {
		  q = new ListNode;
		  q->val = 1;
		  p->next = q;
		  p = q;
	  }
	  p->next = nullptr;
	  return res->next;
  }


//错误思路
#if 0
/***思路：1. 低位(表尾)补0补齐，使得A,B同长 
		 2. A逆置，B逆置，得A', B'
		 3. 结果C=A’+ B', C使用头插法建立  
			过程中注意进位的处理**/

 //链表输出(不带头结点)
  void showL(ListNode* L) {
	  while (L) {
		  cout << L->val << " ";
		  L = L->next;
	  }
	  cout << endl;


  void headInsert(ListNode*& L) { //头插法就地逆置(带头结点)
	  if (L->next) {
		  ListNode* p, * q;
		  p = L->next;
		  L->next = nullptr;
		  while (p) {
			  q = p;
			  p = p->next;
			  q->next = L->next;
			  L->next = q;
		  }
	  }
  }

  void addNode(ListNode*& L, int n) {//(低位/表尾补0),从原表尾进行尾插
	  ListNode* p, * q;
	  p = L;
	  while (p->next)
		  p = p->next;
	  while (n--) {
		  q = new ListNode;
		  q->val = 0;
		  p->next = q;
		  p = p->next;
	  }
	  p->next = nullptr;
  }

  ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
	  //先给链表添加头结点(原表不含头结点)
	  ListNode* p;
	  p = new ListNode;
	  p->next = l1;
	  l1 = p;
	  p = new ListNode;
	  p->next = l2;
	  l2 = p;

	  p = l1;
	  //记录两个表长
	  int len1(0), len2(0);
	  while (p) {
		  p = p->next;
		  len1++;
	  }
	  p = l2;
	  while (p) {
		  p = p->next;
		  len2++;
	  }
	  int n = abs(len1 - len2);

	  //对短表进行0补齐
	  p = len1 > len2 ? l2 : l1;
	  if (n) {
		  addNode(p, n);
		  headInsert(l1);
		  headInsert(l2);
	  }

	  //两表相加
	  int cr = 0,flag=0;
	  ListNode* res=new ListNode; //res作为带头结点的表指针
	  res->next = nullptr;
	  while (l1) {
		  if (flag++) {
			  int num = l1->val + l2->val + cr;
			  if (num > 9) {
				  num -= 10;
				  cr = 1;
			  }
			  else
				  cr = 0;
			  p = new ListNode;
			  p->val = num;
			  p->next = res->next;
			  res->next = p;
		  }
			  l1 = l1->next;
			  l2 = l2->next;
	  }
	  //加完后仍有进位，添加一个结点
	  if (cr) {
		  p = new ListNode;
		  p->val = 1;
		  p = res->next;
		  res = p;
	  }
	  return res->next;
  }


//测试,（带头结点的尾插建表）
  ListNode* tailCreateL() {
	  ListNode *L, *p, *q;
	  int x;
	  L = new ListNode;
	  p = L;
	  cin >> x;
	  while (x!=-1) {
		  q = new ListNode;
		  q->val = x;
		  p->next = q;
		  p = q;
		  cin >> x;
	  }
	  p->next = nullptr;
	  return L->next; //题目中的链表不包含头结点
  }


int main() {
	ListNode* l1, *l2, *res, *tmp;
	l1 = tailCreateL();
	l2 = tailCreateL();

	/*showL(l1);
	showL(l2);*/
	res = addTwoNumbers(l1, l2);
	showL(res);
	
	cout << endl;
	return 0;
}
#endif

enum string {
	x1,
	x2,
	x3 = 10,
	x4,
	x5,
} x;
void main01() {
	
	cout << x << endl;

	unsigned char* p1;
	unsigned long* p2;
	p1 = (unsigned char*)0x801000;
	p2 = (unsigned long*)0x810000;
	cout << p1 + 5 <<endl;
	cout << p2 + 5 << endl;


}
//class A
//{
//public:
//	void FuncA()
//	{
//		printf("FuncA called\n");
//	}
//	virtual void FuncB()
//	{
//		printf("FuncB called\n");
//	}
//};
//class B : public A
//{
//public:
//	void FuncA()
//	{
//		A::FuncA();
//		printf("FuncAB called\n");
//	}
//	virtual void FuncB()
//	{
//		printf("FuncBB called\n");
//	}
//};
//void main(void)
//{
//	B	b;
//	A* pa;
//	pa = &b;
//	A* pa2 = new A;
//	pa->FuncA();
//		pa->FuncB(); 
//		pa2->FuncA(); 
//		pa2->FuncB();
//	delete pa2;
//}


//int FindSubString(char* pch) {
//	int   count = 0;
//	char* p1 = pch;
//	while (*p1 != '\0') {
//		if (*p1 == p1[1] - 1) {
//			p1++;
//			count++;
//		}
//		else {
//			break;
//		}
//	}
//	int count2 = count;
//	while (*p1 != '\0') {
//		if (*p1 == p1[1] + 1) {
//			p1++;
//			count2--;
//		}
//		else {
//			break;
//		}
//	}
//	if (count2 == 0)
//		return(count);
//	return(0);
//}
//void ModifyString(char* pText) {
//	char* p1 = pText;
//	char* p2 = p1;
//	while (*p1 != '\0') {
//		int count = FindSubString(p1);
//		if (count > 0) {
//			*p2++ = *p1;
//			printf_s(p2, "%i", count);
//			while (*p2 != '\0') {
//				p2++;
//			}
//			p1 += count + count + 1;
//		}
//		else {
//			*p2++ = *p1++;
//		}
//	}
//}
//void main(void) {
//	char text[32] = "XYBCDCBABABA";
//	ModifyString(text);
//	printf(text);
//}


void prim(int m, int n)
{
	if (m >= n)
	{
		while (m%n) n++;
		(m/=n);
		prim(m, n);
		cout << n << endl;
	}
}

void main02() {
	prim(96, 3);
}


//DP-最大子数组和-th3

// 1. 暴力
int maxSubArr(vector<int> v) {
	if (v.empty())
		return INT_MIN;
	int len = v.size();
	int maxnum = *v.begin(),tmp=0,left=0,right=0;
	for (int i = 0; i < len; i++) {
		for (int j = i; j < len; j++) {
			tmp += v[j];
			if (maxnum < tmp) {
				maxnum = tmp;
				left = i;
				right = j;
			}
		}
		tmp = 0;
	}
	cout << "[" << left << ", " << right << "]" << endl;
	return maxnum;
}


//DP
int maxSubArr2(vector<int> v) {
	if (v.empty())
		return INT_MIN;
	int len = v.size();
	int maxnum = *v.begin(),left=0,right=0;
	int* sumx = new int[len]; //记录当下最大和
	sumx[0] = *v.begin();
	for (int i = 1; i < len; i++) { //填DP数组
		sumx[i] = max(sumx[i - 1] + v[i],v[i]);
	}
	//回溯DP表，找到最大和与下标
	right = len - 1;
	maxnum = sumx[right];
	for (int i = len - 1; i >= 0; i--) 
		if (maxnum < sumx[i]) { //最大值和右下标
			maxnum = sumx[i];
			right = i;
		}
	//寻找左下标的循环不能和上面的循环合并，否则会出错，如[-1，-2]	
	for (int i = right; i >= 0; i--)
		if (sumx[i] == v[i]) { //左下标
			left = i;
			break;
		}
	cout << "[" << left << ", " << right << "]" << endl;

	delete[] sumx;
	return maxnum;
}

//在线处理
int maxSubArr3(vector<int> v) {
	//该方法缺点：1.下标不容易记录，2.全负数时特殊处理
	if (v.empty())
		return INT_MIN;
	int len = v.size();

	//首先判断是不是全负数，如果为全负数则返回最大值
	bool flag = false; //默认是全负数
	for (int e : v) {
		if (e > 0) {//只要出现正数，则可以在线处理
			flag = true;
			break;
		}
	}

	int maxnum = *v.begin(), tmp = 0;
	if (flag) {
		for (int i = 0; i < len; i++) {
			tmp += v[i]; //累加
			maxnum = tmp > maxnum ? tmp : maxnum; //每轮都需比较一次
			if (tmp < 0) //加到<0时，舍弃 (此处如果数组全负数，则出问题)
				tmp = 0;
		}
	}

	else {	//全负数时，选取最大值
		for (int i = 0; i < len; i++) {
			if (maxnum < v[i]) 
				maxnum = v[i];
		}
	}
	return maxnum;
}

int main03() {
	vector<int> v;
	int num;
	while (cin >> num)
		v.push_back(num);
	cout<<maxSubArr(v)<<endl;
	cout << maxSubArr2(v) << endl;
	cout << maxSubArr3(v) << endl;
	return 0;
}


/***1. 两数之和
给定一个整数数组 nums 和一个整数目标值 target，请你在该数组中找出 和为目标值 target  的那 两个 整数，并返回它们的数组下标。
你可以假设每种输入只会对应一个答案。但是，数组中同一个元素在答案里不能重复出现。
你可以按任意顺序返回答案。

示例 1：
输入：nums = [2,7,11,15], target = 9
输出：[0,1]
解释：因为 nums[0] + nums[1] == 9 ，返回 [0, 1] 。

示例 2：
输入：nums = [3,2,4], target = 6
输出：[1,2]

示例 3：
输入：nums = [3,3], target = 6
输出：[0,1]
 
提示：
2 <= nums.length <= 104
-109 <= nums[i] <= 109
-109 <= target <= 109
只会存在一个有效答案
进阶：你可以想出一个时间复杂度小于 O(n2) 的算法吗？**/


//1. 暴力法，O(n^2),略

//2.先将vector转换成multimap，key=值，val=下标，然后排序，然后双指针查找，复杂度O(nlogn)+O(n)
vector<int> twoSum1(vector<int>& nums, int target) {
	if(nums.empty())
		return vector<int>{-1};
	list<multimap<int, int>> plist;
	int len = nums.size();

	for (int i = 0; i < len; i++) {//转换为multimap
		multimap<int,int> pmap;
		pmap.emplace(nums[i], i); 
		//这里使用insert函数会报错，网上说inert会调用拷贝构造，而emplace和emplace_hint直接调用构造函数并插入，它们效率更高，其中emplace_hint还需指定插入位置
		plist.push_back(pmap);
	}

	//排序 O(nlogn)
	plist.sort(); //因为这里的key实际上是int类型，因此无需重写compare比较规则

	//测试排序后的输出
	for (const auto& e : plist) //const+&, 安全高效，遍历得到multimap对象
		for (const auto& v : e) //e为multimap对象，遍历e得到的v是其中内容
			cout << "[ "<<v.first << ",  " << v.second <<" ]" << endl;

	//查找 O(n)
	list<multimap<int, int>>::iterator itbegin = plist.begin();
	list<multimap<int, int>>::iterator itend = plist.end();
	--itend; //end指向最后一个元素的下一个位置
	while (itbegin!=itend) {
		if (itbegin->begin()->first + itend->begin()->first == target) //找到了
			return vector<int>{itbegin->begin()->second, itend->begin()->second}; 
		if (itbegin->begin()->first + itend->begin()->first < target) //比target小时，左指针右移
			++itbegin;
		if (itbegin->begin()->first + itend->begin()->first > target) //比target大时，右指针左移
			--itend;
	}
	return vector<int>{-1};
}


/****    3. 哈希表解法。每次遇到一个数a,首先在hash表中查询target-a，如果存在，返回a和target-a的坐标
如果hash表中不存在target-a，就将target-a和它的下标放入表中。一次循环就能找到，由于hash表，时间复杂O(n)，空间O(n)**/
vector<int> twoSum2(vector<int>& nums, int target) {
	if (nums.empty())
		return vector<int>{-1};

	//hash_map<int, int> htmp; //有的编译器和系统不支持hash_map，即将被unordered_map替代，跨平台时不要用
	unordered_multimap<int, int> numhashmap;  //c++11新标准加入，底层为哈希结构的map，建议使用它
	//注意这里key为数组值，val为数组下标，因此需要用multimap，不是map

	int len = nums.size();
	vector<int> res;
	unordered_multimap<int, int>::iterator itmap = numhashmap.begin();
	for (int i{}; i < len; i++) {
		int tmp;
		if (numhashmap.empty()) { //向哈希表中放入第一个值
			tmp = target - nums[i];
			numhashmap.emplace(tmp, i);
		}
		else { //表不为空(不是第一次查找)时，开始查找
			int j;
			if (numhashmap.find(nums[i]) != numhashmap.end()) { //找到了
				j = numhashmap.find(nums[i])->second; //记录下标(确保解是两个，不能自己和自己)
				if (i != j) { //找到了且不是自身
					res.push_back(i);
					res.push_back(j);
					break;
				}
			}
			else { //没找到
				tmp = target - nums[i]; //压入target-nums[i]
				numhashmap.emplace(tmp, i);
			}
		}
	}
	return res;
}


int main04() {

	//{ 3,2,0,-5,7,1,3,8,7,3,6 }

	vector<int> v = {7,3,4,1,3,-7,6};
	vector<int> res;
	int target = 6;
	//res=twoSum1(v, target);
	res = twoSum2(v, target);
	for (int& e : res)
		cout << e << " ";
	cout << endl;

#if 0
	//unordered_map test
	unordered_multimap<int, int> mt1{ {-2,0},{1,2},{6,3},{-1,4}, {6,5} };
	for (auto& e : mt1) {
		cout << mt1.find(6)->first << ", " << mt1.find(6)->second << endl; 
		//这里find只找到第一个满足key的元素，比如这里依6，只找到3或5就结束了，另一个找不到
		cout << "***************************************************" << endl;
		cout << e.first << ", " << e.second <<endl;
	}
#endif	

	return 0;
}




