//
// Created by 张力文 on 2021/3/15.
//

//计算多孔体积的平均值
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
double  LogNormFun(double C, double X, double Mu, double Sigma2);
double amod(double a, double b)
{
    int k = (int)(a / b);
    double r = a - k * b;
    return r;
}

//iNumbers = 25 观测到的圈闭的孔隙值
//jNumbers  = 40 观测到的圈闭的厚度值
//i1Numbers  = 45统计得到的孔隙间隔值
//j1Numbers  = 96统计的到的厚度间隔值
//i1Numbers1  = 46 对于孔隙每个统计间隔的终值
//j1Numbers1  = 97 对于厚度每个统计间隔的终值
//kSamp = 2000随机取样数

const int iNumbers = 25, jNumbers=40, i1Numbers=45,j1Numbers=96,i1Numbers1=i1Numbers+1,j1Numbers1 = j1Numbers+1, kSamp = 2000;
//c   FiPoros --- porosity of a trap, fraction 圈闭的孔隙度，分数
//c   Hthick --- thickness of a trap, unit: m 圈闭的厚度，米

//孔隙度fi的测量值，25个
double FiPoros[iNumbers] = {0.21,0.23,0.255,0.26,0.27,
             0.28,0.29,0.305,0.31,0.315,
            0.32,0.325,0.33,0.335,0.34,
            0.345,0.348,0.355,0.36,0.37,
             0.38,0.39,0.42,0.43,0.44};

//厚度H的测量值，40个
int Hthick[jNumbers] = {15,26,28,31,33,
            35,37,42,43,44,
            45,46,47,50,51,
            52,53,54,55,56,
            57,58,59,62,63,
            64,65,66,67,68,
            73,74,75,76,77,
            84,85,86,95,96};
//dimension FiPoros(iNumbers),Hthick(jNumbers)
//c   FiPorosLn --- ln(FiPoros)
//c   HthickLn --- ln(Hthick)
//dimension FiPorosLn(iNumbers),HthickLn(jNumbers)

