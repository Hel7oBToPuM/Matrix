#pragma once
#include <iostream>
#include <random>
#include <Windows.h>
#include "Manager.h"

//Класс символа
class Symbol
{
private:
	enum Color; //Перечисляемый тип цветов

	static bool random_color; //Статический флаг рандомности цвета символа
	static std::uniform_int_distribution<> range_ch; //Диапазон символов линии
	static std::uniform_int_distribution<> range_col; //Диапазон цветов символа

	COORD coordinates; //Координаты символа
	char element; //Символ
	Color color; //Цвет символа
	bool first_symbol; //Первый символ в линии

public:
//Статический сеттер флага рандомности цвета
	static void setRandomColor(const bool& random_col);
//Конструктор для символов линий
	Symbol(COORD _coordinates, const bool& line_symbol);
//Конструктор по умолчанию
	Symbol() {};
//Деструктор для символов линий
	~Symbol() {};
//Вывод элемента строки на экран
	void onDisplay();
//Стирание элемента строки с экрана
	void hide();
};