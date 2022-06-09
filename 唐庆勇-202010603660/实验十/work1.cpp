#include <windows.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdlib.h>

GLsizei winWidth = 500, winHeight = 500;
GLfloat xComplexMin = -2.00, xComplexMax = 0.50;
GLfloat yComplexMin = -1.25, yComplexMax = 1.25;

GLfloat complexWidth = xComplexMax - xComplexMin;
GLfloat complexHeight = yComplexMax - yComplexMin;

typedef struct Num{
    GLfloat x,y;
}complexNum;

typedef struct yanse{
    GLfloat r,g,b;
}color;

void init(){
    glClearColor(1.0,1.0,1.0,1.0);
}

void plotPoint(complexNum z){
    glBegin(GL_POINTS);
    glVertex2f(z.x,z.y);
    glEnd();
}

complexNum complexSquare(complexNum z){
    complexNum zSquare;
    zSquare.x = z.x*z.x - z.y*z.y;
    zSquare.y = 2*z.x*z.y;
    return zSquare;
}

GLint mandelSqTransf(complexNum z0, GLint maxIter){
    complexNum z = z0;
    GLint counts = 0;

    while((z.x*z.x + z.y*z.y <=4)&&(counts<maxIter)){
            z = complexSquare(z);
            z.x += z0.x;
            z.y += z0.y;
            counts++;
    }
    return counts;
}

void mandelbrot(GLint nx, GLint ny, GLint maxIter){
    complexNum z, zIncr;
    color ptColor;
    GLint iterCount;

    zIncr.x = complexWidth/GLfloat(nx);
    zIncr.y = complexHeight/GLfloat(ny);

    for(z.x = xComplexMin; z.x < xComplexMax; z.x+= zIncr.x)
        for(z.y = yComplexMin; z.y < yComplexMax; z.y+= zIncr.y){
            iterCount = mandelSqTransf(z,maxIter);
            if(iterCount >= maxIter) ptColor.r = ptColor.g = ptColor.b = 0.0;
            else if(iterCount > (maxIter / 8)){
                ptColor.r = 1.0;
                ptColor.g = 0.5;
                ptColor.b = 0.0;
            }else if(iterCount > (maxIter / 10)){
                ptColor.r = 1.0;
                ptColor.g = ptColor.b = 0.0;
            }else if(iterCount > (maxIter / 20)){
                ptColor.b = 0.5;
                ptColor.g = ptColor.r = 0.0;
            }else if(iterCount > (maxIter / 40)){
                ptColor.r = ptColor.g = 1.0;
                ptColor.b = 0.0;
            }else if(iterCount > (maxIter / 100)){
                ptColor.r = ptColor.b = 0.0;
                ptColor.g = 0.3;
            }else{
                ptColor.r = 0.0;
                ptColor.g = ptColor.b = 1.0;
            }
        glColor3f(ptColor.r,ptColor.g,ptColor.b);
        plotPoint(z);
    }
}

void displayFcn(void){
    GLint nx = 1000, ny = 1000, maxIter = 1000;
    glClear(GL_COLOR_BUFFER_BIT);
    mandelbrot(nx,ny,maxIter);
    glFlush();
}

void winReshapeFcn(GLint newWidth, GLint newHeight){
    glViewport(0,0,newHeight,newHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(xComplexMin,xComplexMax,yComplexMin,yComplexMax);
    glClear(GL_COLOR_BUFFER_BIT);
}

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowPosition(50,50);
    glutInitWindowSize(winWidth,winHeight);
    glutCreateWindow("Mandelbrot Set");

    init();
    glutDisplayFunc(displayFcn);
    glutReshapeFunc(winReshapeFcn);

    glutMainLoop();
}

