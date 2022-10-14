#include <GL/glut.h>
#include <math.h>
#include <cmath>
#include <time.h>
#include <iostream>
using namespace std;

int cameradistance = 1800;
int sceneryScale = 15;

//camera position
float angle = 0.5;
float cameraX = sqrt(cameradistance) * sin(angle);
float cameraY = 10;
float cameraZ = sqrt(cameradistance) * cos(angle);

//center of interest position
float pointX = 0;
float pointY = 10;
float pointZ = 0;
//vector up
float vectorX = 0;
float vectorY = 1;
float vectorZ = 0;


void initWindow(int w, int h) {
	glViewport(0, 0, w, h);
	//start proyection
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//perspective
	//fov, aspect ratio, zNear, zFar (clipping?)
	gluPerspective(40, (float)w / (float)h, 1, 200);
}

void initLight() {

	//parameters a light
	GLfloat ambient[] = { 0.35,0.35,0.35, 1.0 };
	GLfloat diffuse[] = { 0.25,0.25,0.25, 1.0 };
	GLfloat specular[] = { 0.1,0.1,0.1, 1.0 };
	GLfloat direccion[] = { -25.0, 50.0, 0.0 };
	float lightPosition[] = { 0,70,60,1 };

	//enable lights
	glEnable(GL_LIGHTING);

	//ambient light
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);

	//light, wich param, values
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	//glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, direccion);
	//glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 4);

	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);

	//configuring material
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

}


void scenery() {
		
	glBegin(GL_POLYGON);
	glColor3ub(178, 157, 49);
	glVertex3d(-sceneryScale, 0, -sceneryScale);
	glVertex3d(sceneryScale, 0, -sceneryScale);
	glVertex3d(sceneryScale, 0, sceneryScale);
	glVertex3d(-sceneryScale, 0, sceneryScale);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3ub(252, 225, 0);
	glVertex3d(-sceneryScale, 0, -sceneryScale);
	glVertex3d(sceneryScale, 0, -sceneryScale);
	glColor3ub(200, 115, 117);
	glVertex3d(sceneryScale, sceneryScale*2, -sceneryScale);
	glVertex3d(-sceneryScale, sceneryScale*2, -sceneryScale);
	glEnd();

	glPushMatrix();
	glTranslated(0, 0, 0);
	glRotated(90, 0, 1, 0);
	glBegin(GL_POLYGON);
	glColor3ub(252, 225, 0);
	glVertex3d(-sceneryScale, 0, -sceneryScale);
	glVertex3d(sceneryScale, 0, -sceneryScale);
	glColor3ub(200, 115, 117);
	glVertex3d(sceneryScale, sceneryScale*2, -sceneryScale);
	glVertex3d(-sceneryScale, sceneryScale*2, -sceneryScale);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, 0, 0);
	glRotated(-90, 0, 1, 0);
	glBegin(GL_POLYGON);
	glColor3ub(252, 225, 0);
	glVertex3d(-sceneryScale, 0, -sceneryScale);
	glVertex3d(sceneryScale, 0, -sceneryScale);
	glColor3ub(200, 115, 117);
	glVertex3d(sceneryScale, sceneryScale*2, -sceneryScale);
	glVertex3d(-sceneryScale, sceneryScale*2, -sceneryScale);
	glEnd();
	glPopMatrix();

	//*******************
	// front wall
	//*******************

	//glBegin(GL_POLYGON);
	//glColor3ub(252, 225, 0);
	//glVertex3d(-sceneryScale, 0, sceneryScale);
	//glVertex3d(sceneryScale, 0, sceneryScale);
	//glColor3ub(200, 115, 117);
	//glVertex3d(sceneryScale, sceneryScale * 2, sceneryScale);
	//glVertex3d(-sceneryScale, sceneryScale * 2, sceneryScale);
	//glEnd();

}

void drawAxis() {
	glBegin(GL_LINES);
	glColor3ub(255, 0, 0);
	glVertex3d(0, 0, 0);
	glVertex3d(10, 0, 0);
	glEnd();

	glBegin(GL_LINES);
	glColor3ub(0, 255, 0);
	glVertex3d(0, 0, 0);
	glVertex3d(0, 10, 0);
	glEnd();

	glBegin(GL_LINES);
	glColor3ub(0, 0, 255);
	glVertex3d(0, 0, 0);
	glVertex3d(0, 0, 10);
	glEnd();
}


