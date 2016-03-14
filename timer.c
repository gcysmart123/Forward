#include "timer.h"
#include "ev1527.h"
#include "stc15.h"

unsigned char await_number = 0;      //����ʱ�̼���50MS��������
unsigned char await_number_table = 0;//0.5���־����

unsigned char main_press_time_table = 0;//main����ʱ���������־λ
unsigned char main_press_time = 0;

unsigned char again_and_again_time = 0;// �ж��ظ���������Ҫ�ļ���ʱ�����

unsigned char logout_cycle_number = 0; //���� ѭ�� ���������Լ���־λ
unsigned char logout_cycle_table = 0;

unsigned char return_standby_time = 0;//һ��ʱ��δ����  ���ش�������

unsigned char second_times = 0;

unsigned char fd_table = 0;

unsigned char filter_main = 0;

unsigned int  send_delay = 0;			//����ʱ���ۼӼ�����7500Ϊ0.8s��

unsigned char send_start;				//���Ϳ�ʼ��־λ
unsigned char delay_time;				//ֹͣ ��ʱʱ��
unsigned char send_time = 1;			//����ʱ��
unsigned char flag_Pattern= 0;			/*����ģʽ ��־
											0��ֻ���� 
											1�����ͣ�0.8s��
											2�����ղ�������ʱ*/

unsigned char times = 2;					//Ԥ��������־
unsigned char send_times = 0;			//�Ѿ����ʹ���

//unsigned char send_end;				//����ֹͣ��־
unsigned char received_end;				//��=����ֹͣ��־

unsigned int waite_time_s = 20;			//����ʱ��
unsigned char waite_end = 0;			//���������־

unsigned char repeat_time = 120;

void Init_Timer0(void) 
{
	TMOD |= 0x01;	  //ʹ��ģʽ1��16λ��ʱ����ʹ��"|"���ſ�����ʹ�ö����ʱ��ʱ����Ӱ��	
	TH0 = (65536 - 100) >> 8; //���¸�ֵ 100us
	TL0 = (65536 - 100) & 0xff;
	EA = 1;            //���жϴ�
	ET0 = 1;           //��ʱ���жϴ�
	//TR1=1;           //��ʱ�����ش�
}

void Timer0_isr(void) interrupt 1  //��ʱ��1�жϷ������
{
	TF0 = 0;
	TH0 = (65536 - 100) >> 8;		  //���¸�ֵ 100us
	TL0 = (65536 - 100) & 0xff;
	if (flag_Pattern == 1)
	{
		send_delay++;
		if (send_delay == 7500)
		{
			send_delay = 0;
			LED_G = 1;
			LED_R = 0;
			send_start = 0;

		}
	}
	else
	{
		RF_decode_main();
	}
}

void clear_return_standby_time(void)
{
	return_standby_time = 0;
}