
//
//  Created by mark on 2019/8/10.
//  Copyright © 2019年 mark. All rights reserved.
//


//题目：


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


bool IsSame(vector<int>v1, vector<int>v2)
{
    for(int i = 0; i < 3; i++)
    {
        
        for(vector<int>::iterator iter = v2.begin(); iter != v2.end(); iter++)
        {
            if(v1[i] == *iter)
            {
                //cout << *iter;
                v2.erase(iter);
                break;
            }
            //vector<int>::iterator iter = v2.begin();
        }
    }
    
    if(v2.size() == 0)
        return true;
    else
        return false;
}



int main() {
    
    int n;
    cin >> n;
    
    vector<vector<int>> slide(n);
    
    double temp;
    for(int i = 0; i < n; ++i)
    {
        double x1,y1,x2,y2,x3,y3;
        cin>>x1>>y1>>x2>>y2>>x3>>y3;
        
        temp = (pow((x1 - x2), 2) + pow((y1 - y2), 2));
        slide[i].push_back(temp);     // 压入一个边长
        temp = (pow((x1 - x3), 2) + pow((y1 - y3), 2));
        slide[i].push_back(temp);
        temp = (pow((x2 - x3), 2) + pow((y2 - y3), 2));
        slide[i].push_back(temp);
    }
    
    /*
    for(int i = 0; i < slide.size(); i++)
    {
        for(int j = 0; j < 3; j++)
            cout << slide[i][j];
        cout << endl;
    }
    cout << endl;
    */
    
    int count = 0;
    
    for(vector<vector<int>>::iterator iter1 = slide.begin(); iter1 != slide.end(); iter1++)
    {
        /*
        for(vector<int>::iterator it = (*iter1).begin(); it !=(*iter1).end(); it++)
            cout << *it;
        cout << endl;
        */
        
        vector<vector<int>>::iterator iter2 = (iter1 + 1);
        
        while( iter2 != slide.end())
        {
            /*
            for(vector<int>::iterator it = (*iter2).begin(); it !=(*iter2).end(); it++)
                cout << *it;
            cout << endl;
            */
            
            if(IsSame(*iter1, *iter2))
            {
                count++;
                slide.erase(iter2);
            }
            
            iter2++;
        }
    }
    
    cout << count << endl;
    
    return 0;
}
