#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int read();
int n;
//试除法求单点约数集合 



void solve()
{
    n=read();
    vector<int> vt;
    for(int i=1;i<=n/i;i++)
    {
        if(n%i==0)
        {
            vt.push_back(i);
            if(n/i!=i) vt.push_back(n/i);
        }
    }
    sort(vt.begin(),vt.end());
    for(auto it:vt) cout<<it<<" ";
    cout<<endl;
}

//倍数法
const int N = 10000; 
void slove(){
    vector<int> vt[N];
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n/i;j++)
        {
            int t=i*j;
            vt[t].push_back(i);
        }
    }
    for(int i=1;i<=n;i++)
    {
        for(auto it:vt[i]) cout<<it<<" ";
        cout<<endl;
    }
}