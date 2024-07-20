#include "MyGame.h"
#include "Scene.h"
#include "Engine.h"
#include "GameData.h"
#include "Player.h"
#include "Enemy.h"
#include "Model.h"

bool MyGame::Initialize()
{
	m_scene = new Scene();

	return true;
}

void MyGame::Shutdown()
{
}

void MyGame::Update(float dt)
{
	switch (m_state)
	{
	case eState::Title:

		if (m_engine->GetInput().GetKeyDown(SDL_SCANCODE_SPACE))
		{
			m_state = eState::StartGame;
		}
		break;

	case eState::StartGame:
	{
		m_score = 0;
		m_state = eState::StartLevel;

	}


		break;
	case eState::StartLevel:
	{
		Model* model = new Model{ GameData::shipPoints, Color{ 1, 1, 1} };
		Scene* scene = new Scene();

		Transform transform{ VectorTwo { 400, 300} , 0, 3 };
		Player* player = new Player(800, transform, model);
		player->SetDamping(0.8f);
		player->SetTag("Player");
		scene->AddActor(player);
	}

	m_spawnTime = 3;
	m_spawnTimer = m_spawnTime;


		m_state = eState::Game;
		break;
	case eState::Game:

		m_spawnTimer -= dt;
		if (m_spawnTimer <= 0)
		{
			m_spawnTime -= 0.2f;
			m_spawnTimer = m_spawnTime;

			auto* enemyModel = new Model{ GameData::shipPoints, Color{ 1, 0, 3} };

			auto* enemy = new Enemy(400, Transform{ {10, 10 }, 0, 2 }, enemyModel);
			enemy->SetDamping(1.0f);
			enemy->SetTag("Enemy");
			m_scene->AddActor(enemy);
		}

		break;
	case eState::PlayerDead:
		break;
	case eState::GameOver:
		break;
	default:
		break;
	}

	m_scene->Update(dt);
}

void MyGame::Draw(Renderer& renderer)
{
	switch (m_state)
	{
	case MyGame::eState::Title:

		break;
	case MyGame::eState::GameOver:

		break;
	default:
		break;

	}


	m_scene->Draw(renderer);
}
