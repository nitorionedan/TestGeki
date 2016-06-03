#pragma once

#include "DxLib.h"

#undef max
#undef min

template<typename T>
class Range
{
public:
	Range(){}

	Range(T min, T max) : min_(min), max_(max){
		assert(min_ <= max_);
	}

	// �͈͓����H
	bool isInside(T value) const{
		return (min_ <= value) && (value <= max_);
	}

/*
	// �͈͓��ɃN�����v����
	T clamp(T value) const{
		return ::clamp(value, min_, max_); // �O���̊֐�
	}

	// �͈͓��Ń��b�v�A���E���h����
	T wrap(T value) const{
		return ::wrap(value, min_, max_); // �O���̊֐�
	}
*/

	// �����l�̎擾
	T min() const{
		return min_;
	}

	// ����l�̎擾
	T max() const{
		return max_;
	}

private:
	T min_; // �����l
	T max_; // ����l
};