
//
//  Created by mark on 2019/9/3.
//  Copyright © 2019年 mark. All rights reserved.
//





#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <cmath>
#include <string>
#include <assert.h>
#include <algorithm>
#include <set>

using namespace std;


/*请完成下面这个函数，实现题目要求的功能
 当然，你也可以不按照下面这个模板来作答，完全按照自己的想法来 ^-^
 ******************************开始写代码******************************/
int LevenshteinDis(string str1, string str2)
{
    
    const int size1 = str1.size(),
    size2 = str2.size();
    if (size1 == 0)
        return size2;
    if (size2 == 0)
        return size1;
    
    // ed[i][j]表示 word1[0]~word1[i-1]与word2[0]~word2[j-1]之间的最小编辑距离
    vector<vector<int>> ed(size1 + 1, vector<int>(size2 + 1, 0));
    
    // 初始化任意字符与空字符之间的编辑距离
    for (int i = 0; i <= size1; i++)
    {
        ed[i][0] = i;
    }
    for (int i = 0; i <= size2; i++)
    {
        ed[0][i] = i;
    }
    
    for (int i = 1; i <= size1; i++)
    {
        for (int j = 1; j <= size2; j++)
        {
            if (str1[i - 1] == str2[j - 1])
                ed[i][j] = ed[i - 1][j - 1];
            else
                // 将3种编辑结尾的方法都尝试，取最小的结果
                ed[i][j] = min(min(ed[i][j - 1] + 1, ed[i - 1][j] + 1), ed[i - 1][j - 1] + 1);
        }
    }
    return ed[size1][size2];
}
/******************************结束写代码******************************/


int main() {
    int res;
    
    string _str1;
    getline(cin, _str1);
    string _str2;
    getline(cin, _str2);
    
    res = LevenshteinDis(_str1, _str2);
    cout << res << endl;
    
    return 0;
    
}


