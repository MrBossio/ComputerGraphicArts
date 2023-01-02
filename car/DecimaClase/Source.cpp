#include <GL/glut.h>
#include <math.h>
#include <time.h>
#include <iostream>
#include "Texturas/RgbImage.h"

using namespace std;

float camaraX = -20;
float camaraY = 48;
float camaraZ = 40;

float radio = 18;
float angulo = 1.68;
float centroY = -42;

GLuint textures[5];
GLUquadric* quad;


float carrox = 0;
float carroz = 0;
float angle = 0;
float velocity = 0.2;

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
	loadTexturesFromFile("Texturas/assets/concreto.bmp", 0);
	loadTexturesFromFile("Texturas/assets/cesped.bmp", 1);
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

void bloqueCesped() {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textures[1]);
	glColor3ub(255, 255, 255);


	glBegin(GL_POLYGON);
	glTexCoord2f(0, 2); glVertex3d(-20, 0, -10);
	glTexCoord2f(4, 2); glVertex3d(20, 0, -10);
	glTexCoord2f(4, 0); glVertex3d(20, 0, 10);
	glTexCoord2f(0, 0); glVertex3d(-20, 0, 10);
	glEnd();

	glDisable(GL_TEXTURE_2D);
}

void lines(float posX, float posZ, float rotation) {
	glPushMatrix();
	glTranslated(posX, 0, posZ);
	glRotated(rotation, 0, 1, 0);	
	glBegin(GL_POLYGON);
	glColor3ub(255, 255, 255);
	glVertex3d(-0.5, 0, -5);
	glVertex3d(0.5, 0, -5);
	glVertex3d(0.5, 0, 5);
	glVertex3d(-0.5, 0, 5);
	glEnd();
	glPopMatrix();
	
}

void piso() {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textures[0]);
	glColor3ub(255, 255, 255);

	glPushMatrix();
	glTranslated(0, -0.1, 0);
	glBegin(GL_POLYGON);	
	glTexCoord2f(0,7); glVertex3d(-55, 0, -35);
	glTexCoord2f(11,7); glVertex3d(55, 0, -35);
	glTexCoord2f(11,0); glVertex3d(55, 0, 35);
	glTexCoord2f(0,0); glVertex3d(-55, 0, 35);
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);


	//cesped
	glPushMatrix();
	glTranslated(-25, 0, -15);
	bloqueCesped();
	glPopMatrix();


	glPushMatrix();
	glTranslated(25, 0, -15);
	bloqueCesped();
	glPopMatrix();

	glPushMatrix();
	glTranslated(-25, 0, 15);
	bloqueCesped();
	glPopMatrix();

	glPushMatrix();
	glTranslated(25, 0, 15);
	bloqueCesped();
	glPopMatrix();

	//vertical lines
	lines(0, 0, 0);
	lines(0, 20, 0);
	lines(0, -20, 0);
	lines(-50, 0, 0);
	lines(50, 0, 0);
	lines(-50, -20, 0);
	lines(-50, 20, 0);
	lines(50, -20, 0);
	lines(50, 20, 0);

	//horizontal lines

	lines(0, 30, 90);
	lines(0, -30, 90);

	lines(20, 0, 90);
	lines(40, 0, 90);
	lines(-20, 0, 90);
	lines(-40, 0, 90);

	lines(20, 30, 90);
	lines(40, 30, 90);
	lines(-20, 30, 90);
	lines(-40, 30, 90);

	lines(20, -30, 90);
	lines(40, -30, 90);
	lines(-20, -30, 90);
	lines(-40, -30, 90);
	
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


void llantas() {
	//llantas

	glPushMatrix();
	glColor3ub(50, 50, 50);
	glTranslated(0, 0, 0);
	glRotated(0, 1, 0, 0);
	glScaled(1, 1, 2);
	glutSolidTorus(0.2, 0.8, 16, 16);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(150, 150, 150);
	glTranslated(0, 0, 0);
	glRotated(0, 1, 0, 0);
	glScaled(1, 1, 2.2);
	glutSolidTorus(0.15, 0.6, 16, 16);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(100, 100, 100);
	glTranslated(0, 0, 0.3);
	glRotated(-180, 0, 1, 0);
	glScaled(1, 1, 2.2);
	glutSolidCone(0.2, 1, 16, 4);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(150, 150, 150);
	glTranslated(-0, 0, 0);
	glRotated(0, 1, 0, 0);
	glScaled(10, 3, 3);
	glutSolidCube(0.1);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(150, 150, 150);
	glTranslated(-0, 0, 0);
	glRotated(90, 0, 0, 1);
	glScaled(10, 3, 3);
	glutSolidCube(0.1);
	glPopMatrix();
}

