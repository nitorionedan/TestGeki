#pragma once


#include "BaseScene.hpp"
#include "ISceneChanger.hpp"


class GameOver : public BaseScene
{
public:
	GameOver::GameOver(ISceneChanger* changer);
	~GameOver();
	virtual void Update() override;     //�X�V�������I�[�o�[���C�h
	virtual void Draw() override;       //�`�揈�����I�[�o�[���C�h

private:
	GameOver();

	int gh;
	int time;

	// �t�F�[�h�C��
	int time_in;

	// �t�F�[�h�A�E�g
	int time_out;
};