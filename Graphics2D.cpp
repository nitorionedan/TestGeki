//------------------------------------------------------------------------------
/// @file
/// @brief    Graphics2D.hpp�̎���
/// @author   PG�� ��I
///
/// @copyright  Copyright 2016 Shohei.Y
/// @attention  ���̃t�@�C���̗��p�́A������README�ɂ���
///             ���p�����ɏ]���Ă�������

//------------------------------------------------------------------------------

#include "DxLib.h"

#include "Graphics2D.hpp"
#include "Keyboard.hpp"
#include "Game.hpp"

#include <cmath>
#include <algorithm>

#undef max
#undef min


Graphics2D::Graphics2D()
	: FRAME_NUM(0)
	, gh(nullptr)
{
}


Graphics2D::Graphics2D(int Gr_Handle[], int num)
	: FRAME_NUM(num)
	, count(0)
{
	gh = new int[FRAME_NUM];

	for (int i = 0; i < FRAME_NUM; i++)
		gh[i] = Gr_Handle[i];
}


Graphics2D::~Graphics2D()
{
	delete[] gh;
}


void Graphics2D::Raster_Scroll(const int &X, const int &Y, const int &Gr_Handle, double Cycle,  double Shake)
{
	int Width = 0, Height = 0;	// �摜�̉����Əc��
	int Correction = 0;			// ���X�^�[�X�N���[���̕␳

	GetGraphSize(Gr_Handle, &Width, &Height);

	for (int I = 0; I < Height; ++I)
	{
		const int DestX = X - Width / 2 + std::cos((I + Correction) / 180.0 * DX_PI * Cycle) * Shake;
		const int DestY = Y - Height / 2 + I;

		DrawRectGraph
		(
			DestX, DestY,
			0, I,
			Width, 1,
			Gr_Handle,
			TRUE, FALSE
		);
	}

	++Correction;
}


void Graphics2D::DrawRasterScroll(const int& X, const int& Y, double Cycle, double Shake, const int& Gr_Handle, bool isVertical)
{
	int Width = 0, Height = 0;					// �摜�̉����Əc��
	static int Correction = 0;					// ���X�^�[�X�N���[���̕␳

	GetGraphSize(Gr_Handle, &Width, &Height);	// �摜�̃T�C�Y�𓾂�

	switch (isVertical)
	{
	case true :
		for (int I = 0; I < Height; ++I)
		{
			const int& DestX = X - Width / 2 + std::cos((I + Correction) / 180.0 * DX_PI * Cycle) * Shake;	// cos�̒l�ō��E�ɗh�炷
			const int& DestY = Y - Height / 2 + I;

			// �摜�̕����`��i�c�ɂPpix���j
			DrawRectGraph(
				DestX, DestY,
				0, I,
				Width, 1,
				Gr_Handle,
				TRUE, FALSE
				);
		}	break;

	case false :
		for (int I = 0; I < Width; ++I)
		{
			const int DestX = X - Width / 2 + I;
			const int DestY = Y - Height / 2 + std::cos((I + Correction) / 180. * DX_PI * Cycle) * Shake;

			// �摜�̕����`��i���ɂPpix���j
			DrawRectGraph(
				DestX, DestY,
				I, 0,
				1, Height,
				Gr_Handle,
				TRUE, FALSE
				);
		}	break;
	}

	if (Game::IsPause())	return;
	++Correction;
}


void Graphics2D::DrawBlendAdd(const int &X, const int &Y, const double &ExRate_, const double &Angle_, int Blend_ADD, const int &Gr_Handle, bool TransFlag_)
{
	const int& BLEND_ADD = std::min( 255, std::max(0, Blend_ADD) );

	SetDrawBlendMode(DX_BLENDMODE_ADD, BLEND_ADD);					// ���Z�u�����h���[�h
	DrawRotaGraph(X, Y, ExRate_, Angle_, Gr_Handle, TransFlag_);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);						//�u�����h���[�h���I�t
}


void Graphics2D::DrawColorGraph(const int& X, const int& Y, const double& Exrate, const int& Gr_Handle, int R, int G, int B)
{
	SetDrawBright(R, G, B);
	DrawRotaGraph(X, Y, Exrate, 0.0, Gr_Handle, true);
	SetDrawBright(255, 255, 255);
}


// ���s�o�����Ȃ��`�`�`�`
void Graphics2D::DrawAnimation(const double& X, const double& Y, const double& EXRATE, const double& ANGLE, const int & ANIME_SPEED)
{
	if (gh != nullptr){
		printfDx("�ǂݍ��݃G���[(G2D)\n");	return;
	}
	const int& ALL_NUM = ANIME_SPEED * FRAME_NUM;

	for (int i = 0; i < FRAME_NUM; i++)
	{
		for (int j = 0; j < ALL_NUM; j++)
		{
			if (count >= j && count <= j + (j * ANIME_SPEED))
			{
				DrawRotaGraph(X, Y, EXRATE, ANGLE, gh[i], true);
				break;
			}
		}
	}

	count++;

	if (count == ALL_NUM)	count = 0;
}


void DrawAnime(const double & PosX, const double & PosY, const double & ANGLE, const int & TIME, const int& FRAME_NUM, const int & TIME_FRAME, int Gr_Handle[])
{
	// �]������Ƃ߂邽�߁A�P�𑫂��Ē���
	const int& SUM_FRAME_TIME = (FRAME_NUM * TIME_FRAME + 1);

	// �A�j���[�V����
	for (int j = 0; j < FRAME_NUM; j++)
	{
		const bool& IS_PLAYTIME = ( TIME % SUM_FRAME_TIME < j * TIME_FRAME ||
									TIME % SUM_FRAME_TIME > TIME_FRAME + (j * TIME_FRAME) );
		if (IS_PLAYTIME)	continue;

		DrawRotaGraph(PosX, PosY, 2.0, ANGLE, Gr_Handle[j], true);
		break;
	}
}


void DrawAnime(const double & PosX, const double & PosY, const double & ANGLE, const int & FRAME_NUM, const int & TIME_FRAME, int Gr_Handle[])
{
	// �]������Ƃ߂邽�߁A�P�𑫂��Ē���
	const int& SUM_FRAME_TIME = (FRAME_NUM * TIME_FRAME + 1);
	
	static int aniTime = 0;
	aniTime++;

	// �A�j���[�V����
	for (int j = 0; j < FRAME_NUM; j++)
	{
		const bool& IS_PLAYTIME = ( aniTime % SUM_FRAME_TIME < j * TIME_FRAME ||
									aniTime % SUM_FRAME_TIME > TIME_FRAME + (j * TIME_FRAME) );
		if (IS_PLAYTIME)	continue;

		DrawRotaGraph(PosX, PosY, 2.0, ANGLE, Gr_Handle[j], true);

		break;
	}
}