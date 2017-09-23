#include "USER_Sliding.h"


//int Sliding_Para[17]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
SLiding_Para sliding_para;
volatile float T[4]={0,0,0,0}; //推进器力
volatile float u=0,w=0,x=0,z=0,tt=0;
//u为动系水平速度，w为动系垂直速度，x为水平位置，z为垂直位置，tt为路径规划时间值


//void spacecontrol1(float ax, float az, float gz, float psi, int ud, int psid, int zd, int m,int n,int avx, int avz, int p1)
//ax,az,gz分别为传感器x方向、z方向、绕z轴旋转的加速度和角速度实际值；psi为偏航角实测值；
//ud、psid、zd分别为动系水平速度、偏航角、垂直位置的目标值(都为一个字节)；m、n为控制器参数值（都为一个字节）；
//avx,avz,p1为传感器加速度调零参数(都为两个字节)
void  spacecontrol1(void)
{
    int i;
    float ax1,az1,gz1,s1,s2,s3;
    float timejifen=0.05;
    float ud1;
    float psi1;
    float psid1;
    float zd1;
    float m1,n1;
    float tanh1,tanh2,tanh3;
    float h1,h2,h3;

    float ax,az,gz,psi;
    int ud,psid,zd,m,n,avx,avz,p1;

    //reload parameter
    ax = AHRS_Data[3];
    az = AHRS_Data[5];
    gz = AHRS_Data[8];
    psi = AHRS_Data[0];
    ud = sliding_para.data[4];
    psid = sliding_para.data[6];
    zd = sliding_para.data[3];
    m = sliding_para.data[0];
    n = sliding_para.data[1];

    p1 = sliding_para.data1[0];
    avx = sliding_para.data1[1];
    avz = sliding_para.data1[2];

    ud1=(float)ud/255.0;
    psi1=psi/1.0;
    psid1=psid/1.0;
    zd1=zd/10.0;
    m1=m/1.0;
    n1=n/10.0;


	ax1=(ax-p1)/avx*9.8000;

	x+= u*timejifen+0.5*ax1*timejifen*timejifen; //位置
//	sumAxHeight=100;
	u+= ax1*timejifen;
//		sumAx=0.2;
	az1=9.8-az/avz*9.8;

	z+= w*timejifen+0.5*az1*timejifen*timejifen; //位置
//	sumAzHeight=2/10.0;
	w+= az1*timejifen; //速度
//		sumAz=0;
	gz1=(double)gz/16.4*1.0;
//	gz1=gz;

	s1=u-ud1;
    s2=gz1-0+(psi1-psid1);
    s3=w-0+2.6*(z-zd1);
    s1=s1/n1;
    s2=s2/n1;
    s3=s3/n1;
    if(s1>0)
    {
        if(s1<2.5)
        {
            tanh1=0.0661*s1*s1*s1-0.4782*s1*s1+1.1817*s1;
        }
        else
        {
            tanh1=1;
        }
    }
    else
    {
        if(s1>-2.5)
        {
            tanh1=0.0661*s1*s1*s1+0.4782*s1*s1+1.1817*s1;
        }
        else
        {
            tanh1=-1;
        }
    }

	if(s2>0)
    {
        if(s2<2.5)
        {
            tanh2=0.0661*s2*s2*s2-0.4782*s2*s2+1.1817*s2;
        }
        else
        {
            tanh2=1;
        }
    }
    else
    {
        if(s2>-2.5)
        {
            tanh2=0.0661*s2*s2*s2+0.4782*s2*s2+1.1817*s2;
        }
        else
        {
            tanh2=-1;
        }
    }

	if(s3>0)
    {
        if(s3<2.5)
        {
            tanh3=0.0661*s3*s3*s3-0.4782*s3*s3+1.1817*s3;
        }
        else
        {
            tanh3=1;
        }
    }
    else
    {
        if(s3>-2.5)
        {
            tanh3=0.0661*s3*s3*s3+0.4782*s3*s3+1.1817*s3;
        }
        else
        {
            tanh3=-1;
        }
    }

	h1=-m1*tanh1;
	h2=-1.85*w-m1*tanh2;
	h3=0.905*gz1-m1*tanh3;

	T[0]=-(-14.45*h1+55.56*h2-4.5*h3);
	T[1]=-14.45*h1-55.56*h2+4.5*h3;
	T[2]=-(14.45*h1+55.56*h2+4.5*h3);
	T[3]=14.45*h1-55.56*h2-4.5*h3;

	for(i=0;i<4;i++)
	{
        if(T[i]>40)
        {
            T[i]=40;
        }
        else
        {
            if(T[i]<-40)
            {
                T[i]=-40;
            }
        }
	}


}



/*ax,az,gz分别为传感器x方向、z方向、绕z轴旋转的加速度和角速度实际值；psi为偏航角实测值；
 *xd、psid、zd分别为水平位置、偏航角、垂直位置的目标值(都为一个字节)；t1,t2为路径规划参数值；m、n为控制器参数值(都为一个字节)；
 *avx,avz,p1为传感器加速度调零参数(都为两个字节)
 *void spacecontrol2(float ax, float az, float gz, float psi, int xd, int psid, int zd, int t1, int t2, int m,int n,int avx, int avz, int p1)
 */
