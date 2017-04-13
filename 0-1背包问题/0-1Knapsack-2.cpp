//0-1背包问题动态规划
#include <iostream> 
using namespace std; 
#define MAX_NUM 10  //物品数量上限
#define MAX_CAPACITY 20 //背包容量上限
int m[MAX_NUM][MAX_CAPACITY];

void Knapsack(int v[],int w[],int c,int n)
{
	int jMax = min(w[n]-1,c); //背包剩余容量上限范围[0~w[n]-1]
	for(int j=0; j<=jMax;j++)
		m[n][j]=0;
	for(int j=w[n]; j<=c; j++) //限制范围[w[n]~c]
		m[n][j] = v[n];

	for(int i=n-1; i>1; i--)
	{
		jMax = min(w[i]-1,c);
		for(int j=0; j<=jMax; j++)
		{
			m[i][j] = m[i+1][j]; 
		}
		for(int j=w[i]; j<=c; j++) 
		{
			m[i][j] = max(m[i+1][j],m[i+1][j-w[i]]+v[i]);
		}
	}
	m[1][c] = m[2][c]; //计算最优值,最优值由m[1][c]给出
	if(c>=w[1])
	{
		m[1][c] = max(m[1][c],m[2][c-w[1]]+v[1]);
	}
}

//x[]数组存储解向量,0表示不装入背包，1表示装入背包
void Traceback(int w[],int c,int n,int x[])
{
	for(int i=1; i<n; i++)
	{
		if(m[i][c] == m[i+1][c])
		{
			x[i]=0;
		}
		else
		{
			x[i]=1;
			c-=w[i];
		}
	}
	x[n]=(m[n][c])?1:0;
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
	Knapsack(v,w,C,n);
	Traceback(w,C,n,x);
	cout<<"最优解向量为： ";
	for(int i=1;i<=n;i++)
		cout<<x[i]<<" ";
	cout<<endl<<"最大价值为： "<<m[1][C]<<endl;
	return 0;
}
