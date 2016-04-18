// Fountain.cpp - implementation of our Fountain

#include "GrTown_PCH.H"
#include "DrawUtils.H"
#include "Utilities/Texture.H"
#include "DrawingState.H"
#include "Fountain.H"
#include <GL\glut.h>

Fountain::Fountain(char* name, double s) : GrObject(name)
{
	size = s;
	int i;
	for (i = 0; i < 1500; i++){
		double x1 = rand() % 40;
		double x2 = rand() % 100;
		double x = x1 + x2 * 0.001;
		double y = (-0.25 * pow(x,2)) + (10 * x);
		double angle = rand() % 359;
		particles[i][1] = x;
		particles[i][2] = y;
		particles[i][3] = angle;
	}
}

void Fountain::draw(DrawingState* d)
{
	glPushMatrix;
	drawBassin(size);
}

// draw headlights at night
void Fountain::drawAfter(DrawingState* s)
{
	drawWaterInBassin(size);
	drawWaterFountain();
}

void Fountain::drawBassin(double size)
{
	GLUquadricObj *obj = gluNewQuadric();
	glColor4f(0.3, 0.3, 0.3, 1);

	glPushMatrix();
	glRotatef(-90, 1, 0, 0);
	gluDisk(obj, 0, size + 8, 64, 1);
	gluCylinder(obj, size, size, 6, 64, 1);
	gluCylinder(obj, size+8, size+8, 6, 64, 1);
	glTranslatef(0, 0, 6);
	glutSolidTorus(4, size+4, 16, 64);
	glPopMatrix();
}

void Fountain::drawWaterInBassin(double size){
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_DST_ALPHA);

	GLUquadricObj *obj = gluNewQuadric();
	glColor4f(0.439216, 0.858824, 0.576471, 0.2);

	glPushMatrix();
	glRotatef(-90, 1, 0, 0);
	glTranslatef(0, 0, 6);
	gluDisk(obj, 0, size + 8, 64, 1);
	glPopMatrix();

	glDisable(GL_BLEND);
}

void Fountain::drawWaterFountain(){
	int i;
	for (i = 0; i < 1500; i++){
		glPushMatrix();
		glRotated(particles[i][3], 0, 1, 0);
		glTranslated(particles[i][1], particles[i][2], 0);
		drawParticle();
		glPopMatrix();
	}
}

void Fountain::drawParticle(){
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_DST_ALPHA);

	glColor3f(0.5,0.8,1);
	billboardCheatSphericalBegin();
	fetchTexture("particle1.png");
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-1.0f, -1.0f, 0.0f); // The bottom left corner  
	glTexCoord2f(0, 1.0);
	glVertex3f(-1.0f, 1.0f, 0.0f); // The top left corner 
	glTexCoord2f(1.0, 1.0);
	glVertex3f(1.0f, 1.0f, 0.0f); // The top right corner
	glTexCoord2f(1.0, 0);
	glVertex3f(1.0f, -1.0f, 0.0f); // The bottom right corner
	glEnd();
	glBindTexture(GL_TEXTURE_2D, 0);
	billboardEnd();

	glDisable(GL_BLEND);
}



