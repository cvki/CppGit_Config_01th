#include<iostream>
#include<iomanip>

using namespace std;

template <typename T>
struct sortA {//数组排序

	//swap()
	void swapA(T& a, T& b) {
		T tem = a;
		a = b;
		b = tem;
	}

	void show(T* a, int len) {
		for (int i = 0; i < len; i++) {
			cout << setw(4) << left << a[i];
		}
		cout << endl;
	}
	
	//快速排序
	void quickSortA(T* a, int begin, int end) {//begin从0开始，end也为数组下标
		if (begin >= end)
			return;
		int tem = a[begin],i = begin, j = end;
		while(i<j){
			while (i<j&&a[j] > tem)
				j--;
			a[i] = a[j];
			while (i<j&&a[i] < tem)
				++i;
			a[j] = a[i];
		}
		a[i] = tem;
		quickSortA(a, begin, i - 1);
		quickSortA(a, i + 1, end);
		}

	//冒泡排序
	void bubbleSortA(T* a, int len) {
		if (len < 2)
			return;
		for (int i = 0; i < len - 1; i++)
			for (int j = 0; j < len - i - 1; j++) {
				if (a[j] > a[j + 1]) {
					/*auto tem = a[j];
					a[j] = a[j + 1];
					a[j + 1] = tem;*/
					swapA(a[j], a[j + 1]);
				}
			}
	};

	//简单选择排序
	void selectSortA(T* a, int len) {
		if (len < 2)
			return;
		for (int i = 0; i < len-1; i++) {
			T min = a[i];  //或者auto min = a[i];
			for (int j = i + 1; j < len; j++) {
				if (a[i] > a[j]) {
					/*auto tem = a[j];
					a[j] = a[i];
					a[i] = tem;*/
					swapA(a[i], a[j]);
				}
			}
		}
	};

	//直接插入排序
	void insertSortA(T* a, int len) {
		if (len < 2)
			return;
		for (int i = 0; i < len; i++) {
			auto key = a[i];
			//T key = a[i];
			int j = i - 1;
			for (; j >0; j--) {
				if (a[j] > a[i]) {
					a[j+1] = a[j];
				}
			}
			a[j] = key;
		}
	};

	//归并排序
	void mergeSortA(T* a, int len) {

	};
};
