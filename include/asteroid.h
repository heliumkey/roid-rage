#pragma once
#include "bullet.h"
#include <cstdlib>


class asteroid
{


	public:
		asteroid(float ax, float ay, float axv, float ayv);
		asteroid();
		void update(float delta);
		void draw();
		void destroy();
		bool contains(float cx, float cy);
		void randomposition();
		int collisionhalt;
		float mass;

		wykobi::circle<float> wcirc;
		float radius;

		bool alive;

		float x;
		float y;
		float xa;
		float ya;
		float nx;
		float ny;
		float xv;
		float yv;

};

