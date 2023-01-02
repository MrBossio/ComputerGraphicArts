#include <GL/glut.h>
#include <math.h>
#include <time.h>
#include <iostream>
#include "Texturas/RgbImage.h"

using namespace std;

float camaraX = -20;
float camaraY = 26;
float camaraZ = 40;

float radio = 64;
float angulo = 2.33;
float centroY = 10;

GLuint textures[5];
GLUquadric* quad;

float velocity = 1;
int ladoX = 1;
float posCuboX = 0;

float posCubeX = 0;
float directionX = 1;

float giro = 0;
float girocubo = 0;


// variables anim helicoptero
float girohelice = 0;
float velocidadhelice = 0.2;
float alturaHelicoptero = 0;
float giroHelicoptero = 0;
float vueloHelicoptero = 0;

// variables robor
float anguloPiernaL = 0;
float anguloPiernaR = 0;
float anguloBrazoL = 0;
float anguloBrazoR = 0;
float velocidadPersonaje = 3;
float giroBrazo = 1;
float giroPierna = 1;
float paso = 1;
float altura = 1;
float robotAngle = 0;
float robotAngleFactor = 1;
float robotX = 0;
float robotXfactor = 1;
float robotZ = 0;
float robotZfactor = 1;

void loadTexturesFromFile(const char* filename, int index) {
	RgbImage theTextMap(filename);
	glGenTextures(1, &textures[index]);
	glBindTexture(GL_TEXTURE_2D, textures[index]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, theTextMap.GetNumCols(),
		theTextMap.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE, theTextMap.ImageData());
}

void loadImages() {
	loadTexturesFromFile("Texturas/assets/floor1.bmp", 0);
	loadTexturesFromFile("Texturas/assets/trees022.bmp", 1);
	loadTexturesFromFile("Texturas/assets/wall10.bmp", 2);
	loadTexturesFromFile("Texturas/assets/sky004.bmp", 3);	
}

void iniciarVentana(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(80, (float)w / (float)h, 1, 200);
}
void inicializarLuces() {

	GLfloat luz_ambiente[] = { 0.2,0.2,0.2,1 };
	GLfloat luz_difusa[] = { 0.2,0.2,0.2,1 };
	GLfloat luz_especular[] = { 0.1,0.1,0.1,1 };

	float reflejo[] = { 0,0,0,1 };
	float posicionLuz[] = { 0,70,0,1 };
	int sombra = 256;

	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luz_ambiente);

	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glMaterialfv(GL_FRONT, GL_SPECULAR, reflejo);
	glMateriali(GL_FRONT, GL_SHININESS, sombra);
	glLightfv(GL_LIGHT0, GL_POSITION, posicionLuz);

	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, luz_ambiente);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, luz_difusa);
	glLightfv(GL_LIGHT0, GL_SPECULAR, luz_especular);

	//Luces Piso
	GLfloat light_ambient1[] = { 0.1,0.1,0.1,1 };
	GLfloat light_diffuse1[] = { 0.1,0.1,0.1,1 };
	GLfloat light_specular1[] = { 0.1,0.1,0.1,1 };

	float posicionLuz1[] = { -50,0,0,1 };
	float posicionLuz2[] = { 0,0,50,1 };
	float posicionLuz3[] = { 50,0,0,1 };
	float posicionLuz4[] = { 0,0,-50,1 };

	glEnable(GL_LIGHT1);
	glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse1);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular1);
	glLightfv(GL_LIGHT1, GL_POSITION, posicionLuz1);

	//glEnable(GL_LIGHT2);
	//glLightfv(GL_LIGHT2, GL_AMBIENT, light_ambient1);
	//glLightfv(GL_LIGHT2, GL_DIFFUSE, light_diffuse1);
	//glLightfv(GL_LIGHT2, GL_SPECULAR, light_specular1);
	//glLightfv(GL_LIGHT2, GL_POSITION, posicionLuz2);

	glEnable(GL_LIGHT3);
	glLightfv(GL_LIGHT3, GL_AMBIENT, light_ambient1);
	glLightfv(GL_LIGHT3, GL_DIFFUSE, light_diffuse1);
	glLightfv(GL_LIGHT3, GL_SPECULAR, light_specular1);
	glLightfv(GL_LIGHT3, GL_POSITION, posicionLuz3);

	//glEnable(GL_LIGHT4);
	//glLightfv(GL_LIGHT3, GL_AMBIENT, light_ambient1);
	//glLightfv(GL_LIGHT3, GL_DIFFUSE, light_diffuse1);
	//glLightfv(GL_LIGHT3, GL_SPECULAR, light_specular1);
	//glLightfv(GL_LIGHT3, GL_POSITION, posicionLuz4);

}

