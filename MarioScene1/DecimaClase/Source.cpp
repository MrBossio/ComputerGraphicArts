#include <GL/glut.h>
#include <math.h>
#include <time.h>
#include <iostream>
#include "Texturas/RgbImage.h"

using namespace std;

float camaraX = -20;
float camaraY = 10;
float camaraZ = 37;

float radio = 65;
float angulo = 2.12;
float centroY = 12;

GLuint textures[10];
GLUquadric* quad;

float velocity = 1;
int ladoX = 1;
float posCuboX = 0;

float posCubeX = 0;
float directionX = 1;

float giro = 0;
float girocubo = 0;

// variables mario
float anguloPiernaL = 0;
float anguloPiernaR = 0;
float anguloBrazoL = 0;
float anguloBrazoR = 0;
float velocidadPersonaje = 5;
float giroBrazo = 1;
float giroPierna = 1;
float paso = 1;
float altura = 1;
float angleMario = 0;

// variables nube
float nubeposX = 0;
float nubeposY = 20;
float nubeposZ = 0;
float nuberotX = 0;
float nuberotY = 0;
float nuberotZ = 0;
float velocidadNube = 1.5;
float posYturtle = 0;
float multYturtle = 1;



//variables animacion 1
float anim1posZ = -75;
float anim1saltoY = 0;

//variables logo
float logoPosY = 20;



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
	loadTexturesFromFile("Texturas/assets/tejas.bmp", 0);
	loadTexturesFromFile("Texturas/assets/pasto.bmp", 1);
	loadTexturesFromFile("Texturas/assets/bloqueladrillo.bmp", 2);
	loadTexturesFromFile("Texturas/assets/skyloop.bmp", 3);
	loadTexturesFromFile("Texturas/assets/block.bmp", 4);
	loadTexturesFromFile("Texturas/assets/caminopiedra.bmp", 5);
	loadTexturesFromFile("Texturas/assets/paredpiedra.bmp", 6);
	loadTexturesFromFile("Texturas/assets/box.bmp", 7);
	loadTexturesFromFile("Texturas/assets/peach.bmp", 8);
	loadTexturesFromFile("Texturas/assets/paredladrillos.bmp", 9);

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
	glBindTexture(GL_TEXTURE_2D, textures[1]);
	glColor3ub(255, 255, 255);

	glPushMatrix();
	glTranslated(0, -0.1, 0);
	glBegin(GL_POLYGON);	
	glTexCoord2f(0,20); glVertex3d(-150, 0, -150);
	glTexCoord2f(20,20); glVertex3d(150, 0, -150);
	glTexCoord2f(20,0); glVertex3d(150, 0, 150);
	glTexCoord2f(0,0); glVertex3d(-150, 0, 150);
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

void cubo() {

	glColor3ub(255, 255, 255);
	glPushMatrix();
	glTranslated(0, 7.2, 0);
	glScaled(1.28, 0.72, 1.28);
	glutSolidCube(20);
	glPopMatrix();

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textures[1]);
	glColor3ub(255, 255, 255);
	glPushMatrix();
	glTranslated(-12.8, 0, 12.81);
		glBegin(GL_POLYGON);		
		glTexCoord2f(0, 1); glVertex3d(0,14.4,0);
		glTexCoord2f(1, 1); glVertex3d(25.6,14.4,0);
		glTexCoord2f(1, 0); glVertex3d(25.6, 0, 0);
		glTexCoord2f(0, 0); glVertex3d(0, 0, 0);
		glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);




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
	gluSphere(quad,125,50,50);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
}



void stone_road() {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textures[5]);
	glPushMatrix();
	glColor3ub(255, 255, 255);
	glTranslated(0, 0, 0);
	glRotated(90, 1, 0, 0);
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0); glVertex3d(-5, -75, 0);
	glTexCoord2f(2, 0); glVertex3d(5, -75, 0);
	glTexCoord2f(2, 20); glVertex3d(5, 75, 0);
	glTexCoord2f(0, 20); glVertex3d(-5, 75, 0);
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

void boxSide() {
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3d(-5, 5, 0);
	glTexCoord2f(1, 1); glVertex3d(5, 5, 0);
	glTexCoord2f(1, 0); glVertex3d(5, -5, 0);
	glTexCoord2f(0, 0); glVertex3d(-5, -5, 0);
	glEnd();
}

void wallSide() {
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 3); glVertex3d(-5, 5, 0);
	glTexCoord2f(3, 3); glVertex3d(5, 5, 0);
	glTexCoord2f(3, 0); glVertex3d(5, -5, 0);
	glTexCoord2f(0, 0); glVertex3d(-5, -5, 0);
	glEnd();
}

void tejado() {


	int size = 10;
	int textureTiles = 3;
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textures[0]);

	glPushMatrix();
	glColor3ub(255, 255, 255);
	glTranslated(0, 12.8, 0);
	glBegin(GL_POLYGON);
	glTexCoord2f(0, textureTiles); glVertex3d(-size, 0, size);
	glTexCoord2f(textureTiles, textureTiles); glVertex3d(size, 0, size);
	glTexCoord2f(textureTiles, 0); glVertex3d(size, 0, -size);
	glTexCoord2f(0, 0); glVertex3d(-size, 0, -size);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, 12.8, 0);
	glColor3ub(255, 255, 255);
	glBegin(GL_POLYGON);
	glTexCoord2f(0, textureTiles); glVertex3d(-size, 0, size);
	glTexCoord2f(textureTiles, textureTiles); glVertex3d(0, size, size);
	glTexCoord2f(textureTiles, 0); glVertex3d(0, size, -size);
	glTexCoord2f(0, 0); glVertex3d(-size, 0, -size);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, 12.8, 0);
	glColor3ub(255, 255, 255);
	glScaled(-1, 1, 1);
	glBegin(GL_POLYGON);
	glTexCoord2f(0, textureTiles); glVertex3d(-size, 0, size);
	glTexCoord2f(textureTiles, textureTiles); glVertex3d(0, size, size);
	glTexCoord2f(textureTiles, 0); glVertex3d(0, size, -size);
	glTexCoord2f(0, 0); glVertex3d(-size, 0, -size);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, 12.8, 0);
	glColor3ub(255, 255, 255);
	glScaled(-1, 1, 1);
	glBegin(GL_POLYGON);
	glTexCoord2f(-textureTiles, 0); glVertex3d(-size, 0, size);
	glTexCoord2f(0, textureTiles); glVertex3d(0, size, size);
	glTexCoord2f(textureTiles, 0); glVertex3d(size, 0, size);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, 12.8, 0);
	glColor3ub(255, 255, 255);
	glScaled(-1, 1, 1);
	glBegin(GL_POLYGON);
	glTexCoord2f(-textureTiles, 0); glVertex3d(-size, 0, -size);
	glTexCoord2f(0, textureTiles); glVertex3d(0, size, -size);
	glTexCoord2f(textureTiles, 0); glVertex3d(size, 0, -size);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, 12.8, 0);
	glColor3ub(255, 255, 255);
	glScaled(-1, 1, 1);
	glBegin(GL_POLYGON);
	glTexCoord2f(0, textureTiles); glVertex3d(-size, 0, size);
	glTexCoord2f(textureTiles, textureTiles); glVertex3d(0, size, size);
	glTexCoord2f(textureTiles, 0); glVertex3d(0, size, -size);
	glTexCoord2f(0, 0); glVertex3d(-size, 0, -size);
	glEnd();
	glPopMatrix();


	size = 11;
	glPushMatrix();
	glColor3ub(255, 255, 255);
	glTranslated(0, 6.4, 0);
	glBegin(GL_POLYGON);
	glTexCoord2f(0, textureTiles); glVertex3d(-size, 0, size);
	glTexCoord2f(textureTiles, textureTiles); glVertex3d(size, 0, size);
	glTexCoord2f(textureTiles, 0); glVertex3d(size, 0, -size);
	glTexCoord2f(0, 0); glVertex3d(-size, 0, -size);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor3ub(255, 255, 255);
	glTranslated(0, 0.01, 0);
	glBegin(GL_POLYGON);
	glTexCoord2f(0, textureTiles); glVertex3d(-size, 0, size);
	glTexCoord2f(textureTiles, textureTiles); glVertex3d(size, 0, size);
	glTexCoord2f(textureTiles, 0); glVertex3d(size, 0, -size);
	glTexCoord2f(0, 0); glVertex3d(-size, 0, -size);
	glEnd();
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);

	//peach
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textures[8]);

	glPushMatrix();
	glTranslated(1.8, 12.8, 0);
	glColor3ub(255, 255, 255);
	glScaled(-1, 1, 1);
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0); glVertex3d(0, 0, size);
	glTexCoord2f(0, 1); glVertex3d(0, 2.4*3, size);
	glTexCoord2f(1, 1); glVertex3d(1.3*3, 2.4*3, size);
	glTexCoord2f(1, 0); glVertex3d(1.3*3, 0, size);
	glEnd();
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
}


