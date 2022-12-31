#include <opengl/freeglut.h>

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

GLint order[][4] = {
	0, 2, 3, 1,
	0, 4, 6, 2,
	0, 1, 5, 4,
	4, 5, 7, 6,
	1, 3, 7, 5,
	2, 6, 7, 3
};

void drawCube() {
	glBegin(GL_QUADS);
	for (int i = 0; i < 6; ++i) {
		for (int j = 0; j < 4; ++j) {
			if (i == 4) {
				glColor4f(0.3, 0.3, 0.3, 0.3);
			} else {
				glColor3fv(cube_v[order[i][j]]);
			}
			glVertex3fv(cube_v[order[i][j]]);
		}
	}
	glEnd();
}

void SetLightAndMaterial() {
	GLfloat l_pos_0[4] = { 0.0, 0.0, 3.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, l_pos_0);

	GLfloat m_specular[4] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat m_shininess = 100.0;
	glMaterialfv(GL_FRONT, GL_SPECULAR, m_specular);
	glMaterialf(GL_FRONT, GL_SHININESS, m_shininess);

	glEnable(GL_LIGHTING);     //开启光照系统
	glEnable(GL_LIGHT0);       //开启GL_LIGHT0光源
}

void display() {
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); //指定混合函数
	glEnable(GL_BLEND);	//开启混合模式
	glShadeModel(GL_SMOOTH);

	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	glLoadIdentity();
	gluLookAt(5.0, 1.6, 2.0, 2.0, 0.0, 0.0, -1, 1, -1);

	SetLightAndMaterial();

	glTranslatef(-0.5, -0.5, -0.5);
	drawCube();
	glTranslatef(0.5, 0.5, 0.5);

	glTranslatef(1.5, 0.0, 0.25);
	glColor4f(0.0, 3.0, 0.0, 0.3);
	glutSolidSphere(0.5, 200.0, 20.0);
	glTranslatef(-1.5, 0.0, -0.25);

	glTranslatef(3.0, 0.0, 0.5);
	glColor4f(0.0, 0.0, 1.0, 0.3);
	glutSolidCube(1.0);
	glTranslatef(-3.0, 0.0, -0.5);

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
	glutCreateWindow("transparent");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMainLoop();
	return 0;
}
