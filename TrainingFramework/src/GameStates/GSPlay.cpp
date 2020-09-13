#include "GSPlay.h"
#include "Shaders.h"
#include "Texture.h"
#include "Models.h"
#include "Camera.h"
#include "Font.h"
#include "Sprite2D.h"
#include "Sprite3D.h"
#include "Text.h"
#include <fstream>
#include <iostream>


extern int screenWidth; //need get on Graphic engine
extern int screenHeight; //need get on Graphic engine

GSPlay::GSPlay()
{
}

GSPlay::~GSPlay()
{

}

void GSPlay::InitTank(int k) {
	std::string s = "Tank_1_A";
	s[7] += (k - 1);
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto texture = ResourceManagers::GetInstance()->GetTexture(s);
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	// xet huong
	direction = Direction_A;
	old_direction = Direction_W;
	m_tank = std::make_shared<Sprite2D>(model, shader, texture);
	m_tank->Set2DPosition(ax, ay);
	m_tank->SetSize(64, 64);
}

void GSPlay::SetDirectionTank() {
	
	for each (std::shared_ptr<Tank> tank in lst_tank) {
		std::string s = "Tank_2_A";
		s[7] += (tank->getDirectionk() - 1);
		tank->SetTexture(ResourceManagers::GetInstance()->GetTexture(s));
	}
}

void GSPlay::Init()
{

	m_IsPause = 0; m_isDie = 0;
	// Initialize SoLoud (automatic back-end selection)
	soloud.init();

	sample.load("C:\\Users\\Bleach\\Desktop\\Programming_lesson_06\\nhac_nen.wav"); // Load a wave file
	soloud.play(sample);

	std::ifstream infile;
	infile.open("C:\\Users\\Bleach\\Desktop\\Programming_lesson_06\\\output.txt");
	ax = ay = 0;
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			int x; infile >> x;
			mp[i][j] = x;
		}
	}
	infile.close();

	ax = 50; ay = 600;
	currentTime = 0.0f;
	direction = Direction_Stop;

	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto texture = ResourceManagers::GetInstance()->GetTexture("map");

	//BackGround
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_BackGround = std::make_shared<Sprite2D>(model, shader, texture);
	m_BackGround->Set2DPosition(screenWidth / 2, screenHeight / 2);
	m_BackGround->SetSize(screenWidth, screenHeight);

	// tường

	
	for (int i = 1; i < 19; i++) {
		for (int j = 1; j < 19; j++) {
			if (mp[i][j] == 2) {
				texture = ResourceManagers::GetInstance()->GetTexture("trees");
				auto wall = std::make_shared<Sprite2D>(model, shader, texture);
				wall->Set2DPosition(i*40, j*40);
				wall->SetSize(40, 40);
				lst_wall.push_back(wall);
			} 
			else if (mp[i][j] == 1) {
				texture = ResourceManagers::GetInstance()->GetTexture("gach");
				auto wall = std::make_shared<Sprite2D>(model, shader, texture);
				wall->Set2DPosition(i * 40, j * 40);
				wall->SetSize(40, 40);
				lst_wall.push_back(wall);
			}
			
		}
	}
	
	// view tank
	InitTank(1);

	for (int i = 0; i < 5; i++) {
		auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
		auto texture = ResourceManagers::GetInstance()->GetTexture("Tank_1_A");
		auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
		std::shared_ptr<Tank> tank = std::make_shared<Tank>(model, shader, texture);
		tank->SetAx(400 + (i + 2) *40);
		tank->SetAy(400 - (i + 2) *40);
		tank->SetDirectionk(direction);
		tank->Set2DPosition(tank->GetAx(), tank->GetAy());
		tank->SetSize(64, 64);
		lst_tank.push_back(tank);
	}
}

void GSPlay::Exit()
{

}