void paredesCastillo() {


	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textures[2]);
	glColor3ub(255, 255, 255);

	glPushMatrix();
	glTranslated(0, 5, 0);
	glRotated(90, 1, 0, 0);
	wallSide();
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, -5, 0);
	glRotated(90, 1, 0, 0);
	wallSide();
	glPopMatrix();

	glPushMatrix();
	glTranslated(5, 0, 0);
	glRotated(90, 0, 1, 0);
	wallSide();
	glPopMatrix();

	glPushMatrix();
	glTranslated(-5, 0, 0);
	glRotated(90, 0, 1, 0);
	glRotated(180, 0, 1, 0);
	wallSide();
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, 0, 5);
	glRotated(90, 0, 0, 1);
	glRotated(-90, 0, 0, 1);
	wallSide();
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, 0, -5);
	glRotated(90, 0, 0, 1);
	glRotated(-180, 0, 1, 0);
	glRotated(90, 0, 0, 1);
	wallSide();
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);


}

void paredes() {

	//puerta
	glPushMatrix();
	glColor3ub(0, 0, 0);
	glTranslated(0, 3.2, 5.2);
	glScaled(0.5, 1, 1);
	glutSolidCube(6.1);
	glPopMatrix();

	//marco
	glPushMatrix();
	glColor3ub(200, 200, 200);
	glTranslated(0, 3.1, 5);
	glScaled(0.6, 1, 1);
	glutSolidCube(6.3);
	glPopMatrix();

	//casa
	double multiplier = 1.6;
	glPushMatrix();
	glColor3ub(255, 255, 255);
	glTranslated(0, 6.4, 0);
	glScaled(1* multiplier, 0.8* multiplier, 1* multiplier);
	
	paredesCastillo();

	glPopMatrix();




	//ventana 1
	glPushMatrix();
	glTranslated(5, 9.5, 6.8);
	glScaled(0.9, 0.9, 0.9);

	//marco
	glPushMatrix();
	glColor3ub(100, 100, 100);
	glTranslated(0, 0, 0);
	glScaled(1, 1, 1);
	glutSolidCube(3.5);
	glPopMatrix();

	//ventanas
	glPushMatrix();
	glColor3ub(255, 143, 0);
	glTranslated(0.775, 0.775, 1.2);
	glScaled(1, 1, 1);
	glutSolidCube(1.35);
	glPopMatrix();
	glPushMatrix();
	glColor3ub(255, 143, 0);
	glTranslated(-0.775, 0.775, 1.2);
	glScaled(1, 1, 1);
	glutSolidCube(1.35);
	glPopMatrix();
	glPushMatrix();
	glColor3ub(255, 143, 0);
	glTranslated(0.775, -0.775, 1.2);
	glScaled(1, 1, 1);
	glutSolidCube(1.35);
	glPopMatrix();
	glPushMatrix();
	glColor3ub(255, 143, 0);
	glTranslated(-0.775, -0.775, 1.2);
	glScaled(1, 1, 1);
	glutSolidCube(1.35);
	glPopMatrix();

	glPopMatrix();

	//ventana 1
	glPushMatrix();
	glTranslated(-4, 9.5, 6.8);
	glScaled(0.9, 0.9, 0.9);

	//marco
	glPushMatrix();
	glColor3ub(100, 100, 100);
	glTranslated(0, 0, 0);
	glScaled(1, 1, 1);
	glutSolidCube(3.5);
	glPopMatrix();

	//ventanas
	glPushMatrix();
	glColor3ub(255, 143, 0);
	glTranslated(0.775, 0.775, 1.2);
	glScaled(1, 1, 1);
	glutSolidCube(1.35);
	glPopMatrix();
	glPushMatrix();
	glColor3ub(255, 143, 0);
	glTranslated(-0.775, 0.775, 1.2);
	glScaled(1, 1, 1);
	glutSolidCube(1.35);
	glPopMatrix();
	glPushMatrix();
	glColor3ub(255, 143, 0);
	glTranslated(0.775, -0.775, 1.2);
	glScaled(1, 1, 1);
	glutSolidCube(1.35);
	glPopMatrix();
	glPushMatrix();
	glColor3ub(255, 143, 0);
	glTranslated(-0.775, -0.775, 1.2);
	glScaled(1, 1, 1);
	glutSolidCube(1.35);
	glPopMatrix();

	glPopMatrix();


}

void reja() {
	//horizontal
	glPushMatrix();
	glColor3ub(200, 200, 200);
	glTranslated(9.5, 3.2, 10);
	glScaled(0.05, 1, 0.05);
	glutSolidCube(6.3);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(200, 200, 200);
	glTranslated(6, 3.2, 10);
	glScaled(0.05, 1, 0.05);
	glutSolidCube(6.3);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(200, 200, 200);
	glTranslated(2.5, 3.2, 10);
	glScaled(0.05, 1, 0.05);
	glutSolidCube(6.3);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(200, 200, 200);
	glTranslated(-9.5, 3.2, 10);
	glScaled(0.05, 1, 0.05);
	glutSolidCube(6.3);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(200, 200, 200);
	glTranslated(-6, 3.2, 10);
	glScaled(0.05, 1, 0.05);
	glutSolidCube(6.3);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(200, 200, 200);
	glTranslated(-2.5, 3.2, 10);
	glScaled(0.05, 1, 0.05);
	glutSolidCube(6.3);
	glPopMatrix();
}


