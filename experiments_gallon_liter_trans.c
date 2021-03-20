//
// Created by 张力文 on 2021/3/20.
//
#include <stdio.h>
#define G_to_L 3.785
#define M_to_K 1.609

int main(void)
{
    float miles, gallons = 0.0;
    float miles_per_gallon = 0.0;
    float liter_per_100km = 0.0;
    float km_per_liters = 0.0;
    printf("请输入英里数:\n");
    scanf("%f", &miles);
    printf("请输入加仑数:\n");
    scanf("%f", &gallons);
    miles_per_gallon = miles / gallons;
    printf("每加仑可以行使 %.1f 英里\n", miles_per_gallon);

    liter_per_100km = gallons * G_to_L / (miles * M_to_K) * 100;
    //km_per_liters = miles_per_gallon * M_to_K / G_to_L;
    printf("每100公里行驶所需要的升数：%.1f\n",liter_per_100km);
    //printf("Europe: %.1f\n", km_per_liters);
    return 0;
}