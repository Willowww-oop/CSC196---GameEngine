#include "Particle.h"
#include <iostream>

void Particle::Update(float dt)
{
	if (lifespan != 0.0f) lifespan -= dt;
	position = position + (velocity * dt);
}

void Particle::Draw(Renderer& renderer)
{
}

