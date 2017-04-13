#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<ctime>
#include<cmath>
#include<malloc.h>
#include<iostream>
using namespace std;
#define MAX 100
#define LEN sizeof(struct node)
struct node
{
    int bignum[MAX];
    struct node *next;
};
void print(int a[MAX]);
int compare(int a1[MAX],int a2[MAX]);
void mov(int a[MAX],int *b);
void multiply(int a1[MAX],int a2[MAX],int *c);
void add(int a1[MAX],int a2[MAX],int *c);
void sub(int a1[MAX],int a2[MAX],int *c);
void mod(int a[MAX],int b[MAX],int *c);
void divide(int t[MAX],int b[MAX],int *c ,int *w);
void multiplymod(int a[MAX] ,int b[MAX] ,int n[MAX],int *m);
void expmod(int a[MAX] ,int p[MAX] ,int n[MAX],int *m);
int is_prime_san(int p[MAX]);
int coprime(int e[MAX],int s[MAX]);
void prime_random(int *p,int *q);
void compute_e(int e[MAX],int m[MAX]);
void compute_d(int e[MAX],int g[MAX],int *d);
void printbig(struct node *h);
struct node *input();
struct node *encryption(int e[MAX],int n[MAX],struct node *head);
void decryption(int d[MAX],int n[MAX],struct node *h);

