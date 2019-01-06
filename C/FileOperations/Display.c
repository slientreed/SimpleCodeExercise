#include <stdio.h>

int main(){
    
    char ch;
    FILE* fp = fopen("001.cpp", "r");
    if (fp == NULL) printf("Can not open file!\n");

    while(!feof(fp)){      //feof()函数用来检测流上的文件结束符，一般用来判断文件是否结束。
        putchar(ch);      //putchar()函数把ch字符输出到标准输出终端中
        fscanf(fp,"%c",&ch);   //从流中执行格式化输入；这里从fp中不断输出字符给ch
    }

    fclose(fp);

    return 0;
}
