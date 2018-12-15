#ifndef __FONTS_H
#define __FONTS_H

#include <stdint.h>

// ������ؽṹ����
typedef struct _pFont
{    
  const uint8_t *table;  //��ģ�����ַ
  uint16_t Width;  //��ģ����
  uint16_t Height; //��ģ����
  uint16_t Sizes;	 //��ģ����
} pFONT;

extern const uint8_t  Chinese_Table[];    	// ���ּ�����
extern const uint8_t  GBK2312_1616_Table[];	// �����ֿ�

extern pFONT Font32;	// 3216 ����
extern pFONT Font24;	// 2412 ����
extern pFONT Font20; // 2010 ����
extern pFONT Font16; // 1608 ����
extern pFONT Font12; // 1206 ����

#endif 
 