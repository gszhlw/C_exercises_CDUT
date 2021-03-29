//
// Created by 张力文 on 2020/10/3.
//
#include<stdio.h>
#include<stdlib.h>

char player[][10];
//int flag = 0;
void initiatioin_connect()
{
/*
 * print “Setting up the game”. Ask each player their name.初始化：打印“设置游戏”。询问游戏者姓名。
 */
printf("Setting up thee game.\nplease input your name:\n");
scanf("%s", player[0]);
printf("please input your name:\n");
scanf("%s", player[1]);
return;
}

void Teardown()
{
    //print “Destroying the game”	打印“销毁游戏”
    //只有在main函数中才能调用该函数
    printf("Desdroying the game.\n");
    exit(0);
}

char accept_input_connect(void)
{
    /*
     * ---获取有效输入---
     * 接受输入
     * Accept Input – accept a letter for which column of the game we are going to drop a disc into.
     * Valid letters are A-G (7 columns). You should designate a letter for “Quit the game”.
     * Input must be returned from this function.
     * 接受一个字母作为游戏中我们将要把棋子置入那一列的输入。有效字母在A-G之间。你应该定义一个字母作为退出。输入必须作为函数返回值。
     */
    printf("");
}
int main(void)
{
    //initiatioin_connect();
    //Teardown();
    //while循环去控制gameloop 自顶向下 逐步细化
    //用二维数组去实现棋盘中的具体逻辑
    return 0;
}