void piso() {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textures[0]);
	glColor3ub(255, 255, 255);

	glPushMatrix();
	glTranslated(0, -0.1, 0);
	glBegin(GL_POLYGON);	
	glTexCoord2f(0,5); glVertex3d(-50, 0, -50);
	glTexCoord2f(5,5); glVertex3d(50, 0, -50);
	glTexCoord2f(5,0); glVertex3d(50, 0, 50);
	glTexCoord2f(0,0); glVertex3d(-50, 0, 50);
	glEnd();
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);


}

void ejes() {
	glPushMatrix();
	glBegin(GL_LINES);
	glColor3ub(255, 0, 0);
	glVertex3d(0, 0, 0);
	glVertex3d(50, 0, 0);

	glColor3ub(0, 255, 0);
	glVertex3d(0, 0, 0);
	glVertex3d(0, 50, 0);

	glColor3ub(0, 0, 255);
	glVertex3d(0, 0, 0);
	glVertex3d(0, 0, 50);
	glEnd();
	glPopMatrix();
}


void earth() {

	giro += 0.02;

	glPushMatrix();
	//sobre eje
	//glTranslated(20, 0, 0);	
	glRotated(giro, 0, 1, 0);
	//sobre otro eje
	//glRotated(giro, 0, 1, 0);
	//glTranslated(20, 0, 0);
	

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textures[3]);
	glColor3ub(255, 255, 255);
	glPushMatrix();
	glTranslated(0, 40, 0);
	glScaled(1, 1, 1);
	glRotated(-90, 1, 0, 0);
	quad = gluNewQuadric();
	gluQuadricTexture(quad, 1);
	gluSphere(quad,130,50,50);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
}

