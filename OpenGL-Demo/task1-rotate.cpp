#include <opengl/freeglut.h>

#define STEP 2.0f

// 旋转初始的角度
GLfloat angle = 0.0f;
// 设置旋转轴：两个三维的点确定的旋转轴
GLfloat axis[][3] = {
	0.0f, 0.5f, 0.5f,
	1.0f, 0.5f, 0.5f
};


void display()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);   // 清除屏幕、深度及颜色缓存
	// 深度测试开启，实现遮挡关系
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glLoadIdentity();
	gluLookAt(2, 2, 2, 0.0, 0.0, 0.0, -1, -1, 1);
	// 设置绕给定的轴旋转
	glTranslatef(axis[0][0], axis[0][1], axis[0][2]);
	glRotatef(angle, axis[1][0] - axis[0][0], axis[1][1] - axis[0][1], axis[1][2] - axis[0][2]);
	glTranslatef(-axis[0][0], -axis[0][1], -axis[0][2]);
	// 设置立方体的八个顶点坐标
	static const GLfloat vertex[][3] = {
		0.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f
	};
	// 设置绘制六个面时顶点的顺序
	static const GLint index[][4] = {
		0, 2, 3, 1,
		0, 4, 6, 2,
		0, 1, 5, 4,
		4, 5, 7, 6,
		1, 3, 7, 5,
		2, 6, 7, 3
	};
	// 绘制六个面
	glBegin(GL_QUADS);
	for (int i = 0; i < 6; i++) {
		if (i == 2 || i == 5) continue;
		for (int j = 0; j < 4; j++) {
			glColor3fv(vertex[index[i][j]]);
			glVertex3fv(vertex[index[i][j]]);
		}
	}
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.25f, 0.5f, 0.5f);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.75f, 0.5f, 0.5f);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.75f, 1.0f, 0.5f);
	glVertex3f(0.25f, 1.0f, 0.5f);
	glEnd();

	glutSwapBuffers();
}

// 动画所需的定时器回调函数
void timer_function(GLint value)
{
	angle += STEP;
	if (angle >= 360.0) angle -= 360.0;
	glutPostRedisplay();
	glutTimerFunc(25, timer_function, value);
}

// 窗口大小自适应函数，使得窗口大小改变时仍保持图形的比例不变
void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(2, 2, 2, 0.0, 0.0, 0.0, -1, -1, 1);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("task1-rotate");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutTimerFunc(100, timer_function, 1);
	glutMainLoop();
	return 0;
}