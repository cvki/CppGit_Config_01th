#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
#include <deque>
#include <list>
#include <set>
#include<functional>
using namespace std;


////String
// 将string str的字符串分割后放到vector中
int testStr1(string &str) {
	vector<string> v;
	vector<string>::iterator it;
	int start(0),pos(0) ;
	//cout << str.length()<<endl;
	while (true)
	{
		pos = str.find(".",start);
		if (pos == -1) {
			v.push_back(str.substr(start,str.length() - start));
			break;
		}
		string tmp = str.substr(start, pos - start);
		v.push_back(tmp);
		start = pos+1;
	}
	for (it= v.begin(); it != v.end(); it++)
		cout << *it<<endl;
	return 0;
}
 

void testStr2() {
	string s = "dugba";
	char& a = s[1];
	char& b = s[2];
	char* chv = const_cast<char *>(s.c_str());
	//cout << chv;	成功，强转有效
	char& c = chv[1];
	char& d = chv[2];
	cout << &s << endl;
	cout << &chv << endl;

	s = "uiorhgnmeudhdka";
	for (int i = 0; i < 30; i++) {
		//把长度改长点，出现动态内存分配和引用失效问题
		chv[i] = 't';
	}
	cout << chv << endl;
	

	a = '9';
	b = '8';
	c = '7';
	d = '6';
	cout << s << endl << chv << endl;
	cout << &s << endl;
	cout << &chv << endl;
}

void testStr3(string& s) {
	//将大写字母转换为小写,不区分大小写功能
	int v = 'a' - 'A';
	cout << s << endl;
	for (int i = 0; i < s.length(); i++) {
		/*if (s[i] <= 'Z' && s[i] >= 'A') {
			s[i] += v;
		}*/
		s[i] = tolower(s[i]);	//toupper
	}
	cout << s << endl;
}




/// vector 	
//vector扩容方式查看,暂时看不出规律
void testVector1() {
	vector<int> v1;
	vector<int>::iterator it1;
	for (int i = 0; i < 20; i++) {
		v1.push_back(i);
		cout << "vi=" << i << endl;
		cout << "v_capacity=" <<v1.capacity() << endl;
	}
}

//vector统一输出接口, 第一个会报错
//template<typename T>
//void printVct(const vector<T> &v) {
//	vector<T>::iterator it = v.begin();
//	for (; it != v.end(); it++) {
//		cout << *it << " ";
//	}
//	cout << endl;
//}

void printVct(vector<int>& v) {//参数列表加const会报错
	vector<int>::iterator it = v.begin();
	for (; it != v.end(); it++) {
		cout << *it << " ";
	}
	cout << endl;
}

void testVector2() {
	//vector初始化操作
	vector<int> v1;
	vector<int>::iterator it1;
	v1 = vector<int>(4, 6);//用4个6初始化

	int arr[] = {2, 4, 6, 1, 3, 7};
	////它实际上也是用v.begin,v.end进行构造的
	vector<int> v2(arr, arr + sizeof(arr) / sizeof(int));  //等同于for循环append

	////assign函数：赋值操作
	v1.assign(2, 5);  //将2个5赋值给v1，和上面那个一样

	//v1 = vector<int>(v2.begin(), v2.end()); //将v2赋值给v1
	////同样效果：
	//v2 = v1; //因为它重载了"="
	//v1.assign(v2.begin(), v2.end());

	vector<int>v3(3,7);
	v3.swap(v2);	//该交换和长度无关

	//尾插法，尾删：push_back(),pop_back()
	//删除和批量删除：erase().

	printVct(v1);
	printVct(v2);
	printVct(v3);
}

bool isValidSudoku() {
	//二维向量初始化和遍历
	vector<vector<char>>row(9, vector<char>(9,'0'));

	vector<vector<char>> ::iterator itrow;
	vector<char> vctrow;
	for (itrow = row.begin(); itrow != row.end(); itrow++) {
		vctrow = *itrow;
		for (vector<char>::iterator ittmp = vctrow.begin(); ittmp != vctrow.end(); ittmp++)
			cout << *ittmp<<' ';
		cout << endl;
	}
	return 0;
}


struct ListNode {
	int val;
	ListNode* next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode* next) : val(x), next(next) {}
};

//快慢指针删除倒数第n个节点,也可用栈，或者链表长度(需要遍历两遍)
ListNode* removeNthFromEnd(ListNode* head, int n) {
	if (head) {
		ListNode* quick, * slow, * tmp;
		quick = slow = head;
		while (n-- && quick)
			quick = quick->next;
		if (++n)   //n大于链表长度
			return head;
		if (!quick) { //恰好删除头结点
			tmp = head;
			head = head->next;
		}
		else {
			while (quick->next) {
				quick = quick->next;
				slow = slow->next;
			}
			tmp = slow->next;
			slow->next = tmp->next;
		}
		delete tmp;
	}
	return head;
}

//求链表中是否有环，并判断环的位置
ListNode* detectCycle(ListNode* head) {
	ListNode* quick, * slow, * cross=nullptr;
	quick = slow = head;
	while (quick && quick->next) { //注意判断条件和判断顺序
		quick = quick->next->next;
		slow = slow->next;
		if (quick == slow) {
			cross = quick;
			break;
		}
	}
	if (quick == NULL || quick->next == NULL)
		return NULL;
	slow = head;
	quick = cross;
	while (slow != quick) {
		slow = slow->next;
		quick = quick->next;
	}
	return quick;
}

