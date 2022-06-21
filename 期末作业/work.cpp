#include <windows.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include<iostream>
#define BITMAP_ID 0x4D42
#define Height 16
#define Width 16


static GLfloat xRotate = 0.0;//x方向旋转角度
static GLfloat yRotate = 0.0;//y方向旋转角度
static GLfloat controlValue = 10.0;

GLuint texture[2];
int status;

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

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);//用关照计算当前材质的属性
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

 }

 //读纹理图片
unsigned char *LoadBitmapFile(char *filename, BITMAPINFOHEADER *bitmapInfoHeader)
{
    FILE *filePtr;    // 文件指针
    BITMAPFILEHEADER bitmapFileHeader;    // bitmap文件头
    unsigned char*bitmapImage;        // bitmap图像数据
    int imageIdx = 0;        // 图像位置索引
    unsigned char tempRGB;    // 交换变量

    // 以“二进制+读”模式打开文件filename
    filePtr = fopen(filename, "rb");
    if (filePtr == NULL) {
        printf("file not open\n");
        return NULL;
    }
    // 读入bitmap文件图
    fread(&bitmapFileHeader, sizeof(BITMAPFILEHEADER), 1, filePtr);
    // 验证是否为bitmap文件
    if (bitmapFileHeader.bfType != BITMAP_ID) {
        fprintf(stderr, "Error in LoadBitmapFile: the file is not a bitmap file\n");
        return NULL;
    }
    // 读入bitmap信息头
    fread(bitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, filePtr);
    // 将文件指针移至bitmap数据
    fseek(filePtr, bitmapFileHeader.bfOffBits, SEEK_SET);
    // 为装载图像数据创建足够的内存
    bitmapImage = new unsigned char[bitmapInfoHeader->biSizeImage];
    // 验证内存是否创建成功
    if (!bitmapImage) {
        fprintf(stderr, "Error in LoadBitmapFile: memory error\n");
        return NULL;
    }

    // 读入bitmap图像数据
    fread(bitmapImage, 1, bitmapInfoHeader->biSizeImage, filePtr);
    // 确认读入成功
    if (bitmapImage == NULL) {
        fprintf(stderr, "Error in LoadBitmapFile: memory error\n");
        return NULL;
    }
    //由于bitmap中保存的格式是BGR，下面交换R和B的值，得到RGB格式
    for (imageIdx = 0;imageIdx < bitmapInfoHeader->biSizeImage; imageIdx += 3) {
        tempRGB = bitmapImage[imageIdx];
        bitmapImage[imageIdx] = bitmapImage[imageIdx + 2];
        bitmapImage[imageIdx + 2] = tempRGB;
    }
    // 关闭bitmap图像文件
    fclose(filePtr);
    return bitmapImage;
}

//加载纹理的函数
void texload(int i, char *filename)
{
    BITMAPINFOHEADER bitmapInfoHeader;                                 // bitmap信息头
    unsigned char*   bitmapData;                                       // 纹理数据

    bitmapData = LoadBitmapFile(filename, &bitmapInfoHeader);
    glBindTexture(GL_TEXTURE_2D, texture[i]);
    // 指定当前纹理的放大或缩小过滤方式
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D,
        0,         //mipmap层次(通常为，表示最上层)
        GL_RGB,    //纹理有红、绿、蓝数据
        bitmapInfoHeader.biWidth, //纹理宽带
        bitmapInfoHeader.biHeight, //纹理高度
        0, //边框(0=无边框, 1=有边框)
        GL_RGB,    //bitmap数据的格式
        GL_UNSIGNED_BYTE, //每个颜色数据的类型
        bitmapData);    //bitmap数据指针
}

//定义纹理的函数
void initWenli()
{
    glGenTextures(2, texture); // 第一参数是需要生成标示符的个数, 第二参数是返回标示符的数组
    texload(0, "C://Users//HUAWEI//Desktop//huawen.bmp");//茶壶花纹
    texload(1, "C://Users//HUAWEI//Desktop//huawen1.bmp");//另外一个花纹
}

//显示函数
void display(void)
{
     // 清除之前的深度缓存
     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
     glLoadIdentity();
     // 与显示相关的函数
     glEnable(GL_TEXTURE_2D);
     glBindTexture(GL_TEXTURE_2D, texture[status]);  //选择纹理texture[status]
     glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);//设置纹理受光照影响
     gluLookAt(20.0,20.0,10.0,0.0,0.0,0.0,0.0,1.0,0.0);
     glRotatef(xRotate, 1.0f, 0.0f, 0.0f);
     glRotatef(yRotate, 0.0f, 1.0f, 0.0f);
     //生成茶壶
     glutSolidTeapot(50.0);

     glDisable(GL_TEXTURE_2D);    //关闭纹理texture[status]
     glFlush();
     glutSwapBuffers();
}

//维持图形比例
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

//键盘回调函数
void myKeyboard(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_DOWN:
    {
        xRotate = xRotate + 2.0;
        if (xRotate > 360)
            xRotate = xRotate - 360.0;
        glutPostRedisplay();
        break;
    }
    case GLUT_KEY_UP:
    {
        xRotate = xRotate - 2.0;
        if (xRotate > 360)
            xRotate = xRotate - 360.0;
        glutPostRedisplay();
        break;
    }
    case GLUT_KEY_LEFT:
    {
        yRotate = yRotate - 2.0;
        if (yRotate > 360)
            yRotate = yRotate - 360.0;
        glutPostRedisplay();
        break;
    }
    case GLUT_KEY_RIGHT:
    {
        yRotate = yRotate + 2.0;
        if (yRotate > 360)
            yRotate = yRotate - 360.0;
        glutPostRedisplay();
        break;
    }
    case GLUT_KEY_F1: { //切换茶壶纹理
        if (status == 0)status = 1;
        else if (status == 1)status = 0;
        glutPostRedisplay();
        break;
    }
    default:
        break;
    }
}

int main(int argc, char** argv)
{
     status = 0;//默认选用第一种花纹
     printf("按下上/下/左/右键，茶壶向前/后/左/右方向旋转\n");
     printf("按下F1,切换茶壶表面花纹\n");
     glutInit(&argc, argv);
     glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
     glutInitWindowSize(960, 960);
     glutInitWindowPosition(100, 100);
     glutCreateWindow("Teapot");
     init();
     initWenli();
     glutDisplayFunc(display);//注册绘图函数
     glutReshapeFunc(reshape);//注册调整窗口大小变化时的响应函数
     glutSpecialFunc(&myKeyboard);//注册键盘回调函数
     glutMainLoop();
     return 0;
}

