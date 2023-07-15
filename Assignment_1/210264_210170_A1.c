//Rfib program
#include<stdio.h>
#include<time.h>
int Rfib(int n)
{
	if (n==2)
	{
		return 1;
	}
	else if(n==1)
	{
		return 0;
	}
	else
	{
		return (Rfib(n-1)+Rfib(n-2));
	}
}
 
void forRfib()
{
	int n, ans;
	clock_t start_t, end_t;
	double total_t=0;
	scanf("%d", &n);
	for(int i=0 ; i<1 ; i++)
	{
		start_t=clock();
		ans=Rfib(n);
		end_t=clock();
		total_t+=(end_t-start_t);
	}
	total_t=(double)total_t/CLOCKS_PER_SEC;
	printf("%f %d\n", total_t/1, ans);
}


//Ifib program

int Ifib(long long int n)
{
	if(n==1)
	{
		return 0;
	}
	else if(n==2)
	{
		return 1;
	}
	else
	{
		int a=0;
		int b=1;
		int temp=0;
		for(long long int i=2 ; i<n ; i++)
		{
			temp=b;
			b=(a+b)%2021;
			a=temp;
		}
		return b;
	}
}

void forIfib()
{
	long long int n, ans;
	clock_t start_t, end_t;
	double total_t=0;
	scanf("%lld", &n);
	for(int i=0 ; i<1 ; i++)
	{
		start_t=clock();
		ans=Ifib(n);
		end_t=clock();
		total_t+=(end_t-start_t);
	}
	total_t=(double)total_t/CLOCKS_PER_SEC;
	printf("%f %lld\n", total_t/1, ans);
}


//Cleverfib program

void multiply(int a[2][2], int b[2][2])
{
	int x =  (a[0][0]*b[0][0] + a[0][1]*b[1][0])%2021;
	int y =  (a[0][0]*b[0][1] + a[0][1]*b[1][1]);
	int z =  (a[1][0]*b[0][0] + a[1][1]*b[1][0]);
	int w =  (a[1][0]*b[0][1] + a[1][1]*b[1][1]);
	
	a[0][0] = x;
	a[0][1] = y;
	a[1][0] = z;
	a[1][1] = w;
}

void power(int a[2][2], int n)
{
	if(n==0 || n==1)
	{
		return;
	}
	int b[2][2] = {{1,1},{1,0}};
	power(a, n/2);
		multiply(a, a);	
	if(n%2 != 0)
	{
		multiply(a, b);
	}
}

int Cleverfib(long long int n)
{
	int a[2][2] = {{1,1},{1,0}};
	if(n==0)
	{
		return 0;
	}
	power(a, n-1);
	return a[0][0];
}

void forClever()
{
	long long int n, ans;
	clock_t start_t, end_t;
	double total_t=0;
	scanf("%lld", &n);
	start_t=clock();
	for(long int i=0 ; i<10000000 ; i++)
	{
		ans=Cleverfib(n-1);
	}
	end_t=clock();
	total_t+=(end_t-start_t);
	total_t=(double)total_t;
	printf("%lf %lld\n", total_t/10, ans);
}

void main()
{
	int q;
	printf("for Rfib, input 1, 2 for Ifib, 3 for Cleverfib");
	scanf("%d", &q);
	if(q==1)
	{
		forRfib();
	}
	else if(q==2)
	{
		forIfib();
	}
	else if(q==3)
	{
		forClever();
	}
	else
	{
		printf("1,2,3 only please :)");
	}
}