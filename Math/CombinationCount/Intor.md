# 组合计数

## 一：概念

### 1：排列数：
$$ A_n^m=\frac{n!}{(n-m)!} $$

### 2:组合数：
$$ C_n^m=\frac{n!}{(n-m)!*m！} $$

### 性质：
$$ 1:C_n^m=C_n^{n-m}\\
2:C_n^m=C_{n-1}^m+C_{n-1}^{m-1}\\
3：C_n^0+C_n^1+\dots+C_n^n=2^n
$$

### 组合数求法

#### 1：运用性质2递推求得

#### 2：预处理出（1到n！）mod p的每一个值及其逆元，快速求解

#### 3：若要高精度计算，避免除法，则分解质因数，指数相减

## 二：多重集

$$ S=[n_1*a_1,n_2*a_2,\dots n_ka_k]
$$


### 1：排列数
 
$$ \frac{n!}{n_1!n_2!\dots n_k!} $$

### 2:组合数：从中取r个

$$ C_{k+r-1}^{k-1} $$

## 三：Lucas

### 若p是质数，则对任意1<=m<=n，有

$$ C_n^m≡C_{n mod p}^{m mod p}*C_{n/p}^{m/p}(mod p)$$

## 四：Catalan 

$$ Cat_n=\frac{C_{2n}^n}{n+1}=C_{2n}^n-C_{2n}^{n-1}$$

## 五：Mobius:

### 对正整数N分解质因数

$$
N=p_1^{c_1} p_2^{c_2}\dots p_m^{c_m}  
\\μ(N)=\begin{cases}
\ 0 & ∃i∈[1,m],c_i>1
\\ 1& m≡0(mod2),∀i∈[1,m],c_i=1
\\ 1& m≡1(mod2),∀i∈[1,m],c_i=1
\end{cases}
$$

### Mobius的筛法：
~~~

int u[N],book[N],su[N],idx;
void ini()
{
    book[0]=book[1]=1;
    u[1]=1;
    for(int i=2;i<=50000;i++)
    {
        if(!book[i])
        {
            su[++idx]=i;
            u[i]=-1;
        }
        for(int j=1;j<=idx&&su[j]<=50000/i;j++)
        {
            book[su[j]*i]=1;
            if(i%su[j]==0)
            {
                u[su[j]*i]=0;
                break;
            }
            else u[su[j]*i]=u[su[j]]*u[i];
        }
    }
}
~~~

### 用途：求范围内互质对的个数

对于给出的n个询问，每次求有多少个数对(x,y)，满足a≤x≤b，c≤y≤d，且gcd(x,y) = k，gcd(x,y)函数为x和y的最大公约数。

gcd(x,y)==k,表面x，y都是k的倍数。转化一下即为求：
$$ \frac{a}{k} <=x<= \frac {b}{k}\\
\frac{c}{k} <=y<= \frac {d}{k}\\
$$
下，x,y互质对的个数

设D[a,b,k]为x<=a,y<=b下最大公约数为k的对数。显然x,y都是k的倍数，1~a间k的倍数有[a/k]个，1~b间有[b/k]个。所以共有

$$ D[a,b,k]=[a/k]*[b/k]$$

由容斥原理：

$$ F[a,b]=\sum_{i=1}^{min(a,b)}{u(i)*D[a,b,i]}
$$

根据除法分块：
$$ 
∀i∈[x,min([a/[a/x]],b/[b/x]])]\\
D[a,b,i]=[a/i][b/i]的值都相等
$$

预处理mobius的前缀和，实现跳跃
~~~

    for(int i=2;i<=50000;i++) u[i]+=u[i-1];
~~~

~~~
    int r=min(a,b);
    for(int i=1,t;i<=r;i=t+1)
    {
         t=min(a/(a/i),b/(b/i));
         res+=(u[t]-u[i-1])*(a/i)*(b/i);
    }

~~~

### 对于样例所示，多种限制的，容斥即可