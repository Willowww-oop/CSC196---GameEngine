#pragma once
#include "Particle.h"
#include <vector>


class ParticleSystem
{
public:
	ParticleSystem() = default;
	ParticleSystem(int maxSize)
	{
		m_particles.resize(maxSize);
	}

	void Update(float dt);
	void Draw(Renderer& renderer);

	void AddParticle(const Particle::Data& data);


private:
	Particle* GetFreeParticle();

private:
	std::vector<Particle> m_particles; // pool of particles

};