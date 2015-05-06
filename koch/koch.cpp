#include<iostream>
#include<cmath>
#if defined(__gnu_linux__)||defined(__linux__)
	#include<unistd.h>
#endif
#if defined(_WIN32)||defined(__WINDOWS__)||defined(_WIN64)
	#include<windows.h>
#endif
#include<cstdlib>
#include<ctime>
#include<cstdio>
#include"graph.h"
#include"printw.h"
using namespace std;
int d,choice=1,g;
static int power=d;
float init_size=1;
int cx, cy;
static GLfloat  scaling = 1.0f;
static int lasty = 0;
typedef float point[3];
point init_tri[] = 
{
	{0,10,0},
	{8.66,-5,0},
	{-8.66,-5,0}
};
point color[] = {{1,0,0},{0,1,0},{0,0,1},{1,1,0},{0,1,1},{1,0,1},{0.5,0.5,1},{0,0.5,0.5},{0.8,0,0.7}};
void spread(point a, point b, point c, int m);
void triangle(point a, point b, point c, int m)
{
	glColor3fv(color[(choice+g-m)%9]);
	glBegin(GL_TRIANGLES);
		glVertex3fv(a);
		glVertex3fv(b);
		glVertex3fv(c);
	glEnd();
}
void findvertex(point a, point b,int m)
{
	point c= {0.0},f,q;
	point v1,v2,diff;
	for(int i=0;i<3;i++)
		diff[i]=(b[i]-a[i]);
	for(int i=0;i<3;i++)
	{
		v1[i]=a[i]+diff[i]/3;
		v2[i]=v1[i]+diff[i]/3;
	}
	double s60 = sin(60 * M_PI *pow(-1,(m%2+power%2)) / 180.0);    
	double c60 = cos(60 * M_PI *pow(-1,(m%2+power%2)) / 180.0);
	c[0]= c60 * (v1[0] - v2[0]) - s60 * (v1[1] - v2[1]) + v2[0];
	c[1]= s60 * (v1[0] - v2[0]) + c60 * (v1[1] - v2[1]) + v2[1];
	c[2]=0;
	spread(v1,v2,c,m-1);
	if(m>1)
	{
		findvertex(v1,a,m-1);
		findvertex(b,v2,m-1);
	}
}
void spread(point a, point b, point c, int m)
{
	triangle(a,b,c,m);
	glColor3f(1.0,1.0,1.0);
	glBegin(GL_LINES);
		glVertex3fv(a);
		glVertex3fv(b);
	glEnd();
	int j;
	if(m>0)
	{
		findvertex(c,a,m);
		findvertex(b,c,m);		
	}
	else
		return;
}
void koch(int m)
{
	triangle(init_tri[0],init_tri[1],init_tri[2],g);
	glFlush();
	if(m>0)
	{
		findvertex(init_tri[0],init_tri[1],m);
		findvertex(init_tri[1],init_tri[2],m);
		findvertex(init_tri[2],init_tri[0],m);
	}
}
void myReshape(int w, int h)
{
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	GLfloat r = (GLfloat)h/(GLfloat)w;
	if(w<=h)
		glOrtho(-5,5,-5*r,5*r,-10,10);
	else
		glOrtho(-5/r,5/r,-5,5,-10,10);
	glMatrixMode(GL_MODELVIEW);
	glutPostRedisplay();
}
void idle_display()
{
	static int i=0;
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
		glClearColor(1,1,1,1);
		g=i;
		printw (-1.6, 0.2, 0, "%s : %d", "Succession number", g);
		power=g-1;
		koch(g);
		glFlush();
		sleep(1);
		i++;
	if(i==d+1) i=0;
	glutPostRedisplay();
	
}
void zoom(int x, int y)
{
	glutReshapeWindow(cx,cy);
	int  movy;
	movy = lasty - y;
	if ( abs(movy) < 10 ){ scaling  += (float)(movy) / 100.0f;  }
	if ( scaling < 1.0) scaling = 1.0f;
	if ( scaling > 10.0f) scaling = 10.0f;
	lasty = y;
	glutPostRedisplay();
}
void displayer()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glClearColor(1.0,1.0,1.0,1.0);
	glFlush();
	glutSwapBuffers();
	glScalef(scaling, scaling, scaling);
}
void init_triangle(float size)
{
	init_size/=10;
	for(int i=0;i<3;i++)
		for(int j=0;j<3;j++)
			init_tri[i][j]*=init_size;
}
int main(int argc, char* argv[])
{
	int m_width=600;
	int m_height=600;
	#if !(defined(__gnu_linux__)||defined(__linux__))
		cout << "Enter the number of successions : [0-7] ";
		cin >> d;
		cout << "Next you will have to enter the size of the triangle, a float point value between 0 and 5." << endl;
		cout << "Enter the initial size of the triangle : ";
		cin >> init_size;
		if(init_size>5)
		{
			cout << "Maximum limit of size is 5. Restart the program. Bye!";
			exit(0);
		}
		cout << "Enter the initial color of the triangle you wish to see : \n1. RED \n2. GREEN \n3. BLUE \n Enter your choice :";
		cin >> choice;
		choice-=1;
		g=0;
	#else
		char *pEnd;
		if(argc==0)
		{
			cout << "No args.";
			exit(0);
		}
		d = strtod(argv[1],&pEnd);
		init_size = strtod(pEnd,&pEnd);
		choice = strtod(pEnd,NULL);
		choice--;
		g=0;
	#endif
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB|GLUT_DEPTH);
	glutInitWindowSize(m_width,m_height);
	cx = glutGet(GLUT_SCREEN_WIDTH);
	cy = glutGet(GLUT_SCREEN_HEIGHT);
	glutInitWindowPosition ((cx-m_width) / 2, (cy-m_height) / 2);
	glutCreateWindow("Koch curve");
	init_triangle(init_size);
	glutDisplayFunc(displayer);
	glutIdleFunc(idle_display);
	glutMotionFunc(zoom);
	glutReshapeFunc(myReshape);
	glEnable(GL_DEPTH_TEST);
	glClearColor(1.0,1.0,1.0,1.0);
	glutMainLoop();
	return 0;
}
