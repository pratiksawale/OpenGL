#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<memory.h>
#include<X11/Xlib.h>
#include<X11/Xutil.h>
#include<X11/XKBlib.h>
#include<X11/keysym.h>
#include<GL/gl.h>
#include<GL/glx.h>
#include<GL/glu.h>

#define HEIGHT 600
#define WIDTH 800

using namespace std;
Display *gpDisplay=NULL;
XVisualInfo *gpXVisualInfo=NULL;
bool bFullscreen=false;

GLXContext gGLXContext;
Colormap gColormap;
Window gWindow;
int main(void)
{
   void CreateWindow(void);
   void ToggleFullscreen(void);
   void initialize(void);
   void display(void);
   void resize(int,int);
   void uninitialize();
   
   int winHeight;
   winHeight= HEIGHT;
   int winWidth;
   winWidth= WIDTH;
   bool bDone=false;
   
   CreateWindow();
   
   initialize();

   XEvent event;
   KeySym keysym;
   
   	while(bDone==false)
	{
		while (XPending(gpDisplay))
		{
			XNextEvent(gpDisplay,&event);
			switch(event.type)
			{
				case MapNotify:
					break;
				case KeyPress:
					keysym=XkbKeycodeToKeysym(gpDisplay,event.xkey.keycode,0,0);
					switch(keysym)
					{
						case XK_Escape:
							bDone=true;
							exit(0);
						case XK_F:
						case XK_f:
							if(bFullscreen==false)
							{
								ToggleFullscreen();
								bFullscreen=true;
							}
							else
							{
								ToggleFullscreen();
								bFullscreen=false;
							}
							break;
						default:
							break;
					}
					break;
				case ButtonPress: 
					switch(event.xbutton.button)
					{
						case 1: 
							break;
						case 2: 
							break;
						case 3: 
							break;
						default:
							break;
					}
					break;
				case MotionNotify: 
					break;
				case ConfigureNotify: 
					winWidth=event.xconfigure.width;
					winHeight=event.xconfigure.height;
					resize(winWidth,winHeight);
					break;
				case Expose: 
					break;
				case DestroyNotify:
					break;
				case 33:
					uninitialize();
					exit(0);
				default:
					break;
			}
			
		}
		display();
	}
	uninitialize();
	return(0);
}

int initialize(void)
{
	void resize(int,int);
	gGLXContext=glXCreateContext(gpDisplay,gpXVisualInfo,NULL,GL_TRUE);
	glXMakeCurrent(gpDisplay,gWindow,gGLXContext);
	glClearColor(0.0f,0.0f,1.0f,0.0f);
	resize(WIDTH,HEIGHT);
}

void display(void){
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_TRIANGLES);
		glColor3f(1.0f, 0.2f, 0.3f);
		glVertex3f(0.0f, 50.0f, 0.0f);
		glVertex3f(-50.0f, -50.0f, 0.0f);
		glVertex3f(50.0f, -50.0f, 0.0f);
	glEnd();
	glFlush();
}

void resize(int width, int height)
{
	if (height == 0)
		height=1;
	
	glViewport(0,0,(GLsizei)width,(GLsizei)height);
	
}

void ToggleFullscreen(void)
{
	//variable declarations
	Atom wm_state;
	Atom fullscreen;
	XEvent xev={0};
	
	//code
	wm_state=XInternAtom(gpDisplay,"_NET_WM_STATE",False);
	memset(&xev,0,sizeof(xev));
	
	xev.type=ClientMessage;
	xev.xclient.window=gWindow;
	xev.xclient.message_type=wm_state;
	xev.xclient.format=32;
	xev.xclient.data.l[0]=bFullscreen ? 0 : 1;
	
	fullscreen=XInternAtom(gpDisplay,"_NET_WM_STATE_FULLSCREEN",False);
	xev.xclient.data.l[1]=fullscreen;
	
	XSendEvent(gpDisplay,
	           RootWindow(gpDisplay,gpXVisualInfo->screen),
	           False,
	           StructureNotifyMask,
	           &xev);
}

void uninitialize(void)
{
	GLXContext currentGLXContext;
	currentGLXContext=glXGetCurrentContext();

	if(currentGLXContext!=NULL && currentGLXContext == gGLXContext)
	{
		glXMakeCurrent(gpDisplay,0,0);
	}
	
	if(gGLXContext)
	{
		glXDestroyContext(gpDisplay,gGLXContext);
	}
	if(gWindow)
	{
		XDestroyWindow(gpDisplay,gWindow);
	}
	
	if(gColormap)
	{
		XFreeColormap(gpDisplay,gColormap);
	}
	
	if(gpXVisualInfo)
	{
		free(gpXVisualInfo);
		gpXVisualInfo=NULL;	
	}

	if(gpDisplay)
	{
		XCloseDisplay(gpDisplay);
		gpDisplay=NULL;
	}
}

void CreateWindow(void)
{
	void uninitialize(void);

	XSetWindowAttributes winAttribs;
	int defaultScreen;
	int defaultDepth;
	int styleMask;

	static int frameBufferAttributes[]=
	{
		GLX_RGBA,
		GLX_RED_SIZE, 1,
		GLX_GREEN_SIZE, 1,
		GLX_BLUE_SIZE,1,
		GLX_ALPHA_SIZE,1,
		None
	};
	gpDisplay=XOpenDisplay(NULL);
	if(gpDisplay==NULL)
	{
		printf("ERROR : Unable To Open X Display.\nExitting Now...\n");
		uninitialize();
		exit(1);
	}

	defaultScreen=XDefaultScreen(gpDisplay);
	//defaultDepth=DefaultDepth(gpDisplay,defaultScreen);
	gpXVisualInfo=glXChooseVisual(gpDisplay,defaultScreen,frameBufferAttributes);
	if(gpXVisualInfo==NULL)
	{
		printf("ERROR : Unable To choose Visual .\nExitting Now...\n");
		uninitialize();
		exit(1);	
	}
	
	winAttribs.border_pixel=0;
	winAttribs.background_pixmap=0;
	winAttribs.colormap=XCreateColormap(gpDisplay,RootWindow(gpDisplay, gpXVisualInfo->screen),gpXVisualInfo->visual,AllocNone);
	winAttribs.background_pixel=BlackPixel(gpDisplay,defaultScreen);
	winAttribs.event_mask=ExposureMask | VisibilityChangeMask | ButtonPressMask| KeyPressMask| PointerMotionMask | StructureNotifyMask;
	winAttribs.border_pixmap=0;
	gColormap=winAttribs.colormap;	
	styleMask=CWBorderPixel | CWBackPixel | CWEventMask|CWColormap;
	gWindow=XCreateWindow(gpDisplay,RootWindow(gpDisplay,gpXVisualInfo->screen),0,0,WIDTH,HEIGHT,0,gpXVisualInfo->depth,InputOutput,gpXVisualInfo->visual,
	styleMask,&winAttribs);
	
	if(!gWindow)
	{
		printf("ERROR: Failed To create main Window");
		uninitialize();
		exit(1);
	}
	
	XStoreName(gpDisplay,gWindow,"My Window");
	Atom windowManagerDelete = XInternAtom(gpDisplay,"WM_DELETE_WINDOW",True);
	XSetWMProtocols(gpDisplay,gWindow,&windowManagerDelete,1);
	XMapWindow(gpDisplay,gWindow);
	
}
