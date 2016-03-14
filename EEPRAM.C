/*---------------------------------------------------------------------*/
/* --- STC MCU Limited ------------------------------------------------*/
/* --- STC15F4K60S4 ϵ�� �ڲ�EEPROM����--------------------------------*/
/* --- Mobile: (86)13922805190 ----------------------------------------*/
/* --- Fax: 86-0513-55012956,55012947,55012969 ------------------------*/
/* --- Tel: 86-0513-55012928,55012929,55012966-------------------------*/
/* --- Web: www.STCMCU.com --------------------------------------------*/
/* --- Web: www.GXWMCU.com --------------------------------------------*/
/* ���Ҫ�ڳ�����ʹ�ô˴���,���ڳ�����ע��ʹ����STC�����ϼ�����        */
/* ���Ҫ��������Ӧ�ô˴���,����������ע��ʹ����STC�����ϼ�����        */
/*---------------------------------------------------------------------*/

//��ʾ����Keil������������ѡ��Intel��8058оƬ�ͺŽ��б���
//�����ر�˵��,����Ƶ��һ��Ϊ11.0592MHz


//#include "reg51.h"
#include "intrins.h"
#include "stc15.h"
#include "eepram.h"

void Delay(unsigned char n);
void IapIdle();
unsigned char IapReadByte(unsigned int addr);
void IapProgramByte(unsigned int addr, unsigned char dat);
void IapEraseSector(unsigned int addr);

void eep_cachu()
{
	unsigned int i;
	Delay(10);                      //��ʱ
	IapEraseSector(IAP_ADDRESS);    //��������
    for (i=0; i<512; i++)           //����Ƿ�����ɹ�(ȫFF���)
    {
        if (IapReadByte(IAP_ADDRESS+i) != 0xff)
            goto Error;             //�������,���˳�
    }
Error:
	 IapEraseSector(IAP_ADDRESS);    //��������
}
//void main()
//{
//    WORD i;
//
//    P1 = 0xfe;                      //1111,1110 ϵͳOK
//    Delay(10);                      //��ʱ
//
//    IapEraseSector(IAP_ADDRESS);    //��������
//    for (i=0; i<512; i++)           //����Ƿ�����ɹ�(ȫFF���)
//    {
//        if (IapReadByte(IAP_ADDRESS+i) != 0xff)
//            goto Error;             //�������,���˳�
//    }
//    P1 = 0xfc;                      //1111,1100 �����ɹ�
//    Delay(10);                      //��ʱ
//
//    for (i=0; i<512; i++)           //���512�ֽ�
//    {
//        IapProgramByte(IAP_ADDRESS+i, (BYTE)i);
//    }
//    P1 = 0xf8;                      //1111,1000 ������
//    Delay(10);                      //��ʱ
//
//    for (i=0; i<512; i++)           //У��512�ֽ�
//    {
//        if (IapReadByte(IAP_ADDRESS+i) != (BYTE)i)
//            goto Error;             //���У�����,���˳�
//    }
//    P1 = 0xf0;                      //1111,0000 �������
//    while (1);
//Error:
//    P1 &= 0x7f;                     //0xxx,xxxx IAP����ʧ��
//    while (1);
//}

/*----------------------------
������ʱ
----------------------------*/
void Delay(unsigned char n)
{
	unsigned int x;

    while (n--)
    {
        x = 0;
        while (++x);
    }
}

/*----------------------------
�ر�IAP
----------------------------*/
void IapIdle()
{
    IAP_CONTR = 0;                  //�ر�IAP����
    IAP_CMD = 0;                    //�������Ĵ���
    IAP_TRIG = 0;                   //��������Ĵ���
    IAP_ADDRH = 0x80;               //����ַ���õ���IAP����
    IAP_ADDRL = 0;
}

/*----------------------------
��ISP/IAP/EEPROM�����ȡһ�ֽ�
----------------------------*/
unsigned char IapReadByte(unsigned int addr)
{
	unsigned char dat;                       //���ݻ�����

    IAP_CONTR = ENABLE_IAP;         //ʹ��IAP
    IAP_CMD = CMD_READ;             //����IAP����
    IAP_ADDRL = addr;               //����IAP�͵�ַ
    IAP_ADDRH = addr >> 8;          //����IAP�ߵ�ַ
    IAP_TRIG = 0x5a;                //д��������(0x5a)
    IAP_TRIG = 0xa5;                //д��������(0xa5)
    _nop_();                        //�ȴ�ISP/IAP/EEPROM�������
    dat = IAP_DATA;                 //��ISP/IAP/EEPROM����
    IapIdle();                      //�ر�IAP����

    return dat;                     //����
}

/*----------------------------
дһ�ֽ����ݵ�ISP/IAP/EEPROM����
----------------------------*/
void IapProgramByte(unsigned int addr, unsigned char dat)
{
    IAP_CONTR = ENABLE_IAP;         //ʹ��IAP
    IAP_CMD = CMD_PROGRAM;          //����IAP����
    IAP_ADDRL = addr;               //����IAP�͵�ַ
    IAP_ADDRH = addr >> 8;          //����IAP�ߵ�ַ
    IAP_DATA = dat;                 //дISP/IAP/EEPROM����
    IAP_TRIG = 0x5a;                //д��������(0x5a)
    IAP_TRIG = 0xa5;                //д��������(0xa5)
    _nop_();                        //�ȴ�ISP/IAP/EEPROM�������
    IapIdle();
}

/*----------------------------
��������
----------------------------*/
void IapEraseSector(unsigned int addr)
{
    IAP_CONTR = ENABLE_IAP;         //ʹ��IAP
    IAP_CMD = CMD_ERASE;            //����IAP����
    IAP_ADDRL = addr;               //����IAP�͵�ַ
    IAP_ADDRH = addr >> 8;          //����IAP�ߵ�ַ
    IAP_TRIG = 0x5a;                //д��������(0x5a)
    IAP_TRIG = 0xa5;                //д��������(0xa5)
    _nop_();                        //�ȴ�ISP/IAP/EEPROM�������
    IapIdle();
}
