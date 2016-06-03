#pragma once

#include "Bullet.hpp"
#include "Counter.hpp"
#include "Task.hpp"
#include "Effect.hpp"

#include <array>
#include <memory>


enum AttackState { eAtk1, eAtk2 };	// �U���̎��


/// BossA����U���J�n����̌o�ߎ��Ԃ�A�c��HP�̏��𓾂Đ؂�ւ��Ă���
class Eshot : public Task
{
public:
	Eshot();
	~Eshot();
	virtual void Update() override;
	virtual void Draw() override;
	void SetAttackState(AttackState state);
	void SetFirePos();
	void Fire();

	void Move();

	static void GoFire1();

	AttackState atkState;										// �U�����

private:
	static const double SC_LIMIT_XL;							// ��ʓ��{�[�_�[
	static const double SC_LIMIT_XR;
	static const double SC_LIMIT_YT;
	static const double SC_LIMIT_YB;

	const int		A_INTERVAL;									// �V���b�g�`�̍U���Ԋu
	const int		A_FIRE_NUM;									// �V���b�g�`�̔��ː�
	const double	A_SPEED;									// �`�̑���
	const double	A_BASE_ANGLE;								// �`�̊�ƂȂ�p�x

	void Reset();												// �e�������ɓ��������Ƃ��ɌĂ΂��
	bool isOverLimit(const double X_POS, const double Y_POS);	// ��ʊO�֏o�����H

	std::unique_ptr<Effect> effect;
	std::unique_ptr<Counter> c_atk1, c_atk2;					// ���̍U��������܂ł̑ҋ@����
	std::unique_ptr<Counter> c_fire1, c_fire2;					// �U�����̃J�E���g�i�e�̊Ԋu���󂯂�p�j
	std::array<Bullet*, 64>	shotA;								// 16�����֔�΂��e

	int hg_shotA, hg_shotB;										// �摜�p�n���h��
	int hg_fireA, hg_fireB;										// ���˂����Ƃ��Ɍ����̃A���i�����ł���I�j
	int hs_shotA;												// ���p�n���h��
	int loopCount;
	double speed;
	std::array<double, 2>	x_fireA, y_fireA;
	
	static bool s_isFire1, s_isFire2;
};