void casa() {
	glPushMatrix();
	glTranslated(135, 0, 0);
	glScaled(4, 4, 4);
	glRotated(-90, 0, 1, 0);

	paredes();
	reja();
	tejado();

	glPopMatrix();
}

void cube() {


	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textures[4]);
	glColor3ub(255, 255, 255);

	glPushMatrix();
	glTranslated(0, 5, 0);
	glRotated(90, 1, 0, 0);
	boxSide();
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, -5, 0);
	glRotated(90, 1, 0, 0);	
	boxSide();
	glPopMatrix();

	glPushMatrix();
	glTranslated(5, 0, 0);
	glRotated(90, 0, 1, 0);
	boxSide();
	glPopMatrix();

	glPushMatrix();
	glTranslated(-5, 0, 0);
	glRotated(90, 0, 1, 0);
	glRotated(180, 0, 1, 0);
	boxSide();
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, 0, 5);
	glRotated(90, 0, 0, 1);
	glRotated(-90, 0, 0, 1);
	boxSide();
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, 0, -5);
	glRotated(90, 0, 0, 1);
	glRotated(-180, 0, 1, 0);
	glRotated(90, 0, 0, 1);
	boxSide();
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);


}


void redcube() {

	girocubo += 0.5;

	glPushMatrix();
	//sobre eje
	//glTranslated(20, 10, 0);	
	//glRotated(giro, 0, 1, 0);
	//sobre otro eje
	glRotated(girocubo, 0, 1, 0);
	glTranslated(50, 50, 0);
	cube();
	glPopMatrix();

	glPushMatrix();
	//sobre eje
	//glTranslated(20, 10, 0);	
	//glRotated(giro, 0, 1, 0);
	//sobre otro eje
	glRotated(girocubo, 0, 1, 0);
	glTranslated(-50, 50, 0);
	cube();
	glPopMatrix();

	glPushMatrix();
	//sobre eje
	//glTranslated(20, 10, 0);	
	//glRotated(giro, 0, 1, 0);
	//sobre otro eje
	glRotated(girocubo, 0, 1, 0);
	glTranslated(0, 50, 50);
	cube();
	glPopMatrix();

	glPushMatrix();
	//sobre eje
	//glTranslated(20, 10, 0);	
	//glRotated(giro, 0, 1, 0);
	//sobre otro eje
	glRotated(girocubo, 0, 1, 0);
	glTranslated(0, 50, -50);
	cube();
	glPopMatrix();


}


//mario
void body() {

	glPushMatrix();
	glScaled(1.5, 1.5, 1.5);

	glPushMatrix();
	glColor3ub(0, 0, 255);
	glTranslated(0, 2, 0);
	glRotated(0, 1.5, 0, 0);
	glScaled(1, 0.8, 1);
	glutSolidSphere(1, 16, 16);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(0, 0, 255);
	glTranslated(0, 2.3, 0);
	glRotated(0, 1.5, 0, 0);
	glScaled(1, 0.8, 1);
	glutSolidSphere(1, 16, 16);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(255, 0, 0);
	glTranslated(0, 2.8, -0.1);
	glRotated(0, 0, 0, 0);
	glScaled(0.9, 0.6, 0.9);
	glutSolidSphere(1, 16, 16);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(0, 0, 255);
	glTranslated(-0.4, 2.8, -0.1);
	glScaled(2.0, 0.8, 1.1);
	glRotated(90, 0, 1, 0);
	glRotated(5, 1, 0, 0);
	glutSolidTorus(0.1, 0.8, 8, 16);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(0, 0, 255);
	glTranslated(0.4, 2.8, -0.1);
	glScaled(2, 0.8, 1.1);
	glRotated(90, 0, 1, 0);
	glRotated(-5, 1, 0, 0);
	glutSolidTorus(0.1, 0.8, 8, 16);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(255, 255, 0);
	glTranslated(-0.45, 2.6, 0.9);
	glRotated(-10, 0, 1, 0);
	glScaled(1, 1, 0.3);
	glutSolidSphere(0.2, 16, 16);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(255, 255, 0);
	glTranslated(0.45, 2.6, 0.9);
	glRotated(10, 0, 1, 0);
	glScaled(1, 1, 0.3);
	glutSolidSphere(0.2, 16, 16);
	glPopMatrix();

	//gluPartialDisk(gluNewQuadric(), 1, 4, 16, 16, 0, 180);

	glPopMatrix();
}

void legs(int i) {
	//arms and legs
	glPushMatrix();
	glScaled(i * 1.5, 1.5, 1.5);


		//legs
		glPushMatrix();
		glColor3ub(0, 0, 255);
		glTranslated(-0.4, 1.5, 0);
		glRotated(90, 1, 0, 0);
		glRotated(-15, 1, 1, 0);
		glScaled(1, 1, 1.5);
		gluCylinder(gluNewQuadric(), 0.35, 0.35, 0.5, 16, 4);
		glPopMatrix();

		glPushMatrix();
		glColor3ub(0, 0, 255);
		glTranslated(-0.55, 1, 0.1);
		glRotated(90, 1, 0, 0);
		glRotated(15, 1, 1, 0);
		glScaled(1, 1, 1.5);
		gluCylinder(gluNewQuadric(), 0.35, 0.35, 0.5, 16, 4);
		glPopMatrix();

		glPushMatrix();
		glColor3ub(91, 19, 13);
		glTranslated(-0.5, 0.2, 0.2);
		glScaled(0.3, 0.2, 0.45);
		glRotated(45, 0, 1, 0);
		glutSolidDodecahedron();
		glPopMatrix();
				
	glPopMatrix();
}

void arms(int i) {
	//arms and legs
	glPushMatrix();
	glScaled(i * 1.5, 1.5, 1.5);

	//arms

	glPushMatrix();
	glColor3ub(255, 0, 0);
	glTranslated(-1, 2.8, 0);
	glRotated(45, 1, 0, 0);
	glRotated(45, 0, 1, 0);
	glScaled(2, 1, 1);	
	glutSolidSphere(0.3, 8, 8);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(255, 0, 0);
	glTranslated(-1.20, 2.5, 0.3);
	glRotated(45, 1, 0, 0);
	glRotated(-75, 0, 1, 0);
	glScaled(1.3, 1, 1);	
	glutSolidSphere(0.3, 8, 8);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(255, 0, 0);
	glTranslated(-1.20, 2.5, 0.3);
	glRotated(45, 1, 0, 0);
	glRotated(-75, 0, 1, 0);
	glScaled(1.3, 1, 1);	
	glutSolidSphere(0.3, 8, 8);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(255, 255, 255);
	glTranslated(-1.20, 2.2, 0.5);
	glRotated(0, 0, 0, 0);
	glScaled(1.2, 1.2, 1.2);
	glutSolidSphere(0.3, 8, 8);
	glPopMatrix();

	//ejes();
	glPopMatrix();
}

