#include <GL/freeglut.h>

bool bFullscreen=false; 
GLfloat angleTri=0.0f;
GLfloat angleSquare=0.0f;


bool bLight = false; //for whether lighting is ON/OFF, by default 'off'
GLfloat LightAmbient[] = { 0.5f,0.5f,0.5f,1.0f };
GLfloat LightDiffuse[] = { 1.0f,1.0f,1.0f,1.0f };
GLfloat LightPosition[] = { 0.0f,0.0f,2.0f,1.0f };

int main(int argc,char** argv)
{
	//function prototypes
	void display(void);
	void resize(int,int);
	void keyboard(unsigned char,int,int);
	void mouse(int,int,int,int);
    void spin(void);
	void initialize(void);
	void uninitialize(void);

	//code
	glutInit(&argc,argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

	glutInitWindowSize(800,600); //to declare initial window size
	glutInitWindowPosition(100,100); //to declare initial window position
	glutCreateWindow("Lighting The Pyramid And Cube Windows");

	initialize();

	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutIdleFunc(spin);
	glutCloseFunc(uninitialize);

	glutMainLoop();

//	return(0); 
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	glTranslatef(-1.5f,0.0f,-6.0f);
	glRotatef(angleTri,0.0f,1.0f,0.0f);
	glBegin(GL_TRIANGLES);
		//NOTE : EVERY FACE OF A PYRAMID (EXCEPT THE BASE/BOTTOM) IS A TRIANGLE

	    //****FRONT FACE****
		glNormal3f(-1.0f, 0.0f, 0.0f); //normal for front face of pyramid
		glVertex3f(0.0f,1.0f,0.0f); //apex of triangle
		glVertex3f(-1.0f,-1.0f,1.0f); //left-bottom tip of triangle
		glVertex3f(1.0f,-1.0f,1.0f); //right-bottom tip of triangle

		//****BACK FACE****
		glNormal3f(0.0f, 1.0f, 0.0f); //normal for back face of pyramid
		glVertex3f(0.0f,1.0f,0.0f); //apex of triangle
		glVertex3f(1.0f,-1.0f,-1.0f); //left-bottom tip of triangle
		glVertex3f(-1.0f,-1.0f,-1.0f); //right-bottom tip of triangle

		//****RIGHT FACE****
		glNormal3f(0.0f, 0.0f, 1.0f); //normal for right face of pyramid
		glVertex3f(0.0f,1.0f,0.0f); //apex of triangle
		glVertex3f(1.0f,-1.0f,1.0f); //left-bottom tip of triangle
		glVertex3f(1.0f,-1.0f,-1.0f); //right-bottom tip of triangle

	   //****LEFT FACE****
		glNormal3f(0.0f, 0.0f, -1.0f); //normal for left face of pyramid
		glVertex3f(0.0f,1.0f,0.0f); //apex of triangle
		glVertex3f(-1.0f,-1.0f,-1.0f); //left-bottom tip of triangle
		glVertex3f(-1.0f,-1.0f,1.0f); //right-bottom tip of triangle
	glEnd();

	// ###### CUBE ######

	glLoadIdentity();
	glTranslatef(1.5f,0.0f,-6.0f);
	glScalef(0.75f, 0.75f, 0.75f);
	glRotatef(angleSquare,1.0f,1.0f,1.0f);

	glBegin(GL_QUADS);
		//NOTE : EVERY FACE OF A CUBE IS A SQUARE

	    //****TOP FACE****
		glNormal3f(0.0f, 1.0f, 0.0f); //normal for top face of cube
		glVertex3f(1.0f, 1.0f, -1.0f); //right-top of top face
		glVertex3f(-1.0f, 1.0f, -1.0f); //left-top of top face
		glVertex3f(-1.0f, 1.0f, 1.0f); //left-bottom of top face
		glVertex3f(1.0f, 1.0f, 1.0f); //right-bottom of top face

		//****BOTTOM FACE****
		glNormal3f(0.0f, -1.0f, 0.0f); //normal for bottom face of cube
		glVertex3f(1.0f, -1.0f, 1.0f); //right-top of bottom face
		glVertex3f(-1.0f, -1.0f, 1.0f); //left-top of bottom face 
		glVertex3f(-1.0f, -1.0f, -1.0f); //left-bottom of bottom face
		glVertex3f(1.0f, -1.0f, -1.0f); //right-bottm of bottom face

		//****FRONT FACE****
		glNormal3f(0.0f, 0.0f, 1.0f); //normal for front face of cube
		glVertex3f(1.0f, 1.0f, 1.0f); //right-top of front face
		glVertex3f(-1.0f, 1.0f, 1.0f); //left-top of front face
		glVertex3f(-1.0f, -1.0f, 1.0f); //left-bottom of front face
		glVertex3f(1.0f, -1.0f, 1.0f); //right-bottom of front face

		//****BACK FACE****
		glNormal3f(0.0f, 0.0f, -1.0f); //normal for back face of cube
		glVertex3f(1.0f, -1.0f, -1.0f); //right-top of back face
		glVertex3f(-1.0f, -1.0f, -1.0f); //left-top of back face
		glVertex3f(-1.0f, 1.0f, -1.0f); //left-bottom of back face
		glVertex3f(1.0f, 1.0f, -1.0f); //right-bottom of back face

		//****LEFT FACE****
		glNormal3f(-1.0f, 0.0f, 0.0f); //normal for left face of cube
		glVertex3f(-1.0f, 1.0f, 1.0f); //right-top of left face
		glVertex3f(-1.0f, 1.0f, -1.0f); //left-top of left face
		glVertex3f(-1.0f, -1.0f, -1.0f); //left-bottom of left face
		glVertex3f(-1.0f, -1.0f, 1.0f); //right-bottom of left face
	
		//****RIGHT FACE****
		glNormal3f(1.0f, 0.0f, 0.0f); //normal for right face of cube
		glVertex3f(1.0f, 1.0f, -1.0f); //right-top of right face
		glVertex3f(1.0f, 1.0f, 1.0f); //left-top of right face
		glVertex3f(1.0f, -1.0f, 1.0f); //left-bottom of right face
		glVertex3f(1.0f, -1.0f, -1.0f); //right-bottom of right face

	glEnd();
	

	glutSwapBuffers();
}

void initialize(void)
{
	//code
	glShadeModel(GL_SMOOTH);
	
	glClearColor(0.0f,0.0f,0.0f,0.0f);
	
	glClearDepth(1.0f);
	
	glEnable(GL_DEPTH_TEST);
	
	glDepthFunc(GL_LEQUAL);
	
	glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);
	glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient); 
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);
	glLightfv(GL_LIGHT1, GL_POSITION, LightPosition);
	glEnable(GL_LIGHT1); 
}

