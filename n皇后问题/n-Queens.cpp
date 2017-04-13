#include<iostream>
#include<cmath>
using namespace std;
//判断第t个皇后当前的位置是否与t之前的皇后位置冲突
bool Placed(int x[],int t)
{
	for(int i=1;i<t;i++)
		if((x[i] == x[t])||abs(t-i) == abs(x[t]-x[i]))
		{ return false;}
	return true;
}
//n皇后问题递归算法
void nQueenRecursion(int x[],int t,int n)
{
	if(t>n)
	{
		for(int i=1;i<=n;i++)
			cout<<x[i]<<" ";
		cout<<endl;
	}
	else{
		for(int i=1;i<=n;i++)
		{
			x[t]=i;
			if(Placed(x,t))
			{
				nQueenRecursion(x,t+1,n);
			}
		}
	}
}
//n皇后问题迭代算法
void nQueenIterationn(int x[],int n)
{
	int t=1;
	for(int i=1;i<=n;i++)
		x[i]=0;
	while(t>=1)
	{
		while(x[t]<n)
		{
			x[t]=x[t]+1;
			if(Placed(x,t))
			{
				t=t+1;
				if(t>n)
				{
					for(int i=1;i<=n;i++)
						cout<<x[i]<<" ";
					cout<<endl;
					t=t-1;
				}
			}
		}
		x[t]=0;
		t=t-1;
	}
}

int main()
{
	const int MAX_NUM=11;
	int x[MAX_NUM];
	int n;
	cout<<"请输入n皇后问题的n值（n<=10）：";
	cin>>n;
	cout<<"(1)递归回溯求解："<<endl;
	nQueenRecursion(x,1,n);
	cout<<"(2)迭代回溯求解："<<endl;
	nQueenIterationn(x,n);
}