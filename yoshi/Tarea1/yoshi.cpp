/*Libreria principal de OpenGl*/
#include <GL/glut.h>
#include <math.h>

void draw() {
	//cargar coordenadas de dibujo
	glLoadIdentity();
	gluOrtho2D(0, 20, 0, 20); //local axis, comienza bottom left
	glClear(GL_COLOR_BUFFER_BIT); //limpiar

	//coin
	float radio = 9.5;
	float cx, cy;
	glColor3ub(191, 128, 52);
	glBegin(GL_POLYGON);
	for (double i = 0; i < 3.14159 * 2; i += 0.1) {
		cx = radio * cos(i);
		cy = radio * sin(i);
		glVertex2d(10 + cx, 10 + cy);
	}
	glEnd();

	glColor3ub(242, 200, 75);
	glBegin(GL_POLYGON);
	for (double i = 0; i < 3.14159 * 2; i += 0.1) {
		cx = radio * cos(i);
		cy = radio * sin(i);
		glVertex2d(9.5 + cx, 9.5 + cy);
	}
	glEnd();

	//black
	glPointSize(10);
	glBegin(GL_POINTS);
	glColor3ub(0, 0, 0);
	int i, j;
	for (i = 2; i <= 17; i++) {
		for (j = 5; j <= 10; j++) {
			glVertex2d(i, j);
		}
	}
	for (i = 5; i <= 14; i++) {
		for (j = 6; j <= 15; j++) {
			glVertex2d(i, j);
		}
	}

	glVertex2d(6, 16);
	glVertex2d(7, 17);
	glVertex2d(8, 17);
	glVertex2d(9, 16);
	glVertex2d(13, 16);
	glVertex2d(12, 17);
	glVertex2d(11, 17);
	glVertex2d(10, 16);
	glVertex2d(3, 11);
	glVertex2d(4, 12);
	glVertex2d(15, 12);
	glVertex2d(16, 11);

	for (i = 3; i <= 16; i++)
		glVertex2d(i, 4);
	for (i = 4; i <= 15; i++)
		glVertex2d(i, 3);

	for (i = 6; i <= 13; i++)
		glVertex2d(i, 2);

	//light green
	glColor3ub(89, 198, 75);
	glVertex2d(3, 10);
	glVertex2d(4, 10);
	glVertex2d(4, 11);
	glVertex2d(5, 7);
	glVertex2d(5, 8);
	glVertex2d(5, 9);
	glVertex2d(5, 11);
	glVertex2d(6, 6);
	glVertex2d(6, 7);
	glVertex2d(6, 8);
	glVertex2d(6, 9);
	glVertex2d(6, 10);
	glVertex2d(6, 15);
	glVertex2d(7, 5);
	glVertex2d(7, 6);
	glVertex2d(7, 7);
	glVertex2d(7, 8);
	glVertex2d(7, 9);
	glVertex2d(7, 10);
	glVertex2d(7, 11);
	glVertex2d(7, 16);
	glVertex2d(8, 5);
	glVertex2d(8, 6);
	glVertex2d(8, 7);
	glVertex2d(8, 8);
	glVertex2d(8, 10);
	glVertex2d(8, 11);
	glVertex2d(8, 16);
	glVertex2d(9, 5);
	glVertex2d(9, 6);
	glVertex2d(9, 7);
	glVertex2d(9, 8);
	glVertex2d(9, 9);
	glVertex2d(9, 10);
	glVertex2d(9, 11);
	glVertex2d(9, 15);
	glVertex2d(16, 10);
	glVertex2d(15, 10);
	glVertex2d(15, 11);
	glVertex2d(14, 7);
	glVertex2d(14, 8);
	glVertex2d(14, 9);
	glVertex2d(14, 11);
	glVertex2d(13, 6);
	glVertex2d(13, 7);
	glVertex2d(13, 8);
	glVertex2d(13, 9);
	glVertex2d(13, 10);
	glVertex2d(13, 15);
	glVertex2d(12, 5);
	glVertex2d(12, 6);
	glVertex2d(12, 7);
	glVertex2d(12, 8);
	glVertex2d(12, 9);
	glVertex2d(12, 10);
	glVertex2d(12, 11);
	glVertex2d(12, 16);
	glVertex2d(11, 5);
	glVertex2d(11, 6);
	glVertex2d(11, 7);
	glVertex2d(11, 8);
	glVertex2d(11, 10);
	glVertex2d(11, 11);
	glVertex2d(11, 16);
	glVertex2d(10, 5);
	glVertex2d(10, 6);
	glVertex2d(10, 7);
	glVertex2d(10, 8);
	glVertex2d(10, 9);
	glVertex2d(10, 10);
	glVertex2d(10, 11);
	glVertex2d(10, 15);

	//dark green
	glColor3ub(66, 147, 56);
	glVertex2d(5, 5);
	glVertex2d(5, 6);
	glVertex2d(6, 4);
	glVertex2d(6, 5);
	glVertex2d(7, 3);
	glVertex2d(7, 4);
	glVertex2d(8, 3);
	glVertex2d(8, 4);
	glVertex2d(9, 3);
	glVertex2d(9, 4);
	glVertex2d(10, 3);
	glVertex2d(10, 4);
	glVertex2d(11, 3);
	glVertex2d(11, 4);
	glVertex2d(12, 3);
	glVertex2d(12, 4);
	glVertex2d(12, 5);
	glVertex2d(12, 11);
	glVertex2d(13, 4);
	glVertex2d(13, 5);
	glVertex2d(13, 6);
	glVertex2d(13, 10);
	glVertex2d(14, 5);
	glVertex2d(14, 6);
	glVertex2d(14, 7);
	glVertex2d(14, 8);
	glVertex2d(14, 9);

	//white
	glColor3ub(255, 255, 255);
	glVertex2d(3, 6);
	glVertex2d(3, 7);
	glVertex2d(3, 8);
	glVertex2d(3, 9);
	glVertex2d(4, 4);
	glVertex2d(6, 12);
	glVertex2d(6, 13);
	glVertex2d(6, 14);
	glVertex2d(7, 13);
	glVertex2d(7, 14);
	glVertex2d(7, 15);
	glVertex2d(8, 15);
	glVertex2d(9, 13);
	glVertex2d(9, 14);
	glVertex2d(16, 6);
	glVertex2d(16, 7);
	glVertex2d(16, 8);
	glVertex2d(16, 9);
	glVertex2d(15, 4);
	glVertex2d(13, 12);
	glVertex2d(13, 13);
	glVertex2d(13, 14);
	glVertex2d(12, 13);
	glVertex2d(12, 14);
	glVertex2d(12, 15);
	glVertex2d(11, 15);
	glVertex2d(10, 13);
	glVertex2d(10, 14);
	glEnd();

	//coin bright
	glBegin(GL_POLYGON);
	glColor3ub(255, 255, 255);

	glVertex2d(16.5, 17.5);
	glVertex2d(17, 19);
	glVertex2d(17.5, 17.5);
	glVertex2d(19, 17);
	glVertex2d(17.5, 16.5);
	glVertex2d(17, 15);
	glVertex2d(16.5, 16.5);
	glVertex2d(15, 17);
	glEnd();

	glFlush();
}

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE);
	glutInitWindowSize(200, 200);
	glutInitWindowPosition(500, 500);
	glutCreateWindow("Yoshi");
	glutDisplayFunc(draw);
	glutMainLoop();
	return 0;
}