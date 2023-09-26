# Baby Step,Giant Step

## 求解a^x≡b(mod p)
## 一：若a,p互质，则a^(i-j)可以写成a^i\*a^(-j),又令t=sqrt(p),那么[0,p)的所有数都可以用i*t-j来表示，其中i,j∈[1,t],那么a^x≡b(mod p)-->a^(i*t-j)≡b(mod p)-->a^(i*t)≡b*a^j(mod p)

### 枚举b*a^j(mod p)，用哈希记录，！！！如果以出现则还要重新标记，以使j最大化，答案最小化

### 再枚举a^(i*t)(mod p)看答案是否出现过

## 二：若a,p不互质，原式可以写成a^x+p*y=b
### 知识：若两数不互质，则不断的除以最大公约数终会互质

### 所以式子不断除以an=gcd(a,(p/a1/a2...))（若在循环当中an还不为1但b已经无法整除an则判断无解）
### 最终形式为a^(x-n)*a^n/(a1*a2...an)+p/(a1*a2...an)*y=b/(a1*a2...an)

### 即a^(x-n)*a^n/(a1*a2...an)≡b/(a1*a2...an)(mod p/(a1*a2...an))

### 即a^(x-n)*a’≡b’(mod p’)

### 后续步骤同一
### 若a与p不互质-----------------
### 默认x>n，枚举判断x<n是否有解

```
inline bool check(ll &res)
{
    ll k=1%p;
    for(int i=0;i<=40;i++)
    {
        if(k==b)
        {
            res=i;
            return 1;
        }
        k=1ll*k*a%p;
    }
    return 0;
}

inline long long qpow(ll a,ll b,ll p)
{
    ll res=1;
    while(b)
    {
        if(b&1) res=1ll*res*a%p;
        a=1ll*a*a%p;
        b>>=1;
    }
    return res;
}

inline ll ex_gcd(ll a,ll b,ll &x,ll &y)
{
    if(!b)
    {
        x=1,y=0;
        return a;
    }
    ll t=ex_gcd(b,a%b,x,y);
    ll z=x;
    x=y,y=z-y*(a/b);
    return t;
}

// 解线性同余方程最小正整数解
inline ll solve_equ(ll a,ll b,ll c)
{
    ll x,y;
    ll d=ex_gcd(a,b,x,y);
    if(c%d!=0) return -1;//先判断再除
    ll mod=b/d;
    return (1ll*x*(c/d)%mod+mod)%mod;
}

inline bool ex_bsgs(ll &res)
{
    a%=p,b%=p;
    //不断除gcd(a,p)使a,p互质---------
    if(!a) return 0;
    if(check(res)) return 1;
    ll idx=0,d=0,x,y;
    a1=1;
    while((d=ex_gcd(a,p,x,y))!=1)
    {
        idx++;
        a1=1ll*a1*(a/d)%p;
        p/=d;
        /*
        如果a,p还没有互质，但b已经整除
        不了d时判断无解
        */
        if(b%d)
        {
            return 0;
        }
        b/=d;
    }
    //a,p互质--------------------
    b=1ll*b*solve_equ(a1,p,1)%p;
    mp.clear();
    ll t=ceil(sqrt(p));
    ll tmp=b;
    for(int i=1;i<=t;i++)
    {
        tmp=1ll*tmp*a%p;
        mp[tmp]=i;
    }
    ll pw=qpow(a,t,p);
    tmp=pw;
    for(int i=1;i<=t;i++)
    {
        if(mp.find(tmp)!=mp.end())
        {
            res=i*t-mp[tmp]+idx;
            return 1;
        }
        tmp=1ll*tmp*pw%p;
    }
    return 0;

}


```
