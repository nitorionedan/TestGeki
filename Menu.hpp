#pragma once

#include "DxLib.h"

#include "BaseScene.hpp"
#include "Graphic.hpp"
#include "Keyboard.hpp"
#include "Score.hpp"
#include "Title.hpp"
#include "Counter.hpp"

#include <memory>
#include <array>


// ���j���[�̃J�[�\���N���X
/*
class Title_Select
{
public:
	int hg;
	int hs_select;	// select SE
	int hs_choice;
	int y;
	int selectNum;

	const int x;

public:
	Title_Select()
		: x(262)
	{
	}
	~Title_Select()
	{
		DeleteGraph(hg);
		DeleteSoundMem(hs_select);
		DeleteSoundMem(hs_choice);
	}
};
*/


//���j���[��ʃN���X
class Menu : public BaseScene
{
public:
	Menu(ISceneChanger* changer);
	~Menu();

private:
	void Update() override;
	void Draw() override;
	void AnotherUpdate();		// �閧�̔�

	std::unique_ptr<Title>   title;
	std::unique_ptr<Graphic> graphic;
	std::unique_ptr<Score>   score;
	std::unique_ptr<Counter> c_game;

	const int X;				// ���ڂ̂����W
	const int SPACE;			// �����ƕ����̊Ԋu
	const int X_CUR;			// �J�[�\���̂����W
	const int ALL_SELECT_NUM;	// ���j���[�̍��ڐ�

	std::array<int, 4> y;		// ���ڂ̂����W
	int y_cur;					// �J�[�\���̍��W
	int selectNum;				// ���݂̑I��ԍ�
	int h_twi, h_cursor;		// �摜�p�n���h��
	int hs_choice, hs_move;		// �T�E���h�p�n���h��
	int ano_tri;				// Another Trigger
	bool isGame;
};