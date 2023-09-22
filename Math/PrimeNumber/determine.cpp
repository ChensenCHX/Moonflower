##试除法

bool is_prime(int x)
{
    if(x<2) return 0;
    if(x!=2&&x%2==0) return 0; 
    //第一步不可省略
    //不为2的偶数一定不是质数，可有效提高效率
    for(int i=2;i<=x/i;i++)
    {
        if(x%i==0) return 0;
    }
    return 1;
}
//------------------------------------

## Miller-Robbin

//前置知识：
//1：费马小定理：如果p位质数，则a^(p-1)≡1(mod p)
//但是！质数一定满足费马小定理，但满足费马小定理的不一定是质数，所以还需要外加一个判断
//2:如果p为质数，则对任意0<x<p,有x^2≡1(mod p),x1=1,x2=p-1
//所以就对符合费马小定理的情况再加以判断，看值是不是1/p-1
//3：运算上的知识，任何一个偶数都可以化为2^x*y

int prime[]={2,3,5,7,11,13,17,19,23,29,31};//多重判定的基底

ll read()
{
    ll res=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9')
    {
        if(c=='-') f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9')
    {
        res=res*10+c-'0';
        c=getchar();
    }
    return res*f;
}

ll qmul(ll x,ll y,ll mod)//快乘!!! 高精度的直接乘法会报错
{
    return (x*y-(ll)(x/(long double )mod*y+1e-3)*mod+mod)%mod;
}

ll qpow(ll a,ll b,ll mod)//快速幂
{
    ll res=1;
    while(b)
    {
        if(b&1) res=qmul(res,a,mod);
        a=qmul(a,a,mod);
        b>>=1;
    }
    return res;
}

bool Miller_Robbin(ll x)
{
    if(x<2) return 0;
    if(x!=2&&x%2==0) return 0;
    ll s=x-1;//x一定为奇数，-1化为就成为了偶数
    while(!(s&1)) s>>=1;  //不断除2，找到2^x*y中的y，在此基础上再不断平方
    for(int i=0;i<=10;i++)
    {
        if(x==prime[i]) return 1    ;
        ll t=s,m=qpow(prime[i],s,x);
        while(t!=x-1&&m!=1&&m!=x-1)
        {
            m=qmul(m,m,x);//m不断的平方，t的最大限制是x-1，如果期间m==1||m==x-1则退出
            t<<=1;
        }
        if(m!=x-1&&!(t&1)) return 0;
    }
    return 1;
}
