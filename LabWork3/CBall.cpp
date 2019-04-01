// ������������ ���� ����������� ������ CBall.
#include "CBall.h"

// ����������� ������ CBall.
CBall::CBall(void)
{
}

// ���������� ������ CBall.
CBall::~CBall()
{
	
}

// ������������ ���������� ������ CBall.
void CBall::SetParams(double x, double y, double r, double vx, double vy, RECT rect)
{
	this->x = x;
	this->y = y;
	this->r = r;
	this->vx = vx;
	this->vy = vy;
	this->bounds = rect;
}

// ����� ������������ ������.
void CBall::SetBounds(RECT bnds)
{
	this->bounds = bnds;
}

// ����� ��������.
void CBall::Move(DWORD delta_ticks)
{
	// ������ ������� ����� ������������� � ��������.
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

// ����� ��������� ���������� X
double CBall::GetX()
{
	return this->x;
}

// ����� ��������� ���������� Y
double CBall::GetY()
{
	return this->y;
}

// ����� ��������� �������� �� x vx
double CBall::GetVx()
{
	return this->vx;
}

// ����� ��������� �������� �� y vy
double CBall::GetVy()
{
	return this->vy;
}

// ����� ��������� ������� r
double CBall::GetR()
{
	return this->r;
}

// ����� ������������ �������� �� x vx
void CBall::SetVx(double vx)
{
	this->vx = vx;
}

// ����� ������������ �������� �� y vy
void CBall::SetVy(double vy)
{
	this->vy = vy;
}

// ����� ���������.
void CBall::Draw(HDC dc)
{

	Ellipse(dc, (x-r), (y-r), (x+r), (y+r));
	
}

// ����� ������������ ����� (������)
void CBall::SetColor(unsigned char r, unsigned char g, unsigned char b)
{

}


