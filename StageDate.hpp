#pragma once
#include "Stage.hpp"


class StageData
{
private:
	char*   name = "stage_data.dat"; // �ǂ̃X�e�[�W����n�߂邩...
	FILE*   fp;
	errno_t error;

public:
	StageData();
	~StageData();

	void SetFirstStage(eStage estage); // �ŏ��Ɏn�߂�X�e�[�W��ݒ�config�Őݒ肳�ꂽ���̂��瓐���Ă���
	void LoadStage(); // �R���e�B�j���[����Ƃ��g���܂�
	void SaveStage(); // �R���e�B�j���[����Ƃ��g���܂�
};