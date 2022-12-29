#include <opengl/freeglut.h>
#include <math.h>

#define DEPTH 8
using namespace std;

GLfloat init_vertex[][3] = {
	 0.0f,		 0.0f,		 1.0f,
	 0.0f,		 0.942809f, -0.333333f,
	-0.816497f, -0.471405f, -0.333333f,
	 0.816497f, -0.471405f, -0.333333f
};

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

struct Material {
	GLfloat* ambient;
	GLfloat* diffuse;
	GLfloat* specular;
};

void normalize3f(GLfloat* v)
{
	GLfloat d = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
	for (int i = 0; i < 3; ++i) v[i] /= d;
}

void divide_triangle(GLfloat* a, GLfloat* b, GLfloat* c, int depth)
{
	if (depth > 0) {
		GLfloat ab[3], ac[3], bc[3];
		for (int i = 0; i < 3; ++i) {
			ab[i] = a[i] + b[i];
			ac[i] = a[i] + c[i];
			bc[i] = b[i] + c[i];
		}	
		normalize3f(ab);
		normalize3f(ac);
		normalize3f(bc);

		divide_triangle(a, ab, ac, depth - 1);
		divide_triangle(b, bc, ab, depth - 1);
		divide_triangle(c, ac, bc, depth - 1);
		divide_triangle(ab, bc, ac, depth - 1);
	}
	else {
		glBegin(GL_TRIANGLES);
		glColor3f(sqrt(a[0] * a[0]), sqrt(a[1] * a[1]), sqrt(a[2] * a[2]));
		glVertex3fv(a);
		glVertex3fv(b);
		glVertex3fv(c);
		glEnd();
	}
}

void drawSphere() {
	divide_triangle(init_vertex[0], init_vertex[2], init_vertex[1], DEPTH);
	divide_triangle(init_vertex[0], init_vertex[3], init_vertex[2], DEPTH);
	divide_triangle(init_vertex[0], init_vertex[1], init_vertex[3], DEPTH);
	divide_triangle(init_vertex[1], init_vertex[2], init_vertex[3], DEPTH);
}

void drawBottom() {
	glBegin(GL_QUADS);
	glVertex3f(8.0, -2.0, 8.0);
	glVertex3f(8.0, -2.0, -8.0);
	glVertex3f(-8.0, -2.0, -8.0f);
	glVertex3f(-8.0, -2.0, 8.0f);
	glEnd();
}

void drawAxisLine() {
	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 0.0);
	glVertex3f(-6.0, 0.0, 0.0);
	glVertex3f(6.0, 0.0, 0.0);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, -6.0);
	glVertex3f(0.0, 0.0, 6.0);
	glEnd();
}

void drawCube() {
	//glTranslatef(3.0, 0.0, 0.0);
	//glTranslatef(-0.5, -0.5, -0.5);

	glBegin(GL_QUADS);
	for (int i = 0; i < 6; ++i) {
		glNormal3fv(cube_v[i]);
		for (int j = 0; j < 4; ++j) {
			//glColor3fv(cube_v[order[i][j]]);
			glColor3f(0.3, 0.3, 0.3);
			glVertex3fv(cube_v[order[i][j]]);
		}
	}
	glEnd();

	//glTranslatef(0.5, 0.5, 0.5);
	//glTranslatef(-3.0, 0.0, 0.0);
}

void drawCubeShadow(GLfloat x, GLfloat y, GLfloat z) {
	GLfloat m[16] = { 0.0 };
	m[0] = m[5] = m[10] = 1.0;
	m[7] = -1.0 / y;
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslatef(x, y, z);
	glMultMatrixf(m);
	glTranslatef(-x, -y, -z);
	drawCube();
	glPopMatrix();
}

void SetLightAndMaterial() {
	GLfloat l_ambient_0[4] = { 0.5, 0.5, 0.5, 0.0 };
	GLfloat l_diffuse_0[4] = { 0.5, 0.5, 0.5, 0.2 };
	GLfloat l_specular_0[4] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat l_pos_0[4] = { 0.0, 6.5, -1.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, l_ambient_0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, l_diffuse_0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, l_specular_0);
	glLightfv(GL_LIGHT0, GL_POSITION, l_pos_0);

	GLfloat l_ambient_1[4] = { 1.0, 1.0, 1.0, 0.0 };
	GLfloat l_diffuse_1[4] = { 1.0, 1.0, 1.0, 0.5 };
	GLfloat l_specular_1[4] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat l_pos_1[4] = { 3.5, 2.5, -1.0, 1 };
	glLightfv(GL_LIGHT1, GL_AMBIENT, l_ambient_1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, l_diffuse_1);
	glLightfv(GL_LIGHT1, GL_SPECULAR, l_specular_1);
	glLightfv(GL_LIGHT1, GL_POSITION, l_pos_1);

	GLfloat m_ambient_brightgold[4] = { 0.247250, 0.224500, 0.064500, 1.0 };
	GLfloat m_diffuse_brightgold[4] = { 0.346150, 0.314300, 0.090300, 1.0 };
	GLfloat m_specular_brightgold[4] = { 0.797357, 0.723991, 0.208006, 1.0 };
	GLfloat m_shininess_brightgold = 83.199997;
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, m_ambient_brightgold);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, m_diffuse_brightgold);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, m_specular_brightgold);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, m_shininess_brightgold);

	// 颜色追踪
	//glEnable(GL_COLOR_MATERIAL);
	//glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);


	glEnable(GL_LIGHTING);     //开启光照系统
	glEnable(GL_LIGHT0);       //开启GL_LIGHT0光源
	glEnable(GL_LIGHT1);       //开启GL_LIGHT1光源
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glLoadIdentity();
	gluLookAt(5.0, 3.0, 4.0, 2.0, 0.0, 0.0, -1, 1, -1);

	SetLightAndMaterial();

	drawBottom();
	drawSphere();
	drawAxisLine();
	
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	
	glTranslatef(3.0, 0.0, 0.0);	// 为了使其与圆同轴，移动绘图坐标
	glTranslatef(-0.5, -0.5, -0.5);
	drawCube();
	drawCubeShadow(0.0, 10.0, 0.0);
	glTranslatef(0.5, 0.5, 0.5);	// 移回绘图坐标
	glTranslatef(-3.0, 0.0, 0.0);

	glDisable(GL_COLOR_MATERIAL);

	glTranslatef(5.0, 0.0, 0.0);
	glutSolidSphere(0.5, 200.0, 20.0);	// 用glut画的球
	glTranslatef(-5.0, 0.0, 0.0);
	
	glutSwapBuffers();
}

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
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("sphere and light");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMainLoop();
	return 0;
}
