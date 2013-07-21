#include"CProtechny.h"

bool CProtechny::Init(int num)
{
	if(CParticule::Init(num))
	{
	   for(int i=0;i<m_pnum;i++)
	   {
		float x,y,z,vx,vy,vz;
		x=0.005f*(rand()%9);
		y=0.005f*(rand()%9)-1;
	    z=0.005f*(rand()%6);
		m_parlist[i].m_pos=Vector3(x,y,z);
		vx = 0.0000007f * (rand()%9000-rand()%9000);
		vy = 0.0000042f * (rand()%9000);
		vz = 0.0000001f * (rand()%9000);
	    m_parlist[i].m_velocity = Vector3(vx,vy,vz);

			// ��ʼ�����ٶ� 
			m_parlist[i].m_acceleration = Vector3(0.0,-0.00025f,0.0);

			//��ʼ����������ʱ�� 
			m_parlist[i].m_lifetime = 100;
			
			// ��ʼ�����ӵĳߴ� 
			m_parlist[i].m_size = 0.01f;

			// ��ʼ�����ӵ���ʧ�ٶ� 
			m_parlist[i].m_dec = 0.05 * (rand()%50);

			//��ʼ�����ӵ���ɫ 
			m_parlist[i].m_color[0] = 255.0f;
			m_parlist[i].m_color[1] = 255.0f;
			m_parlist[i].m_color[2] = 255.0f;

		}
	   if(!m_Bmp.Load("flare.bmp"))
	   {
		   MessageBox(NULL,"������������ʧ��","����",MB_OK);
	       return false;
	   }
	   else
		   return true;
  }
	else 
		return false;
}
void CProtechny::Render()
{   
	glPushMatrix();
	glBlendFunc(GL_SRC_ALPHA,GL_ONE);      //���û�����ӻ�ð�͸��Ч�� 
    glEnable(GL_BLEND);				     //< ���û�� 
	glEnable(GL_TEXTURE_2D);   
	glTranslatef(0.0f,-4.0f,-6.0f);
	glBindTexture(GL_TEXTURE_2D,m_Bmp.ID);     //ѡ������
	for(int i=0;i<m_pnum;i++)
	{
		float x=m_parlist[i].m_pos.x;
	    float y=m_parlist[i].m_pos.y;
		float z=m_parlist[i].m_pos.z;
		float size=m_parlist[i].m_size;
		glColor3fv(m_parlist[i].m_color);
		glNormal3f(0.0f,0.0f,1.0f);
		glBegin(GL_QUADS);                   //��������
		    glTexCoord2f(0.0f,0.0f);glVertex3f(x-size,y-size,z);
			glTexCoord2f(1.0f,0.0f);glVertex3f(x+size,y-size,z);
			glTexCoord2f(1.0f,1.0f);glVertex3f(x+size,y+size,z);
			glTexCoord2f(0.0f,1.0f);glVertex3f(x-size,y+size,z);
		glEnd(); 
	

    }    
	    glDisable(GL_BLEND);
		glPopMatrix();
	Upadate();
}
void CProtechny::Upadate()
{
	for(int i=0;i<m_pnum;i++)
	{          //����λ��                        
		m_parlist[i].m_pos.x+=m_parlist[i].m_velocity.x;
		m_parlist[i].m_pos.y+=m_parlist[i].m_velocity.y;
		m_parlist[i].m_pos.z+=m_parlist[i].m_velocity.z;
		       //�����ٶ�
		m_parlist[i].m_velocity.y+=m_parlist[i].m_acceleration.y;
		      //������ʱ��
		m_parlist[i].m_lifetime-=m_parlist[i].m_dec;

		if(m_parlist[i].m_pos.y<=-1||m_parlist[i].m_lifetime<=0)
		{
		float x,y,z,vx,vy,vz;	
		x=0.005f*(rand()%9);
		y=0.005f*(rand()%9)-1;
	    z=0.005f*(rand()%6);
		m_parlist[i].m_pos=Vector3(x,y,z);
		vx = 0.0000007f * (rand()%9000-rand()%9000);
		vy = 0.0000042f * (rand()%9000);
		vz = 0.0000001f * (rand()%9000);
	    m_parlist[i].m_velocity = Vector3(vx,vy,vz);

			// ��ʼ�����ٶ� 
		m_parlist[i].m_acceleration = Vector3(0.0,-0.00025f,0.0);

			//��ʼ����������ʱ�� 
		m_parlist[i].m_lifetime = 100;
			
			// ��ʼ�����ӵĳߴ� 
		m_parlist[i].m_size = 0.01f;

			// ��ʼ�����ӵ���ʧ�ٶ� 
		m_parlist[i].m_dec = 0.05 * (rand()%50);

		}
  }
}
