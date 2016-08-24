#pragma once

#include "Task.hpp"

/// nullptrの代わり
class NullTask : public Task
{
public:
	NullTask(){}
	~NullTask(){}
	virtual void Update() override {}	// 何もしない
	virtual void Draw() override {}		// 何もしない
};