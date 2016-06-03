#pragma once

#include "Task.hpp"
#include "ISceneChanger.hpp"


//�V�[���̊��N���X
class BaseScene : public Task
{
protected:
	ISceneChanger* mSceneChanger;	//�N���X���L���ɃV�[���؂�ւ���`����C���^�[�t�F�C�X

public:
	BaseScene(ISceneChanger* changer);
	virtual ~BaseScene(){}
	virtual void Initialize() override {}	//�������������I�[�o�[���C�h
	virtual void Finalize() override {}		//�I���������I�[�o�[���C�h
	virtual void Update() override {}		//�X�V�������I�[�o�[���C�h
	virtual void Draw() override {}			//�`�揈�����I�[�o�[���C�h
};