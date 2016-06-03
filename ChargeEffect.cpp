#include "DxLib.h"
#include "ChargeEffect.hpp"

#include <cmath>


int ChargeEffect::count;


ChargeEffect::ChargeEffect()
	: ENERGY_DIS(80)
	, ENERGY_EXR(10)
	, ENERGY_TIM(10)
	, c_play(new Counter(100))
	, gh_energy(LoadGraph("GRAPH/GAME/Eshot/efire0.png"))
	, sh(LoadSoundMem("SOUND/SE/charge00.wav"))
	, ene_rota(0.)
	, isPlay(false)
{
	isSweeped.fill(true);
	count = 0;
}


ChargeEffect::ChargeEffect(int dis_, int exrate_, int playTime, int moveTime)
	: ENERGY_DIS(dis_)
	, ENERGY_EXR(exrate_)
	, ENERGY_TIM(moveTime)
	, c_play(new Counter(playTime))
	, gh_energy(LoadGraph("GRAPH/GAME/Eshot/efire0.png"))
	, sh(LoadSoundMem("SOUND/SE/charge00.wav"))
	, isPlay(false)
{
	isSweeped.fill(true);
}


ChargeEffect::~ChargeEffect()
{
	DeleteGraph(gh_energy);
	DeleteSoundMem(sh);
}


void ChargeEffect::Update()
{
	count++;
	ene_rota += 0.1;

	if (!isPlay)
	{
		if (!CheckFinish())
		{
			for (int i = 0; i < ENERGY_LEN; i++)
				Move(i);
		}
	}
	if (!isPlay)	return;
	// �J�E���g�_�E��------------------------------
	c_play->Update();

	//�f�[�^�X�V-----------------------------------
	for (int i = 0; i < ENERGY_LEN; i++) {
		Move(i);
	}

	//�Đ��I��-------------------------------------
	if(c_play->isLast())
	{
		c_play->Reset();
		isPlay = false;
	}
}


void ChargeEffect::Update(const double & PosX, const double & PosY)
{
	center.SetVecor2D(PosX, PosY);
	Update();
}


void ChargeEffect::Draw()
{
	if (CheckFinish())	return;

	// �_�ł����邽��
	if (count % 4 >= 2)	return;

	for (int i = 0; i < ENERGY_LEN; i++)
	{
		if (isSweeped[i])	continue;
		DrawRotaGraph(pos[i].x, pos[i].y, exrate[i], 0.0, gh_energy, true);
	}
}


void ChargeEffect::PlayAnime(const double & PosX, const double & PosY)
{
	if (isPlay && !CheckFinish())	return;
	isPlay = true;
	center.SetVecor2D(PosX, PosY);
	isSweeped.fill(false);
	PlaySoundMem(sh, DX_PLAYTYPE_BACK);

	// ���o�̂��߂̃f�[�^��������
	for (int i = 0; i < ENERGY_LEN; i++) {
		Reset(i);
	}
}

void ChargeEffect::Move(const int & i)
{
	if (isSweeped[i])	return;

	const int& T = move_Maxtime[i];
	const double& E = Minexrate[i];

	// �ړI�n�܂ň��ɐi��
	pos[i].x += std::cos(angle[i]) * (dis[i] / T);
	pos[i].y += std::sin(angle[i]) * (dis[i] / T);
//	pos[i].x += (dis[i] / T) * std::sin(ene_rota);
//	pos[i].y += (dis[i] / T) * std::cos(ene_rota);

	exrate[i] -= E / T;

	// �^�C���J�E���g
	move_time[i]--;
	if(move_time[i] == 0)
	{
		if (isPlay)
			Reset(i);
		else
			isSweeped[i] = true;
	}
}


void ChargeEffect::Reset(const int & i)
{
	pos[i].x = center.x + GetRand(200 * 2) - 200;
	pos[i].y = center.y + GetRand(200 * 2) - 200;
	dis[i] = std::pow((center.x - pos[i].x) * (center.x - pos[i].x) + (center.y - pos[i].y) + (center.y - pos[i].y), 0.5);
	angle[i] = atan2(center.y - pos[i].y, center.x - pos[i].x);
	exrate[i] = (GetRand(ENERGY_EXR) + ENERGY_EXR) / 10.0;
	Minexrate[i] = exrate[i] - 0.1;
	move_time[i] = GetRand(ENERGY_TIM) + ENERGY_TIM; // 30�`60�t���[��
	move_Maxtime[i] = move_time[i];
}


bool ChargeEffect::CheckFinish()
{
	for(auto Sweeped : isSweeped)	if (!Sweeped)	return false;

	return true;
}
