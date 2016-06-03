//------------------------------------------------------------------------------
/// @file
/// @brief    Piece�N���X
/// @author   PG�� ��I
///
/// @copyright  Copyright 2016 Shohei.Y
/// @attention  ���̃t�@�C���̗��p�́A������README�ɂ���
///             ���p�����ɏ]���Ă�������

//------------------------------------------------------------------------------

#pragma once

#include "EffectTask.hpp"
#include "Vector2D.hpp"
#include "Counter.hpp"

#include <array>


enum ePiece_t
{
	ePiece_SmallGray,	// �������j�Ёi�D�F�j
	ePiece_SmallCoin,	// �R�C���݂�����
	ePiece_SmallSquare,	// �����`
	ePiece_Smalls,		// ���X�i�W��ށj
	ePiece_BigNut,		// �i�b�g
	ePiece_BigPlate,	// ��
	ePiece_BigSquare,	// �����`
	ePiece_BigPlate3,
	ePiece_Bigs,		// �傫�Ȕj�Ђ���
	ePiece_Special,		// �n���o�[�K�[�A���S

	ePiece_None
};


class Piece : public EffectTask
{
private:
	static const int PIECE_ALL_NUM = 60;

public:
	Piece() : type(ePiece_None){}
	Piece(ePiece_t type_);
	~Piece();
	void Update() override;
	void Draw() override;

	// @brief		�j�Ђ��P��΂�
	// @param[in]	PosX, PosY	���W
	// @param[in]	ANGLE	��΂��p�x�i�x���@�j
	// @param[in]	VEC		��΂���
	// @param[in]	FSPEED	�R�}����̑���
	// @param[in]	SPIN	��]���鑬��
	// @param[in]	TYPE	�j�Ђ̎��
	// @param[in]	R,G,B	RGB�l�B0�ŃO���[�X�P�[��
	// @note		�W�Afalse�ł���isPlay�𒊏o�����̓Y�����ɑΉ����郁���o�ϐ��Ɉ����̒l��ݒ肷��
	// @attention	false�ł���isPlay�������ꍇ�A������
	void Play(const double& PosX, const double& PosY, const double& V_ANGLE, const double& VEC, const int& FSPEED, const double& SPIN, const double& BRAKE, int R, int G, int B);

private:
	void PlayAnime(const double& PosX, const double& PosY) override;
	
	// @brief		Draw�̒��g�̕���
	// @param[in]	i	�Y�����̔ԍ�
	void Draw_Piece(const int& i);

	// @brief		�j�Ђ̓����𐧌�
	// @param[in]	INDEX	�Y�����̔ԍ�
	// @attention	0����ALL_NUM�̒l�܂�
	void Move(const int& INDEX);

	const ePiece_t type;

	std::array<Vector2D, PIECE_ALL_NUM> pos;		// ���W
	std::array<int, PIECE_ALL_NUM> fspeed;		// �A�j���[�V�������x
	std::array<int, PIECE_ALL_NUM> red, green, blue;		// RGB�l
	std::array<int, PIECE_ALL_NUM> rand;			// �����_�����
	std::array<double, PIECE_ALL_NUM> vangle;		// ��΂��p�x
	std::array<double, PIECE_ALL_NUM> vec;		// ��΂���
	std::array<double, PIECE_ALL_NUM> angle;		// �p�x
	std::array<double, PIECE_ALL_NUM> spin;		// ��]���x
	std::array<double, PIECE_ALL_NUM> brake;		// �u���[�L
	std::array<bool, PIECE_ALL_NUM> isPlay;		// �Đ������H
	std::array<bool, PIECE_ALL_NUM> isSlow;		// ���������H
	Counter** c_play;						// �Đ�������t���[�����J�E���^�[

	int gh_small1[8],	// �D
		gh_small5[4],	// �����������`
		gh_small6[5],	// �R�C���݂�����
		gh_smalls[8],	// ���X
		gh_big1[8],		// �i�b�g
		gh_big2[14],	// �����`�P
		gh_big3[6],		// �����`
		gh_big5[14],		// �傫�Ȕj��
		gh_bigs[8],		// �傫�Ȕj�Ђ���
		gh_kit,
		gh_burger;
};