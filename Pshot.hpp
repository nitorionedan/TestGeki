#pragma once

#include "Bullet.hpp"
#include "Player.hpp"
#include "Counter.hpp"
#include "Task.hpp"
#include "Vector2D.hpp"
#include "HitEffect.hpp"
#include "Effect.hpp"
#include "Bomb.hpp"

#include <array>
#include <memory>


enum eShot_Color
{
	eShot_Blue,
	eShot_Orange,
	eShot_Red,
};


class Pshot : public Task
{
public:
	Pshot::Pshot();
	Pshot::~Pshot();
	virtual void Update() override;
	virtual void Draw() override;
	void ShiftReset();

private:
	void Input();													// ���͊Ǘ�
	void ShotCount();												// �Z�~�I�[�g�A�˂̂��߂̃J�E���g�Ǘ�
	void SetFirePosition(const double X_POS, const double Y_POS);	// ���ˈʒu��ݒ�
	void Fire();													// f_exist�𗧂Ă�
	void Move();													// �������v�Z
	void HitCheck();
	void Reset();													// �e�����Z�b�g
	void SetAtk(const int Aatk, const int Batk, const int Catk);	// �U���͂�ς���
	void CopyStaticMem();

	const int SCREEN_LIMIT_XR, SCREEN_LIMIT_XL;		// ��ʂ͈̔�
	const int SCREEN_LIMIT_YT, SCREEN_LIMIT_YB;

	const double A_SPEED, B_SPEED, C_SPEED;
	const double BASE_ANGLE;
	const double ADD_ANGLE1;
	const double ADD_ANGLE2;
	const double ADD_ANGLE3;
	const double ADD_ANGLE4;
	const double ADD_ANGLE5;
	const double ADD_ANGLE6;

	const double ANGLE_L_1;
	const double ANGLE_L_2;
	const double ANGLE_L_3;
	const double ANGLE_L_4;
	const double ANGLE_L_5;
	const double ANGLE_L_6;

	const double ANGLE_R_1;
	const double ANGLE_R_2;
	const double ANGLE_R_3;
	const double ANGLE_R_4;
	const double ANGLE_R_5;
	const double ANGLE_R_6;
	
	const double ADD_FIRE_POS;
	const double ADD_FIRE_POS_Y;

	std::unique_ptr<Counter> c_shot;				// ���ˎ��ԗp�J�E���^�[
//	std::unique_ptr<HitEffect> effect;
	std::unique_ptr<Effect> effect;
	std::unique_ptr<Bomb> bomb;
	std::array<Bullet*, 20>	Ashot;					// ��
	std::array<Bullet*, 30>	Bshot;					// ��
	std::array<Bullet*, 30>	Cshot;					// ��

	std::array<int, 3> hg;							// �ԁA�A��
	std::array<int, 3> hg2;							// �ԁA�A��(����ver)
	int hg_fire;
	int hs_shot;									// ���ʉ��n���h��
	int hs_hit;
	int shiftLevel;									// �V�t�g���x��
	double mPlayer_x, mPlayer_y;					// ���@�̍��W
	std::array<double, 3> x_pos, y_pos, angle;		// ���W�A��]�l
	std::array<double, 2> x_fire;
	double y_fire;
	bool isShot;									// ���˒����H
	bool isShotNext;								// �������˂��邩�H

	static std::array<Vector2D, 20>	s_Apos;
	static std::array<Vector2D, 30>	s_Bpos;
	static std::array<Vector2D, 30>	s_Cpos;
};