#include <iostream>
using namespace std;

// 直接用递归方法求解
int fibonacci_recur(int n)
{
	if (n == 0) {
		return 0;
	}
	else if (n == 1) {
		return 1;
	}
	else {
		return fibonacci_recur(n - 1) + fibonacci_recur(n - 2);
	}
}
// 用迭代法求解，时间复杂度为O(n)
int fibonacci_iter(int n)
{
	if (n == 0) {
		return 0;
	}
	else if (n == 1) {
		return 1;
	}
	else {
		int fib_n_1 = 1;
		int fib_n_2 = 0;
		int fib_n = 0;
		for (int i = 2; i <= n; i++)
		{
			fib_n = fib_n_1 + fib_n_2;
			fib_n_2 = fib_n_1;
			fib_n_1 = fib_n;
		}
		return fib_n;
	}
}

// 用矩阵快速幂求解，时间复杂度为O(log(n))

// 定义2*2矩阵
struct matrix {
	int m_00, m_01;
	int m_10, m_11;
	matrix(int m0 = 1, int m1 = 1, int m2 = 1, int m3 = 0)
	{
		m_00 = m0;
		m_01 = m1;
		m_10 = m2;
		m_11 = m3;
	}
};
// 计算矩阵相乘
matrix matrix_multiply(const matrix&matrix1, const matrix&matrix2)
{
	return matrix(
		matrix1.m_00 * matrix2.m_00 + matrix1.m_01 * matrix2.m_10,
		matrix1.m_00 * matrix2.m_01 + matrix1.m_01 * matrix2.m_11,
		matrix1.m_10 * matrix2.m_00 + matrix1.m_11 * matrix2.m_10,
		matrix1.m_10 * matrix2.m_01 + matrix1.m_11 * matrix2.m_11
	);
}
// 矩阵求幂
matrix matrix_power(int n)
{
	matrix R(1,1,1,0);
	matrix M;
	if (n == 1) 
	{
		return R;
	}
	else 
	{
		if (n % 2 == 0) {  // n为偶数
			M = matrix_power(n / 2);
			M = matrix_multiply(M, M);
		}
		else {  // n为奇数
			M = matrix_power((n - 1) / 2);
			M = matrix_multiply(M, M);
			M = matrix_multiply(M, R);
		}
	}
	return M;
}
int fibonacci_matrix(int n)
{
	if (n == 0) {
		return 0;
	}
	else if (n == 1) {
		return 1;
	}
	matrix M_res = matrix_power(n - 1);
	return M_res.m_00;
}

int main()
{
	int n;
	while (cin>>n)
	{
		cout << "Fibonacci(n)= " << fibonacci_recur(n) << endl;
		cout << "Fibonacci(n)= " << fibonacci_iter(n) << endl;
		cout << "Fibonacci(n)= " << fibonacci_matrix(n) << endl;
	}
	return 0;
}