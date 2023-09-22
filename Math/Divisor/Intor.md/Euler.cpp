//定义：φ(N)=(1-N)中与N互质的数的个数
//分解N=(p1^c1)*(p2^c2)*(p3^c3)*...(pk^ck)
//φ(N)=N*[(p1-1)/p1]*[(p2-1)/p2]*...[(pk-1)/pk]

//试除法
#include <math.h>
using namespace std;

int Euler(int x)
{
    int res=x;
    for(int i=2;i<=sqrt(x);i++)
    {
        if(x%i==0)
        {
            res=res/i*(i-1);
        }
        while(x%i==0) x/=i;
    }
    if(x>1) res=res/x*(x-1);
    return res;
    //一个合数的质因子最多仅有一个在sqrt(N)外
}

//线性筛求欧拉
//前置：
//1:设p为质数，若p|n，且p^2|n,
//φ(N)=φ(N/p)*p
//1：设p为质数，若p|n，且不p^2|n
//φ(N)=φ(N/p)*(p-1)

const int SIZE = 1000;

int book[SIZE];
int Eul[SIZE];
int su[SIZE];
int cnt = 0;

int Euler(int n){
    book[0]=book[1]=1;
    Eul[1]=1;
    for(int i=2;i<=n;i++)
    {
        if(!book[i])
        {
            su[++cnt]=i;
            Eul[i]=i-1;
        }
        for(int j=1;j<=cnt&&su[j]<=n/i;j++)
        {
            book[i*su[j]]=1;
            Eul[i*su[j]]=(i%su[j])?su[j]-1:su[j];
            Eul[i*su[j]]*=Eul[i];
            if(i%su[j]==0) break;
        }
    }
}

//姚岳宸附一版 STL
#include <vector>
const int MAXN = 100000;
bool isnp[MAXN];
vector<int> primes; // 质数表
void init(int n)
{
    for (int i = 2; i <= n; i++)
    {
        if (!isnp[i])
            primes.push_back(i);
        for (int p : primes)
        {
            if (p * i > n)
                break;
            isnp[p * i] = 1;
            if (i % p == 0)
                break;
        }
    }
}
