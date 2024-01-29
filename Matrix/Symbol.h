#pragma once
#include <iostream>
#include <random>
#include <Windows.h>
#include "Manager.h"

//����� �������
class Symbol
{
private:
	enum Color; //������������� ��� ������

	static bool random_color; //����������� ���� ����������� ����� �������
	static std::uniform_int_distribution<> range_ch; //�������� �������� �����
	static std::uniform_int_distribution<> range_col; //�������� ������ �������

	COORD coordinates; //���������� �������
	char element; //������
	Color color; //���� �������
	bool first_symbol; //������ ������ � �����

public:
//����������� ������ ����� ����������� �����
	static void setRandomColor(const bool& random_col);
//����������� ��� �������� �����
	Symbol(COORD _coordinates, const bool& line_symbol);
//����������� �� ���������
	Symbol() {};
//���������� ��� �������� �����
	~Symbol() {};
//����� �������� ������ �� �����
	void onDisplay();
//�������� �������� ������ � ������
	void hide();
};