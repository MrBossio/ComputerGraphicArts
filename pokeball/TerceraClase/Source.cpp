#include <GL/glut.h>
#include <math.h>

void floor() {
	glColor3ub(252, 232, 143);
	glBegin(GL_POLYGON);

	glVertex2d(0, 2);
	glVertex2d(14, 2);
	glVertex2d(14, 0);
	glVertex2d(0, 0);

	glEnd();
}

void background() {
	glColor3ub(254, 252, 214);
	glBegin(GL_POLYGON);

	glVertex2d(0, 2);
	glVertex2d(14, 2);
	glVertex2d(14, 10);
	glVertex2d(0, 10);

	glEnd();
}

void wheel1() {
	float cx, cy;
	float radio = 2.0;
	glColor3ub(252, 236, 149);
	glBegin(GL_POLYGON);
	for (double i = 0; i < 3.14159 * 2; i += 0.001) {
		cx = radio * cos(i);
		cy = radio * sin(i);
		glVertex2d(cx, cy);
	}
	glEnd();
	glColor3ub(252, 215, 2);
	glBegin(GL_POLYGON);
	for (double i= -2.2; i < 1.1; i += 0.001) {
		cx = radio * cos(i);
		cy = radio * sin(i);
		glVertex2d(cx, cy);
	}
	glEnd();
}

void wheel2() {
	float cx, cy;
	float radio = 2.0;
	glColor3ub(96, 41, 81);
	glBegin(GL_POLYGON);
	for (double i = 0; i < 3.14159 * 2; i += 0.001) {
		cx = radio * cos(i);
		cy = radio * sin(i);
		glVertex2d(cx, cy);
	}
	glEnd();

	glColor3ub(254, 252, 214);
	radio = 1.5;
	glBegin(GL_POLYGON);
	for (double i = 0; i < 3.14159 * 2; i += 0.001) {
		cx = radio * cos(i);
		cy = radio * sin(i);
		glVertex2d(cx, cy);
	}
	glEnd();

	glColor3ub(3, 127, 135);
	radio = 1.5;
	glBegin(GL_POLYGON);
	for (double i = 0; i < 3.14159; i += 0.001) {
		cx = radio * cos(i);
		cy = radio * sin(i);
		glVertex2d(cx, cy);
	}
	glEnd();

}

void wheel3() {
	float cx, cy;
	float radio = 0.7;

	glColor3ub(96, 41, 81);	
	glBegin(GL_POLYGON);
	for (double i = 0; i < 3.14159*2; i += 0.001) {
		cx = radio * cos(i);
		cy = radio * sin(i);
		glVertex2d(cx, cy);
	}
	glEnd();

}

void cyclebody() {
	glColor4ub(158,251,232,150);
	glBegin(GL_TRIANGLES);
	glVertex2f(8,4);
	glVertex2f(9.6,6.7);
	glVertex2f(11.2,4);
	glEnd();

	glColor4ub(252, 138, 137, 150);
	glBegin(GL_TRIANGLES);
	glVertex2f(8, 4);
	glVertex2f(9.6, 6.7);
	glVertex2f(5.6, 6.7);
	glEnd();
}


void draw() {
	glLoadIdentity();
	gluOrtho2D(0,14,0,10);
	glClear(GL_COLOR_BUFFER_BIT);

	/*active opacity*/
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	//


	floor();
	background();

	glPushMatrix();	
	glTranslated(4.86, 4, 0);	
	wheel1();
	glPopMatrix();

	glPushMatrix();
	glTranslated(11.2, 4, 0);
	wheel2();
	glPopMatrix();

	glPushMatrix();
	glTranslated(8, 4, 0);
	wheel3();
	glPopMatrix();

	cyclebody();

	glFlush();

}

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE);
	glutInitWindowSize(1400*0.45, 1000*0.45);
	glutInitWindowPosition(50,50);
	glutCreateWindow("Week3-excercise1");
	glutDisplayFunc(draw);
	glutMainLoop();
	return 0;
}

