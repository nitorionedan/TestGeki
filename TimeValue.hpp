#pragma once
#include <memory>
#include "Counter.hpp"


/*
	�C�ӂ̓���̎��Ԃ̏����N���X
	���Â��ɍ���I
*/
class TimeValue
{
private:
	std::unique_ptr<Counter> c_time;

private:
	TimeValue();

public:
	TimeValue(int time);
	~TimeValue();
	void GetTimeValue(double* value, double time, double delta);
};