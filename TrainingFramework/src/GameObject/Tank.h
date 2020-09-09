#pragma once
#include "Sprite2D.h"

class Tank : public Sprite2D
{
public:
	Tank(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture);
	~Tank();
	void	SetOnClick(void	(*pBtClick)());
	void	HandleTouchEvents(GLint x, GLint y, bool bIsPressed);
	bool	IsHandle();
	void	SetAx(int x);
	void	SetAy(int y);
	int		GetAx();
	int		GetAy();
	void	SetDirectionk(int k);
	int		getDirectionk();
	void	RandomDir();
	int		IsDie(int x, int y, int k);
private:
	void	(*m_pBtClick)();
	bool	m_isHandle;
	int		m_directionk, ax, ay;
};