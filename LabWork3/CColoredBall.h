#pragma once

// Заголовочный файл определения класса CBall
#include "CBall.h"

class CColoredBall : public CBall
{
	HBRUSH brush;

public:
	CColoredBall(void);
	virtual ~CColoredBall(void);

	virtual void SetColor(unsigned char r, unsigned char g, unsigned char b);

	virtual void Draw (HDC dc);
};