void head() {

	glPushMatrix();
	glColor3ub(255, 209, 149);
	glTranslated(0, 6.2, 0);
	glRotated(0, 0, 0, 0);
	glScaled(1, 1, 1);
	gluSphere(gluNewQuadric(), 1.5, 30, 30);
	//glutSolidSphere(1.5, 12, 12);
	glPopMatrix();


	//ears
	glPushMatrix();	
	glColor3ub(255, 209, 149);
	glTranslated(-1.5, 6.2, -0.2);
	glRotated(15, 0, 1, 0);
	glScaled(1, 5, 5);
	gluSphere(gluNewQuadric(), 0.1, 30, 30);
	//glutSolidSphere(0.5, 12, 12);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(255, 209, 149);
	glTranslated(1.5, 6.2, -0.2);
	glRotated(-15, 0, 1, 0);
	glScaled(1, 5, 5);
	gluSphere(gluNewQuadric(), 0.1, 30, 30);
	//glutSolidSphere(0.5, 12, 12);
	glPopMatrix();

	//hat
	glColor3ub(255, 20, 0);
	glPushMatrix();	
	glTranslated(0, 7.4, -0.2);
	glRotated(-20, 1, 0, 0);
	glScaled(1, 0.5, 1);
	gluSphere(gluNewQuadric(), 1.7, 30, 30);
	//glutSolidSphere(1.7, 12, 12);
	glPopMatrix();

	glColor3ub(255, 20, 0);
	glPushMatrix();
	glTranslated(0, 7.1, 0.2);
	glRotated(-10, 1, 0, 0);
	glScaled(3, 0.75, 3);
	gluSphere(gluNewQuadric(), 0.5, 30, 30);
	//glutSolidSphere(1.5, 12, 12);
	glPopMatrix();

	//nose
	glPushMatrix();
	glColor3ub(255, 209, 149);
	glTranslated(0, 6, 1.6);
	glRotated(0, 0, 0, 0);
	glScaled(1, 1, 1);
	glutSolidSphere(0.5, 12, 12);
	glPopMatrix();


	glPushMatrix();
	glColor3ub(91, 19, 13);
	glTranslated(-0.4, 5.7, 1.4);
	glRotated(-90, 0, 0, 1);
	glScaled(1, 1, 1);
	gluPartialDisk(gluNewQuadric(), 0.05, 0.4, 16, 16, 0, 180);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(91, 19, 13);
	glTranslated(0.4, 5.75, 1.4);
	glRotated(-90, 0, 0, 1);
	glScaled(1, 1, 1);
	gluPartialDisk(gluNewQuadric(), 0.05, 0.4, 16, 16, 0, 180);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(91, 19, 13);
	glTranslated(-0.6, 6.7, 1.35);
	glRotated(90, 0, 0, 1);
	glScaled(1, 1, 1);
	gluPartialDisk(gluNewQuadric(), 0.3, 0.4, 16, 16, 0, 135);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(91, 19, 13);
	glTranslated(0.6, 6.7, 1.35);
	glRotated(45, 0, 0, 1);
	glScaled(1, 1, 1);
	gluPartialDisk(gluNewQuadric(), 0.3, 0.4, 16, 16, 0, 135);
	glPopMatrix();

}

void eyes(int x) {

	glPushMatrix();
	glScaled(x * 1, 1, 1);

	//eyes
	glPushMatrix();
	glColor3ub(255, 255, 255);
	glTranslated(-0.625, 6.5, 1.35);
	glRotated(-15, 0.2, 1, 0);
	glScaled(7.5, 8, 1);
	glutSolidSphere(0.05, 12, 12);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(0, 0, 255);
	glTranslated(-0.55, 6.5, 1.4);
	glRotated(-15, 0.2, 1, 0);
	glScaled(2.75, 3.5, 0.5);
	glutSolidSphere(0.1, 12, 12);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(0, 0, 0);
	glTranslated(-0.5, 6.5, 1.45);
	glRotated(-15, 0.2, 1, 0);
	glScaled(1.75, 3, 0.5);
	glutSolidSphere(0.1, 12, 12);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(255, 255, 255);
	glTranslated(-0.45, 6.5, 1.5);
	glRotated(-15, 0.2, 1, 0);
	glScaled(0.75, 1.25, 0.5);
	glutSolidSphere(0.1, 12, 12);
	glPopMatrix();

	glPopMatrix();

}

void mario() {
	glPushMatrix();
	altura = 0.5*-abs(-1.0 / 45 * anguloBrazoL) ;

	glTranslated(0, altura, 0);
	glScaled(2, 2, 2);

	// variables mario
	//float anguloPiernaL = 0;
	//float anguloPiernaR = 0;
	//float anguloBrazoL = 0;
	//float anguloBrazoR = 0;
	//float velocidadPersonaje = 1;


	body();
	head();
	eyes(1);
	eyes(-1);


	glPushMatrix();
	glTranslated(2.6, 4.4, 0);
	anguloBrazoL += (giroBrazo * velocidadPersonaje);
	if (anguloBrazoL > 60) giroBrazo = -1;
	if (anguloBrazoL < -60) giroBrazo = 1;
	glRotated(anguloBrazoL, 1, 0, 0);
	glTranslated(-2.6, -4.4, 0);
	arms(1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(2.6, 4.4, 0);
	anguloBrazoR += (-giroBrazo * velocidadPersonaje);
	glRotated(anguloBrazoR, 1, 0, 0);
	glTranslated(-2.6, -4.4, 0);
	arms(-1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, 2, 0);
	anguloPiernaR += (giroPierna*velocidadPersonaje);
	if (anguloPiernaR > 60) giroPierna = -1;
	if (anguloPiernaR < -60) giroPierna = 1;
	glRotated(anguloPiernaR*0.75, 1, 0, 0);
	glTranslated(0, -2, 0);
	legs(-1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, 2, 0);
	anguloPiernaL += (-giroPierna*velocidadPersonaje);
	glRotated(anguloPiernaL*0.75, 1, 0, 0);
	glTranslated(0, -2, 0);
	legs(1);
	glPopMatrix();


	
	
	

	glPopMatrix();
}

//nube

void nube() {

	int radius = 6;

	glPushMatrix();
	glTranslated(0, 10, 0);
	glColor3ub(255, 255, 255);

	glPushMatrix();
	glTranslated(5, 5, 5);
	glutSolidSphere(radius, 16, 16);
	glPopMatrix();

	glPushMatrix();
	glTranslated(5, 5, -5);
	glutSolidSphere(radius, 16, 16);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-5, 5, 5);
	glutSolidSphere(radius, 16, 16);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-5, 5, -5);
	glutSolidSphere(radius, 16, 16);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, 5, 8);
	glutSolidSphere(radius, 16, 16);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, 5, -8);
	glutSolidSphere(radius, 16, 16);
	glPopMatrix();


	glPushMatrix();
	glTranslated(0, 0, 0);
	glutSolidSphere(radius, 16, 16);
	glPopMatrix();

	glPushMatrix();
	glTranslated(3, 2, 4);
	glutSolidSphere(radius, 16, 16);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-3, 2, -4);
	glutSolidSphere(radius, 16, 16);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-3, 2, 4);
	glutSolidSphere(radius, 16, 16);
	glPopMatrix();

	glPushMatrix();
	glTranslated(3, 2, -4);
	glutSolidSphere(radius, 16, 16);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-5, 3.5, 0);
	glutSolidSphere(radius, 16, 16);
	glPopMatrix();

	glPushMatrix();
	glTranslated(5, 3.5, -0);
	glutSolidSphere(radius, 16, 16);
	glPopMatrix();

	glPopMatrix();
	
}

