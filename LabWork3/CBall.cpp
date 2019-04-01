// Заголовочный файл определения класса CBall.
#include "CBall.h"

// Конструктор класса CBall.
CBall::CBall(void)
{
}

// Деструктор класса CBall.
CBall::~CBall()
{
	
}

// Установление параметров класса CBall.
void CBall::SetParams(double x, double y, double r, double vx, double vy, RECT rect)
{
	this->x = x;
	this->y = y;
	this->r = r;
	this->vx = vx;
	this->vy = vy;
	this->bounds = rect;
}

// Метод установления границ.
void CBall::SetBounds(RECT bnds)
{
	this->bounds = bnds;
}

// Метод движения.
void CBall::Move(DWORD delta_ticks)
{
	// Расчёт времени между перемещениями в секундах.
	double s_delta = ((double)delta_ticks) / 1000.0;

	if ((this->x >= (bounds.right - r)) && (this->vx > 0))
		this->vx = -(this->vx);
	if ((this->x <= r) && (this->vx < 0))
		this->vx = -(this->vx);

	if((this->y >= (bounds.bottom - r)) && (this->vy > 0))
		this->vy = -(this->vy);
	if((this->y <= r) && (this->vy < 0))
		this->vy = -(this->vy);

	double dx = vx * s_delta;
	double dy = vy * s_delta;

	this->x += dx;
	this->y += dy;
}

// Метод получения координаты X
double CBall::GetX()
{
	return this->x;
}

// Метод получения координаты Y
double CBall::GetY()
{
	return this->y;
}

// метод получения скорости по x vx
double CBall::GetVx()
{
	return this->vx;
}

// метод получения скорости по y vy
double CBall::GetVy()
{
	return this->vy;
}

// метод получения радиуса r
double CBall::GetR()
{
	return this->r;
}

// метод установления скорости по x vx
void CBall::SetVx(double vx)
{
	this->vx = vx;
}

// метод установления скорости по y vy
void CBall::SetVy(double vy)
{
	this->vy = vy;
}

// Метод отрисовки.
void CBall::Draw(HDC dc)
{

	Ellipse(dc, (x-r), (y-r), (x+r), (y+r));
	
}

// метод установления цвета (пустой)
void CBall::SetColor(unsigned char r, unsigned char g, unsigned char b)
{

}


