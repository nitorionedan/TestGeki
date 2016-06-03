#include "DxLib.h"

#include "Title.hpp"
#include <algorithm>

#undef max
#undef min


Title::Title() : 
	Y_MIN(150.0)
{
	hg_title	= LoadGraph("GRAPH/MENU/title.png");
	hs_intro	= LoadSoundMem("SOUND/SE/intro.mp3");
	x			= 320.0;
	y			= 640.0;
	speed		= 6.3;		// 4.25
	isStop		= false;
}


Title::~Title()
{
	DeleteGraph(hg_title);
	DeleteSoundMem(hs_intro);
}

// �^�C�g�����C�Y�C��
void Title::Update()
{
	if (isStop)	return;

	speed -= 0.04;									// �W���W���Ɋ�Ɍ���
	y = std::max(y, Y_MIN);							// ���傤�ǂ����ʒu�Ŏ~�߂�
	if (y == Y_MIN)
	{
		PlaySoundMem(hs_intro, DX_PLAYTYPE_BACK);
		isStop = true;								// �ړI�̈ʒu�Œ�~
	}
	if ( ! isStop )	y -= speed;						// �^�C�g�����~�܂��Ă��Ȃ���Ώオ��
}


void Title::Draw()
{
	DrawRotaGraph(x, y, 2.0, 0.0, hg_title, true);
}