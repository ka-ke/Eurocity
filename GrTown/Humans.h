#pragma once
// these are example objects - very simple - hopefully yours will be nicer!

#include "GrObject.H"
#include <GL\glut.h>

// keep a pointer to the texture, that way we only look it up the first time
class Texture;

class Human : public GrObject {
public:
	Human(char* name, int c, bool z);

	int character;
	float motionPosition;
	bool motionPositionInv;
	bool zombie;

	virtual void draw(DrawingState*);
	virtual void drawAfter(DrawingState*);
};



