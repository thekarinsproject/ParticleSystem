#include <iostream>
#include <SDL.h>
#include <math.h>
#include "Screen.h"
#include <stdlib.h>
#include <time.h>
#include "Swarm.h"

using namespace std;
using namespace tkp;

int main(int argc, char *args[]) {

	srand(time(NULL));

	Screen screen;

	if (screen.init() == false) {
		cout << "Error initialising SDL" << endl;
	}

	Swarm swarm;

	//Variables
	bool quit = false;

	// while game loop
	while (!quit) 
	{
		// Update Particles
		// Draw Particles

		int elapsed = SDL_GetTicks(); // Gets the current program up time in miliseconds

		swarm.update(elapsed);

		
		// calculates a value between 0 and 255 - (1 + (-1/1) * 128), note: Adding a cast to unsigned char nullifies the smoothness.
		unsigned char green = (1 + sin(elapsed * 0.0001)) * 128;
		unsigned char red = (1 + sin(elapsed * 0.0002)) * 128;
		unsigned char blue = (1 + sin(elapsed * 0.0003)) * 128;

		const Particle* const pParticles = swarm.getParticles();

		for (int i = 0; i < Swarm::NPARTICLES; i++) {
			Particle particle = pParticles[i];

			int x = (particle.m_x + 1) * Screen::SCREEN_WIDTH / 2;
			int y = (particle.m_y + 1) * Screen::SCREEN_HEIGHT / 2;

			screen.setPixel(x, y, red, green, blue);
		}

		screen.boxBlur();

		/*
		for (int y = 0; y < Screen::SCREEN_HEIGHT; y++) {
			for (int x = 0; x < Screen::SCREEN_WIDTH; x++)
				screen.setPixel(x, y, red, green, blue);
		}
		*/
		//Draw Screen
		screen.update();
		// Check for events/messages
		if (!screen.processEvent()) {
			break;
		}

	}

	screen.close();

	return 0;
}