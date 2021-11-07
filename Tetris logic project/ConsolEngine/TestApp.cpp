// Copyright 2009-2014 Blam Games, Inc. All Rights Reserved.

#include <time.h>
#include "TestApp.h"



TestApp::TestApp() : Parent(40, 40)
{
	mDirection = true;
	mObj1XOld = 18;
	mObj1YOld = 10;

	mObj1X = mObj2X = mObj3X = mObj4X = 25;  
	mObj1Y = mObj2Y = mObj3Y = mObj4Y = 11;

	mObjNext1X = mObjNext2X = mObjNext3X = mObjNext4X = 10; 
	mObjNext1Y = mObjNext2Y = mObjNext3Y = mObjNext4Y = 5;

	// random figure generator
	figureType = rand() % 7 + 1;	
	figureTypeNext = rand() % 7 + 1; 

	arFullCells[16][16] = {0};	

	timeHolder = 0.0;
	timeFallSpeed = 0.8;

	playerScore = 0;

	rotationStage = 1; 

	figureFallEvent = true;	// фигура падает = 1

	
}

void TestApp::KeyPressed(int btnCode)
{
	if (btnCode == 32) //w 119 ----------- замена на пробел
		RotateFigure();

	if (btnCode == 80) //s 115
		timeFallSpeed = 0.0;

	else if (btnCode == 75) //a 97
		    { if ( !((arFullCells[mObj1X - 19 - 1][mObj1Y - 11] == 1) 
				|| (arFullCells[mObj2X - 19 - 1][mObj2Y - 11] == 1) 
				|| (arFullCells[mObj3X - 19 - 1][mObj3Y - 11] == 1) 
				|| (arFullCells[mObj4X - 19 - 1][mObj4Y - 11] == 1)) 
				 )
			mObj1X--;
			}
		 else if (btnCode == 77) //d 100
			{
			 if (!((arFullCells[mObj1X - 19 + 1][mObj1Y - 11] == 1)
			 || (arFullCells[mObj2X - 19 + 1][mObj2Y - 11] == 1)
			 || (arFullCells[mObj3X - 19 + 1][mObj3Y - 11] == 1)
			 || (arFullCells[mObj4X - 19 + 1][mObj4Y - 11] == 1))
			)
				 mObj1X++;
			}
  // ограничения перемещения
	 if (mObj1X < 19) mObj1X = 19; else if (mObj1X >= 34) mObj1X = 33;
	 if (mObj2X < 19 || mObj3X < 19 || mObj4X < 19) mObj1X = 20; else if (mObj2X >= 34 || mObj3X >= 34 || mObj4X >= 34) mObj1X = 32;
	 if (mObj2X < 18 || mObj3X < 18 || mObj4X < 18) mObj1X = 21; else if (mObj2X >= 35 || mObj3X >= 35 || mObj4X >= 35) mObj1X = 31;
	 if (mObj2X < 17 || mObj3X < 17 || mObj4X < 17) mObj1X = 22; else if (mObj2X >= 36 || mObj3X >= 36 || mObj4X >= 36) mObj1X = 30;

	 if (mObj1Y < 11) mObj1Y = 11; else if (mObj1Y >= 26) mObj1Y = 25;
	 if (mObj2Y < 11) mObj2Y = 11; else if (mObj2Y >= 26) mObj2Y = 25;
	 if (mObj3Y < 11) mObj3Y = 11; else if (mObj3Y >= 26) mObj3Y = 25;
	 if (mObj4Y < 11) mObj4Y = 11; else if (mObj4Y >= 26) mObj4Y = 25;
}
// изменение стадии поворота
void TestApp::RotateFigure()
{
	if (rotationStage != 4)
		rotationStage++;
	else
		rotationStage = 1;
}

