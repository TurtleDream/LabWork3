// Заголовочный файл определения класса CColoredBall
#include "CColoredBall.h"

// Конструктор класса CColoredBall
CColoredBall::CColoredBall(void)
{
	this->brush = CreateSolidBrush(RGB(0, 0, 0));
}

// Деструктор класса CColoredBall
CColoredBall::~CColoredBall(void)
{
	DeleteBrush(this->brush);
}

// Метод установления цвета
void CColoredBall::SetColor(unsigned char r, unsigned char g, unsigned char b)
{
	DeleteBrush(this->brush);

	this->brush = CreateSolidBrush(RGB(r,g,b));
}

// Метод отрисовки
void CColoredBall::Draw(HDC dc)
{
	HBRUSH oldBrush = SelectBrush(dc, this->brush);

	Ellipse(dc, (this->GetX() - this->GetR()), (this->GetY() - this->GetR()), (this->GetX() + this->GetR()), (this->GetY() + this->GetR()));

	SelectBrush(dc, oldBrush);
}