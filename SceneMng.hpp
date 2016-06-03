#pragma once

#include "ISceneChanger.hpp"
#include "BaseScene.hpp"


class SceneMng : public ISceneChanger, Task
{
public:
	SceneMng   ();
	~SceneMng();
	virtual void Update() override; // �X�V
	virtual void Draw  () override; // �`��

	// ���� nextScene �ɃV�[����ύX����
	void ChangeScene(eScene NextScene) override;

private:
	BaseScene* mScene;     // �V�[���Ǘ��ϐ� (���C�ӂ̃^�C�~���O�Ń������̊m�ہA��������܂�)
	eScene     mNextScene; // ���̃V�[���Ǘ��ϐ�
};