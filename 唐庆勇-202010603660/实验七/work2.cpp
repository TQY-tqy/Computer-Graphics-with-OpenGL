#include <windows.h>
#include <gl/glut.h>
#define NO 0
#define YES 1

int Drawing;

void Initialization()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_DST_ALPHA);

	glEnable(GL_POINT_SMOOTH);           //启用点反走样
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);

	glEnable(GL_LINE_SMOOTH);            //启用直线反走样，初始化函数中所调用的那3条命令才真正起作用
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);


	Drawing=NO;
}

//绘制一个笑脸
void OnDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	if(Drawing == YES)		//启用混合状态，初始化函数中所调用的那3条命令才真正起作用
	{
		glEnable(GL_BLEND);
	}
	else					//关闭混合状态
	{
		glDisable(GL_BLEND);
	}
	glColor3f(0.0f, 1.0f, 1.0f);//嘴巴为蓝色

	glLineWidth(10);
	glBegin(GL_LINE_STRIP);
	{
		glVertex2f(-3.0f, -0.0f);
		glVertex2f(0.0f, -2.0f);
		glVertex2f(3.0f, -0.0f);
	}
	glEnd();

    glColor3f(1.0f, 0.0f, 0.0f);//眼睛为红色
	glPointSize(50);
	glBegin(GL_POINTS);
	{
		glVertex2f(1.0f, 1.0f);
		glVertex2f(-1.0f, 1.0f);
	}
	glEnd();

	glutSwapBuffers();
}

void OnReShape(int w,int h)
{
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION); //将当前矩阵指定为投影模式
	glLoadIdentity();

	if (h!=0)
	{
		GLfloat aspect = (float)w / (float)h;

		if(w < h)
		{
			gluOrtho2D(-3, 3, -3 * aspect, 3 * aspect);
		}
		else
		{
			gluOrtho2D(-3 / aspect, 3 / aspect, -3, 3);
		}
	}
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

HMENU CreateMenu()
{
	glutAddMenuEntry("正常显示", NO);
	glutAddMenuEntry("反走样", YES);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void OnMenu(int value)
{
	Drawing = value;
	glutPostRedisplay();
}

int main(int argc,char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(600, 480);
	glutCreateWindow("OpenGL反走样");

	glutReshapeFunc(OnReShape);
	glutDisplayFunc(OnDisplay);
	glutCreateMenu(OnMenu);

	Initialization();
	CreateMenu();


	glutMainLoop();
}
