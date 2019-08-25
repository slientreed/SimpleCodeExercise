
//
//  Created by mark on 2019/8/18.
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


// 参考：https://blog.csdn.net/NK_test/article/details/48912763



using namespace std;


// 大数相加：使用字符串每位运算，主要是要注意进位
string BigAdd(string num1, string num2)
{
    string res = "";
    
    int m = num1.size();
    int n = num2.size();
    
    int len = max(m,n);
    
    vector<int> temp(len + 1);   // 两个数相加，长度为大数+1
    
    int carry = 0;
    while(m >= 1 && n >= 1)
    {
        int a = num1[m - 1] - '0';
        int b = num2[n - 1] - '0';
        temp[len--] = (a + b + carry) % 10;
        carry = (a + b + carry) / 10;
        --m;
        --n;
    }
    while(m >= 1)
    {
        int a = num1[m - 1] - '0';
        temp[len--] = (a + carry) % 10;
        carry = (a + carry) / 10;
        m--;
    }
    while(n >= 1)
    {
        int b = num2[n - 1] - '0';
        temp[len--] = (b + carry) % 10;
        carry = (b + carry) / 10;
        n--;
    }

    // 把结果存入返回值中
    vector<int>::iterator iter = temp.begin();
    if(*iter == 0)          // 去掉第一个为0的字符
        temp.erase(iter);
    
    for(auto a : temp)
    {
        res = res + to_string(a);
    }

    return res;
}



// 大数相减：主要要考虑借位和负数问题
string BigSub(string num1, string num2)
{
    string res = "";
    stack<int> s;
    vector<int> temp_s;
    
    int m = num1.size();
    int n = num2.size();
    //cout << m << " " << n << endl;
    string max_num = num1;
    string min_num = num2;
    if(m < n || (m == n && (num1[0] - '0') < (num2[0] - '0')) )   // 保证符号位，且保证是大数减小数
    {
        max_num = num2;
        min_num = num1;
        res += '-';
        m = max_num.size();
        n = min_num.size();
    }
    
    //cout << m << " " << n << endl;
    //cout << max_num << endl;
    
    int carry = 0,temp;
    while(n >= 1)
    {
        int a = max_num[m - 1] - '0' - carry;
        int b = min_num[n - 1] - '0';
        if(a < b)
            carry = 1;
        
        temp = (10 * carry + a) - b;
        s.push(temp);
        --n;
        --m;
    }
    while(m >= 1)
    {
        int a = max_num[m - 1] - '0';
        temp = (a - carry);
        s.push(temp);
        carry = 0;
        --m;
    }
    
    
    // 从栈中正序
    while (!s.empty()) {
        temp_s.push_back(s.top());
        s.pop();
    }
    
    
    // 把结果存入返回值中
    vector<int>::iterator iter = temp_s.begin();
    if(*iter == 0)          // 去掉第一个为0的字符
        temp_s.erase(iter);
    
    for(auto a : temp_s)
    {
        res = res + to_string(a);
    }

    
    return res;
}




// 大数相乘函数。对应位相乘，最后处理进位
string BigMultiple(string num1, string num2)
{
    string res = "";
    
    int m = num1.size();
    int n = num2.size();
    
    vector<int> temp(m + n - 1);     // 结果至少是m + n - 1位
    
    // 对每一位进行乘积运算
    for(int i = 0; i < m; ++i)
    {
        int a = num1[i] - '0';
        for(int j = 0; j < n; ++j)
        {
            int b = num2[j] - '0';
            temp[i + j] += a * b;
        }
    }
    
    // 对每一位进行处理
    int carry = 0;
    for(int i = temp.size() - 1; i >= 0; --i)
    {
        int t = temp[i] + carry;
        temp[i] = t % 10;
        carry = t / 10;
    }
    
    
    // 遍历完还有进位
    while(carry != 0)
    {
        int t = carry % 10;
        carry /= 10;
        temp.insert(temp.begin(), t);     // 往某一位插入
    }
    
    
    // 把结果存入返回值中
    for(auto a : temp)
    {
        res = res + to_string(a);
    }
    
    if(res.size() > 0 && res[0] == '0')
        return "0";
    
    return res;
    
}



// 比较str1是否大于str2，是返回0；否则返回1
int strComp(string &str1, string &str2)
{
    int len1 = str1.length();
    int len2 = str2.length();
    
    if(len1 > len2)
        return 0;
    else if(len1 < len2)
        return 1;
    else
    {
        if(str1[0] - '0' >= str2[0] - '0')
            return 0;
        else
            return 1;
    }
}



// 大数相除；
// 除法看作是减法来处理，用被减数不断的减去减数，记录减的次数即是商的值；记录被减数和减数的位数之差len，将减数扩大10的len倍。然后依次去减，一旦被减数小于减数时，将减数减小10倍，直至到原值.
string BigDivide(string num1, string num2)
{
    
    int m = num1.length();
    int n = num2.length();
    int dis = m - n;
    stack<int> s;
    vector<int> temp_int;
    
    for(int i = 0; i < dis; ++i)   // 把减数s2从后添加0，添加到和被减数一样
        num2 += '0';
    string res = "";
    
    while(dis >= 0)
    {
        int sum = 0;
        string temp ;
        
        while((temp = BigSub(num1, num2))[0] != '-')         // 添加长度后的减数和被减数做减法，依次从最高位往后得结果
        {
            //temp = BigSub(num1, num2);
            sum++;
            num1 = temp;                                    // 更新被除数
            
        }
        
        //if(num2.length() >= n && num2[0] != '0')
        //s.push(sum);     // 依次存放高位除法之后的结果
        temp_int.push_back(sum);
        dis--;
        num2 = num2.substr(0, n + dis);   // 截取一段长度，参数是起止位置。相当于从末尾去掉一个0
    }
    
    
    
    vector<int>::iterator iter = temp_int.begin();  // 去除向量第一个非0元素前的0元素
    while(iter != temp_int.end())
    {
        if(*iter == 0)
            temp_int.erase(iter);
        else
            break;
    }
    
    //reverse(temp_int.begin(), temp_int.end());
    // 把结果存入返回值中
    for(auto a : temp_int)
    {
        res = res + to_string(a);
    }

    return res;
}




int main(){
    
    string num1, num2;
    cin>>num1>>num2;
    string res_mul = BigMultiple(num1, num2);
    string res_add = BigAdd(num1, num2);
    string res_sub = BigSub(num1, num2);
    string res_div = BigDivide(num1, num2);
    
    cout << "相加：" << res_add << endl;
    cout << "相减：" << res_sub << endl;
    cout << "相乘：" << res_mul << endl;
    cout << "相除：" << res_div << endl;
    
    
    return 0;
    
}
    

