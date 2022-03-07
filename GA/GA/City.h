#pragma once

#include<string>

using namespace std;

const int MAXSIZECITY = 34;
//34省会城市
string s[MAXSIZECITY]{ "北京","天津","上海","重庆","拉萨","乌鲁木齐","银川","呼和浩特","南宁","哈尔滨","长春",
					"沈阳","石家庄","太原","西宁","济南","郑州","南京","合肥","杭州","福州",
					"南昌","长沙","武汉","广州","台北","海口","兰州","西安","成都","贵阳",
					"昆明","香港","澳门" };

class City {
	string name;//城市名
	double x;//经度
	double y;//纬度
public:
	City(string s, double x, double y) :name(s), x(x), y(y) {};
	string getname()const { return name; }
	double caldis(const City& c)const;
};

class CityGph {
	static string nameCity[MAXSIZECITY];//城市表
	int lenCity;//城市数目
	double** dis;//邻接矩阵
public:
	CityGph(int sizeCity, double** dis);
	CityGph(const CityGph& c);
	~CityGph();
	int getSizeCity()const { return lenCity; }
	double getDis (const City& c1, const City& c2)const;
	bool setDis(const City& c1, const City& c2,double v);
};