#include <iostream>
#include <cmath>
using namespace std;

//Newton法求解方程
//给定不同初值x0
void CalNewton(double x0, double *fx, int n)
{
	const double e = 1e-5;  //定义误差精度
	const int MAX_NUM = 100;  //定义最大迭代次数
	int k = 0;   //记录迭代次数
	 
	//计算f'(x)的系数项
	double *f = new double[n];
	for (int i = n-1; i >= 0; i--)
	{
		f[i] = (i + 1)*fx[i + 1];
	}

	double xk = x0;
	double xk1;
	double fx_k;
	double f_k;
	while (k < MAX_NUM)
	{
		fx_k = 0;
		f_k = 0;
		//计算f(xk)
		for (int i = n; i >= 0; i--)
		{
			fx_k += fx[i] * pow(xk, i);
		}
		//计算f'(xk)
		for (int i = n - 1; i >= 0; i--)
		{
			f_k += f[i] * pow(xk, i);
		}
		//Newton法公式
		xk1 = xk - fx_k / f_k;

		cout << k << "\t" << xk << endl;
		if (abs(xk1 - xk) < e)
		{
			cout << k+1 << "\t" << xk1 << endl;
			return;
		}
		k++;
		xk = xk1;
	}
	delete[]f;
	return;
}

int main()
{
	int n;
	double x0;

	cout << "请输入方程的最高阶次数：";
	cin >> n;

	double *fx = new double[n+1];
	cout << "请输入方程的系数项：";
	for (int i = n; i >=0; i--)
	{
		cin >> fx[i];
	}
	while (true)
	{
		cout << "请输入初值x0：";
		cin >> x0;
		cout << "k\tx(k)" << endl;
		CalNewton(x0, fx, n);
		char ch;
		cout << "继续？（Y/N）";
		cin >> ch;
		if (ch == 'N' || ch == 'n')
		{
			break;
		}
	}
	
	delete[]fx;
	return 0;
}