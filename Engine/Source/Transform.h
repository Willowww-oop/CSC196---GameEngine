#pragma once
#include "VectorTwo.h"

struct Transform
{
	VectorTwo position;
	float rotation;
	float scale;

	Transform() = default;
	Transform(VectorTwo position, float rotation = 0, float scale = 1) :
	
		position{ position },
		rotation { rotation },
		scale{ scale }
	{}
};