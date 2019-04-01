#pragma once

// ������������ ���� ����������� ������ CBall
#include "CBall.h"

class CTrap2
{
public:
	// ������� �������
	double x, y;
	// ����������� ���������� � �������
	double f;

	//���������� �� ������, ����� �������� ����������� ������� �� ����������� (� ��������� ������� ���� ����������� ������� ��������������� �������� ����������)
	double r;

	CTrap2(double x, double y, double f, double r);
	virtual ~CTrap2(void);

	void Draw(HDC dc);
	void Effect(CBall* ball);
};