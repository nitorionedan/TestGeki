#include "DxLib.h"
#include "EnemyMng.hpp"

#include <cstdlib>
#include <cstring>


Enemy** EnemyMng::enemy;
int     EnemyMng::e_num;


EnemyMng::EnemyMng()
	: T_T(1)
{
	// ��̓G���쐬
	enemy = new Enemy*[2];
	for (int i = 0; i < 2; i++)	enemy[i] = nullptr;
}


EnemyMng::~EnemyMng()
{
	for (int i = 0; i < sizeof(enemy) / sizeof(enemy[0]); i++)	delete enemy[i];
	delete[]	enemy;
}


void EnemyMng::Load(eStage stage)
{
	if(stage != eStage::stage1)
	{
		printf("EnemyMng::Load�@�܂������ĂȂ���B\n");
		return;
	}

	e_num = 0;

	// �t�@�C����
	char* fname = nullptr;

	if (enemy != nullptr)
	{
		for (int i = 0; i < sizeof(enemy) / sizeof(enemy[0]); i++)	delete enemy[i];
		delete[]	enemy;
	}

	// ���̃X�e�[�W�̓G�e�[�u����ǂݍ���
	switch (stage)
	{
	case eStage::stage1: fname = "EnemyTable1.csv"; break;
	case eStage::stage2: fname = "EnemyTable2.csv"; break;
	case eStage::stage3: fname = "EnemyTable3.csv"; break;
	case eStage::stage4: fname = "EnemyTable4.csv"; break;
	case eStage::stage5: fname = "EnemyTable5.csv"; break;
	case eStage::stage6: fname = "EnemyTable6.csv"; break;
	case eStage::stage0: fname = "EnemyTable0.csv"; break;
	}

	FILE* fp;
	int c;

	fopen_s(&fp, fname, "rb");

	// �G�f�[�^�̐��𐔂���
	{
		while (T_T)
		{
			c = std::fgetc(fp);

			if (c == EOF)	break;		// �����Ȃ烋�[�v�𔲂���

			if (c == '\n')	e_num++;	// ���s�Ȃ�A�J�E���g
		}

		e_num--; // �����킹

		fclose(fp);
	}

	// �G�̐���ݒ�
	enemy = new Enemy*[e_num];

	// �G�𐶐�
	tEnemyData* ene_date;
	ene_date = new tEnemyData[e_num];

	char buf[100];
	int col = 1;
	int row = 0;

	std::memset(buf, 0, sizeof(buf));
	fopen_s(&fp, fname, "rb");

	// �w�b�_�ǂݔ�΂�
	while (std::fgetc(fp) != '\n');

	while (T_T)		// ��
	{

		while (T_T)	// �����ė�
		{
			c = std::fgetc(fp);

			// �����Ȃ烋�[�v�𔲂���
			if (c == EOF)	goto out;

			// �J���}�����s�ȊO�Ȃ�A�����Ƃ��ĘA��
			if (c != ',' && c != '\n'){
				strcat_s(buf, sizeof(buf) / sizeof(buf[0]), (const char*)&c);
			}
			// �J���}�����s�Ȃ烋�[�v�𔲂���
			else {
				break;
			}

		}

		// �����ɗ����Ƃ������Ƃ́A1�Z�����̕����񂪏o���オ�����Ƃ���������
		switch (col)
		{
					// 1��ڂ͓G��ނ�\���Batoi�֐��Ő��l�Ƃ��đ��
		case 1:		ene_date[row].type = std::atoi(buf);		break;
					// 2��ڂ͒e��ށB�ȍ~�ȗ�
		case 2:		ene_date[row].stype = std::atoi(buf);		break;
		case 3:		ene_date[row].m_pattern = std::atoi(buf);	break;
		case 4:		ene_date[row].s_pattern = std::atoi(buf);	break;
		case 5:		ene_date[row].in_time = std::atoi(buf);		break;
		case 6:		ene_date[row].stop_time = std::atoi(buf);	break;
		case 7:		ene_date[row].shot_time = std::atoi(buf);	break;
		case 8:		ene_date[row].out_time = std::atoi(buf);	break;
		case 9:		ene_date[row].x_pos = std::atoi(buf);		break;
		case 10:	ene_date[row].y_pos = std::atoi(buf);		break;
		case 11:	ene_date[row].s_speed = std::atoi(buf);		break;
		case 12:	ene_date[row].hp = std::atoi(buf);			break;
		case 13:	ene_date[row].item = std::atoi(buf);		break;
		}

		// �o�b�t�@��������
		std::memset(buf, 0, sizeof(buf));

		// �񐔂𑫂�
		++col;

		// �����ǂݍ��񂾕����񂪉��s��������񐔂����������čs���𑝂₷
		if (c == '\n')
		{
			col = 1;
			++row;
		}
	}

out:
	// �t�@�C�������
	std::fclose(fp);

	// �G�I�u�W�F�N�g����
	for (int i = 0; i < e_num; i++)
	{
		enemy[i] = new Enemy(
			ene_date[i].type,
			ene_date[i].stype,
			ene_date[i].m_pattern,
			ene_date[i].s_pattern,
			ene_date[i].in_time,
			ene_date[i].stop_time,
			ene_date[i].shot_time,
			ene_date[i].out_time,
			ene_date[i].x_pos,
			ene_date[i].y_pos,
			ene_date[i].s_speed,
			ene_date[i].hp,
			ene_date[i].item);
	}

	// �p�͖����Ȃ������߉��
	delete[] ene_date;
}


void EnemyMng::Update()
{
	if (enemy == nullptr)	return;

	for (int i = 0; i < e_num; i++)	enemy[i]->Update();
}


void EnemyMng::Draw()
{
	if (enemy == nullptr)	return;

	for (int i = 0; i < e_num; i++)	enemy[i]->Draw();
}


bool EnemyMng::IsHit(const double & ColX, const double & ColY, const int& DAMAGE)
{
	if (enemy == nullptr)	return false;

	bool isHit;

	for (int i = 0; i < e_num; i++)
	{
		isHit = enemy[i]->IsHit(ColX, ColY, DAMAGE);

		// true�Ȃ�Ԃ�
		if (isHit)	return isHit;
	}

	// �S��false�Ȃ炱���܂�
	return isHit;
}


bool EnemyMng::IsHit(const int & ColCircle, const double & ColX, const double & ColY, const int & Damage)
{
	if (enemy == nullptr)	return false;

	bool isHit;

	for (int i = 0; i < e_num; i++)
	{
		isHit = enemy[i]->IsHit(ColCircle, ColX, ColY, Damage);

		// true�Ȃ�Ԃ�
		if (isHit)	return isHit;
	}

	// �S��false�Ȃ炱���܂�
	return isHit;
}


/********************************************
�R�����g�@�F	csv�t�@�C���̓ǂݍ��݂Ɋւ���
�Q�l�T�C�g�F	http://bituse.info/game/shot/11
�A�N�Z�X���F	2016/5/13

*********************************************/

// EOF