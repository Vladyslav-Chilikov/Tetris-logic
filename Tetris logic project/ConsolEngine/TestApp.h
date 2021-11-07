// Copyright 2009-2014 Blam Games, Inc. All Rights Reserved.

#pragma once

#include "BaseApp.h"

class TestApp : public BaseApp
{
	typedef BaseApp Parent;

	private:
		int mObj1XOld;
		int mObj1YOld;

		int mObj1X;		// координаты фрагментов фигуры
		int mObj1Y;
		int mObj2X;
		int mObj2Y;
		int mObj3X;
		int mObj3Y;
		int mObj4X;
		int mObj4Y;

		int mObjNext1X, mObjNext1Y;	// координаты фрагментов ьудущей фигуры
		int mObjNext2X, mObjNext2Y;
		int mObjNext3X, mObjNext3Y;
		int mObjNext4X, mObjNext4Y;

		int figureType;		// 1-i 2-j 3-l 4-o 5-s 6-t 7-z
		int figureTypeNext; 

		int arFullCells[15][15]; // массив данных занятого сегмента поля

		int rotationStage; // стадия поворота фигуры

		int playerScore; //счет

		float timeHolder;	// переменная таймера
		float timeFallSpeed; //скорость падения фигуры

		bool figureFallEvent; // t - фигура падает

		bool mDirection;

		void RotateFigure(); //поворот фигуры
		


	public:
		TestApp();
		virtual void KeyPressed(int btnCode);
		virtual void UpdateF(float deltaTime);
};