void  spacecontrol2(void)
{
	int i;
	float ax1,az1,s1,s3;
	float timejifen=0.05;
	float xd1;
	float zd1;
	float n1;
	float tanh1,tanh3;
	float t11,t21,a1,b1,a2,b2;
	float xd2,ud2,uddot,zd2,wd2,wddot;
	float a,b;
	float F1,F2;

    float ax,az,gz,psi;
    int xd,psid,zd,t1,t2,m,n,avx,avz,p1;

    //reload parameter
    ax = AHRS_Data[3];
    az = AHRS_Data[5];
    gz = AHRS_Data[8];
    psi = AHRS_Data[0];
    xd = sliding_para.data[2];
    psid = sliding_para.data[6];
    zd = sliding_para.data[3];
    t1 = sliding_para.data[9];
    t2 = sliding_para.data[10];
    m = sliding_para.data[0];
    n = sliding_para.data[1];

    p1 = sliding_para.data1[0];
    avx = sliding_para.data1[1];
    avz = sliding_para.data1[2];

	xd1=(float)xd;
	zd1=zd/10.0;
	n1=n/10.0;

	ax1=(ax-p1)/avx*9.8000;

	x+= u*timejifen+0.5*ax1*timejifen*timejifen; //位置
//	sumAxHeight=100;
	u+= ax1*timejifen;
//		sumAx=0.2;
	az1=9.8-(float)az/avz*9.8;

	z+= w*timejifen+0.5*az1*timejifen*timejifen; //位置
//	sumAzHeight=2/10.0;
	w+= az1*timejifen; //速度
//		sumAz=0;
//	gz1=(double)gz/16.4*(-1);

	t11=t1/10.0;
    t21=t2/10.0;
    xd1=(float)xd;
    zd1=zd/10.0;
    a1=-2/t11/t11/t11*xd1;
    b1=3/t11/t11*xd1;
    a2=-2/t21/t21/t21*zd1;
    b2=3/t21/t21*zd1;
    tt=tt+0.05;
    if(tt<=t11)
    {
        xd2=a1*tt*tt*tt+b1*tt*tt;
        ud2=3*a1*tt*tt+2*b1*tt;
        uddot=6*a1*tt+2*b1;
    }
    else
    {
        xd2=xd1;
        ud2=0;
        uddot=0;
    }

    if(tt<=t21)
    {
        zd2=a2*tt*tt*tt+b2*tt*tt;
        wd2=3*a2*tt*tt+2*b2*tt;
        wddot=6*a2*tt+2*b2;
    }
    else
    {
        zd2=zd1;
        wd2=0;
        wddot=0;
    }



	s1=u-ud2+2.5*(x-xd2);;
	s3=(w-wd2)+2.6*(z-zd2);
    s1=s1/n1;
    s3=s3/n1;
    if(s1>0)
    {
        if(s1<2.5)
        {
            tanh1=0.0661*s1*s1*s1-0.4782*s1*s1+1.1817*s1;
        }
        else
        {
            tanh1=1;
        }
    }
    else
    {
        if(s1>-2.5)
        {
            tanh1=0.0661*s1*s1*s1+0.4782*s1*s1+1.1817*s1;
        }
        else
        {
            tanh1=-1;
        }
    }
//	if(s2>0)
//			{if(s2<2.5)
//			{tanh2=0.0661*s2*s2*s2-0.4782*s2*s2+1.1817*s2;}
//			else
//			{
//				tanh2=1;
//			}
//			}
//		else
//		{if(s2>-2.5)
//			{tanh2=0.0661*s2*s2*s2+0.4782*s2*s2+1.1817*s2;}
//		else
//		{
//			tanh2=-1;
//		}
//		}
	if(s3>0)
    {
        if(s3<2.5)
        {
            tanh3=0.0661*s3*s3*s3-0.4782*s3*s3+1.1817*s3;
        }
        else
        {
            tanh3=1;
        }
    }
    else
    {
        if(s3>-2.5)
        {
            tanh3=0.0661*s3*s3*s3+0.4782*s3*s3+1.1817*s3;
        }
        else
        {
            tanh3=-1;
        }
    }
    a=-40.77*m*tanh1+2.448*u*abs(u)-101.93*u+40.77*uddot+101.93*ud2;
    b=-111.02*w-59.87*m*tanh3+59.87*wddot+155.66*wd2;

    F1=(a*0.577+b)/4*2;
    F2=(a*0.577-b)/4*2;

    T[0]=-F2;
    T[1]=F1;
    T[2]=F1;
    T[3]=-F2;

    for(i=0;i<4;i++)
  	{
        if(T[i]>40)
        {
            T[i]=40;
        }
        else
        {
            if(T[i]<-40)
            {
                T[i]=-40;
            }
        }
  	}
}

extern void Set_SlidingPara(void)
{
	uint8_t i = 0,j=0;
	int temp = 0;
	for(i = 0; i< 11;i++)
	{
		sliding_para.data[i] = Real_PcBuff[i+2];
	}

	j = 13;
	for(i = 0; i< 3;i++)
	{
		temp = 0;
		temp = (Real_PcBuff[j] <<8 ) + Real_PcBuff[j+1];
		if(temp&0x8000)
		{
			temp = 0 - temp&0x7fff;
		}
		else
		{
			temp = (temp&0x7fff);
		}
		sliding_para.data1[i] = temp;
		j = j + 2;
	}
	UART_Send();
}

