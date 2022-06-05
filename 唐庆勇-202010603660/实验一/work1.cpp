#include <windows.h>
#include <GL/glut.h>

void init(void){
    glClearColor(1.0,1.0,1.0,0.0);//窗口背景颜色为白色
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0,200.0,0.0,150.0);//x坐标从0到200，y坐标从0到150
}

void lineSegment(void){
    glClear(GL_COLOR_BUFFER_BIT);//创建显示窗口
    glColor3f(0.0,0.4,0.2);//直线颜色为深绿色
    glBegin(GL_LINES);//画直线
    glVertex2i(180,15);
    glVertex2i(10,145);
    glEnd();
    glFlush();
}

int main(int argc, char** argv){
    glutInit(&argc, argv);//GLUT初始化
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);//创建颜色模型
    glutInitWindowPosition(50,100);
    glutInitWindowSize(400,300);
    glutCreateWindow("test_1");//标题
    init();
    glutDisplayFunc(lineSegment);
    glutMainLoop();//完成窗口处理操作

    return 0;
}