void BodyCharOne() {

	//body
	glPushMatrix();
	glColor3ub(0, 0, 0);
	glTranslated(0,7,0);
	glRotated(0,0,0,0);
	glScaled(1,1.2,1);
	glutSolidSphere(2, 16, 16);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(192, 223, 234);
	glTranslated(0, 6.8, 0);
	glRotated(0, 0, 0, 0);
	glScaled(1, 1.2, 1);
	glutSolidSphere(2, 16, 16);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(0, 0, 0);
	glTranslated(0, 3, 0);
	glRotated(0, 0, 0, 0);
	glScaled(1, 1.2, 1);
	glutSolidSphere(2, 16, 16);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(254, 182, 42);
	glTranslated(0, 2.5, 0);
	glRotated(0, 0, 0, 0);
	glScaled(1.05, 0.5, 1.05);
	glutSolidSphere(2, 16, 16);
	glPopMatrix();

	//face

	glPushMatrix();
	glColor3ub(0, 0, 0);
	glTranslated(-0.8, 6.5, 1.75);
	glRotated(0, 0, 0, 0);
	glScaled(1, 1, 1);
	glutSolidCube(0.4);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(0, 0, 0);
	glTranslated(0.8, 6.5, 1.75);
	glRotated(0, 0, 0, 0);
	glScaled(1, 1, 1);
	glutSolidCube(0.4);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(230, 57, 85);
	glTranslated(0, 6, 1.75);
	glRotated(0, 0, 0, 0);
	glScaled(1, 1, 1);
	glutSolidCube(0.4);
	glPopMatrix();

}

void armsAndLegsCharOne(int x) {
	
	//arms
	glPushMatrix();
	glColor3ub(0, 0, 0);
	glTranslated(x*-2.5, 3, 0);
	glRotated(-90, 1, 0, 0);
	glRotated(x*45, 0, 1, 0);
	glScaled(x * 1, 1, 1);
	gluCylinder(gluNewQuadric(), 0.5, 0.5, 2, 16, 4);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(192, 223, 234);
	glTranslated(x*-2.5, 3, 0);
	glScaled(x * 1, 1, 1);
	glRotated(0, 0, 0, 0);	
	glutSolidSphere(0.6, 12, 12);
	glPopMatrix();

	//legs
	glPushMatrix();
	glColor3ub(0, 0, 0);
	glTranslated(x * -1.8, 0, 0);
	glRotated(-90, 1, 0, 0);
	glRotated(x * 15, 0, 1, 0);
	glScaled(x * 1, 1, 1);
	gluCylinder(gluNewQuadric(), 0.6, 0.5, 2, 16, 4);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(177, 100, 181);
	glTranslated(x * -1.8, 0, 0);
	glScaled(x * 1.3, 1, 1.5);
	glRotated(0, 0, 0, 0);
	glutSolidSphere(0.7, 12, 12);
	glPopMatrix();

}

void characterOne() {
	BodyCharOne();
	armsAndLegsCharOne(1);
	armsAndLegsCharOne(-1);
}


void BodyCharTwo() {

	//body
	glPushMatrix();
	glColor3ub(0, 0, 0);
	glTranslated(0, 7, 0);
	glRotated(0, 0, 0, 0);
	glScaled(1, 1.2, 1);
	glutSolidSphere(2, 12, 12);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(255, 255, 255);
	glTranslated(0, 6.8, 0);
	glRotated(0, 0, 0, 0);
	glScaled(1, 1.2, 1);
	glutSolidSphere(2, 12, 12);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(51, 217, 0);
	glTranslated(0, 3, 0);
	glRotated(0, 0, 0, 0);
	glScaled(1, 1.2, 1);
	glutSolidSphere(2, 12, 12);
	glPopMatrix();

	//face

	glPushMatrix();
	glColor3ub(0, 0, 0);
	glTranslated(-0.8, 6.5, 1.75);
	glRotated(0, 0, 0, 0);
	glScaled(1, 1, 1);
	glutSolidCube(0.4);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(0, 0, 0);
	glTranslated(0.8, 6.5, 1.75);
	glRotated(0, 0, 0, 0);
	glScaled(1, 1, 1);
	glutSolidCube(0.4);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(230, 57, 85);
	glTranslated(0, 6, 1.75);
	glRotated(0, 0, 0, 0);
	glScaled(1, 1, 1);
	glutSolidCube(0.4);
	glPopMatrix();

}

