//0-1背包问题动态规划
#include<iostream>
using namespace std;

//一位数组dp[]表示状态转移方程
int Knapsack(int dp[],int w[],int v[],int n,int C)
{
	for(int i=0;i<=C;i++)
		dp[i]=0;
	for(int i=1;i<=n;i++)
		for(int j=C;j>=w[i];j--)
		{
			dp[j]=max(dp[j],dp[j-w[i]]+v[i]);
		}
	return dp[C];
}

int main()
{
	int dp[20],w[11],v[11]; //最大物品数量为10
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
	cout<<"装入背包的最大价值为： "<<Knapsack(dp,w,v,n,C)<<endl;
	return 0;
}