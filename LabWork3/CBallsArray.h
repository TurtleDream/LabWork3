#pragma once

// ������������ ���� ����������� ������ CBall.
#include "CBall.h"

// ������������ ���� ����������� ������ CBall.
#include "CColoredBall.h"

// ������������ ���� ����������� ������ CTrap
#include "CTrap.h"
#include "CTrap2.h"

class CBallsArray
{
	CBall* *balls;
	int count;
	int max_balls;
	double gF;

public:
	CBallsArray(int max_balls);
	virtual ~CBallsArray(void);
	CTrap* trap;// ��������� �� �������������� �������
	CTrap2* trap2;
	CBall* Add();
	void Draw(HDC dc);
	void Move(DWORD delta_ticks);
	void SetBounds(RECT bnds);
	void SetGravityFactor(double gF);
	

	CColoredBall* AddColoredBall();
};