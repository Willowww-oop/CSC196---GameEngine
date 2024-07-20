#include "Engine.h"
#include "Player.h"
#include "Scene.h"
#include "Enemy.h"
#include "GameData.h"
#include "MyGame.h"

#include <iostream>
#include <cstdlib>
#include <vector>


int main(int argc, char* argv[])
{

	g_engine.Initialize();


	//g_engine.GetAudio()->AddSounds("bass.wav");
	//g_engine.GetAudio()->AddSounds("bass.wav");
	//g_engine.GetAudio()->AddSounds("bass.wav");
	//g_engine.GetAudio()->AddSounds("bass.wav");
	//g_engine.GetAudio()->AddSounds("bass.wav");
	//g_engine.GetAudio()->AddSounds("bass.wav");
	//g_engine.GetAudio()->AddSounds("bass.wav");

	//std::vector<FMOD::Sound*> sounds;
	//audio->createSound("bass.wav", FMOD_DEFAULT, 0, &sounds);


	std::vector<Particle> particles;
	float offset = 0;

	std::vector<VectorTwo> points;


	Model* model = new Model{ GameData::shipPoints, Color{ 1.0f, 1.0f, 1.0f, 0.0f} };
	Scene* scene = new Scene();


	Transform transform{ VectorTwo { 400, 300} , 0, 3 };
	Player* player = new Player(randomf(200, 500.0f), transform, model);
	player->SetDamping(0.8f);
	player->SetTag("Player");
	scene->AddActor(player);

	auto* enemyModel = new Model{ GameData::shipPoints, Color{ 1, 0, 3, 0} };

	auto* enemy = new Enemy(400, Transform{ {10, 10 }, 0, 2 }, enemyModel);
	enemy->SetDamping(1.0f);
	enemy->SetTag("Enemy");
	scene->AddActor(enemy);


		// 0001 = 1
		// 0010 = 2
		// 0100 = 4
		// 1000 = 8

		// >> 1

		float rotation = 0;

		VectorTwo position{ 400, 300 };


		VectorTwo v1{ 400, 300 };
		VectorTwo v2{ 100, 600 };

		//for (int i = 0; 1 < 100; i++)
		//{
		//	points.push_back(VectorTwo{ rand() % 800, rand() % 600 });
		//}

		//float offset = 0;

		float spawnTimer = 2;


		// Main loop
		while (!g_engine.IsQuit())
		{
			g_engine.Update();

			//transform.rotation = transform.rotation + time.GetDeltaTime();



			// UPDATE
			scene->Update(g_engine.GetTime().GetDeltaTime());

			VectorTwo mousePosition = g_engine.GetInput().GetMousePosition();

			if (g_engine.GetInput().GetMouseButtonDown(0))
			{
				for (int i = 0; i < 300; i++)
				{
					particles.push_back(Particle{ mousePosition, randomOnUnitCircle() * randomf(10, 200), 1.0f, random(255), random(255), random(255), 0 });
				}
			}

			for (Particle& particle : particles)
			{
				particle.Update(g_engine.GetTime().GetDeltaTime());
				if (particle.position.x > 1000) particle.position.x = 0;
				if (particle.position.y > 800) particle.position.y = 0;
			}


			if (g_engine.GetInput().GetMouseButtonDown(0) && !g_engine.GetInput().GetPrevMouseButtonDown(0))
			{
				std::cout << "mouse pressed" << std::endl;
				points.push_back(mousePosition);
			}

			if (g_engine.GetInput().GetMouseButtonDown(0) && !g_engine.GetInput().GetPrevMouseButtonDown(0))
			{
				float distance = (points.back() - mousePosition).Length();

				if (distance > 25) points.push_back(mousePosition);
			}

			// [p, p, p, p]
			VectorTwo speed{ 0.1f, -0.1f };
			for (VectorTwo& point : points)
			{
				point = point + 0.002f;
			}

			// DRAW
			// clear screen


			g_engine.GetRenderer().SetColor(0, 0, 0, 0);
			g_engine.GetRenderer().BeginFrame();

			g_engine.GetRenderer().SetColor(255, 255, 255, 0);
			float radius = 60;
			offset += (90 * g_engine.GetTime().GetDeltaTime());


			g_engine.GetRenderer().SetColor(255, 255, 255, 0);
			for (Particle particle : particles)
			{
				particle.Draw(g_engine.GetRenderer());
			}

			scene->Draw(g_engine.GetRenderer());


			g_engine.GetRenderer().EndFrame();


		}

		return 0;
	}
	