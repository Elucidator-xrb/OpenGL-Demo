#include <opengl/freeglut.h>
#include "CBMPLoader.h"

GLuint tex2D;

GLfloat cube_v[][3] = {
    0.0, 0.0, 0.0,
    1.0, 0.0, 0.0,
    0.0, 1.0, 0.0,
    1.0, 1.0, 0.0,
    0.0, 0.0, 1.0,
    1.0, 0.0, 1.0,
    0.0, 1.0, 1.0,
    1.0, 1.0, 1.0
};

GLfloat cube_n[][3] = {
    0.0, 0.0, -1.0,
    -1.0, 0.0, 0.0,
    0.0, -1.0, 0.0,
    0.0, 0.0, 1.0,
    1.0, 0.0, 0.0,
    0.0, 1.0, 0.0
};

GLfloat cube_t[][2] = {
    0.0, 0.0,
    1.0, 0.0,
    1.0, 1.0,
    0.0, 1.0
};

GLint order[][4] = {
    0, 2, 3, 1,
    0, 4, 6, 2,
    0, 1, 5, 4,
    4, 5, 7, 6,
    1, 3, 7, 5,
    2, 6, 7, 3
};

void loadTexture() {
    CBMPLoader bmpLoader;
    bmpLoader.LoadBitmap("./texture-self.bmp");
    glGenTextures(1, &tex2D);   // 创建纹理
    glBindTexture(GL_TEXTURE_2D, tex2D);
    // 纹理滤波参数设置
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bmpLoader.imageWidth, bmpLoader.imageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, bmpLoader.image);
}

void drawCube() {
    glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, tex2D);    // 选择之前备好的tex2D纹理
    glBegin(GL_QUADS);
    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 4; ++j) {
            glTexCoord2fv(cube_t[j]);
            glVertex3fv(cube_v[order[i][j]]);
        }
    }
    glEnd();
    
    glDisable(GL_TEXTURE_2D);
}


void display() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);   // 换一个试试，means '<'；之前的GL_LEQUAL means '<='
    glShadeModel(GL_SMOOTH);
    
    glLoadIdentity();
    gluLookAt(2.0, 2.0, 2.0, 0.0, 0.0, 0.0, -1, 1, -1);

    drawCube();

    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(2, 2, 2, 0.0, 0.0, 0.0, -1, -1, 1);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("texture mapping");
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    loadTexture();
    glutMainLoop();
    return 0;
}