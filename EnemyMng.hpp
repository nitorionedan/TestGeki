#ifndef ENEMY_CSV_HPP
#define ENEMY_CSV_HPP

#include "Enemy.hpp"
#include "Stage.hpp"


typedef struct
{
	int type,		// �G���
		stype,		// �e���
		m_pattern,	// �ړ��p�^�[��
		s_pattern,	// ���˃p�^�[��
		in_time,	// �o������
		stop_time,	// ��~����
		shot_time,	// �e���ˎ���
		out_time,	// �A�Ҏ���
		x_pos,		// x���W
		y_pos,		// y���W
		s_speed,	// �e�X�s�[�h
		hp,			// HP
		item;		// �A�C�e��
} tEnemyData;


class EnemyMng
{
public:
	EnemyMng();
	~EnemyMng();

	// @brief	���̃X�e�[�W�̓G�̃f�[�^�����[�h
	void Load(eStage stage);
	void Update();
	void Draw();
	static bool IsHit(const double& ColX, const double& ColY, const int& DAMAGE);
	static bool IsHit(const int& ColCircle, const double& ColX, const double& ColY, const int& Damage);

private:
	const int T_T;

	// �G���G
	static Enemy** enemy;

	// �G�̐�
	static int e_num;
};


#endif