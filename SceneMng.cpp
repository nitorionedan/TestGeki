#include "DxLib.h"

#include "Config.hpp"
#include "Game.hpp"
#include "GameOver.hpp"
#include "Menu.hpp"
#include "SceneMng.hpp"
#include "Another.hpp"
#include "Keyboard.hpp"
#include "DebugMode.hpp"


SceneMng::SceneMng() :	mNextScene(eScene_None){
	mScene = static_cast<BaseScene*> (new Game(this));	// �ŏ��̃V�[��
}


SceneMng::~SceneMng()
{
	delete mScene;
}


//�X�V
void SceneMng::Update()
{			
	DebugMode::Update();

	if (mNextScene != eScene_None)								// ���̃V�[�����Z�b�g����Ă�����
	{    
		delete mScene;											// ���݂̃V�[���̏I�����������s
		switch (mNextScene)										// �V�[���ɂ���ď����𕪊�
		{
		case eScene_Menu:										// ���̉�ʂ����j���[�Ȃ�
			mScene = static_cast<BaseScene*> (new Menu(this));	// ���j���[��ʂ̃C���X�^���X�𐶐�����
			break;												// �ȉ���
		case eScene_Game:
			mScene = static_cast<BaseScene*> (new Game(this));
			break;
		case eScene_Config:
			mScene = static_cast<BaseScene*> (new Config(this));
			break;
		case eScene_Another:
			mScene = static_cast<BaseScene*> (new Another(this));
			break;
		case eScene_GameOver:
			mScene = static_cast<BaseScene*> (new GameOver(this));
			break;
		}
		mNextScene = eScene_None;								// ���̃V�[�������N���A
	}
	mScene->Update();											// �V�[���̍X�V

	// DEBUG ONLY
	if (Keyboard_Get(KEY_INPUT_F1) == 1)	DebugMode::SwitchTest();
}


//�`��
void SceneMng::Draw()
{
	DebugMode::Draw();
	mScene->Draw();
}


// ���� nextScene �ɃV�[����ύX����
void SceneMng::ChangeScene(eScene NextScene){	mNextScene = NextScene;	}	// ���̃V�[�����Z�b�g