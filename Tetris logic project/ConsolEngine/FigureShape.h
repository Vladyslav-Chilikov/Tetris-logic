#pragma once

#include "BaseApp.h"

class Figure
{
	Figure(char fType);

public:
	int symbolAxxisList[4][2];

	char figureType;

	void SetFigChar(Figure F);

};