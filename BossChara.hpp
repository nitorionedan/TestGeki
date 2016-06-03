//------------------------------------------------------------------------------
/// @file
/// @brief    BossChara�N���X
/// @author   PG�� ��I
///
/// @copyright  Copyright 2016 Shohei.Y
/// @attention  ���̃t�@�C���̗��p�́A������README�ɂ���
///             ���p�����ɏ]���Ă�������

//------------------------------------------------------------------------------

#pragma once

#include "BossTask.hpp"


enum eBoss_num
{
	eBoss_A,
	eBoss_B,
	eBoss_C,
	eBoss_D,
	eBoss_E,
	eBoss_F,
	eBoss_G,

	eBoss_None,
};


class BossChara
{
public:
	BossChara(BossTask* mBoss_);
	~BossChara();
	void Update();
	void Draw();

	// @brief		�w����W�Ƃ̓����蔻��
	// @param[in]	ColX, ColY	�Փ˂��镨�̂̍��W
	// @param[in]	DamagePoint	�_���[�W�l
	bool HitCheck(const double& ColX, const double& ColY, const int& DamagePoint);
	
	// @brief		�{�X��o�ꂳ����
	// @param[in]	�o�ꂳ����{�X�̎��
	void Start(eBoss_num num);

private:
	BossChara(){}
	BossTask* mBoss;
};
