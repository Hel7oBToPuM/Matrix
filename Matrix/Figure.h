#pragma once
#include <random>
#include <chrono>

//Абстрактный класс фигуры
class Figure
{
protected:
	bool dead; //Флаг статуса смерти
	unsigned int speed; //Скорость
	unsigned short step; //Текущий шаг
	std::chrono::milliseconds step_time; //Время на шаг
	std::chrono::steady_clock::time_point start_point; //Время начала движения

	//Пришло время двигаться
	bool isReadyForStep(const std::chrono::steady_clock::time_point& now);
	//Проверка шага
	void checkStep(unsigned short& step);
	//Движение
	virtual bool movement() = 0;
public:
	virtual ~Figure();
	//Попробовать сдвинуться
	virtual Figure* handle() = 0;
	//Геттер статуса смерти
	bool getDeadStatus();
};

#include "Manager.h"