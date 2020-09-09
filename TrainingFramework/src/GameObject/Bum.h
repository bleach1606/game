#pragma once
#include "Sprite2D.h"

class Bum : public Sprite2D
{
public:
	Bum(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture);
	~Bum();
	void	SetOnClick(void	(*pBtClick)());
	void	HandleTouchEvents(GLint x, GLint y, bool bIsPressed);
	bool	IsHandle();
	void	SetAx(int x);
	void	SetAy(int y);
	int		GetAx();
	int		GetAy();
	void	SetFram(int k);
	int		getFram();
private:
	void	(*m_pBtClick)();
	bool	m_isHandle;
	int		m_fram, ax, ay;
};