#include "GSPlay.h"

#include "Shaders.h"
#include "Texture.h"
#include "Models.h"
#include "Camera.h"
#include "Font.h"
#include "Sprite2D.h"
#include "Sprite3D.h"
#include "Text.h"

extern int screenWidth; //need get on Graphic engine
extern int screenHeight; //need get on Graphic engine

GSPlay::GSPlay()
{
}


GSPlay::~GSPlay()
{

}

void GSPlay::InitTank(int k, int f) {

	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto texture = ResourceManagers::GetInstance()->GetTexture("Hull_06");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	// xet huong
	direction = Direction_A;

	if (k)
	{
		m_tank = std::make_shared<Sprite2D>(model, shader, texture);
		m_tank->Set2DPosition(ax, ay);
		m_tank->SetSize(64, 64);

		texture = ResourceManagers::GetInstance()->GetTexture("Gun_07_A");
		m_Weapon = std::make_shared<Sprite2D>(model, shader, texture);
		m_Weapon->Set2DPosition(ax, ay + f * 40);
		m_Weapon->SetSize(9, 28);
		return;
	}

	//show tank
	texture = ResourceManagers::GetInstance()->GetTexture("Hull_06_01");
	//shader = ResourceManagers::GetInstance()->GetShader("Hull_06");
	m_tank = std::make_shared<Sprite2D>(model, shader, texture);
	m_tank->Set2DPosition(ax, ay);
	m_tank->SetSize(64, 64);

	texture = ResourceManagers::GetInstance()->GetTexture("Gun_07_A_01");
	m_Weapon = std::make_shared<Sprite2D>(model, shader, texture);
	m_Weapon->Set2DPosition(ax + f * 40, ay);
	m_Weapon->SetSize(28, 9);
}

void GSPlay::Init()
{
	for (int i = 0; i < 20; i++)
		for (int j = 0; j < 20; j++)
			mp[i][j] = 0;
	ax = ay = 400;
	currentTime = 0.0f;
	direction = Direction_Stop;

	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_play");

	//BackGround
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_BackGround = std::make_shared<Sprite2D>(model, shader, texture);
	m_BackGround->Set2DPosition(screenWidth / 2, screenHeight / 2);
	m_BackGround->SetSize(screenWidth, screenHeight);

	//text game title
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("arialbd");
	m_score = std::make_shared< Text>(shader, font, "score: 10", TEXT_COLOR::RED, 1.0);
	m_score->Set2DPosition(Vector2(5, 25));

	// view tank
	InitTank(1, -1);
}

void GSPlay::Exit()
{

}


void GSPlay::Pause()
{

}

void GSPlay::Resume()
{

}


void GSPlay::HandleEvents()
{

}

void GSPlay::HandleKeyEvents(int key, bool bIsPressed)
{
	if (bIsPressed)
	{
		if (key == 'W' || key == 'w' || key == 'S' || key == 's')
		{
			
			if (key == 'S' || key == 's') {
				InitTank(1, 1);
				direction = Direction_S;
			}
			else {
				InitTank(1, -1);
				direction = Direction_W;
			}
		}
		else if (key == 'A' || key == 'a' || key == 'D' || key == 'd')
		{
			
			if (key == 'A' || key == 'a') {
				InitTank(0, -1);
				direction = Direction_A;
			}
			else {
				InitTank(0, 1);
				direction = Direction_D;
			}
		}
	}
	else
	{
		direction = Direction_Stop;
	}
	
}

void GSPlay::HandleTouchEvents(int x, int y, bool bIsPressed)
{
}

void GSPlay::Update(float deltaTime)
{
	currentTime += deltaTime;
	
	if (currentTime > 0.1f)
	{
		currentTime -= 0.1f;
		switch (direction)
		{
			case Direction_A:
				ax -= 10;
				if (ax < 0 ) ax = 0;
				break;
			case Direction_D:
				ax += 10;
				if (ax >  750) ax = 750;
				break;
			case Direction_W:
				ay -= 10;
				if (ay < 0) ay = 0;
				break;
			case Direction_S:
				ay += 10;
				if (ay > 750) ay = 750;
				break;
			default:
				break;
		}
	}

	m_tank->Set2DPosition(ax, ay);
	m_tank->Draw();
	m_Weapon->Draw();
}

void GSPlay::Draw()
{
	m_BackGround->Draw();
	m_score->Draw();
	m_tank->Draw();
	m_Weapon->Draw();
}

void GSPlay::SetNewPostionForBullet()
{
}