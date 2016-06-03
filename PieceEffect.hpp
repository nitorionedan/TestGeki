//------------------------------------------------------------------------------
/// @file
/// @brief    PieceEffec�N���X
/// @author   PG�� ��I
///
/// @copyright  Copyright 2016 Shohei.Y
/// @attention  ���̃t�@�C���̗��p�́A������README�ɂ���
///             ���p�����ɏ]���Ă�������

//------------------------------------------------------------------------------

#pragma once

#include "EffectTask.hpp"
#include "Counter.hpp"
#include "Vector2D.hpp"
#include "Piece.hpp"

#include <array>


enum eSpread_t
{
	// ��{�I�Ȕj��
	eSpread_SmallGrey,
	eSpread_SmallBlue,
	eSpread_SmallOrange,
	eSpread_SmallRed,
	eSpread_SmallAll,	// �����Ȃ��́i���j
	eSpread_Smalls,

	// �ł����S�~
	eSpread_BigAll,		// �����Ȃ��́i��j
	eSpread_Bigs,

	// ���̑�
	eSpread_All,		// �F��Ȃ��́i��E���j

	eSpread_None,
};


class PieceEffect : public EffectTask
{
public:
	PieceEffect();
	~PieceEffect();
	virtual void Update() override;
	virtual void Draw() override;

	// @brief		�j�Ђ������΂�
	// @param[in]	PosX, PosY	�Đ�������W
	// @param[in]	ANGLE		��Ԋp�x
	// @param[in]	kind_		�ǂ�Ȕj�Ђ��΂���
	void PlayAnime(const double& PosX, const double& PosY, const double& ANGLE, eSpread_t kind_);

private:
	virtual void PlayAnime(const double& PosX, const double& PosY){}
	void GetRadian(double* rad, const double& ANGLE);

	const double SPEED1;
	const double SPEED2;
	const double SPEED3;
	const double SPEED4;
	const double SPEED5;
	const double SPEED6;
	const double SPEED7;
	const double SPEED8;
	const double SPEED9;
	const double SPEED10;
	const double SPEED11;
	const double SPEED12;

	const double ANGLE1;
	const double ANGLE2;
	const double ANGLE3;
	const double ANGLE4;
	const double ANGLE5;
	const double ANGLE6;
	const double ANGLE7;
	const double ANGLE8;
	const double ANGLE9;
	const double ANGLE10;
	const double ANGLE11;
	const double ANGLE12;

	const double BRAKE1;
	const double BRAKE2;
	const double BRAKE3;
	const double BRAKE4;
	const double BRAKE5;
	const double BRAKE6;
	const double BRAKE7;
	const double BRAKE8;
	const double BRAKE9;
	const double BRAKE10;
	const double BRAKE11;
	const double BRAKE12;

	Piece** piece;
};