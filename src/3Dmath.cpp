
#include <math.h>	
#include <float.h>	
#include"3Dmath.h"
float Absolute(float num) //����һ������
{
	
	if(num < 0)
		return (0 - num);
	return num;
}

Vector3 Cross(Vector3 vVector1, Vector3 vVector2)//�������������Ĳ��
{
	Vector3 vNormal;									
	vNormal=vVector1.crossProduct(vVector2);
    return vNormal;										
}

float Magnitude(Vector3 vNormal)  //���ز�������������������ȣ�
{
	return (float)vNormal.length();

}

Vector3 Normalize(Vector3 vNormal) //���ص�λ�漶����
{
	float magnitude = Magnitude(vNormal);			

	vNormal.x /= magnitude;							
	vNormal.y /= magnitude;								
	vNormal.z /= magnitude;						

	return vNormal;										
}

Vector3 Normal(Vector3 vPolygon[])					//���ض���εĵ�λ������
{														
	Vector3 vVector1 = vPolygon[2] - vPolygon[0];   
	Vector3 vVector2 = vPolygon[1] - vPolygon[0];
	Vector3 vNormal = Cross(vVector1, vVector2);		
	vNormal = Normalize(vNormal);	
	return vNormal;
}

float Distance(Vector3 vPoint1, Vector3 vPoint2)   //���ؿռ�������ľ���
{
	
	double distance =(vPoint2-vPoint1).length();
	return (float)distance;
}

Vector3 ClosestPointOnLine(Vector3 vA, Vector3 vB, Vector3 vPoint)//�����߶��е�һ�����������ĵ�
{
	Vector3 vVector1 = vPoint - vA;
    Vector3 vVector2 = Normalize(vB - vA);
    float d = Distance(vA, vB);
	float t =vVector2.dotProduct(vVector1);
    if (t <= 0) 
		return vA;                                              //vPoint��vA��
    if (t >= d) 
		return vB;                                               //vPoint��vB��
    Vector3 vVector3 = vVector2 * t;
    Vector3 vClosestPoint = vA + vVector3;
	return vClosestPoint;                                 //vPoint��vA-vB��
}



float PlaneDistance(Vector3 Normal, Vector3 Point)//����ƽ�浽ԭ��ľ���
{	
	float distance = 0;					//ƽ�淽��AX+BY+CZ=D,d=-(ax+by+cz);(a,b,c)		
    distance = - Normal.dotProduct(Point);//Ϊ��λ������
	return distance;									
}

bool IntersectedPlane(Vector3 vPoly[], Vector3 vLine[], Vector3 &vNormal, float &originDistance)//�߶���ƽ���Ƿ��ཻ
{
	float distance1=0, distance2=0;				
			
	vNormal = Normal(vPoly);							
	originDistance = PlaneDistance(vNormal, vPoly[0]);
	distance1 = vNormal.dotProduct(vLine[0]);
	distance2 = vNormal.dotProduct(vLine[1]);
    if(distance1 * distance2 >= 0)			 //��������˵���ƽ��ͬ�࣬����У������ཻ
	   return false;						
	return true;							
}


double AngleBetweenVectors(Vector3 Vector1, Vector3 Vector2)//�������ļн�
{							
	float dotProduct =Vector1.dotProduct(Vector2);				
	float vectorsMagnitude = Magnitude(Vector1) * Magnitude(Vector2) ;
	double angle = acos( dotProduct / vectorsMagnitude );
    if(_isnan(angle))
		return 0;
	return( angle );                               //���ػ���
}

Vector3 IntersectionPoint(Vector3 vNormal, Vector3 vLine[], double distance)//���㽻��
{
	distance=PlaneDistance(vNormal,  vLine[0]);
	Vector3 vPoint, vLineDir;				
	double Numerator = 0.0, Denominator = 0.0, dist = 0.0;
	vLineDir = vLine[1] - vLine[0];		
	vLineDir = Normalize(vLineDir);				
	Numerator = - (vNormal.dotProduct(vLine[0])+ distance);
	Denominator =vNormal.dotProduct(vLineDir);		
	if( Denominator == 0.0)						
		return vLine[0];						

	dist = Numerator / Denominator;			
	
	vPoint.x = (float)(vLine[0].x + (vLineDir.x * dist));
	vPoint.y = (float)(vLine[0].y + (vLineDir.y * dist));
	vPoint.z = (float)(vLine[0].z + (vLineDir.z * dist));

	return vPoint;								
}

