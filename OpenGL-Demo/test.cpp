#include <opengl/freeglut.h>

void diplay() {
	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_QUADS);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex2f(-0.8f, 0.1f);
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex2f(-0.2f, 0.1f);
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex2f(-0.2f, 0.7f);
		glVertex2f(-0.8f, 0.7f);
	glEnd();

	glBegin(GL_TRIANGLES);
		glColor3f(0.2f, 1.0f, 0.1f);
		glVertex2f(0.1f, -0.6f);
		glColor3f(0.2f, 0.8f, 0.1f);
		glVertex2f(0.7f, -0.6f);
		glColor3f(0.2f, 0.5f, 0.1f);
		glVertex2f(0.4f, -0.1f);
	glEnd();

	glBegin(GL_POLYGON);
		glColor3f(0.2f, 1.0f, 0.1f);
		glVertex2f(0.1f, -0.6f);
		glColor3f(0.2f, 0.8f, 0.1f);
		glVertex2f(0.7f, -0.6f);
		glColor3f(0.2f, 0.5f, 0.1f);
		glVertex2f(0.4f, -0.1f);
		glColor3f(0.2f, 0.5f, 0.7f);
		glVertex3f(0.4f, 0.5f, 0.1f);
	glEnd();

	glFlush();
}

void initGL() {
	glClearColor(1.0f, 1.0f, 1.0f, 0.5f);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	int mode = GLUT_RGB | GLUT_SINGLE;
	glutInitDisplayMode(mode);
	glutCreateWindow("Vertex, Primitive & Color");
	glutInitWindowSize(320, 320);
	glutInitWindowPosition(50, 50);
	glutDisplayFunc(diplay);
	initGL();
	glutMainLoop();
	return 0;
}