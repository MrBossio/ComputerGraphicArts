#include <GL/glut.h>
#include <math.h>
#include <time.h>

void sea() {
	glBegin(GL_POLYGON);
	glColor3ub(248, 43, 11);
	glVertex2d(0, 5);
	glVertex2d(22, 5);
	glColor3ub(7, 170, 233);
	glVertex2d(22, 0);
	glVertex2d(0, 0);
	glEnd();
}
void sky() {
	glBegin(GL_POLYGON);
	glColor3ub(248, 43, 11);
	glVertex2d(0, 15);
	glVertex2d(22, 15);
	glColor3ub(248, 200, 153);
	glVertex2d(22, 5);
	glVertex2d(0, 5);
	glEnd();
}

void stars() {
	
	glColor3ub(255, 242, 0);
	glPointSize(3);
	glBegin(GL_POINTS);
	for (int i = 0; i < 10; i++) {
		int cx = rand() % (22 - 7 + 1) + 7;
		int cy = rand() % (15 - 6 + 1) + 6;
		glVertex2d(cx,cy);
	}
	glEnd();
}

void ship() {

	glColor3ub(0, 0,0);
	glBegin(GL_POLYGON);
	glVertex2d(10.6, 7);
	glVertex2d(10.8, 7);
	glVertex2d(10.8, 3.4);
	glVertex2d(10.6, 3.4);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex2d(15, 3.4);
	glVertex2d(14.6, 2.7);
	glVertex2d(9, 2.7);
	glVertex2d(8.6, 3.4);
	glEnd();

	glColor3ub(242, 156, 139);
	glBegin(GL_POLYGON);
	glVertex2d(10.6, 3.4);
	glVertex2d(10.6, 6);
	glVertex2d(9.8, 4);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex2d(10.8, 3.4);
	glVertex2d(10.8, 6);
	glVertex2d(12.4, 4);
	glEnd();

	glLineWidth(2);
	glColor3ub(242, 202, 139);
	glBegin(GL_LINE_STRIP);
	glVertex2d(10.6, 6);
	glVertex2d(9.8, 4);
	glVertex2d(10.6, 3.4);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glVertex2d(10.8, 3.4);
	glVertex2d(12.4, 4);
	glVertex2d(10.8, 6);
	glEnd();
}

void seagull(int x, int y) {

	glColor3ub(0, 0, 0);
	glLineWidth(5);
	glBegin(GL_LINE_STRIP);
	glVertex2d(0+x, 0+y);
	glVertex2d(0+x, 0.2+y);
	glVertex2d(0.2+x, 0.2+y);
	glVertex2d(0.2+x, 0.4+y);
	glVertex2d(0.4+x, 0.4+y);	
	glEnd();
}

void sun() {
	float radio = 3.93;
	float cx, cy;

	glColor3ub(250, 218, 186);
	glBegin(GL_POLYGON);
	for (double i = 0; i < 3.14159 * 2; i += 0.001) {
		cx = radio * cos(i);
		cy = radio * sin(i);
		glVertex2d(2.6 + cx, 13 + cy);
	}
	glEnd();

	glColor3ub(218, 94, 84);
	glBegin(GL_POLYGON);
	for (double i = 0; i < 3.14159 * 2; i += 0.001) {
		cx = radio * cos(i);
		cy = radio * sin(i);
		glVertex2d(2.4 + cx, 13.2 + cy);
	}
	glEnd();
}

void draw() {
	glLoadIdentity();
	gluOrtho2D(0, 22, 0, 15);
	glClear(GL_COLOR_BUFFER_BIT);
	sea();
	sky();
	sun();
	stars();
	//capas
	glPushMatrix();
	glTranslated(-7, 0, 0);
		ship();
	glPopMatrix();
	
	for (int i = 0; i < 5; i++) {
		int cx = rand() % (22 - 0 + 1) + 0;
		int cy = rand() % (15 - 5 + 1) + 5;
		seagull(cx, cy);
	}
	glFlush();
}

int main(int argc, char* argv[]) {
	srand(time(NULL));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE);
	glutInitWindowSize(1110, 779);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("Week2-excercise1");
	glutDisplayFunc(draw);
	glutMainLoop();
	return 0;
}