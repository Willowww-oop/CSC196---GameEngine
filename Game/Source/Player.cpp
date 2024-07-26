#include "Player.h"
#include "Engine.h"
#include "Scene.h"
#include "Bullet.h"
#include "MyGame.h"

#include <iostream>

void Player::Update(float dt)
{
	// Movement

	float thrust = 0;
	VectorTwo direction{ 0, 0 };

	if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_W))
	{
		direction.x = 1;
	}
	if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_S)) direction.x = -1;

	if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_Q)) direction.y = -1;
	if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_E)) direction.y = 1;


	if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_A)) m_transform.rotation -= Math::DegToRad(100) * dt;
	if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_D)) m_transform.rotation += Math::DegToRad(100) * dt;


	//m_velocity += VectorTwo{ thrust, 0.0f }.Rotate(m_transform.rotation);


	VectorTwo acceleration = direction.Rotate(m_transform.rotation) * m_speed;
	m_velocity += acceleration * dt;


	if (m_transform.position.x > 1000) m_transform.position.x = 0;
	if (m_transform.position.x < 0) m_transform.position.x = 1000;
	if (m_transform.position.y > 800) m_transform.position.y = 0;
	if (m_transform.position.y < 0) m_transform.position.y = 800;

	//m_transform.position.x = Math::Wrap(m_transform.position.x, (float)g_engine.GetRenderer().GetWidth());
	//m_transform.position.y = Math::Wrap(m_transform.position.y, (float)g_engine.GetRenderer().GetHeight());

	// Shoot
	
	m_fireTimer -= dt;
	std::vector<Particle> particles;

	if (g_engine.GetInput().GetMouseButtonDown(0))
	{
		for (int i = 0; i < 300; i++)
		
			particles.push_back(Particle{ g_engine.GetInput().GetMousePosition(), randomOnUnitCircle() * randomf(10, 200), 1.0f, random(255), random(255), random(255), 0});
		}
	}

	for (Particle& particle : particles)
	{
		particle.Update(g_engine.GetTime().GetDeltaTime());
		if (particle.position.x > 1000) particle.position.x = 0;
		if (particle.position.x < 0) particle.position.x = 1000;
		if (particle.position.y > 800) particle.position.y = 0;
		if (particle.position.y < 0) particle.position.y = 800;
	}

	if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_SPACE) && m_fireTimer <=0/* && !g_engine.GetInput().GetPrevKeyDown(SDL_SCANCODE_SPACE)*/)
	{
		m_fireTimer = 0.2f;

		VectorTwo direction = g_engine.GetInput().GetMousePosition() - m_transform.position;
		float angle = direction.Angle();


		std::vector<VectorTwo> points;
		points.push_back(VectorTwo{ 5, 0 });
		points.push_back(VectorTwo{ -5, -5 });
		points.push_back(VectorTwo{ -5, 5 });
		points.push_back(VectorTwo{ 5, 0 });

		Model* model = new Model{ points, Color{ 1, 1, 0, 0} };
		Transform transform{ m_transform.position, angle , 1.0f };

		auto bullet = std::make_unique<Bullet>(400.0f, transform, model);
		bullet->SetLifespan(2.0f);

		bullet->SetTag("Bullet");

		m_scene->AddActor(std::move(bullet));
		
	}


	Actor::Update(dt);
}

void Player::OnCollision(Actor* actor)
{
	if (actor->GetTag() == "Enemy")
	{
		m_destroyed = true;

		/*MyGame* game = dynamic_cast <MyGame*>(m_scene->GetGame())->OnPlayerDeath();
		if (game)
		{
			game->OnPlayerDeath();
		}*/

		dynamic_cast <MyGame*>(m_scene->GetGame())->OnPlayerDeath();
	}
}

