#include "Line.h"

std::uniform_int_distribution<> Line::range_pos; //Диапазон позиций линии
std::uniform_int_distribution<> Line::range_line_begin(false, true); //Диапазон 0-1 для выбора начала хода линии
std::uniform_int_distribution<> Line::range_chance(1, 1000); //Диапазон 1-1000 для вероятности
unsigned short Line::explosion_chance; //Вероятность взрыва

//Сеттер параметров линий
void Line::setLinesParameters(const unsigned short& chance)
{
	explosion_chance = chance;
	range_pos = std::uniform_int_distribution<>(0, Manager::console_size.Y - 1);
}

//Конструктор для линий
Line::Line(const std::chrono::milliseconds& line_time_point, const unsigned short& line_length, const unsigned short& line_speed) : appear_time(std::chrono::steady_clock::now() + line_time_point), length(line_length)
{ 
	speed = line_speed;
	step_time = std::chrono::milliseconds(1000 / speed);

	begin_status = range_line_begin(Manager::generator);
	position.Y = range_pos(Manager::generator);
	if (begin_status)
		position.Y++;
	position.X = Manager::console_size.X;

	dead = false;
	appear = false;
	step = 0;
}

//Это первое движение
bool Line::isItFirstMove()
{
	if ((std::chrono::steady_clock::now() >= appear_time && !appear)) {
		appear = true;
		return true;
	}
	return false;
}

//Вероятность взрыва линии
bool Line::isLineExplode() { return range_chance(Manager::generator) <= explosion_chance; }

//Движение
bool Line::movement()
{
	if (position.X < 0) {
		field.back().hide();
		field.pop_back();
		if (field.size() == 0) {
			dead = true;
			return false;
		}

		if (position.X == -1)
			field.front().onDisplay();
	}
	else {
		if (field.size() != 0)
			field.front().onDisplay();

		field.emplace_front(position, true);

		if (field.size() > length) {
			field.back().hide();
			field.pop_back();
		}
	}
	return true;
}

//Движение линии
Figure* Line::handle()
{
	Figure* explosion = nullptr;
	if (isItFirstMove())
		start_point = std::chrono::steady_clock::now();
	else if (std::chrono::steady_clock::now() < appear_time)
		return nullptr;

	if (isReadyForStep(std::chrono::steady_clock::now())) {
		
		checkStep(step);
		if (!movement()) return nullptr;

		if (isLineExplode()) {
			explosion = new Explosion(position);
			if (position.X >= 0) {
				field.front().hide();
				field.pop_front();
			}
			length--;
			if (field.size() == 0) {
				dead = true;
				return explosion;
			}
		}
		else {
			position.X--;
			if (begin_status) {
				begin_status = false;
				position.Y--;
			}
			else {
				begin_status = true;
				position.Y++;
			}
		}
	}
	return explosion;
}