void TestApp::UpdateF(float deltaTime)
{	// границы поля
	for (int row = 0; row <= 16; row++)
	{
		SetChar(mObj1XOld + row, mObj1YOld, L'_');
		SetChar(mObj1XOld + row, mObj1YOld + 16, L'_');
	}
	for (int row = 1; row <= 15; row++)
	{
		SetChar(mObj1XOld, mObj1YOld + row, L'|');
		SetChar(mObj1XOld + 16, mObj1YOld + row, L'|');
	}
	//заполнение поля
	for (int rowX = 1; rowX <= 15; rowX++)
		for (int rowY = 1; rowY <= 15; rowY++)
		{
			SetChar(mObj1XOld + rowX, mObj1YOld + rowY, L'.');
		}

	for (int rowX = 1; rowX <= 10; rowX++)		// бэкграунт для следующей фигуры
		for (int rowY = 1; rowY <= 15; rowY++)
		{
			SetChar(5 + rowX, 2 + rowY, L' ');
		}
	
	//заполнение полных "ячеек"
	for (int rowY = 0; rowY <= 14; rowY++)
	{
		for (int rowX = 0; rowX <= 14; rowX++)
		{
			if (arFullCells[rowX][rowY] == 1)
			{
				SetChar(rowX + 19, rowY + 11, L'o');
			}
		}
	}
	  // удаление полных строк / перемещение строк
	int arrayCounter = 0;
	for (int rowY = 0; rowY <= 14; rowY++)
	{
		arrayCounter = 0;
		for (int rowX = 0; rowX <= 14; rowX++)
		{
			if (arFullCells[rowX][rowY] == 1) arrayCounter++;
			if (arrayCounter == 15)
			{
				playerScore++;
				for (int index = 0; index <= 14; index++)
					for (int iYCounter = rowY; iYCounter > 0; iYCounter--)
					{

						arFullCells[index][iYCounter] = arFullCells[index][iYCounter - 1];

					}
			}
				
		}
	}

	// Вывод счета
	char charScore100 = '0';
	char charScore10 = '0';
	char charScore1 = '0';

	int temp = playerScore % 100;
	int ones = temp % 10;
	int tens = temp - 5;
	tens /= 10;
	int hundreds = playerScore - temp;
	hundreds /= 100;

	if (playerScore > 0) charScore1 = '0' + ones;
	if (tens > 0) charScore10 = '0' + tens;
	if (hundreds > 0) charScore100 = '0' + hundreds;

	SetChar(7, 30, charScore100);
	SetChar(8, 30, charScore10);
	SetChar(9, 30, charScore1);

	SetChar(0, 5, L'N');	// Next:
	SetChar(1, 5, L'e');
	SetChar(2, 5, L'x');
	SetChar(3, 5, L't');
	SetChar(4, 5, L':');

	SetChar(0, 30, L'S');	// Score:
	SetChar(1, 30, L'c');
	SetChar(2, 30, L'o');
	SetChar(3, 30, L'r');
	SetChar(4, 30, L'e');
	SetChar(5, 30, L':');

	// генератор новой фигуры
	if (!figureFallEvent)
	{
		figureType = figureTypeNext;
		figureTypeNext = rand() % 7 + 1;
		timeFallSpeed = 0.8;
		figureFallEvent = true;
		mDirection = true;
	}		// "столкновение" с заполненным сегментом
			if(  ( arFullCells[mObj1X - 19][mObj1Y - 11 + 1] == 1 ) 
			|| ( arFullCells[mObj2X - 19][mObj2Y - 11 + 1] == 1 ) 
			|| ( arFullCells[mObj3X - 19][mObj3Y - 11 + 1] == 1 ) 
			|| ( arFullCells[mObj4X - 19][mObj4Y - 11 + 1] == 1 ) 
				) 
			{ 
				mDirection = false; figureFallEvent = false;
				//добавление 0 на поле
				arFullCells[mObj1X - 19][mObj1Y - 11] = 1;
				arFullCells[mObj2X - 19][mObj2Y - 11] = 1;
				arFullCells[mObj3X - 19][mObj3Y - 11] = 1;
				arFullCells[mObj4X - 19][mObj4Y - 11] = 1;
				mObj1X = mObj2X = mObj3X = mObj4X = 25;
				mObj1Y = mObj2Y = mObj3Y = mObj4Y = 11;
			}

	if (mDirection)
	{
		timeHolder += deltaTime;
		if (timeHolder >= timeFallSpeed)
		{
			mObj1Y++; mObj2Y++; mObj3Y++; mObj4Y++; timeHolder = 0.0;
		}
		if (mObj1Y == 25 || mObj2Y == 25 || mObj3Y == 25 || mObj4Y == 25)
		{
			mDirection = false; figureFallEvent = false;
			//добавление 0 на поле
			arFullCells[mObj1X - 19][mObj1Y - 11] = 1;
			arFullCells[mObj2X - 19][mObj2Y - 11] = 1;
			arFullCells[mObj3X - 19][mObj3Y - 11] = 1;
			arFullCells[mObj4X - 19][mObj4Y - 11] = 1;
			mObj1X = mObj2X = mObj3X = mObj4X = 25; 
			mObj1Y = mObj2Y = mObj3Y = mObj4Y = 11;
			rotationStage = 1;
		}
	}
		{
			 SetChar(mObj1X, mObj1Y, L'o'); // интерпретация типа фигуры
			 if (figureType == 1) // 1-i
			 { 
				 if ( rotationStage == 1 || rotationStage == 3)
				 {
				 mObj2X = mObj3X = mObj4X = mObj1X; 
				 mObj2Y = mObj1Y + 1;
				 mObj3Y = mObj1Y + 2;
				 mObj4Y = mObj1Y + 3;
				 }
				 else if (rotationStage == 2 || rotationStage == 4)
					{
					 mObj2Y = mObj3Y = mObj4Y = mObj1Y;
					 mObj2X = mObj1X + 1;
					 mObj3X = mObj1X - 1;
					 mObj4X = mObj1X - 2;
					}
			 }
			 else if (figureType == 2) //2 - j
			 {
				 if (rotationStage == 1)
				 {
					 mObj2X = mObj1X;
					 mObj3X = mObj2X + 1;
					 mObj4X = mObj3X + 1;
					 mObj2Y = mObj3Y = mObj4Y = mObj1Y + 1;
				 }
				 else if (rotationStage == 2)
					{
					 mObj2X = mObj3X = mObj4X = mObj1X - 1;
					 mObj2Y = mObj1Y;
					 mObj3Y = mObj2Y + 1;
					 mObj4Y = mObj3Y + 1;
					}
				 else if (rotationStage == 3)
				 {
					 mObj2X = mObj1X; 
					 mObj3X = mObj1X - 1;
					 mObj4X = mObj3X - 1;
					 mObj3Y = mObj4Y = mObj1Y;
					 mObj2Y = mObj1Y + 1;
				 }
				 else if (rotationStage == 4)
				 {
					 mObj2X = mObj3X = mObj1X;
					 mObj4X = mObj1X - 1;
					 mObj2Y = mObj1Y + 1;
					 mObj3Y = mObj4Y =mObj2Y + 1;
				 }
			 }
			 else if (figureType == 3) //3-l
			 {
				 if (rotationStage == 1)
				 {
					 mObj2X = mObj1X;
					 mObj3X = mObj2X - 1;
					 mObj4X = mObj3X - 1;
					 mObj2Y = mObj3Y = mObj4Y = mObj1Y + 1;
				 }
				 if (rotationStage == 2)
				 {
					 mObj2X = mObj3X = mObj1X;
					 mObj4X = mObj1X + 1;
					 mObj2Y = mObj1Y + 1;
					 mObj3Y = mObj4Y = mObj2Y + 1;
				 }
				 if (rotationStage == 3)
				 {
					 mObj3X = mObj1X + 1;
					 mObj4X = mObj3X + 1;
					 mObj2X = mObj1X;
					 mObj3Y = mObj4Y = mObj1Y;
					 mObj2Y = mObj1Y + 1;
				 }
				 if (rotationStage == 4)
				 {
					 mObj2X = mObj3X = mObj1X;
					 mObj4X = mObj1X - 1;
					 mObj4Y = mObj1Y;
					 mObj2Y = mObj1Y + 1;
					 mObj3Y =  mObj2Y + 1;
				 }
			
			 }
			 else if (figureType == 4) // 4-o
			 {
				 mObj2X = mObj4X = mObj1X + 1;
				 mObj3X = mObj1X;
				 mObj2Y = mObj1Y;
				 mObj3Y = mObj4Y = mObj1Y + 1;

			
			 }
			 else if (figureType == 5) //5-s
			 {
				 if (rotationStage == 1 || rotationStage == 3)
				 {
					 mObj2X = mObj1X + 1;
					 mObj3X = mObj1X;
					 mObj4X = mObj1X - 1;
					 mObj2Y = mObj1Y;
					 mObj3Y = mObj4Y = mObj1Y + 1;
				 }
				 if (rotationStage == 2 || rotationStage == 4)
				 {
					 mObj2X = mObj1X;
					 mObj4X = mObj3X = mObj2X + 1;
					 mObj4Y = mObj3Y + 1;
					 mObj3Y = mObj2Y = mObj1Y + 1;

				 }
			 }
			 else if (figureType == 6) //6-t
			 {
				 if (rotationStage == 1 )
				 {
					 mObj2X = mObj1X + 1;
					 mObj3X = mObj1X - 1;
					 mObj4X = mObj1X;
					 mObj2Y = mObj3Y = mObj1Y;
					 mObj4Y = mObj1Y + 1;
				 }
				 if (rotationStage == 2)
				 {
					 mObj2X = mObj4X = mObj1X;
					 mObj3X = mObj1X - 1;
					 mObj2Y = mObj1Y - 1;
					 mObj3Y = mObj1Y;
					 mObj4Y = mObj1Y + 1;
				 }
				 if (rotationStage == 3)
				 {
					 mObj2X = mObj1X + 1;
					 mObj3X = mObj1X - 1;
					 mObj4X = mObj1X;
					 mObj2Y = mObj3Y = mObj1Y;
					 mObj4Y = mObj1Y - 1;
				 }
				 if (rotationStage == 4)
				 {
					 mObj2X = mObj4X = mObj1X;
					 mObj3X = mObj1X + 1;
					 mObj2Y = mObj1Y - 1;
					 mObj3Y = mObj1Y;
					 mObj4Y = mObj1Y + 1;
				 }
			 }
			 else if (figureType == 7) //7-z
			 {
				 if (rotationStage == 1 || rotationStage == 3)
				 {
					 mObj2X = mObj1X - 1;
					 mObj3X = mObj1X;
					 mObj4X = mObj1X + 1;
					 mObj2Y = mObj1Y;
					 mObj3Y = mObj4Y = mObj1Y + 1;
				 }
				 if (rotationStage == 2 || rotationStage == 4)
				 {
					 mObj2X = mObj1X;
					 mObj4X = mObj3X = mObj2X - 1;
					 mObj3Y = mObj2Y = mObj1Y + 1;
					 mObj4Y = mObj3Y + 1;
				 }

				 
			 }
			 SetChar(mObj2X, mObj2Y, L'o');
			 SetChar(mObj3X, mObj3Y, L'o');
			 SetChar(mObj4X, mObj4Y, L'o');
			 if (figureTypeNext == 1) // 1-i
			 {
				 mObjNext2X = mObjNext3X = mObjNext4X = mObjNext1X;
				 mObjNext2Y = mObjNext1Y + 1;
				 mObjNext3Y = mObjNext1Y + 2;
				 mObjNext4Y = mObjNext1Y + 3;
			 }
			 else if (figureTypeNext == 2) //2 - j
			 {
				 mObjNext2X = mObjNext1X;
				 mObjNext3X = mObjNext2X + 1;
				 mObjNext4X = mObjNext3X + 1;
				 mObjNext2Y = mObjNext3Y = mObjNext4Y = mObjNext1Y + 1;
			 }
			 else if (figureTypeNext == 3) //3-l
			 {
				 mObjNext2X = mObjNext1X;
				 mObjNext3X = mObjNext2X - 1;
				 mObjNext4X = mObjNext3X - 1;
				 mObjNext2Y = mObjNext3Y = mObjNext4Y = mObjNext1Y + 1;
			 }
			 else if (figureTypeNext == 4) // 4-o
			 {
				 mObjNext2X = mObjNext4X = mObjNext1X + 1;
				 mObjNext3X = mObjNext1X;
				 mObjNext2Y = mObjNext1Y;
				 mObjNext3Y = mObjNext4Y = mObjNext1Y + 1;
			 }
			 else if (figureTypeNext == 5) //5-s
			 {
					 mObjNext2X = mObjNext1X + 1;
					 mObjNext3X = mObjNext1X;
					 mObjNext4X = mObjNext1X - 1;
					 mObjNext2Y = mObjNext1Y;
					 mObjNext3Y = mObjNext4Y = mObjNext1Y + 1;
			 }
			 else if (figureTypeNext == 6) //6-t
			 {
					 mObjNext2X = mObjNext1X + 1;
					 mObjNext3X = mObjNext1X - 1;
					 mObjNext4X = mObjNext1X;
					 mObjNext2Y = mObjNext3Y = mObjNext1Y;
					 mObjNext4Y = mObjNext1Y + 1;
			 }
			 else if (figureTypeNext == 7) //7-z
			 {
					 mObjNext2X = mObjNext1X - 1;
					 mObjNext3X = mObjNext1X;
					 mObjNext4X = mObjNext1X + 1;
					 mObjNext2Y = mObjNext1Y;
					 mObjNext3Y = mObjNext4Y = mObjNext1Y + 1;
			 }
			 SetChar(mObjNext1X, mObjNext1Y, L'o');
			 SetChar(mObjNext2X, mObjNext2Y, L'o');
			 SetChar(mObjNext3X, mObjNext3Y, L'o');
			 SetChar(mObjNext4X, mObjNext4Y, L'o');
		}

		if (mObj1X < 19) mObj1X = 19; else if (mObj1X >= 34) mObj1X = 33;
		if (mObj2X < 19 || mObj3X < 19 || mObj4X < 19) mObj1X = 20; else if (mObj2X >= 34 || mObj3X >= 34 || mObj4X >= 34) mObj1X = 32;
		if (mObj2X < 18 || mObj3X < 18 || mObj4X < 18) mObj1X = 21; else if (mObj2X >= 35 || mObj3X >= 35 || mObj4X >= 35) mObj1X = 31;
		if (mObj2X < 17 || mObj3X < 17 || mObj4X < 17) mObj1X = 22; else if (mObj2X >= 36 || mObj3X >= 36 || mObj4X >= 36) mObj1X = 30;
	}

