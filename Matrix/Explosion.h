#pragma once
#include <random>
#include <Windows.h>
#include "ArrayList.h"
#include "Manager.h"
#include "Figure.h"
#include "Symbol.h"

class Symbol;

//Класс взрыва
class Explosion : public Figure
{
private:
	static std::uniform_int_distribution<> range_radius; //Диапазон радиусов для взрыва
	unsigned short radius; //Радиус взрыва
	unsigned short radius_step; //Текущий радиус
	ArrayList<Symbol> field; //Поле взрыва
	COORD central_position; //Центральная позиция взрыва

	//Элемент помещается в окно консоли
	bool isElementInConsole(const COORD& element);
	//Движение
	bool movement() override;
public:
	//Сеттер радиусов
	static void setRadii(const std::uniform_int_distribution<>& distrib);

	//Конструктор взрыва
	Explosion(COORD position);
	//Попробовать сдвинуться
	Figure* handle() override;
};