#include "GrTown/GrTown_PCH.H"
#include "GrTown/DrawUtils.H"
#include "Utilities/Texture.H"
#include "GrTown/DrawingState.H"
#include "Ufo.H"

int ufoCtr = 0;
float size = 3;
Ufo::Ufo(char* name, int c) : GrObject(name, c, name)
{
	rideAbove = 10;
	ridable = 1;

	// note: we can't actually load the textures now (since we don't have a GL context)
	// so we just say that we don't have textures
	frontTexture = 0;
	sideTexture = 0;
}

void Ufo::drawBody(DrawingState* d)
{

}

void Ufo::drawAfter(DrawingState* s)
{
	}

void Ufo::draw(DrawingState* s)
{
	GLUquadricObj *obj = gluNewQuadric();

	glPushMatrix();
	glColor3f(0.5, 0.5, 0.5);
	glRotatef(90, 1, 0, 0);
	glutSolidTorus(size, 3 * size, 3, 50);

	glPushMatrix();
	glRotatef(180, 1, 0, 0);
	glutSolidCone(1, size * 4, 10, 10);
	glTranslatef(0, 0, size * 4);
	glutSolidSphere(size / 8, 50, 50);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, -size*1.55);
	gluCylinder(obj, size * 2, size * 3, size, 50, 50);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, size / 2);
	gluCylinder(obj, size * 3, size*1.5, size, 50, 50);
	glPopMatrix();

	glColor3f(0.8, 0.8, 0);
	glTranslatef(0, 0, -size*0.5);
	glutSolidSphere(size*2.5, 50, 50);

	glPopMatrix();
}




