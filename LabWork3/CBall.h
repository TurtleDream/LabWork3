#pragma once 

//Заголовочный файл, где находится описание основных функциий Windows API.
#include <Windows.h>
// Заголовочный файл, где находится подключение дополнительных библиотек для работы с графикой.
#include <windowsx.h>



class CBall
{


	double x, y;
	double vx, vy;
	double r;
	RECT bounds;// границы окна


public:
	CBall(void);
	virtual ~CBall(void);

	double GetX();
double GetY();
double GetVx();
double GetVy();
double GetR();

void SetVx(double vx);
void SetVy(double vy);

	virtual void SetParams(double x, double y, double r, double vx, double vy, RECT rect);
	virtual void Draw(HDC dc);
	void Move(DWORD delta_ticks);
	void SetBounds(RECT bnds);
	void SetColor(unsigned char r, unsigned char g, unsigned char b);

};