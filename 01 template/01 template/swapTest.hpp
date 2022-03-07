#pragma once
#include<iostream>
#include<string>

using namespace std;

template <typename T>
void swapT(T& a, T& b) {
	T tem = a;
	a = b;
	b = tem;
}

