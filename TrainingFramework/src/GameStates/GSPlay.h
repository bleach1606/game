#pragma once
#include "gamestatebase.h"
#include "Bullet.h"
#include "Tank.h" 
#include "Bum.h"
#include "soloud.h"
#include "soloud_wav.h"
#include "GameButton.h"

class Sprite2D;
class Sprite3D;
class Text;

enum Direction
{
	Direction_Stop = 0,
	Direction_W,
	Direction_A,
	Direction_S,
	Direction_D,
};

enum Bullet_Fly
{
	Bullet_Computer = 0,
	Bullet_Player = 1,
};

class GSPlay :
	public GameStateBase
{
public:
	GSPlay();
	~GSPlay();

	void Init();
	void Exit();

	void Pause();
	void Resume();
	void EndGame(int k);

	void InitTank(int k);

	void HandleEvents();
	void HandleKeyEvents(int key, bool bIsPressed);

	void HandleTouchEvents(int x, int y, bool bIsPressed);
	void Update(float deltaTime);
	void Draw();
	void SetDirectionTank();


	void SetNewPostionForBullet();

private:
	int mp[100][100], ax, ay, direction, old_direction, m_isDie, m_IsPause;
	float currentTime;
	std::shared_ptr<Sprite2D> m_BackGround;
	std::shared_ptr<Text>  m_score;
	std::shared_ptr<Sprite2D> m_tank;
	std::list<std::shared_ptr<Bullet>> lst_bullet;
	std::list<std::shared_ptr<Tank>> lst_tank;
	std::list<std::shared_ptr<Bum>> lst_bum;
	std::list<std::shared_ptr<Sprite2D>> lst_wall;
	std::list<std::shared_ptr<GameButton>>	m_listButton;
	SoLoud::Soloud soloud; // Engine core
	SoLoud::Wav sample;    // One sample
	std::shared_ptr<Text>  m_Text_gameName;
};