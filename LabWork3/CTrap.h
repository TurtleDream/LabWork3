#pragma once

// ������������ ���� ����������� ������ CBall
#include "CBall.h"

class CTrap
{
public:
	// ������� �������
	double x, y;
	// ����������� ���������� � �������
	double f;

	//���������� �� ������, ����� �������� ����������� ������� �� ����������� (� ��������� ������� ���� ����������� ������� ��������������� �������� ����������)
	double r;

	CTrap(double x, double y, double f, double r);
	virtual ~CTrap(void);

	void Draw(HDC dc);
	void Effect(CBall* ball);
};