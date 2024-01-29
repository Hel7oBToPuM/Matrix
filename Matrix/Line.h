#pragma once
#include <chrono>
#include <Windows.h>
#include <random>
#include "LinkedList.h"
#include "Manager.h"
#include "Figure.h"
#include "Explosion.h"

class Symbol;
class Explosion;

// Класс линии
class Line : public Figure
{
private:
	static std::uniform_int_distribution<> range_pos; //Диапазон позиций линии
	static std::uniform_int_distribution<> range_line_begin; //Диапазон 0-1 для выбора начала хода линии
	static std::uniform_int_distribution<> range_chance; //Диапазон 1-1000 для вероятности
	static unsigned short explosion_chance; //Вероятность взрыва

	bool begin_status; //Задает в какую сторону пойдут символы (true - сверху вниз, false - снизу вверх)
	bool appear; //Флаг статуса появилась/не появилась
	unsigned short length; //Длина линии
	LinkedList<Symbol> field; //Поле для символов
	COORD position; //Позиция крайнего элемента
	std::chrono::steady_clock::time_point appear_time; //Время появления

	//Это первое движение
	bool isItFirstMove();
	//Вероятность взрыва линии
	bool isLineExplode();
	//Движение
	bool movement() override;
public:
	//Сеттер параметров линий
	static void setLinesParameters(const unsigned short& chance);
	//Конструктор для линий
	Line(const std::chrono::milliseconds& line_time_point, const unsigned short& line_length, const unsigned short& line_speed);
	//Движение линии
	Figure* handle() override;
};