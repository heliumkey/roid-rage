//#include "stdafx.h"
#include "ship.h"
#include <algorithm>


ship::ship(float sx, float sy){

	rotation = 291;
	sizeh = 20;
	sizew = 20;

	centerx = centernx = sx;
	centery = centerny = sy;

	x = nx = centerx;
	y = ny = centery + sizeh / 3;

	x1 = nx1 = centerx + sizew / 2;
	y1 = ny1 = centery - sizeh / 2;

	x2 = nx2 = centerx - sizew / 3;
	y2 = ny2 = centery - sizeh;

	xv = xa = yv = ya = 0;
	rotate(rotation);
	bsize = 100;
	bcount = 0;

	bullets = new bullet[bsize];
    firetimer = al_create_timer(0.3);

}

void ship::draw() {

	//al_draw_circle(x, y, 10, al_map_rgb(255, 255, 255), 5);
	if (thrust) {
		al_draw_filled_triangle(rnx, rny, rnx1, rny1, rnx2, rny2, white);
	}
	else {
		al_draw_triangle(rnx, rny, rnx1, rny1, rnx2, rny2, white, 2);
	}

}

void ship::update(float delta) {

	centerx = centernx;
	centery = centerny;

	x = nx;
	y = ny;

	x1 = nx1;
	y1 = ny1;

	x2 = nx2;
	y2 = ny2;

	//calc velocity
	xv = xv + (xa * delta);
	yv = yv + (ya * delta);

	//calc forward position
	centernx = centernx + (xv * delta);
	centerny = centerny + (yv * delta);

	//calc triangle points
	nx  = centernx;
	ny  = centerny + sizeh / 3;

	//tip
	nx1 = centernx + sizew / 2;
	ny1 = centerny - sizeh / 2;

	nx2 = centernx - sizew / 3;
	ny2 = centerny - sizeh;




	if (rotation >= 360) {
		rotation = 0;
	}
	if (rotation < 0) {
		rotation = 360;
	}
	if (firing) {;
		if (al_get_timer_count(firetimer) >= 1) {
			al_set_timer_count(firetimer, 0);
			fire();
		}

	}
	else if (!firing) {
		al_stop_timer(firetimer);
		al_set_timer_count(firetimer, 0);
	}

	rotate(rotation);
	wtri = wykobi::make_triangle(rnx, rny, rnx1, rny1, rnx2, rny2);

	xa = 0;
	ya = 0;


}
void ship::rotate(float deg) {

	float rad = (deg * ALLEGRO_PI) / 180.0f;
	float cnx = (nx + nx1 + nx2) / 3;
	float cny = (ny + ny1 + ny2) / 3; 
	rnx = (nx - cnx) * std::cos(rad) - (ny - cny) * std::sin(rad) + cnx;
	rny = (ny - cny) * std::cos(rad) + (nx - cnx) * std::sin(rad) + cny;

	rnx1 = (nx1 - centernx) * std::cos(rad) - (ny1 - cny) * std::sin(rad) + cnx;
	rny1 = (ny1 - cny) * std::cos(rad) + (nx1 - cnx) * std::sin(rad) + cny;

	rnx2 = (nx2 - cnx) * std::cos(rad) - (ny2 - cny) * std::sin(rad) + cnx;
	rny2 = (ny2 - cny) * std::cos(rad) + (nx2 - cnx) * std::sin(rad) + cny;

}

void ship::rotateLeft(float speed) {
	rotation -= speed;

}

void ship::rotateRight(float speed) {
	rotation += speed;
}

void ship::fire() {

	if (bcount < bsize - 1) {
		bcount++;
	}
	else {
		bcount = 0;
	}

	bullets[bcount].nx = rnx1;
	bullets[bcount].ny = rny1;
    bullets[bcount].xv = (bullets[bcount].nx - (rnx + rnx1 + rnx2) / 3) * 5000;
    bullets[bcount].yv = (bullets[bcount].ny - (rny + rny1 + rny2) / 3) * 5000;
	bullets[bcount].alive = true;
	al_start_timer(bullets[bcount].lifespan);


}

void ship::printpos() {
	std::cout << "ship position: " << x << ", " << y << std::endl;
	std::cout << "ship position next: " << nx << ", " << ny << std::endl;
	std::cout << "ship v: " << xv << ", " << yv << std::endl;
	std::cout << "ship a: " << xa << ", " << ya << std::endl;
	std::cout << "ship n: " << nx << ", " << ny << std::endl;
}




