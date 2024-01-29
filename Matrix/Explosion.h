#pragma once
#include <random>
#include <Windows.h>
#include "ArrayList.h"
#include "Manager.h"
#include "Figure.h"
#include "Symbol.h"

class Symbol;

//����� ������
class Explosion : public Figure
{
private:
	static std::uniform_int_distribution<> range_radius; //�������� �������� ��� ������
	unsigned short radius; //������ ������
	unsigned short radius_step; //������� ������
	ArrayList<Symbol> field; //���� ������
	COORD central_position; //����������� ������� ������

	//������� ���������� � ���� �������
	bool isElementInConsole(const COORD& element);
	//��������
	bool movement() override;
public:
	//������ ��������
	static void setRadii(const std::uniform_int_distribution<>& distrib);

	//����������� ������
	Explosion(COORD position);
	//����������� ����������
	Figure* handle() override;
};