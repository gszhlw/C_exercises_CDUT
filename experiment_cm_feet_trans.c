//
// Created by 张力文 on 2021/3/20.
//

/**
 * 1 英尺=30.48 厘米
 * 1 英寸=2.54 厘米
 */
#define cm_to_feet 30.48
#define cm_to_inches 2.54
#include<stdio.h>
int main(void)
{
    double height_centimeter = 0;
    int feet = 0;
    double inches = 0.0;

    printf("Enter a height in centimeters:");
    scanf("%lf", &height_centimeter);
    feet = (int)(height_centimeter / cm_to_feet);
    inches = (height_centimeter - feet * cm_to_feet) / cm_to_inches;
    printf("%.1lf cm = %d feet, %.1lf inches.\n", height_centimeter, feet, inches);
    while(height_centimeter > 0)
    {
        printf("Enter a height in centimeters(<=0 to quit):");
        scanf("%lf", &height_centimeter);
        if(height_centimeter <= 0)
        {
            printf("bye\n");
            break;
        }
        feet = (int)(height_centimeter / cm_to_feet);
        inches = (height_centimeter - feet * cm_to_feet) / cm_to_inches;

        printf("%.1lf cm = %d feet, %.1lf inches.\n", height_centimeter, feet, inches);

    }

    return 0;
}