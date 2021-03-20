//
// Created by 张力文 on 2021/3/15.
//

//计算多孔体积的平均值
// C  $$$$$$$$$$$$$$$$$$$$$$$$  PorVolTrap.f  $$$$$$$$$$$$$$$$$$$$$head
//C
//        C            ************************************************
//C            *       $$$$$   PROGRAM PorVolTrap  $$$$$      *
//        C            *   Its function:                              *
//C            *      ---  Monte Carlo Method  ---            *
//C            *     calculation of porous volume for a trap  *
//C            *     by use of Monte Carlo method             *
//        C            ************************************************
//C
//        C             All Rights Reserved by Prof. Guangren Shi
//C
//        PROGRAM PorVolTrap
//        c  %%%%%%%%%%%%%%%%%%%%%%%%%% Note %%%%%%%%%%%%%%%%%%%%%%%%%%%%% top//
//        c    file name     attribution  logical unit(decimal)  record size
//c  PorVolTrap.PRT  print file         7                    133
//c   --------------------------------------------------------------
//c  INPUT DATA:  Sarea, FiPoros, Hthick, VminFi,VminH,
//c               VintervalFi, VintervalH,
//        c               and all the parameters in statement PARAMETER.
//c  INTERMEDIATE RESULTS:  MuPoros, SigmaPoros, FiPorosMid,
//c                         ProDisFporos;
//c                         MuThick, SigmaThick, HthickMid,
//        c                         ProDisFthick
//        c  FINAL RESULTS:  PsRANDOM, Vfi, Random,VfiPr
//        c  %%%%%%%%%%%%%%%%%%%%%%%%%% Note %%%%%%%%%%%%%%%%%%%%%%%%%%%%% bot
//
//        c   iNumbers --- number of the observed porosity for a trap 陷阱观察到的孔隙度的数目
//c   jNumbers --- number of the observed thickness for a trap 一个陷阱的观测厚度数
//c   i1Numbers --- number of the statistical intervals for porosity 孔隙度统计间隔的数目
//        c   j1Numbers --- number of the statistical intervals for thickness
//        c   i1Numbers1 --- number of terminal values on each statistical
//        c                  interval for porosity //孔隙度每个统计间隔上的终值数
//        c   j1Numbers1 --- number of terminal values on each statistical
//        c                  interval for thickness
//        c   kSamp --- number of random samplings
//parameter 是设定变数的固定值，其作用就相当于 C 的 const 一样
//PARAMETER(iNumbers=25,jNumbers=40,
//1          i1Numbers=45,j1Numbers=96,
//2          i1Numbers1=i1Numbers+1,j1Numbers1=j1Numbers+1,
//3          kSamp=2000)
#define E 2.7182818
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
const int iNumbers = 25, jNumbers=40, i1Numbers=45,j1Numbers=96,i1Numbers1=i1Numbers+1,j1Numbers1=j1Numbers+1, kSamp=2000;
//c   FiPoros --- porosity of a trap, fraction 陷阱的孔隙度，分数
//c   Hthick --- thickness of a trap, unit: m

//data FiPoros/0.21,0.23,0.255,0.26,0.27,
//             0.28,0.29,0.305,0.31,0.315,
//            0.32,0.325,0.33,0.335,0.34,
//            0.345,0.348,0.355,0.36,0.37,
//             0.38,0.39,0.42,0.43,0.44/
double Fiporos[iNumbers] = {0.21,0.23,0.255,0.26,0.27,
             0.28,0.29,0.305,0.31,0.315,
            0.32,0.325,0.33,0.335,0.34,
            0.345,0.348,0.355,0.36,0.37,
             0.38,0.39,0.42,0.43,0.44};
int Hthick[jNumbers] = {15.,26.,28.,31.,33.,
            35.,37.,42.,43.,44.,
            45.,46.,47.,50.5,51.,
            52.,53.,54.,55.,56.,
            57.,58.,59.,62.,63.,
            64.,65.,66.,67.,68.,
            73.,74.,75.,76.,77.,
            84.,85.,86.,95.,96.}
//dimension FiPoros(iNumbers),Hthick(jNumbers)
//c   FiPorosLn --- ln(FiPoros)
//c   HthickLn --- ln(Hthick)
//dimension FiPorosLn(iNumbers),HthickLn(jNumbers)

