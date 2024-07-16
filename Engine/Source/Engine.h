#pragma once
#include "Renderer.h"
#include "VectorTwo.h"
#include "Audio.h"
#include "Input.h"
#include "Random.h"
#include "ETime.h"
#include "Model.h"
#include "Actor.h"
#include "Particle.h"
#include "MathUtils.h"
#include "Transform.h"
#include "MathUtils.h"

//#include <fmod.hpp>
#include <SDL.h>

// #define RENDERER g_engine.GetRenderer()

class Engine
{
public:
	Engine() = default;
	~Engine() = default;

	bool Initialize();
	void Shutdown();

	void Update();

	Renderer& GetRenderer() { return *m_renderer; }
	Input& GetInput() { return *m_input; }
	Audio& GetAudio() { return *m_audio; }

private:
	Renderer* m_renderer{ nullptr };
	Input* m_input{ nullptr };
	Audio* m_audio{ nullptr };
};

extern Engine g_engine;
