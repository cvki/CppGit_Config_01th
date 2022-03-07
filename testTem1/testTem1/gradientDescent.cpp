//单特征时的批量梯度下降算法
#include<iostream>
#include<fstream>

using namespace std;

const int DATASIZE = 10;//数据规模
double datax[DATASIZE];//存储变量训练数据
double result[DATASIZE];//存储结果训练数据
const double ALPHA = 0.005;//学习率

//线性模型，h(x)=x1*theta1+x0*theta0（其中x0=1）
//double lineFun(const double theta0,const double theta1,const double data) {
//	return theta1 * data + theta0;
//}

//求梯度,更新theta
void getGradient( double* theta0,double* theta1, const double *data,const double *result) {
	double gradient0=0,gradient1 = 0,tmp=0,res=0;
	for (int i = 0; i < DATASIZE; i++) {
		tmp += (*theta1 * data[i] + *theta0 - result[i]);
		//res += tmp * data[i];//为什么用这一句会出错？
		res += (*theta1 * data[i] + *theta0 - result[i]) * data[i];
	}
	gradient0 = tmp / DATASIZE;
	gradient1= res / DATASIZE;
	*theta0 -= (gradient0 * ALPHA);
	*theta1 -= (gradient1 * ALPHA);
	//cout << "gradient:theta: " << *theta0 <<"\t"<<*theta1 << endl;
}

//求损失函数值
double loseFun(double theta0,double theta1, const double data[], const double result[]) {
	double tmp = 0, res = 0;
	for (int i = 0; i < DATASIZE; i++) {
		//tmp = pow(lineFun(theta0, theta1, data[i]) - result[i],2);
		tmp = pow(theta1 * data[i] + theta0 , 2);
		res += tmp;
	}
	return res / 2 / DATASIZE;
}


void gradientDescent() {
	double val_los = 0, tmp_val = 0, count = 0;
	double theta0, theta1;
	/*cout << "Enter training data and result(data result):" << endl;
	for (int i = 0; i < DATASIZE; i++) {
		cin >> datax[i] >> result[i];
	}
	cout << "Enter theta0 and theta1:" << endl;
	cin >> theta0 >> theta1;*/
	double tmp0, tmp1;
	int ind1 = 0,ind0=0;
	ifstream in("C:\\Users\\buaa203\\Desktop\\testX.txt");
	while (in>>tmp0>>tmp1&&tmp1!=-1)
	{
		datax[ind0++] = tmp0;
		result[ind1++] = tmp1;
	}
	in >> theta0 >> theta1;
	val_los = loseFun(theta0, theta1, datax, result);
	while (abs(val_los - tmp_val) > 1e-8 && count < 1000000) {
		tmp_val = val_los;
		getGradient(&theta0, &theta1, datax, result);
		val_los = loseFun(theta0, theta1, datax, result);
		//cout << "val_los: "<<val_los <<"\t" << "tmp_val: " << tmp_val<<endl;
		count++;
	}
	in.close();
	cout << "theta0: " << theta0 << endl << "theta1: " << theta1 << endl<<"count: "<<count<<endl;
}

