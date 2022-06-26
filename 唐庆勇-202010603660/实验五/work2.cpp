#include<windows.h>
#include<stdlib.h>
#include<iostream>
#include<gl/glut.h>
#include<math.h>

using namespace std;
typedef float Color[3];

//初始化
void init(void) {
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0, 400, 0, 400);
}

void setPixel(int x, int y) {
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
	glFlush();
}

void getPixel(GLint x, GLint y, Color&c) {
	glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, c);//获取点的颜色
}

bool compareColor(Color c1, Color c2) {
	for (int i = 0; i < 3; i++)
        if (c1[i] - c2[i] > 0.001 || c1[i] - c2[i] < -0.001) return false;
    return true;
}

//4种子点填充
void boundaryFill4(int x, int y, Color fillColor, Color  borderColor)
{
	Color interiorColor;
	getPixel(x, y, interiorColor);
	glColor3f(fillColor[0], fillColor[1], fillColor[2]);
	if (compareColor(interiorColor, borderColor)) {
		setPixel(x, y);
		boundaryFill4(x + 1, y, fillColor, borderColor);
		boundaryFill4(x - 1, y, fillColor, borderColor);
		boundaryFill4(x, y + 1, fillColor, borderColor);
		boundaryFill4(x, y - 1, fillColor, borderColor);
	}
}


void myDraw(void) {
		int x = 101, y = 101;
		Color fillColor, interiorColor;
		glClear(GL_COLOR_BUFFER_BIT);
		glColor3f(0.0, 0.0, 0.0);
		glBegin(GL_LINE_LOOP);
		glVertex2f(100.0, 100.0);
		glVertex2f(300.0, 100.0);
		glVertex2f(300.0, 300.0);
		glVertex2f(100.0, 200.0);
		glEnd();
		fillColor[0] = 1.0;
		fillColor[1] = 1.0;
		fillColor[2] = 0.0;
		interiorColor[0] = 1;
		interiorColor[1] = 1;
		interiorColor[2] = 1;
		boundaryFill4(x, y, fillColor, interiorColor);
		glFlush();

	}

int main(int argc, char** argv) {
		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
		glutInitWindowPosition(20, 100);
		glutInitWindowSize(400,400);
		glutCreateWindow("种子点填充");
		init();
		glutDisplayFunc(myDraw);
		glutMainLoop();
}
