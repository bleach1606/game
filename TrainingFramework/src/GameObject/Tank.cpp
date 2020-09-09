#include "Tank.h"
#include <queue>
using namespace std;

Tank::Tank(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture)
	: Sprite2D(model, shader, texture)
{
	m_pBtClick = nullptr;
	m_isHandle = false;
}

Tank::~Tank()
{
}

void Tank::RandomDir() {
	if (rand() % 5 == 0) {
		int k = rand() % 4 + 1;
		this->m_directionk = k;
	}
}

int Tank::IsDie(int x, int y, int k) {
	int ok = 0;
	if ( (x-ax)* (x - ax) + (y - ay) * (y - ay) < (k+32) * (k+32)) {
		ok = 1;
	}
	return ok;
}

void Tank::SetOnClick(void(*pBtClickFun)())
{
	m_pBtClick = pBtClickFun;
}

int Tank::GetAx() {
	return ax;
}

int Tank::GetAy() {
	return ay;
}

int Tank::getDirectionk() {
	return m_directionk;
}

void Tank::SetAx(int x) {
	this->ax = x;
}

void Tank::SetAy(int x) {
	this->ay = x;
}

void Tank::SetDirectionk(int x) {
	this->m_directionk = x;
}

void Tank::HandleTouchEvents(GLint x, GLint y, bool bIsPressed)
{
	m_isHandle = false;
	if ((x > m_Vec2DPos.x - m_iWidth / 2) && (x < m_Vec2DPos.x + m_iWidth / 2) && (y > m_Vec2DPos.y - m_iHeight / 2) && (y < m_Vec2DPos.y + m_iHeight / 2))
	{
		m_pBtClick();
		m_isHandle = true;
	}
}

bool Tank::IsHandle()
{
	return m_isHandle;
}
