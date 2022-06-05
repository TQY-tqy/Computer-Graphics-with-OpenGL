#include<windows.h>
#include <stdlib.h>
#include <GL/glut.h>


float theta=0.0;
void drawPyramid() //该金字塔在以原点为中心，边长为2的立方体范围内
{
	glBegin(GL_TRIANGLES);
	  glColor3f(1.0f,0.0f,0.0f);	  //前面为红色
	  glVertex3f( 0.0f, 1.0f, 0.0f);	//前面三角形上顶点
	  glVertex3f(-1.0f,-1.0f, 1.0f);  //前面三角形左顶点
	  glVertex3f( 1.0f,-1.0f, 1.0f);	//前面三角形右顶点

	  glColor3f(0.0f,1.0f,0.0f);		//右面为绿色
	  glVertex3f( 0.0f, 1.0f, 0.0f);	//右面三角形上顶点
	  glVertex3f( 1.0f,-1.0f, 1.0f);	//右面三角形左顶点
	  glVertex3f( 1.0f,-1.0f, -1.0f);	 //右面三角形右顶点

	  glColor3f(0.0f,0.0f,1.0f);		//背面为蓝色
	  glVertex3f( 0.0f, 1.0f, 0.0f);  //背面三角形上顶点
	  glVertex3f( 1.0f,-1.0f, -1.0f);	 //背面三角形左顶点
	  glVertex3f(-1.0f,-1.0f, -1.0f);	//背面三角形右顶点

	  glColor3f(1.0f,1.0f,0.0f);		//左面为黄色
	  glVertex3f( 0.0f, 1.0f, 0.0f);	//左面三角形上顶点
	  glVertex3f(-1.0f,-1.0f,-1.0f);	//左面三角形左顶点
	  glVertex3f(-1.0f,-1.0f, 1.0f);	//左面三角形右顶点
	glEnd();
	glBegin(GL_POLYGON);  //金字塔底面正方形
      glColor3f(0.5f,0.5f,0.5f);  //底面为灰色
	  glVertex3f(-1.0f,-1.0f, 1.0f);
	  glVertex3f(1.0f,-1.0f, 1.0f);
	  glVertex3f(1.0f,-1.0f, -1.0f);
	  glVertex3f(-1.0f,-1.0f, -1.0f);
	glEnd();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT); //清空颜色和深度缓存
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//gluLookAt(2.0, 2.0, 2.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	glTranslatef(0.0f,0.0f,-5.0f);
	glRotatef(theta,0.0f,1.0f,0.0f);
	drawPyramid();

	glutSwapBuffers();

}

void reshape(int w, int h) //重绘回调函数，在窗口首次创建或用户改变窗口尺寸时被调用
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glFrustum(-1.0, 1.0, -1.0, 1.0, 3.1, 10.0);
	//gluPerspective(45,1,0.1,10.0);
	glOrtho(-2.0, 2.0, -2.0, 2.0, 2.0, 10.0);
}

void init()
{
	glClearColor (1.0, 1.0, 1.0, 1.0);
	glEnable(GL_DEPTH_TEST);     //启动深度测试模式
}

void myKeyboard(unsigned char key,  int x, int y)
{
	if(key == 'a' || key == 'A')
		theta += 5.0;
	if(key == 's' || key == 'S')
		theta -= 5.0;
    if(key == 'c' || key == 'C')
		exit(0);
	if (theta>360) theta -=360;
	if (theta<0) theta +=360;
	glutPostRedisplay(); //重新调用绘制函数
}

int main(int argc, char** argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode (GLUT_DEPTH |GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(0,0);
	glutCreateWindow("金字塔---A键:顺时针旋转,S键:逆时针旋转,C键:退出");
	glutReshapeFunc(reshape); //指定重绘回调函数
	glutDisplayFunc(display);
	glutKeyboardFunc( myKeyboard);   //指定键盘回调函数
	init();
	glutMainLoop();
}
