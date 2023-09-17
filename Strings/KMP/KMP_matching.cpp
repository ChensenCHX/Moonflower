#include <iostream>
#include <vector>
#include <string>

//你说得对 但是STL确实香.jpg
using namespace std;

/// @brief 根据模式串生成相应的跳转vector表
/// @param pattern 存储模式串的字符串
/// @return 存储错配时跳转到模式串的目标位置
vector<int> GetPrefixList(string pattern){
    int n = pattern.length();
    vector<int> Pi(n);

    int j;
    //用于存储正在比较的位置

    for(int i = 1; i < n; i++){
        //从模式串的第二项开始构建 因为第一项不可能有真前后缀
        
        j = Pi[i-1];
        //Pi的每项至多比上一项增大1 因而j的最大值就是Pi[i-1] (位置值是长度值的-1)
        //但这么写这里初值会出现比较pattern[1]与pattern[1] 因而将+1后置
        //所以直接使用pattern[Pi[i-1]]开始筛选

        while(j > 0 && pattern[j] != pattern[i]) j = Pi[j-1];
        //第一个条件j > 0:  j若筛到0则无需再筛  退出循环
        //第二个条件pattern[j] != pattern[i]:   判定真前缀和真后缀最后一字是否相同 如相同则退出循环
        
        //如果第二个条件不满足 由前缀子串的性质可以知道
        //下一个最长的可能字串长度只能是Pi[j-1]    下例:
        //s0 s1 s2 s3 ... sn sn+1 sn+2 sn+3 中 s3与sn+3不匹配 此时假设Pi[i-1] == 2
        //j改为2 由于Pi[i-1] == 2 那么保证了 s0 s1 与 sn sn+1 的匹配情况 继续判别s2与sn+2是否匹配即可

        if (pattern[i] == pattern[j]) j++;
        //长度值是位置值的+1 因而在这里给j++

        Pi[i] = j;
    }

    return Pi;
}

/// @brief 进行匹配，返回含有匹配结果的vector<int>
/// @param text 目标串
/// @param pattern 模式串
/// @param spliter 分隔符 默认为#
/// @return 装有结果的vector<int> (注意这里返回的是偏移量)
vector<int> MatchString(string text, string pattern, char spliter = '#') {
    string cur = pattern + spliter + text;
    int sz1 = text.size(), sz2 = pattern.size();
    vector<int> v;
    vector<int> lps = GetPrefixList(cur);
    for (int i = sz2 + 1; i <= sz1 + sz2; i++) {
        if (lps[i] == sz2)
        v.push_back(i - 2 * sz2);
    }
    return v;
}

int main(){
    string txt, pat;
    cin>>txt>>pat;

    vector<int> ans = MatchString(txt, pat);
    if(ans.empty()) ans.push_back(-1);

    cout<<ans[0];

    return 0;
}