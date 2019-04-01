// «аголовочный файл определени€ класса CBallSettingsMonitor.
#include "CBallSettingsMonitor.h"
// «аголовочный файл дл€ использовани€ математических функций.
#include <math.h>

//  онструктор класса CBallSettingsMonitor.
CBallSettingsMonitor::CBallSettingsMonitor(void)
{
	this->angle = 45; // угол по умолчанию
	this->speed = 50; // скорость по умолчанию
}

// деструктор класса CBallSettingsMonitor.
CBallSettingsMonitor::~CBallSettingsMonitor(void)
{
}

// метод отрисовки.
void CBallSettingsMonitor::Draw(HDC dc)
{
	// «начение скорости нормализуетс€, чтобы при скорости 120 максимальна€ длина вектора на изображении была 30.
	double halfspeed = ((this->speed / 120) * 30) / 2;
	double rad_angle = (this->angle / 180) * 3.1415;

	double x = halfspeed * cos(rad_angle);
	double y = halfspeed * sin(rad_angle);

	Rectangle(dc, 0, 0, 30, 30);

	MoveToEx(dc, (15-x), (15-y), NULL);
	LineTo(dc, (15+x), (15+y));

	Ellipse(dc, (15 + x - 2), (15 + y - 2), (15 + x + 2), (15 + y + 2));
}

// метод увеличени€ скорости.
void CBallSettingsMonitor::SpeedUp()
{
	if (this->speed < 120)
		speed++;
}

// метод уменьшени€ скорости
void CBallSettingsMonitor::SpeedDown()
{
	if (this->speed > 10)
		speed--;
}

// ћетод увеличени€ угла направлени€.
void CBallSettingsMonitor::AngleUp()
{
	angle++;

	if (this->angle >= 360)
		angle = 0;
}

// метод уменьшени€ угла направлени€
void CBallSettingsMonitor::AngleDown()
{
	angle--;

	if (this->angle <= 0)
		angle = 360;
}

// метод расчЄта скоростей по x и по y
void CBallSettingsMonitor::GetVxVy(double& vx, double& vy)
{
	double rad_angle = (this->angle / 180) * 3.1415;

	vx = this->speed * cos(rad_angle);
	vy = this->speed * sin(rad_angle);
}