void BodyCharOne() {


	//body
	glPushMatrix();
	glColor3ub(255, 217, 13);
	glTranslated(0, 7, 0);
	glRotated(0, 0, 0, 0);
	glScaled(1, 1, 1);
	glutSolidSphere(2, 16, 16);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(255, 217, 13);
	glTranslated(0, 6.8, 0);
	glRotated(0, 0, 0, 0);
	glScaled(1, 1, 1);
	glutSolidSphere(2, 16, 16);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(255, 255, 0);
	glTranslated(0, 3, 0);
	glRotated(0, 0, 0, 0);
	glScaled(1, 1.2, 1);
	glutSolidSphere(2, 16, 16);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(255, 255, 255);
	glTranslated(0, 3, -1.4);
	glRotated(0, 0, 0, 0);
	glScaled(1.2, 1.2, 0.4);
	glutSolidSphere(2, 16, 16);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(113, 168, 72);
	glTranslated(0, 3, -1.5);
	glRotated(0, 0, 0, 0);
	glScaled(1, 1, 0.8);
	glutSolidSphere(2, 16, 16);
	glPopMatrix();

	//face

	glPushMatrix();
	glColor3ub(0, 0, 0);
	glTranslated(-0.55, 6.5, 1.9);
	glRotated(0, 0, 0, 0);
	glScaled(0.7,0.7,0.7);
	glutSolidSphere(0.4, 16, 16);
	glPopMatrix();//

	glPushMatrix();
	glColor3ub(255, 255, 255);
	glTranslated(-0.9, 6.8, 1.75);
	glRotated(-15, 0, 1, 0);
	glScaled(5 ,5, 1);
	glutSolidSphere(0.2, 32, 32);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(0, 0, 0);
	glTranslated(0.55, 6.5, 1.9);
	glRotated(0, 0, 0, 0);
	glScaled(0.7, 0.7, 0.7);
	glutSolidSphere(0.4, 16, 16);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(255, 255, 255);
	glTranslated(0.9, 6.8, 1.75);
	glRotated(15, 0, 1, 0);
	glScaled(5, 5, 1);
	glutSolidSphere(0.2, 32, 32);
	glPopMatrix();//

	glPushMatrix();
	glColor3ub(255, 217, 13);
	glTranslated(0, 6, 1.75);
	glRotated(0, 0, 0, 0);
	glScaled(1, 1, 1);
	glutSolidSphere(0.4, 16, 16);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(255, 0, 0);
	glTranslated(0, 5.5, 1.4);
	glRotated(18, 1, 0, 0);
	glScaled(2, 1, 0.5);
	glutSolidSphere(0.4, 16, 16);
	glPopMatrix();


}

void armsAndLegsCharOne(int x) {

	//arms
	glPushMatrix();
	glColor3ub(255, 217, 13);
	glTranslated(x * -2.5, 3, 0);
	glRotated(-90, 1, 0, 0);
	glRotated(x * 45, 0, 1, 0);
	glScaled(x * 1, 1, 1);
	gluCylinder(gluNewQuadric(), 0.5, 0.5, 2, 16, 4);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(255, 217, 13);
	glTranslated(x * -2.5, 3, 0);
	glScaled(x * 1, 1, 1);
	glRotated(0, 0, 0, 0);
	glutSolidSphere(0.6, 12, 12);
	glPopMatrix();

	//legs
	glPushMatrix();
	glColor3ub(255, 217, 13);
	glTranslated(x * -1.8, 0, 0);
	glRotated(-90, 1, 0, 0);
	glRotated(x * 15, 0, 1, 0);
	glScaled(x * 1, 1, 1);
	gluCylinder(gluNewQuadric(), 0.6, 0.5, 2, 16, 4);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(255, 217, 13);
	glTranslated(x * -1.8, 0, 0);
	glScaled(x * 1.3, 1, 1.5);
	glRotated(0, 0, 0, 0);
	glutSolidSphere(0.7, 12, 12);
	glPopMatrix();


}

void characterOne() {

	glPushMatrix();
	glTranslated(0, 18, 0);
	glScaled(1.5, 1.5, 1.5);
	BodyCharOne();
	armsAndLegsCharOne(1);
	armsAndLegsCharOne(-1);
	glPopMatrix();

}

void tortuga() {

	

	if (nubeposY < 2) {
		if (posYturtle <= 0) multYturtle = 1;
		else if (posYturtle >= 4) multYturtle = -1;
		posYturtle += multYturtle * 0.2;
		cout << posYturtle << endl;
	}


	glPushMatrix();
	glTranslated(0, posYturtle, 0);
	characterOne();
	glPopMatrix();

	nube();
}