void carro() {

	int ancho = 2;
	int largo = 2;
	int alto = 4;

	//techo
	glPushMatrix();
	glTranslated(0, 0, 0);
	glBegin(GL_POLYGON);
	glColor3ub(255, 50,50);
	glVertex3d(-largo, alto, -ancho);
	glVertex3d(largo, alto, -ancho);
	glVertex3d(largo, alto, ancho);
	glVertex3d(-largo, alto, ancho);
	glEnd();
	glPopMatrix();

	glBegin(GL_POLYGON);
	glColor3ub(255, 25, 25);
	glVertex3d(4, 2, -2);
	glVertex3d(2, 4, -2);
	glVertex3d(2, 4, 2);
	glVertex3d(4, 2, 2);
	glEnd();

	//back
	glBegin(GL_POLYGON);
	glColor3ub(200, 0, 0);
	glVertex3d(4, 0, -2);
	glVertex3d(4, 2, -2);
	glVertex3d(4, 2, 2);
	glVertex3d(4, 0, 2);
	glEnd();

	
	glPushMatrix();
	glColor3ub(255, 0, 0);
	glTranslated(4, 0.2, 0);
	glScaled(1,2, 11);
	glutSolidCube(0.4);
	glPopMatrix();

	//separador
	glPushMatrix();
	glColor3ub(0, 0, 0);
	glTranslated(0, 2, 0);
	glScaled(2, 39.5, 42);
	glutSolidCube(0.1);
	glPopMatrix();

	//front
	glPushMatrix();
	glColor3ub(255, 0, 0);
	glTranslated(-6, 0.2, 0);
	glScaled(1, 2, 11);
	glutSolidCube(0.4);
	glPopMatrix();

	glBegin(GL_POLYGON);
	glColor3ub(200, 0, 0);
	glVertex3d(-6, 0, -2);
	glVertex3d(-6, 2, -2);
	glVertex3d(-6, 2, 2);
	glVertex3d(-6, 0, 2);
	glEnd();

	//capot

	glPushMatrix();
	glTranslated(-4, 2, 0);
	glBegin(GL_POLYGON);
	glColor3ub(255, 0, 0);
	glVertex3d(-largo, 0, -ancho);
	glVertex3d(largo, 0, -ancho);
	glVertex3d(largo, 0, ancho);
	glVertex3d(-largo, 0, ancho);
	glEnd();
	glPopMatrix();


	//izquierda
	glPushMatrix();
	glTranslated(0, 0, 2);
	glBegin(GL_POLYGON);
	glColor3ub(200, 0, 0);
	glVertex3d(-largo*3, 0, 0);
	glVertex3d(-largo * 3, 2, 0);
	glVertex3d(largo * 2, 2, 0);
	glVertex3d(largo * 2, 0, 0);
	glEnd();
	glPopMatrix();



	//derecha
	glPushMatrix();
	glTranslated(0, 0, -2);
	glBegin(GL_POLYGON);
	glColor3ub(200, 0, 0);
	glVertex3d(-largo * 3, 0, 0);
	glVertex3d(-largo * 3, 2, 0);
	glVertex3d(largo * 2, 2, 0);
	glVertex3d(largo * 2, 0, 0);
	glEnd();
	glPopMatrix();

	//lunas

	glPushMatrix();
	glTranslated(0, 0, 1.95);
	glBegin(GL_POLYGON);
	glColor3ub(255, 0, 0);
	glVertex3d(-4, 2, 0);
	glVertex3d(-2, 4, 0);
	glVertex3d(2, 4, 0);
	glVertex3d(4, 2, 0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, 0, -1.95);
	glBegin(GL_POLYGON);
	glColor3ub(255, 0, 0);
	glVertex3d(-4, 2, 0);
	glVertex3d(-2, 4, 0);
	glVertex3d(2, 4, 0);
	glVertex3d(4, 2, 0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, 0, 2);
	glBegin(GL_POLYGON);
	glColor3ub(153, 217, 234);
	glVertex3d(-3.9, 1.9, 0);
	glVertex3d(-1.9, 3.9, 0);
	glVertex3d(1.9, 3.9, 0);
	glVertex3d(3.9, 1.9, 0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, 0, -2);
	glBegin(GL_POLYGON);
	glColor3ub(153, 217, 234);
	glVertex3d(-3.9, 1.9, 0);
	glVertex3d(-1.9, 3.9, 0);
	glVertex3d(1.9, 3.9, 0);
	glVertex3d(3.9, 1.9, 0);
	glEnd();
	glPopMatrix();

	glBegin(GL_POLYGON);
	glColor3ub(153, 217, 234);
	glVertex3d(-4, 2, -2);
	glVertex3d(-2, 4, -2);
	glVertex3d(-2, 4, 2);
	glVertex3d(-4, 2, 2);
	glEnd();


	//anadidos
	//turbo cono
	glPushMatrix();
	glColor3ub(225, 0, 0);
	glTranslated(3.5, 3.0, -1);
	glRotated(-90, 0, 1, 0);
	glRotated(45, 0, 0, 1);
	glutSolidCone(0.75, 4, 4, 4);
	glPopMatrix();
	glPushMatrix();
	glColor3ub(50, 50, 50);
	glTranslated(3.6, 3.0, -1);
	glRotated(-90, 0, 1, 0);
	glRotated(45, 0, 0, 1);
	glutSolidCone(0.70, 4, 4, 4);
	glPopMatrix();
	glPushMatrix();
	glColor3ub(225, 0, 0);
	glTranslated(3.5, 3.0, 1);
	glRotated(-90, 0, 1, 0);
	glRotated(45, 0, 0, 1);
	glutSolidCone(0.75, 4, 4, 4);
	glPopMatrix();
	glPushMatrix();
	glColor3ub(50, 50, 50);
	glTranslated(3.6, 3.0, 1);
	glRotated(-90, 0, 1, 0);
	glRotated(45, 0, 0, 1);
	glutSolidCone(0.70, 4, 4, 4);
	glPopMatrix();

	//turbo cilindro
	glPushMatrix();
	glColor3ub(225, 0, 0);
	glTranslated(4.1, 0.9, -1.3);
	glRotated(-90, 0, 1, 0);
	glRotated(45, 0, 0, 1);
	glutSolidCone(0.31, 4, 16, 4);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(50, 50, 50);
	glTranslated(4.2, 0.9, -1.3);
	glRotated(-90, 0, 1, 0);
	glRotated(45, 0, 0, 1);
	glutSolidCone(0.30, 4, 16, 4);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(225, 0, 0);
	glTranslated(4.1, 1.6, -1.3);
	glRotated(-90, 0, 1, 0);
	glRotated(45, 0, 0, 1);
	glutSolidCone(0.31, 4, 16, 4);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(50, 50, 50);
	glTranslated(4.2, 1.6, -1.3);
	glRotated(-90, 0, 1, 0);
	glRotated(45, 0, 0, 1);
	glutSolidCone(0.30, 4, 16, 4);
	glPopMatrix();

	//

	glPushMatrix();
	glColor3ub(225, 0, 0);
	glTranslated(4.1, 0.9, 1.3);
	glRotated(-90, 0, 1, 0);
	glRotated(45, 0, 0, 1);
	glutSolidCone(0.31, 4, 16, 4);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(50, 50, 50);
	glTranslated(4.2, 0.9, 1.3);
	glRotated(-90, 0, 1, 0);
	glRotated(45, 0, 0, 1);
	glutSolidCone(0.30, 4, 16, 4);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(225, 0, 0);
	glTranslated(4.1, 1.6, 1.3);
	glRotated(-90, 0, 1, 0);
	glRotated(45, 0, 0, 1);
	glutSolidCone(0.31, 4, 16, 4);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(50, 50, 50);
	glTranslated(4.2, 1.6, 1.3);
	glRotated(-90, 0, 1, 0);
	glRotated(45, 0, 0, 1);
	glutSolidCone(0.30, 4, 16, 4);
	glPopMatrix();

	//

	glPushMatrix();
	glColor3ub(225, 0, 0);
	glTranslated(4.1, 0.9, 0);
	glRotated(-90, 0, 1, 0);
	glRotated(45, 0, 0, 1);
	glutSolidCone(0.31, 4, 16, 4);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(50, 50, 50);
	glTranslated(4.2, 0.9, 0);
	glRotated(-90, 0, 1, 0);
	glRotated(45, 0, 0, 1);
	glutSolidCone(0.30, 4, 16, 4);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(225, 0, 0);
	glTranslated(4.1, 1.6, 0);
	glRotated(-90, 0, 1, 0);
	glRotated(45, 0, 0, 1);
	glutSolidCone(0.31, 4, 16, 4);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(50, 50, 50);
	glTranslated(4.2, 1.6, 0);
	glRotated(-90, 0, 1, 0);
	glRotated(45, 0, 0, 1);
	glutSolidCone(0.30, 4, 16, 4);
	glPopMatrix();


	//luces
	glPushMatrix();
	glColor3ub(225, 0, 0);
	glTranslated(-6.1, 1.3, 1.3);
	glRotated(90, 0, 1, 0);
	glRotated(45, 0, 0, 1);
	glutSolidCone(0.51, 4, 16, 4);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(255, 242, 0);
	glTranslated(-6.15, 1.3, 1.3);
	glRotated(90, 0, 1, 0);
	glRotated(45, 0, 0, 1);
	glutSolidCone(0.5, 4, 16, 4);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(225, 0, 0);
	glTranslated(-6.1, 1.3, -1.3);
	glRotated(90, 0, 1, 0);
	glRotated(45, 0, 0, 1);
	glutSolidCone(0.51, 4, 16, 4);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(255, 242, 0);
	glTranslated(-6.15, 1.3, -1.3);
	glRotated(90, 0, 1, 0);
	glRotated(45, 0, 0, 1);
	glutSolidCone(0.5, 4, 16, 4);
	glPopMatrix();


	glPushMatrix();
	glRotated(0, 0, 1, 0);
	glTranslated(-4, 0, 2);	
	llantas();
	glPopMatrix();
	glPushMatrix();	
	glTranslated(-4, 0, -2);
	glRotated(180, 0, 1, 0);
	llantas();
	glPopMatrix();
	glPushMatrix();
	glTranslated(2, 0, -2);
	glRotated(180, 0, 1, 0);
	llantas();
	glPopMatrix();
	glPushMatrix();
	glTranslated(2, 0, 2);
	glRotated(0, 0, 1, 0);
	llantas();
	glPopMatrix();

}