int main(void)
{

    double FiPorosLn[iNumbers];
    double HthickLn[jNumbers];

    //对孔隙度取对数
    for (int i = 0; i < iNumbers; i++) {
        FiPorosLn[i] = log(FiPoros[i]);
        //printf("%lf ", FiPorosLn[i]);
    }

    for (int j = 0; j < jNumbers; j++) {
        HthickLn[j] = log(Hthick[j]);
        //printf("%lf ", HthickLn[j]);
    }

//c   FiPorosStar --- terminal values of each statistical interval
//c                   for porosity, fraction 孔隙度、分数的每个统计间隔的终端值
//        c   HthickStar --- terminal values of each statistical interval
//c                  for thickness, unit: m
//dimension FiPorosStar(i1Numbers1),HthickStar(j1Numbers1)
    double FiPorosStar[i1Numbers1];
    double HthickStar[j1Numbers1];



//c   FiPorosMid --- middle point values of each statistical interval 每个孔隙统计间隔的中点值，分数
//        c                  for porosity, fraction
//        c   HthickMid --- middle point values of each statistical interval
//        c                 for thickness, unit: m
//        dimension FiPorosMid(i1Numbers),HthickMid(j1Numbers)

    double FiPorosMid[i1Numbers];
    double HthickMid[j1Numbers];
//c   ProDisFporos --- probability distribution values for porosity 每个统计区间孔隙度的概率分布值
//        c                    on each statistical interval
//c   ProDisFthick --- probability distribution values for thickness 每个统计区间厚度的概率分布值
//        c                    on each statistical interval
//dimension ProDisFporos(i1Numbers),ProDisFthick(j1Numbers)
    double ProDisFporos[i1Numbers];
    double ProDisFthick[j1Numbers];
//c   PsRANDOM --- pseudo random number 伪随机数
//        c   Vfi --- porous volumes for a trap respecting the pseudo random 陷阱的多孔体积，根据伪随机数
//c           number, unit: m^3
//dimension PsRANDOM(kSamp),Vfi(kSamp)
    double PsRANDOM[kSamp];
    double Vfi[kSamp];
//c   MuPoros --- Mu of of the lognormal distribution function 孔隙度对数正态分布函数的Mu
//        c               for porosity
//        c   MuThick --- Mu of of the lognormal distribution function
//        c               for thickness
    double MuPoros, MuThick;

//        c   Sarea --- area of a trap, unit: km^2
//data Sarea/1.0/
    double Sarea = 1.0;//圈闭的面积，单位为km^2

//c   FiPoros --- porosity of a trap, fraction
//c   Hthick --- thickness of a trap, unit: m

//c   VminFi --- minimum of the FiPorosStar, fraction
//c   VminH --- minimum of the HthickStar, unit: m

    double VminFi = 0.0;
    double VminH = 0.0;
    double VintervalFi = 0.01;
    double VintervalH = 1.0;


//计算孔隙体积的平均值
    double sum1 = 0.0;//sum1为孔隙体积的平均值
    for (int i = 0; i < iNumbers; i++) {
        sum1 = sum1 + FiPoros[i];
        sum1 = sum1 / iNumbers;

    }


//do j=1,jNumbers
//sum2=sum2+Hthick(j)
//enddo
//        sum2=sum2/jNumbers
    double sum2 = 0.0;
    for (int j = 0; j < jNumbers; j++)
    {
        sum2 = sum2 + Hthick[j];
        sum2 = sum2 / jNumbers;
    }

//Volfi=1E6*sum1*sum2*Sarea
    double Volfi;
    Volfi = pow(10, 6) * sum1 * sum2 * Sarea;


//c     open the print file PorVolTrap.PRT 从PorVolTrap.PRT打开打印文件
//以下是读写PorVolTrap.PRT文件操作，并向该文件写入一开始的变量名称等
    printf("$$$$ Program PorVolTrap begins to run $$$$\n");
    printf("  average of FiPoros: %14.6E\n", sum1);
    printf("  average of Hthick: %14.6E\n", sum2);
    printf("  average of Vfi: %14.6E", Volfi);
    FiPorosStar[1] = VminFi;
    for (int i1 = 0; i1 < i1Numbers; i1++) {
        FiPorosStar[i1 + 1] = FiPorosStar[i1] + VintervalFi;
    }


//厚度统计间隔的生成
//c  1(b): generation of the statistical interval for thickness
//HthickStar(1)=VminH
//        DO 30 j1=1,j1Numbers
//HthickStar(j1+1)=HthickStar(j1)+VintervalH
//30   continue

    for (int j1 = 0; j1 < j1Numbers; j1++) {
        HthickStar[j1 + 1] = HthickStar[j1] + VintervalH;
    }


//孔隙度每个统计间隔的中间点值的生成
//c  1(c): generation of the middle point values of each statistical
//        c        interval for porosity
//        DO 40 i1=1,i1Numbers
//FiPorosMid(i1)=FiPorosStar(i1)+
//               1                (FiPorosStar(i1+1)-FiPorosStar(i1))/2.
//40   continue
//FiPorosMid 每个孔隙统计间隔的中点值
    for (int i1 = 0; i1 < i1Numbers; i1++) {
        FiPorosMid[i1] = FiPorosStar[i1] + ((FiPorosStar[i1 + 1] - FiPorosStar[i1]) / 2.0);
    }


//生成厚度的每个统计间隔的中间点值
//c  1(d):  generation of the middle point values of each statistical
//        c        interval for thickness
//        DO 50 j1=1,j1Numbers
//HthickMid(j1)=HthickStar(j1)+
//              1                (HthickStar(j1+1)-HthickStar(j1))/2.
//50   continue

    for (int j1 = 0; j1 < j1Numbers; j1++) {
        HthickMid[j1] = HthickStar[j1] + ((HthickStar[j1 + 1] - HthickStar[j1]) / 2.0);
    }


//孔隙度对数正态分布函数的Mu和Sigma的计算
//c  2-1(a): calculation of Mu and Sigma of the lognormal distribution
//        c          function for porosity
    MuPoros = 0.0;
//DO 100 i=1,iNumbers
//FiPorosLn(i)=ALOG(FiPoros(i))
//MuPoros=MuPoros+FiPorosLn(i)
//100  continue
//MuPoros=MuPoros/iNumbers
//
    for (int i = 0; i < iNumbers; i++)
    {
        FiPorosLn[i] = log(FiPoros[i]);
        MuPoros = MuPoros + FiPorosLn[i];

    }
     MuPoros = MuPoros / iNumbers; 

    double SigmaPoros = 0.0;
    double SigmaPoros2;
//DO 120 i=1,iNumbers
//SigmaPoros=SigmaPoros+ABS(FiPorosLn(i)-MuPoros)
//120  continue
//SigmaPoros2 = SigmaPoros/(iNumbers-1);
//SigmaPoros=SQRT(SigmaPoros2)

    for (int i = 0; i < iNumbers; i++)
    {
        SigmaPoros = SigmaPoros + fabs(FiPorosLn[i] - MuPoros);
    }

    SigmaPoros2 = SigmaPoros / (iNumbers - 1);
    SigmaPoros = sqrt(SigmaPoros2);

//打印孔隙的对数正态分布函数的Mu和西格玛
//c  2-1(b): print Mu and Sigma of the lognormal distribution function
//        c          for porosity
//write(7,150) MuPoros,SigmaPoros
//150  format(/1X,'for porosity, ','Mu=',E12.4,'; Sigma=',E12.4)
//fprintf(fp, "for porosity, Mu= %E; Sigma= %E\n", MuPoros, SigmaPoros);
    printf("for porosity, Mu= %12.4E; Sigma= %12.4E\n", MuPoros, SigmaPoros);

//计算孔隙的累积频数分布
//c  2-1(c): calculation of cumulative frequency distribution
//        c          for porosity, which is considered as the probability
//c          distribution function 看作概率分布函数
//write(7,200)
//200  format(/1X,'interval No.',2X,'mid. of interval',2X,
//1           'probability dis. func. value')
//fprintf("fp, interval No.  mid. of interval  probability dis. func. value\n")
    printf("interval No.  mid. of interval  probability dis. func. value\n");

//SUM=0.
//constant=1.0/(SQRT(2.*3.1416)*SigmaPoros)
//DO 220 i1=i1Numbers,1,-1
//DO index=istart,iend,iner   ! 分别代表初值、结束值、步长值（可正可负）
//DeltaFi=VintervalFi/2.
//FiMiddle=FiPorosStar(i1)+DeltaFi
    double sum = 0.0;
    double constant_num = 1.0 / (sqrt(2.0 * 3.1416) * SigmaPoros);
    double DeltaFi;
    double FiMiddle;
    for (int i1 = i1Numbers; i1 >= 1; i1--)
    {
        DeltaFi = VintervalFi / 2.0;
        FiMiddle = FiPorosStar[i1] + DeltaFi;



//孔隙度对数正态分布函数的计算
//c  calculation of the lognormal distribution function for porosity
//        CALL LogNormFun(constant,FiMiddle,MuPoros,SigmaPoros,y)
        double y = LogNormFun(constant_num, FiMiddle, MuPoros, SigmaPoros);
//SUM=SUM+y*VintervalFi
        sum = sum + y * VintervalFi;
//if (SUM.LE.1.) then
//ProDisFporos(i1)=SUM
//else
//ProDisFporos(i1)=1.
//endif
//220  continue
        if (sum <= 1.0) {
            ProDisFporos[i1] = sum;
        } else {
            ProDisFporos[i1] = 1;
        }
    }

//c  2-1(d): print the probability distribution function for porosity 打印孔隙率的概率分布函数
//        DO 250 i1=1,i1Numbers
//write(7,230) i1,FiPorosMid(i1),ProDisFporos(i1)
//230  format(3X,I4,11X,E12.4,10X,E12.4)
//250  continue
    for (int i1 = 0; i1 < i1Numbers; i1++) {
        printf("   %d           %E          %E\n", i1, FiPorosMid[i1], ProDisFporos[i1]);
    }


//对数正态分布的mu和西格玛的计算
//c  2-2(a): calculation of Mu and Sigma of the lognormal distribution
//        c          function for thickness
    MuThick = 0.0;
//        MuThick=0.
//DO 300 j=1,jNumbers
//HthickLn(j)=ALOG(Hthick(j))
//MuThick=MuThick+HthickLn(j)
//300  continue
    for (int j = 0; j < jNumbers; j++) {
        HthickLn[j] = log(Hthick[j]);
        MuThick = MuThick + HthickLn[j];
    }

//MuThick=MuThick/jNumbers
//SigmaThick=0.
    MuThick = MuThick / jNumbers;
    double SigmaThick = 0.0;
    double SigmaThick2 = 0.0;
//DO 320 j=1,jNumbers
//SigmaThick=SigmaThick+ABS(HthickLn(j)-MuThick)
//320  continue
    for (int j = 1; j <= jNumbers; j++) {
        SigmaThick = SigmaThick + fabs(HthickLn[j] - MuThick);
    }

    SigmaThick2 = SigmaThick / (jNumbers - 1);
    SigmaThick = sqrt(SigmaThick2);

//对数正态分布的mu和西格玛的打印
//c  2-2(b): print Mu and Sigma of the lognormal distribution function
//        c          for thickness
//write(7,350) MuThick,SigmaThick
//350  format(/1X,'for thickness, ','Mu=',E12.4,'; Sigma=',E12.4)
//fprintf(fp, " for thickness, Mu= %E, Sigma= %E", MuThick, SigmaThick);
    printf(" for thickness, Mu= %E, Sigma= %E\n", MuThick, SigmaThick);


//C  --------------------------------------------------------------------
//
//c  2-2(c): calculation of cumulative frequency distribution 厚度累积频率分布的计算
//        c          for thickness, which is considered as the probability
//c          distribution function
//write(7,400)
//400  format(/1X,'interval No.',2X,'mid. of interval (m)',2X,
//1           'probability dis. func. value')
//fprintf(fp, " interval No.  mid. of interval (m)  probability dis. func. value\n");

    printf(" interval No.  mid. of interval (m)  probability dis. func. value\n");
//SUM=0.
//constant=1.0/(SQRT(2.*3.1416)*SigmaThick)
//DO 420 j1=j1Numbers,1,-1
//DeltaH=VintervalH/2.0
//ThMiddle=HthickStar(j1)+DeltaH

    sum = 0.0;
    constant_num = 1.0 / (sqrt(2 * 3.1416) * SigmaThick);
    for (int j1 = j1Numbers; j1 >= 1; j1--) {
        double DeltaH = VintervalH / 2.0;
        double ThMiddle = HthickStar[j1] + DeltaH;


//c  calculation of the lognormal distribution function for thickness
//        CALL LogNormFun(constant,ThMiddle,MuThick,SigmaThick,y)

//SUM=SUM+y*VintervalH
        double y = LogNormFun(constant_num, ThMiddle, MuThick, SigmaThick);
        sum = sum + y * VintervalH;
//if (SUM.LE.1.) then
//ProDisFthick(j1)=SUM
//else
//ProDisFthick(j1)=1.
//endif
//420  continue

        if (sum <= 1.0) {
            ProDisFthick[j1] = sum;
        } else {
            ProDisFthick[j1] = 1.0;
        }
    }

//c  2-2(d): print the probability distribution function for thickness   打印厚度的概率分布函数
//        DO 450 j1=1,j1Numbers
//write(7,430) j1,HthickMid(j1),ProDisFthick(j1)
//430  format(3X,I4,11X,E12.4,14X,E12.4)
//450  continue
    for (int j1 = 0; j1 < j1Numbers; j1++) {
        //   fprintf(fp, "   %d           %E              %E\n", j1, HthickMid[j1],ProDisFthick[j1]);
        printf("   %d           %E              %E\n", j1, HthickMid[j1], ProDisFthick[j1]);
    }
//c  3: k=1
//k=1
    int k = 1;
    double VM = 524288.0;
    double Alpha = 3125.0;

    double Beta = 3.0;
    double X1 = 23.0;
    double Xk = X1;

//产生伪随机数k
//c  4: generation of the pseudo random number about k
//500  RANDOMk=Xk/VM
    double randomk;
    double randomkpre;
    
    while (k <= kSamp)
    {
        randomk = Xk / VM;

        if ((k != 1) && randomkpre == randomk)
        {
            printf(" ERROR 1: current pseudo random number (%lf)          equals to          the last pseudo random number (%lf)",
                   randomk, randomkpre);
        }

        randomkpre = randomk;
        Xk = Alpha * Xk + Beta;
        Xk = amod(Xk, VM);

        int i1HIT;
        int j1HIT;
        int i1;
        int H;
        double Fi;
    
            

        for (int i1 = 0; i1 < i1Numbers - 1; i1++)
        {
            if ((randomk >= ProDisFporos[i1 + 1]) && (randomk <= ProDisFporos[i1])) {
                i1HIT = i1;
                Fi = FiPorosMid[i1HIT] +
                     (FiPorosMid[i1HIT + 1] - FiPorosMid[i1HIT]) / (ProDisFporos[i1HIT + 1] - ProDisFporos[i1HIT]) *
                     (randomk - ProDisFporos[i1HIT]);
            }
        }
            if (randomk <= ProDisFporos[i1Numbers])
            {
                i1HIT = i1Numbers;
                Fi = FiPorosMid[i1HIT];
            }
            if (randomk >= ProDisFporos[1])
            {
                i1HIT = 1;
                Fi = FiPorosMid[i1HIT];
            }

            for (int j1 = 0; j1 < j1Numbers - 1; j1++)
            {
               if ((randomk >= ProDisFthick[j1 + 1]) && randomk <= ProDisFthick[j1])
               {
                   j1HIT = j1;
                   H = HthickMid[j1HIT] +
                       (HthickMid[j1HIT + 1] - HthickMid[j1HIT]) / (ProDisFthick[j1HIT + 1] - ProDisFthick[j1HIT]) *
                       (randomk - ProDisFthick[j1HIT]);
               }
            }


            printf(" ERROR 2: pseudo random number = %E could not be located in any probability distribution function interval for porosity\n",
                   randomk);



        for (int j1 = 0; j1 < j1Numbers - 1; j1++)
        {

            if ((randomk >= ProDisFthick[j1 + 1]) && randomk <= ProDisFthick[j1])
            {
                j1HIT = j1;
                H = HthickMid[j1HIT] +
                    (HthickMid[j1HIT + 1] - HthickMid[j1HIT]) / (ProDisFthick[j1HIT + 1] - ProDisFthick[j1HIT]) *
                    (randomk - ProDisFthick[j1HIT]);
            }
        }
            if (randomk <= ProDisFthick[j1Numbers])
            {
                j1HIT = j1Numbers;
                H = HthickMid[j1HIT];
                PsRANDOM[k] = randomk;
                Vfi[k] = pow(10.0, 6) * Fi * H * Sarea;
            }
            if (randomk >= ProDisFthick[1])
            {
                j1HIT = 1;
                H = HthickMid[j1HIT];
                PsRANDOM[k] = randomk;
                Vfi[k] = pow(10.0, 6) * Fi * H * Sarea;
            }
            printf(" ERROR 3: pseudo random number = %E could not be located in any probability distribution function interval for thickness\n",
                   randomk);




        k = k + 1;

    }



//
//c  9(a):  generation of the probability distribution function
//c         for the porous volume, that is,
//        c         sequencing the pseudo random number in order
//        c         from big to small, and its respective porous volumes
//c         are in the same time
//DO 800  k=1,kSamp
//PsMAX=-1.0
    double PsMAX;
    int k1;
    int k1HIT;
    double buff1;
    double buff2;
    for (int k = 0; k < kSamp; k++) {
        PsMAX = -1.0;

//DO 700  k1=k,kSamp
        k1 = k;
        k1 = kSamp;

//if (PsRANDOM(k1).GT.PsMAX) then
//        k1HIT=k1
//PsMAX=PsRANDOM(k1)
//endif
//700  continue
        if (PsRANDOM[k1] > PsMAX) {
            k1HIT = k1;
            PsMAX = PsRANDOM[k1];
        }
    }
//
//if (k1HIT.EQ.k) go to 800
//buff1=PsRANDOM(k1HIT)
//buff2=Vfi(k1HIT)
//PsRANDOM(k1HIT)=PsRANDOM(k)
//Vfi(k1HIT)=Vfi(k)
//PsRANDOM(k)=buff1
//Vfi(k)=buff2
//800  continue
//write(*,801) kSamp
//write(7,801) kSamp
//801  format(/3X,'total number of samplings:',I6)

    if (k1HIT == k) {
        printf("   total number of samplings: %E\n", kSamp);
    }

    buff1 = PsRANDOM[k1HIT];
    buff2 = Vfi[k1HIT];
    PsRANDOM[k1HIT] = PsRANDOM[k];
    Vfi[k1HIT] = Vfi[k];
    PsRANDOM[k] = buff1;
    Vfi[k] = buff2;

//c  9(b):  delete some pseudo random numbers which equal to
//c         one another,
//c         and leave only one of them
//        kNew=0
//do 805 k=1,kSamp-1
//if (PsRANDOM(k).eq.PsRANDOM(k+1)) then
//        go to 805
//endif
//        kNew=kNew+1
//PsRANDOM(kNew)=PsRANDOM(k)
//Vfi(kNew)=Vfi(k)
//805  continue
//kSampNew=kNew
//write(*,806) kSampNew
//write(7,806) kSampNew
//806  format(3X,'total number of available samplings:',I4)
//
    int kNew = 0;
    int kSampNew;
    for (int k = 0; k < kSamp - 1; k++) {

        if (PsRANDOM[k] == PsRANDOM[k + 1]) {
            kSampNew = kNew;
            printf("   total number of available samplings: %E", kSampNew);
        } else {
            kNew = kNew + 1;
            PsRANDOM[kNew] = PsRANDOM[k];
            Vfi[kNew] = Vfi[k];

        }

    }
//c  9(c):  by using the linear interporation,
//c         calculate the porous volumes
//        c         when pseudo random number is 0.95, 0.50, .05


//
//DO 900  L=1,3
//if (L.EQ.1) Random=0.95
//if (L.EQ.2) Random=0.50
//if (L.EQ.3) Random=0.05
//
    double Random;
    for (int L = 1; L <= 3; L++) {
        if (L == 1) {
            Random = 0.95;
        }
        if (L == 2) {
            Random = 0.50;
        }
        if (L == 3) {
            Random = 0.05;
        }

        int kHIT;
        double VfiPr;
        for (int k = 1; k <= kSamp - 1; k++) {
            if ((Random >= PsRANDOM[k + 1]) && (Random <= PsRANDOM[k])) {
                kHIT = k;
                VfiPr = Vfi[kHIT] +
                        (Vfi[kHIT + 1] - Vfi[kHIT]) / (PsRANDOM[kHIT + 1] - PsRANDOM[kHIT]) * (Random - PsRANDOM[kHIT]);

            }
            printf(" ERROR 4: pseudo random number = %E could not be located in any pseudo random number interval",
                   Random);

        }

        printf("     when probability= %5.2lf  porous volume= %E (m^3)\n", Random, VfiPr);


    }

//DO 810  k=1,kSampNew-1
//if ((Random.GE.PsRANDOM(k+1)).AND.
//1      (Random.LE.PsRANDOM(k))) then
//        kHIT=k
//go to 830
//endif
//810  continue










//write(*,820) Random
//write(7,820) Random
//820  format(/1X,'ERROR 4: pseudo random number =',E12.4,','/
//1        1X,'         could not be located in any pseudo'/
//2        1X,'         random number interval')
//stop


//830  VfiPr=Vfi(kHIT)+(Vfi(kHIT+1)-Vfi(kHIT))
//1                     /(PsRANDOM(kHIT+1)-PsRANDOM(kHIT))
//2                     *(Random-PsRANDOM(kHIT))
//write(7,840) Random,VfiPr
//840  format(/5X,'when probability=',F5.2,','2X,
//1           'porous volume=',E12.4,' (m^3)')
//900  continue


//write(*,1000)
//write(7,1000)
//1000 format(/1X,'$$$$ Program PorVolTrap has been finished $$$$')
//CLOSE(UNIT=7)
//STOP
//        END
    printf(" $$$$ Program PorVolTrap has been finished $$$$");

//计算对数正态分布函数的值。
//SUBROUTINE LogNormFun(C,X,Mu,Sigma2,y)
//c  Its function: calculate the value of
//c                the lognormal distribution function.
//c  Enter Parameters: C, X, Mu, Sigma2
//        c  Exit Results: y
    //real Mu
    return 0;
}
double LogNormFun(double C, double X, double Mu, double Sigma2)
{

    //y=C/X*EXP(-(ALOG(X)-Mu)**2/(2.*Sigma2))
    double y = C / X * exp(-(log(X) - Mu) * 2 /(2.0 * Sigma2));
    return y;
}
//
//        y=C/X*EXP(-(ALOG(X)-Mu)**2/(2.*Sigma2))
//
//RETURN
//        END



