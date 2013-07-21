#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "stadafx.h"
#include"Vector.h"
#include"3Dmath.h"
#include"Cplane.h"
class Camera
{
public:
	
	/** ���캯������������ */
	Camera();
	~Camera();
	void DrawLine();
	/** ��������״̬���� */
	Vector3 getPosition()   {	return m_Position;		}
	Vector3 getView()	    {	return m_View;			}
	Vector3 getUpVector()   {	return m_UpVector;		}
	float   getSpeed()      {   return m_Speed;         }

	/** �����ٶ� */
	void setSpeed(float speed)
	{ 
		m_Speed  = speed;
	}
     
	/** �����������λ��, �۲����������� */
	void setCamera(float positionX, float positionY, float positionZ,
			 	   float viewX,     float viewY,     float viewZ,
				   float upVectorX, float upVectorY, float upVectorZ);


	
	/** ��ת��������� */
	void rotateView(float angle, float X, float Y, float Z);

	/** �����������������۲췽�� */
	void setViewByMouse(); 
	
    /** ����������ƶ� */
	void yawCamera(float speed);

	/** ǰ���ƶ������ */
	void moveCamera(float speed);
	
	/** ��������� */
	void setLook();
	
    //�õ������ָ��
	int    count;
	static Camera* GetCamera(void) { return m_pCamera;}
    void   CheckCameraCollision(Vector3 *pVertices, int numOfVerts);
	void   SetCameraradius(float radius){m_radius=radius;}
private:
	/** ��������� */
	static Camera  *m_pCamera;     /**< ��ǰȫ�������ָ�� */
	Vector3        m_Position;      /**< λ�� */
	Vector3        m_View;          /**< ���� */
	Vector3        m_UpVector;      /**< �������� */
	float          m_Speed;         /**< �ٶ� */
	float          m_radius;       //������뾶
	//Colide         colide;
	//Cdraw          draw;
	Cplane         plane;
};

#endif //__CAMERA_H__