void armsAndLegsCharTwo(int x) {

	//arms
	glPushMatrix();
	glColor3ub(254,239,8);
	glTranslated(x * -2.5, 3, 0);
	glRotated(-90, 1, 0, 0);
	glRotated(x * 45, 0, 1, 0);
	glScaled(x * 1, 1, 1);
	gluCylinder(gluNewQuadric(), 0.5, 0.5, 2, 16, 4);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(255, 255, 255);
	glTranslated(x * -2.5, 3, 0);
	glScaled(x * 1, 1, 1);
	glRotated(0, 0, 0, 0);
	glutSolidSphere(0.6, 12, 12);
	glPopMatrix();

	//legs
	glPushMatrix();
	glColor3ub(0, 0, 0);
	glTranslated(x * -1.8, 0, 0);
	glRotated(-90, 1, 0, 0);
	glRotated(x * 15, 0, 1, 0);
	glScaled(x * 1, 1, 1);
	gluCylinder(gluNewQuadric(), 0.6, 0.5, 2, 16, 4);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(0,0,0);
	glTranslated(x * -1.8, 0, 0);
	glScaled(x * 1.3, 1, 1.5);
	glRotated(0, 0, 0, 0);
	glutSolidSphere(0.7, 12, 12);
	glPopMatrix();

}

void characterTwo() {
	BodyCharTwo();
	armsAndLegsCharTwo(1);
	armsAndLegsCharTwo(-1);
}


void world() {
	glPushMatrix();
	glColor3ub(220, 233, 18);
	glTranslated(0, 10, 0);
	glRotated(0, 0, 0, 0);
	glScaled(1, 1, 1);
	glutSolidSphere(8, 32, 32);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(255, 255, 255);
	glTranslated(0, 10, 0);
	glRotated(30, 0, 0, 1);
	glRotated(30, 0, 1, 0);
	glScaled(0.8, 1.05, 1.05);
	glutSolidSphere(8, 32, 32);
	glPopMatrix();
}


void draw() {
	initLight();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(cameraX, cameraY, cameraZ, pointX, pointY, pointZ, vectorX, vectorY, vectorX);

	glClearColor(164 / 255.0, 131 / 255.0, 28 / 255.0, 1);

	//floor
	glPushMatrix();
	glTranslated(0, 0, 0);
	scenery();
	glPopMatrix();

	//axis
	glPushMatrix();
	glTranslated(0, 0.01, 0);
	drawAxis();
	glPopMatrix();

	world();
	
	glPushMatrix();
	glTranslated(3, 16.5, 3.5);
	glRotated(-30, 0, 0, 1);
	glRotated(15, 1, 0, 0);
	glScaled(0.75, 0.75, 0.75);
	characterOne();
	glPopMatrix();

	glPushMatrix();
	glTranslated(-3, 17.2, 3);
	glRotated(30, 0, 0, 1);
	glRotated(15, 1, 0, 0);
	glScaled(0.32, 0.32, 0.32);
	characterTwo();
	glPopMatrix();

	glutSwapBuffers();
}

void timer(int t) {
	glutPostRedisplay();
	glutTimerFunc(20, timer, 0);
}

void keyboardIn(int key, int x, int y) {
	cout << key << "\n";

	switch (key) {
	case 101:
		cameraY += 0.29;
		break;
	case 103:
		cameraY -= 0.29;
		break;
	case 100:
		angle -= 0.1;
		cameraX = sqrt(cameradistance) * sin(angle);
		cameraZ = sqrt(cameradistance) * cos(angle);
		cout << cameraX << "-" << cameraY << "-" << cameraZ << '\n';
		break;
	case 102:
		angle += 0.1;
		cameraX = sqrt(cameradistance) * sin(angle);
		cameraZ = sqrt(cameradistance) * cos(angle);
		cout << cameraX << "-" << cameraY << "-" << cameraZ << '\n';
		break;
	}

}

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(1050, 750);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("miniworld");
	glutReshapeFunc(initWindow);
	glutDisplayFunc(draw);

	//control
	glutSpecialFunc(keyboardIn);
	glutTimerFunc(0, timer, 0);

	glutMainLoop();
	return 0;
}