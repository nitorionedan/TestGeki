//------------------------------------------------------------------------------
/// @file
/// @brief    Graphics2D�N���X
/// @author   PG�� ��I
///
/// @copyright  Copyright 2016 Shohei.Y
/// @attention  ���̃t�@�C���̗��p�́A������README�ɂ���
///             ���p�����ɏ]���Ă�������

//------------------------------------------------------------------------------

#pragma once


// �g���H�`��N���X
class Graphics2D
{
public:
	Graphics2D();

	// @param[in]	num	�g���R�}��
	Graphics2D(int Gr_Handle[], int num);
	~Graphics2D();

	// @brief		�^���I�Ƀ��X�^�[�X�N���[����������
	// @param[in]	X, Y		�`�悷�钆�S���W
	// @param[in]	Gr_Handle	�摜�n���h��
	// @param[in]	Cycle		�����i���ɂႮ�ɂ�̑����j
	// @param[in]	Snake		�U���i���ɂ�鋗���j
	// @attention	�{���̕ύX�ɖ��Ή�
	void Raster_Scroll(const int &X, const int &Y, const int &Gr_Handle, double Cycle, double Shake);

	// @brief		Graphics2D::Raster_Scroll() �����̃Q�[���p�Ɏ������������
	// @param[in]	X, Y		�`�悷�钆�S���W
	// @param[in]	Cycle		�����i���ɂႮ�ɂ�̑����j
	// @param[in]	Snake		�U���i���ɂ�鋗���j
	// @param[in]	Gr_Handle	�摜�n���h��
	// @param[in]	isVertical	�c�ɗh�炷���H
	// @attention	�{���̕ύX�ɖ��Ή�
	void DrawRasterScroll(const int &X, const int &Y, double Cycle, double Shake, const int &Gr_Handle, bool isVertical = true);

	// @brief		�����x������ݒ肵�Ȃ���摜��`��
	// @param[in]	X, Y		�`�悷�钆�S���W
	// @param[in]	EXRATE_		�`�悷��Ƃ��̊g��{��
	// @param[in]	ANGLE_		��]�l
	// @param[in]	Blend_ADD	���Z�l�i�O�`�Q�T�T�j
	// @param[in]	Gr_Handle	�摜�n���h��
	// @param[in]	TransFlag	�����̔��]�t���O
	void DrawBlendAdd(const int &X, const int &Y, const double &EXRATE_, const double &ANGLE_, int Blend_ADD, const int &Gr_Handle, bool TransFlag_ = true);
	
	// @brief		�P�x������ݒ肵�Ȃ���摜��`��
	// @param[in]	X, Y		�`����W
	// @param[in]	EXRATE		�`��{��
	// @param[in]	Gr_Handle	�摜�n���h��
	// @param[in]	R, G, B		�P�x�iRGB�l�j
	// @attention	���̊֐��͍Ō�ɋP�x���i255, 255, 255�j�ɐݒ肵�Ă���
	void DrawColorGraph(const int& X, const int& Y, const double& EXRATE, const int &Gr_Handle, int R, int G, int B);

	// @brief					�R�}�A�j����`��
	// @param[in]	ANIME_SPEED	�R�}�𑗂鑬���i�P�����̃t���[�����j
	// @attention				Graphics2D�N���X�̈����t���R���X�g���N�^�Ŋi�[���ꂽ�I�u�W�F�N�g�̂ݎg�p�\
	void DrawAnimation(const double& X, const double& Y, const double& EXRATE, const double& ANGLE, const int& ANIME_SPEED);

	// @brief					�w�肵�����Ԃ����`��
	// @param[in]	X, Y		�`����W
	// @param[in]	EXRATE		�`��{��
	// @param[in]	Gr_Handle	�摜�n���h��
	// @param[in]	time		�`�悷�鎞�ԁi�t���[���j
	void DrawForTime(const double& X, const double& Y, const double& EXRATE, const double& ANGLE, const int &Gr_Handle, int time){}

private:
	const int FRAME_NUM;
	int* gh;
	int count;
};


// @brief					�A�j���[�V�����Đ��֐��E��
// @pram[in]	PosX, PosY	�`�撆�S���W
// @pram[in]	ANGLE		�`��p�x
// @pram[in]	TIME		���t���[���P������ϐ�
// @pram[in]	FRAME_NUM	�A�j���[�V�����̑�����
// @pram[in]	TIME_FRAME	�P�R�}�̕\�����ԁi�t���[�����j
// @pram[in]	Gr_Handle[]	�摜�n���h���z��
// @attention				�z��̑����v�𒴂����l�����Ȃ��ł��������B�{���͂Q�{�ɂ���Ă��܂��B
void DrawAnime(const double& PosX, const double& PosY, const double& ANGLE, const int& TIME, const int& FRAME_NUM, const int& TIME_FRAME, int Gr_Handle[]);


// @biref					���Ԃ�S�ē����ɂ��邽�߂̃A�j���[�V�����Đ��֐�
// @pram[in]	PosX, PosY	�`�撆�S���W
// @pram[in]	ANGLE		�`��p�x
// @pram[in]	FRAME_NUM	�A�j���[�V�����̑�����
// @pram[in]	TIME_FRAME	�P�R�}�̕\�����ԁi�t���[�����j
// @pram[in]	Gr_Handle[]	�摜�n���h���z��
// @attention				�z��̑����v�𒴂����l�����Ȃ��ł��������B�{���͂Q�{�ɂ���Ă��܂��B
void DrawAnime(const double& PosX, const double& PosY, const double& ANGLE, const int& FRAME_NUM, const int& TIME_FRAME, int Gr_Handle[]);


/* ���� */
// new�Ŋm�ۂ���ƃq�[�v�̈�ɋL�������

// EOF