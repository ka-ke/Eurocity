// Human.cpp - implementation of our humans

#include "GrTown_PCH.H"
#include "DrawUtils.H"
#include "Utilities/Texture.H"
#include "DrawingState.H"
#include "Humans.H"
#include <GL\glut.h>

/////////////////////////////////////////////////////
// car colors have names too
struct Character{
	char* name;
	char* faceTex;
	char* bodyTexTop;
	char* bodyTexMid; 
	char* bodyTexLow;
};
Character characters[] = {
	{ "Runner1", "MaleFace2.png", "Run1Top.bmp", "Run1Mid.bmp", "Run1Low.bmp"},
	{ "Runner2", "FemaleFace3.bmp", "Run1Top.bmp", "Run1Mid.bmp", "Run1Low.bmp" },
	{ "Zombie", "ZombieFace2.bmp", "Run1Top.bmp", "Run1Mid.bmp", "Run1Low.bmp" }
};
const int nCharacters = 3;

///////////////////////////////////////////////////////
// the generic dude...
int HumanCtr = 0;

//Colors
GLfloat gaWhite[] = { 1, 1, 1, 1 };

GLfloat gaGreen[] = { 0.0, 0.8, 0.0, 1 };
GLfloat gaBlue[] = { 0.0, 0.0, 0.8, 1 };
GLfloat gaRed[] = { 0.8, 0.0, 0.0, 1 };

GLfloat gaGray[] = { 0.8, 0.85, 0.8, 1 };

GLfloat gaYellow[] = { 0.5, 0.8, 0.0, 1 };

GLfloat gaDarkBrown[] = { 0.5, 0.35, 0.3, 1 };

GLfloat gaBrown[] = { 0.8, 0.55, 0.5, 1 };

#pragma region Person

void createHat(){
	GLUquadricObj *obj = gluNewQuadric();

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, gaRed);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, gaRed);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, gaWhite);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 20.0);

	glPushMatrix();
	glTranslatef(0, 0, 0.3);
	gluCylinder(obj, 1.7, 0, 3, 32, 1);
	gluDisk(obj, 1.7, 2.4, 32, 1);
	glPopMatrix();
}

void createHead(){
	GLUquadricObj *obj = gluNewQuadric();
	gluQuadricTexture(obj, GL_TRUE);

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, gaBrown);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, gaBrown);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, gaYellow);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 20.0);

	glPushMatrix();
	glTranslatef(0, 0, 0.5);
	gluCylinder(obj, 1, 1, 1.5, 32, 1);
	glTranslatef(0, -0.5, 2);
	glRotatef(-45, 1, 0, 0);
	glScalef(1, 1, 1.4);
	//createHat();
	glRotatef(45, 1, 0, 0);

	gluSphere(obj, 1.5, 32, 32);

	glPopMatrix();
}

void createLArm(float position){
	GLUquadricObj *obj = gluNewQuadric();

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, gaBrown);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, gaBrown);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, gaYellow);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 20.0);

	glPushMatrix();
	glRotatef((position * 60), 1, 0, 0);
	glRotatef(20, 0, 1, 0);
	glRotatef(-180, 1, 0, 0);
	gluCylinder(obj, 0.9, 0.7, 4, 32, 1);
	glTranslatef(0, -0.05, 4);
	gluSphere(obj, 0.8, 32, 32);
	glTranslatef(0, 0.05, 0);
	glRotatef(-80, 1, 0, 0);
	gluCylinder(obj, 0.7, 0.5, 4, 32, 1);
	glTranslatef(0, 0, 4);
	glScalef(1, 1, 1.2);
	gluSphere(obj, 0.8, 32, 32);
	glTranslatef(0.3, 0.6, 0);
	gluSphere(obj, 0.4, 32, 32);
	glPopMatrix();
}

void createRArm(float position){
	GLUquadricObj *obj = gluNewQuadric();

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, gaBrown);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, gaBrown);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, gaYellow);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 20.0);


	glPushMatrix();
	glRotatef(-(position * 60), 1, 0, 0);
	glRotatef(-20, 0, 1, 0);
	glRotatef(-180, 1, 0, 0);
	gluCylinder(obj, 0.9, 0.7, 4, 32, 1);
	glTranslatef(0, -0.05, 4);
	gluSphere(obj, 0.8, 32, 32);
	glTranslatef(0, 0.05, 0);
	glRotatef(-80, 1, 0, 0);
	gluCylinder(obj, 0.7, 0.5, 4, 32, 1);
	glTranslatef(0, 0, 4);
	glScalef(1, 1, 1.2);
	gluSphere(obj, 0.8, 32, 32);
	glTranslatef(-0.3, 0.6, 0);
	gluSphere(obj, 0.4, 32, 32);
	glPopMatrix();
}

