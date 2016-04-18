#include "GrTown/GrTown_PCH.H"
#include "GrTown/DrawUtils.H"
#include "Utilities/Texture.H"
#include "GrTown/DrawingState.H"
#include "Ufo.H"

int ufoCtr = 0;
float size = 3;

float RandomFloat2(float a, float b) {
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = b - a;
	float r = random * diff;
	return a + r;
}

Ufo::Ufo(char* name, int c) : GrObject(name, c, name)
{
	rideAbove = 10;
	ridable = 1;
	position = RandomFloat2(1, 999);
	height; // not used atm

	// note: we can't actually load the textures now (since we don't have a GL context)
	// so we just say that we don't have textures
	frontTexture = 0;
	sideTexture = 0; // not used atm
}

void Ufo::drawBody(DrawingState* d)
{

}

void Ufo::drawAfter(DrawingState* d)
{
	int tod = d->timeOfDay;
	bool daytime;
	if (tod >= 6 && tod <= 19)
		daytime = true;
	else
		daytime = false;

	if (!daytime) {

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_DST_ALPHA);
		float cone_length = 110;
		float radius = 10;
		float theta, dtheta = pi / 16;
		int c;

		float norm[3];
		float sum;

		glPushMatrix();

		glFrontFace(GL_CW);
		glTranslatef(0, -cone_length, 0);

		glBegin(GL_TRIANGLE_FAN);
		glColor4f(1, 1, 0, .8f);
		glVertex3f(0, cone_length + 10, 0);
		for (c = 0, theta = 0.0; c <= 32; theta += dtheta, c++) {
			float z = sin(theta) * radius;
			float x = cos(theta) * radius;
			glColor4f(1, 1, 0, .2f);

			norm[0] = 0; norm[1] = x; norm[2] = z; sum = norm[0] + norm[1] + norm[2];
			norm[0] /= sum; norm[1] /= sum; norm[2] /= sum;
			glNormal3f(norm[0], norm[1], norm[2]);

			glVertex3f(x, cone_length / 6, z);
		}

		glEnd();


		glPopMatrix();

		glDisable(GL_BLEND);
		glClearColor(1, 1, 1, 1);
	}
}

void Ufo::draw(DrawingState* s)
{
	int tod = s->timeOfDay;
	bool daytime;
	if (tod >= 8 && tod <= 16){
		daytime = true;
		height = 300;
	}
	else {
		daytime = false;
	}

	if (!daytime) {

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
}




