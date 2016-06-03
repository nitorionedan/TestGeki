#pragma once

#include "Task.hpp"
#include "Keyboard.hpp"
#include "Graphic.hpp"
#include "Range.hpp"
#include "Counter.hpp"
#include "Enemy.hpp"
#include "Vector2D.hpp"
#include "PieceEffect.hpp"

#include <memory>


// ���͂����L�[�̕���
enum class InputDir
{
	Neutral,
	Right,
	Left
};


enum ePlayerState
{
	ePlayerState_Start,
	ePlayerState_Game,
	ePlayerState_Dead,
};


class Player : public Task
{
public:
	Player();
	~Player();
	void Update()	override;
	void Draw()		override;
	void Update_Start();
	void Update_Game();
	void Update_Dead();
	void Draw_Start();
	void Draw_Game();
	void Draw_Dead();
	void SetStart();
	void InputMng();						// �A�˃f�[�^�Ǘ�
	void GetPos(double* x, double* y);
	Vector2D& GetPos();
	void AddBomb();
	void ShiftReset();
	void DownBombNum();

	// ���W���O���֓`���邽��-----
	static void Shift(const bool isUp);			// �V�t�g����
	static int GetShiftLevel();
	static int GetBombNum();
	static int GetLife();
	static int GetRensha();
	static bool IsDead();
	static bool IsMuteki();
	static bool IsStart();

	// @brief	���@�̉~�Ƒ��̓_�̓����蔻��
	bool HitCheckCircle(const double& ColX, const double& ColY);

	// @brief	���@�̉~�Ƒ��̉~�̓����蔻��
	bool HitCheckCircle(const double & Range1, const double & Range2, const double & X1, const double & Y1, const double & X2, const double & Y2);

	static const int HIT_RANGE;
	

private:
	void Move();									// �v���C���[�̓���
	void CopyStaticMem();							// static�����o�ϐ��ɒl���R�s�[
	void Rensha_Update();

	static const int	MaxPowLevel;				// �V�t�g�̌��E�l
	static const int	MAX_RENSHA,					// �A�˃Q�[�W�͈̔�
						MIN_RENSHA;
	const double	SpeedForce;						// �ړ����x
	const double	LimitScreenXL, LimitScreenXR;	// ��ʐ���
	const double	LimitScreenYT, LimitScreenYB;
	const double	Y_START;						// �X�^�[�g�n�_

	// ���W���O���֓`���邽��-----
	static ePlayerState state;		// �v���C���[�̏��
	static Vector2D s_pos;
	static int	hs_shiftUp,
				hs_shiftDown,
				hs_dead;
	static int	s_powlv;		// �p���[���x��(�V�t�g���x��)
	static int	s_bombNum;
	static int	bombNum;		// ���݂̃{����
	static int	s_life;
	static int	s_rensha;		// �A�˃Q�[�W
	static bool	s_isDead;
	static bool	s_isMuteki;
	static bool	s_isStart;		// �X�^�[�g�n�_�ɓ��B�������H
	static bool	isHit;			// ��e�������H
	// ---------------------------

	std::unique_ptr<Graphic>	graphic;	// �����摜
	std::unique_ptr<Counter>	c_start;	// �X�^�[�g�����p�J�E���^�[
	std::unique_ptr<Counter>	c_dead;
	std::unique_ptr<Enemy>		test;		// �e�X�g�p�T���h�o�b�O

	InputDir	 keydir;	// �L�[���͕���
	eSpread_t	dead_ef;	// ���ꉉ�o
	Vector2D	pos;		// ���@�̍��W
	static Vector2D	vec;	// ���@�̈ړ��x�N�g��
	int			hg[3];		// �摜�p�n���h��
	int			life;		// �c�@
	int			elapsedTime;
	bool		isDead;		// ����ł��邩�H
	bool		isMuteki;	// ���G���H
	bool		isShield;	// �V�[���h�𒣂��Ă��邩�H
};
// EOF