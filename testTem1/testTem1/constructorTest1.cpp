#include<iostream>
#include<vector>
#include<fstream>
using namespace std;

class A
{
	friend ostream& operator<<(ostream& out, const A& a);
public:
	A(int x = 0) :x(x) { cout << "Default constructor" << endl; };
	A(const A& a) :x(a.x) { cout << "Copy constructor" << endl; };
	A operator+(const A& a);
	int getX() const{ return x; }
	~A() { cout << "Destructor" << endl; };

private:
	int x;
	char ch = NULL;
};
A A::operator+(const A& a) {
	A tmp(a.x + x);
	return tmp;
}

ostream& operator<<(ostream& out, const A& a) {
	//return out << a.getX();
	return out << a.x;
}



void gdecent2() {
    double theta0 = 0, theta1 = 0;
    //double v = 0.005;
    int count = 0;
    double v = 0.005;
    double cost = INT_MAX;
    vector<double>x; vector<double>y;
    ifstream in("C:\\Users\\buaa203\\Desktop\\testX.txt");
    if (!in)
        cout << "can not open!" << endl;
    double temp0, temp1;
    while (in >> temp0 >> temp1&&temp1!=-1) {
        x.push_back(temp0);
        y.push_back(temp1);
    }
    in >> theta0 >> theta1;
    cout << theta0 << "\t" << theta1<<endl;
    int m = x.size();
    while (true) {
        temp1 = 0; temp0 = 0;
        for (int i = 0; i < m; i++) {
            temp0 += (theta0 + theta1 * x[i]) - y[i];
            temp1 += ((theta0 + theta1 * x[i]) - y[i]) * x[i];
        }
        //double odd_theta0 = theta0;
        //double odd_theta1 = theta1;
        theta0 = theta0 - v * temp0 / m;
        theta1 = theta1 - v * temp1 / m;
        double temp = 0;
        for (int i = 0; i < m; i++) {
            temp += (theta0 + theta1 * x[i]-y[i]) * (theta0 + theta1 * x[i] - y[i]);
        }
        temp = 1.0 / 2 / m * temp;
        //cout << "cost: " << cost << "\t" << "costtem" << temp << endl;
        if (abs(cost - temp) < 1e-8||count>1000000) break;//0.00000000000000000000001
        cost = temp;
        count++;
        //cout << "theta0: " << theta0 << "\t" << "theta1: " << theta1 << endl;
    }
    in.close();
    cout << theta0 << endl;
    cout << theta1 << endl;
    cout << count << endl;
}
