#pragma once

#include "EffectTask.hpp"
#include "Counter.hpp"
#include "Vector2D.hpp"

#include <memory>
#include <array>


class ChargeEffect : public EffectTask
{
private:
	static const int ENERGY_LEN = 8;

	const int ENERGY_DIS;	// 80 // 200
	const int ENERGY_EXR;	// 10
	const int ENERGY_TIM;	// 10

public:
	ChargeEffect();

	// @param[in]	dis_		�G�l���M�[�̏o���͈́i���a�j
	// @param[in]	exrate_		�G�l���M�[�̊g�嗦�iexrate_ �` exrate_ * 2�܂ł͈̔́j
	// @param[in]	playTime	�Đ����ԁi�t���[���j
	// @param[in]	moveTime	�G�l���M�[�̕\������()
	ChargeEffect(int dis_, int exrate_, int playTime, int moveTime);
	~ChargeEffect();
	void Update() override;
	void Update(const double& PosX, const double& PosY) override;
	void Draw()	override;
	void PlayAnime(const double& PosX, const double& PosY) override;

private:
	// @brief		��������
	// @param[in]	i	�Y����
	void Move(const int& i);

	// @brief		�G�l���M�[�̃f�[�^�̏�����
	// @param[in]	i	�Y����
	void Reset(const int& i);

	bool CheckFinish();

	// �S�̂̉��o����
	std::unique_ptr<Counter>	c_play;
	
	// ���o�̒��S���W
	Vector2D center;

	// �G�l���M�[�̍��W
	std::array<Vector2D, ENERGY_LEN>	pos;

	// �G�l���M�[�̋z�����܂��܂ł̎���
	std::array<int, ENERGY_LEN>	move_time;

	// �G�l���M�[�̋z�����܂��܂ł̎���
	std::array<int, ENERGY_LEN>	move_Maxtime;

	// �G�l���M�[�ƍĐ����W�Ƃ̍ŏ��̋���
	std::array<double, ENERGY_LEN>	dis;

	// �G�l���M�[�̊g�嗦
	std::array<double, ENERGY_LEN>	exrate;

	// �G�l���M�[�̊g�嗦
	std::array<double, ENERGY_LEN>	Minexrate;

	// �G�l���M�[�̔�ԋz�����܂��p�x
	std::array<double, ENERGY_LEN>	angle;

	// �G�l���M�[���z�����܂ꂽ���ǂ���
	std::array<bool, ENERGY_LEN> isSweeped;

	double ene_rota;

	int gh_energy;

	int sh;

	// ���o���Ă��邩�H
	bool isPlay;

	static int count;
};