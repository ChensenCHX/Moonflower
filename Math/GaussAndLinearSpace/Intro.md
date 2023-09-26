# 一：高斯消元 (求解线性方程组)

## 1：对于常数运算
### 给定m个n元一次方程，求解x。

### 先用方程组中的所有系数与常数构建一个m*(n+1)的增广矩阵

$$
\begin{cases}
 \ X_{1} + 2X_{2}-X_{3}=-6\\
 \ 2X_{1} + X_{2}-3X_{3}=-9\\
 \ -X_{1}  -X_{2}+2X_{3}=-7
\end{cases} = 
 \left [
    \begin{array}{ccc|c}
    1 & 2 & -6 &-1\\
    2 & 1 & -3 & -9\\
    -1 & -2 & 2 & 7
    \end{array}
 \right]
 $$

### 枚举每一列i，枚举每一行j(j>i)，如果（j，i）有值，将其替换到第i行。并用它去消去其他行上i列的系数

### 代码前提：没有自由元
~~~

double a[N][N],b[N];
a为系数矩阵，b为常数

    for(int i=1;i<=n;i++)
    {
        for(int j=i;j<=n;j++)
        {
            if(fabs(a[j][i])>=1e-8)
            {
                for(int k=1;k<=n;k++) swap(a[j][k],a[i][k]);
                swap(b[i],b[j]);
                break;
            }
        }

        for(int j=1;j<=n;j++)
        {
            if(j==i) continue;
            double t=a[j][i]/a[i][i];
            for(int k=1;k<=n;k++) a[j][k]-=t*a[i][k];
            b[j]-=t*b[i];
        }
    }
~~~
 
### 有自由元：枚举的是第i列，pos是存放在第pow行，使非0行连续

~~~

double a[N][N],b[N];
a为系数矩阵，b为常数
for(int i=1,pos=1;i<=n;i++)
    {
        for(int j=i;j<=n;j++)
        {
            if(fabs(a[j][i])>=1e-8)
            {
                swap(a[j],a[pos]);
                swap(b[j],b[pos]);
                break;
            }
        }
        if(fabs(a[pos][i])<1e-3) continue;
        for(int j=1;j<=n;j++)
        {
            if(j==pos) continue;
            double t=a[j][i]/a[i][i];
            for(int k=1;k<=n;k++) a[j][k]-=t*a[i][k];
            b[j]-=t*b[i];
        }
        pos++;
    }
~~~

 ### 那么每一个x的值等于其所在行的常数除以x的系数
 ~~~
      for(int i=1;i<=n;i++)
     {
         double t=b[i]/a[i][i];
         if(fabs(t)<eps) t=0;//注意浮点数用eps判断是否为0
         cout<<fixed<<setprecision(3)<<t<<" ";
     }
~~~
 
### 如果方程等号两边存在0=0情况，表明方程有无穷多解

### 如果方程等号两边存在0=b情况，表明方程无解

 ## 2：异或运算

 ### 形如：
$$
\begin{cases} 
		a_{11}x_1&xor&a_{12}x_2&xor&\cdots&+a_{1n}x_n&=& src_1&xor&dst_1\\
        a_{21}x_1&xor&a_{22}x_2&xor&\cdots&+a_{2n}x_n&=& src_2&xor&dst_2\\
		&&&&\vdots\\
		a_{n1}x_1&xor&a_{n2}x_2&xor&\cdots&+a_{nn}x_n&=& src_n&xor&dst_n\\		
\end{cases}
$$

### 在记录上，每一行可以用一个整数代替，即

$$ t1=a_{11}*2^{n} +  a_{12}*2^{n-1}+\cdots+a_{11}*2^1+b_1*2^0
$$

### 枚举i行，枚举j(j>i)，每次找到最大值，与i进行替换，因为值越大说明第一个不为0的系数的数位越高。找到替换后第i行的第一个不为0的数位k，对其他所有行，如果第k位不为0则进行异或运算进行小消去

~~~
il void Gauss()
{
    for(int i=1;i<=n;i++)
    {
        for(int j=i+1;j<=n;j++)
        {
            if(a[j]>a[i]) swap(a[j],a[i]);
        }
        if(a[i]==1) //表示无解
        {
            return;
        }
        if(a[i]==0) //表示有n-i+1个自由元，即有pow(2,n-i+1)个解
        {
            res=pow(2,n-i+1);
            return;
        }
        int t;
        for(int j=n;j;j--)
        {
            if(a[i]&(1<<j))
            {
                t=j;
                break;
            }
        }
        for(int j=1;j<=n;j++)
        {
            if(i==j) continue;
            if(a[j]&(1<<t))
            {
                a[j]^=a[i];
            }
        }
    }
    res=1;
}
~~~

# 二：线性空间

## 概念：

### 1：线性相关：对于若干向量，若存在其中一个能被其他向量表出，则称这些向量线性相关，否则线性无关

### 2：基，维数：线性空间的一个极大线性无关子集，一个线性空间所有基包含的向量个数相等，其值为该空间的维数

### 3：秩：将所有向量做系数矩阵，进行消元，最后所得的非0向量数就是该线性空间的秩，这些向量为该空间的一个基

## 最大/小-基的求法：贪心

~~~
    for(int i=1,pos=1;i<=m;i++)
    {
        for(int j=pos+1;j<=n;j++)
        {
            if(fabs(a[j][i])>eps&&(fabs(a[pos][i])<eps||b[j]<b[pos]))
            {
                swap(a[pos],a[j]);
                swap(b[pos],b[j]);
            }
        }
    }
~~~