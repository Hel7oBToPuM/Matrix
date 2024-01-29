#pragma once
#include <iostream>
#include <random>
#include <chrono>
#include <Windows.h>
#include "LinkedList.h"
#include "Symbol.h"
#include "Line.h"
#include "Figure.h"

class Line;
class Symbol;
class Explosion;

//Класс менеджера приложения
class Manager
{
private:
	static std::uniform_int_distribution<> time_range; //Диапазон точек времени для линий
	const static std::chrono::seconds appearance_tact; //Такт появления линий
	static std::random_device seed; //Сид для рандома

	//Получить размер окна
	static COORD getWindowSize();
	//Скрыть курсор консоли
	static void hideConsoleCursor();

	unsigned short frequency; //Частота появления линий
	unsigned short line_speed; //Скорость линии
	unsigned short line_length; //Длина линии
	unsigned short chance; //вероятность взрыва линии
	unsigned short min_radius; //миниальный радиус взрыва
	unsigned short max_radius; //максимальный радиус взрыва
	bool epilepsy; //Флаг эпилепсии
	LinkedList <Figure*> field; //Поле линий
	std::chrono::steady_clock::time_point start; //время старта работы программы

	//Получение от пользователя флага эпилепсии
	bool getValidFlag(const std::string& request);
	//Получение от пользователя параметра
	unsigned short getValidProperty(const std::string& request, const unsigned short& min, const unsigned short& max);
	//Подготовка
	void preparation();
	//Булевая функция проверки условия
    bool isItTimeForAppearance(const std::chrono::steady_clock::time_point& now, bool& first_second);
public:
	const static COORD console_size; //Размеры консоли
	const static HANDLE h_stdout; //Дескриптор потока вывода
	static std::mt19937 generator; //Генератор рандомных чисел

	//Конструктор менеджера
	Manager();
	//Работа программы
	void run();
	//Получить параметры от пользователя
	void getParametersFromUser();
	
};