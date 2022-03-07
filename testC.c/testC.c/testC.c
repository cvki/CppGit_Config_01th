#pragma warning(disable:4996)

#include<stdio.h>

#define PI 3.14159

int main() {
	double area,dia;
	scanf("%lf", &dia);//scanf("%lf", &dia);³ö´í
	area =PI * dia * dia;
	printf("area=%.3f", area);
	return 0;
}