#include <opengl/freeglut.h>

void drawCoord() {
	glBegin(GL_LINES);
	glColor3f(1.0, 0.0, 0.0);	// 红色-x轴
	glVertex3f(-6.0, 0.0, 0.0);
	glVertex3f(6.0, 0.0, 0.0);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0.0, 1.0, 0.0);	// 绿色-y轴
	glVertex3f(0.0, 0.0, -6.0);
	glVertex3f(0.0, 0.0, 6.0);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 1.0);	// 蓝色-z轴
	glVertex3f(0.0, -6.0, 0.0);
	glVertex3f(0.0, 6.0, 0.0);
	glEnd();
}

void display()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);   // 清除屏幕、深度及颜色缓存
	// 深度测试开启，实现遮挡关系
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	
	glLoadIdentity();
	gluLookAt(5.0, 3.0, 4.0, 2.0, 0.0, 0.0, -1, 1, -1);

	drawCoord();
	
	glTranslatef(1.5, 0, 0);
	glutWireSphere(0.5, 50, 20);
	
	glutSwapBuffers();
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
	
	glutMainLoop();
	return 0;
}