bool InsidePolygon(Vector3 vIntersection, Vector3 Poly[], long verticeCount)//�жϽ����Ƿ��ڶ������
{
	const double MATCH_FACTOR = 0.99;		// ���ǲ���Ҫ��С��λ
	double Angle = 0.0;				
	Vector3 vA, vB;					
	for (int i = 0; i < verticeCount; i++)		
	{	
		vA = Poly[i] - vIntersection;		
											
		vB = Poly[(i + 1) % verticeCount] - vIntersection;
												
		Angle += AngleBetweenVectors(vA, vB);	
	}
											
	if(Angle >= (MATCH_FACTOR * (2.0 * PI)) )	// ���ȴ��ڻ����2PI,�ڶ������
		return true;							
		
	return false;								
}

bool IntersectedPolygon(Vector3 vPoly[], Vector3 vLine[], int verticeCount)
{
	Vector3 vNormal;
	float originDistance = 0;
    if(!IntersectedPlane(vPoly, vLine,vNormal,originDistance))
		return false;
	Vector3 vIntersection = IntersectionPoint(vNormal, vLine, originDistance);//���㽻��
	if(InsidePolygon(vIntersection, vPoly, verticeCount))//�ҵ����㣬�ж��Ƿ��ڶ������
		return true;						
	return false;								
}

int ClassifySphere(Vector3 &vCenter, 
				   Vector3 &vNormal, Vector3 &vPoint, float radius, float &distance)
{                                                              //������ƽ��Ĺ�ϵ
	float d = (float)PlaneDistance(vNormal, vPoint);

	
	distance = (vNormal.dotProduct(vCenter)+ d);

	if(Absolute(distance) < radius)   //����ֵС�ڰ뾶���ཻ
		return INTERSECTS;
	else if(distance >= radius)       //���ڻ���ڰ뾶��ǰ��   
		return FRONT;
	return BEHIND;
}

bool EdgeSphereCollision(Vector3 &vCenter, 
						 Vector3 vPolygon[], int vertexCount, float radius)//���������εı��Ƿ��ཻ
{
	Vector3 vPoint;
	for(int i = 0; i < vertexCount; i++)
	{

	 vPoint = ClosestPointOnLine(vPolygon[i],     //���ص�ǰ��������������ĵ�
		 vPolygon[(i + 1) % vertexCount], vCenter);
		float distance = Distance(vPoint, vCenter);//��������������ĵľ���
		if(distance < radius)
			return true;
	}
	return false;
}

bool SpherePolygonCollision(Vector3 vPolygon[], 
							Vector3 &vCenter, int vertexCount, float radius)
{
	Vector3 vNormal = Normal(vPolygon);
	float distance = 0.0f;                              //���嵽ƽ��ľ���
	int classification = ClassifySphere(vCenter, vNormal, vPolygon[0], radius, distance);
	if(classification == INTERSECTS) 
	{
		Vector3 vOffset = vNormal * distance;            //ͶӰ�������ĵ�ƽ��
		Vector3 vPosition = vCenter - vOffset;
		if(InsidePolygon(vPosition, vPolygon, 3))        //�жϽ����Ƿ��ڶ������
			return true;	
		else
		{

			if(EdgeSphereCollision(vCenter, vPolygon, vertexCount, radius)) //����
			{
				return true;	
			}
		}
	}
	return false;
}

Vector3 GetCollisionOffset(Vector3 &vNormal, float radius, float distance)
{
	Vector3 vOffset = Vector3(0, 0, 0);

	if(distance > 0)
	{
		float distanceOver = radius - distance;
		vOffset = vNormal * distanceOver;
	}
	else 
	{
		float distanceOver = radius + distance;
		vOffset = vNormal * -distanceOver;
	}

	return vOffset;
}