for(int i = 0; i < iNumbers; i++)
{
    FiPorosLn[i] = log(Fiporos[i]);
}

for(int j = 0; j < jNumbers; j++)
{
    HthickLn[j] = log(Hthick[j]);
}
//c   FiPorosStar --- terminal values of each statistical interval
//c                   for porosity, fraction
//        c   HthickStar --- terminal values of each statistical interval
//c                  for thickness, unit: m
//dimension FiPorosStar(i1Numbers1),HthickStar(j1Numbers1)
double FiPorosStar[i1Numbers];
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
double MuPoros,MuThick;

//        c   Sarea --- area of a trap, unit: km^2
//data Sarea/1.0/
double Sarea = 1.0;//陷阱的面积，单位为km^2

//c   FiPoros --- porosity of a trap, fraction
//data FiPoros/0.21,0.23,0.255,0.26,0.27,
//1             0.28,0.29,0.305,0.31,0.315,
//2             0.32,0.325,0.33,0.335,0.34,
//3             0.345,0.348,0.355,0.36,0.37,
//4             0.38,0.39,0.42,0.43,0.44/
//c   Hthick --- thickness of a trap, unit: m
//        data Hthick/15.,26.,28.,31.,33.,
//1            35.,37.,42.,43.,44.,
//2            45.,46.,47.,50.5,51.,
//3            52.,53.,54.,55.,56.,
//4            57.,58.,59.,62.,63.,
//5            64.,65.,66.,67.,68.,
//6            73.,74.,75.,76.,77.,
//7            84.,85.,86.,95.,96./6t
//c   VminFi --- minimum of the FiPorosStar, fraction
//c   VminH --- minimum of the HthickStar, unit: m

double VminFi,VminH = 0.0;

//c   VintervalFi --- value of the each statistical interval 孔隙度的每个统计间隔的值，分数
//c                   for porosity, fraction
//        c   VintervalH --- value of the each statistical interval
//c                  for thickness, unit: m
double VintervalFi = 0.01;
double VintervalH = 1.0;

//c  calculate the average of porous volume 计算孔隙体积的平均值
//c  (only for observation) 仅仅用于观察
//sum1=0.
//do i=1,iNumbers
//sum1=sum1+FiPoros(i)
//enddo
//        sum1=sum1/iNumbers
//sum2=0.
int sum1 = 0;
for(int i = 1; i <= iNumbers; i++)
{
    sum1 = sum1 + Fiporos[i];
    sum1 = sum1 / iNumbers;

}


//do j=1,jNumbers
//sum2=sum2+Hthick(j)
//enddo
//        sum2=sum2/jNumbers
int sum2 = 0;
for(int j = 1; j <= jNumbers; j++)
{
    sum2=sum2+Hthick[j];
    sum2=sum2/jNumbers;
}

//Volfi=1E6*sum1*sum2*Sarea
//double Volfi;
Volfi = E * pow(10, 6) * sum1 * sum2 * Sarea;
//c     open the print file PorVolTrap.PRT 从PorVolTrap.PRT打开打印文件
//以下是读写PorVolTrap.PRT文件操作，并向该文件写入一开始的变量名称等

FILE *fp = NULL;
fp = fopen("monte_carlo.txt","w+");
//OPEN(UNIT=7,FILE='PorVolTrap.PRT')
write(*,10)
write(7,10)
10   format(/1X,'$$$$ Program PorVolTrap begins to run $$$$')
//c  print the average of porous volume (only for observation)
write(7,1) sum1
1    format(/1X,'  average of FiPoros:',E14.6)
write(7,2) sum2
2    format(/1X,'  average of Hthick:',E14.6)
write(7,3) Volfi
3    format(/1X,'  average of Vfi:',E14.6)

fprintf(fp, " $$$$ Program PorVolTrap begins to run $$$$\n");
fprintf(fp,"  average of FiPoros: %")
//c  1(a): generation of the statistical interval for porosity 孔隙度的统计时间间隔的生成
//FiPorosStar[1]=VminFi;
//        DO 20 i1=1,i1Numbers
//FiPorosStar(i1+1)=FiPorosStar(i1)+VintervalFi
//20   continue

