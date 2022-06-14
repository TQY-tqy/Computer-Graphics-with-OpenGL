#include<windows.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdio.h>
#include <stdlib.h>

GLsizei winWidth = 400, winHeight = 300;


void init(void){
    glClearColor(1.0,1.0,1.0,0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0,1000.0,0.0,2000.0);
}

void displayFun(void){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0,0.0,0.0);
    glPointSize(3.0);
}


void winReshapeFun(GLint newWidth, GLint newHeight){
    glViewport(0,0,newWidth,newHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0,GLdouble(newWidth),0.0,GLdouble(newHeight));
    winWidth = newWidth;
    winHeight = newHeight;
}

void plotPoint(GLint x, GLint y){
    glBegin(GL_POINTS);
    glVertex2i(x,y);
    glEnd();
}

void mousePtPlot(GLint button, GLint action, GLint xMouse, GLint yMouse){
    if(button == GLUT_LEFT_BUTTON && action == GLUT_DOWN)
        plotPoint(xMouse,winHeight-yMouse);

    glFlush();
}


int main(int argc,char * argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowPosition(200,200);
    glutInitWindowSize(winWidth,winHeight);
    glutCreateWindow("test_7");
    init();
    glutDisplayFunc(displayFun);
    glutReshapeFunc(winReshapeFun);
    glutMouseFunc(mousePtPlot);
    glutMainLoop();
    return 0;
}
