/*
	������������������������������������������������������������������������������������������������������������������������
	�������������������������������������������������������������A����������������������������������������������������������
	������������������������������������������������������������������������������������������������������������������������
	���������������������������������ʂ��悢�B������������������������������������������������������������������������������
	������������������������������������������������������������������������������������������������������������������������

	�@�@�@�@�@�@�����@�@���������@���@�@���@�������@�������@�@���������@���@�@�@���@�@�������@���@�@�@���@�@����
	�@�@�@�@�@���@�@�@�@���@�@�@�@���@���@�@�@���@�@���@�@���@���@�@�@�@�����@�@���@���@�@�@�@���@�@�@���@���@�@��
	�@�@�@�@�@���@�����@�������@�@�����@�@�@�@���@�@�������@�@�������@�@���@���@���@�@�����@�@�����������@��������
	�@�@�@�@�@���@�@���@���@�@�@�@���@���@�@�@���@�@���@�@���@���@�@�@�@���@�@�����@�@�@�@���@���@�@�@���@���@�@��
	�@�@�@�@�@�@�����@�@���������@���@�@���@�������@���@�@���@���������@���@�@�@���@�������@�@���@�@�@���@���@�@�� 68k

�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�`�@��D���Ȓ��A��68k�̂��߂Ɂ@�`												  
�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@
	 ������������������������������������������������������������������������������������������������������������������������
	 �������������ˌ���������������������������������������������������������������������������������������������������������
	 ������������������������������������������������������������������������������������������������������������������������

     // �ǂ����Ɂu���v�u�A�v�u�ˁv���B��Ă����I�T���Ă݂悤�I
*/
#include "DxLib.h"

#include "Keyboard.hpp"
#include "SceneMng.hpp"
#include "DebugMode.hpp"

#include <memory>
#include <time.h>


static int  FrameStartTime;			// 60fps�Œ��p
static int  FPS;
static bool ScSizeFrag = false;		// ��ʃ��[�h�ύX�p
static bool quit       = false;		// �����I���t���O

void QuitGame();					// �Q�[���I���`�B�֐�

void message_box()
{
	int flag;

	flag = MessageBox(
		NULL,
		TEXT("�t���X�N���[�����[�h�ŋN�����܂����H\n�iF5�L�[�ł��ύX�ł��܂��B�j"),
		TEXT("�X�N���[���ݒ�"),
		MB_YESNOCANCEL | MB_ICONQUESTION);
	
	if (flag == IDNO)
	{
		ScSizeFrag = true;
//		SetUseBackBufferTransColorFlag(true); // �S���������t���O
	}
	if (flag == IDCANCEL)	QuitGame();
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	message_box();																				// �E�B���h�E�X�^�C������
	SetGraphMode(640, 480, 32), ChangeWindowMode(ScSizeFrag), DxLib_Init();						// �E�B���h�E�����ݒ�(VGA),DxLib�N��
	SetDrawScreen(DX_SCREEN_BACK);																// ����ʏ���
	SetMainWindowText("���A��");																// �^�C�g����ݒ�
	SetChangeScreenModeGraphicsSystemResetFlag(FALSE);											// ��ʃ��[�h�ύX��A�f�ރ����������Z�b�g���Ȃ�
	SetEmulation320x240(TRUE);																	// 320x240�̉𑜓x�ɂ���
	SetWaitVSyncFlag(FALSE);																	// ���������M����҂��Ȃ�
	FrameStartTime = GetNowCount();																// �J�n���Ԃ�ݒ�
	FPS = 60;
	std::unique_ptr<SceneMng> sceneMng(new SceneMng);											// �V�[���Ǘ�
	SRand((unsigned)time(NULL));																// �����V�[�h
	LoadPauseGraph("GRAPH/Cover.png");															// ��A�N�e�B�u��Ԏ��̉摜

	// �Q�[��--------------------------------------------------------------------------------------
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0 && !quit)
	{
		while (GetNowCount() - FrameStartTime < 1000 / FPS) {}									// 1/60 �b�܂ő҂�
		FrameStartTime = GetNowCount();															// ���݂̃J�E���g��ۑ�

		sceneMng->Update();																		// ���݂̃V�[���f�[�^���X�V
		Keyboard_Update();																		// �L�[���̓f�[�^�X�V

		if (Keyboard_Get(KEY_INPUT_ESCAPE) == 1)	break;										// [Esc]�ŋ^�������I��
		if (Keyboard_Get(KEY_INPUT_F5) == 1)		ChangeWindowMode(ScSizeFrag = !ScSizeFrag);	// ��ʃ��[�h�ύX
		if (Keyboard_Get(KEY_INPUT_F) == 1)	FPS = 30;											// �������
		if (Keyboard_Get(KEY_INPUT_G) == 1)	FPS = 60;											// ����

		sceneMng->Draw();																		// ���݂̃V�[����`��
		DebugMode::Draw();
	}
	LoadPauseGraph(NULL);
	DxLib_End();																				// �c�w���C�u�����g�p�̏I������
	return 0;																					// �\�t�g�̏I�� 
}


void QuitGame(){
	quit = true;
}