//格式化输出
void print(int a[MAX])
{
    for(int i=0; i<a[99]; i++)
        printf("%d",a[a[99]-i-1]);
    printf("\n");
    return;
}
//比较函数
int compare(int a1[MAX],int a2[MAX])
{
    int l1, l2;
    int i;
    l1=a1[99];
    l2=a2[99];
    if (l1>l2)
        return 1;
    if (l1<l2)
        return -1;
    for(i=(l1-1); i>=0; i--)
    {
        if (a1[i]>a2[i])
            return 1 ;
        if (a1[i]<a2[i])
            return -1;
    }
    return 0;
}
//复制函数
void mov(int a[MAX],int *b)
{
    for(int j=0; j<MAX; j++)
        b[j]=a[j];
    return ;
}
//乘法计算函数
void multiply(int a1[MAX],int a2[MAX],int *c)
{
    int i,j,y,x,z,w,l1,l2;
    l1=a1[MAX-1];
    l2=a2[MAX-1];
    if (a1[MAX-2]=='-'&& a2[MAX-2]=='-')
        c[MAX-2]=0;
    else if (a1[MAX-2]=='-')
        c[MAX-2]='-';
    else if (a2[MAX-2]=='-')
        c[MAX-2]='-';
    for(i=0; i<l1; i++)
    {
        for(j=0; j<l2; j++)
        {
            x=a1[i]*a2[j];
            y=x/10;
            z=x%10;
            w=i+j;
            c[w]=c[w]+z;
            c[w+1]=c[w+1]+y+c[w]/10;
            c[w]=c[w]%10;
        }
    }
    w=l1+l2;
    if(c[w-1]==0)w=w-1;
    c[MAX-1]=w;
    return;
}
//加法计算函数
void add(int a1[MAX],int a2[MAX],int *c)
{
    int i,l1,l2;
    int len,temp[MAX];
    int k=0;
    l1=a1[MAX-1];
    l2=a2[MAX-1];
    if((a1[MAX-2]=='-')&&(a2[MAX-2]=='-'))
    {
        c[MAX-2]='-';
    }
    else if (a1[MAX-2]=='-')
    {
        mov(a1,temp);
        temp[MAX-2]=0;
        sub(a2,temp,c);
        return;
    }
    else if (a2[MAX-2]=='-')
    {
        mov(a2,temp);
        temp[98]=0;
        sub(a1,temp,c);
        return;
    }
    if(l1<l2)len=l1;
    else len=l2;
    for(i=0; i<len; i++)
    {
        c[i]=(a1[i]+a2[i]+k)%10;
        k=(a1[i]+a2[i]+k)/10;
    }
    if(l1>len)
    {
        for(i=len; i<l1; i++)
        {
            c[i]=(a1[i]+k)%10;
            k=(a1[i]+k)/10;
        }
        if(k!=0)
        {
            c[l1]=k;
            len=l1+1;
        }
        else len=l1;
    }
    else
    {
        for(i=len; i<l2; i++)
        {
            c[i]=(a2[i]+k)%10;
            k=(a2[i]+k)/10;
        }
        if(k!=0)
        {
            c[l2]=k;
            len=l2+1;
        }
        else len=l2;
    }
    c[99]=len;
    return;
}
//减法计算函数
void sub(int a1[MAX],int a2[MAX],int *c)
{
    int i,l1,l2;
    int len,t1[MAX],t2[MAX];
    int k=0;
    l1=a1[MAX-1];
    l2=a2[MAX-1];
    if ((a1[MAX-2]=='-') && (a2[MAX-2]=='-'))
    {
        mov(a1,t1);
        mov(a2,t2);
        t1[MAX-2]=0;
        t2[MAX-2]=0;
        sub(t2,t1,c);
        return;
    }
    else if( a2[MAX-2]=='-')
    {
        mov(a2,t2);
        t2[MAX-2]=0;
        add(a1,t2,c);
        return;
    }
    else if (a1[MAX-2]=='-')
    {
        mov(a2,t2);
        t2[MAX-2]='-';
        add(a1,t2,c);
        return;
    }
    if(compare(a1,a2)==1)
    {

        len=l2;
        for(i=0; i<len; i++)
        {
            if ((a1[i]-k-a2[i])<0)
            {
                c[i]=(a1[i]-a2[i]-k+10)%10;
                k=1;
            }
            else
            {
                c[i]=(a1[i]-a2[i]-k)%10;
                k=0;
            }
        }

        for(i=len; i<l1; i++)
        {
            if ((a1[i]-k)<0)
            {
                c[i]=(a1[i]-k+10)%10;
                k=1;
            }
            else
            {
                c[i]=(a1[i]-k)%10;
                k=0;
            }
        }
        if(c[l1-1]==0)
        {
            len=l1-1;
            i=2;
            while (c[l1-i]==0)
            {
                len=l1-i;
                i++;
            }
        }
        else
        {
            len=l1;
        }
    }
    else if(compare(a1,a2)==(-1))
    {
        c[MAX-2]='-';
        len=l1;
        for(i=0; i<len; i++)
        {
            if ((a2[i]-k-a1[i])<0)
            {
                c[i]=(a2[i]-a1[i]-k+10)%10;
                k=1;
            }
            else
            {
                c[i]=(a2[i]-a1[i]-k)%10;
                k=0;
            }
        }
        for(i=len; i<l2; i++)
        {
            if ((a2[i]-k)<0)
            {
                c[i]=(a2[i]-k+10)%10;
                k=1;
            }
            else
            {
                c[i]=(a2[i]-k)%10;
                k=0;
            }
        }
        if(c[l2-1]==0)
        {
            len=l2-1;
            i=2;
            while (c[l1-i]==0)
            {
                len=l1-i;
                i++;
            }
        }
        else len=l2;

    }
    else if(compare(a1,a2)==0)
    {
        len=1;
        c[len-1]=0;
    }
    c[MAX-1]=len;
    return;
}
//求模运算c=a mod b
void mod(int a[MAX],int b[MAX],int *c)
{
    int d[MAX];
    mov (a,d);
    while (compare(d,b)!=(-1))
    {
        sub(d,b,c);
        mov(c,d);
    }
    return ;
}
//广义欧几里得除法运算
void divide(int t[MAX],int b[MAX],int *c ,int *w)
{
    int a1,b1,i,j,m;
    int d[MAX],e[MAX],f[MAX],g[MAX],a[MAX];

    mov(t,a);
    for(i=0; i<MAX; i++)
        e[i]=0;
    for(i=0; i<MAX; i++)
        d[i]=0;
    for(i=0; i<MAX; i++) g[i]=0;
    a1=a[MAX-1];
    b1=b[MAX-1];
    if (compare(a,b)==(-1))
    {
        c[0]=0;
        c[MAX-1]=1;
        mov(t,w);
        return;
    }
    else if (compare(a,b)==0)
    {
        c[0]=1;
        c[MAX-1]=1;
        w[0]=0;
        w[MAX-1]=1;
        return;
    }
    m=(a1-b1);
    for(i=m; i>=0; i--)
    {
        for(j=0; j<MAX; j++)
            d[j]=0;
        d[i]=1;
        d[MAX-1]=i+1;
        mov(b,g);
        multiply(g,d,e);

        while (compare(a,e)!=(-1))
        {
            c[i]++;
            sub(a,e,f);
            mov(f,a);
        }
        for(j=i; j<MAX; j++) 
            e[j]=0;
    }
    mov(a,w);
    if (c[m]==0) c[MAX-1]=m;
    else c[MAX-1]=m+1;
    return;
}
//求模运算 m=a*b mod n
void multiplymod(int a[MAX] ,int b[MAX] ,int n[MAX],int *m)
{
    int c[MAX],d[MAX];
    int i;
    for(i=0; i<MAX; i++)
        d[i]=c[i]=0;
    multiply(a,b,c);
    divide(c,n, d,m);
    for(i=0; i<m[MAX-1]; i++)
        printf("%d",m[m[MAX-1]-i-1]);
    printf("\nm length is : %d \n",m[MAX-1]);
}
//求模 m=a^p mod n
void expmod(int a[MAX] ,int p[MAX] ,int n[MAX],int *m)
{
    int t[MAX],l[MAX],temp[MAX]; //t放入2，l放入1
    int w[MAX],s[MAX],c[MAX],b[MAX],i;
    for(i=0; i<MAX-1; i++)
        b[i]=l[i]=t[i]=w[i]=0;
    t[0]=2;
    t[MAX-1]=1;
    l[0]=1;
    l[MAX-1]=1;
    mov(l,temp);
    mov(a,m);
    mov(p,b);
    while(compare(b,l)!=0)
    {
        for(i=0; i<MAX; i++)
            w[i]=c[i]=0;
        divide(b,t,w,c);
        mov(w,b);
        if(compare(c,l)==0)
        {
            for(i=0; i<MAX; i++)
                w[i]=0;
            multiply(temp,m,w);
            mov(w,temp);

            for(i=0; i<MAX; i++)
                w[i]=c[i]=0;
            divide(temp,n,w,c);
            mov(c,temp);
        }
        for(i=0; i<MAX; i++)
            s[i]=0;
        multiply(m,m,s);
        for(i=0; i<MAX; i++)
            c[i]=0;
        divide(s,n,w,c);
        mov (c,m);
    }
    for(i=0; i<MAX; i++)
        s[i]=0;
    multiply(m,temp,s);
    for(i=0; i<MAX; i++)
        c[i]=0;
    divide(s,n,w,c);
    mov (c,m);
    m[MAX-2]=a[MAX-2];
    return;
}
//判断大数是否为素数
int is_prime_san(int p[MAX])
{

    int i,a[MAX],t[MAX],s[MAX],o[MAX];
    for(i=0; i<MAX; i++)
        s[i]=o[i]=a[i]=t[i]=0;
    t[0]=1;
    t[MAX-1]=1;
    a[0]=2;
    a[MAX-1]=1;
    sub(p,t,s);
    expmod ( a, s, p ,o);
    if ( compare(o,t) != 0 )
    {
        return 0;
    }
    a[0]=3;
    for(i=0; i<MAX; i++) o[i]=0;
    expmod ( a, s, p ,o);
    if ( compare(o,t) != 0 )
    {
        return 0;
    }
    a[0]=5;
    for(i=0; i<MAX; i++) o[i]=0;
    expmod ( a, s, p ,o);
    if ( compare(o,t) != 0 )
    {
        return 0;
    }
    a[0]=7;
    for(i=0; i<MAX; i++) o[i]=0;
    expmod ( a, s, p ,o);
    if ( compare(o,t) != 0 )
    {
        return 0;
    }
    return 1;
}
//判断两个大数是否互素
int coprime(int e[MAX],int s[MAX])
{
    int a[MAX],b[MAX],c[MAX],d[MAX],o[MAX],l[MAX];
    int i;
    for(i=0; i<MAX; i++)
        l[i]=o[i]=c[i]=d[i]=0;
    o[0]=0;
    o[MAX-1]=1;
    l[0]=1;
    l[MAX-1]=1;
    mov(e,b);
    mov(s,a);
    do
    {
        if(compare(b,l)==0)
        {
            return 1;
        }
        for(i=0; i<MAX; i++)
            c[i]=0;
        divide(a,b,d,c);
        mov(b,a);
        mov(c,b);
    }
    while(compare(c,o)!=0);
    return 0;
}
//产生随机素数p和q
void prime_random(int *p,int *q)
{
    int i,k;
    time_t t;
    p[0]=1;
    q[0]=3;
    p[MAX-1]=10;
    q[MAX-1]=11;

    do
    {
        t=time(NULL);
        srand((unsigned long)t);
        for(i=1; i<p[MAX-1]-1; i++)
        {
            k=rand()%10;
            p[i]=k;
        }
        k=rand()%10;
        while (k==0)
        {
            k=rand()%10;
        }
        p[p[MAX-1]-1]=k;
    }
    while((is_prime_san(p))!=1);
    printf("随机生成素数p为: p=");
    for(i=0; i<p[MAX-1]; i++)
    {
        printf("%d",p[p[MAX-1]-i-1]);
    }
    printf("\n");
    do
    {
        t=time(NULL);
        srand((unsigned long)t);
        for(i=1; i<q[MAX-1]; i++)
        {
            k=rand()%10;
            q[i]=k;
        }
    }
    while((is_prime_san(q))!=1);
    printf("随机生成素数q为: q=");
    for(i=0; i<q[MAX-1]; i++)
    {
        printf("%d",q[q[MAX-1]-i-1]);
    }
    printf("\n");
    return;
}
//产生公钥e
void compute_e(int e[MAX],int m[MAX])
{
    int i,k;
    time_t t;
    e[MAX-1]=5;
    printf("生成公钥e为: e=");
    do
    {
        t=time(NULL);
        srand((unsigned long)t);
        for(i=0; i<e[MAX-1]-1; i++)
        {
            k=rand()%10;
            e[i]=k;
        }
        while((k=rand()%10)==0)
            k=rand()%10;
        e[e[MAX-1]-1]=k;
    }
    while(coprime( e, m)!=1);
    for(i=0; i<e[MAX-1]; i++)
    {
        printf("%d",e[e[MAX-1]-i-1]);
    }
    printf("\n");
    return ;
}
//计算私钥d
void compute_d(int e[MAX],int g[MAX],int *d)
{
    int r[MAX],n1[MAX],n2[MAX],k[MAX],w[MAX];
    int i,t[MAX],b1[MAX],b2[MAX],temp[MAX];
    mov(g,n1);
    mov(e,n2);
    for(i=0; i<MAX; i++)
        k[i]=w[i]=r[i]=temp[i]=b1[i]=b2[i]=t[i]=0;
    b1[MAX-1]=0;
    b1[0]=0;
    b2[MAX-1]=1;
    b2[0]=1;
    while(1)
    {
        for(i=0; i<MAX; i++)
            k[i]=w[i]=0;
        divide(n1,n2,k,w);
        for(i=0; i<MAX; i++)
            temp[i]=0;
        multiply(k,n2,temp);
        for(i=0; i<MAX; i++)
            r[i]=0;
        sub(n1,temp,r);
        if((r[MAX-1]==1) && (r[0]==0))
        {
            break;
        }
        else
        {
            mov(n2,n1);
            mov( r,n2);
            mov(b2, t);
            for(i=0; i<MAX; i++)
                temp[i]=0;
            multiply(k,b2,temp);
            for(i=0; i<MAX; i++)
                b2[i]=0;
            sub(b1,temp,b2);
            mov(t,b1);
        }
    }
    for(i=0; i<MAX; i++)
        t[i]=0;
    add(b2,g,t);
    for(i=0; i<MAX; i++)
        temp[i]=d[i]=0;
    divide(t,g,temp,d);
    printf("生成私钥d为: d=");
    for(i=0; i<d[MAX-1]; i++)
        printf("%d",d[d[MAX-1]-i-1]);
    printf("\n");
}
//加密和解密
void printbig(struct node *h)
{
    struct node *p;
    int i;
    p=(struct node * )malloc(LEN);
    p=h;
    if(h!=NULL)
        do
        {
            for(i=0; i<p->bignum[MAX-1]; i++)
                printf("%d",p->bignum[p->bignum[MAX-1]-i-1]);
            p=p->next;
        }
        while(p!=NULL);
    printf("\n");
}
//输入处理函数
struct node *input()
{
    struct node *head;
    struct node *p1,*p2;
    int i,n,c,temp;
    char ch;
    n=0;
    p1=p2=(struct node * )malloc(LEN);
    head=NULL;
    printf("输入待加密的明文：\n");
    fflush(stdin);//清空输入缓冲区
    while((ch=getchar())!='\n')
    {
        i=0;
        c=ch;
        if(c<0)
        {
            c=abs(c);//把负数取正并且做一个标记
            p1->bignum[MAX-2]='0';
        }
        else
        {
            p1->bignum[MAX-2]='1';
        }
        while(c/10!=0)
        {
            temp=c%10;
            c=c/10;
            p1->bignum[i]=temp;
            i++;
        }
        p1->bignum[i]=c;
        p1->bignum[MAX-1]=i+1;
        n=n+1;
        if(n==1)
            head=p1;
        else p2->next=p1;
        p2=p1;
        p1=(struct node * )malloc(LEN);
    }
    p2->next=NULL;
    return(head);
}
//加密模块，即C = M^e mod n
struct node *encryption(int e[MAX],int n[MAX],struct node *head)
{
    struct node *p;
    struct node *h;
    struct node *p1,*p2;
    int m=0,i;
    printf("加密后密文为：\n");
    p1=p2=(struct node* )malloc(LEN);
    h=NULL;
    p=head;
    if(head!=NULL)
        do{
            expmod( p->bignum , e ,n ,p1->bignum);
            for(i=0; i<p1->bignum[MAX-1]; i++)
            {
                printf("%d",p1->bignum[p1->bignum[MAX-1]-1-i]);
            }
            m=m+1;
            if(m==1)
                h=p1;
            else p2->next=p1;
            p2=p1;
            p1=(struct node * )malloc(LEN);
            p=p->next;
        }
        while(p!=NULL);
    p2->next=NULL;
    p=h;
    printf("\n");
    return(h);

}
//解密模块，即P = C^d mod n
void decryption(int d[MAX],int n[MAX],struct node *h)
{
    int i,j,temp;
    struct node *p,*p1;
    char ch[65535];
    p1=(struct node* )malloc(LEN);
    p=h;
    j=0;

    if(h!=NULL)
        do
        {
            for(i=0; i<MAX; i++)
                p1->bignum[i]=0;
            expmod( p->bignum , d ,n ,p1->bignum);
            temp=p1->bignum[0]+p1->bignum[1]*10+p1->bignum[2]*100;
            if (( p1->bignum[MAX-2])=='0')
            {
                temp=0-temp;
            }

            ch[j]=temp;
            j++;
            p=p->next;
        }
        while (p!=NULL);
    printf("解密后明文为:\n");
    for(i=0; i<j; i++)
        printf("%c",ch[i]);
    printf("\n");
    return;
}

//主函数
int main()
{
    char c;
    int p[MAX],q[MAX],n[MAX],d[MAX],e[MAX],m[MAX],p1[MAX],q1[MAX];
    struct node *head,*h1;
	printf("******************【RSA算法】*********************\n");
    while(1)
    {
        for(int i=0; i<MAX; i++)
		{
			m[i]=p[i]=q[i]=n[i]=d[i]=e[i] = 0;
		}
        prime_random(p,q); //随机产生两个大素数
        multiply(p,q,n); //n=p*q
        printf("计算系统模: n=");
        print(n);
        mov(p,p1);
        p1[0]--;  //p-1
        mov(q,q1);
        q1[0]--;  //q-1
        multiply(p1,q1,m); //m=(p-1)*(q-1)
		printf("计算欧拉函数: Φ（N）=");
		print(m);
        compute_e(e,m); //产生一个与m互素的随机数
        compute_d(e,m,d); //e*d = 1 mod m
   
        head=input();
        h1=encryption(e, n, head);
        decryption(d, n, h1);
        
		printf("是否继续？（Y/N）");
		cin>>c;
		if(c == 'N' || c == 'n')
			break;
    }
    return 0;
}