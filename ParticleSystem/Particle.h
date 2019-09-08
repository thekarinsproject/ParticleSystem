#pragma once
namespace tkp {
	struct Particle
	{
	public:
		double m_x;
		double m_y;
	public:
		Particle();
		virtual ~Particle();
		void update(int interval); // updates the position and color of particles
	private:
		double m_speed;
		double m_direction;
	private:
		void init();
	};
}