void walls() {

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textures[2]);
	
	glPushMatrix();
	glColor3ub(255, 255, 255);
	glTranslated(-50, 0, 0);
	glRotated(90, 0, 1, 0);
	glBegin(GL_POLYGON);
		glTexCoord2f(0, 1); glVertex3d(-50, 15, 0);
		glTexCoord2f(10, 1); glVertex3d(50, 15, 0);
		glTexCoord2f(10, 0); glVertex3d(50, 0, 0);
		glTexCoord2f(0, 0); glVertex3d(-50, 0, 0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	
	glTranslated(50, 0, 0);
	glRotated(90, 0, 1, 0);
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3d(-50, 15, 0);
	glTexCoord2f(10, 1); glVertex3d(50, 15, 0);
	glTexCoord2f(10, 0); glVertex3d(50, 0, 0);
	glTexCoord2f(0, 0); glVertex3d(-50, 0, 0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	
	glTranslated(0, 0, 50);
	glRotated(180, 0, 1, 0);
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3d(-50, 15, 0);
	glTexCoord2f(10, 1); glVertex3d(50, 15, 0);
	glTexCoord2f(10, 0); glVertex3d(50, 0, 0);
	glTexCoord2f(0, 0); glVertex3d(-50, 0, 0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	
	glTranslated(0, 0, -50);
	glRotated(180, 0, 1, 0);
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3d(-50, 15, 0);
	glTexCoord2f(10, 1); glVertex3d(50, 15, 0);
	glTexCoord2f(10, 0); glVertex3d(50, 0, 0);
	glTexCoord2f(0, 0); glVertex3d(-50, 0, 0);
	glEnd();
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
}




//character
void body() {

	glPushMatrix();
	glColor3ub(255, 255, 255);
	glTranslated(0, 9.5, 0);
	glScaled(1, 0.8, 1);
	glutSolidSphere(0.7, 24, 24);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(255, 255, 255);
	glTranslated(0, 9.5, 1);
	glScaled(1, 1, 1);
	glutSolidSphere(0.25, 24, 24);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(0, 0, 255);
	glTranslated(0, 9.8, 0.7);
	glScaled(1.2, 0.5, 0.2);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(255, 255, 255);
	glTranslated(0, 8, 0);
	glScaled(1, 0.5, 1);
	glutSolidSphere(2, 24, 24);	
	glPopMatrix();

	glPushMatrix();
	glColor3ub(150, 150, 150);
	glTranslated(0, 6, 0);	
	glScaled(1, 1, 1);	
	glRotated(-90, 1, 0, 0);
	gluCylinder(gluNewQuadric(), 1, 2, 2, 16, 4);
	glPopMatrix();

	//cintura
	glPushMatrix();
	glColor3ub(255, 255, 0);
	glTranslated(0, 6,0);
	glScaled(2, 0.5, 2.2);
	glutSolidCube(1);
	glPopMatrix();
		
	glPushMatrix();
	glColor3ub(255, 255, 0);
	glTranslated(0, 5.5, 0);
	glScaled(0.5, 0.5, 2.2);
	glutSolidCube(1);
	glPopMatrix();

}

void legs(int i) {
	// legs
	glPushMatrix();
		glScaled(i * 1, 1, 1);

		glPushMatrix();
		glColor3ub(150, 150, 150);
		glTranslated(-0.6, 5.5, 0);		
		glutSolidSphere(0.4, 24, 24);
		glPopMatrix();

		glPushMatrix();
		glColor3ub(255, 255, 255);
		glTranslated(-0.6, 5.5, 0);
		glRotated(90, 1, 0, 0);				
		gluCylinder(gluNewQuadric(), 0.35, 0.35,2.5, 16, 4);
		glPopMatrix();

		glPushMatrix();
		glColor3ub(150, 150, 150);
		glTranslated(-0.6, 3, 0);
		glutSolidSphere(0.4, 24, 24);
		glPopMatrix();

		glPushMatrix();
		glColor3ub(0, 0, 255);
		glTranslated(-0.6, 3, 0);
		glRotated(90, 1, 0, 0);
		gluCylinder(gluNewQuadric(), 0.45, 0.45, 2.5, 16, 4);
		glPopMatrix();

		glPushMatrix();
		glColor3ub(255, 0, 0);
		glTranslated(-0.6, 0.5, 0);
		glScaled(1, 0.3, 1);
		glutSolidCube(0.8);
		glPopMatrix();

	glPopMatrix();


}

void arms(int i) {
	// arms
	glPushMatrix();
	glScaled(i * 1, 1, 1);

	glPushMatrix();
	glColor3ub(150, 150, 150);
	glTranslated(-2, 8, 0);
	glutSolidSphere(0.6, 24, 24);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(255, 255, 255);
	glTranslated(-2, 8, 0);
	glRotated(90, 1, 0, 0);
	gluCylinder(gluNewQuadric(), 0.35, 0.35, 2, 16, 4);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(150, 150, 150);
	glTranslated(-2, 6, 0);
	glutSolidSphere(0.5, 24, 24);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(255, 0, 0);
	glTranslated(-2, 5.7, 0);
	glRotated(90, 1, 0, 0);
	gluCylinder(gluNewQuadric(), 0.45, 0.45, 2, 16, 4);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(255, 0, 0);
	glTranslated(-2, 3.3, 0);
	glScaled(0.3, 1, 1);
	glutSolidCube(0.8);
	glPopMatrix();

	glPopMatrix();




}


void robot() {
	glPushMatrix();
	altura = 0.5*-abs(-1.0 / 45 * anguloBrazoL) ;

	glTranslated(0, altura, 0);
	glScaled(2, 2, 2);

	body();

	glPushMatrix();
	glTranslated(2.6, 8.5, 0);
	anguloBrazoL += (giroBrazo * velocidadPersonaje);
	if (anguloBrazoL > 60) giroBrazo = -1;
	if (anguloBrazoL < -60) giroBrazo = 1;
	glRotated(anguloBrazoL, 1, 0, 0);
	glTranslated(-2.6, -8.5, 0);
	arms(1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(2.6, 8.5, 0);
	anguloBrazoR += (-giroBrazo * velocidadPersonaje);
	glRotated(anguloBrazoR, 1, 0, 0);
	glTranslated(-2.6, -8.5, 0);
	arms(-1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, 5.5, 0);
	anguloPiernaR += (giroPierna*velocidadPersonaje);
	if (anguloPiernaR > 60) giroPierna = -1;
	if (anguloPiernaR < -60) giroPierna = 1;
	glRotated(anguloPiernaR*0.75, 1, 0, 0);
	glTranslated(0, -5.5, 0);
	legs(-1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, 5.5, 0);
	anguloPiernaL += (-giroPierna*velocidadPersonaje);
	glRotated(anguloPiernaL*0.75, 1, 0, 0);
	glTranslated(0, -5.5, 0);
	legs(1);
	glPopMatrix();

	glPopMatrix();
}

void robotControl() {

	//float robotAngle = 0;
	//float robotAngleFactor = 1;
	//float robotX = 0;
	//float robotXfactor = 1;
	//float robotY = 0;
	//float robotYfactor = 1;
	robotX += velocidadPersonaje * 0.25 * robotXfactor;
	robotZ += velocidadPersonaje * 0.25 * robotZfactor;


	//if (robotAngle == 0) {
	//	robotXfactor = 0;
	//	robotZfactor = 1;
	//}
	//if (robotAngle == 90 || robotAngle == -270) {
	//	robotXfactor = -1;
	//	robotZfactor = 0;
	//}
	//if (robotAngle == 180 || robotAngle == -180) {
	//	robotXfactor = 0;
	//	robotZfactor = -1;
	//}
	//if (robotAngle == -90 || robotAngle == 270) {
	//	robotXfactor = 1;
	//	robotZfactor = 0;
	//}


	if (robotAngle == 0) {
		robotXfactor = 0;
		if (robotZ > 50) {
			robotZfactor = -1;
			robotAngle = 180;
		}
		else robotZfactor = 1;
	}
	else if (robotAngle == 90 || robotAngle == -270) {		
		robotZfactor = 0;
		if (robotX > 50) {
			robotXfactor = -1;
			robotAngle = -90;
		}
		else robotXfactor = 1;
	}
	else if (robotAngle == 180 || robotAngle == -180) {
		robotXfactor = 0;
		if (robotZ < -50) {
			robotZfactor = 1;
			robotAngle = 0;
		}
		else robotZfactor = -1;
	}
	else if (robotAngle == 270 || robotAngle == -90) {
		robotZfactor = 0;
		if (robotX < -50) {
			robotXfactor = 1;
			robotAngle = 90;
		}
		else robotXfactor = -1;
	}

	//cout << robotX << " " << robotZ << endl;


	glPushMatrix();
	glTranslated(robotX, 0, robotZ);
	glRotated(robotAngle, 0, 1, 0);
	robot();
	glPopMatrix();
}

void dibujar() {
	inicializarLuces();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(radio * cos(angulo), camaraY, radio * sin(angulo), 0, centroY, 0, 0, 1, 0);
	glClearColor(255 / 255.0, 255 / 255.0, 255 / 255.0, 1);
	glPushMatrix();

	piso();
	ejes();

	earth();
	walls();
		
	robotControl();

	glPopMatrix();
	glutSwapBuffers();
		
}


void timer(int t) {
	glutPostRedisplay();
	glutTimerFunc(20, timer, 0); //in milliseconds
}

void teclado(int tecla, int x, int y) {

	cout << "Angle: " << angulo << " cameraY: " << camaraY << " radio: " << radio << " centroY: " << centroY << endl;

	switch (tecla) {
	case 100:
		angulo += 0.05;
		break;
	case 102:
		angulo -= 0.05;
		break;
	case 101:
		camaraY += 1;
		break;
	case 103:
		camaraY -= 1;
		break;
	case 105:
		robotAngle =  ((int)robotAngle - 90)%360;
		//radio += 2;
		break;
	case 104:
		robotAngle = ((int)robotAngle + 90) % 360;
		//radio -= 2;
		break;
	case 106:
		centroY += 2;
		break;
	case 107:
		centroY -= 2;
		break;
	}
}

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(1009, 711);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("the_walking_robot");
	loadImages();
	glutReshapeFunc(iniciarVentana);
	glutDisplayFunc(dibujar);
	glutSpecialFunc(teclado);
	glutTimerFunc(0, timer, 0);	
	glutMainLoop();
	return 0;
}