#include<windows.h>
#include<GL/glut.h>
#include<math.h>
#include<stdio.h>
#include<stdlib.h>

#define pi 3.14159

float theta = 0;
float tx = 0;
float ty = 0;
float tz = 0;
float total = 0;
int flag = 0;

typedef struct{
    GLfloat x;
    GLfloat y;
    GLfloat z;
}wcPt3D;

wcPt3D verts[4] ={{0.0,1.63,0},{-1.0,0.0,0.58},{1.0f,0.0f,0.58f},{0.0f,0.0f,-1.15f}};//定义一个三棱锥

typedef GLfloat Matrix4x4[4][4];
Matrix4x4 matComposite;//3D变换复合矩阵

void Matrix4x4SetIdentity(Matrix4x4 matIdent4x4)
{
	//生成一个单位矩阵
	GLint row, col;
	for (row = 0; row < 4;++row)
	for (col = 0; col < 4;++col)
	{
		matIdent4x4[row][col] = (row==col);
	}
}
void matrix4x4Premultiply(Matrix4x4 m1, Matrix4x4 m2)
{
   //矩阵的乘法，结果储存在M2中
	GLint row, col;
	Matrix4x4 matTemp;
	for (row = 0; row < 4; ++row)
        for (col = 0; col < 4; col++){
                matTemp[row][col] = m1[row][0] * m2[0][col] + m1[row][1] * m2[1][col] + m1[row][2] * m2[2][col]+ m1[row][3]*m2[3][col];
	}
	for (row = 0; row < 4; ++row)
        for (col = 0; col < 4; col++){
            m2[row][col] = matTemp[row][col];
	}
}


void translate3D(GLfloat tx, GLfloat ty, GLfloat tz)
{
	/*通过偏移量tx,ty产生平移矩阵matTransl之后，再通过矩阵的乘法，实现对象的平移*/
	Matrix4x4 matTransl;//平移矩阵
	Matrix4x4SetIdentity(matTransl);
	matTransl[0][3] = tx;
	matTransl[1][3] = ty;
	matTransl[2][3] = tz;
	/*矩阵乘法，平移*/
	matrix4x4Premultiply(matTransl,matComposite);
}
void rotate3D(GLfloat theta)
{

	Matrix4x4 matRot;//旋转矩阵
	/*假设饶Y轴旋转*/
	Matrix4x4SetIdentity(matRot);
	matRot[0][0] = cos(theta);
	matRot[0][2] = -sin(theta);
	matRot[2][0] = sin(theta);
	matRot[2][2] = cos(theta);
	/*矩阵乘法，旋转*/
	matrix4x4Premultiply(matRot, matComposite);
}

void after3D(GLint nverts, wcPt3D *verts)
{
   //对象顶点与复合变换矩阵的乘法，得到坐标变换后的点
	GLint k;
	GLfloat tempx,tempy,tempz;
	for (k = 0; k < nverts; k++)
	{
		tempx = verts[k].x*matComposite[0][0] + verts[k].y*matComposite[0][1] + verts[k].z*matComposite[0][2]+matComposite[0][3];
		tempy = verts[k].x*matComposite[1][0] + verts[k].y*matComposite[1][1] + verts[k].z*matComposite[1][2]+matComposite[1][3];
		tempz = verts[k].x*matComposite[2][0] + verts[k].y*matComposite[2][1] + verts[k].z*matComposite[2][2]+matComposite[2][3];
		verts[k].x = tempx;
		verts[k].y = tempy;
		verts[k].z = tempz;
	}
}

void triangle() //该三棱锥以原点为中心
{
     Matrix4x4SetIdentity(matComposite);
     if(flag == 1) rotate3D(theta);//旋转
     if(flag == 2) translate3D(tx,ty,tz);//平移
	 after3D(4,verts);
	 glBegin(GL_TRIANGLES);
	  glColor3f(1.0f,0.0f,0.0f);	  //前面为红色
	  glVertex3f(verts[0].x, verts[0].y, verts[0].z);	//前面三角形上顶点
	  glVertex3f(verts[1].x, verts[1].y, verts[1].z);  //前面三角形左顶点
	  glVertex3f(verts[2].x, verts[2].y, verts[2].z);	//前面三角形右顶点

	  glColor3f(0.0f,1.0f,0.0f);		//左面为绿色
	  glVertex3f(verts[0].x, verts[0].y, verts[0].z);	//左面三角形上顶点
	  glVertex3f(verts[3].x, verts[3].y, verts[3].z);	//左面三角形左顶点
	  glVertex3f(verts[1].x, verts[1].y, verts[1].z);	 //左面三角形右顶点

	  glColor3f(0.0f,0.0f,1.0f);		//右面为蓝色
	  glVertex3f(verts[0].x, verts[0].y, verts[0].z);  //背面三角形上顶点
	  glVertex3f(verts[3].x, verts[3].y, verts[3].z);	 //背面三角形左顶点
	  glVertex3f(verts[2].x, verts[2].y, verts[2].z);	//背面三角形右顶点
	glEnd();
	glBegin(GL_TRIANGLES);  //三棱锥底面三角形
      glColor3f(0.5f,0.5f,0.5f);  //底面为灰色
	  glVertex3f(verts[1].x, verts[1].y, verts[1].z);
	  glVertex3f(verts[2].x, verts[2].y, verts[2].z);
	  glVertex3f(verts[3].x, verts[3].y, verts[3].z);
	glEnd();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT); //清空颜色和深度缓存
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//gluLookAt(2.0, 2.0, 2.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	glTranslatef(0.0f,0.0f,-5.0f);
	triangle();
	glutSwapBuffers();
}

void reshape(int w, int h) //重绘回调函数，在窗口首次创建或用户改变窗口尺寸时被调用
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glFrustum(-1.0, 1.0, -1.0, 1.0, 3.1, 10.0);
	//gluPerspective(45,1,0.1,10.0);
	glOrtho(-2.0, 2.0, -2.0, 3.0, 2.0, 10.0);
}

void init()
{
	glClearColor (1.0, 1.0, 1.0, 1.0);
	glEnable(GL_DEPTH_TEST);     //启动深度测试模式
}

void myKeyboard(unsigned char key,  int x, int y)
{
	if(key == 'a' || key == 'A'){
        theta = pi/180*4;
        flag = 1;
	}
	if(key == 'd' || key == 'D'){
        theta = -pi/180*4;
        flag = 1;
	}
	if(key == 'w' || key == 'W'){
        tx = ty = tz = 1;
        total++;
        flag = 2;
	}
    if(key == 's' || key == 'S'){
        tx = ty = tz = -1;
        total--;
        flag = 2;
    }
    if(key == 'c' || key == 'C')
		exit(0);
	if (total>3){
        tx = ty = tz = -5;
        total = total - 6;
	}
	if (total <-3){
        tx = ty = tz = 5;
        total = total + 6;
	}
	glutPostRedisplay(); //重新调用绘制函数
}

int main(int argc, char** argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode (GLUT_DEPTH |GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(0,0);
	glutCreateWindow("三棱锥---A键:顺时针旋转,D键:逆时针旋转,W键:向右上角平移，S键：向下平移；C键:退出");
	glutReshapeFunc(reshape); //指定重绘回调函数
	glutDisplayFunc(display);
	glutKeyboardFunc( myKeyboard);   //指定键盘回调函数
	init();
	glutMainLoop();
}
