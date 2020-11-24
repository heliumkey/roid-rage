#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <../wykobi/wykobi.hpp>
#define black al_map_rgb(0, 0, 0)
#define white al_map_rgb(255, 255, 255)
#define bclear al_clear_to_color(black)

class bullet
{

	public:
		bullet(float bx, float by);
		bullet();
		void update(float delta);
		void draw();
		void destroy();
		ALLEGRO_TIMER* lifespan;
		bool alive;
		wykobi::point2d<float> wpoint;
		float x;
		float y;

		float nx;
		float ny;

		float xv;
		float yv;

		float xa;
		float ya;

};

