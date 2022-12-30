#include <opengl/freeglut.h>

GLfloat cube_v[][3] = {
	0.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
	1.0f, 1.0f, 0.0f,
	0.0f, 0.0f, 1.0f,
	1.0f, 0.0f, 1.0f,
	0.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f
};

GLint order[][4] = {
	0, 2, 3, 1,
	0, 4, 6, 2,
	0, 1, 5, 4,
	4, 5, 7, 6,
	1, 3, 7, 5,
	2, 6, 7, 3
};

void init() {
	float l_ambient[4] = { 0.1, 0.1, 0.1, 1.0 };
	float l_diffuse[4] = { 0.9, 0.8, 0.9, 1.0 };
	float l_position[4] = { 1.0, 1.0, 1.0, 0.0 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, l_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, l_diffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, l_position);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	// 自动生成纹理坐标
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
}

void drawCube() {
	glDisable(GL_LIGHTING);
	
	glBegin(GL_QUADS);
	for (int i = 0; i < 6; ++i) {
		glNormal3fv(cube_v[i]);
		for (int j = 0; j < 4; ++j) {
			glColor3fv(cube_v[order[i][j]]);
			//glColor3f(0.3, 0.3, 0.3);
			glVertex3fv(cube_v[order[i][j]]);
		}
	}
	glEnd();

	glEnable(GL_LIGHTING);
}

void drawCoord() {
	glDisable(GL_LIGHTING);

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

	glEnable(GL_LIGHTING);
}

void display() {
	glClearColor(0.9, 0.9, 0.8, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glShadeModel(GL_FLAT);

	glEnable(GL_TEXTURE_2D);

	glLoadIdentity();
	gluLookAt(5.0, 3.0, 4.0, 2.0, 0.0, 0.0, -1, 1, -1);

	glPushMatrix();
	glTranslatef(3, 0, 0);
	drawCube();
	glPopMatrix();
	drawCoord();

	glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 0, 0, 500, 500, 1);	// 将以上环境内容作为纹理

	// 清除场景，重画
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(5.0, 3.0, 4.0, 2.0, 0.0, 0.0, -1, 1, -1);

	glPushMatrix();
	glTranslatef(3, 0, 0);
	drawCube();
	glPopMatrix();
	drawCoord();
	glutSolidSphere(1.0, 20, 20);

	glutSwapBuffers();
}

void reshape(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(70.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(2, 2, 2, 0.0, 0.0, 0.0, -1, -1, 1);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("environment mapping");
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	init();
	glutMainLoop();
	return 0;
}