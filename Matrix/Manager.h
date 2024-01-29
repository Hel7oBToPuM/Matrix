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

//����� ��������� ����������
class Manager
{
private:
	static std::uniform_int_distribution<> time_range; //�������� ����� ������� ��� �����
	const static std::chrono::seconds appearance_tact; //���� ��������� �����
	static std::random_device seed; //��� ��� �������

	//�������� ������ ����
	static COORD getWindowSize();
	//������ ������ �������
	static void hideConsoleCursor();

	unsigned short frequency; //������� ��������� �����
	unsigned short line_speed; //�������� �����
	unsigned short line_length; //����� �����
	unsigned short chance; //����������� ������ �����
	unsigned short min_radius; //���������� ������ ������
	unsigned short max_radius; //������������ ������ ������
	bool epilepsy; //���� ���������
	LinkedList <Figure*> field; //���� �����
	std::chrono::steady_clock::time_point start; //����� ������ ������ ���������

	//��������� �� ������������ ����� ���������
	bool getValidFlag(const std::string& request);
	//��������� �� ������������ ���������
	unsigned short getValidProperty(const std::string& request, const unsigned short& min, const unsigned short& max);
	//����������
	void preparation();
	//������� ������� �������� �������
    bool isItTimeForAppearance(const std::chrono::steady_clock::time_point& now, bool& first_second);
public:
	const static COORD console_size; //������� �������
	const static HANDLE h_stdout; //���������� ������ ������
	static std::mt19937 generator; //��������� ��������� �����

	//����������� ���������
	Manager();
	//������ ���������
	void run();
	//�������� ��������� �� ������������
	void getParametersFromUser();
	
};