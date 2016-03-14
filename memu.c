#include "stc15.h"
#include "ev1527.h"
#include "timer.h"
#include "pca.h"
#include "intrins.h"
#include "timer_2.h"
#include "out.h"
#include "memu.h"
#include "FUNCTION.h"
#include "debug.h"

char num = 0;
unsigned char send_continue =0 ; 
unsigned char decode_success =0 ;		//�����������Ч �����˸��־

unsigned char i;
void memu()
{	
		 
		switch (flag_Pattern)
		{
		case 0:		//���� ���� 
			receive_rf_decoder();	//���뺯��
			if (return_again_receive_rf_decoder_finished() == 1) //��־λ����1 ˵����2�μ�����ͨ��,���յ���Ч��
			{	
				clear_again_receive_rf_decoder_finished();//�����־λ
				if (num < 40)
				{
					decode_success = 1;
					shanshuo = 0;

					old2_RF_RECE_REG_SAVE[0][num] = old2_RF_RECE_REG[0];
					old2_RF_RECE_REG_SAVE[1][num] = old2_RF_RECE_REG[1];
					old2_RF_RECE_REG_SAVE[2][num] = old2_RF_RECE_REG[2];
					num++;
				}
				flag_Pattern = 3;
			}
			break;
		case 1:
			LED_G = 0;
			LED_R = 1;
			out();	 //����old2_RF_RECE_REG_SAVE[0][0]��
						 //	   old2_RF_RECE_REG_SAVE[1][0]��
						 //	   old2_RF_RECE_REG_SAVE[2][0]��
						 //	   ������ ����0.8s

			if (send_times==times)
			{
				LED_R = 0;
				send_times = 0;	
				if(num==1)
				{
					for (i = 0; i < num; i++)
					{
						old2_RF_RECE_REG_SAVE[0][i] = old2_RF_RECE_REG_SAVE[0][i + 1];
						old2_RF_RECE_REG_SAVE[1][i] = old2_RF_RECE_REG_SAVE[1][i + 1];
						old2_RF_RECE_REG_SAVE[2][i] = old2_RF_RECE_REG_SAVE[2][i + 1];
					}
					num--;
					LED_R = 0;
					flag_Pattern = 0;
					
				}
				else
				{
					for (i = 0; i < num; i++)
						{
							old2_RF_RECE_REG_SAVE[0][i] = old2_RF_RECE_REG_SAVE[0][i + 1];
							old2_RF_RECE_REG_SAVE[1][i] = old2_RF_RECE_REG_SAVE[1][i + 1];
							old2_RF_RECE_REG_SAVE[2][i] = old2_RF_RECE_REG_SAVE[2][i + 1];
						}
					num--;
					flag_Pattern = 3;
					send_continue = 1;
					
					//LED_R = 0;
				}
				
				//flag_Pattern = 1;
			}
			else
			{
				flag_Pattern = 2;	//��ʱ 1.2s  2.2s  3.2s����������
			}

						
			break;
		case 2:			 //��ʱ 1.2s  2.2s  3.2s����������
			
			receive_rf_decoder();	//���뺯��
			if (return_again_receive_rf_decoder_finished() == 1) //��־λ����1 ˵����2�μ�����ͨ��,���յ���Ч��
			{
				clear_again_receive_rf_decoder_finished();//�����־λ

				if (num < 40)
				{
					decode_success = 1;
					shanshuo = 0;

					old2_RF_RECE_REG_SAVE[0][num] = old2_RF_RECE_REG[0];
					old2_RF_RECE_REG_SAVE[1][num] = old2_RF_RECE_REG[1];
					old2_RF_RECE_REG_SAVE[2][num] = old2_RF_RECE_REG[2];
					num++;
				}
			}

			if (received_end == 1)	//��ʱ������׼
			{
				received_end = 0;
				flag_Pattern = 1;
			}
			break;
		case 3:
			receive_rf_decoder();	//���뺯��
			if (return_again_receive_rf_decoder_finished() == 1) //��־λ����1 ˵����2�μ�����ͨ��,���յ���Ч��
			{
				clear_again_receive_rf_decoder_finished();//�����־λ
				if (num < 40)
				{
					decode_success = 1;
					shanshuo = 0;

					old2_RF_RECE_REG_SAVE[0][num] = old2_RF_RECE_REG[0];
					old2_RF_RECE_REG_SAVE[1][num] = old2_RF_RECE_REG[1];
					old2_RF_RECE_REG_SAVE[2][num] = old2_RF_RECE_REG[2];
					num++;
				}
			}

			if (waite_end == 1)	//��ʱ������־
			{
				waite_end = 0;
				flag_Pattern = 1;
			}
		default:
			break;
		}
	
	
	}