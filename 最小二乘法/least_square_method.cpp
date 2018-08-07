#include <iostream>
#include <cmath>
using namespace std;

double SumPow(double *x, int n, int exp)
{
	double sumPow = 0;
	for (int i = 0; i < n; i++)
	{
		sumPow += pow(x[i], exp);
	}
	return sumPow;
}

//计算方程组的系数矩阵
//保存在matrixA中
void CalMatrixA(double *x, int n, int exp, double **&matrixA)
{
	for (int i = 0; i <= exp; i++)
	{
		for (int j = 0; j <= exp; j++)
		{
			matrixA[i][j] = SumPow(x, n, i + j);
		}
	}
}
//计算方程组的右端项
//保存在vectorB中
void CalVectorB(double *x, double *y, int n, int exp, double *&vectorB)
{
	double sumMultiplyXY = 0;
	for (int i = 0; i <= exp; i++)
	{
		sumMultiplyXY = 0;
		for (int j = 0; j < n; j++)
		{
			sumMultiplyXY += pow(x[j], i)*y[j];
		}
		vectorB[i] = sumMultiplyXY;
	}
}
//高斯消去法求解方程组
//结果保存在coff[]中
void CalEquation(double **&matrixA, double *vectorB, int exp, double *&coff)
{
	//消元过程
	for (int k = 0; k <= exp - 1; k++)
	{
		for (int i = k + 1; i <= exp; i++)
		{
			double m1 = 0;
			if (abs(matrixA[k][k]) >= 1e-5)
			{
				m1 = matrixA[i][k] / matrixA[k][k];
			}
			for (int j = k + 1; j <= exp; j++)
			{
				matrixA[i][j] = matrixA[i][j] - matrixA[k][j] * m1;
			}
			vectorB[i] = vectorB[i] - vectorB[k] * m1;
		}
	}
	//回代求解
	for (int m = exp; m >= 0; m--)
	{
		double sumAB = 0;
		for (int j = m + 1; j <= exp; j++)
		{
			sumAB += matrixA[m][j] * coff[j];
		}
		coff[m] = (vectorB[m] - sumAB) / matrixA[m][m];
	}
}

//计算偏差平方和
double CalSquareSum(double *y, double *x, double *coff, int n, int exp)
{
	double squareSum = 0;
	for (int i = 0; i < n; i++)
	{
		double Yi = 0;
		for (int k = 0; k <= exp; k++)
		{
			Yi += coff[k] * pow(x[i], k);
		}
		cout << y[i] << "\t" << Yi << endl;
		squareSum = squareSum +pow( (y[i] - Yi), 2);
	}
	return squareSum;
}

int main()
{
	const int n = 29;
	//年份x
	double x[n] = { 1949,1950,1952,1953,1955,1956,1957,1958,1959,1960,
		1961,1962,1963,1965,1966,1967,1968,1970,1971,1972,
		1974,1975,1976,1977,1979,1980,1982,1983,1984 };
	//人口数y
	double y[n] = { 5.4167, 5.5196, 5.7428, 5.8796, 6.1465, 6.2828, 6.4653, 6.4653, 6.5994, 6.6207,
		6.5859, 6.7297, 6.9172, 7.2538, 7.4542, 7.6368, 7.8534, 8.2992, 8.5229, 8.7177,
		9.0859, 9.242, 9.3717, 9.4974, 9.7542, 9.8705, 10.1541, 10.2495, 10.3475 };

	cout << "样本数据为：\n年份x\t人口数y（亿）" << endl;

	for (int i = 0; i < n; i++)
	{
		cout << x[i] << "\t" << y[i] << endl;
	}

	int exp;
	cout << "请输入拟合多项式的次数n: ";
	cin >> exp;
	double **matrixA = new double*[exp + 1];
	for (int i = 0; i < exp + 1; i++)
	{
		matrixA[i] = new double[exp + 1];
	}
	double *vectorB = new double[exp + 1];
	double *coff = new double[exp + 1];

	CalMatrixA(x, n, exp, matrixA);
	CalVectorB(x, y, n, exp, vectorB);
	CalEquation(matrixA, vectorB, exp, coff);

	cout << "最小二乘拟合函数为： y = ";
	
	for (int i = 0; i < exp + 1;i++)
	{
		if (i == 0)
		{
			cout << coff[0];
		}
		else if (i == 1)
		{
			if (coff[1] < 0)
			{
				cout << " - " << (0 - coff[1]) << "x";
			}
			else
				cout <<" + "<< coff[1] << "x";
		}
		else
		{
			if (coff[i] < 0)
			{
				cout << " - " << (0 - coff[i]) << "x^" << i;
			}
			else
				cout<<" + " << coff[i] << "x^" << i ;
		}
	}

	cout << endl << endl <<  "实际值y\t拟合值Y" << endl;
	double sum = CalSquareSum(y, x, coff, n, exp);
	cout << "偏差平方和Q为："<<sum<<endl;

	for (int i = 0; i < exp + 1; i++)
		delete[]matrixA[i];
	delete[]matrixA;
	delete[] coff;
	return 0;
}