void logoMario() {

	glPushMatrix();
	glScaled(10, 10, 10);

	// back
	glBegin(GL_POLYGON);
	glColor3ub(0, 0, 0);
	glVertex2d(0.6913610386018552, 1.9554379613779733);
	glVertex2d(1.6144155172279206, 1.5796812709638253);
	glVertex2d(1.8431369809582732, 2.3475318992014325);
	glVertex2d(1.9411604654141386, 3.8995704030859573);
	glVertex2d(1.475793348205457, 3.9737568708610214);
	glVertex2d(0.6935046305498318, 2.199814494399562);
	glEnd();
	glBegin(GL_POLYGON);
	glColor3ub(0, 0, 0);
	glVertex2d(2.055762126304459, 1.9740941592421994);
	glVertex2d(1.8431369809582732, 2.3475318992014325);
	glVertex2d(1.9411604654141386, 3.8995704030859573);
	glVertex2d(2.6936390734949893, 3.9950314031448917);
	glVertex2d(2.3478739993169446, 2.301974833031722);
	glEnd();
	glBegin(GL_POLYGON);
	glColor3ub(0, 0, 0);
	glVertex2d(2.383642800093984, 1.5210226827330415);
	glVertex2d(3.1467105500041517, 1.6998666866182355);
	glVertex2d(3.921701233506665, 5.175401828787172);
	glVertex2d(3.921701233506665, 5.312515565099154);
	glVertex2d(3.158633483596498, 5.384053166653231);
	glVertex2d(2.6936390734949893, 3.9950314031448917);
	glVertex2d(2.3478739993169446, 2.301974833031722);
	glEnd();
	glBegin(GL_POLYGON);
	glColor3ub(0, 0, 0);
	glVertex2d(3.647473760882699, 1.586598817490946);
	glVertex2d(4.422464444385213, 5.109825694029268);
	glVertex2d(3.921701233506665, 5.175401828787172);
	glVertex2d(3.1467105500041517, 1.6998666866182355);
	glEnd();
	glBegin(GL_POLYGON);
	glColor3ub(0, 0, 0);
	glVertex2d(3.9753544346722225, 2.0277473604077576);
	glVertex2d(4.076699370207167, 1.598521751083292);
	glVertex2d(4.690730450213004, 1.6998666866182355);
	glVertex2d(4.422464444385213, 5.109825694029268);
	glEnd();
	glBegin(GL_POLYGON);
	glColor3ub(0, 0, 0);
	glVertex2d(3.569974692532446, 1.9323638916689876);
	glVertex2d(4.21381310651915, 2.05159322759245);
	glVertex2d(3.9455471006913565, 3.2915783211964618);
	glEnd();
	glBegin(GL_POLYGON);
	glColor3ub(0, 0, 0);
	glVertex2d(3.218248151558229, 5.258862363933597);
	glVertex2d(2.8188298762146258, 5.556935703742253);
	glVertex2d(2.157107061839403, 5.485398102188175);
	glVertex2d(1.7934575872728384, 4.919058756551728);
	glVertex2d(1.8053805208651847, 4.650792750723937);
	glVertex2d(1.9365327903809948, 4.585216615966033);
	glVertex2d(2.7413308078643746, 3.756572731297967);
	glEnd();
	glBegin(GL_POLYGON);
	glColor3ub(0, 0, 0);
	glVertex2d(2.079607993489151, 3.7446497977056206);
	glVertex2d(1.7636502532919724, 4.054646071106624);
	glVertex2d(1.7338429193111067, 4.340796477322934);
	glVertex2d(1.9365327903809948, 4.585216615966033);
	glVertex2d(2.5088336028136204, 4.4182955456731845);
	glVertex2d(3.093057348838592, 3.8221488660558713);
	glEnd();
	glBegin(GL_POLYGON);
	glColor3ub(0, 0, 0);
	glVertex2d(5.412067932549947, 1.6760208194335449);
	glVertex2d(5.680333938377739, 5.2290550299527325);
	glVertex2d(5.251108329053271, 5.455590768207311);
	glVertex2d(4.404580043996681, 5.288669697914464);
	glVertex2d(4.422464444385213, 5.109825694029268);
	glVertex2d(4.690730450213004, 1.6998666866182355);
	glVertex2d(4.702653383805339, 1.5746758838986017);
	glEnd();
	glBegin(GL_POLYGON);
	glColor3ub(0, 0, 0);
	glVertex2d(6.592438358192234, 5.288669697914464);
	glVertex2d(5.739948606339471, 5.431744901022618);
	glVertex2d(5.680333938377739, 5.2290550299527325);
	glVertex2d(5.394183532161427, 1.8787106905034314);
	glVertex2d(5.638603670804527, 1.5746758838986017);
	glVertex2d(6.169174215663938, 1.8071730889493538);
	glEnd();
	glBegin(GL_POLYGON);
	glColor3ub(0, 0, 0);
	glVertex2d(6.956087832758796, 2.1827454971082614);
	glVertex2d(6.878588764408545, 1.6402520186565062);
	glVertex2d(6.157251282071592, 1.5925602842871212);
	glVertex2d(6.169174215663938, 1.8071730889493538);
	glVertex2d(6.592438358192234, 5.288669697914464);
	glVertex2d(6.5800820894166705, 5.359745129589715);
	glVertex2d(7.421470626736925, 5.494932256689132);
	glVertex2d(8.012662093007512, 5.149902424838383);
	glVertex2d(7.908805666197917, 4.296846410162363);
	glEnd();
	glBegin(GL_POLYGON);
	glColor3ub(0, 0, 0);
	glVertex2d(7.839700143786773, 4.395048994641408);
	glVertex2d(8.087025171363631, 4.144086834306071);
	glVertex2d(8.094299436880599, 3.834930549835003);
	glVertex2d(7.930628462748854, 3.780373558457755);
	glVertex2d(7.199564778293726, 3.838567682593486);
	glEnd();
	glBegin(GL_POLYGON);
	glColor3ub(0, 0, 0);
	glVertex2d(7.930628462748854, 3.780373558457755);
	glVertex2d(8.439827048936504, 3.7149051688050583);
	glVertex2d(8.97812269719202, 2.954744422282079);
	glVertex2d(8.959937033399605, 2.7401535895315727);
	glVertex2d(8.734434802373645, 1.903613055080447);
	glVertex2d(7.930628462748854, 1.5144398499227498);
	glVertex2d(7.112273592090129, 1.776313408533537);
	glVertex2d(6.890408493822653, 2.2782377292042124);
	glVertex2d(7.514914641638598, 3.9845784140939453);
	glEnd();
	glBegin(GL_POLYGON);
	glColor3ub(0, 0, 0);
	glVertex2d(3.63, 2.98);
	glVertex2d(4.2, 2.5);
	glVertex2d(4.87, 5.04);
	glVertex2d(4.17, 5.14);
	glEnd();

	//super

	glPushMatrix();
	glTranslated(0, 0, 0.2);


	glBegin(GL_QUAD_STRIP);
	glColor3ub(1, 155, 217);
	glVertex2d(1.8653492660701274, 4.3313677509486554);
	glVertex2d(2.1088691654216536, 4.614868529298189);
	glVertex2d(2.2833311828675233, 3.9679052146030993);
	glVertex2d(2.4686970764037595, 4.316829249494833);
	glVertex2d(2.908486745381889, 3.9933475921472885);
	glVertex2d(2.548658834399783, 4.404060258217767);
	glVertex2d(3.152006644733415, 4.487656641577244);
	glVertex2d(2.610447465578529, 4.498560517667611);
	glVertex2d(2.4977740793114047, 4.934715561282278);
	glVertex2d(1.9380417733392397, 4.934715561282278);
	glVertex2d(2.566831961217061, 5.029215820732123);
	glVertex2d(2.2397156785060557, 5.363601354170034);
	glVertex2d(2.610447465578529, 5.109177578728145);
	glVertex2d(2.7921787337513093, 5.421755359985323);
	glVertex2d(2.984813878014457, 4.854753803286256);
	glVertex2d(3.202891399821794, 5.101908328001234);
	glEnd();
	glBegin(GL_QUAD_STRIP);
	glColor3ub(252, 207, 0);
	glVertex2d(3.2683146563639958, 5.269101094720188);
	glVertex2d(3.780796832611238, 5.203677838177988);
	glVertex2d(3.1956221490948833, 4.258675243679543);
	glVertex2d(3.6499503195268357, 4.404060258217766);
	glVertex2d(3.5081999303520663, 3.9751744653300096);
	glVertex2d(3.6723125276077813, 4.357582180734021);
	glVertex2d(4.15116474415209, 3.9663497314722953);
	glVertex2d(3.996301899652654, 4.373883532786594);
	glVertex2d(4.399760362953816, 4.237359709346304);
	glVertex2d(4.039695294152509, 4.381458479804402);
	glVertex2d(4.519733977015921, 4.97688327334213);
	glVertex2d(4.0058254982426895, 5.041934979515957);
	glEnd();
	glBegin(GL_QUAD_STRIP);
	glColor3ub(255, 0, 0);
	glVertex2d(5.068288572416108, 3.970847662341962);
	glVertex2d(4.678885304416513, 3.9340536527671977);
	glVertex2d(5.046825400164162, 4.298927581050278);
	glVertex2d(4.645157462306312, 4.289729078656587);
	glVertex2d(4.998204992274677, 4.931362236558833);
	glVertex2d(4.550106270904835, 5.175851475915498);
	glVertex2d(5.015990441604779, 4.997422476927784);
	glVertex2d(5.236927782967115, 5.323027514214556);
	glVertex2d(5.310515802116645, 4.902962571569328);
	glVertex2d(5.715249907439059, 5.05320477733295);
	glVertex2d(5.276787960006443, 4.651536839475105);
	glVertex2d(5.635529553360401, 4.574882652861012);
	glVertex2d(5.221596945644296, 4.611676662435777);
	glVertex2d(5.374905318872483, 4.311192250908533);
	glVertex2d(5.02842839537678, 4.596345825112958);
	glVertex2d(5.0663056752384925, 4.3123452045472055);
	glEnd();
	glBegin(GL_QUAD_STRIP);
	glColor3ub(62, 178, 53);
	glVertex2d(6.672297341957204, 5.12896148714712);
	glVertex2d(6.629706094309711, 4.7882315059671745);
	glVertex2d(6.19482703938267, 5.2208689162811845);
	glVertex2d(6.2060352624477995, 4.938421695039914);
	glVertex2d(5.818230744394304, 5.283634965445911);
	glVertex2d(6.167927304026358, 4.92945511658781);
	glVertex2d(5.800297587490096, 4.853239199744928);
	glVertex2d(6.120852767152812, 4.71874052296337);
	glVertex2d(5.76443127368168, 4.678390919928903);
	glVertex2d(6.0849864533443965, 4.474401260143541);
	glVertex2d(5.762189629068654, 4.521475797017086);
	glVertex2d(6.11636947792676, 4.2883447572623865);
	glVertex2d(5.616482729221966, 4.362319029492244);
	glVertex2d(6.123094411765838, 4.24799515422792);
	glVertex2d(5.703906869129979, 3.9857227345038826);
	glVertex2d(6.331567360777255, 4.272653244971205);
	glVertex2d(6.665572408118126, 3.952098065308493);
	glVertex2d(6.6050480035664245, 4.306277914166595);
	glEnd();
	glBegin(GL_QUAD_STRIP);
	glColor3ub(62, 178, 53);
	glVertex2d(6.486240839076047, 4.427326723269996);
	glVertex2d(6.524348797497489, 4.7030490106721885);
	glVertex2d(6.040153561083876, 4.458709747852359);
	glVertex2d(6.076826248028273, 4.737213188330309);
	glEnd();

	glBegin(GL_QUAD_STRIP);
	glColor3ub(252, 207, 0);
	glVertex2d(7.201325470631336, 3.965547932986649);
	glVertex2d(6.835937398708101, 3.925198329952182);
	glVertex2d(7.174425735275024, 4.987737876526485);
	glVertex2d(6.712646944991672, 5.2567352300896);
	glVertex2d(7.1721840906619985, 5.037054058013056);
	glVertex2d(7.400831841190649, 5.364334171514845);
	glVertex2d(7.48377269187261, 4.933938405813862);
	glVertex2d(7.882785432991236, 5.072920371821471);
	glVertex2d(7.474806113420507, 4.853239199744928);
	glVertex2d(7.795361293083222, 4.586483490794839);
	glVertex2d(7.452389667290246, 4.687357498381007);
	glVertex2d(7.57343847639365, 4.4362933017221);
	glVertex2d(7.421006642707883, 4.642524606120488);
	glVertex2d(7.317890990508688, 4.398185343300659);
	glVertex2d(7.187875602953181, 4.5999333584729944);
	glVertex2d(7.1990838260183105, 4.404910277139736);
	glEnd();
	glBegin(GL_QUAD_STRIP);
	glColor3ub(252, 207, 0);
	glVertex2d(7.5151557164549745, 3.929681619178234);
	glVertex2d(7.941068192929912, 4.113496477446362);
	glVertex2d(7.1990838260183105, 4.404910277139736);
	glVertex2d(7.57343847639365, 4.4362933017221);
	glVertex2d(7.187875602953181, 4.5999333584729944);
	glVertex2d(7.421006642707883, 4.642524606120488);
	glEnd();

	//mario

	glBegin(GL_QUAD_STRIP);
	glColor3ub(255, 0, 0);
	glVertex2d(0.8820110246361276, 2.277411340892305);
	glVertex2d(1.503763378041032, 1.9832889701199297);
	glVertex2d(1.2952715709112437, 3.2230706089452577);
	glVertex2d(1.7792704088911093, 2.8842714223593573);
	glVertex2d(1.555886329823479, 3.8075922825055475);
	glVertex2d(1.815100185905797, 2.9147657509869798);
	glVertex2d(1.9588830208453918, 3.7489613475196775);
	glVertex2d(2.0765989565645198, 2.4349229953061804);
	glVertex2d(2.1614639334783097, 3.198707787530276);
	glVertex2d(2.4406970833236827, 2.889361258780015);
	glVertex2d(2.4270091838214585, 3.7243231284156746);
	glVertex2d(2.4621964189157457, 2.8719104545998935);
	glVertex2d(2.8650530409249497, 3.6726959284158176);
	glVertex2d(2.470636712238238, 2.6014102872732194);
	glVertex2d(3.2021226839348738, 2.0588639915641176);
	glVertex2d(2.5183631688143557, 1.9119156747180446);
	glEnd();
	glBegin(GL_QUAD_STRIP);
	glColor3ub(62,178,53);
	glVertex2d(4.760431754318136, 2.096736385760017);
	glVertex2d(4.183291882887881, 1.9619552181804985);
	glVertex2d(4.193659665009383, 3.6519037039852305);
	glVertex2d(3.941376966719511, 3.1888094358915002);
	glVertex2d(3.816963581261492, 3.7002866872189037);
	glVertex2d(3.7824043075231533, 3.2337364917513396);
	glVertex2d(3.4264437880182665, 3.7383018883310757);
	glVertex2d(3.6614468494389683, 2.7706422236576094);
	glVertex2d(3.184528871849896, 2.87086411749879);
	glVertex2d(3.595784229336125, 2.3006361008162117);
	glVertex2d(3.357325240541589, 1.986146709797335);
	glVertex2d(3.5404893913547832, 1.9619552181804985);
	glEnd();
	glBegin(GL_QUAD_STRIP);
	glColor3ub(62, 178, 53);
	glVertex2d(4.079614061672865, 2.3939461399097244);
	glVertex2d(4.02086329631769, 2.7706422236576094);
	glVertex2d(3.595784229336125, 2.3006361008162117);
	glVertex2d(3.6614468494389683, 2.7706422236576094);
	glEnd();
	glBegin(GL_QUAD_STRIP);
	glColor3ub(252, 207, 0);
	glVertex2d(6.239356547856121, 2.2214961843376853);
	glVertex2d(5.688859332859676, 1.9590830041321294);
	glVertex2d(5.757314945087213, 2.63508217487905);
	glVertex2d(5.25815943926142, 2.609411320293724);
	glVertex2d(5.812601962544498, 2.6630588510852893);
	glVertex2d(5.237817436321573, 2.830767864041579);
	glVertex2d(6.083985638055588, 2.826193981870044);
	glVertex2d(5.554939933548015, 2.9146223705197234);
	glVertex2d(6.199986044056979, 3.4282090270613037);
	glVertex2d(5.635711868391468, 3.2664099802754962);
	glVertex2d(5.522368662940714, 3.8166641706497555);
	glVertex2d(5.229930044443547, 3.355201396507443);
	glVertex2d(4.5967601915506, 3.650322938110085);
	glVertex2d(5.232612967549026, 3.092274932170544);
	glVertex2d(4.728223423719051, 2.569104926602225);
	glVertex2d(5.248710506181897, 2.5422756955474393);
	glVertex2d(4.945054340821331, 1.9672333143647667);
	glVertex2d(5.268776731301124, 2.019028896841533);
	glEnd();
	glBegin(GL_QUAD_STRIP);
	glColor3ub(1, 155, 217);
	glVertex2d(7.0460126550352244, 3.5955569384781043);
	glVertex2d(6.372670082837252, 3.7509436859084033);
	glVertex2d(6.767611399222601, 1.9963683295079468);
	glVertex2d(6.2982139330269, 1.963996090459968);
	glEnd();
	glBegin(GL_QUAD_STRIP);
	glColor3ub(62, 178, 53);
	glVertex2d(7.489512329992542, 3.699148103431637);
	glVertex2d(7.777625257519559, 3.113210576663219);
	glVertex2d(7.113994357035981, 3.200615622092762);
	glVertex2d(7.583391823231683, 2.8153859774218133);
	glVertex2d(7.039538207225628, 2.640575886562727);
	glVertex2d(7.583391823231683, 2.753878723230653);
	glVertex2d(7.214348298084717, 2.1323317335094583);
	glVertex2d(7.803523048757942, 2.5078497064660135);
	glVertex2d(7.936249228854658, 1.8895399406496165);
	glVertex2d(7.877979198568295, 2.4981380347516198);
	glVertex2d(8.632252368386215, 2.2132623311294055);
	glVertex2d(8.159617678285716, 2.6341014387531314);
	glVertex2d(8.810299683150102, 2.9545866053281222);
	glVertex2d(8.13695711095213, 3.0031449639000907);
	glVertex2d(8.37327445600238, 3.585845266763711);
	glVertex2d(7.939486452759456, 3.084075561520038);
	glVertex2d(7.483237884675505, 3.671615910570393);
	glVertex2d(7.75266712240357, 3.0908103681625967);
	glEnd();

	glPopMatrix();
	glPopMatrix();

}

