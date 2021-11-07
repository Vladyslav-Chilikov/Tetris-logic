

#include "FigureShape.h"
#include "BaseApp.h"

Figure::Figure(char fType)
{
	figureType = fType;

	int symbolAxxis[4][2] = {0};

	switch (fType)
	{
	case 'o': 
	{
		symbolAxxis[1][0] = symbolAxxis[0][0] + 1;
		symbolAxxis[2][1] = symbolAxxis[0][0] + 1;
		symbolAxxis[3][0] = symbolAxxis[3][1] = symbolAxxis[0][0] + 1; 
	}; break;
		
	case'z': 
	{
		symbolAxxis[1][0] = symbolAxxis[0][0] + 1; 
		symbolAxxis[3][0] = symbolAxxis[3][1] = symbolAxxis[0][0] + 1;
		symbolAxxis[3][0] = symbolAxxis[0][0] + 1; symbolAxxis[3][1] = symbolAxxis[0][0] + 2;
	}; break;
	case'l': 
	{	
		symbolAxxis[1][1] = symbolAxxis[0][0] + 1;
		symbolAxxis[2][1] = symbolAxxis[1][1] + 1;
		symbolAxxis[3][1] = symbolAxxis[2][1] + 1;
	}; break;
	case'j': {

	}; break;
	case't': {

	}; break;
	case's': {

	}; break;
	case'i': {

	}; break;
	default: 
		break;
	}

}

void Figure::SetFigChar(Figure F)
{
	SetChar(F.symbolAxxisList[0][0], F.symbolAxxisList[0][1], L'O');
	SetChar(F.symbolAxxisList[1][0], F.symbolAxxisList[1][1], L'O');
	SetChar(F.symbolAxxisList[2][0], F.symbolAxxisList[2][1], L'O');
	SetChar(F.symbolAxxisList[3][0], F.symbolAxxisList[3][1], L'O');
};