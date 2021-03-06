#include <stdio.h>
#include <stdlib.h>
#include<math.h>;
typedef unsigned __int64 hugeint;
//求出最大公约数
hugeint gcd(hugeint A, hugeint B)
{
    while (A != 0)
    {
        hugeint C = B % A;
        B = A;
        A = C;
    }
    return B;
}

//求a*b%c，要求:a,b的范围在hugeint范围的一般以内，在hugeint为unsigned __int64时，a,b需要是__int64能表示的数
hugeint product_mod(hugeint A, hugeint B, hugeint C)
{
    hugeint R, D;
    R = 0;
    D = A;
    while (B > 0)
    {
        if ( B&1 ) R = (R + D) % C;
        D = (D + D) % C;
        B >>=1;
    }
    return R;
}

//求a^b%c，要求:a,b的范围在hugeint范围的一般以内，在hugeint为unsigned __int64时，a,b需要是__int64能表示的数
hugeint power_mod(hugeint A, hugeint B, hugeint C)
{
    hugeint R = 1, D = A;
    while (B )
    {
        if (B&1) R = product_mod(R, D, C);
        D = product_mod(D, D, C);
        B >>=1;
    }
    return R;
}

//给出随机数，可以简单的用rand()代替
hugeint rAndom()
{ 
        hugeint a; 
        a  = rand();
        a *= rand(); 
        a *= rand();
        a *= rand();
        return a; 
}

//rabinmiller方法测试n是否为质数
int pri[]={2,3,5,7,11,13,17,19,23,29};
bool isprime(hugeint n)  
{
    if(n<2)
        return false;
    if(n==2)
        return true;
    if(!(n&1))
        return false;
    hugeint k = 0, i, j, m, a; 
    m = n - 1; 
    while(m % 2 == 0)
        m = (m >> 1), k++; 
    for(i = 0; i < 10; i ++)
    {
        if(pri[i]>=n)return 1;
        a = power_mod( pri[i], m, n ); 
        if(a==1)    
            continue; 
        for(j = 0; j < k; j ++)
        { 
            if(a==n-1)break; 
            a = product_mod(a,a,n); 
        } 
        if(j < k)
            continue; 
        return false ; 
    } 
    return true; 
} 

//pollard_rho分解，给出N的一个非1因数，返回N时为一次没有找到
hugeint pollard_rho(hugeint C, hugeint N)
{
    hugeint I, X, Y, K, D;
    I = 1;
    X = rand() % N;
    Y = X;
    K = 2;
    do
    {
        I++;
        D = gcd(N + Y - X, N);
        if (D > 1 && D < N) return D;
        if (I == K) Y = X, K *= 2;
        X = (product_mod(X, X, N) + N - C) % N;
    }while (Y != X);
    return N;
}

//找出N的最小质因数
hugeint rho(hugeint N)
{
    if (isprime(N)) return N;
    do
    {
        hugeint T = pollard_rho(rand() % (N - 1) + 1, N);
        if (T < N)
        {
              hugeint A, B;
              A = rho(T);
			  B=N;
			  while(B%T==0) B/=T;
			  if(B==1) return A;
              B = rho(B);
              return A < B ? A : B;
        }
    }
    while (true);
}
/*
long long leh(long long n)
{
	if(isprime(n)) return n;
	long long a,b,c,r,m,B=(long long) pwo((double )n),1.0/3.0+1;
	double t;
	for(int i=2;i<=B;i++)
	{
		if(n%i==0) return i;
	}
	for(i=1;i<=b;i++)
	{
		if(i%2==0)
		{
			m=2;
			r=1;
		}
		else
		{
			m=4;
			r=(i+n)%m;
		}
		t=4;
		t*=i*n;
		a=sqrt(n);
		while(a*a<)
	}
}
*/
int main ()
{

    int t;
    hugeint n, ans;
    scanf ( "%d", &t );
    while ( t -- )
    {
        scanf ( "%I64d", &n );
        ans = rho ( n );
        if ( ans == n )
        {
            printf ( "Prime\n"  );
        }
        else
        {
            printf ( "%I64d\n", ans );
        }
    }
    return 0;
}
