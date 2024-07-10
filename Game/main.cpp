#include "Renderer.h"
#include "VectorTwo.h"
#include "Input.h"
#include "Random.h"
#include "ETime.h"
#include "MathUtils.h"

#include <SDL.h>
#include <iostream>
#include <cstdlib>
#include <vector>

int main(int argc, char* argv[])
{

	Renderer renderer;
	renderer.Initialize();
	renderer.CreateWindow("Game Engine", 800, 600);

	Input input;
	input.Initialize();

	Time time;

	std::vector<Particle> particles;

	/*for (int i = 0; i < 10000; i++)
	{
		particles.push_back(Particle{ { rand() % 800, rand() % 600 }, { randomf(0.01f, 1.0f), 0.0f}});
	}*/

	VectorTwo v1{ 400, 300 };
	VectorTwo v2{ 100, 600 };

	std::vector<VectorTwo> points; 
	for(int i = 0; 1 < 100; i++)
	{
		points.push_back(VectorTwo{ rand() % 800, rand() % 600 });
	}

	float offset = 0;

	// Main loop
	bool quit = false;
	while (!quit)
	{
		time.Tick();
		std::cout << time.GetTime() << std::endl;


		// INPUT 
		input.Update(1);

		if (input.GetKeyDown(SDL_SCANCODE_ESCAPE))
		{
			quit = true;
		}

		// UPDATE
		VectorTwo mousePosition = input.GetMousePosition();

		if (input.GetMouseButtonDown(0))
		{
			particles.push_back(Particle{ { mousePosition, randomOnUnitCircle()  * randomf(50, 300), {randomf(-100, 100), randomf(-100, 100)}});
		}

		for (Particle& particle : particles)
		{
			particle.Update();
			if (particle.position.x > 800) particle.position.x = 0;
			if (particle.position.x < 0) particle.position.x = 800;
		}


		std::cout << mousePosition.x << " " << mousePosition.y << std::endl;

		if (input.GetMouseButtonDown(0) && !input.GetPrevMouseButtonDown(0))
		{
			std::cout << "mouse pressed" << std::endl;
			points.push_back(mousePosition);
		}

		if (input.GetMouseButton(0) && input.getPrevMouseButtonDown(0))
		{
			float distance = (points.back() - mousePosition).Length();

			if(distance > 25) points.push_back(mousePosition);
		}

		// [p, p, p, p]
		/*VectorTwo speed{ 0.1f, -0.1f };
		for (VectorTwo& point : points)
		{
			point = point + 0.002f;
		}*/

		// DRAW
	    // clear screen
		renderer.SetColor(0, 0, 0, 0);
		renderer.BeginFrame();

		renderer.SetColor(255, 255, 255, 0);
		float radius = 60;
		offset += (90 * time.GetDeltaTime());

		for (float angle = 0; angle < 360; angle += 360 / 30)
		{
			float x = Math::Cos(Math::DegToRad(angle + offset)) * Math::Sin(offset + angle) * radius;
			float y = Math::Sin(Math::DegToRad(angle + offset)) * Math::Sin(offset + angle) * radius;

			renderer.DrawRect(400 + x, 300 + y, 4.0f, 4.0f);
		}


	//	// draw line
		renderer.SetColor(255, 255, 255, 0);
		renderer.DrawLine(300, 400, 400, 300);
		renderer.DrawLine(400, 300, 500, 500);
		renderer.DrawLine(500, 400, 300, 400);
		renderer.DrawLine(v1.x, v1.y, v2.x, v2.y);

		for (int i = 0; points.size() > 1 && i < points.size(); i++)
		{
			renderer.DrawLine(points[i].x, points[i].y, points[i + 1].x, points[i + 1].y);
		}

		for (int i = 0; i < 50; i++)
		{
			renderer.SetColor(rand() % 256, rand() % 256, rand() % 256, 0);
			renderer.DrawLine(rand() % 800, rand() % 600);
			renderer.SetColor(rand() % 256, rand() % 256, rand() % 256, 0);
			renderer.DrawLine(rand() % 800, rand() % 600, rand() % 800, rand()% 600);
		}

		renderer.SetColor(255, 255, 255, 0);
		for (Particle particle : particles)
		{
			particle.Draw(renderer);
		}


		renderer.EndFrame();
	}

	//return 0;
}