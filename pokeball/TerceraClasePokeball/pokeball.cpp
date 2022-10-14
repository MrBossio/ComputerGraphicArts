#include <GL/glut.h>
#include <math.h>

void background() {
	glBegin(GL_POLYGON);
		glColor3ub(50, 50, 50);
		glVertex2d(0, 3);
		glVertex2d(8, 3);
		glColor3ub(250, 250, 250);
		glVertex2d(8, 6);
		glVertex2d(0, 6);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3ub(50, 50, 50);	
	glVertex2d(8, 3);
	glVertex2d(0, 3);
	glColor3ub(250, 250, 250);
	glVertex2d(0, 0);
	glVertex2d(8, 0);
	glEnd();
}

void pokeball_red() {
	
	float cx, cy, radio = 2.1;
	float firstColor1 = 224;
	float firstColor2 = 4;
	float firstColor3 = 4;
	float finalColor1 = 140;
	float finalColor2 = 15;
	float finalColor3 = 15;

	glBegin(GL_POLYGON);
	for (double r = 0; r <= radio; r += 0.001) {
		glColor3ub(
			(firstColor1 - ((firstColor1 - finalColor1)/radio*r)),
			(firstColor2 - ((firstColor2 - finalColor2) / radio * r)),
			(firstColor3 - ((firstColor3 - finalColor3) / radio * r))
		);
		for (double i = 0; i < 3.14159; i += 0.001) {
			cx = r * cos(i);
			cy = r * sin(i);
			glVertex2d(cx, cy);
		}
	}	
	glEnd();
}

void pokeball_white() {
	float cx, cy, radio = 2.1;
	float firstColor1 = 255;
	float firstColor2 = 255;
	float firstColor3 = 255;
	float finalColor1 = 150;
	float finalColor2 = 150;
	float finalColor3 = 150;

	glBegin(GL_POLYGON);
	for (double r = 0; r <= radio; r += 0.001) {
		glColor3ub(
			(firstColor1 - ((firstColor1 - finalColor1) / radio * r)),
			(firstColor2 - ((firstColor2 - finalColor2) / radio * r)),
			(firstColor3 - ((firstColor3 - finalColor3) / radio * r))
		);
		for (double i = 3.14159; i < 3.14159*2; i += 0.001) {
			cx = r * cos(i);
			cy = r * sin(i);
			glVertex2d(cx, cy);
		}
	}
	glEnd();
}

void shadow() {
	float cx, cy, radio = 2.1;

	float firstColor1 = 0;
	float firstColor2 = 0;
	float firstColor3 = 0;
	float finalColor1 = 150;
	float finalColor2 = 150;
	float finalColor3 = 150;

	glBegin(GL_POLYGON);
	for (double r = 0; r <= radio; r += 0.001) {
		glColor3ub(
			(firstColor1 - ((firstColor1 - finalColor1) / radio * r)),
			(firstColor2 - ((firstColor2 - finalColor2) / radio * r)),
			(firstColor3 - ((firstColor3 - finalColor3) / radio * r))
		);
		for (double i = 0; i < 3.14159 * 2; i += 0.001) {
			cx = r * cos(i);
			cy = r * sin(i);
			glVertex2d(cx, cy);
		}
	}
	glEnd();
}

void pokeball_black1() {
	glColor3ub(0, 0, 0);
	float cx, cy, radio = 2;
	glBegin(GL_POLYGON);
	for (double i = 0; i < 3.14159 * 2; i += 0.01) {
		cx = radio * cos(i);
		cy = radio * sin(i);
		glVertex2d(cx, cy);
	}
	glVertex2d(0, 0);
	glEnd();
}

void pokeball_button() {
	glColor3ub(0, 0, 0);
	float cx, cy, radio = 0.7;
	glBegin(GL_POLYGON);
	for (double i = 0; i < 3.14159 * 2; i += 0.01) {
		cx = radio * cos(i);
		cy = radio * sin(i);
		glVertex2d(cx, cy);
	}	
	glEnd();

	glColor3ub(255, 255, 255);
	radio = 0.55;
	glBegin(GL_POLYGON);
	for (double i = 0; i < 3.14159 * 2; i += 0.01) {
		cx = radio * cos(i);
		cy = radio * sin(i);
		glVertex2d(cx, cy);
	}	
	glEnd();

	glColor3ub(0, 0, 0);
	radio = 0.4;
	glLineWidth(3);
	glBegin(GL_LINE_LOOP);
	for (double i = 0; i < 3.14159 * 2; i += 0.001) {
		cx = radio * cos(i);
		cy = radio * sin(i);
		glVertex2d(cx, cy);
	}	
	glEnd();

}

void draw() {
	glLoadIdentity();
	gluOrtho2D(0, 8, 0, 6);
	glClear(GL_COLOR_BUFFER_BIT);

	/*active opacity*/
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	//

	background();

	glPushMatrix();
	glTranslated(4, 1, 0);
	glScaled(0.9, 0.5, 0);
	glRotated(45, 0, 0, 0);
	shadow();
	glPopMatrix();

	glPushMatrix();
	glTranslated(4, 3, 0);
	pokeball_black1();
	glPopMatrix();

	glPushMatrix();
	glTranslated(4, 3.1, 0);
	pokeball_red();
	glPopMatrix();

	glPushMatrix();
	glTranslated(4, 2.9, 0);
	pokeball_white();
	glPopMatrix();

	glPushMatrix();
	glTranslated(4, 3, 0);
	pokeball_button();
	glPopMatrix();

	glFlush();
}

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("Pokeball");
	glutDisplayFunc(draw);
	glutMainLoop();
	return 0;
}
