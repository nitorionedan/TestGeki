#pragma once

#include "Task.hpp"

/// nullptr�̑���
class NullTask : public Task
{
public:
	NullTask(){}
	~NullTask(){}
	virtual void Update() override {}	// �������Ȃ�
	virtual void Draw() override {}		// �������Ȃ�
};