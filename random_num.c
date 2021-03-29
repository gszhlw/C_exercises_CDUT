//
// Created by 张力文 on 2021/3/20.
//

//随机数============================================================== 

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

static unsigned  int randseed;//seed

int main(void)
{
    unsigned  int r;
    int ans = 0;
    srand(time(0));
    randseed = (unsigned int) time(NULL);

    ans = rand() % 20 + 2;
    printf("num = %d\n", ans);
    return 0;
}
