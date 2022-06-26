#include "Windows.h"
#include "math.h"
#include <iostream>
#include <gl/glut.h>
using namespace std;

int s1, s2, s3;    //视角位置，全局变量

void Init()
{
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
}

void Line(void)
{
    //坐标轴
    glLineWidth(2.0); glColor3f(0.0, 0.0, 0.0);

    glBegin(GL_LINES);
    glVertex3i(0, 0, 0);glVertex3i(400, 0, 0);
    glVertex3i(0, 0, 0);glVertex3i(0, 300, 0);
    glVertex3i(0, 0, 0);glVertex3i(0, 0, 300);

    glEnd();
    glFlush();
}

void buffer(void)
{
 //顶点表
    int x[10] = { 80, 100, 50, 0, 20, 80, 100, 50, 0, 20 };
    int y[10] = { 0, 80, 120, 80, 0, 0, 80, 120,80, 0 };
    int z[10] = { 140,140,140,140,140, 0, 0, 0, 0,0 };
//面点表
    int f[7] = { 0,1,2,3,4,5,6 }; //面的号码
    int p[7] = { 6,5,6,5,5,5,5 }; //面的顶点数
    int fp[7][6] = { {0,1,2,3,4,0},{0,5,6,1,0,0},{5,9,8,7,6,5},{9,4,3,8,9,0},
    {1,6,7,2,1,0},{3,2,7,8,3,0},{0,4,9,5,0,0} }; //面的顶点序
    int i, j, k, SN;
    int p1, p2, p3, u1, u2, u3, v1, v2, v3;
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(s1, s2, s3, 0, 0, 0, 0, 1, 0);
    Line();
    glLineWidth(3); glColor3f(0.0, 1.0, 0.0);
 //算法
    for (i = 0; i < 7; i++)
    {
        p1 = fp[i][0]; p2 = fp[i][1]; p3 = fp[i][2]; //取前三个顶点
        //计算法线
        u1 = x[p2] - x[p1]; u2 = y[p2] - y[p1]; u3 = z[p2] - z[p1];
        v1 = x[p3] - x[p2]; v2 = y[p3] - y[p2]; v3 = z[p3] - z[p2];
        //计算法线与视角的点乘
        SN = s1*(u2 * v3 - u3 * v2) + s2*(u3 * v1 - u1 * v3) + s3*(u1 * v2 - u2 * v1);
        if (SN < 0) f[i] = -1;       //法线与视角点乘小于零
    }
    for (i = 0; i < 7; i++)
    {//消隐的部分
        if (f[i] == -1)
        {
            glEnable(GL_LINE_STIPPLE);
            glLineStipple(2, 0x3333);
            glBegin(GL_LINE_STRIP);
            for (j = 0; j < p[i]; j++)
            {
                k = fp[i][j]; glVertex3i(x[k], y[k], z[k]);

            }
           // Sleep(1000);
            glEnd(); glFlush();
            glDisable(GL_LINE_STIPPLE);
        }
        //可见的部分
        else
        {
            glBegin(GL_LINE_STRIP);
            for (j = 0; j < p[i]; j++)
            {
                k = fp[i][j]; glVertex3i(x[k], y[k], z[k]);
            }

            glEnd(); glFlush();
        }
    }
}

void Reshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
//3D
    glOrtho(-w/2,w/2,-h/2,h/2,-300,300);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}



int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    cout << "请输入视角（如：1 1 1）" << endl;
    cin >> s1 >> s2 >> s3;
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(840, 680);
    glutCreateWindow("test_15");

    Init();

    glutDisplayFunc(buffer);
    glutReshapeFunc(Reshape);

    glutMainLoop();
    return 0;

}