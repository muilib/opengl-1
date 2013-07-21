#ifndef _3DMATH_H_
#define _3DMATH_H_
#include"Vector.h"
#define PI 3.1415926535897932					

#define BEHIND		0
#define INTERSECTS	1
#define FRONT		2
//	���ط������������������ĳ���
float Magnitude(Vector3 vNormal);
// ��ռ��������ľ���
float Distance(Vector3 vPoint1, Vector3 vPoint2);
Vector3 Normal(Vector3 vPolygon[])	;				//���ض���εĵ�λ������
// ������vA-vB��vPoint����ĵ�
Vector3 ClosestPointOnLine(Vector3 vA, Vector3 vB, Vector3 vPoint);

// ����ƽ�浽ԭ�㣨0��0��0���ľ��룬����Ϊƽ��ķ�������ƽ������һ��
float PlaneDistance(Vector3 Normal, Vector3 Point);

//�ж�ƽ����߶ε��ཻ
bool IntersectedPlane(Vector3 vPoly[], Vector3 vLine[], Vector3 &vNormal, float &originDistance);
// ���������ļн�
double AngleBetweenVectors(Vector3 Vector1, Vector3 Vector2);

// ����ƽ����ߵĽ���
Vector3 IntersectionPoint(Vector3 vNormal, Vector3 vLine[], double distance);

//�жϽ����Ƿ��ڶ���Σ�����/�����Σ���
bool InsidePolygon(Vector3 vIntersection, Vector3 Poly[], long verticeCount);

// �ж϶�������߶ε���ײ
bool IntersectedPolygon(Vector3 vPoly[], Vector3 vLine[], int verticeCount);

// ����ƽ��������Ĺ�ϵ��front behind intersects)
int ClassifySphere(Vector3 &vCenter, 
				   Vector3 &vNormal, Vector3 &vPoint, float radius, float &distance);

// �ж����������εı��Ƿ��ཻ
bool EdgeSphereCollision(Vector3 &vCenter, 
						 Vector3 vPolygon[], int vertexCount, float radius);

// �ж������������Ƿ��ཻ
bool SpherePolygonCollision(Vector3 vPolygon[], 
							Vector3 &vCenter, int vertexCount, float radius);


// ��������Ҫ���ص��������Ӷ�ʹ������ƽ���ཻ
Vector3 GetCollisionOffset(Vector3 &vNormal, float radius, float distance);

#endif 


