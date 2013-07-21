#include"Demo.h"
GLApplication *GLApplication::Create(const char* class_name)//��������ʵ��
{
	Demo * demo = new Demo(class_name);
	return reinterpret_cast<GLApplication *>(demo);
}
Demo::Demo(const char *class_name):GLApplication(class_name)
{
}
bool Demo::Init()
{
   glClearColor(0.0f,0.0f,0.0f,0.5f);
   glClearDepth(1.0f);
   glDepthFunc(GL_LEQUAL);
   glEnable(GL_DEPTH_TEST);
   glShadeModel(GL_SMOOTH);
   glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	
   m_Camera.SetCameraradius(1);
   ResizeDraw(true);
   if(!m_protechny.Init(5000))
	{
		MessageBox(NULL,"��Ȫϵͳ��ʼ��ʧ��!","����",MB_OK);
		exit(-1);
	}
   m_3ds.Init("model.3ds");
   if(!m_draw.LoadTexture())
	   MessageBox(NULL,"��������ʧ��","����",MB_OK);
   /** ��������� */
   m_Camera.setCamera(0.0f,-3.5f, 0.0f, 0.0f, -3.5f, -0.1f,0.0f, 1.0f, 0.0f);
   m_draw.SetLight();
   return true;

}
void Demo::Uninit()
{
	
	m_draw.Delete();
	 
}

void Demo::Draw()											
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);			
	glLoadIdentity();
	plane.Init(4);
	m_Camera.CheckCameraCollision(plane.Vertexs, 12);      
	m_Camera.setLook();
	
	                        // ���ƹ���
	Show3DS(m_3ds.GetmPosition().x,-5.0f,m_3ds.GetmPosition().z);
	m_draw.DrawBox();
	m_draw.DrawQuads();
	m_protechny.Render();
	PrintText();
	glFlush();						//ǿ��ִ�����е�OpenGL��������
	Sleep((1.0/70-1.0/380)*1000);

}

/** ��������� */
void Demo::UpdateCamera()
{
	m_Camera.setViewByMouse();
	
	/** ���̰�����Ӧ */
	if(m_Keys.IsPressed(VK_SHIFT))                      /**< ����SHIFT��ʱ���� */
	{
		m_Camera.setSpeed(0.2f);
	}
	if(!m_Keys.IsPressed(VK_SHIFT))
	{
		m_Camera.setSpeed(0.1f);
	}
	if( m_Keys.IsPressed('W'))/**< ���Ϸ������'W'������ */
	{	
		
		m_Camera.moveCamera(m_Camera.getSpeed());         /**< �ƶ������ */
	}
	

	if( m_Keys.IsPressed('S')||m_Keys.IsPressed(VK_DOWN)) /**< ���·������'S'������ */
	{
		m_Camera.moveCamera(-m_Camera.getSpeed());         /**< �ƶ������ */
	}
	if( m_Keys.IsPressed('A')) /**< ���������'A'������ */
	{
		m_Camera.yawCamera(-m_Camera.getSpeed());          /**< �ƶ������ */
    }
	if( m_Keys.IsPressed('D')) /**< ���ҷ������'D'������ */
	{
		m_Camera.yawCamera(m_Camera.getSpeed());            /**< �ƶ������ */
	}
}
void Demo::Update(DWORD milliseconds)
{
	if (m_Keys.IsPressed(VK_ESCAPE) == true)					// ��ESC�˳� 
	{
		TerminateApplication();									
	}


	if (m_Keys.IsPressed(VK_F1) == true)					// ��F1�ڴ��ں�ȫ�����л� 
	{
		ToggleFullscreen();									
	}
	Upadate3ds();
	UpdateCamera();
}
void Demo::Show3DS(float x,float y,float z)
{
	glPushMatrix();
	glTranslatef(x,y,z);
	m_3ds.Draw();
	glPopMatrix();
}
void Demo::Upadate3ds()
{
	m_3ds.Setspeed(0.1);
	if(m_Keys.IsPressed(VK_UP))
		m_3ds.MovemodleFB(-m_3ds.Getspeed());
	if(m_Keys.IsPressed(VK_DOWN))
		m_3ds.MovemodleFB(m_3ds.Getspeed());
	if(m_Keys.IsPressed(VK_LEFT))
		m_3ds.MovemodleLR(-m_3ds.Getspeed());
	if(m_Keys.IsPressed(VK_RIGHT))
		m_3ds.MovemodleLR(m_3ds.Getspeed());
}
void Demo::CaculateFrameRate()
{
	static float lasttime=0.0f;             //��¼�ϴ�ʱ��
	static float framepersecond=0.0f;        //������ʾ��֡��
	float  currenttime=GetTickCount()*0.001f;//���㵱ǰʱ�䣨��תΪ�뵥λ��

	framepersecond++;
	if(currenttime-lasttime>1.0f)
	{
		lasttime=currenttime;              //����һ����ǰʱ��Ϊ�����
		m_Fps=framepersecond;              //��һ����֡������m_Fps
		framepersecond=0;                  //֡����0����ʼ��¼�����ڵ�֡��
	}
}
void Demo::PrintText()
{
    char string[128];                               /**< ���ڱ�������ַ��� */
	glPushAttrib(GL_CURRENT_BIT);                   /**< ����������ɫ������Ϣ */
	glColor3f(0.0f,1.0f,1.0f);                      /**< ����������ɫ */

	/** ���֡�� */
    CaculateFrameRate();                               // ����֡�� 
    sprintf(string,"FPS:%d",(int)m_Fps);               /**< �ַ�����ֵ */
    m_font.PrintText(string, -5.0f,3.0f);              /**< ����ַ��� */
	sprintf(string,"��ǰλ��:X=%3.1f  Y=%3.1f  Z=%3.1f Speed=%3.1f ",   
		m_Camera.getView().x,m_Camera.getView().y ,m_Camera.getView().z,
			 m_Camera.getSpeed()); /**< �ַ�����ֵ */
	m_font.PrintText(string,-5.0f,3.5f);
	sprintf(string,"��ײ����:n=%d",m_Camera.count);
	m_font.PrintText(string,-5.0f,2.5f);
	glPopAttrib();
		
}

