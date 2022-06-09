#include <windows.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>

float r;//r是圆的半径
void init(void){
    glClearColor(1.0,1.0,1.0,0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0,1000.0,0.0,1000.0);
}

void setPixel(GLint x, GLint y){
    glBegin(GL_POINTS);
    glVertex2i(x,y);
    glEnd();
}

//八分画圆
void CirclePoints(int x,int tx,int y,int ty){
    setPixel(x + tx, y + ty);
    setPixel(x - tx, y + ty);
    setPixel(x + tx, y - ty);
    setPixel(x - tx, y - ty);
    setPixel(x + ty, y + tx);
    setPixel(x - ty, y + tx);
    setPixel(x + ty, y - tx);
    setPixel(x - ty, y - tx);
}


void drawCircle(int x,int y, int r){
    int tx = 0,ty = r,d = 1.25 - r;

    CirclePoints(x,tx,y,ty);
    while(tx <= ty){
        //利用圆的八分对称性画点

        if(d<0) d+=2*tx+3;
        else{
            d+=2*(tx - ty) + 5;
            ty--;
            }
        tx++;
        CirclePoints(x,tx,y,ty);
    }
    glFlush();
}

void myDisplay(void){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0,0.0,0.0);
    drawCircle(500,500,r);
}

int main(int argc,char * argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowPosition(200,200);
    glutInitWindowSize(300,300);
    printf("请输入圆的半径\n");
    scanf("%f",&r);

    glutCreateWindow("中点画圆算法");
    init();
    glutDisplayFunc(myDisplay);
    glutMainLoop();
    return 0;
}
