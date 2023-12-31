//更相减损法
//1:gcd(a,b)=gcd(a,a-b)=gcd(b,b-a)
//2:gcd(2a,2b)=2*gcd(a,b)

//高精度的除法与取模并不容易实现
//所以要做高精度运算时，建议此法

#include <iostream>
using namespace std;

int read();

void solve()
{
    int a=read(),b=read();
    while(a!=b)
    {
        if(a>b) a-=b;
        else b-=a;
    }
    cout<<a<<endl;
}

//欧几里得

int gcd(int a,int b)
{
    if(b) return gcd(b,a%b);
    else return a;
}