#if 0
//小题目：有4名选手ABCD，10位评委分别对其打分，
//去掉每个人的最高分和最低分，求每个人的平均分。
//数据结构
struct Cpn {
public:
	string name;
	float score[10];
	Cpn(string n, float sc[10]) :name(n) {
		for (int i = 0; i < 10; i++)
			score[i] = sc[i];
	};
	void operator=(float sc[10]) {
		for (int i = 0; i < 10; i++)
			score[i] = sc[i];
	}
	void printCpn() {
		cout << "name:"<<name << endl;
		for (int i = 0; i < 10; i++)
			cout << score[i] << " ";
		cout << endl;
	}
};

void testApp1() {
	float score1[10] = { 1, 2, 3, 4, 5, 6, 7, 9, 8, 43 };
	float score2[10] = { 2, 3, 4, 5, 6, 7, 9, 8, 10,22 };
	float score3[10] = { 3, 4, 5, 6, 7, 9, 8, 9, 5, 11 };
	float score4[10] = { 2, 3, 4, 5, 6, 7, 9, 1, 3, 6 };
	Cpn p1("zs", score1);
	Cpn p2 = p1;
	p2.name = "lisi";
	float v[10] = { 11,22,33,44,55,66,77,88,99,10 };
	p2 = v;
	p1.printCpn(); //输出表明，p2的改变并未对p1产生影响。因此这里p2是深拷贝于p1的
	p2.printCpn();
}

//按要求求均分,有错误，因为当两端是最值时，会导致中间值插不进去,还是得用sort
float setArr2Deq(float score1[10]) {
	deque<float> deqScore;
	//排序
	deque<float>::iterator itsc=deqScore.begin();
	deqScore.push_back(score1[0]);
	for (int i = 1; i < 10; i++) {
		if (score1[i] <= deqScore.front()) {
			deqScore.push_front(score1[i]);
			continue;
		}
		if (score1[i] >= deqScore.back()) {
			deqScore.push_back(score1[i]);
			continue;
		}
	}
	//删除极值
	deqScore.pop_back();
	deqScore.pop_front();
	for (; itsc != deqScore.end(); itsc++) {
		cout << *itsc << " ";
	}
	cout << endl;
	float sum = 0;
	for (int i = 0; i < 8; i++) {
		sum += deqScore.at(i);
	}
	sum /= 8;
	return sum;
}

void testApp2() { //对上面题目进行解
	float score1[10] = { 1, 2, 3, 4, 5, 6, 7, 9, 8, 43 };
	float score2[10] = { 2, 3, 4, 5, 6, 7, 9, 8, 10,22 };
	float score3[10] = { 3, 4, 5, 6, 7, 9, 8, 9, 5, 11 };
	float score4[10] = { 2, 3, 4, 5, 6, 7, 9, 1, 3, 6 };
	Cpn p1("zs", score1);
	Cpn p2("lisi", score2);
	Cpn p3("wang5", score3);
	Cpn p4("c6", score4);
	
	// 计算均分
	float avg[4];
	avg[0] = setArr2Deq(p1.score);
	avg[1] = setArr2Deq(p2.score);
	avg[2] = setArr2Deq(p3.score);
	avg[3] = setArr2Deq(p4.score);

	for (int i = 0; i < 4; i++) {
		cout << avg[i]<<' ';
	}
	cout << endl;
}
#endif

class Mycompare {  //相当于内建的函数对象 less<int>(),升序则是greater<int>()
public:
	bool operator()(int v1, int v2)const {
		//这里规则定义必须是仿函数，且必须加const，否则报错
		return v1 > v2;
	}
};

int main() {
	//string str1= "dasx.rer.uuipb.k";
	//string str3 = "fa23HVkjiOpB6Umv";
	//testStr1(str);
	//testStr2();
	//testStr3(str3);

	//Vector
	//testVector1();
	//testVector2();
	//isValidSudoku();
	//isValidSudoku();

	//deque
	//testApp1();
	//testApp2();
	

	//随机数，不用srand也能随即成功，但仅仅是v中元素相同，如果v是个二维数组。则它每行都一样
	//因此，对于多次生成随机数时，srand必不可少。比如有v1,v2,v3...无srand就会出问题
	//srand(time(0));
	//int v[10];
	//for(int i =0;i<10;i++)
	//	v[i]= rand()%41+60;//这里不会由于for执行的太快而使得v中元素都一样。
	//for (int i = 0; i < 10; i++)
	//	cout << v[i]<<" ";
	//cout << endl;


	//stack
	//构造(默认，拷贝)，size，empty,top,pop,push...无迭代器


	//queue
	//同理，构造，push，pop，empty，size，还有首尾front,back...无迭代器


	//list
	//初始化: 构造函数
	//list<int> l; //定义，有开辟空间给指针l，但l指向的存储数据空间没有
	//cout << l.size() << endl;
	////初始化列表 initializer_list,它可以用来初始化，比一个个push方便
	//list<int> lst1{ 1,3,4,1,6,2 };
	//for (auto itlst = lst1.begin(); itlst != lst1.end();) {//auto关键字的使用
	//	cout << *itlst++ << " ";
	//}
	// 逆序输出操作
	/*list<int> lst2{ 9,3,1,5,6,2,1 };
	for (auto itlst2 = lst2.rbegin(); itlst2 != lst2.rend();)
		cout << *itlst2++ << " ";*/

	
	//set
	set<int, Mycompare> set1{ 5,2,6,1,9,4 };
	for (auto itset = set1.begin(); itset != set1.end();)
		cout << *itset++ << " ";  //*itset是指的第一个，正好是int值
	cout << endl;
	//另外，对于自定义类型，要指定排序规则。因为set默认会对键排序，如果自定义类型不指定排序规则，它不知道怎么排就会报错
	
	set<int, less<int>> set2{ 3,6,8,1,0 };  //这里加less<int>()会出错，去掉小括号就对了。为什么？
	for (auto numx: set2)
		cout << numx << " ";

	return 0;
}



