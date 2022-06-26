#include<windows.h>
#include<iostream>
#include<GL/glut.h>

using namespace std;
static GLfloat xRotate = 0.0;
static GLfloat yRotate = 0.0;
static GLfloat controlValue = 10.0;

void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_SMOOTH);

    // 定义光源
    GLfloat light_position[] = { -100.0,100.0,100.0,1.0 };  // （点）光源的位置
    GLfloat light_ambient[] = { 0.1f,0.1f,0.1f,1.0f };  // 环境光
    GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };  // 漫反射光，白色
    GLfloat light_specular[] = { 0.8f,0.8f,0.8f,1.0f };  // 镜面反射光，白色
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

    // 开启光源
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);

    // 定义壶的材质
    GLfloat mat_ambient[] = { 0.1f,0.1f,0.1f,1.0f };
    GLfloat mat_diffuse[] = { 0.8f,0.8f,0.8f,1.0f };  // 材质的漫反射光，白色
    GLfloat mat_specular[] = { 0.8f,0.8f,0.8f,1.0f };  // 材质的镜面反射光，白色
    GLfloat mat_emission[] = { 0.0f,0.0f,0.0f,1.0f };  // 材质的幅射光，黑色
    GLfloat mat_shininess[] = { 5.0 };

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

 }

void display(void)
{
     // 清除之前的深度缓存
     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
     glLoadIdentity();

     // 与显示相关的函数
     gluLookAt(20.0,20.0,10.0,0.0,0.0,0.0,0.0,1.0,0.0);
     glRotatef(xRotate, 1.0f, 0.0f, 0.0f);
     glRotatef(yRotate, 0.0f, 1.0f, 0.0f);
     glutSolidTeapot(50.0);

     glFlush();
     glutSwapBuffers();
}

void spinDisplay(void)
{
     xRotate = xRotate + 2.0;
     if (xRotate > 360)
         xRotate = xRotate - 360.0;
     glutPostRedisplay();
}

void reshape(int w, int h)
{
     glViewport(0, 0, (GLsizei)w, (GLsizei)h);
     glMatrixMode(GL_PROJECTION);
     glLoadIdentity();

     if (w <= h)
         glOrtho(-200, 200, -200 * (GLfloat)h / (GLfloat)w, 200 * (GLfloat)h / (GLfloat)w, -100.0, 100.0);
     else
         glOrtho(-200 * (GLfloat)w / (GLfloat)h, 200 * (GLfloat)w / (GLfloat)h, -200, 200, -100.0, 100.0);
     glMatrixMode(GL_MODELVIEW);
     glLoadIdentity();
}

int main(int argc, char** argv)
{
     glutInit(&argc, argv);
     glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
     glutInitWindowSize(960, 960);
     glutInitWindowPosition(100, 100);
     glutCreateWindow("光照模型");
     init();
     glutDisplayFunc(display);
     glutReshapeFunc(reshape);

     glutMainLoop();
     return 0;
}
