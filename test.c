






//#include<stdio.h>
//int main(void)
//{
//    FILE *fp = fopen("test.txt", "w");
//    if(fp == NULL)
//    {
//        printf("write error!\n");
//    }
//
//    for(int i = 0; i < 3; i++)
//    {
//        fprintf(fp, "%d", i);
//        fclose(fp);
//    }
//
//    int num[3] = {0};
//
//    FILE *fp_read = fopen("test.txt","r");
//
//    if(fp_read == NULL)
//    {
//        printf("read error!\n");
//    }
//
//    for(int i = 0; i < 3; i++)
//    {
//        fscanf(fp_read, "%d ", num[i]);
//        printf("%d ", num[i]);
//    }
//
//    getchar();
//
//    return 0;
//}

//#include <stdio.h>
//
//#include <stdio.h>
//
//int main()
//{
//    FILE *fp = NULL;
//
//    fp = fopen("test.txt", "w+");
//    fprintf(fp, "This is testing for fprintf...123\n");
//    fputs("This is testing for fputs...456\n", fp);
//    fclose(fp);
//}
//#include "stdio.h"
//#include "string.h"
//void main()
//{
//    char a[6]="china";
//    char temp[1024];
//    int n=0;//记录有多少个china
//    FILE *outFile=fopen("b.txt","r+");
//    FILE *inFile=fopen("a.txt","r+");
//    while(fgets(temp,500,inFile)!=NULL)
//    {
//        int k=0;
//        for(int i=0;i<strlen(temp);i++)
//        {
//            if(temp[i]==a[k] && k<strlen(a))
//            {
//                k++;
//            }
//            else
//            {
//                if(k==strlen(a))
//                {
//                    n++;
//                    fprintf(outFile,"%s",a);
//                }
//                k=0;
//            }
//        }
//    }
//}


#include <stdio.h>

int main()
{
    FILE *fp = NULL;

    fp = fopen("/Users/zlw/Downloads/test.txt", "w+");
    fprintf(fp, "This is testing for fprintf...\n");
    fputs("This is testing for fputs...\n", fp);
    fclose(fp);
}