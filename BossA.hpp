#pragma once

#include "DxLib.h"

#include "BossTask.hpp"
#include "Counter.hpp"
#include "Task.hpp"
#include "EShot03.hpp"

#include <memory>


enum eBossA_state
{
	eBossA_Start,
	eBossA_Normal,
	eBossA_Weak,
	eBossA_Dead,
	eBossA_End,
};


class BossA : public BossTask
{
public:
	BossA();
	~BossA();

	void Update() override;
	void Draw() override;

	// @brief		�����蔻��
	// @param[in]	ColX, ColY	�����郂�m�̍��W
	// @param[in]	DamagePoint	�_���[�W�l
	// @attention	�~�`�Ɠ_�̓����蔻�����
	bool HitCheck(const double& ColX, const double& ColY, const int& DamagePoint) override;
	void GetPosition(double* x, double *y);
	
	void Start_Update();
	void Normal_Update();
	void Weak_Update();
	void Dead_Update();
	void End_Update();

	// static ----------------
	static VECTOR GetPos();
	static int GetTime();
	static bool IsDead();
	static void Damage(const int& point);

	static const float	HIT_RANGE;

	static bool		isExist;

private:
	// @brief		�{�X�̓�����ω�������
	// @param[in]	state_	�����̎��
	static void ChangeState(eBossA_state state_);
	static bool isFine();		// ���C�ł����[�I�H
	void HitCheck();

	// @brief		��ʊO�ɏo����
	// @out			��ʊO�Ȃ�true�A��ʓ��Ȃ�false��Ԃ�
	bool isOverLimit();	// �o�Ă܂����[�I�H
	
	static const float	SC_LIMIT_XL, SC_LIMIT_XR;	// ��ʓ��{�[�_�[
	static const float	SC_LIMIT_YT, SC_LIMIT_YB;
	static const int MAX_HP;
	const float SPEED;

	std::unique_ptr<Counter>	c_starting;
	std::unique_ptr<Counter>	c_end;
	std::unique_ptr<Counter>	c_atk1;
	std::unique_ptr<EShot03>	shot3;

	VECTOR	mPos;							// ���f���̃��[���h���W
	VECTOR	rota;							// ���f���̉�]�l
	VECTOR	startPos;						// �X�N���[���ƃ��[���h���W�̐���
	int		hm;								// ���f�����O�f�[�^�p�n���h��
	int		hg_shield;						// �V�[���h
	int		hs_big;							// ���e
	int		hs_exp;							// �唚��
	int		in_time, stop_time, out_time;	// �o��A��~�A�ޏ�̎���
	int		big_time;
	float	targetX, targetY;				// �ړI�n
	float	angle;							// �̓�����̕����p
	bool	isMove;							// �U���J�n���Ă��邩�H
	bool	isEnd;							// �ޏꂵ�����H

	// static -----------------------------
	static eBossA_state state;
	static VECTOR	pos;					// ���f���̃X�N���[�����W
	static int		hp;			// �̗�
	static int		time;		// �����Ă��鎞��
	static int		hs_break;						// �V�[���h�j��
	static bool		isDead;		// ���񂾂��H
	static bool		isHit;
	static bool		isWeak;
};
// EOF