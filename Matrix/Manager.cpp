#include "Manager.h"

const HANDLE Manager::h_stdout = GetStdHandle(STD_OUTPUT_HANDLE); //���������� ������ ������
std::uniform_int_distribution<> Manager::time_range(1, 999); //�������� ����� ������� ��� �����
const COORD Manager::console_size = getWindowSize(); //������� �������
const std::chrono::seconds Manager::appearance_tact(1); //���� ��������� �����
std::random_device Manager::seed; //��� ��� �������
std::mt19937 Manager::generator; //��������� ��������� �����

//����������� ���������
Manager::Manager()
{
	std::cout << "_______________________________________________________| MATRIX |_______________________________________________________\n" <<
		         "_______________________| THIS PROGRAM IMITATES THE MATRIX EFFECT FROM THE MOVIE OF THE SAME NAME |______________________\n\n\n\n";
}

void Manager::getParametersFromUser()
{
	frequency = getValidProperty("Enter frequency of appearance of lines (1-30): ", 1, 30);
	line_speed = getValidProperty("Enter speed of lines (1-30): ", 1, 30);
	line_length = getValidProperty("Enter length of lines (1-30): ", 1, 30);
	chance = getValidProperty("Enter chance of exploding lines (1-1000): ", 1, 1000);
	min_radius = getValidProperty("Enter minimal radius of explosion (1-10): ", 1, 10);
	max_radius = getValidProperty("Enter maximal radius of explosion (1-10): ", 1, 10);
	epilepsy = getValidFlag("Do you want to enable epilepsy mode? (Y/N): ");
}

//��������� �� ������������ ����� ���������
bool Manager::getValidFlag(const std::string& request)
{
	char answer;
	while (true) {
		std::cout << request;
		std::cin >> answer;

		std::cin.ignore(1000, '\n');
		if (std::cin.gcount() > 1)
			continue;

		if (answer == 'Y' || answer == 'y')
			return true;
		else if (answer == 'N' || answer == 'n')
			return false;
	}
}

//��������� �� ������������ ���������
unsigned short Manager::getValidProperty(const std::string& request, const unsigned short& min, const unsigned short& max)
{
	int property;
	while (true) {
		std::cout << request;
		std::cin >> property;

		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(1000, '\n');
			continue;
		}
		std::cin.ignore(1000, '\n');
		if (std::cin.gcount() > 1) 
			continue;

		if (property >= min && property <= max) {
			if (request == "Enter maximal radius of explosion (1-10): ") {
				if (property >= min_radius)
					return property;
				else
					std::cout << "Maximal radius is lower then minimal!\n";
			}
			else
				return property;
		}
	}
}

//������ ���������
void Manager::run()
{
	preparation();
	bool first_second = true;
	while (true) {
		if (isItTimeForAppearance(std::chrono::steady_clock::now(), first_second)) {
			start = std::chrono::steady_clock::now();
			for (size_t i = 0; i < frequency; i++)
				field.push_front(new Line(std::chrono::milliseconds(time_range(generator)), line_length, line_speed));
		}

		for (auto it = field.begin(); it != field.end(); it++) {
			Figure* figure = (*it)->handle();
			if (figure != nullptr)
				field.push_front(figure);
		}

		field.remove_if([](Figure* figure) { 
			bool dead = figure->getDeadStatus();
			if (dead) 
				delete figure;
			return dead; });
	}
}

//�������� ������� ����� �������
bool Manager::isItTimeForAppearance(const std::chrono::steady_clock::time_point& now, bool& first_second)
{
	if (now - start >= appearance_tact || first_second) {
		if (first_second)
			first_second = false;
		return true;
	}
	else
		return false;
}

//����������
void Manager::preparation()
{
	system("cls");
	hideConsoleCursor();
	generator.seed(seed());
	Line::setLinesParameters(chance);
	Symbol::setRandomColor(epilepsy);
	Explosion::setRadii(std::uniform_int_distribution<>(min_radius, max_radius));
}

//�������� ������ ����
COORD Manager::getWindowSize()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	GetConsoleScreenBufferInfo(h_stdout, &csbi);
	COORD console_size { csbi.srWindow.Right, csbi.srWindow.Bottom };
	return console_size;
}

//������ ������ �������
void Manager::hideConsoleCursor()
{
	CONSOLE_CURSOR_INFO cursorInfo;

	GetConsoleCursorInfo(h_stdout, &cursorInfo);
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(h_stdout, &cursorInfo);
}