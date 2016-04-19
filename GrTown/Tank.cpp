#include "GrTown/GrTown_PCH.H"
#include "GrTown/DrawUtils.H"
#include "Utilities/Texture.H"
#include "GrTown/DrawingState.H"
#include "Tank.H"

int tankCtr = 0;
Tank::Tank(char* name, int c) : GrObject(name, c, name)
{
	rideAbove = 10;
	ridable = 1;
}

void Tank::drawBody(DrawingState* d)
{

}

void Tank::drawAfter(DrawingState* s)
{
}

void Tank::draw(DrawingState* s)
{
	GLUquadric *obj = gluNewQuadric();

	glPushMatrix();
	glTranslatef(4, 1, 0);
	glRotatef(180, 0, 1, 0);
	glScalef(2, 2, 2);

	// Tank cabin
	glColor3f(0.4, 0.7, 0.4);

	glBegin(GL_TRIANGLE_STRIP);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 5);
	glVertex3f(4, 0, 5);
	glVertex3f(4, 0, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 5);
	glVertex3f(0, 3, 4);
	glVertex3f(0, 3, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 3, 0);
	glVertex3f(4, 3, 0);
	glVertex3f(4, 0, 0);
	glVertex3f(0, 0, 0);
	glEnd();

	glBegin(GL_TRIANGLE_STRIP);
	glVertex3f(4, 3, 4);
	glVertex3f(4, 3, 0);
	glVertex3f(0, 3, 0);
	glVertex3f(0, 3, 4);
	glVertex3f(4, 3, 4);
	glVertex3f(0, 3, 4);
	glVertex3f(0, 0, 5);
	glVertex3f(4, 0, 5);
	glVertex3f(4, 3, 4);
	glVertex3f(4, 3, 0);
	glVertex3f(4, 0, 0);
	glVertex3f(4, 0, 5);
	glVertex3f(4, 3, 4);
	glEnd();

	// Tank "wheels" (apply texture)
	float wd = 0;
	glColor3f(0.4, 0.5, 0.4);

	glBegin(GL_TRIANGLE_STRIP);
	glVertex3f(wd, -1, -1);
	glVertex3f(wd - 1, -1, -1);
	glVertex3f(wd - 1, -1, 6);
	glVertex3f(wd, -1, 6);
	glVertex3f(wd, -1, -1);
	glVertex3f(wd, 1, -1.5);
	glVertex3f(wd - 1, 1, -1.5);
	glVertex3f(wd - 1, -1, -1);
	glVertex3f(wd, -1, -1);
	glVertex3f(wd, 1, -1.5);
	glVertex3f(wd, 1, 6.5);
	glVertex3f(wd, -1, 6);

	glVertex3f(wd, -1, -1);
	glEnd();

	glBegin(GL_TRIANGLE_STRIP);
	glVertex3f(wd - 1, 1, 6.5);
	glVertex3f(wd, 1, 6.5);
	glVertex3f(wd, -1, 6);
	glVertex3f(wd - 1, -1, 6);
	glVertex3f(wd - 1, 1, 6.5);
	glVertex3f(wd, 1, 6.5);
	glVertex3f(wd, 1, -1.5);
	glVertex3f(wd - 1, 1, -1.5);
	glVertex3f(wd - 1, 1, 6.5);
	glVertex3f(wd - 1, -1, 6);
	glVertex3f(wd - 1, -1, -1);
	glVertex3f(wd - 1, 1, -1.5);

	glVertex3f(wd - 1, 1, 6.5);
	glEnd();

	wd = 5;

	glBegin(GL_TRIANGLE_STRIP);
	glVertex3f(wd - 1, 1, 6.5);
	glVertex3f(wd, 1, 6.5);
	glVertex3f(wd, -1, 6);
	glVertex3f(wd - 1, -1, 6);
	glVertex3f(wd - 1, 1, 6.5);
	glVertex3f(wd, 1, 6.5);
	glVertex3f(wd, 1, -1.5);
	glVertex3f(wd - 1, 1, -1.5);
	glVertex3f(wd - 1, 1, 6.5);
	glVertex3f(wd - 1, -1, 6);
	glVertex3f(wd - 1, -1, -1);
	glVertex3f(wd - 1, 1, -1.5);
	glVertex3f(wd - 1, 1, 6.5);
	glEnd();

	glBegin(GL_TRIANGLE_STRIP);
	glVertex3f(wd, -1, -1);
	glVertex3f(wd - 1, -1, -1);
	glVertex3f(wd - 1, -1, 6);
	glVertex3f(wd, -1, 6);
	glVertex3f(wd, -1, -1);
	glVertex3f(wd, 1, -1.5);
	glVertex3f(wd - 1, 1, -1.5);
	glVertex3f(wd - 1, -1, -1);
	glVertex3f(wd, -1, -1);


	glVertex3f(wd, 1, -1.5);
	glVertex3f(wd, 1, 6.5);
	glVertex3f(wd, -1, 6);


	glVertex3f(wd, -1, -1);
	glEnd();

	// Tank cannon
	glColor3f(0.4, 0.7, 0.4);

	glTranslatef(2, 2, 4);
	gluCylinder(obj, 0.5, 0.5, 3, 50, 50);
	glTranslatef(0, 0, 3);
	glutSolidCube(1);

	glPopMatrix();
}




