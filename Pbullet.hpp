#pragma once

#include "Task.hpp"
#include "Bullet.hpp"
#include "Counter.hpp"
#include "Keyboard.hpp"
#include "Player.hpp"
#include <memory>
#include <array>


class Pbullet									// ���v���΁ushot�v�̂ق����������肭�邵�A�Z���B���̃A�z�[�I
{
public:
	Pbullet();
	~Pbullet();
	void Update();
	void Draw();
	void SetFirePos(const double* x, const double* y);
	void SetPlayerPow(int powlv);
	void FireEffect(double fx, double fy);

private:
	void Fire();									// ���˃t���O�����Ă�
	void Move();									// �t���O�������Ă���e�𓮂���
	void Reset(int num);							// ��ʊO�̒e�����Z�b�g

	const int AllBulletNum;							// �ő�e��
	const double SPEED;								// �e�̑���
	const double Angle;								// ��΂�����(�p�x)
	const double LimScXR, LimScXL;					// �e�̐����͈�
	const double LimScYT, LimScYB;					//
	std::array<Bullet*, 4> Abullet;					// ��
	std::array<Bullet*, 4> Bbullet;					// ��
	std::array<Bullet*, 4> Cbullet;					// ��
	std::array<Bullet*, 4> Dbullet;					// �ׁ̗i�p�x���ς��e�j
	std::unique_ptr<Counter> c_blt;					// �V���b�g�Ԋu�p�J�E���^�[
	std::unique_ptr<Counter> c_fire;				// ���˒���̔��s�摜�p�J�E���^�[

	int		hg_blue, hg_orange, hg_red, hg_eftest;	// �摜�p�n���h��
	int		shiftLevel;								// �V���b�g���x��
	double	x_pos, y_pos;
	bool	isShot;									// ��������		// �������ɓ���������������������������
};
// EOF