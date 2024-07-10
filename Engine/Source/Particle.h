#pragma once
#include "VectorTwo.h"
#include "Renderer.h"

struct Particle
{
	VectorTwo position{ 0, 0 };
	VectorTwo velocity{ 0, 0 };
	float lifespan = 0;


	Particle() = default;
	Particle(VectorTwo position, VectorTwo velocity) : position{ position }, velocity{ velocity }
	{

	}
	void Update(float dt);
	void Draw(Renderer& renderer);
};