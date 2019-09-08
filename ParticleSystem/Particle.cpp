#include "Particle.h"
#include <math.h>
#include <SDL.h>
#include <stdlib.h>
using namespace std;
namespace tkp {

	Particle::Particle() {
		init();
	}
	Particle::~Particle() {}

	void Particle::init() {
		m_x = 0;
		m_y = 0;
		m_direction = (2 * M_PI * rand()) / RAND_MAX;
		m_speed = (0.025 * rand()) / RAND_MAX;

		m_speed *= m_speed;
	}
	// Moves the particles
	void Particle::update(int interval) {

		m_direction += interval * 0.0004; // The particles will orbitate

		double xspeed = m_speed * cos(m_direction);
		double yspeed = m_speed * sin(m_direction);

		// Similar to unity, speed * time to generate a movement
		m_x += xspeed * interval;
		m_y += yspeed * interval;

		// reset the particles that has gone outside the screen
		if (m_x < -1 || m_x > 1 || m_y < -1 || m_y > 1) {
			init();
		}

		if (rand() < RAND_MAX / 100) {
			init();
		}
	}
}