void carroControl() {

	//float carrox = 0;
	//float carroz = 0;
	//float angle = 0;
	//float velocity = 1;





}

void dibujar() {
	inicializarLuces();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(radio * cos(angulo), camaraY, radio * sin(angulo), 0, centroY, 0, 0, 1, 0);
	glClearColor(200 / 255.0, 200 / 255.0, 200 / 255.0, 1);
	glPushMatrix();

	piso();
	ejes();
	
	glPushMatrix();
	glTranslated(carrox, 1, carroz);
	glRotated(angle, 0, 1, 0);
	carro();
	glPopMatrix();

	glPopMatrix();
	glutSwapBuffers();
		
}


void timer(int t) {
	glutPostRedisplay();
	glutTimerFunc(20, timer, 0); //in milliseconds
}

void carrito(unsigned char tecla, int x, int y) {
	//cout << tecla << endl;
	switch (tecla) {
	case 'w':
		angle = -90;
		carroz -= velocity;
		break;
	case 'a':
		angle = 0;
		carrox -= velocity;
		break;
	case 's':
		angle = 90;
		carroz += velocity;
		break;
	case 'd':
		angle = 180;
		carrox += velocity;
		break;
	}

	cout << carrox << " " << carroz << endl;
}


void teclado(int tecla, int x, int y) {

	//cout << "Angle: " << angulo << " cameraY: " << camaraY << " radio: " << radio << " centroY: " << centroY << endl;

	/*cout << tecla << endl;*/

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
		radio += 2;
		break;
	case 104:
		radio -= 2;
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
	glutCreateWindow("ExamenFinal01");
	loadImages();
	glutReshapeFunc(iniciarVentana);
	glutDisplayFunc(dibujar);
	glutSpecialFunc(teclado);
	glutKeyboardFunc(carrito);
	glutTimerFunc(0, timer, 0);	
	glutMainLoop();
	return 0;
}