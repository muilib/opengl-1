//========================================================
/**
*  @file      Camera.cpp
*
*  ��Ŀ������ ���������
*  �ļ�����:  �������  
*  ����ƽ̨�� Windows98/2000/NT/XP
*  
*  ���ߣ�     WWBOSS
*  �����ʼ�:  wwboss123@gmail.com
*  �������ڣ� 2006-12-06	
*  �޸����ڣ� 2006-12-07
*
*/     
//=======================================================
#include"Camera.h"

Camera* Camera::m_pCamera = NULL;

/** ���캯�� */
Camera::Camera()
{
	/** ��ʼ������ֵ */
	Vector3 zero = Vector3(0.0, 0.0, 0.0);		
	Vector3 view = Vector3(0.0, 0.0, 0.0);		
	Vector3 up   = Vector3(0.0, 0.0, 1.0);		
    
	/** ��ʼ������� */
	m_Position	= zero;					
	m_View		= view;				
	m_UpVector	= up;	
	m_Speed     = 0.1f;
	count=0;
	m_pCamera = this;
}


Camera::~Camera()
{
}

/** �����������λ��,������������� */
void Camera::setCamera( float positionX, float positionY, float positionZ,
				  		float viewX,     float viewY,     float viewZ,
						float upVectorX, float upVectorY, float upVectorZ)
{
	/** �������� */
	Vector3 Position	= Vector3(positionX, positionY, positionZ);
	Vector3 View		= Vector3(viewX, viewY, viewZ);
	Vector3 UpVector	= Vector3(upVectorX, upVectorY, upVectorZ);

	/** ��������� */
	m_Position = Position;	
	m_View     = View;			
	m_UpVector = UpVector;	
}

/**  ��ת���������  */
void Camera::rotateView(float angle, float x, float y, float z)
{
	Vector3 newView;

	/** ���㷽������ */
	Vector3 view = m_View - m_Position;		

	/** ���� sin ��cosֵ */
	float cosTheta = (float)cos(angle);
	float sinTheta = (float)sin(angle);

	/** ������ת������xֵ */
	newView.x  = (cosTheta + (1 - cosTheta) * x * x)		* view.x;
	newView.x += ((1 - cosTheta) * x * y - z * sinTheta)	* view.y;
	newView.x += ((1 - cosTheta) * x * z + y * sinTheta)	* view.z;

	/** ������ת������yֵ */
	newView.y  = ((1 - cosTheta) * x * y + z * sinTheta)	* view.x;
	newView.y += (cosTheta + (1 - cosTheta) * y * y)		* view.y;
	newView.y += ((1 - cosTheta) * y * z - x * sinTheta)	* view.z;

	/** ������ת������zֵ */
	newView.z  = ((1 - cosTheta) * x * z - y * sinTheta)	* view.x;
	newView.z += ((1 - cosTheta) * y * z + x * sinTheta)	* view.y;
	newView.z += (cosTheta + (1 - cosTheta) * z * z)		* view.z;

	/** ����������ķ��� */
	m_View = m_Position + newView;
}

/** �������ת����� */
void Camera::setViewByMouse()
{
	POINT mousePos;									  /**< ���浱ǰ���λ�� */
	int middleX = GetSystemMetrics(SM_CXSCREEN) >> 1; /**< �õ���Ļ��ȵ�һ�� */
	int middleY = GetSystemMetrics(SM_CYSCREEN) >> 1; /**< �õ���Ļ�߶ȵ�һ�� */
	float angleY = 0.0f;							  /**< �����������ת�Ƕ� */
	float angleZ = 0.0f;		                      /**< �����������ת�Ƕ� */					
	static float currentRotX = 0.0f;
	
	/** �õ���ǰ���λ�� */
	GetCursorPos(&mousePos);						
	ShowCursor(false);
	
	/** ������û���ƶ�,���ø��� */
	if( (mousePos.x == middleX) && (mousePos.y == middleY) )
		return;

	/** �������λ������Ļ���� */
	SetCursorPos(middleX, middleY);	
	
	/**< �õ�����ƶ����� */
	angleY = (float)( (middleX - mousePos.x) ) / 1000.0f;		
	angleZ = (float)( (middleY - mousePos.y) ) / 1000.0f;		

    static float lastRotX = 0.0f;      /**< ���ڱ�����ת�Ƕ� */
 	lastRotX = currentRotX; 
	
	/** ���������������ת�Ƕ� */
	currentRotX += angleZ;
 
	/** ���������ת���ȴ���1.0,���ǽ�ȡ��1.0����ת */
	if(currentRotX > 1.0f)     
	{
		currentRotX = 1.0f;
		
		/** ���ݱ���ĽǶ���ת���� */
		if(lastRotX != 1.0f) 
		{
			/** ͨ������ҵ�����ת����ֱ������ */
			Vector3 vAxis = m_View - m_Position;
			vAxis = vAxis.crossProduct(m_UpVector);
			vAxis = vAxis.normalize();
			
			///��ת
			rotateView( 1.0f - lastRotX, vAxis.x, vAxis.y, vAxis.z);
		}
	}
	/** �����ת����С��-1.0,��Ҳ��ȡ��-1.0����ת */
	else if(currentRotX < -1.0f)
	{
		currentRotX = -1.0f;
				
		if(lastRotX != -1.0f)
		{
			
			/** ͨ������ҵ�����ת����ֱ������ */
			Vector3 vAxis = m_View - m_Position;
			vAxis = vAxis.crossProduct(m_UpVector);
			vAxis = vAxis.normalize();
			
			///��ת
			rotateView( -1.0f - lastRotX, vAxis.x, vAxis.y, vAxis.z);
		}
	}
	/** �������תangleZ�� */
	else 
	{	
		/** �ҵ�����ת����ֱ���� */
		Vector3 vAxis = m_View - m_Position;
		vAxis = vAxis.crossProduct(m_UpVector);
		vAxis = vAxis.normalize();
	
		///��ת
		rotateView(angleZ, vAxis.x, vAxis.y, vAxis.z);
	}

	/** ����������ת����� */
	rotateView(angleY, 0, 1, 0);
}


