// g++ main.cpp -o main -lglut -lGL && ./main
#include <GL/glut.h>
#include<iostream>
#include<cmath>
#include<unistd.h>
#include <GL/glut.h>
using namespace std;
typedef float point[3];
int d,choice=1,g;
float init_size=1;
static int power;
point init_tri[] = 
{
	{0,100,0},
	{86.6,-50,0},
	{-86.6,-50,0}
};
point color[] = {{1,0,0},{0,1,0},{0,0,1},{1,1,1}};
double centerX = 0, centerY = 0;
double width = 0, height = 0;
void spread(point a, point b, point c, int m);
void triangle(point a, point b, point c)
{
	glColor3fv(color[choice]);
	glBegin(GL_TRIANGLES);
	glVertex3fv(a);
	glVertex3fv(b);
	glVertex3fv(c);
	glEnd();
}
void findvertex(point a, point b,int m)
{
	point c= {0.0};
	point v1,v2,diff;
	for(int i=0;i<3;i++)
		diff[i]=b[i]-a[i];
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
	point v1,v2,v3;
	triangle(a,b,c);
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
	triangle(init_tri[0],init_tri[1],init_tri[2]);
	glFlush();
	if(m>0)
	{
	findvertex(init_tri[0],init_tri[1],m);
	findvertex(init_tri[1],init_tri[2],m);
	findvertex(init_tri[2],init_tri[0],m);
	}
}
void mouse( int button, int state, int mx, int my )
{
	// flip mouse y axis so up is +y
	my = glutGet( GLUT_WINDOW_HEIGHT ) - my;
	// convert mouse coords to (-1/2,-1/2)-(1/2, 1/2) box
	double x = ( mx / (double)glutGet( GLUT_WINDOW_WIDTH ) ) - 0.5;
	double y = ( my / (double)glutGet( GLUT_WINDOW_HEIGHT ) ) - 0.5;
	if( GLUT_UP == state )
	{
		double preX = ( x * width );
		double preY = ( y * height );
		double zoomFactor = 1.5;
		if( button == GLUT_LEFT_BUTTON )
		{
		// zoom in
			width /= zoomFactor;
			height /= zoomFactor;
		}
		if( button == GLUT_RIGHT_BUTTON )
		{
		// zoom out
			width *= zoomFactor;
			height *= zoomFactor;
		}
		double postX = ( x * width );
		double postY = ( y * height );
		// recenter
		centerX += ( preX - postX );
		centerY += ( preY - postY );
	}

	glutPostRedisplay();
}
void init_triangle(float size)
{
	for(int i=0;i<3;i++)
	for(int j=0;j<3;j++)
	init_tri[i][j]*=init_size;
}
void display()
{
	glClear( GL_COLOR_BUFFER_BIT );

	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	glOrtho(centerX - ( width / 2.0 ),centerX + ( width / 2.0 ),centerY - ( height / 2.0 ),centerY + ( height / 2.0 ),-1,1);
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
	koch(g);
	glutSwapBuffers();
}

int main( int argc, char **argv )
{
	int m_width=600;
	int m_height=600;
	int cx,cy;
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
	g=d;
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
	g=d;
	#endif
	power=d+1;
	glutInit( &argc, argv );
	glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE );
	glutInitWindowSize(m_width, m_height);
	cx = glutGet(GLUT_SCREEN_WIDTH);
	cy = glutGet(GLUT_SCREEN_HEIGHT);
	glutInitWindowPosition ((cx-m_width) / 2, (cy-m_height) / 2);
	glutCreateWindow( "Koch Zoom" );
	glutDisplayFunc( display );
	glutMouseFunc( mouse );
	width = glutGet( GLUT_WINDOW_WIDTH );
	height = glutGet( GLUT_WINDOW_HEIGHT );
	glClearColor(1.0,1.0,1.0,1.0); 
	glutMainLoop();
	return 0;
}
