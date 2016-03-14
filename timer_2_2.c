
#include "stc15.h"
#include "timer_2.h"
#include "timer.h"
#include "debug.h"
#include "memu.h"
#include "key.h"
#include "FUNCTION.h"

unsigned int waite_time = 0;
unsigned char shanshuo = 0;				//���� �����˸����
#if DEBUG_FANHUI
unsigned char memu_dispaly_time = 0;	//����100Ϊ5s ����ܻظ���- -��
#endif

//#define T1MS (65536-FOSC/1000)      //1Tģʽ
#define T1MS (65536-50000) //12Tģʽ

//�жϷ������
void t2int() interrupt 12           //�ж����
{
#if DEBUG
	if (flag_Pattern == 3)
	{
		if (send_continue==0)
		{
			waite_time++;
			if (waite_time == waite_time_s)
			{
				waite_time = 0;
				waite_end = 1;

			}
		}
		else
		{
			waite_time++;
			if (waite_time == 20)
			{
				send_continue = 0;
				waite_time = 0;
				waite_end = 1;

			}
		}
#if DEBUG_SHANSHUO
		if (decode_success == 1)
		{
			LED_R = !LED_R;
			shanshuo++;
			if (shanshuo == 2)
			{
				decode_success = 0;
			}
		}
#endif
#if DEBUG_FANHUI
		if (memu_dispaly_time_start == 1)
		{
			memu_dispaly_time++;
			if (memu_dispaly_time == 100)
			{
				memu_dispaly_time_start = 0;
				memu_dispaly_time = 0;
				H = 12;
				L = 12;
				memu_count = 0;
			}
			//	return;
		}
#endif
	}
	else
	{
		waite_time = 0;
#if DEBUG_SHANSHUO
		if (decode_success == 1)
		{
			LED_R = !LED_R;
			shanshuo++;
			if (shanshuo == 2)
			{
				decode_success = 0;
			}
		}
#endif
#if DEBUG_FANHUI
		if (memu_dispaly_time_start == 1)
		{
			memu_dispaly_time++;
			if (memu_dispaly_time == 100)
			{
				memu_dispaly_time_start = 0;
				memu_dispaly_time = 0;
				H = 12;
				L = 12;
				memu_count = 0;
			}
			//	return;
		}
#endif
	}
#endif
	//  IE2 &= ~0x04;                   //����Ҫ�ֶ�����жϱ�־,���ȹر��ж�,��ʱϵͳ���Զ�����ڲ����жϱ�־
	//  IE2 |= 0x04;                    //Ȼ���ٿ��жϼ���
}

//-----------------------------------------------

/* main program */
void Init_Timer2()
{
//    AUXR |= 0x04;                   //��ʱ��2Ϊ1Tģʽ
  AUXR &= ~0x04;                  //��ʱ��2Ϊ12Tģʽ
    T2L = T1MS;                     //��ʼ����ʱֵ
    T2H = T1MS >> 8;
    AUXR |= 0x10;                   //��ʱ��2��ʼ��ʱ
    
	IE2 |= 0x04;			 //����ʱ���ж�
   

    
}