void tree() {
	
	quad = gluNewQuadric();

	glColor3ub(125, 166, 63);
	glPushMatrix();
	glTranslated(0, 25, 0);
	glScaled(8, 8, 8);
	glutSolidDodecahedron();
	glPopMatrix();

	glColor3ub(89, 44, 28);
	glPushMatrix();
	glTranslated(0, 0, 0);
	glRotated(-90, 1, 0, 0);	
	gluCylinder(quad, 6,3,16,16,8);
	glPopMatrix();

	//
	glPushMatrix();
	glScaled(0.7, 0.7, 0.7);

	glColor3ub(125, 166, 63);
	glPushMatrix();
	glTranslated(20, 25, 20);
	glScaled(8, 8, 8);
	glRotated(90, 0, 1, 0);
	glutSolidDodecahedron();
	glPopMatrix();

	glColor3ub(116, 107, 73);
	glPushMatrix();
	glTranslated(20, 0, 20);
	glRotated(-90, 1, 0, 0);
	gluCylinder(quad, 6, 3, 16, 16, 8);
	glPopMatrix();

	glPopMatrix();
	
	//
	glPushMatrix();
	glScaled(0.5, 0.5, 0.5);

	glColor3ub(125, 166, 63);
	glPushMatrix();
	glTranslated(-20, 25, 20);
	glScaled(8, 8, 8);
	glRotated(-90, 0, 1, 0);
	glutSolidDodecahedron();	
	glPopMatrix();

	glColor3ub(89, 44, 28);
	glPushMatrix();
	glTranslated(-20, 0, 20);
	glRotated(-90, 1, 0, 0);
	gluCylinder(quad, 6, 3, 16, 16, 8);
	glPopMatrix();

	glPopMatrix();
}


