#pragma once
#include <memory>
#include "Counter.hpp"


/*
	任意の特定の時間の処理クラス
	名づけに困る！
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