#pragma once
#include "gamestatebase.h"
#include "Bullet.h"

class Sprite2D;
class Sprite3D;
class Text;

enum Direction
{
	Direction_Stop = 0,
	Direction_W,
	Direction_S,
	Direction_A,
	Direction_D,
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

	void InitTank(int k, int f);

	void HandleEvents();
	void HandleKeyEvents(int key, bool bIsPressed);

	void HandleTouchEvents(int x, int y, bool bIsPressed);
	void Update(float deltaTime);
	void Draw();

	
	void SetNewPostionForBullet();

private:
	int mp[20][20], ax, ay, direction;
	float currentTime;
	std::shared_ptr<Sprite2D> m_BackGround;
	std::shared_ptr<Text>  m_score;
	std::shared_ptr<Sprite2D> m_tank, m_Weapon;
	std::list<std::shared_ptr<Bullet>> lst_bullet;
};

