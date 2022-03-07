#include"City.h"
#include<iostream>
#include<string>
#include<cmath>

using namespace std;

double City::caldis(const City& c) const{
	return sqrt(pow(this->x - c.x, 2) + pow(this->y - c.y, 2));
};

CityGph::CityGph(int sizeCity,double** dis) {
	lenCity = sizeCity;
	for (int i = 0; i < lenCity; i++) {
		this->dis= new double* [lenCity];
		for (int j = 0; j < lenCity; j++) {
			this->dis[i] = new double[lenCity];
			this->dis[i][j] = dis[i][j];
		}
	}
}

CityGph::CityGph(const CityGph& c) {
	lenCity = c.lenCity;
	for (int i = 0; i < lenCity; i++) {
		dis = new double* [lenCity];
		for (int j = 0; j < lenCity; j++) {
			dis[i] = new double[lenCity];
			dis[i][j] = c.dis[i][j];
		}
	}
};
CityGph::~CityGph() {
	for (int i = 0; i < lenCity; i++) {
		delete[] dis[i];
	}
	delete[] dis;
};
double CityGph::getDis(const City& c1, const City& c2)const {
	return c1.caldis(c2);
};
bool CityGph::setDis(const City& c1, const City& c2, double v) {
	for (int i = 0; i < lenCity; i++) {
		if (nameCity[i] == c1.getname()) {
			for (int j = 0; j < lenCity; j++)
				if (nameCity[j] == c2.getname()) {
					dis[i][j] = v;
					return true;
				}
		}
	}	
	return false;
};