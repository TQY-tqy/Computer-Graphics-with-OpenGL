#include <stdlib.h>
#include <windows.h>
#include <GL/glut.h>
#include <math.h>
#define DEG_TO_RAD 0.017453  //角度转为弧度的参数，即 2*PI/360

float theta=30.0; //直线与X轴正方向的夹角
float length=200.0;  //直线的长度
float x=300.0, y=200.0; //直线的第一个端点

void init (void)
{
    glClearColor (1.0, 1.0, 1.0, 0.0);
    glMatrixMode (GL_PROJECTION);
    gluOrtho2D (0.0, 640.0, -100.0, 480.0);
}

void display (void)
{
    glClear (GL_COLOR_BUFFER_BIT);

    glColor3f (0.0, 1.0, 0.9);
    glBegin (GL_POLYGON);
        glVertex2f (x, y);
        glVertex2f (x + length*cos(DEG_TO_RAD*theta),y + length*sin(DEG_TO_RAD*theta));
		glVertex2f (x + length*cos(DEG_TO_RAD* (theta+30)),y + length*sin(DEG_TO_RAD* (theta+30)));
    glEnd ( );
    glutSwapBuffers ( );     //交换前后台缓存
}


void mySpecialKeyboard(int key,  int x, int y)
{
    //按下F1或者左键，逆时针旋转
	if(key == GLUT_KEY_F1 || key == GLUT_KEY_LEFT)
		theta += 5.0;
       x+=100;
    //按下F2或者右键，逆时针旋转
	if(key == GLUT_KEY_F2 || key == GLUT_KEY_RIGHT)
		theta -= 5.0;
   	if (theta>360) theta -=360;
	if (theta<0) theta +=360;
	glutPostRedisplay(); //重新调用绘制函数
}

int main (int argc, char** argv)
{
    glutInit (&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition (100, 100);
    glutInitWindowSize (640, 480);
    glutCreateWindow ("Draw Triangle with Double Buffer");

    init ( );
    glutDisplayFunc (display);
	glutSpecialFunc( mySpecialKeyboard);        //指定键盘回调函数
    glutMainLoop ( );
}

