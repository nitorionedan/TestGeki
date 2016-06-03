#pragma once

#include "Task.hpp"
#include "Graphic.hpp"

#include <memory>


class Score : public Task
{
public:
	Score();
	~Score();
	void Update() override;
	void Draw() override;
	void IsShowScore(const bool& IsShow);
	void ShowResult();
	static void AddScore(const int& point);

	int secBonus; // ���b���Z�X�R�A // �Ȃ��̕�����(^^;

private:
	void LoadScore();				// �Z�[�u�t�@�C�����[�h
	void SaveScore();
	void DeleteScore();				// �Z�[�u�f�[�^�폜

	std::unique_ptr<Graphic> graphic;
	char* name;						// �Z�[�u�t�@�C��
	FILE* fp;						// �t�@�C���A�N�Z�X�|�C���^
	errno_t error;					// ��O

	static const int digit;			// ����
	static int score;
	int x_pos, y_pos;
	int hi_score, x_hi, y_hi;
	int val_score;
	int val_hiscore;
	int x_num;

	int c_secscore;					// ���b���Z�X�R�A�p�J�E���^�[
	bool f_exist;					// ���݂��Ă��邩�H
};