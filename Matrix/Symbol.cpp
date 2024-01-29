#include "Symbol.h"

enum Symbol::Color //Перечисляемый тип цветов
{
	Black = 0, Blue, Green, Cyan,
	Red, Magenta, Brown, LightGray,
	DarkGray, LightBlue, LightGreen,
	LightCyan, LightRed, LightMagenta,
	Yellow, White
};

bool Symbol::random_color; //статический флаг рандомности цвета символа
std::uniform_int_distribution<> Symbol::range_ch('0', '9'); //диапазон символов линии
std::uniform_int_distribution<> Symbol::range_col(Blue, Yellow); //диапазон цветов символа

//Статическая функция установки флага рандомности цвета для всех символов
void Symbol::setRandomColor(const bool& random_col) { random_color = random_col; }

//Конструктор для символов линий
Symbol::Symbol(COORD _coordinates, const bool& line_symbol) : coordinates(_coordinates), first_symbol(line_symbol)
{
	element = range_ch(Manager::generator);
	color = line_symbol ? White : static_cast<Color>(range_col(Manager::generator));
	onDisplay();
}

//Стирание элемента строки с экрана
void Symbol::hide()
{
	SetConsoleCursorPosition(Manager::h_stdout, coordinates);
	std::cout << ' ';
}

//Вывод элемента строки на экран
void Symbol::onDisplay()
{
	if (first_symbol) {
		first_symbol = false;
		SetConsoleTextAttribute(Manager::h_stdout, (WORD)((0 << 4) | color));
		SetConsoleCursorPosition(Manager::h_stdout, coordinates);
		std::cout << element;
		color = random_color ? static_cast<Color>(range_col(Manager::generator)) : Green;
	}
	else
		SetConsoleTextAttribute(Manager::h_stdout, (WORD)((0 << 4) | color));
	SetConsoleCursorPosition(Manager::h_stdout, coordinates);
	std::cout << element;
}