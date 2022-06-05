//DDA画线算法
#include<windows.h>
#include <GLUT/glut.h>
#include<string.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

inline int round (const float a){
    return int(a+0.5);//四舍五入
}

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

void DDALine(int x0, int y0, int xEnd, int yEnd){
    int dx = xEnd - x0, dy = yEnd - y0, max, k;
    GLfloat xIncrement, yIncrement, x = x0, y = y0;
    //算法核心
    if(fabs(dx)>fabs(dy)) max = fabs(dx);
    else max = fabs(dy);
    xIncrement = (GLfloat)dx/(GLfloat)max;
    yIncrement = (GLfloat)dy/(GLfloat)max;
    setPixel(round(x), round(y));//绘制初始点
    for(k = 0; k < max; k++){
        x += xIncrement;
        y += yIncrement;
        setPixel(round(x), round(y));
    }
    glFlush();
}

void myFunc(void){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0,0.4,0.2);
    DDALine(100,200,700,1200);//绿色 k>1
    glColor3f(0.0,0.0,0.0);
    DDALine(50,60,600,500);//黑色 0<k<1
    glColor3f(1.0,0.0,0.0);
    DDALine(100,800,800,150);//红色 -1<k<0
    glColor3f(1.0, 1.0, 0.0);
    DDALine(80,1000,500,400);//黄色 k<-1
}

int main(int argc,char * argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutCreateWindow("DDA算法");
    init();
    glutDisplayFunc(myFunc);
    glutMainLoop();
    return 0;
}


