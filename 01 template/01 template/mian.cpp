#include"swapTest.hpp"
#include<iomanip>
#include "sortA.cpp"



//


int main() {

#if(0)
	int a, b;
	char c1, c2;
	string s1, s2;
	cout << "input int num:" << endl;
	cin >> a >> b;
	cout << "input char num:" << endl;
	cin >> c1>>c2;
	//为什么c1和c2之间不加getchar(),c2也能正常读入？因为cin和scanf不同，cin忽略空格并将其作为结束标志，这里输入c1后就算遇到空格，cin也不会把它放到c2里，但为什么没有导致跳过输入>>c2导致出错呢？
	//因为cin遇到空格后会终止当前的输入，也就是c1之后的输入，并不会影响接下来对c2的输入，cin遇到空白符是把它丢弃了，而不是终止输入或者对输入流的其他内容产生影响。

	getchar();//这个位置必须加上getchar()，否则getline(s1)会遇到回车导致s1=NULL
	cout << "input string num:" << endl;
	getline(cin, s1);
	getline(cin, s2);
	swapT(a, b);
	swapT(c1, c2);
	swapT(s1, s2);

	cout << "after swap():" << endl;
	cout << a << "\t" << b << endl << c1 << "\t" << c2 << endl << s1 << "\t" << s2 << endl;
	//cout << s1 << "\t" << s2 << endl;
#endif

	int a[8] = { 7,3,0,9,2,6,5,4 };
	int b[8] = { 7,3,0,9,2,6,5,4 };
	int c[8] = { 7,3,0,9,2,6,5,4 };
	int d[8] = { 7,3,0,9,2,6,5,4 };
	int e[8] = { 7,3,0,9,2,6,5,4 };
	//int a[3] = { 7,6,1};
	sortA<int> s1;

	int len = sizeof(a) / sizeof(*(a));
	cout << "len: " << len << endl;

	s1.bubbleSortA(a, len);
	cout << "bubbleSort(): " << endl;
	s1.show(a, len);

	s1.selectSortA(b, len);
	cout << "selectSortA(): " << endl;
	s1.show(b, len);

	//quickSorttt(c, 0, len - 1);
	
	s1.quickSortA(c, 0, len - 1);
	cout << "quicksortA(): " << endl;
	s1.show(c, len);

	s1.insertSortA(d, len);
	cout << "insertSortA(): " << endl;
	s1.show(d, len);

	s1.mergeSortA(e, len);
	cout << "mergeSortA(): " << endl;
	s1.show(e, len);

	return 0;
}