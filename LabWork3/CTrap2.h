#pragma once

// «аголовочный файл определени€ класса CBall
#include "CBall.h"

class CTrap2
{
public:
	// ѕозици€ ловушки
	double x, y;
	// коэффициент прит€жени€ к ловушке
	double f;

	//рассто€ние от центра, после которого воздействие ловушки не наблюдаетс€ (в остальных случа€х сила воздействи€ обратно пропорциональна квадрату рассто€ни€)
	double r;

	CTrap2(double x, double y, double f, double r);
	virtual ~CTrap2(void);

	void Draw(HDC dc);
	void Effect(CBall* ball);
};