for(int i1 = 1; i < i1Numbers; i++)
{
    FiPorosStar[i1+1] = FiPorosStar[i1] + VintervalFi;
}
//c  1(b): generation of the statistical interval for thickness 厚度统计间隔的生成
//HthickStar(1)=VminH
//        DO 30 j1=1,j1Numbers
//HthickStar(j1+1)=HthickStar(j1)+VintervalH
//30   continue

for(int j1 = 1; j < j1Numbers; j++)
{
    HthickStar[j1+1] = HthickStar[j1] + VintervalH;
}
//c  1(c): generation of the middle point values of each statistical
//        c        interval for porosity
//        DO 40 i1=1,i1Numbers
//FiPorosMid(i1)=FiPorosStar(i1)+
//               1                (FiPorosStar(i1+1)-FiPorosStar(i1))/2.
//40   continue

for(int i1 = 1; i < i1Numbers; i++)
{
    FiPorosStar[i1]+(FiPorosStar[i1+1]-FiPorosStar[i1])/2;
}
//c  1(d): generation of the middle point values of each statistical
//        c        interval for thickness
//        DO 50 j1=1,j1Numbers
//HthickMid(j1)=HthickStar(j1)+
//              1                (HthickStar(j1+1)-HthickStar(j1))/2.
//50   continue

for(int j1 = 1; j < j1Numbers; j++)
{
    HthickMid[j1]=HthickStar[j1]+(HthickStar[j1+1]-HthickStar[j1])/2.
}

//c  2-1(a): calculation of Mu and Sigma of the lognormal distribution 孔隙度对数正态分布函数的Mu和Sigma的计算
//        c          function for porosity
        MuPoros=0;
//DO 100 i=1,iNumbers
//FiPorosLn(i)=ALOG(FiPoros(i))
//MuPoros=MuPoros+FiPorosLn(i)
//100  continue
//MuPoros=MuPoros/iNumbers
//
for(int i = 1; i < iNumbers; i++)
{
    FiPorosLn[i] = log(FiPoros[i]);
    MuPoros = MuPoros+FiPorosLn[i];
    MuPoros = MuPoros/iNumbers;
}


double SigmaPoros=0;
double SigmaPoros2;
//DO 120 i=1,iNumbers
//SigmaPoros=SigmaPoros+ABS(FiPorosLn(i)-MuPoros)
//120  continue
//SigmaPoros2 = SigmaPoros/(iNumbers-1);
//SigmaPoros=SQRT(SigmaPoros2)

for(int i = 1; i < iNumbers; i++)
{
    SigmaPoros = SigmaPoros + abs(FiPorosLn[i] - MuPoros);
    SigmaPoros2 = SigmaPoros/(iNumbers-1);
    SigmaPoros=sqrt(SigmaPoros2);
}



//c  2-1(b): print Mu and Sigma of the lognormal distribution function 打印对数正态分布函数的Mu和西格玛
//        c          for porosity
write(7,150) MuPoros,SigmaPoros
150  format(/1X,'for porosity, ','Mu=',E12.4,'; Sigma=',E12.4)
//c  2-1(c): calculation of cumulative frequency distribution
//        c          for porosity, which is considered as the probability
//c          distribution function
write(7,200)
200  format(/1X,'interval No.',2X,'mid. of interval',2X,
1           'probability dis. func. value')
SUM=0.
constant=1.0/(SQRT(2.*3.1416)*SigmaPoros)
DO 220 i1=i1Numbers,1,-1
DeltaFi=VintervalFi/2.
FiMiddle=FiPorosStar(i1)+DeltaFi


//c  calculation of the lognormal distribution function for porosity
        CALL LogNormFun(constant,FiMiddle,MuPoros,SigmaPoros,y)
SUM=SUM+y*VintervalFi
if (SUM.LE.1.) then
ProDisFporos(i1)=SUM
else
ProDisFporos(i1)=1.
endif
220  continue
//c  2-1(d): print the probability distribution function for porosity
        DO 250 i1=1,i1Numbers
write(7,230) i1,FiPorosMid(i1),ProDisFporos(i1)
230  format(3X,I4,11X,E12.4,10X,E12.4)
250  continue

//c  2-2(a): calculation of Mu and Sigma of the lognormal distribution
//        c          function for thickness
        MuThick=0.
