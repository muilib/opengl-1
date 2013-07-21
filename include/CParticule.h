#ifndef _CPARTICULE_H_
#define _CPARTICULE_H_
#include"Vector.h"
struct tParticule{
	Vector3    m_pos;              // λ��
	Vector3    m_velocity;               //�ٶ�
	Vector3    m_acceleration;          //���ٶ�
	float      m_lifetime;             //����ֵ
	float      m_dec;                     //��ʧ������
	float      m_size;                  //�ߴ�
	float      m_color[3];              //��ɫ
};
class CParticule
{
public:
	CParticule();
	virtual bool Init(int num);
	virtual void Upadate();
	virtual void Render();
	virtual ~CParticule();
protected:
	tParticule *m_parlist;                 //����ָ��
	int        m_pnum;                   //������Ŀ
};
#endif       _CPARTICULE_H_