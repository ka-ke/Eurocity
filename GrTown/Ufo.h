#pragma once
// these are example objects - very simple - hopefully yours will be nicer!

// Cars - cars are actually just static, rigid objects
// A driving behavior is added to move them around
//
#include "GrTown/GrObject.H"
#include <GL/glut.h>

// keep a pointer to the texture, that way we only look it up the first time
class Texture;

class Ufo : public GrObject {
public:

	Ufo(char* type, int color);
	float position;
	float height;
	float size;

	// this draw the whole car - subclasses just redefine "body"
	virtual void draw(DrawingState*);
	virtual void drawAfter(DrawingState*);
	virtual void drawBody(DrawingState*);
};

class Saucer : public Ufo {
public:
	Saucer();
};


