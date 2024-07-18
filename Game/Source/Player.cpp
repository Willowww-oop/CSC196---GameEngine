#include "Player.h"
#include "Engine.h"
#include "Scene.h"
#include "Bullet.h"

#include <iostream>

void Player::Update(float dt)
{
	// Movement

	float thrust = 0;
	if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_LEFT)) m_transform.rotation -= Math::DegToRad(100) * dt;
	if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_RIGHT)) m_transform.rotation += Math::DegToRad(100) * dt;

	if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_DOWN)) thrust = m_speed;
	if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_UP)) thrust = m_speed;

	VectorTwo acceleration = VectorTwo{ thrust, 0.0f, }.Rotate(m_transform.rotation);
	m_velocity += acceleration * dt;

	m_transform.position.x = Math::Wrap(m_transform.position.x, (float)g_engine.GetRenderer().GetWidth());
	m_transform.position.x = Math::Wrap(m_transform.position.x, (float)g_engine.GetRenderer().GetWidth());

	// Shoot
	
	m_fireTimer -= dt;

	if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_SPACE) && m_fireTimer <=0/* && !g_engine.GetInput().GetPrevKeyDown(SDL_SCANCODE_SPACE)*/)
	{
		m_fireTimer = 1;

		std::vector<VectorTwo> points;
		points.push_back(VectorTwo{ 5, 0 });
		points.push_back(VectorTwo{ -5, -5 });
		points.push_back(VectorTwo{ -5, 5 });
		points.push_back(VectorTwo{ 5, 0 });

		Model* model = new Model{ points, Color{ 1, 1, 0, 0} };
		Transform transform{ m_transform.position, m_transform.rotation, 1.0f };

		Bullet* bullet = new Bullet(400, transform, model);
		bullet->SetLifespan(1);

		bullet->SetTag("Player");

		m_scene->AddActor(bullet);
		
	}


	Actor::Update(dt);
}

void Player::OnCollision(Actor* actor)
{
	if (actor->GetTag() == "Enemy")
	{
		m_destroyed = true;
	}
}
