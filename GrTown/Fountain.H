#pragma once

#include "GrObject.H"
#include <GL\glut.h>

class Texture;

class Fountain : public GrObject {
public:
	Fountain(char* name, double size);
	
	double size;
	double particles[1500][6];

	virtual void draw(DrawingState*);
	virtual void drawAfter(DrawingState*);

private: 
	void drawBassin(double);
	void drawWaterInBassin(double, DrawingState*);
	void drawWaterFountain(DrawingState*);
	void drawParticle(DrawingState*);
};



