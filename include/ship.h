#pragma once
#include <iostream>
#include <fstream>
#include "bullet.h"
#include "asteroid.h"




class ship
{

	public:
		ship(float sx, float sy);
		void update(float delta);
		void printpos();
		

		ALLEGRO_BITMAP* shipbmp = al_create_bitmap(20, 20);

		ALLEGRO_TIMER* firetimer;
		wykobi::triangle<float, 2> wtri;
		float sizeh;
		float sizew;
		float rotation;
		bullet* bullets;
		void fire();
		void rotate(float degrees);
		void rotateLeft(float speed);
		void rotateRight(float speed);
		void draw();

		bool thrust;
		bool firing;


		int bcount;
		int bsize;

		float x;
		float y;

		float nx;
		float ny;

		float x1;
		float y1;

		float nx1;
		float ny1;

		float x2;
		float y2;

		float nx2;
		float ny2;

		float rnx;
		float rny;

		float rnx1;
		float rny1;

		float rnx2;
		float rny2;

		float xv;
		float yv;

		float xa;
		float ya;

		float centerx;
		float centery;

		float centernx;
		float centerny;

};

