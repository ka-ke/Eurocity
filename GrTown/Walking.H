#pragma once

// written by Michael   - originally written Fall, 2000
// updated Fall, 2005
// updated Fall, 2006 - smoothness at boundaries, direction preferences
// updated Fall, 2008 - comments added, connection to the centralized utilities

// WARNING: the road system code is meant as an example in terms of what it
// does, not necessarily for code to read and modify. 
// Don't start here! 

//
// new driving behaviors for the new Road System
//
// the thing you want to use here is randomdrive

#include "GrObject.H"
#include "Behavior.H"

// generic base class of all driving behaviors
// keeps track of basic stuff common to all driving behaviors
// this is a base class - don't use it
class Motion : public Behavior
{
public:
	Motion(GrObject* human, unsigned long duration);

	// put the car in the right position
	void setMatrix();
};


// a simple test driving behavior: just do a lane over and over
class Turning : public Motion
{
public:
	Turning(GrObject* human, unsigned long duration);

	virtual void simulateUntil(unsigned long duration);
};


// a more complex driving behavior - randomly drive around
// when you get to a dead end, turn around
// when you get to an intersection, make a random choice
class Walking : public Motion
{
public:
	Walking(GrObject* human, unsigned long duration);

	virtual void simulateUntil(unsigned long duration);
};


