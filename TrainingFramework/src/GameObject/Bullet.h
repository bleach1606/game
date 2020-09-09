#pragma once
#include "Sprite2D.h"

class Bullet : public Sprite2D
{
public:
	Bullet(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture);
	~Bullet();
	void	SetOnClick(void	(*pBtClick)());
	void	HandleTouchEvents(GLint x, GLint y, bool bIsPressed);
	bool	IsHandle();
	void	SetAx(int x);
	void	SetAy(int y);
	int		GetAx();
	int		GetAy();
	void	SetType(int t);
	int		GetType();
	void	SetDirectionk(int k);
	int		getDirectionk();
private:
	void	(*m_pBtClick)();
	bool	m_isHandle;
	int		m_directionk, ax, ay, type;
};