#pragma once
#include <random>
#include <chrono>

//����������� ����� ������
class Figure
{
protected:
	bool dead; //���� ������� ������
	unsigned int speed; //��������
	unsigned short step; //������� ���
	std::chrono::milliseconds step_time; //����� �� ���
	std::chrono::steady_clock::time_point start_point; //����� ������ ��������

	//������ ����� ���������
	bool isReadyForStep(const std::chrono::steady_clock::time_point& now);
	//�������� ����
	void checkStep(unsigned short& step);
	//��������
	virtual bool movement() = 0;
public:
	virtual ~Figure();
	//����������� ����������
	virtual Figure* handle() = 0;
	//������ ������� ������
	bool getDeadStatus();
};

#include "Manager.h"