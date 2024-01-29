#include "Explosion.h"

std::uniform_int_distribution<> Explosion::range_radius; //Диапазон радиусов для взрыва

//Сеттер радиусов
void Explosion::setRadii(const std::uniform_int_distribution<>& distrib) { range_radius = distrib; }

//Конструктор взрыва
Explosion::Explosion(COORD position) : central_position(position)
{
	speed = 2;
	step_time = std::chrono::milliseconds(1000 / 2);
	step = 0;
	radius = range_radius(Manager::generator);
	radius_step = 1;
	dead = false;
	start_point = std::chrono::steady_clock::now();
}

//Элемент помещается в окно консоли
bool Explosion::isElementInConsole(const COORD& element) { return (element.X >= 0 && element.X <= Manager::console_size.X) && (element.Y >= 0 && element.Y <= Manager::console_size.Y); }

//Движение
bool Explosion::movement()
{
	COORD element{ central_position.X, central_position.Y - radius_step };
	for (size_t i = 0; i < 4 * radius_step; i++) {
		if (isElementInConsole(element))
			field.emplace_back(element, false);
		if (i < radius_step) {
			element.X++;
			element.Y++;
		}
		else if (i < 2 * radius_step) {
			element.X--;
			element.Y++;
		}
		else if (i < 3 * radius_step) {
			element.X--;
			element.Y--;
		}
		else {
			element.X++;
			element.Y--;
		}
	}
	radius_step++;
	return true;
}

//Попробовать сдвинуться
Figure* Explosion::handle()
{
	if (isReadyForStep(std::chrono::steady_clock::now())) {
		for (size_t i = 0; i < field.size(); i++)
			field[i].hide();
		field.clear();
		if (radius_step > radius) {
			dead = true;
			return nullptr;
		}
		checkStep(step);
		movement();
	}
	return nullptr;
}
