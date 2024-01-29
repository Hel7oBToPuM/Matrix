#include "Figure.h"

//������ ����� ���������
bool Figure::isReadyForStep(const std::chrono::steady_clock::time_point& now) { return now >= start_point + step_time * step; }

//�������� ����
void Figure::checkStep(unsigned short& step)
{
	if (step != speed - 1)
		step++;
	else {
		start_point = std::chrono::steady_clock::now() + step_time + std::chrono::milliseconds(1000 % speed);
		step = 0;
	}
}

Figure::~Figure()
{
}

//������ ������� ������
bool Figure::getDeadStatus() { return dead; }