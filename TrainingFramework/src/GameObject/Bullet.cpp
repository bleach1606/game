#include "Bullet.h"


Bullet::Bullet(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture)
	: Sprite2D(model, shader, texture)
{
	m_pBtClick = nullptr;
	m_isHandle = false;
}

Bullet::~Bullet()
{
}

void Bullet::SetOnClick(void(*pBtClickFun)())
{
	m_pBtClick = pBtClickFun;
}

int Bullet::GetAx() {
	return ax;
}

int Bullet::GetAy() {
	return ay;
}

int Bullet::getDirectionk() {
	return m_directionk;
}

void Bullet::SetAx(int x) {
	this->ax = x;
}

void Bullet::SetAy(int x) {
	this->ay = x;
}

void Bullet::SetDirectionk(int x) {
	this->m_directionk = x;
}

void Bullet::HandleTouchEvents(GLint x, GLint y, bool bIsPressed)
{
	m_isHandle = false;
	if ((x > m_Vec2DPos.x - m_iWidth / 2) && (x < m_Vec2DPos.x + m_iWidth / 2) && (y > m_Vec2DPos.y - m_iHeight / 2) && (y < m_Vec2DPos.y + m_iHeight / 2))
	{
		m_pBtClick();
		m_isHandle = true;
	}
}

bool Bullet::IsHandle()
{
	return m_isHandle;
}
