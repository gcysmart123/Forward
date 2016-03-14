/*---------------------------------------------------------------------*/
/* --- STC MCU Limited ------------------------------------------------*/
/* --- STC15F4K60S4 系列 内部EEPROM举例--------------------------------*/
/* --- Mobile: (86)13922805190 ----------------------------------------*/
/* --- Fax: 86-0513-55012956,55012947,55012969 ------------------------*/
/* --- Tel: 86-0513-55012928,55012929,55012966-------------------------*/
/* --- Web: www.STCMCU.com --------------------------------------------*/
/* --- Web: www.GXWMCU.com --------------------------------------------*/
/* 如果要在程序中使用此代码,请在程序中注明使用了STC的资料及程序        */
/* 如果要在文章中应用此代码,请在文章中注明使用了STC的资料及程序        */
/*---------------------------------------------------------------------*/

//本示例在Keil开发环境下请选择Intel的8058芯片型号进行编译
//若无特别说明,工作频率一般为11.0592MHz


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
	Delay(10);                      //延时
	IapEraseSector(IAP_ADDRESS);    //扇区擦除
    for (i=0; i<512; i++)           //检测是否擦除成功(全FF检测)
    {
        if (IapReadByte(IAP_ADDRESS+i) != 0xff)
            goto Error;             //如果出错,则退出
    }
Error:
	 IapEraseSector(IAP_ADDRESS);    //扇区擦除
}
//void main()
//{
//    WORD i;
//
//    P1 = 0xfe;                      //1111,1110 系统OK
//    Delay(10);                      //延时
//
//    IapEraseSector(IAP_ADDRESS);    //扇区擦除
//    for (i=0; i<512; i++)           //检测是否擦除成功(全FF检测)
//    {
//        if (IapReadByte(IAP_ADDRESS+i) != 0xff)
//            goto Error;             //如果出错,则退出
//    }
//    P1 = 0xfc;                      //1111,1100 擦除成功
//    Delay(10);                      //延时
//
//    for (i=0; i<512; i++)           //编程512字节
//    {
//        IapProgramByte(IAP_ADDRESS+i, (BYTE)i);
//    }
//    P1 = 0xf8;                      //1111,1000 编程完成
//    Delay(10);                      //延时
//
//    for (i=0; i<512; i++)           //校验512字节
//    {
//        if (IapReadByte(IAP_ADDRESS+i) != (BYTE)i)
//            goto Error;             //如果校验错误,则退出
//    }
//    P1 = 0xf0;                      //1111,0000 测试完成
//    while (1);
//Error:
//    P1 &= 0x7f;                     //0xxx,xxxx IAP操作失败
//    while (1);
//}

/*----------------------------
软件延时
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
关闭IAP
----------------------------*/
void IapIdle()
{
    IAP_CONTR = 0;                  //关闭IAP功能
    IAP_CMD = 0;                    //清除命令寄存器
    IAP_TRIG = 0;                   //清除触发寄存器
    IAP_ADDRH = 0x80;               //将地址设置到非IAP区域
    IAP_ADDRL = 0;
}

/*----------------------------
从ISP/IAP/EEPROM区域读取一字节
----------------------------*/
unsigned char IapReadByte(unsigned int addr)
{
	unsigned char dat;                       //数据缓冲区

    IAP_CONTR = ENABLE_IAP;         //使能IAP
    IAP_CMD = CMD_READ;             //设置IAP命令
    IAP_ADDRL = addr;               //设置IAP低地址
    IAP_ADDRH = addr >> 8;          //设置IAP高地址
    IAP_TRIG = 0x5a;                //写触发命令(0x5a)
    IAP_TRIG = 0xa5;                //写触发命令(0xa5)
    _nop_();                        //等待ISP/IAP/EEPROM操作完成
    dat = IAP_DATA;                 //读ISP/IAP/EEPROM数据
    IapIdle();                      //关闭IAP功能

    return dat;                     //返回
}

/*----------------------------
写一字节数据到ISP/IAP/EEPROM区域
----------------------------*/
void IapProgramByte(unsigned int addr, unsigned char dat)
{
    IAP_CONTR = ENABLE_IAP;         //使能IAP
    IAP_CMD = CMD_PROGRAM;          //设置IAP命令
    IAP_ADDRL = addr;               //设置IAP低地址
    IAP_ADDRH = addr >> 8;          //设置IAP高地址
    IAP_DATA = dat;                 //写ISP/IAP/EEPROM数据
    IAP_TRIG = 0x5a;                //写触发命令(0x5a)
    IAP_TRIG = 0xa5;                //写触发命令(0xa5)
    _nop_();                        //等待ISP/IAP/EEPROM操作完成
    IapIdle();
}

/*----------------------------
扇区擦除
----------------------------*/
void IapEraseSector(unsigned int addr)
{
    IAP_CONTR = ENABLE_IAP;         //使能IAP
    IAP_CMD = CMD_ERASE;            //设置IAP命令
    IAP_ADDRL = addr;               //设置IAP低地址
    IAP_ADDRH = addr >> 8;          //设置IAP高地址
    IAP_TRIG = 0x5a;                //写触发命令(0x5a)
    IAP_TRIG = 0xa5;                //写触发命令(0xa5)
    _nop_();                        //等待ISP/IAP/EEPROM操作完成
    IapIdle();
}

