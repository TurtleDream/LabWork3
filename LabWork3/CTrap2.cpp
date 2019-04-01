// ������������ ���� ����������� ������ CTrap
#include "CTrap2.h"
// ������������ ���� ����������� �������������� �������
#include <math.h>

// ����������� ������ CTrap
CTrap2::CTrap2(double x, double y, double f, double r)
{
	this->x = x;
	this->y = y;
	this->f = f;
	this->r = r;
}

// ���������� ������ CTrap
CTrap2::~CTrap2()
{
}

// ����� ���������
void CTrap2::Draw(HDC dc)
{
	HPEN pen = CreatePen(PS_SOLID, 4, RGB(0, 0, 0));
	HBRUSH brush = CreateSolidBrush(RGB(0, 255, 50));

	double rDraw = 10;

	SelectObject(dc, pen);
	SelectObject(dc, brush);

	Ellipse(dc, (x- rDraw), (y - rDraw), (x + rDraw), (y + rDraw));

	pen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	brush = (HBRUSH)GetStockObject(WHITE_BRUSH);

	SelectObject(dc, pen);
	SelectObject(dc, brush);
}

// ����� ����������� �� ����
void CTrap2::Effect(CBall* ball)
{
	double xDist = this->x - ball->GetX();
	double yDist = this->y - ball->GetY();

	double xDistSqr = xDist * xDist;
	double yDistSqr = yDist * yDist;

	double distSqr = xDistSqr + yDistSqr;

	double dist = sqrt(distSqr);

	if (dist > this->r)
		return;

	if (distSqr < 0.6)
		distSqr = 0.6;

	double xCoef = (this->f * (xDist / dist)) / distSqr;
	double yCoef = (this->f * (yDist / dist)) / distSqr;

	double tmpVx = ball->GetVx();
	tmpVx -= xCoef;
	ball->SetVx(tmpVx);

	double tmpVy = ball->GetVy();
	tmpVy -= yCoef;
	ball->SetVy(tmpVy);
}