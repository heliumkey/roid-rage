
#include "asteroid.h"

#include <iostream>

asteroid::asteroid(float ax, float ay, float axv, float ayv)
{
	x = ax;
	y = ay;

	nx = ax;
	ny = ay;

	xv = axv;
	yv = ayv;

	xa = 0;
	ya = 0;
	alive = false;
	radius = 25;
	collisionhalt = 0;
	mass = 10;

}

asteroid::asteroid() {

	x = 0;
	y = 0;
	nx = 0;
	ny = 0;
	xv = 0;
	yv = 0;
	xa = 0;
	ya = 0;
	alive = false;
	radius = 25;
	collisionhalt = 0;
	mass = 10;
}
void asteroid::update(float delta) {

	x = nx;
	y = ny;

	xv = xv + (xa * delta);
	yv = yv + (ya * delta);

	nx = nx + (xv * delta);
	ny = ny + (yv * delta);

	if (collisionhalt != 0) {
		collisionhalt--;
	}

	wcirc = wykobi::make_circle(x, y, radius);

}

bool asteroid::contains(float cx, float cy) {


	if ((cx > nx) && (cx < nx + 40) && (cy > ny) && (cy < ny + 40)) {
		return true;

	}
	else {
		return false;
	}

}

void asteroid::destroy() {
	alive = false;
}

void asteroid::randomposition() {
	bool xvdir = rand() % 2;
	bool yvdir = rand() % 2;
	bool xdir = rand() % 2;
	bool ydir = rand() % 2;

	if (xvdir) {
		xv = (float)(((rand() % 10 + 1) * 100) * -1);
	}
	else if (!xvdir) {
		xv = (float)((rand() % 10 + 1) * 100);
	}
	if (yvdir) {
		yv = (float)(((rand() % 10 + 1)) * 100) * -1;
	}
	else if (!yvdir) {
		yv = (float)(((rand() % 10 + 1)) * 100);

	}
	if (xdir) {
		nx = (float)(rand() % 800);
		ny = (radius * 2) * -1;
	}
	else {
		ny = (float)(rand() % 600);
		nx = (radius * 2) * -1;
	}
	alive = true;




}

void asteroid::draw() {
	if (alive) {

		al_draw_circle(x, y, radius, white, 1);
	}

}