void createCorpul(float position, Character c){
	GLUquadricObj *obj = gluNewQuadric();
	gluQuadricTexture(obj, GL_TRUE);

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, gaWhite);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, gaWhite);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, gaWhite);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 20.0);


	fetchTexture(c.bodyTexLow);
	glPushMatrix();
	glScalef(0.8, 0.6, 1);
	gluCylinder(obj, 2.5, 4, 3, 32, 1);

	fetchTexture(c.bodyTexMid);
	glRotated(-180, 1, 0, 0);
	gluCylinder(obj, 2.5, 4, 5, 32, 1);

	glTranslatef(0, 0, 5);

	fetchTexture(c.bodyTexTop);
	gluCylinder(obj, 4, 1, 1, 32, 1);

	fetchTexture(c.faceTex);
	glScalef(1.25, 1.666, 1);
	createHead();

	glBindTexture(GL_TEXTURE_2D, 0);
	glTranslatef(-2.3, 0, -0.8);
	gluSphere(obj, 1, 32, 32);
	createLArm(position);

	glTranslatef(4.6, 0, 0);
	gluSphere(obj, 1, 32, 32);
	createRArm(position);

	glPopMatrix();
}

void createFoot(){
	GLUquadricObj *obj = gluNewQuadric();

	glPushMatrix();

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, gaGray);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, gaGray);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, gaYellow);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 20.0);

	gluSphere(obj, 0.7, 16, 16);
	glTranslated(0, -0.6, 0.7);
	glScalef(1, 1, 2);
	glRotated(-90, 1, 0, 0);

	gluDisk(obj, 0, 1, 32, 1);
	gluCylinder(obj, 1, 0.9, 0.3, 32, 1);

	glTranslated(0, 0, 0.3);

	gluDisk(obj, 0, 0.9, 32, 1);
	glPopMatrix();
}

void createLLeg(float position){
	GLUquadricObj *obj = gluNewQuadric();

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, gaBrown);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, gaBrown);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, gaYellow);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 20.0);

	glPushMatrix();
	glRotatef((position * 60), 1, 0, 0);
	gluSphere(obj, 1.2, 32, 32);
	gluCylinder(obj, 1.2, 0.9, 3.8, 32, 1);
	glTranslatef(0, 0.1, 3.8);
	gluSphere(obj, 1, 32, 32);
	glTranslatef(0, -0.1, 0);
	glRotatef((abs(position) * 60), 1, 0, 0);
	gluCylinder(obj, 0.9, 0.6, 3.6, 32, 1);
	glTranslatef(0, 0, 3.6);
	glRotatef(-90, 1, 0, 0);
	createFoot();
	glPopMatrix();
}

void createRLeg(float position){
	GLUquadricObj *obj = gluNewQuadric();

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, gaBrown);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, gaBrown);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, gaYellow);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 20.0);

	glPushMatrix();
	glRotatef(-(position * 60), 1, 0, 0);
	gluSphere(obj, 1.2, 32, 32);
	gluCylinder(obj, 1.2, 0.9, 3.8, 32, 1);
	glTranslatef(0, 0.1, 3.8);
	gluSphere(obj, 1, 32, 32);
	glTranslatef(0, -0.1, 0);
	glRotatef((abs(position) * 60), 1, 0, 0);
	gluCylinder(obj, 0.9, 0.6, 3.6, 32, 1);
	glTranslatef(0, 0, 3.6);
	glRotatef(-90, 1, 0, 0);
	createFoot();
	glPopMatrix();
}
#pragma endregion

Human::Human(char* name, int c, bool z) : GrObject(name, HumanCtr, characters[c%nCharacters].name)
{
	character = c%nCharacters;
	motionPosition = 0;
	motionPositionInv = false;
	zombie = z;
}

void Human::draw(DrawingState* d)
{
	int tod = d->timeOfDay;

	if (tod >= 6 && tod <= 19){
		if (character != 2){
			glPushMatrix();
			glDisable(GL_COLOR_MATERIAL);
			glRotatef(180, 0, 1, 0);
			glScalef(0.7, 0.7, 0.7);
			glTranslatef(0, 10, 0);
			glRotatef(90, 1, 0, 0);
			createCorpul(motionPosition, characters[character]);
			glTranslatef(0, 0, 2);
			glTranslatef(1.5, 0, 0);
			createLLeg(motionPosition);
			glTranslatef(-3, 0, 0);
			createRLeg(motionPosition);
			glEnable(GL_COLOR_MATERIAL);
			glPopMatrix();
		}
	}
	else{
		if (zombie == true){
			character = 2;
		}
		glPushMatrix();
		glDisable(GL_COLOR_MATERIAL);
		glRotatef(180, 0, 1, 0);
		glScalef(0.7, 0.7, 0.7);
		glTranslatef(0, 10, 0);
		glRotatef(90, 1, 0, 0);
		createCorpul(motionPosition, characters[character]);
		glTranslatef(0, 0, 2);
		glTranslatef(1.5, 0, 0);
		createLLeg(motionPosition);
		glTranslatef(-3, 0, 0);
		createRLeg(motionPosition);
		glEnable(GL_COLOR_MATERIAL);
		glPopMatrix();
	}
}

void Human::drawAfter(DrawingState* s)
{
}


