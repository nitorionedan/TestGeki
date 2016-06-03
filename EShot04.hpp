#pragma once

#include "ShotTask.hpp"
#include "Vector2D.hpp"
#include "Effect.hpp"

#include <array>
#include <memory>


class EShot04 : public ShotTask
{
public:
	EShot04();
	~EShot04();
	void Update(const double& PosX, const double& PosY) override;
	void Draw() override;

	// @brief					���ˁi1���j
	// @param[in]	vec_speed	�i�ޑ��x
	// @param[in]	vec_angle	�i�ފp�x
	void Fire(const double& SPEED, const double& ANGLE) override;
	void Fire(const double& PosX, const double& PosY, const double& SPEED, const double& ANGLE) override;


	// @brief					�����蔻��
	// @param[in]	ColX, ColY	�Փ˂��镨�̂̍��W
	// @param[in]	ColR		�Փ˂��镨�̂̓�����ό`
	// @out						�����������ǂ���
	bool IsHit(const double& ColX, const double& ColY, const double& ColR) override;

private:
	// @param[in]	id	�Y�����ԍ�
	void Move(const int& id);

	const int ALL_FRAME_NUM;	// �A�j���[�V�����̑�����
	const int FRAME_TIME;		// �P�R�}�̕\�����ԁi�t���[�����j
	const int HIT_RANGE;		// ������͈�
	static const int ALL_NUM = 30;

	int gh[10];
	std::unique_ptr<Effect> effect;
	std::array<int, ALL_NUM> time;			// �o�ߎ���
	std::array<Vector2D, ALL_NUM> pos;		// ���W
	std::array<double, ALL_NUM> vspeed;		// �e�̑���
	std::array<double, ALL_NUM> vangle;		// �i�ފp�x
	std::array<double, ALL_NUM> ang;		// �i�ފp�x
	std::array<double, ALL_NUM> rad;		// �摜�̉�]�l
	std::array<double, ALL_NUM> rota;		// ������]�l
	std::array<double, ALL_NUM> isExist;	// ���݂��Ă��邩�H
};

// EOF