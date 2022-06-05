#include <windows.h>
#include <GL/glut.h>
#include <stdlib.h>

//Bre算法，适用于各斜率直线的绘制以及从左到右或者从右到左方向直线的绘制
void init(void){
    glClearColor(1.0,1.0,1.0,0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0,1000.0,0.0,2000.0);
}

void setPixel(GLint x, GLint y){
    glBegin(GL_POINTS);
    glVertex2i(x,y);
    glEnd();
}

//flag为交换标记
void Bresenham(GLint x0, GLint y0, GLint x1, GLint y1, int flag)
{
	GLint dy = y1 - y0, dx = x1 - x0;
	GLint dxAbs = abs(dx);
	GLint dyAbs = abs(dy);
	GLint twoDyAbs = dyAbs * 2, twoDyMinusDxAbs = 2 * (dyAbs - dxAbs);//前者为2△y，后者为2(△y - △x)
	GLint stepX = ((dx == 0) ? 0 : dx / dxAbs); //算法中x的增量
	GLint stepY = ((dy == 0) ? 0 : dy / dyAbs); //算法中y的增量
	GLfloat pk = twoDyAbs - dxAbs;//决策参数
	GLint x = x0, y = y0;
	int i;
	//如果|k|≥1,交换x与y方向的规则
	if (dxAbs < dyAbs){
        flag = 1;
		Bresenham(y0, x0, y1, x1, flag);
		return;
	}
	/*画出初始点*/

	if (flag == 1) setPixel(y, x);
	else setPixel(x, y);

	/*对水平线以及k = 1的情况单独处理*/
	if (dyAbs == dxAbs || dyAbs == 0 || dxAbs == 0){
		for (i = 0 ; i < dxAbs ; i++)
			if (flag == 1)
				setPixel (y += stepY, x += stepX);
			else
				setPixel (x += stepX, y += stepY);
		return;
	}

	/*算法核心*/
	for (i = 0; i < dxAbs; i++, x += stepX){
		if (pk < 0){
			pk += twoDyAbs;
		}else {
			y += stepY;
			pk += twoDyMinusDxAbs;
		}
		if (flag == 1) setPixel(y, x);
		else setPixel(x, y);
	}
	glFlush();
}


void myDisplay(void){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0,0.4,0.2);
    Bresenham(100,200,700,1200,0);//绿色 k>1
    glColor3f(0.0,0.0,0.0);
    Bresenham(50,60,600,500,0);//黑色 0<k<1
    glColor3f(1.0,0.0,0.0);
    Bresenham(100,800,800,150,0);//红色 -1<k<0
    glColor3f(1.0, 1.0, 0.0);
    Bresenham(80,1000,500,400,0);//黄色 k<-1
}

int main(int argc,char * argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutCreateWindow("Bresenham算法");
    init();
    glutDisplayFunc(myDisplay);
    glutMainLoop();
    return 0;
}