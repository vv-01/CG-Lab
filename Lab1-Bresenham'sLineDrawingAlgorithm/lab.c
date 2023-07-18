#include<stdio.h>
#include<math.h>
#include<GL/glut.h>
GLint xOne, yOne, xTwo, yTwo;
void init();
void LineBres_L1(GLint, GLint, GLint, GLint, GLfloat);
void LineBres_GE1(GLint, GLint, GLint, GLint, GLfloat);
void setPixel(GLint, GLint);
void display();

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	GLfloat m;
	glColor3f(1, 0, 0);//vertical line
	glBegin(GL_LINES);
	glVertex2i(0, -500);
	glVertex2i(0, 500);
	glEnd();

	glColor3f(0, 1, 0); //horizontal line
	glBegin(GL_LINES);
	glVertex2i(-500, 0);
	glVertex2i(500, 0);
	glEnd();

	glColor3f(0, 0, 1);//Line color

	m = (float)(yTwo - yOne) / (xTwo - xOne);
	if (fabs(m) >= 1)
		LineBres_GE1(xOne, yOne, xTwo, yTwo, m);
	else
		LineBres_L1(xOne, yOne, xTwo, yTwo, m);
}
void LineBres_L1(GLint x0, GLint y0, GLint xEnd, GLint yEnd, GLfloat m)
{
	GLint dx = abs(xEnd - x0);
	GLint dy = abs(yEnd - y0);
	GLint p = 2 * dy - dx;
	GLint twoDy = 2 * dy;
	GLint twoDyMinusDx = 2 * (dy - dx);
	GLint x = x0, y = y0;
	if (x0>xEnd)
	{
		x = xEnd;
		y = yEnd;
		xEnd = x0;
	}
	else
	{
		x = x0;
		y = y0;
	}
	setPixel(x, y);
	while (x < xEnd)
	{
		x++;
		if (p < 0)
			p += twoDy;
		else
		{
			if (m < 0)
				y--;
			else
				y++;
			p += twoDyMinusDx;
		}
		setPixel(x, y);
	}
}

void LineBres_GE1(GLint x0, GLint y0, GLint xEnd, GLint yEnd, GLfloat m)
{
	GLint dx = abs(xEnd - x0);
	GLint dy = abs(yEnd - y0);
	GLint p = 2 * dx - dy;
	GLint twoDx = 2 * dx;
	GLint twoDxMinusDy = 2 * (dx - dy);
	GLint x = x0, y = y0;
	if (y0>yEnd)
	{
		x = xEnd;
		y = yEnd;
		yEnd = y0;
	}
	else
	{
		x = x0;
		y = y0;
	}
	setPixel(x, y);
	while (y < yEnd)
	{
		y++;
		if (p < 0)
			p += twoDx;
		else
		{
			if (m < 0)
				x--;
			else
				x++;
			p += twoDxMinusDy;
		}
		setPixel(x, y);
	}
}
void setPixel(GLint xCoordinate, GLint yCoordinate)
{
	glBegin(GL_POINTS);
	glVertex2i(xCoordinate, yCoordinate);
	glEnd();
	glFlush();
}

void init()
{
	glClearColor(1.0, 1.0, 1.0, 0);
	glColor3f(0.0, 0.0, 0.0);
	glPointSize(3.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-500, 500, -500, 500);
}
void main(int argc, char **argv)
{
	printf("enter two points for draw lineBresenham:\n");
	printf("\n enter point1(X1,Y1):");
	scanf("%d%d", &xOne, &yOne);
	printf("\n enter point2(X2,Y2):");
	scanf("%d%d", &xTwo, &yTwo);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(300, 400);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("LineBresenham");
	init();
	glutDisplayFunc(display);
	glutMainLoop();
}

