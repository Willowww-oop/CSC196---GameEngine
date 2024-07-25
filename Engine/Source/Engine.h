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
#include "ParticleSystem.h"
#include "MathUtils.h"

#include <fmod.hpp>
#include <SDL.h>
#include <memory>

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
	ParticleSystem& GetPS() { return *m_particleSystem; }
	
	Time& GetTime() { return *m_time; }

	bool IsQuit() { return quit; }

private:
	bool quit{ false };

	std::unique_ptr<Time> m_time;


	std::unique_ptr<Renderer> m_renderer;
	std::unique_ptr<Input> m_input;
	std::unique_ptr<Audio> m_audio;

	std::unique_ptr<ParticleSystem> m_particleSystem;
};



extern Engine g_engine;
