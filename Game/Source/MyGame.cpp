#include "MyGame.h"
#include "Scene.h"
#include "Engine.h"
#include "GameData.h"
#include "Player.h"
#include "Enemy.h"
#include "Model.h"
#include "PickUp.h"
#include "Font.h"
#include "Text.h"

bool MyGame::Initialize()
{
	m_scene = new Scene(this);


	if (TTF_Init() == -1) {
		printf("TTF_Init: %s\n", TTF_GetError());
		exit(2);
	}


	//m_font = new Font();
	//m_font->Load("MoulinRougeFLF.ttf", 20);

	//m_fontLarge->Load("MoulinRougeFLF.ttf", 70);

	//m_textScore = new Text(m_font);
	//m_textLives = new Text(m_font);
	//m_textTitle = new Text(m_fontLarge);

	g_engine.GetAudio().AddSound("bass.wav");
	g_engine.GetAudio().AddSound("clap.wav");
	g_engine.GetAudio().AddSound("close-hat.wav");
	g_engine.GetAudio().AddSound("cowbell.wav");
	g_engine.GetAudio().AddSound("open-hat.wav");
	g_engine.GetAudio().AddSound("snare.wav");
	g_engine.GetAudio().AddSound("test.wav");
	g_engine.GetAudio().AddSound("MyGameTheme.wav");
	

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
		m_score = 0;
		m_lives = 3;

		m_state = eState::StartLevel;
		break;

	case eState::StartLevel:
		m_scene->RemoveAll();
	{
		Model* playerModel = new Model{ GameData::shipPoints, Color{ 1, 1, 0, 0} };
		Scene* scene = new Scene(this);

		Transform transform{ VectorTwo { 200, 500} , 0, 3 };
		auto player = std::make_unique<Player>(400, transform, playerModel);
		player->SetDamping(0.8f);
		player->SetTag("Player");
		m_scene->AddActor(std::move(player));
	}

	m_spawnTime = 3;
	m_spawnTimer = m_spawnTime;


		m_state = eState::Game;
		break;
	case eState::Game:

		if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_T)&& !g_engine.GetInput().GetPrevKeyDown(SDL_SCANCODE_T)) g_engine.GetAudio().PlaySound("snare.wav");
		if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_Y)&& !g_engine.GetInput().GetPrevKeyDown(SDL_SCANCODE_Y)) g_engine.GetAudio().PlaySound("bass.wav");
		if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_U)&& !g_engine.GetInput().GetPrevKeyDown(SDL_SCANCODE_U)) g_engine.GetAudio().PlaySound("cowbell.wav");
		if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_R)&& !g_engine.GetInput().GetPrevKeyDown(SDL_SCANCODE_R)) g_engine.GetAudio().PlaySound("test.wav");


		g_engine.GetAudio().PlaySound("MyGameTheme.wav");

		m_spawnTimer -= dt;
		if (m_spawnTimer <= 0)
		{
			m_spawnTime -= 0.2f;
			m_spawnTimer = m_spawnTime;


			// create enemy
			auto* enemyModel = new Model{ GameData::shipPoints, Color{ 1, 0.2f, 3, 0.3f} };

			auto enemy = std::make_unique<Enemy>(100, Transform{ {random(g_engine.GetRenderer().GetWidth()), random(g_engine.GetRenderer().GetHeight())}, 0, 2}, enemyModel);
			enemy->SetDamping(0.5f);
			enemy->SetTag("Enemy");
			m_scene->AddActor(std::move(enemy));

			// create pickup
			auto* pickupModel = new Model{ GameData::powerPoints, Color{ 1, 1, 0.5f, 1} };

			auto pickup = std::make_unique<PickUp>(Transform{ {random(g_engine.GetRenderer().GetWidth()), random(g_engine.GetRenderer().GetHeight())}, 0, 2 }, pickupModel);
			pickup->SetTag("Pickup");
			m_scene->AddActor(std::move(pickup));
		}

		break;
	case eState::PlayerDead:

		m_stateTimer -= dt;
		if (m_stateTimer <= 0)
		{
			m_state = eState::StartLevel;
		}

		break;
	case eState::GameOver:

		m_stateTimer -= dt;
		if (m_stateTimer <= 0)
		{
			m_state = eState::Title;
		}

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

		//m_textTitle->Create(renderer, "Pew! Pew!", Color{1, 0, 0, 1});
	//	m_textTitle->Draw(renderer, 260, 300);

		break;
	case MyGame::eState::GameOver:

		//m_textTitle->Create(renderer, "Game Over", Color{1, 0, 0, 1});
		//m_textTitle->Draw(renderer, 260, 300);

		break;
	default:
		break;

	}

	std::string text = "Score " + std::to_string(m_score);
	//m_textScore->Create(renderer, text, { 0, 1, 0, 1 });
	//m_textScore->Draw(renderer, 20, 20);

	text = "Lives " + std::to_string(m_lives);
	//m_textLives->Create(renderer, text, {0, 1, 0, 1});
	//m_textLives->Draw(renderer, renderer.GetWidth() - 100, 20);


	m_scene->Draw(renderer);
}

void MyGame::OnPlayerDeath()
{
	m_lives--;
	m_state = (m_lives == 0) ? eState::GameOver : eState::PlayerDead;
	m_stateTimer = 3;
}