void GSPlay::Pause()
{
	//todo pause
	int k = 1;
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto texture = ResourceManagers::GetInstance()->GetTexture("xxx");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");

	//resume button
	texture = ResourceManagers::GetInstance()->GetTexture("button_resume");
	std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(screenWidth / 2, 300);
	button->SetSize(200, 50);
	button->SetOnClick([]() {
		
		});
	m_listButton.push_back(button);

	//exit button
	texture = ResourceManagers::GetInstance()->GetTexture("button_quit");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(screenWidth / 2, 500);
	button->SetSize(200, 50);
	button->SetOnClick([]() {
		exit(0);
		});
	m_listButton.push_back(button);


	for each (std::shared_ptr<GameButton> button in m_listButton) {
		button->Draw();
	}
}

void GSPlay::EndGame()
{
	//todo pause
	int k = 1;
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto texture = ResourceManagers::GetInstance()->GetTexture("xxx");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");

	//resume button
	texture = ResourceManagers::GetInstance()->GetTexture("button_play");
	std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(screenWidth / 2, 300);
	button->SetSize(200, 50);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Play);
		});
	m_listButton.push_back(button);

	//resume button
	texture = ResourceManagers::GetInstance()->GetTexture("button_back");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(screenWidth / 2, 450);
	button->SetSize(200, 50);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Menu);
		});
	m_listButton.push_back(button);

	//exit button
	texture = ResourceManagers::GetInstance()->GetTexture("button_quit");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(screenWidth / 2, 600);
	button->SetSize(200, 50);
	button->SetOnClick([]() {
		exit(0);
		});
	m_listButton.push_back(button);


	
}

void GSPlay::Resume()
{
	m_listButton.clear();
	m_IsPause = 0;
}

void GSPlay::HandleEvents()
{

}

void GSPlay::HandleKeyEvents(int key, bool bIsPressed)
{
	if (m_isDie || m_IsPause )
	{
		return;
	}

	if (bIsPressed)
	{
		if (key == 27)
		{
			m_IsPause = 1;
			this->Pause();
		}
		if (key == 'W' || key == 'w' || key == 'S' || key == 's')
		{
			
			if (key == 'S' || key == 's') {
				InitTank(Direction_S);
				old_direction = direction = Direction_S;
			}
			else {
				InitTank(Direction_W);
				old_direction = direction = Direction_W;
			}
		}
		else if (key == 'A' || key == 'a' || key == 'D' || key == 'd')
		{
			
			if (key == 'A' || key == 'a') {
				InitTank(Direction_A);
				old_direction = direction = Direction_A;
			}
			else {
				InitTank(Direction_D);
				old_direction = direction = Direction_D;
			}
		}
		else if (key == 32)
		{
			auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
			auto texture = ResourceManagers::GetInstance()->GetTexture("bullet");
			auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
			std::shared_ptr<Bullet> bullet = std::make_shared<Bullet>(model, shader, texture);
			bullet->SetAx(ax);
			bullet->SetAy(ay);
			bullet->SetDirectionk(old_direction);

			switch (bullet->getDirectionk())
			{
			case Direction_A:
				bullet->SetAx(bullet->GetAx() - 40);
				break;
			case Direction_D:
				bullet->SetAx(bullet->GetAx() + 40);
				break;
			case Direction_W:
				bullet->SetAy(bullet->GetAy() - 40);
				break;
			case Direction_S:
				bullet->SetAy(bullet->GetAy() + 40);
				break;
			default:
				break;
			}
			
			bullet->Set2DPosition(bullet->GetAx(), bullet->GetAy());
			bullet->SetSize(128, 128);
			bullet->SetType(Bullet_Player);
			lst_bullet.push_back(bullet);
		}
	}
	else
	{
		if (key == 'W' || key == 'w' || key == 'S' || key == 's' || key == 'A' || key == 'a' || key == 'D' || key == 'd') 
		{
			direction = Direction_Stop;
		}

	}
	
}

void GSPlay::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	for (auto it : m_listButton)
	{
		(it)->HandleTouchEvents(x, y, bIsPressed);
		if ((it)->IsHandle()) break;
	}
	if (m_IsPause) {
		if ( (300 < x && x < 600) && ( 200< y && y < 400))
		{
			this->Resume();
		}
	}
	else if (m_IsPause) {
		if ((300 < x && x < 600) && (200 < y && y < 400))
		{
			this->Init();
		}
	}

}

