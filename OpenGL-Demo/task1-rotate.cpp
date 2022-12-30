#include <opengl/freeglut.h>

GLfloat angle = 0.0;	// 旋转相关： 角度和转轴

GLfloat axis[][3] = {
	0.0, 0.5, 0.5,
	1.0, 0.5, 0.5
};

static const GLfloat cube_v[][3] = {
	0.0, 0.0, 0.0,
	1.0, 0.0, 0.0,
	0.0, 1.0, 0.0,
	1.0, 1.0, 0.0,
	0.0, 0.0, 1.0,
	1.0, 0.0, 1.0,
	0.0, 1.0, 1.0,
	1.0, 1.0, 1.0
};

// 绘制顺序
static const GLint order[][4] = {
	0, 2, 3, 1,
	0, 4, 6, 2,
	0, 1, 5, 4,
	4, 5, 7, 6,
	1, 3, 7, 5,
	2, 6, 7, 3
};

void display()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	glLoadIdentity();
	gluLookAt(3, 2, 2, 0.0, 0.0, 0.0, -1, -1, 1);

	// 旋转矩阵变换
	glTranslatef(axis[0][0], axis[0][1], axis[0][2]);
	glRotatef(angle, axis[1][0] - axis[0][0], axis[1][1] - axis[0][1], axis[1][2] - axis[0][2]);
	glTranslatef(-axis[0][0], -axis[0][1], -axis[0][2]);

	glBegin(GL_QUADS);
	for (int i = 0; i < 6; ++i) {
		if (i == 2 || i == 5) continue;
		for (int j = 0; j < 4; ++j) {
			glColor3fv(cube_v[order[i][j]]);
			glVertex3fv(cube_v[order[i][j]]);
		}
	}
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(0.25, 0.5, 0.5);
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(0.75, 0.5, 0.5);
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(0.75, 1.0, 0.5);
	glVertex3f(0.25, 1.0, 0.5);
	glEnd();

	glutSwapBuffers();
}


void timer(GLint value) {
	angle += 2.0;
	if (angle >= 360.0) angle -= 360.0;
	glutPostRedisplay();
	glutTimerFunc(25, timer, value);
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

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("rotate");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutTimerFunc(100, timer, 1);
	glutMainLoop();
	return 0;
}