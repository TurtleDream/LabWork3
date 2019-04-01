#pragma once

// Заголовочный файл, в котором находится описание основных функций Windows API.
#include <Windows.h>

class CBallSettingsMonitor
{
	double angle;
	double speed;

public:
	CBallSettingsMonitor(void);
	~CBallSettingsMonitor(void);

	void Draw(HDC dc);
	void SpeedUp();
	void SpeedDown();
	void AngleUp();
	void AngleDown();
	void GetVxVy(double& vx, double& vy);
};