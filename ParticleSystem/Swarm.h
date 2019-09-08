#pragma once
#include "Particle.h"

namespace tkp {
	class Swarm
	{
	public: 
		const static int NPARTICLES = 3000;
	public:
		Swarm();
		virtual ~Swarm();
		const Particle*  const getParticles() { return m_pParticles; };
		void update(int elapsed);
	private:
		Particle* m_pParticles;
		int lastTime;
	};
}

