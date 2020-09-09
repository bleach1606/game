#include "Bum.h"


Bum::Bum(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture)
	: Sprite2D(model, shader, texture)
{
	m_pBtClick = nullptr;
	m_isHandle = false;
}

Bum::~Bum()
{
}

void Bum::SetOnClick(void(*pBtClickFun)())
{
	m_pBtClick = pBtClickFun;
}

int Bum::GetAx() {
	return ax;
}

int Bum::GetAy() {
	return ay;
}

int Bum::getFram() {
	return m_fram;
}

void Bum::SetAx(int x) {
	this->ax = x;
}

void Bum::SetAy(int x) {
	this->ay = x;
}

void Bum::SetFram(int x) {
	this->m_fram = x;
}

void Bum::HandleTouchEvents(GLint x, GLint y, bool bIsPressed)
{
	m_isHandle = false;
	if ((x > m_Vec2DPos.x - m_iWidth / 2) && (x < m_Vec2DPos.x + m_iWidth / 2) && (y > m_Vec2DPos.y - m_iHeight / 2) && (y < m_Vec2DPos.y + m_iHeight / 2))
	{
		m_pBtClick();
		m_isHandle = true;
	}
}

bool Bum::IsHandle()
{
	return m_isHandle;
}