bool IsCheckWall(int mp[100][100], int x, int y, int k) {
	x = x / 40; y = y / 40;
	bool kq = true;
	switch (k)
	{
	case Direction_A:
		if (mp[x - 1][y] == 1)
		{
			kq = false;
		}
		break;
	case Direction_D:
		if (mp[x + 1][y] == 1)
		{
			kq = false;
		}
		break;
	case Direction_W:
		if (mp[x][y-1] == 1)
		{
			kq = false;
		}
		break;
	case Direction_S:
		if (mp[x][y + 1] == 1)
		{
			kq = false;
		}
		break;
	default:
		break;
	}
	return kq;
}

int IsDie(int ax, int ay, int x, int y, int k) {
	int ok = 0;
	if ((x - ax) * (x - ax) + (y - ay) * (y - ay) < (k + 32) * (k + 32)) {
		ok = 1;
	}
	return ok;
}

void GSPlay::Update(float deltaTime)
{
	if (m_isDie || m_IsPause)
	{
		return;
	}
	if (deltaTime <= 0) return;
	currentTime += deltaTime;
	if (currentTime > 0.06f)
	{
		currentTime -= 0.06f;
		switch (direction)
		{
			case Direction_A:
				if (IsCheckWall(mp, ax, ay, direction))
				{
					ax -= 10;
					if (ax < 50) ax = 50;
				}
				break;
			case Direction_D:
				if (IsCheckWall(mp, ax, ay, direction))
				{
					ax += 10;
					if (ax > 750) ax = 750;
				}
				break;
			case Direction_W:
				if (IsCheckWall(mp, ax, ay, direction))
				{
					ay -= 10;
					if (ay < 50) ay = 50;
				}
				break;
			case Direction_S:
				if (IsCheckWall(mp, ax, ay, direction))
				{
					ay += 10;
					if (ay > 750) ay = 750;
				}
				break;
			default:
				break;
		}
		m_tank->Set2DPosition(ax, ay);
		auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
		auto texture = ResourceManagers::GetInstance()->GetTexture("Explosion_A");
		auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
		

		// xử lý sự kiện nổ
		std::list<std::shared_ptr<Bum>> bums;
		for each (std::shared_ptr<Bum> bum in lst_bum) {
			bum->SetFram(bum->getFram() + 1);
			if (bum->getFram() < 8) {
				std::string s = "Explosion_A";
				s[10] += bum->getFram();
				bum->SetTexture(ResourceManagers::GetInstance()->GetTexture(s));
				bums.push_back(bum);
			}
		}

		lst_bum.clear();
		lst_bum = bums;

		// xử lý sự kiện đạn bay
		std::list<std::shared_ptr<Bullet>> temp;
		for each (std::shared_ptr<Bullet> bullet in lst_bullet)
		{
			switch (bullet->getDirectionk())
			{
			case Direction_A:
				bullet->SetAx(bullet->GetAx() - 40);
				break;
			case Direction_D:
				bullet->SetAx(bullet->GetAx() + 40);
				break;
			case Direction_W:
				bullet->SetAy(bullet->GetAy() - 40);
				break;
			case Direction_S:
				bullet->SetAy(bullet->GetAy() + 40);
				break;
			default:
				break;
			}
			if ( 30 > bullet->GetAx() || bullet->GetAx() > 780 || 30 > bullet->GetAy() || bullet->GetAy() > 780 
				|| !IsCheckWall(mp, bullet->GetAx(), bullet->GetAy(), bullet->getDirectionk()))
			{
				//lst_bullet.erase()
				//bullet->~Bullet();
			}
			else {
				if (bullet->GetType() == Bullet_Computer) {
					if(IsDie(ax, ay, bullet->GetAx(), bullet->GetAy(), 10)) 
					{
						m_isDie = 1;
						this->EndGame();
					}
					temp.push_back(bullet); 
				}
				else {
					std::list<std::shared_ptr<Tank>> tankss;
					int ok = 0;
					for each (std::shared_ptr<Tank> tank in lst_tank) {
						if (ok) {
							tankss.push_back(tank);
							continue;
						}
						ok = tank->IsDie(bullet->GetAx(), bullet->GetAy(), 10);
						if (ok) {
							//tank->~Tank();

							std::shared_ptr<Bum> bum = std::make_shared<Bum>(model, shader, texture);
							// xet huong
							bum->SetFram(0);
							bum->Set2DPosition(tank->GetAx(), tank->GetAy());
							bum->SetSize(64, 64);
							bum->Draw();
							lst_bum.push_back(bum);
						}
						else {
							tankss.push_back(tank);
						}
					}
					lst_tank.clear();
					lst_tank = tankss;

					if (!ok) temp.push_back(bullet);
				}
				
			}
			bullet->Set2DPosition(bullet->GetAx(), bullet->GetAy());
			bullet->Draw();
		}
		
		lst_bullet.clear();
		lst_bullet = temp;
		
		// xử lý sự kiện tank computer
		for each (std::shared_ptr<Tank> tank in lst_tank) {
			tank->RandomDir();
			if (IsCheckWall(mp, tank->GetAx(), tank->GetAy(), tank->getDirectionk()))
			{
				switch (tank->getDirectionk())
				{
				case Direction_A:
					tank->SetAx(tank->GetAx() - 10);
					if (tank->GetAx() < 50) tank->SetAx(50);
					break;
				case Direction_D:
					tank->SetAx(tank->GetAx() + 10);
					if ((tank->GetAx() > 700)) tank->SetAx(700);
					break;
				case Direction_W:
					tank->SetAy(tank->GetAy() - 10);
					if (tank->GetAy() < 50) tank->SetAy(50);
					break;
				case Direction_S:
					tank->SetAy(tank->GetAy() + 10);
					if (tank->GetAy() > 700) tank->SetAy(700);
					break;
				default:
					break;
				}
			}
			
			tank->Set2DPosition(tank->GetAx(), tank->GetAy());
			if (IsDie(ax, ay, tank->GetAx(), tank->GetAy(), 20))
			{
				m_isDie = 1;
				this->EndGame();
			}
			// xự kiện tank_computer bắn đạn
			if (rand() % 10 == 0) {
				auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
				auto texture = ResourceManagers::GetInstance()->GetTexture("bullet");
				auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
				std::shared_ptr<Bullet> bullet = std::make_shared<Bullet>(model, shader, texture);
				bullet->SetAx(tank->GetAx());
				bullet->SetAy(tank->GetAy());
				bullet->SetDirectionk(tank->getDirectionk());

				switch (bullet->getDirectionk())
				{
				case Direction_A:
					bullet->SetAx(bullet->GetAx() - 40);
					break;
				case Direction_D:
					bullet->SetAx(bullet->GetAx() + 40);
					break;
				case Direction_W:
					bullet->SetAy(bullet->GetAy() - 40);
					break;
				case Direction_S:
					bullet->SetAy(bullet->GetAy() + 40);
					break;
				default:
					break;
				}

				bullet->Set2DPosition(bullet->GetAx(), bullet->GetAy());
				bullet->SetSize(128, 128);
				bullet->SetType(Bullet_Computer);
				lst_bullet.push_back(bullet);
			}
			
		}	
		SetDirectionTank();
	}
}

void GSPlay::Draw()
{
	m_BackGround->Draw();
	m_tank->Draw();
	for each (std::shared_ptr<Bullet> bullet in lst_bullet) {
		bullet->Draw();
	}

	for each (std::shared_ptr<Tank> tank in lst_tank) {
		tank->Draw();
	}

	for each (std::shared_ptr<Bum> bum in lst_bum) {
		bum->Draw();
	}

	for each (std::shared_ptr<Sprite2D> wall in lst_wall) {
		wall->Draw();
	}

	for each (std::shared_ptr<GameButton> button in m_listButton) {
		button->Draw();
	}

}

void GSPlay::SetNewPostionForBullet()
{
}