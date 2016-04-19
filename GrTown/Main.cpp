/// GraphicsTown2006
// written by Michael   - originally written Fall, 2000
//
// updated Fall 2006 - more testing code
// updated Fall 2008 - switched some internal stuff (no more linked lists)

#include "GrTown_PCH.H"
#include "GraphicsTownUI.H"
#include "FlyCamera.H"
#include "GrWorld.H"
#include "DrawUtils.H"
#include "Examples/Objects.H"
#include "Examples/SimpleBehaviors.H"
#include "Examples/Cars.H"
#include "Humans.h"
#include "Fountain.H"
#include "Ufo.h"
#include "Tank.h"

// for setting up shader paths and textures
#include "Utilities/ShaderTools.H"
#include "Utilities/Texture.H"


// Example code (objects and behaviors)
#include "Examples/Suburbs.H"

#include "Roads/Roads.H"
#include "Roads/Drive.H"

// define this to get 2 cars that always turn
// #define TESTCARS

float RandomFloat3(float a, float b) {
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = b - a;
	float r = random * diff;
	return a + r;
}

const int numCars = 1;
const int nGrids = 5;

int main(int /*argc*/, char** /*argv*/)
{ 

  // put in some texture paths - look all over the place
	texturePaths.push_back(".");
	texturePaths.push_back("..");
	texturePaths.push_back("Textures/signs");
	texturePaths.push_back("../Textures/signs");
	texturePaths.push_back("Textures/Textures");
	texturePaths.push_back("../Textures/Textures");
	texturePaths.push_back("Textures/Objects");
	texturePaths.push_back("../Textures/Objects");

	shaderPaths.push_back("Shaders");
	shaderPaths.push_back("../Shaders");


  // add some more stuff
  GrObject* o1 = new Church;
  o1->interesting = true;
  o1->laX = 0; o1->laY = 0; o1->laZ = 0;
  o1->lfX = -50; o1->lfY = 100; o1->lfZ = 300;
  add(o1,-100,0,100,pi/2.f);

  GrObject* o2 = new FerryWheel(10);
  o2->interesting = true;
  o2->laX = 0; o2->laY = 65; o2->laZ = 20;
  o2->lfX = -70; o2->lfY = 10; o2->lfZ = 160;
  add(o2, 1500, 0, 690, pi / 3.f);
  new RunFerryWheel(o2);

  GrObject* o3 = new Fountain("myFountain",120);
  o3->interesting = true;
  o3->laX = 0; o3->laY = 0; o3->laZ = 0;
  o3->lfX = -100; o3->lfY = 100; o3->lfZ = 300;
  add(o3, 1100, 0, 690, pi / 3.f);
  new Spray(o3);

  // *****************************************************************
  //  Make your town here

  ////////////////////////////////////////////////////////////////////////
  // now to make a real town!
  int r,c;
  // make a 5x5 grid of town blocks - 5 houses per
  for( r=0; r<6; r++) {
	  for( c=0; c<6; c++) {
		  if (!(((r == 2) || (r == 3)) && ((c == 2) || (c == 3)))){
			  add(new SimpleSubdivision(4), static_cast<float>(r * 430), 0, static_cast<float>(c * 230));
			  add(new StraightRoad(static_cast<float>(r * 430), static_cast<float>(c * 230), static_cast<float>(r * 430 + 400), static_cast<float>(c * 230)));
		  }
		  if(c == 2)add(new StraightRoad(static_cast<float>(r * 430), static_cast<float>(c * 230), static_cast<float>(r * 430 + 400), static_cast<float>(c * 230)));
	  }
	  add(new StraightRoad(static_cast<float>(r * 430), static_cast<float>(c * 230), static_cast<float>(r * 430 + 400), static_cast<float>(c * 230)));
  }
  //// make cross streets
  for(int r=0; r<=6; r++) {
	  for(c=0; c<6; c++) {
		  if(!((r == 3) && ((c == 2) || (c == 3))))add(new StraightRoad(static_cast<float>(r * 430 - 15), static_cast<float>(c * 230 + 15), static_cast<float>(r * 430 - 15), static_cast<float>(c * 230 + 215)));
	  }
  }

  // make intersections
  // make an intersection intersesting so we can look at it
  for(int r=0; r<7; r++) {
	  for(c=0; c<7; c++) {
		  if(!((r == 3) && (c == 3))){
			  GrObject* g = new Intersection(static_cast<float>(r * 430 - 15), static_cast<float>(c * 230));
			  if ((r == 1) && (c == 4)) {
				  g->interesting = 1;
				  g->name = "Intersection(1,4)";
				  g->laX = static_cast<float>(r * 430 - 15);    g->laY = 0;    g->laZ = static_cast<float>(c * 230);
				  g->lfX = static_cast<float>(r * 430 + 25);   g->lfY = 100;   g->lfZ = static_cast<float>(c * 230 + 150);
			  }
			  add(g);
		  }
	  }
  }

#ifndef TESTCARS
  // add some cars
  for(int r=0; r<50; r++) {
	GrObject* c;
	switch (rand() % 4) {
	case 0: c = new Van(rand()); break;
	case 1: c = new SUV(rand()); break;
	case 2: c = new HatchBack(rand()); break;
	case 3: c = new Tank("tank", rand()); break;
	}
	add(c);
    new RandomDrive(c,theRoads[rand() % theRoads.size()],.2f,rand() % 2);
  }
#endif

#ifdef TESTCARS
  // two cars - one always turns right, one always turns left
  Car* c1 = new HatchBack(1);
  Car* c2 = new HatchBack(2);
	add(c1);
	add(c2);
  new RandomDrive(c1,theRoads[7],.5,0,-1);
  new RandomDrive(c2,theRoads[8],.5,0,1);

#endif

// ========== TODO1: ===================
// The following code added a round race track, 
//  you're required to replace it with an elliptical race track and put two cars running on it.


	// a race track
    Road* t = new RoundRoad(1100,690,180);
	add(t);
	t->name = "Track";
	t->interesting = true;
	t->laX = 1100; t->laY = 0;   t->laZ = 690;
	t->lfX = 600; t->lfY = 200; t->lfZ = 450;
	// make joggers go around the track

	Human* h = new Human("Daniel", 0, true);
	add(h);
	new Walking(h);
	Drive* d = new SimpleDrive(h, t, 0, 0);
	d->speed *= 0.1;
	h = new Human("Diana",1, false);
	add(h);
	new Walking(h);
	d = new SimpleDrive(h,t,0,1);
	d->speed *= 0.2;

	// make ufo that patrols over the city
		Ufo* ufo1;
		ufo1 = new Ufo("ufo", 1);
		add(ufo1, ufo1->position, 500, ufo1->position);
		new RandomFly(ufo1);
		new Descend(ufo1);

	// make an ufo that captures people every night
	Ufo* ufo2;
	ufo2 = new Ufo("ufo", 101);
	add(ufo2, 50, 100, 70);
	new Descend(ufo2);
	new Spin(ufo2);

	h = new Human("Unlucky", 2, true);
	add(h, 50, 0, 70);
	new Walking(h);
	new Ascend(h);
	d->speed *= 0.1;

	// big and scary mothership
	Ufo* ufoBig;
	ufoBig = new Ufo("ufo", 1000);
	ufoBig->size = 80;
	add(ufoBig, 1100, 2000, 690);
	new Descend(ufoBig);

	// and more zombies
	for (int zN = 0; zN < 25; zN++){
		Human* zombie;
		zombie = new Human("zombie", 0, true);
		add(zombie, RandomFloat3(-10, 1500), 0, RandomFloat3(-10, 1500));
	}

  // *****************************************************************
  // now make a UI
  FlyCamera* fc = new FlyCamera;
  Map* m = new Map;

  add(fc);
  add(m);

  GraphicsTownUI grTown;
  grTown.make_window();
  grTown.townView->defaultCamera = fc;
  grTown.window->show();

  Fl::run();
  return 1;
}

