#ifndef __EEPRAM_H__
#define __EEPRAM_H__

//typedef unsigned char BYTE;
//typedef unsigned int WORD;

//-----------------------------------------------

//sfr IAP_DATA    =   0xC2;           //IAP���ݼĴ���
//sfr IAP_ADDRH   =   0xC3;           //IAP��ַ�Ĵ������ֽ�
//sfr IAP_ADDRL   =   0xC4;           //IAP��ַ�Ĵ������ֽ�
//sfr IAP_CMD     =   0xC5;           //IAP����Ĵ���
//sfr IAP_TRIG    =   0xC6;           //IAP������Ĵ���
//sfr IAP_CONTR   =   0xC7;           //IAP���ƼĴ���

#define CMD_IDLE    0               //����ģʽ
#define CMD_READ    1               //IAP�ֽڶ�����
#define CMD_PROGRAM 2               //IAP�ֽڱ������
#define CMD_ERASE   3               //IAP������������

//#define ENABLE_IAP 0x80           //if SYSCLK<30MHz
//#define ENABLE_IAP 0x81           //if SYSCLK<24MHz
#define ENABLE_IAP  0x82            //if SYSCLK<20MHz
//#define ENABLE_IAP 0x83           //if SYSCLK<12MHz
//#define ENABLE_IAP 0x84           //if SYSCLK<6MHz
//#define ENABLE_IAP 0x85           //if SYSCLK<3MHz
//#define ENABLE_IAP 0x86           //if SYSCLK<2MHz
//#define ENABLE_IAP 0x87           //if SYSCLK<1MHz

//���Ե�ַ
#define IAP_ADDRESS 0x0400

extern void Delay(unsigned char n);
extern void IapIdle();
extern unsigned char IapReadByte(unsigned int addr);
extern void IapProgramByte(unsigned int addr, unsigned char dat);
extern void IapEraseSector(unsigned int addr);
extern void eep_cachu();
#endif