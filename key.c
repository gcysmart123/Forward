#include "STC15.h"
#include "delay.h"
#include "FUNCTION.h"
#include "debug.h"
#include "timer_2.h"

#define KEY_EST  	P37
#define KEY_UP   	P36
#define KEY_DOWN 	P34
#define KEY_ESC 	P33
//unsigned char u;

//void display (unsigned char LED_H,unsigned char LED_L);
unsigned char memu_dispaly_time_start = 0;			//�˵���ʾʱ���ʱ��ʼ��־

void key()
{ 

	if (!KEY_EST)  //�����⵽�͵�ƽ��˵����������
	{
		DelayMs(); //��ʱȥ����һ��10-20ms
		if (!KEY_EST)     //�ٴ�ȷ�ϰ����Ƿ��£�û�а������˳�
		{
			while (!KEY_EST);//���ȷ�ϰ��°����ȴ������ͷţ�û���ͷ���һֱ�ȴ�
			{
				
				memu_count++;
				switch (memu_count)
				{
				case 1:
					H = 11;
					L = 1;
					f_num = L;
					break;
				case 2:
					if (f_num == 1)
					{
						H = f_num_3_h;
						L = f_num_3_l;
					}
					else if (f_num == 2)
					{
						H = f_num_4_h;
						L = f_num_4_l;
					}
					else
					{
						H = f_num_5_h;
						L = f_num_5_l;
					}

					break;
				case 3:
					memu_count = 0;
					H = L = 12;
					break;
				default:
					break;//Ĭ�ϵ�break
				}
#if DEBUG_FANHUI
				memu_dispaly_time_start = 1;
				memu_dispaly_time = 0;
#endif
			}
		}
		//display(H,L);
	}


	if (!KEY_UP)  //�����⵽�͵�ƽ��˵����������
	{
		DelayMs(); //��ʱȥ����һ��10-20ms
		if (!KEY_UP)     //�ٴ�ȷ�ϰ����Ƿ��£�û�а������˳�
		{
			while (!KEY_UP);//���ȷ�ϰ��°����ȴ������ͷţ�û���ͷ���һֱ�ȴ�
			{
				switch (memu_count)
				{
				case 1:
					f_num++;
					if (f_num == 4)
					{
						f_num = 1;
					}
					L = f_num;
					break;
				case 2:
					switch (f_num)
					{
					case 1:
						if (L == 9)L = 0;
						else L++;

						f_num_3_h = H;
						f_num_3_l = L;
						break;
					case 2:
						L++;
						if (L >= 10)
						{
							L = L % 10;
							H++;
							if (H >= 10)
							{
								H = 0;
								L = 0;
							}/*
							L = L % 10;
							H++;*/
						}

						f_num_4_h = H;
						f_num_4_l = L;
						break;
					case 3:
						L++;
						if (L >= 10)
						{
							L = L % 10;
							H++;
							if (H >= 10)
							{
								H = 0;
								L = 0;
							}/*
							L = L % 10;
							H++;*/
						}

						f_num_5_h = H;
						f_num_5_l = L;
						break;
					}
					break;
				default:
					break;
				}
#if DEBUG_FANHUI
				memu_dispaly_time_start = 1;
				memu_dispaly_time = 0;
#endif
			}
		}
		//display(H,L);
	}


	if (!KEY_DOWN)  //�����⵽�͵�ƽ��˵����������
	{
		DelayMs(); //��ʱȥ����һ��10-20ms
		if (!KEY_DOWN)     //�ٴ�ȷ�ϰ����Ƿ��£�û�а������˳�
		{
			while (!KEY_DOWN);//���ȷ�ϰ��°����ȴ������ͷţ�û���ͷ���һֱ�ȴ�
			{
				switch (memu_count)
				{
				case 1:
					f_num--;
					if (f_num == 0)
					{
						f_num = 3;
					}
					L = f_num;
					break;
				case 2:
					switch (f_num)
					{
					case 1:
						if (L==0)
							L = 9;
						else L--;

						f_num_3_h = H;
						f_num_3_l = L;
						break;
					case 2:
						if (L == 0)
						{
							if (H == 0)
							{
								H = 9;
								L = 9;
							}
							else
							{
								H--;
								L = 9;
							}
						}
						else
							L--;

						f_num_4_h = H;
						f_num_4_l = L;

						break;
					case 3:
						if (L == 0)
						{
							if (H == 0)
							{
								H = 9;
								L = 9;
							}
							else
							{
								H--;
								L = 9;
							}
						}
						else
							L--;

						f_num_5_h = H;
						f_num_5_l = L;
						break;

					}
					break;

				default:
					break;//Ĭ�ϵ�break
				}
#if DEBUG_FANHUI
				memu_dispaly_time_start = 1;
				memu_dispaly_time = 0;
#endif
			}
		}
		//display(H,L);
	}


	if (!KEY_ESC)  //�����⵽�͵�ƽ��˵����������
	{
		DelayMs(); //��ʱȥ����һ��10-20ms
		if (!KEY_ESC)     //�ٴ�ȷ�ϰ����Ƿ��£�û�а������˳�
		{
			while (!KEY_ESC);//���ȷ�ϰ��°����ȴ������ͷţ�û���ͷ���һֱ�ȴ�
			{
				if (memu_count == 0)
				{
					memu_count = 0;
				}
				else
					memu_count--;
				switch (memu_count)
				{
				case 0:
					H = 12;
					L = 12;
					break;
				case 1:
					H = 11;
					L = f_num;
					break;
				default:
					break;//Ĭ�ϵ�break
				}
#if DEBUG_FANHUI
				memu_dispaly_time_start = 1;
				memu_dispaly_time = 0;
#endif
			}
		}
	}
	//display(H,L);
}
