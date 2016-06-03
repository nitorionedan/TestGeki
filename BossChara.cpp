//------------------------------------------------------------------------------
/// @file
/// @brief    BossChara.hpp�̎���
/// @author   PG�� ��I
///
/// @copyright  Copyright 2016 Shohei.Y
/// @attention  ���̃t�@�C���̗��p�́A������README�ɂ���
///             ���p�����ɏ]���Ă�������

//------------------------------------------------------------------------------

#include "BossChara.hpp"
#include "NullBoss.hpp"
#include "BossA.hpp"



BossChara::BossChara(BossTask* mBoss_)
	: mBoss(mBoss_)
{
}


BossChara::~BossChara(){
	delete mBoss;
}


void BossChara::Update(){
	mBoss->Update();
}


void BossChara::Draw(){
	mBoss->Draw();
}


bool BossChara::HitCheck(const double& ColX, const double& ColY, const int& DamagePoint)
{
	const bool& IS_HIT = mBoss->HitCheck(ColX, ColY, DamagePoint);
	return  IS_HIT ? true : false;
}


void BossChara::Start(eBoss_num num)
{
	delete mBoss;
	switch (num)
	{
	case eBoss_A:		mBoss = new BossA;	break;
	case eBoss_B:		break;
	case eBoss_C:		break;
	case eBoss_D:		break;
	case eBoss_E:		break;
	case eBoss_F:		break;
	case eBoss_G:		break;
	case eBoss_None:	mBoss = new NullBoss;	break;
	default:			mBoss = new NullBoss;	break;
	}
}