void forest() {
	int distance = 65;

	glPushMatrix();
	glTranslated(-distance, 0, -distance);
	tree();
	glPopMatrix();

	glPushMatrix();
	glTranslated(distance, 0, -distance);
	tree();
	glPopMatrix();

	glPushMatrix();
	glTranslated(-distance, 0, distance);
	tree();
	glPopMatrix();

	glPushMatrix();
	glTranslated(distance, 0, distance);
	tree();
	glPopMatrix();


	glPushMatrix();
	glTranslated(0, 0, distance+30);
	tree();
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, 0, -distance-30);
	tree();
	glPopMatrix();
}

void animMario1() {

	if (anim1posZ < 0) anim1posZ += 0.5;

	if (anim1posZ < -25 && anim1posZ > -35) anim1saltoY += 0.75;
	if (anim1posZ < -15 && anim1posZ > -25) anim1saltoY -= 0.75;
	if (anim1posZ >= 0) velocidadPersonaje = 0;
	if (velocidadPersonaje <= 1 && angleMario < 15) angleMario += 1;

	glPushMatrix();
	glTranslated(0, anim1saltoY, anim1posZ-10);
	glRotated(angleMario, 0, 1, 0);
	mario();
	glPopMatrix();
}

void animTorturga() {

	if (nubeposY > 2) nubeposY -= 0.1*velocidadNube;
	if (nubeposY > 2) nuberotY += 1*velocidadNube;

	nubeposZ = -20;



	glPushMatrix();
	glRotated(nuberotY, 0, 1, 0);
	glTranslated(nubeposX, nubeposY, nubeposZ);
	tortuga();
	glPopMatrix();

}

void animLogoMario() {



	if (logoPosY > -2) logoPosY -= 0.2;


	glPushMatrix();
	glTranslated(6, logoPosY, -15);
	glScaled(0.65, 0.65, 0.65);
	glRotated(-30, 0, 1, 0);
	logoMario();
	glPopMatrix();
}

void animCamera() {
	if (angulo > 3.727) angulo -= 0.006;
	if (camaraY > 16) camaraY -= 0.2;
	if (radio > 37) radio -= 0.2;

	
}

void dibujar() {
	inicializarLuces();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(radio * cos(angulo)+30, camaraY, radio * sin(angulo), 30, centroY, 0, 0, 1, 0);
	glClearColor(255 / 255.0, 255 / 255.0, 255 / 255.0, 1);
	glPushMatrix();

	piso();
	//ejes();

	redcube();
	earth();
	
	animLogoMario();
	
	glPushMatrix();
	glTranslated(0, 0, -5);
	
	//animTorturga();
	animMario1();
	glPopMatrix();

	forest();

	stone_road();
	casa();

	animCamera();

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
	glutInitWindowSize(1920, 1080);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("MarioScene1");
	loadImages();
	glutReshapeFunc(iniciarVentana);
	glutDisplayFunc(dibujar);
	glutSpecialFunc(teclado);
	glutTimerFunc(0, timer, 0);

	glutMainLoop();
	return 0;
}