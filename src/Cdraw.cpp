#include"Cdraw.h"

int Cdraw::DrawQuads()
{
	
	//count++;
	//�����������
	GLfloat mat_ambient[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    GLfloat mat_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
	//���ò�������
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D,m_Bmp1.ID);
	glTranslatef(0.0f,0.0f,-10.0f);
	glBegin(GL_QUADS);
	
	plane.Bedraw();
	glEnd();
	 glPopMatrix();
	
	 return 0;
}


int Cdraw::DrawTriangle()
{
	int count=0;
	return count;
}
void Cdraw:: ProduceRand()
{
	static float lasttime=0.0f;             //��¼�ϴ�ʱ��
	float  currenttime=GetTickCount()*0.001f;//���㵱ǰʱ�䣨��תΪ�뵥λ��

	if(currenttime-lasttime>1.0f)
	{
		lasttime=currenttime;              //����һ����ǰʱ��Ϊ�����
		m_rand=rand()%5;
	}
}
void Cdraw::DrawBox()
{
	
	// ���ò������� 
	float m_angle=0.0f;
	GLfloat mat_ambient[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat mat_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glPushMatrix();
	ProduceRand();
	if(m_rand==0){
		glTranslatef(-0.5f,-3.5f,-7.0f);}
	else if(m_rand==1){
		glTranslatef(0.5f,-3.5f,-7.0f);}
	else if(m_rand==2){
		glTranslatef(0.5f,-3.5f,-5.0f);}
	else
		glTranslatef(-0.5f,-3.5f,-5.0f);
	glScalef(0.1f,0.2f,0.05f);
	glRotatef(m_angle,0.0f,1.0f,0.0f);
	// ѡ������ 
	glBindTexture(GL_TEXTURE_2D, m_Bmp2.ID);
	
	// ��ʼ�����ı��� 
	glBegin(GL_QUADS);												
		
	    /// ǰ����
		glNormal3f( 0.0f, 0.0f, 1.0f);								//< ָ������ָ��۲��� 
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  0.0f);	
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 0.0f, -1.0f,  0.0f);	
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 0.0f,  0.0f,  0.0f);	
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  0.0f,  0.0f);	
		
		/// �����
		glNormal3f( 0.0f, 0.0f,-1.0f);								//ָ�����߱���۲��� 
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);	
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  0.0f, -1.0f);	
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 0.0f,  0.0f, -1.0f);	
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 0.0f, -1.0f, -1.0f);	
		
		/// ����
		glNormal3f( 0.0f, 1.0f, 0.0f);								//ָ���������� 
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  0.0f, -1.0f);	
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,  0.0f,  0.0f);	
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 0.0f,  0.0f,  0.0f);	
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 0.0f,  0.0f, -1.0f);	
		
		/// ����
		glNormal3f( 0.0f,-1.0f, 0.0f);								// ָ�����߳��� 
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);	
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 0.0f, -1.0f, -1.0f);	
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 0.0f, -1.0f,  0.0f);	
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  0.0f);	
		
		/// �Ҳ���
		glNormal3f( 1.0f, 0.0f, 0.0f);								// ָ�����߳��� 
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 0.0f, -1.0f, -1.0f);	
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 0.0f,  0.0f, -1.0f);	
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 0.0f,  0.0f,  0.0f);	
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 0.0f, -1.0f,  0.0f);	
		
		/// �����
		glNormal3f(-1.0f, 0.0f, 0.0f);								// ָ�����߳��� 
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);	
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  0.0f);	
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  0.0f,  0.0f);	
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  0.0f, -1.0f);	
	glEnd();

	glPopMatrix();
}
bool Cdraw::LoadTexture()
{
	/** ����λͼ�ļ� */
	if(!m_Bmp1.Load("2.bmp")||!m_Bmp2.Load("zhuan.bmp"))                        /**< ����λͼ�ļ� */
	{
		MessageBox(NULL,"װ��λͼ�ļ�ʧ�ܣ�","����",MB_OK);  /**< �������ʧ���򵯳��Ի��� */
		return false;
	}
	/** ��������ӳ�� */
	glEnable(GL_TEXTURE_2D);

  	return true;
}
void Cdraw::SetLight()
{
	 // �����Դ������ֵ 
	GLfloat LightAmbient[]= { 0.0f, 0.0f, 0.0f, 1.0f }; 	/**< ��������� */
	GLfloat LightDiffuse[]= { 0.5f, 0.5f, 0.5f, 1.0f };		/**< �������� */
	GLfloat LightSpecular[]= { 1.0f, 1.0f, 1.0f, 1.0f };	/**< �������� */
	GLfloat LightPosition[]= { 0.0f, 0.0f, 2.0f, 1.0f };	/**< ��Դλ�� */
	GLfloat diffuseLightB[] = { 0.0f, 0.0f, 1.0f, 1.0f };
	GLfloat specularLightB[] = { 0.0f, 0.0f, 1.0f, 1.0f };
	GLfloat lightPositionB[]=  {0.0f,0.0f,0.0f,1.0f};
	/** ���ù�Դ������ֵ */
	glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);		/**< ���û����� */
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);		/**< ��������� */
	glLightfv(GL_LIGHT1, GL_SPECULAR, LightSpecular);	/**< ��������� */
	glLightfv(GL_LIGHT1, GL_POSITION, LightPosition);	/**< ���ù�Դλ�� */

	glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuseLightB);
	glLightfv(GL_LIGHT2, GL_SPECULAR, specularLightB);
	glLightfv(GL_LIGHT2, GL_POSITION, lightPositionB);
	/** ���ù�Դ */
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT1); 
	//glEnable(GL_LIGHT2);
}
void Cdraw::Delete()
{
	

		m_Bmp1.FreeImage();
	    glDeleteTextures(1,&m_Bmp1.ID);
		m_Bmp2.FreeImage();
		glDeleteTextures(1,&m_Bmp2.ID);
	
}