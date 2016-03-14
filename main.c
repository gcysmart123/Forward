#include "stc15.h"
#include "ev1527.h"
#include "timer.h"
#include "timer_2.h"
#include "pca.h"
#include "memu.h"
#include "FUNCTION.h"
#include "delay.h"
#include "eepram.h"

unsigned char eep_dat[6]={0};
void main ()
{
	unsigned char j;
	Init_Timer0();

	Init_Timer2();
		
	exint0_init();

 	pca_timer_init();

	P3M1 = 0X04;			//设置 P3.2为高阻状态 否则无法解码 P3.5为推挽输出 否则无法发出信号
	P3M0 = 0X21;

	P1M1 = 0X00;			
	P1M0 = 0XFF;

	P5M0 = 0X30;
	P5M1 = 0X00;

	LED_G = 1;
	LED_R = 0;
	P35 = 0;
		for(j=0;j<6;j++)
	{
		eep_dat[j]=IapReadByte(IAP_ADDRESS+j);
	}
		
	f_num_3_h = eep_dat[0];
	f_num_3_l = eep_dat[1];

	f_num_4_h = eep_dat[2];
	f_num_4_l = eep_dat[3];

	f_num_5_h = eep_dat[4];
	f_num_5_l = eep_dat[5];
	if(f_num_3_h==0xff)
	{
		f_num_3_h = 0;
		f_num_3_l = 1;
	
		f_num_4_h = 0;
		f_num_4_l = 6;
	
		f_num_5_h = 0;
		f_num_5_l = 6;

		eep_dat[0]=	f_num_3_h;
		eep_dat[1]= f_num_3_l;
		
		eep_dat[2]= f_num_4_h; 
		eep_dat[3]= f_num_4_l; 
		
		eep_dat[4]= f_num_5_h; 
		eep_dat[5]= f_num_5_l; 

			eep_cachu();
			for(j=0;j<6;j++)
			{
				IapProgramByte(IAP_ADDRESS+j,eep_dat[j]);
			}
	}
		

 	while(1)
	{  		
		function();
		if(eep_dat[0]!=f_num_3_h||eep_dat[1]!=f_num_3_l)
		{
			eep_dat[0]=	f_num_3_h;
			eep_dat[1]= f_num_3_l;
		
			eep_dat[2]= f_num_4_h; 
			eep_dat[3]= f_num_4_l; 
		
			eep_dat[4]= f_num_5_h; 
			eep_dat[5]= f_num_5_l; 

			eep_cachu();
			for(j=0;j<6;j++)
			{
				IapProgramByte(IAP_ADDRESS+j,eep_dat[j]);
			}
		}
		memu();
	
	}
}