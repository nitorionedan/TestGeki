#pragma once
#include "Counter.hpp"
#include <memory>


class Particle
{
private:
	std::unique_ptr<Counter> c_life;
	
	double x_pos, y_pos;	// ���W
	double speed;			// �����鑬��
	double ang_spd;			// ��]�̑���
	double angle;			// ��]�l
	bool   f_dead;

public:
	Particle(int PartcleLife);
	~Particle();
	void Update();
	void Draw(int &Gr_Handle);
	bool isDead();
};