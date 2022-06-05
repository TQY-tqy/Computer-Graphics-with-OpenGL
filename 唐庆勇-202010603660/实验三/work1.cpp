#include <windows.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdlib.h>
#include <math.h>

//改进前的Bresenham算法，使用于从左到右画线且斜率
void setPixel(GLint x, GLint y){
    glBegin(GL_POINTS);
    glVertex2i(x,y);
    glEnd();
}

void init(void){
    glClearColor(1.0,1.0,1.0,0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0,1000.0,0.0,2000.0);
}

//flag为交换标记
void lineBres(GLint x0, GLint y0, GLint x1, GLint y1)
{
	GLint dy = y1 - y0, dx = x1 - x0;
	GLint dxAbs = abs(dx);
	GLint dyAbs = abs(dy);
	GLint twoDyAbs = dyAbs * 2, twoDyMinusDxAbs = 2 * (dyAbs - dxAbs);//前者为2△y，后者为2(△y - △x)
	GLint stepX = ((dx == 0) ? 0 : dx / dxAbs); //算法中x的增量
	GLint stepY = ((dy == 0) ? 0 : dy / dyAbs); //算法中y的增量
	GLfloat pk = twoDyAbs - dxAbs;//决策参数
	GLint x,y;
	int i;
	if(x0 > x1){
        x = x1;
        y = y1;
        x1 = x0;
	}else{
	    x = x0;
	    y = y0;
	}
	/*画出初始点*/
	setPixel(x,y);
	/*算法核心*/
	for (i = 0; i < dxAbs; i++, x += stepX){
		if (pk < 0){
			pk += twoDyAbs;
		}else {
			y += stepY;
			pk += twoDyMinusDxAbs;
		}
		setPixel(x, y);
	}
	glFlush();
}

void myFunc(void){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0,0.0,0.0);
    lineBres(50,60,600,500);//black 0<k<1
    glColor3f(1.0,0.0,0.0);
    lineBres(100,400,400,150);//red -1<k<0
}

int main(int argc,char * argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutCreateWindow("test_Bre");
    init();
    glutDisplayFunc(myFunc);
    glutMainLoop();
    return 0;
}