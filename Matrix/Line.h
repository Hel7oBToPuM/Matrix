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

// ����� �����
class Line : public Figure
{
private:
	static std::uniform_int_distribution<> range_pos; //�������� ������� �����
	static std::uniform_int_distribution<> range_line_begin; //�������� 0-1 ��� ������ ������ ���� �����
	static std::uniform_int_distribution<> range_chance; //�������� 1-1000 ��� �����������
	static unsigned short explosion_chance; //����������� ������

	bool begin_status; //������ � ����� ������� ������ ������� (true - ������ ����, false - ����� �����)
	bool appear; //���� ������� ���������/�� ���������
	unsigned short length; //����� �����
	LinkedList<Symbol> field; //���� ��� ��������
	COORD position; //������� �������� ��������
	std::chrono::steady_clock::time_point appear_time; //����� ���������

	//��� ������ ��������
	bool isItFirstMove();
	//����������� ������ �����
	bool isLineExplode();
	//��������
	bool movement() override;
public:
	//������ ���������� �����
	static void setLinesParameters(const unsigned short& chance);
	//����������� ��� �����
	Line(const std::chrono::milliseconds& line_time_point, const unsigned short& line_length, const unsigned short& line_speed);
	//�������� �����
	Figure* handle() override;
};