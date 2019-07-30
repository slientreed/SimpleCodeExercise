
//
//  Created by mark on 2019/7/30.
//  Copyright © 2019年 mark. All rights reserved.
//

/*
 八皇后问题：练习经典的回溯方法
 */


#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <cmath>
#include <string>
#include <assert.h>
#include <cstdio>
#include <fstream>
#include <map>
#include <set>
#include <deque>
#include <algorithm>
#include <list>

using namespace std;

#define max 16
int queen[max], sum = 0;

// 打印出皇后一个解法坐标
void printSolu()
{
    for(int i = 0; i < max; i++)     // 这里直接输出，因为肯定是每列都有一个皇后
        cout << "(" << i << "," << queen[i] << ")" " ";
    cout << endl;
    sum++;
}

// 检查当前列能否放置
bool place(int n)
{
    for(int i = 0; i < n; i++)   // 看当前横排和对角线可以否
    {
        if(queen[i] == queen[n] || abs(i - n ) == abs(queen[i] - queen[n]))
            return false;
    }
    
    return true;
}

// 回溯递归皇后位置，n为第n个
void nqueen(int n)
{
    for(int i = 0; i < max; i++)
    {
        queen[n] = i;       // 把皇后放到当前i循环位置
        if(place(n))
        {
            if(n == max - 1)
                printSolu();     // 到最后一列，找到一个解法
            else
                nqueen(n + 1);   // 继续递归后一列
        }
    }
}


int main()
{
    nqueen(0);
    cout << "一共解法：" << sum << endl;
    
    return 0;
}


