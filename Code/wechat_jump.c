#include<reg52.h>
#define uchar unsigned char
#define uint unsigned int

/* ����λ���� */
sbit dula = P2^6;
sbit wela = P2^7;

/* ����ܱ���� */
uchar code table[]={
0x3f, 0x06, 0x5b, 0x4f, 
0x66, 0x6d, 0x7d, 0x07,
0x7f, 0x6f, 0x77, 0x7c,
0x39, 0x5e, 0x79, 0x71, 0};

/* ȫ�ֱ������� */
uint press_time, TIME_BASE;
uchar flag, numL, numH;

/* �������� */
void init();
void display(uint);
void delay(uint);

/* ������ */
void main()
{
	//һ����ʼ��
	init();
	
	//����������ѭ��
	while(1)
	{
		//1.��ȡ����ʱ������
		while(!RI);
		RI = 0;
		numL = SBUF;	//�ӻ�����ȡ����8λ
		
		while(!RI);
		RI = 0;
		numH = SBUF;	//�ӻ�����ȡ����8λ
		press_time = (numH<<8)|numL;	//��װ��16λ
		
		//2.���ն�ȡ��ʱ�����е���ʱ���ڼ��������ʾʱ����P1^0����0
		TR0 = 1;	//������ʱ��
		while(TIME_BASE<press_time)
		{
			display(press_time);
			P1 = 0xFE;
		}
		TR0 = 0;	//�رն�ʱ��
		
		//3.��λ
		TIME_BASE = 0;
		P1 = 0xFF;
		dula = 1;
		P0 = table[16];
		dula = 0;
	}
}


/* ��ʼ������ */
void init()
{
	/* ��ʼ�������� */
	dula = 0;
	wela = 0;
	
	/* ��ʼ����ʱ��1 */
	//���ö�ʱ��1Ϊ������ʽ2����ʱ��0Ϊ������ʽ1
	TMOD = 0x21;
	//����ʱ��1װ��ֵ��������Ϊ9600bps
	TH1 = 0xFD;
	TL1 = 0xFD;
	//������ʱ��1
	TR1 = 1;
	
	/* ��ʼ����ʱ��0 */
//	TMOD = 0x01;	//���ö�ʱ��0������ʽ
	TH0 = (65536-922)/256;	//����ֵ�ĸ�λ��ֵ ��ʱ1ms ����11.0592MHZ
	TL0 = (65536-922)%256;	//����ֵ�ĵ�λ��ֵ
	EA = 1;		//�����ж�
	ET0 = 1;	//����ʱ��0�ж�
	TR0 = 0;	//�رն�ʱ��0
	TIME_BASE = 0;	//��ʼ������TIME_BASE

	/* ��ʼ������ */
	//���ô���Ϊ������ʽ1
	SM0 = 0;
	SM1 = 1;
	//�����ڽ�������
	REN = 1;
}



/* ����ܶ�̬��ʾ���� */
void display(uint number)
{
	uchar qian;
	uchar bai;
	uchar shi;
	uchar ge;
	
	if (number>999)
	{
		qian = number/1000;
		bai = number%1000/100;
		shi = number%1000%100/10;
		ge = number%10;
		
		//ǧλ
		dula = 1;
		P0 = table[qian];
		dula = 0;
		P0 = 0xFF;	//��Ӱ
		wela = 1;
		P0 = 0xFE;
		wela = 0;
		delay(1);
		
		//��λ
		dula = 1;
		P0 = table[bai];
		dula = 0;
		P0 = 0xFF;	//��Ӱ
		wela = 1;
		P0 = 0xFD;
		wela = 0;
		delay(1);
		
		//ʮλ
		dula = 1;
		P0 = table[shi];
		dula = 0;
		P0 = 0xFF;	//��Ӱ
		wela = 1;
		P0 = 0xFB;
		wela = 0;
		delay(1);
		
		//��λ
		dula = 1;
		P0 = table[ge];
		dula = 0;
		P0 = 0xFF;	//��Ӱ
		wela = 1;
		P0 = 0xF7;
		wela = 0;
		delay(1);
	}
	
	else if (number>99)
	{
		bai = number/100;
		shi = number%100/10;
		ge = number%10;
		
		//��λ
		dula = 1;
		P0 = table[bai];
		dula = 0;
		P0 = 0xFF;	//��Ӱ
		wela = 1;
		P0 = 0xFE;
		wela = 0;
		delay(1);
		
		//ʮλ
		dula = 1;
		P0 = table[shi];
		dula = 0;
		P0 = 0xFF;	//��Ӱ
		wela = 1;
		P0 = 0xFD;
		wela = 0;
		delay(1);
		
		//��λ
		dula = 1;
		P0 = table[ge];
		dula = 0;
		P0 = 0xFF;	//��Ӱ
		wela = 1;
		P0 = 0xFB;
		wela = 0;
		delay(1);
	}
	
	else if (number>9)
	{
		shi = number/10;
		ge = number%10;
		
		//ʮλ
		dula = 1;
		P0 = table[shi];
		dula = 0;
		P0 = 0xFF;	//��Ӱ
		wela = 1;
		P0 = 0xFE;
		wela = 0;
		delay(1);
		
		//��λ
		dula = 1;
		P0 = table[ge];
		dula = 0;
		P0 = 0xFF;	//��Ӱ
		wela = 1;
		P0 = 0xFD;
		wela = 0;
		delay(1);
	}
	
	else
	{
		dula = 1;
		P0 = table[number];
		dula = 0;
		P0 = 0xFF;	//��Ӱ
		wela = 1;
		P0 = 0xFE;
		wela = 0;
		delay(1);
	}
}


/* ��ʱ���� */
void delay(uint time)
{
	uint x,y;
	for (x=time; x>0; x--)
		for (y=114; y>0; y--);
}


/* ��ʱ���жϷ������ */
void Time0() interrupt 1
{
	TH0 = (65536-922)/256;	//��װ��ֵ
	TL0 = (65536-922)%256;
	TIME_BASE++;	//ÿ��1ms��TIME_BASE��1
}