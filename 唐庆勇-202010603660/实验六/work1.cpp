#include <windows.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#define pi 3.1415

typedef struct node{
    float x;
    float y;
}wcPt;

void init(void){
    glClearColor(1.0,1.0,1.0,0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0,1000.0,0.0,2000.0);
}

void triangle(wcPt* verts){
    GLint k;
    glBegin(GL_TRIANGLES);
    for(k = 0; k < 3; k++) glVertex2f(verts[k].x, verts[k].y);
    glEnd();
    glFlush();
}

void translate2D(GLfloat tx, GLfloat ty, GLint n, wcPt*verts){//平移
    GLint k;
    for(k = 0; k < n; k++){
        verts[k].x = verts[k].x + tx;
        verts[k].y = verts[k].y + ty;
    }
    glColor3f(1.0,0.0,0.0);//红色为平移变换
    triangle(verts);
}

void rotate2D(GLint n, wcPt*verts, wcPt pivPt, GLdouble theta){//旋转
    GLint k;
    wcPt vertsRot[3];
    for(k = 0; k < n; k++){
        vertsRot[k].x = pivPt.x + (verts[k].x - pivPt.x)*cos(theta) - (verts[k].y - pivPt.y)*sin(theta);
        vertsRot[k].y = pivPt.y + (verts[k].x - pivPt.x)*sin(theta) + (verts[k].y - pivPt.y)*cos(theta);
    }
    glColor3f(0.0,0.4,0.2);//深绿色为旋转变换
    triangle(vertsRot);
}

void scale2D(GLfloat sx, GLfloat sy, GLint n, wcPt*verts, wcPt fixedPt){//比例
    GLint k;
    wcPt vertsNew[3];
    for(k = 0; k < n; k++){
        vertsNew[k].x = verts[k].x*sx + fixedPt.x*(1-sx);
        vertsNew[k].y = verts[k].y*sy + fixedPt.y*(1-sy);
    }
    glColor3f(1.0, 1.0, 0.0);//黄色为比例变换
    triangle(vertsNew);
}

void symmetry2D(GLint n, wcPt*verts){//对称
    GLint k;
    wcPt vertsSym[3];
    for(k = 0; k < n; k++){
        vertsSym[k].x = verts[k].x;
        vertsSym[k].y = - verts[k].y + 500;
    }
    glColor3f(0.0,0.0,0.0);//黑色为关于y = 50 对称
    triangle(vertsSym);
}


void myDisplay(void){
    GLint n = 3;
    wcPt verts[3] = {{351,324},{452,324},{399,399}};
    wcPt centPt;
    GLint k, xsum = 0, ysum = 0;
    for(k = 0; k < n; k++){
        xsum += verts[k].x;
        ysum += verts[k].y;
    }

    centPt.x = GLfloat(xsum)/GLfloat(n);
    centPt.y = GLfloat(ysum)/GLfloat(n);

    wcPt pivPt, fixedPt;
    pivPt = centPt;
    fixedPt = centPt;

    GLfloat tx = 200, ty = 100;
    GLfloat sx = 2 ,sy = 0.5;
    GLdouble theta = 180*pi/180;

    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.0, 0.0,0.0);
	glBegin(GL_LINES);
	glVertex2f(0.0, 100.0);
	glVertex2f(900.0, 100.0);
	glEnd();
	glFlush();
	glBegin(GL_LINES);
	glVertex2f(50.0, 25.0);
	glVertex2f(50.0,1500.0);
	glEnd();
	glFlush();
    glColor3f(0.0,0.0,1.0);
    triangle(verts);//蓝色为原始的三角形
    symmetry2D(n,verts);//对称
    translate2D(tx,ty,n,verts);//平移
    rotate2D(n,verts,pivPt,theta);//旋转
    scale2D(sx,sy,n,verts,fixedPt);//比例

}

int main(int argc,char * argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowPosition(200,200);
    glutInitWindowSize(600,600);
    glutCreateWindow("二维变换");
    init();
    glutDisplayFunc(myDisplay);
    glutMainLoop();
    return 0;
}