DO 300 j=1,jNumbers
HthickLn(j)=ALOG(Hthick(j))
MuThick=MuThick+HthickLn(j)
300  continue
MuThick=MuThick/jNumbers
SigmaThick=0.
DO 320 j=1,jNumbers
SigmaThick=SigmaThick+ABS(HthickLn(j)-MuThick)
320  continue
SigmaThick2=SigmaThick/(jNumbers-1)
SigmaThick=SQRT(SigmaThick2)
//c  2-2(b): print Mu and Sigma of the lognormal distribution function
//        c          for thickness
write(7,350) MuThick,SigmaThick
350  format(/1X,'for thickness, ','Mu=',E12.4,'; Sigma=',E12.4)

//C  --------------------------------------------------------------------
//c  2-2(c): calculation of cumulative frequency distribution
//        c          for thickness, which is considered as the probability
//c          distribution function
write(7,400)
400  format(/1X,'interval No.',2X,'mid. of interval (m)',2X,
1           'probability dis. func. value')

SUM=0.
constant=1.0/(SQRT(2.*3.1416)*SigmaThick)
DO 420 j1=j1Numbers,1,-1
DeltaH=VintervalH/2.0
ThMiddle=HthickStar(j1)+DeltaH
//c  calculation of the lognormal distribution function for thickness
        CALL LogNormFun(constant,ThMiddle,MuThick,SigmaThick,y)
SUM=SUM+y*VintervalH
if (SUM.LE.1.) then
ProDisFthick(j1)=SUM
else
ProDisFthick(j1)=1.
endif
420  continue

//c  2-2(d): print the probability distribution function for thickness
        DO 450 j1=1,j1Numbers
write(7,430) j1,HthickMid(j1),ProDisFthick(j1)
430  format(3X,I4,11X,E12.4,14X,E12.4)
450  continue

//c  3: k=1
k=1
//c     VM=2.**19=524288.
VM=524288.
Alpha=3125.
//c  the pair of (Beta,X1) can be (3,23), or (7,11),
//c                           or (11,19), or (17,37)
Beta=3.
X1=23.
Xk=X1
//c  4: generation of the pseudo random number about k
500  RANDOMk=Xk/VM
if ((k.ne.1).and.(RANDOMkPre.eq.RANDOMk)) then
write(*,510) RANDOMk,RANDOMkPre
write(7,510) RANDOMk,RANDOMkPre
510  format(/1X,'ERROR 1: current pseudo random number (',
1            E12.4,'),'/
2        1X,'         equals to'/
3        1X,'         the last pseudo random number (',
4            E12.4,').')
stop
        endif
RANDOMkPre=RANDOMk
Xk=Alpha*Xk+Beta
Xk=AMOD(Xk,VM)
//c  5: respecting the pseudo random number about k, RANDOMk,
//c     calculate the value of porosity and thickness
//c     on their probability distribution function
//c  5(a):  for porosity
        DO 600 i1=1,i1Numbers-1
if ((RANDOMk.GE.ProDisFporos(i1+1)).AND.
1      (RANDOMk.LE.ProDisFporos(i1))) then
        i1HIT=i1
go to 620
endif
600  continue
if (RANDOMk.LE.ProDisFporos(i1Numbers)) then
        i1HIT=i1Numbers
Fi=FiPorosMid(i1HIT)
go to 630
endif
if (RANDOMk.GE.ProDisFporos(1)) then
        i1HIT=1
Fi=FiPorosMid(i1HIT)
go to 630
endif
write(*,610) RANDOMk
write(7,610) RANDOMk
610  format(/1X,'ERROR 2: pseudo random number =',E12.4,','/
1        1X,'         could not be located in any probability'/
2        1X,'         distribution function interval'/
3        1X,'         for porosity')
stop
620  Fi=FiPorosMid(i1HIT)+(FiPorosMid(i1HIT+1)-FiPorosMid(i1HIT))
1                /(ProDisFporos(i1HIT+1)-ProDisFporos(i1HIT))
2                     *(RANDOMk-ProDisFporos(i1HIT))
//c  5(b):  for thickness
630  DO 650 j1=1,j1Numbers-1
if ((RANDOMk.GE.ProDisFthick(j1+1)).AND.
1      (RANDOMk.LE.ProDisFthick(j1))) then
        j1HIT=j1
go to 670
endif
650  continue
if (RANDOMk.LE.ProDisFthick(j1Numbers)) then
        j1HIT=j1Numbers
