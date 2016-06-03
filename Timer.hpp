#pragma once
#include <algorithm>

#undef max
#undef min

/*--------------------------------------

	Timer�N���X
	�@�\�F��莞�Ԃ̂��鏈����������

--------------------------------------*/
class Timer
{
private:
	double nowTime_;   // ���݂̎���
	double limitTime_; // ��������

public:
	Timer(double limitTime) : nowTime_(0), limitTime_(limitTime)
	{}

	void Update(double deltaTime){
		nowTime_ = std::min(nowTime_ + deltaTime, limitTime_);
	}

	void Reset() {
		nowTime_ = 0;
	}

	bool isTimeout() const {
		return nowTime_ >= limitTime_;
	}
};