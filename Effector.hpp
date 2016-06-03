#pragma once

#include "Counter.hpp"
#include "Vector2D.hpp"

#include <memory>
#include <array>
#include <deque>
#include <vector>


class Effector
{
public:
	Effector();
	~Effector();

	void Update();
	void Draw();
	void Shift(const bool isSHIFT_UP, const int pow); // true : UP false : DOWN, Power Level
	static void Update_HitAnime();	// Game.cpp��
	static void Draw_HitAnime();	// �C�ӂ̏ꏊ��
	bool getIsAnime();
	
	static void PlayHitAni(const double& PosX, const double& PosY);

private:
	void ShiftUp(const int powLv);
	void ShiftDown(const int powLv);
	void CopyCounter();



	std::unique_ptr<Counter> c_anime;
	std::array<Counter*, 20> c_hit;
	std::array<int, 5>	hg_shift;	// �����P�������̉摜
	std::array<int, 2>	hs_shift;	// �o�[���I�@�Ɓ@���`��...
	bool   f_PlayAnime;				// �A�j���[�V�����Đ� 
	bool   f_up, f_down;			// �A�b�v���_�E����
	double x_pos, y_pos;
	int    shiftLv;					// �O�`4Lv

	static const int MAX_HIT_NUM;
	static int s_c_hit[];
	static Vector2D s_hitPos[];
	static bool s_isHitAnime[];
	static int s_hg_hit[];
};

// static�����o�ϐ��ŃG�t�F�N�g���Ǘ�����H 12/10/2015
// ��static bool f_pdamage, f_edamage
// ���������́A���̃N���X���Ƃ� static�����o�ϐ���p�ӂ����邩�ǂ��炪�ǂ����B