H=HthickMid(j1HIT)
go to 690
endif
if (RANDOMk.GE.ProDisFthick(1)) then
        j1HIT=1
H=HthickMid(j1HIT)
go to 690
endif
write(*,660) RANDOMk
write(7,660) RANDOMk
660  format(/1X,'ERROR 3: pseudo random number =',E12.4,','/
1        1X,'         could not be located in any probability'/
2        1X,'         distribution function interval'/
3        1X,'         for thickness')
stop
670  H=HthickMid(j1HIT)+(HthickMid(j1HIT+1)-HthickMid(j1HIT))
1            /(ProDisFthick(j1HIT+1)-ProDisFthick(j1HIT))
2                     *(RANDOMk-ProDisFthick(j1HIT))

//c  6:  form the probability distribution function
//        c      for the porous volume
690  PsRANDOM(k)=RANDOMk
Vfi(k)=1E6*Fi*H*Sarea
//c  7:  k=k+1
k=k+1
//c  8:  decide if k is greater than kSamp or not?
if (k.LE.kSamp) go to 500
//c  9(a):  generation of the probability distribution function
//c         for the porous volume, that is,
//        c         sequencing the pseudo random number in order
//        c         from big to small, and its respective porous volumes
//c         are in the same time
DO 800  k=1,kSamp
PsMAX=-1.0
DO 700  k1=k,kSamp
if (PsRANDOM(k1).GT.PsMAX) then
        k1HIT=k1
PsMAX=PsRANDOM(k1)
endif
700  continue
if (k1HIT.EQ.k) go to 800
buff1=PsRANDOM(k1HIT)
buff2=Vfi(k1HIT)
PsRANDOM(k1HIT)=PsRANDOM(k)
Vfi(k1HIT)=Vfi(k)
PsRANDOM(k)=buff1
Vfi(k)=buff2
800  continue
write(*,801) kSamp
write(7,801) kSamp
801  format(/3X,'total number of samplings:',I6)
//c  9(b):  delete some pseudo random numbers which equal to
//c         one another,
//c         and leave only one of them
        kNew=0
do 805 k=1,kSamp-1
if (PsRANDOM(k).eq.PsRANDOM(k+1)) then
        go to 805
endif
        kNew=kNew+1
PsRANDOM(kNew)=PsRANDOM(k)
Vfi(kNew)=Vfi(k)
805  continue
kSampNew=kNew
write(*,806) kSampNew
write(7,806) kSampNew
806  format(3X,'total number of available samplings:',I4)
//c  9(c):  by using the linear interporation,
//c         calculate the porous volumes
//        c         when pseudo random number is 0.95, 0.50, .05
DO 900  L=1,3
if (L.EQ.1) Random=0.95
if (L.EQ.2) Random=0.50
if (L.EQ.3) Random=0.05
DO 810  k=1,kSampNew-1
if ((Random.GE.PsRANDOM(k+1)).AND.
1      (Random.LE.PsRANDOM(k))) then
        kHIT=k
go to 830
endif
810  continue
write(*,820) Random
write(7,820) Random
820  format(/1X,'ERROR 4: pseudo random number =',E12.4,','/
1        1X,'         could not be located in any pseudo'/
2        1X,'         random number interval')
stop
830  VfiPr=Vfi(kHIT)+(Vfi(kHIT+1)-Vfi(kHIT))
1                     /(PsRANDOM(kHIT+1)-PsRANDOM(kHIT))
2                     *(Random-PsRANDOM(kHIT))
write(7,840) Random,VfiPr
840  format(/5X,'when probability=',F5.2,','2X,
1           'porous volume=',E12.4,' (m^3)')
900  continue
write(*,1000)
write(7,1000)
1000 format(/1X,'$$$$ Program PorVolTrap has been finished $$$$')
CLOSE(UNIT=7)
STOP
        END

SUBROUTINE LogNormFun(C,X,Mu,Sigma2,y)
//c  Its function: calculate the value of
//c                the lognormal distribution function.
//c  Enter Parameters: C, X, Mu, Sigma2
//        c  Exit Results: y
        real Mu
        y=C/X*EXP(-(ALOG(X)-Mu)**2/(2.*Sigma2))
RETURN
        END


//C  $$$$$$$$$$$$$$$$$$$$$$$$  PorVolTrap.f  $$$$$$$$$$$$$$$$$$$$$foot
