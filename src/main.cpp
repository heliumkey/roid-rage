//#include "stdafx.h"
#include "ship.h"
#include <string>
#include <ctime>


//todo: move variables around in a more sane way
//eliminate superfluous loops
//increase asteroid buffer outside of screen, move randomposition to this buffer so that asteroids slide in smoothly
//ship will still utilize screen boundary, asteroid boundary will be size of asteroid
//clean up main

int main()
{
	al_init();
    al_init_font_addon();
	al_init_primitives_addon();

    if(!al_is_keyboard_installed()){
        al_install_keyboard();
    }

	
	ALLEGRO_EVENT_QUEUE* ev_queue = al_create_event_queue();
	ALLEGRO_TIMER* drawtimer;
	ALLEGRO_TIMER* ptimer;

	//init delta time
	float dt = al_get_time();
	float fpsdt = 0;
	ALLEGRO_BITMAP * icon = al_create_bitmap(32, 32);

	ALLEGRO_DISPLAY* display = al_create_display(800, 600);

	al_set_target_bitmap(icon);
	al_draw_triangle(16, 8, 0, 30, 32, 30, black, 2);

	al_set_target_bitmap(al_get_backbuffer(display));
	al_set_display_icon(display, icon);
	ALLEGRO_FONT* font = al_create_builtin_font();
	ship pship = ship(100, 100);

	asteroid *asteroids;

	int score = 0;

	bclear;
	float maxx = 0;
	float maxy = 0;
    float fps = 120;
	float fpscounter;
	drawtimer = al_create_timer(1.0 / fps);
    ptimer = al_create_timer(1.0 / 240);

	//register event sources
	al_register_event_source(ev_queue, al_get_display_event_source(display));
	al_register_event_source(ev_queue, al_get_keyboard_event_source());
	al_register_event_source(ev_queue, al_get_timer_event_source(drawtimer));
	al_register_event_source(ev_queue, al_get_timer_event_source(ptimer));

	//seed rng with current system time
	std::time_t time = std::time(nullptr);
	srand(time);

	//initial number of asteroids - fix this
    int asize = 15;
	int initialcount = (rand() % 5) + 5;
	asteroids = new asteroid[asize];
	//populate initial asteroids
	for (int l = 0; l < initialcount; l++) {
		asteroids[l] = asteroid();
		asteroids[l].randomposition();
		asteroids[l].update(al_get_time() - dt);
		asteroids[l].alive = true;
	}
	for (int m = initialcount; m < asize; m++) {
		asteroids[m] = asteroid();
	}
	

	//move this shit
	bool forward = false;
	bool left = false;
	bool right = false;

	bool exit = false;
	bool debugflag = false;
	//std::ofstream file;
	//file.open("bulletcoords.txt");
	al_start_timer(drawtimer);
	al_start_timer(ptimer);
	while (!exit) {
		//std::time_t time = std::time(nullptr);
		std::vector<wykobi::rectangle<float>> list;
		ALLEGRO_EVENT event;
		al_wait_for_event(ev_queue, &event);

		dt = al_get_time();
		maxx = al_get_display_width(display) + 5;
		maxy = al_get_display_height(display) + 5;

		std::string posline = "Position: X: ";
		posline.append(std::to_string(pship.x));
		posline.append(" Y: ");
		posline.append(std::to_string(pship.y));

		std::string accelline = "Acceleration: X: ";
		accelline.append(std::to_string(pship.xa));
		accelline.append(" Y: ");
		accelline.append(std::to_string(pship.ya));


		std::string velline = "Velocity: X: ";
		velline.append(std::to_string(pship.xv));
		velline.append(" Y: ");
		velline.append(std::to_string(pship.yv));

		std::string dirline = "Rotation: ";
		dirline.append(std::to_string(pship.rotation));

		std::string fpsline = "FPS: ";
		//check for display close button/signal
		if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			exit = true;
			break;
		}
		//physics loop
		if (event.type == ALLEGRO_EVENT_TIMER && event.timer.source == ptimer) {

			//entity updates
			pship.update(al_get_time() - dt);

			for (int i = 0; i < pship.bsize; i++) {
				pship.bullets[i].update(al_get_time() - dt);
			}
			for (int k = 0; k < asize; k++) {
				asteroids[k].update(al_get_time() - dt);
			}
			//new asteroid generation


			//check for and remove dead asteroids




			//move these variables to entities
			if (forward) {
				pship.xa = (pship.rnx1 - ((pship.rnx + pship.rnx1 + pship.rnx2) / 3)) * 500000;
				pship.ya = (pship.rny1 - ((pship.rny + pship.rny1 + pship.rny2) / 3)) * 500000;

				pship.thrust = true;
			}
			if (left) {
				pship.rotateLeft(1.5);
			}
			if (right) {
				pship.rotateRight(1.5);
			}
			//ship wrapping
			if (pship.centernx >= maxx) {
				pship.centernx = 0;

			}
			if (pship.centernx <= -5) {
				pship.centernx = al_get_display_width(display) + 3;

			}
			if ((pship.centerny >= maxy)) {
				pship.centerny = 0;

			}
			if (pship.centerny <= -5) {
				pship.centerny = al_get_display_height(display);
			}

			//bullet iterator
			for (int j = 0; j < pship.bsize; j++) {

				//bullet wrapping
				if (pship.bullets[j].nx >= al_get_display_width(display)) {
					pship.bullets[j].nx = 1;

				}
				if (pship.bullets[j].nx <= 0) {
					pship.bullets[j].nx = al_get_display_width(display) - 1;

				}
				if ((pship.bullets[j].ny >= al_get_display_height(display))) {
					pship.bullets[j].ny = 1;

				}
				if (pship.bullets[j].ny <= 0) {
					pship.bullets[j].ny = al_get_display_height(display) - 1;
				}
				//bullet -> asteroid collision check
				for (int d = 0; d < asize; d++) {
					if (wykobi::point_in_circle(pship.bullets[j].wpoint, asteroids[d].wcirc) && asteroids[d].alive && pship.bullets[j].alive) {
						asteroids[d].destroy();
						pship.bullets[j].destroy();
						score++;
					}

				}
				//asteroid iterator
				for (int f = 0; f < asize; f++) {
					//make new asteroids
					
					if (!asteroids[f].alive && rand() % 500 == 5 && rand() % 500 == 5) {
						//std::cout << "alive!" << std::endl;

                        //std::cout << "rand!" << std::endl;
						asteroids[f].destroy();
						asteroids[f].randomposition();
						asteroids[f].update(al_get_time() - dt);
						asteroids[f].alive = true;
						
					}

					//asteroid wrapping
					if (asteroids[f].nx >= al_get_display_width(display) + (asteroids[f].radius * 2)) {
						asteroids[f].nx = (asteroids[f].radius * 2) * -1;
					}
					if (asteroids[f].nx <= (asteroids[f].radius * 2) * -1) {
						asteroids[f].nx = al_get_display_width(display) + (asteroids[f].radius * 2) - 1;
					}
					if (asteroids[f].ny >= al_get_display_height(display) + (asteroids[f].radius * 2)) {
						asteroids[f].ny = (asteroids[f].radius * 2) * -1;

					}
					if (asteroids[f].ny <= (asteroids[f].radius * 2) * -1) {
						asteroids[f].ny = al_get_display_height(display) + (asteroids[f].radius * 2) - 1;
					}

					//collision check with ship
					if (wykobi::intersect(pship.wtri, asteroids[f].wcirc) && asteroids[f].alive) {
						score = 0;
					}
					//asteroid iterator-iterator - for asteroid collisions 
					for (int e = 0; e < asize; e++) {
						//check for intersection
						if (wykobi::intersect(asteroids[f].wcirc, asteroids[e].wcirc) && &asteroids[f] != &asteroids[e] && asteroids[f].collisionhalt == 0) {
							//possibly not needed
							asteroids[f].collisionhalt = 50;
							//closest point of intersection
							wykobi::point2d<float> ipoint = wykobi::closest_point_on_circle_from_circle(asteroids[e].wcirc, asteroids[f].wcirc);


						}
					}
				}
			}
		}

		//draw loop
		if (event.type == ALLEGRO_EVENT_TIMER && event.timer.source == drawtimer) {
            //update fps delta
            fpsdt = al_get_time();
			std::string scorestring = "Score: ";
			scorestring.append(std::to_string(score));
			al_draw_text(font, white, 700, 15, 0, scorestring.c_str());

			//calc fps
            //fpscounter = 1 / ((al_get_time() - fpsdt));
			fpsline.append(std::to_string(fpscounter));


			if (debugflag) {
				al_draw_text(font, white, 15, 15, 0, posline.c_str());
				al_draw_text(font, white, 15, 25, 0, accelline.c_str());
				al_draw_text(font, white, 15, 35, 0, velline.c_str());
				al_draw_text(font, white, 15, 45, 0, dirline.c_str());
				al_draw_text(font, white, 15, 55, 0, fpsline.c_str());
			}
			//draw entities
			for (int i = 0; i < asize; i++) {
				asteroids[i].draw();
			}
			pship.draw();
			for (int b = 0; b < pship.bsize; b++) {
				pship.bullets[b].draw();
			}
			al_flip_display();

			bclear;
		}

		//key handling

		if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
			switch (event.keyboard.keycode) {
			case ALLEGRO_KEY_W:
				forward = true;
				break;
			case ALLEGRO_KEY_S:
				//pship.ya = 100;
				break;
			case ALLEGRO_KEY_A:
				left = true;
				break;
			case ALLEGRO_KEY_D:
				right = true;
				break;
			case ALLEGRO_KEY_SPACE:
				pship.fire();
				pship.firing = true;
				al_start_timer(pship.firetimer);
				break;
			case ALLEGRO_KEY_F1:
				break;
			case ALLEGRO_KEY_ESCAPE:
				exit = true;

			}
		}
		if (event.type == ALLEGRO_EVENT_KEY_UP) {
			switch (event.keyboard.keycode) {
			case ALLEGRO_KEY_W:
				forward = false;
				pship.thrust = false;
				break;
			case ALLEGRO_KEY_S:
				//pship.ya = 100;
				break;
			case ALLEGRO_KEY_A:
				left = false;
				break;
			case ALLEGRO_KEY_D:
				right = false;
				break;
			case ALLEGRO_KEY_SPACE:
				pship.firing = false;
				break;
			case ALLEGRO_KEY_F1:
				debugflag = !debugflag;
				break;
			}
			//pship.xa = pship.ya = 0;

		}

	}
	return 0;
}
