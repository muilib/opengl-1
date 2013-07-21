#ifndef _CBMPLOADER_H_
#define _CBMPLOADER_H_
#include"stadafx.h"
#define BITMAP_ID 0x4D42  //λͼ�ļ���־
class CbmpLoader
{
public:
	CbmpLoader();
	~CbmpLoader();
	bool LoadBitmap(const char* file); //����һ��bmp�ļ�            
	void FreeImage();               //�ͷ�ͼ������
	bool Load(const char* fileName);//����λͼ����������
	unsigned int ID;                //��������ID��
	int imageWidth;                 //ͼ����
	int imageHeight;                //ͼ��߶�
	unsigned char* image;           //ָ��ͼ������ָ��
};
#endif