/** �����ƶ������ */
void Camera::yawCamera(float speed)
{
	Vector3 yaw;
	Vector3 cross = m_View - m_Position;
	cross = cross.crossProduct(m_UpVector);

	///��һ������
	yaw = cross.normalize();
 
	m_Position.x += yaw.x * speed;
	m_Position.z += yaw.z * speed;

	m_View.x += yaw.x * speed;
	m_View.z += yaw.z * speed;


}

/** ǰ���ƶ������ */
void Camera::moveCamera(float speed)
{
	/** ���㷽������ */
	Vector3 vector = m_View - m_Position;
	vector = vector.normalize();/**< ��λ�� */

    m_Position.x += vector.x * speed;    /**< �����ٶȸ���λ�� */
	m_Position.z += vector.z * speed;	
	m_Position.y += vector.y * speed;
	
	m_View.x += vector.x * speed;		 /**< �����ٶȸ��·��� */	
	m_View.y += vector.y * speed;
	m_View.z += vector.z * speed;
	

}

/** �����ӵ� */
void Camera::setLook()
{
	
	/** �����ӿ� */
	gluLookAt(m_Position.x, m_Position.y, m_Position.z,	
			  m_View.x,	 m_View.y,     m_View.z,	
			  m_UpVector.x, m_UpVector.y, m_UpVector.z);
}


void Camera::CheckCameraCollision(Vector3 *pVertices, int numOfVerts)
{
   m_radius=(m_Position-m_View).length();
   for(int i = 11; i >= 0; i -= 3)
	{
		// ��ȡ�����ж�������
		Vector3 vTriangle[3] ;
		vTriangle[0]=pVertices[i];
		vTriangle[1]=pVertices[i-1];
		vTriangle[2]=pVertices[i-2];
		Vector3 vLine[2];
		vLine[0]=m_Position;
		vLine[1]=m_View;
		// 1) �ҵ�����������ƽ���ǰ�����ཻ��
		// ��������
		Vector3 vNormal;
        vNormal=Normal(vTriangle);
		// �洢���嵽ƽ��ľ���
		float distance = 0.0f;
		float originDistance=0.0f;
		// ȷ��������ƽ��Ĺ�ϵ
		//if(IntersectedPlane(vTriangle, vLine, vNormal, originDistance))//�߶���ƽ���Ƿ��ཻ)
		//{
			//Vector3 vIntersection=IntersectionPoint(vNormal,  vLine, distance);
		int classification = ClassifySphere(m_Position, vNormal, vTriangle[0], m_radius, distance);
        // ����ཻ������һ�����
		if(classification == INTERSECTS) 
		{
			// 2) �ҵ�ƽ���ϵ�α����

			// ��ƽ�����ҵ��������ĵ�ͶӰ
		    Vector3 vOffset = vNormal * distance;
			Vector3 vIntersection = m_Position-vOffset;
			///�����ڶ�����ڻ��������εı��ཻ
			if(InsidePolygon(vIntersection, vTriangle, 3) ||
			   EdgeSphereCollision(m_Position, vTriangle, 3, m_radius / 2))
			{
				
				//Vector3 vOffset= GetCollisionOffset(vNormal, m_radius, distance);
				count++;
			}
		}
	}
}
