#include <GL/freeglut.h>

bool bFullscreen = false;

GLfloat angleTri = 0.0f;
GLfloat angleSquare = 0.0f;

int main(int argc, char** argv)
{
	//function prototypes
	void display(void);
	void resize(int, int);
	void keyboard(unsigned char, int, int);
	void mouse(int, int, int, int);
	void spin(void);
	void initialize(void);
	void uninitialize(void);

	//code
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

	glutInitWindowSize(800, 600); 
	glutInitWindowPosition(100, 100); 
	glutCreateWindow("2D Rotation : Triangle And Square"); 
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


void keyboard(unsigned char key, int x, int y)
{
	//code
	switch (key)
	{
	case 27: // Escape
		glutLeaveMainLoop();
		break;
	case 'F':
	case 'f':
		if (bFullscreen == false)
		{
			glutFullScreen();
			bFullscreen = true;
		}
		else
		{
			glutLeaveFullScreen();
			bFullscreen = false;
		}
		break;
	default:
		break;
	}
}

void mouse(int button, int state, int x, int y)
{
	//code
	switch (button)
	{
	case GLUT_LEFT_BUTTON:
		break;
	default:
		break;
	}
}

void resize(int width, int height)
{
	//code
	if (height == 0)
		height = 1;
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void spin(void)
{
	// code
	angleTri = angleTri + 2.0f;
	if (angleTri >= 360.0f)
		angleTri = angleTri - 360.0f;

	angleSquare = angleSquare + 2.0f;
	if (angleSquare >= 360.0f)
		angleSquare = angleSquare - 360.0f;

	glutPostRedisplay();
}
void display(void)
{
	//code
	//to clear all pixels
	glClear(GL_COLOR_BUFFER_BIT);

	//###### TRIANGLE ######

	glLoadIdentity();
	glTranslatef(-1.5f, 0.0f, -6.0f);
	glRotatef(angleTri, 0.0f, 1.0f, 0.0f);

	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 0.0f, 0.0f); //red : Colour of apex of triangle
	glVertex3f(0.0f, 1.0f, 0.0f); //apex of triangle

	glColor3f(0.0f, 1.0f, 0.0f); //green : Colour of left-bottom of triangle
	glVertex3f(-1.0f, -1.0f, 0.0f); //left-bottom tip of triangle

	glColor3f(0.0f, 0.0f, 1.0f); //blue : Colour of right-bottom of triangle
	glVertex3f(1.0f, -1.0f, 0.0f); //right-bottom tip of triangle
	glEnd();

	//###### SQUARE ######

	glLoadIdentity();
	glTranslatef(1.5f, 0.0f, -6.0f);
	glRotatef(angleSquare, 1.0f, 0.0f, 0.0f);

	glBegin(GL_QUADS);
	//blue : Colour of square
	glColor3f(0.0f, 0.0f, 1.0f);
	// square
	glVertex3f(1.0f, 1.0f, 0.0f); //right-top of square
	glVertex3f(-1.0f, 1.0f, 0.0f); //left-top of square
	glVertex3f(-1.0f, -1.0f, 0.0f); //left-bottom of square
	glVertex3f(1.0f, -1.0f, 0.0f); //right-bottom of square
	glEnd();

	//to process buffered OpenGL Routines
	glutSwapBuffers();
}

void initialize(void)
{
	//code
	//to select clearing (background) clear
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); //black
}

void uninitialize(void)
{
	//code
}