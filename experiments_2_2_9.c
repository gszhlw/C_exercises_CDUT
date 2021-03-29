//
// Created by 张力文 on 2021/3/20.
//

#include<stdio.h>
int main(void)
{
    //用小时、分钟分别相减，然后输出
    int h1 = 0;
    int h2 = 0;
    int hh1 = 0;
    int hh2 = 0;
    int mm1 = 0;
    int mm2 = 0;
    int mm = 0;
    int hh = 0;
    if(scanf("%d %d", &h1, &h2))
    //需要把输入分解成每两位
    {
        hh1 = h1 / 100; //1201 / 100 = 12
        hh2 = h2 / 100;

        mm1 = h1 % 100; //1201 % 100 = 01
        mm2 = h2 % 100;
    }



    //分钟需要处理借位的情况
    if(mm2 >= mm1)
    {
        mm = mm2 - mm1;
        hh = hh2 - hh1;
    }
    else{
        mm = mm2 - mm1 + 60;
        hh = hh2 - hh1 - 1; // 1502 1230
    }

    printf("%02d:%02d", hh, mm);
    return 0;
}

//#include<stdio.h>
//int main()
//{
//    int a,b,m,n,p,q;
//    scanf("%2d%2d %2d%2d",&a,&b,&m,&n);
//    if(n >= b)
//    {
//        p = m-a;
//        q = n-b;
//    }
//    else
//    {
//        p=m - a - 1;//p = m - 1 - a的时候，在输入0000 2400时，m = 24 a = 00 n = 00 b = 00 p = 23
//        q=n - b + 60 ;
//    }
//    printf("%02d:%02d",p,q);
//    return 0;
//}
//