void keyboard(unsigned char key,int x,int y)
{
	//code
	switch(key)
	{
	case 27: //Escape
		glutLeaveMainLoop();
		break;
	case 'L':
	case 'l':
		if (bLight == false)
		{
			bLight = true;
			glEnable(GL_LIGHTING);
		}
		else
		{
			bLight = false;
			glDisable(GL_LIGHTING);
		}
		break;
	case 'F':
	case 'f':
		if(bFullscreen==false)
		{
			glutFullScreen();
			bFullscreen=true;
		}
		else
		{
			glutLeaveFullScreen();
			bFullscreen=false;
		}
		break;
	default:
		break;
	}
}

void mouse(int button,int state,int x,int y)
{
	//code
	switch(button)
	{
	case GLUT_LEFT_BUTTON:
		break;
	default:
		break;
	}
}

void resize(int width,int height)
{
    //code
	if(height==0)
		height=1;
	glViewport(0,0,(GLsizei)width,(GLsizei)height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void spin(void)
{
	//code
	angleTri=angleTri+1.0f;
	if(angleTri>=360.0f)
		angleTri=angleTri-360.0f;

	angleSquare=angleSquare+1.0f;
	if(angleSquare>=360.0f)
		angleSquare=angleSquare-360.0f;

	glutPostRedisplay();
}

void uninitialize(void)
{
	//code
}