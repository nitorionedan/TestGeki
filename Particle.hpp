#pragma once
#include "Counter.hpp"
#include <memory>


class Particle
{
private:
	std::unique_ptr<Counter> c_life;
	
	double x_pos, y_pos;	// 座標
	double speed;			// 落ちる速さ
	double ang_spd;			// 回転の速さ
	double angle;			// 回転値
	bool   f_dead;

public:
	Particle(int PartcleLife);
	~Particle();
	void Update();
	void Draw(int &Gr_Handle);
	bool isDead();
};