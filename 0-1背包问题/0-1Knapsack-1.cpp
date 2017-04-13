//0-1背包问题动态规划
#include<iostream>
using namespace std;
#define MAX_NUM 10 //物品数量上限
#define MAX_CAPACITY 20 //背包容量上限
int c[MAX_NUM][MAX_CAPACITY];

void Knapsack(int w[],int v[],int n,int C)
{
	for(int i=0;i<=C;i++)
		c[0][i]=0;
	for(int i=1;i<=n;i++)
	{
		c[i][0]=0;
		for(int j=1;j<=C;j++)
		{
			if(w[i]<=j)
			{
				if(v[i]+c[i-1][j-w[i]] > c[i-1][j])
					c[i][j] = v[i]+c[i-1][j-w[i]];
				else c[i][j] = c[i-1][j];
			}
			else c[i][j]= c[i-1][j];
		}
	}
}

//x[]数组存储解向量,0表示不装入背包，1表示装入背包
void Traceback(int w[],int n,int C,int x[])
{
	for(int k=n;k>=2;k--)
	{
		if(c[k][C]==c[k-1][C])
			x[k]=0;
		else
		{
			x[k]=1;
			C=C-w[k];
		}
	}
	x[1]=c[1][C]?1:0;
}
int main()
{
	int w[10],v[10];
	int x[10];
	int n,C;
	cout<<"输入物品的总数： ";
	cin>>n;
	cout<<"输入背包的容量： ";
	cin>>C;
	cout<<"依次输入物品的重量： ";
	for(int i=1;i<=n;i++)
		cin>>w[i];
	cout<<"依次输入物品的价值： ";
	for(int i=1;i<=n;i++)
		cin>>v[i];
	Knapsack(w,v,n,C);
	Traceback(w,n,C,x);
	cout<<"最优解向量为： ";
	for(int i=1;i<=n;i++)
		cout<<x[i]<<" ";
	cout<<endl<<"最大价值为： "<<c[n][C]<<endl;
	return 0;
}