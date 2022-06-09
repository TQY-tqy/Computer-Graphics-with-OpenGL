#include <windows.h>
#include <GL/glut.h>
#include<stdio.h>
#include<stdlib.h>

#define LEFT_EDGE 1
#define RIGHT_EDGE 2
#define BOTTOM_EDGE 4
#define TOP_EDGE 8

void LineGL(float x0, float y0, float x1, float y1){
	glBegin(GL_LINES);
	glColor3f(1.0f, 0.0f, 0.0f); glVertex2f(x0, y0);
	glColor3f(0.0f, 1.0f, 0.0f); glVertex2f(x1, y1);
	glEnd();
}

typedef struct Rectangle{
	float xmin, xmax, ymin, ymax;
}Rect;

Rect rect;
float x0, y0, x1, y1;
float xm, ym, xs, ys;

//区域编码
int CompCode(float x, float y, Rect rect){
	int code = 0x00;
	if (y < rect.ymin)
		code = code | 4;
	if (y>rect.ymax)
		code = code | 8;
	if (x>rect.xmax)
		code = code | 2;
	if (x<rect.xmin)
		code = code | 1;
	return code;
}

//裁剪算法
int cohensutherlandlineclip(Rect rect, float &x0, float &y0, float &x1, float &y1)
{
	int accept, done;
	float x, y;
	accept = 0;
	done = 0;

	int code0, code1, codeout;
	code0 = CompCode(x0, y0, rect);
	code1 = CompCode(x1, y1, rect);
	do{
		if (!(code0 | code1)){//整条线段在窗口内
			accept = 1;//取之
			done = 1;
		}
		else if (code0 & code1)//两个端点同在窗口一侧，弃之
			done = 1;
		else{//线段与窗口存在交点
			if (code0 != 0)
				codeout = code0;
			else
				codeout = code1;
            //求交点
			if (codeout&LEFT_EDGE){
				y = y0 + (y1 - y0)*(rect.xmin - x0) / (x1 - x0);
				x = (float)rect.xmin;
			}
			else if (codeout&RIGHT_EDGE){
				y = y0 + (y1 - y0)*(rect.xmax - x0) / (x1 - x0);
				x = (float)rect.xmax;
			}
			else if (codeout&BOTTOM_EDGE){
				x = x0 + (x1 - x0)*(rect.ymin - y0) / (y1 - y0);
				y = (float)rect.ymin;
			}
			else if (codeout&TOP_EDGE){
				x = x0 + (x1 - x0)*(rect.ymax - y0) / (y1 - y0);
				y = (float)rect.ymax;
			}
			//舍弃在窗口外的部分线段
			if (codeout == code0){
				x0 = x; y0 = y;
				code0 = CompCode(x0, y0, rect);
			}
			else
			{
				x1 = x; y1 = y;
				code1 = CompCode(x1, y1, rect);
			}
		}
	}while (!done);
		if (accept)
		LineGL(x0, y0, x1, y1);
	else{
		x0 = 0; y = 0; x1 = 0; y1 = 0;
		LineGL(x0, y0, x1, y1);
	}
	return accept;
}

void myDisplay(){
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0f, 1.0f, 0.0f);//裁剪窗口设置为黄色
	glRectf(rect.xmin, rect.ymin, rect.xmax, rect.ymax);

	LineGL(x0, y0, x1, y1);

	glFlush();
}
void Init(){
	glClearColor(0.0, 0.0, 0.0, 0.0);//背景设置为白色
	glShadeModel(GL_FLAT);

	rect.xmin = 100;
	rect.xmax = 300;
	rect.ymin = 100;
	rect.ymax = 300;
	x0 = xm, y0 = ym;
	x1 = xs, y1 = ys;
	printf("按下 'c' 裁剪!\n按下 's' 复原!\n按下'q'退出！\n");

}

void Reshape(int w, int h){
	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, (GLdouble)w, 0.0, (GLdouble)h);
}

void keyboard(unsigned char key, int x, int y){
	switch (key){
	case 'c':
		cohensutherlandlineclip(rect, x0, y0, x1, y1);
		glutPostRedisplay();
		break;
	case 's':
		Init();
		glutPostRedisplay();
		break;
	case 'q':
		exit(0);
		break;
	default:
		break;
	}
}

int main(int argc, char *argv[]){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(640,480);
	glutCreateWindow("Sutherland裁剪");
	//输入直线端点
    printf("请输入直线左边端点的x值\n");
	scanf("%f",&xm);
	printf("请输入直线左边端点的y值\n");
	scanf("%f",&ym);
	printf("请输入直线右边端点的x值\n");
	scanf("%f",&xs);
	printf("请输入直线右边端点的y值\n");
	scanf("%f",&ys);
	Init();
	glutDisplayFunc(myDisplay);
    glutKeyboardFunc(keyboard);
    glutReshapeFunc(Reshape);

	glutMainLoop();
	return 0;
}
