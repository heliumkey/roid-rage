//#include "stdafx.h"
#include "bullet.h"


bullet::bullet(float bx, float by)
{

	x = bx;
	nx = bx;

	y = by;
	ny = by;

	xa = 0;
	ya = 0;
	xv = 0;
	yv = 0;
	lifespan = al_create_timer(1);
	alive = false;
	wpoint = wykobi::make_point(nx, ny);

}

bullet::bullet() {

	x = 0;
	nx = 0;

	y = 0;
	ny = 0;

	xa = 0;
	ya = 0;
	xv = 0;
	yv = 0;
    lifespan = al_create_timer(2);
	alive = false;
	wpoint = wykobi::make_point(nx, ny);
}

void bullet::update(float delta) {

	x = nx;
	y = ny;

	xv = xv + (xa * delta);
	yv = yv + (ya * delta);

	nx = nx + (xv * delta);
	ny = ny + (yv * delta);
	if (al_get_timer_count(lifespan) >= 1) {
		destroy();
		al_stop_timer(lifespan);
		al_set_timer_count(lifespan, 0);

	}
	wpoint = wykobi::make_point(nx, ny);

}

void bullet::destroy() {
	xv = 0;
	yv = 0;
	x = 0;
	nx = 0;
	y = 0;
	ny = 0;
	alive = false;
}

void bullet::draw() {
	//al_draw_circle(nx, ny, 5, white, 5);
	if (alive) {
		al_draw_line(x, y, x + 1, y + 1, white, 1);
	}

	//std::cout << xv << ", " << yv << std::endl;
}


