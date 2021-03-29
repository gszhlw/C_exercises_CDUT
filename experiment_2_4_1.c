//
// Created by 张力文 on 2021/3/20.
//

#include<stdio.h>

int is( int number );
void count_sum( int a, int b );


int is( int number )
{
    int ans = 0;
    int sum = 0;
    while(number)
    {
        int d = number % 10;
        sum += d;
        number /= 10;
    }

    if(sum == 5)
    {
        ans = 1;
    }
    else
        ans = 0;
    return ans;
}

void count_sum( int a, int b )
{
    int sum = 0;
    int count = 0;
    for(int i = a; i <= b; i++)
    {
        if(is(i))
        {
            count++;
            sum += i;
        }
    }
    printf("count = %d, sum = %d\n", count, sum);
    return;
}


