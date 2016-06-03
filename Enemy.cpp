#include "DxLib.h"

#include "Enemy.hpp"
#include "Stage.hpp"
#include "Player.hpp"
#include "Pshot.hpp"
#include "Vector2D.hpp"
#include "Graphics2D.hpp"
#include "DebugMode.hpp"
#include "Score.hpp"
#include "Game.hpp"

// Shots
#include "EShot00.hpp"
#include "EShot01.hpp"
#include "EShot02.hpp"
#include "Eshot04.hpp"

#include <algorithm>
#include <cmath>

#undef max // ������Ȃ��̃J�X�K�v�˂��񂾂�I
#undef min // What's the fuck!


Enemy::Enemy(int type, int stype, int m_pattern, int s_pattern, int in_time, int stop_time, int shot_time, int out_time, int x_pos, int y_pos, int s_speed, int hp, int item)
	: SCREEN_LIMIT_XL(-10)
	, SCREEN_LIMIT_XR(650)
	, SCREEN_LIMIT_YT(-10)
	, SCREEN_LIMIT_YB(490)
	, MAX_HP(hp)
	, DROP_RATE(2)
	, shot(nullptr)
	, shot2(nullptr)
	, shot3(nullptr)
	, SPEED_0(4.)
	, gh_shot00(NULL)
	, sh_voice(NULL)
	, elapsedTime(0)
	, moveTime(0)
	, s_time(0)
	, angle(0.)
	, isExist(false)
	, isMove(true)
	, isDamage(false)
	, isUngry(false)
{
	// ��O����
	if(item < 0 || item > 3)
	{
		printfDx("�A�C�e��ID�͈͊O�ł��B\n");
		std::min(4, std::max(0, item));
	}

	// �f�[�^�ݒ�
	this->type = type;
	this->stype = stype;
	this->m_pattern = m_pattern;
	this->s_pattern = s_pattern;
	this->in_time = in_time;
	this->stop_time = stop_time;
	this->shot_time = shot_time;
	this->out_time = out_time;
	this->x_pos = x_pos;
	this->y_pos = y_pos;
	this->s_speed = s_speed;
	this->hp = hp;
	this->item = item;
	pos.SetVecor2D(static_cast<double>(x_pos), static_cast<double>(y_pos));

	// �^�C�v�ɍ��킹��
	switch (type)
	{
	case 0:
		gh_ene00 = LoadGraph("GRAPH/GAME/ENEMY/ene00.png");
		hitRange = 20.;
		break;
	case 1:
		break;
	case 2:
		LoadDivGraph("GRAPH/GAME/ENEMY/ene02.png", 4, 4, 1, 31, 16, gh_ene02);
		hitRange = 20.;
		hitSRange.SetVecor2D(40., 40.);
		break;
	case 3:
		break;
	case 4:
		LoadDivGraph("GRAPH/GAME/ENEMY/career.png", 8, 4, 2, 124, 78, gh_ene04);
		sh_voice = LoadSoundMem("SOUND/SE/scream00.wav");
		hitRange = 50.;
		break;
	case 5:
		break;
	case 6:
		break;
	case 7:
		break;
	}

	// ���x
	switch (m_pattern)
	{
	case 0:
		vspeed_x = 2.;
		vspeed_y = 4.;
		break;
	case 1:
		break;
	case 2:
		vspeed_x = 2.;
		vspeed_y = 0.1;
		break;
	case 3:
		break;
	case 4:
		break;
	case 5:
		break;
	case 6:
		break;
	case 7:
		break;
	}

	// �e���[�h
	switch (s_pattern)
	{
	case 0:	shot = new Shot(new EShot00);	break;
	case 1:	break;
	case 2:	shot = new Shot(new EShot00);	break;
	case 3:	break;
	case 4:
		shot = new Shot(new EShot04);
		shot2 = new Shot(new EShot01);	break;
	case 5:	break;
	case 6:	break;
	case 7:	break;

	default: printfDx("Enemy.cpp:ERROR");	break;
	}

	gh_shot00 = LoadGraph("GRAPH/GAME/Eshot/efire0.png");
}


Enemy::~Enemy()
{
	delete shot;
	delete shot2;
	delete shot3;

	// �摜�A�����[�h
	switch (type)
	{
	case 0:
		DeleteGraph(gh_ene00);
		break;
	case 1:
		break;
	case 2:
		for (int i = 0; i < sizeof(gh_ene02) / sizeof(gh_ene02[0]); i++)
			DeleteGraph(gh_ene02[i]);
		break;
	case 3:
		break;
	case 4:
		for (int i = 0; i < sizeof(gh_ene04) / sizeof(gh_ene04[0]); i++)
			DeleteGraph(gh_ene04[i]);
		break;
	case 5:
		break;
	case 6:
		break;
	case 7:
		break;

	default:
		printfDx("ERROR:Enemy.cpp");
		break;
	}

	if (gh_shot00 != NULL)	DeleteGraph(gh_shot00);
	if (sh_voice != NULL)	DeleteSoundMem(sh_voice);
}


void Enemy::Update()
{
	// �o�ꎞ�Ԃ�������o�Ă���
	if (Stage::GetTime() == in_time)
	{
		isExist = true;
	}

	if (isExist)
	{
		// ���Ԃ��o�߂�����
		elapsedTime++;

		s_time++;

		isDamage = false;

		// �U�����ꂽ��N����
		if (Keyboard_Get(KEY_INPUT_Z) == 1)	isUngry = true;

		Move();
	}

	shot->Update(pos.x, pos.y);
	
	if (shot2 != nullptr)	shot2->Update(pos.x, pos.y);
	
	if (shot3 != nullptr)	shot3->Update(pos.x, pos.y);

	if (!isExist)	return;
	
	Fire();
}


void Enemy::Draw()
{
	if (isExist)
	{
		// On-Damage-Effect
		if (MAX_HP / 3 >= hp && elapsedTime % 12 >= 10)
		{
			SetDrawBlendMode(DX_BLENDMODE_INVSRC, 255);
			SetDrawBright(255, 0, 0);
		}

		if (isDamage)	SetDrawBlendMode(DX_BLENDMODE_INVSRC, 255);

		switch (type)
		{
		case 0:
			DrawRotaGraph(pos.x, pos.y, 2., angle, gh_ene00, true);
			break;
		case 1:
			break;
		case 2:
			DrawAnime(pos.x, pos.y, angle, elapsedTime, sizeof(gh_ene02) / sizeof(gh_ene02[0]), 2, gh_ene02);
			break;
		case 3:
			break;
		case 4:
			DrawAnime(pos.x, pos.y, 0.0, elapsedTime, sizeof(gh_ene04) / sizeof(gh_ene04[0]), 8, gh_ene04);
			if (s_time == stop_time ||
				s_time == stop_time + 20 ||
				s_time == stop_time + 40)
			{
				DrawRotaGraph(pos.x + 70, pos.y - 30, 2.0, 0.0, gh_shot00, true);
				DrawRotaGraph(pos.x + 50, pos.y, 2.0, 0.0, gh_shot00, true);
				DrawRotaGraph(pos.x - 70, pos.y - 30, 2.0, 0.0, gh_shot00, true);
				DrawRotaGraph(pos.x - 50, pos.y, 2.0, 0.0, gh_shot00, true);
			}
			break;
		case 5:
			break;
		case 6:
			break;
		case 7:
			break;
		}

		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		SetDrawBright(255, 255, 255);
	}

	shot->Draw();
	if (shot2 != nullptr)	shot2->Draw();
	if (shot3 != nullptr)	shot3->Draw();

	// TEST
	if (!DebugMode::isTest)	return;

	if (!isExist)			return;

	//	DrawFormatString(300, 300, GetColor(0, 255, 0), "%lf", angle);
	DrawCircle(pos.x, pos.y, hitRange, GetColor(0, 255, 0), false);
}


bool Enemy::IsHit(const double & ColX, const double & ColY, const int& DAMAGE)
{
	if (!isExist)	return false;

	bool isHit;

	switch (type)
	{
	case 0:
		isHit = Vector2D::CirclesCollision(hitRange, 6, pos.x, pos.y + 9., ColX, ColY);	
		break;
	case 1:
		break;
	case 2:
		isHit = Vector2D::CirclesCollision(hitRange, 6, pos.x, pos.y + 9., ColX, ColY);
		break;
	case 3:
		break;
	case 4:
		isHit = Vector2D::CirclesCollision(hitRange, 6, pos.x, pos.y + 9., ColX, ColY);
		break;
	case 5:
		break;
	case 6:
		break;
	case 7:
		break;
	}

	// �_���[�W����
	if (isHit)	Damage(DAMAGE);

	// �S��false�Ȃ炱���ɂ���
	return isHit;
}


bool Enemy::IsHit(const int & ColCircle, const double & ColX, const double & ColY, const int & Damage)
{
	if (!isExist)	return false;

	const bool& IS_HIT = Vector2D::CirclesCollision(ColCircle, hitRange, ColX, ColY, pos.x, pos.y);
	
	if (IS_HIT)	this->Damage(Damage);
	
	return IS_HIT;
}


void Enemy::AngleTarget(const double Target_x, const double Target_y){
	angle = atan2(Target_y - pos.y, Target_x - pos.x) - DX_PI / 2;	// ���@�Ɍ���
}


void Enemy::Move()
{
	switch (m_pattern)
	{
	case 0:	Move_0();	break;
	case 1:	Move_1();	break;
	case 2:	Move_2();	break;
	case 3:	Move_3();	break;
	case 4:	Move_4();	break;
	case 5:	Move_5();	break;
	case 6:	Move_6();	break;
	case 7:	Move_7();	break;
	}

	const bool& IS_HIT = Game::IsHitPlayer(hitRange, Player::HIT_RANGE, pos.x, pos.y, Game::GetPlayerPos().x, Game::GetPlayerPos().y);
	if (IS_HIT)	Damage(1);
}


void Enemy::Move_0()
{
	const bool& IS_IN = (elapsedTime >= 0 && elapsedTime <= stop_time);
	const bool& IS_OUT = (elapsedTime >= out_time);
	const double& BRAKE = 0.03;

	// �ŏ��̈ړ�
	if (IS_IN)
	{
		// �v���C���[�̑O����ʂ̏㔼���Ȃ�
		if (Game::GetPlayerPos().y - 60.0 > pos.y || pos.y >= 320.)
		{
			// ����
//			vspeed_y -= 0.02;
			vspeed_y = (Game::GetPlayerPos().y - 60. - pos.y) * BRAKE;
		}

		// �~���
		if (isMove)	pos.y += vspeed_y;

		// ���ړ��F������E
		if (pos.x < Game::GetPlayerPos().x - 10. && isMove)
		{
			vspeed_x = (Game::GetPlayerPos().x - 20. - pos.x) * BRAKE;
			pos.x += vspeed_x;
		}

		// ���ړ��Q�F�E���獶
		if (pos.x > Game::GetPlayerPos().x + 10. && isMove)
		{
			pos.x -= vspeed_x;
			vspeed_x *= 0.99999999;
		}

		// ���x�𕉂ɂ��Ȃ�
		if (vspeed_x < 0.)
		{
			vspeed_x = 0.;
			isMove = false;
		}
		if (vspeed_y < 0.)	vspeed_y = 0.;

	}

	// ���@�Ɍ���
	if (elapsedTime < out_time)	AngleTarget(Game::GetPlayerPos().x, Game::GetPlayerPos().y);

	// �X�s�[�h�ύX
	if (elapsedTime == out_time)	vspeed_y = 0.;

	// �A��
	if (elapsedTime >= out_time)
	{
		// ����
		if (vspeed_y > -SPEED_0)	vspeed_y -= 0.05;

		// �ړ�
		pos.y += vspeed_y;

		// �����]���̂���i�[�������Ȃ������Ȃ̂ŏC������v��j
		if (angle >= 0.)	angle += 0.02;
		if (angle < 0.)		angle -= 0.02;
	}

	// �ޏ�
	if (IS_OUT)
	{
		if (pos.y <= -40)	isExist = false;
	}
}


void Enemy::Move_1()
{
	vspeed_x = std::cos(elapsedTime / 30.) * 8. * std::sin(elapsedTime / 10.) * std::cos(elapsedTime / 10.);

	pos.x += vspeed_x;
	pos.y += vspeed_y;

	// ���@�Ɍ���
	AngleTarget(Game::GetPlayerPos().x, Game::GetPlayerPos().y);
}


void Enemy::Move_2()
{
	vspeed_x = 0.;
	vspeed_y = 2.;

	pos.y += vspeed_y;
}


void Enemy::Move_3()
{
}


void Enemy::Move_4()
{
	static float c_move = 0.f;
	c_move += 0.01f;

	vspeed_x = 0.7;
	vspeed_y = 0.2;

	if (s_time < stop_time ||
		s_time > stop_time + 40)
	{
		pos.y += vspeed_y;
	}
	pos.x += vspeed_x * std::cos(c_move);

	if (pos.y < -70.)	isExist = false;
}


void Enemy::Move_5()
{
}


void Enemy::Move_6()
{
}


void Enemy::Move_7()
{
}


void Enemy::Fire()
{
	switch (type)
	{
	case 0: Fire_0();	break;
	case 1: Fire_1();	break;
	case 2:	Fire_2();	break;
	case 3:	Fire_3();	break;
	case 4:	Fire_4();	break;
	case 5:	Fire_5();	break;
	case 6:	Fire_6();	break;
	case 7:	Fire_7();	break;
	}
}


void Enemy::Fire_0()
{
	const double& ANGLE = atan2(Game::GetPlayerPos().y - pos.y, Game::GetPlayerPos().x - pos.x);

	if (elapsedTime == 20)
	{
		int dir = GetRand(1);
		double addAng = (GetRand(3) / 15.);

		if (dir == 0)
			shot->Fire(s_speed, ANGLE - addAng);
		else
			shot->Fire(s_speed, ANGLE + addAng);
	}

	if (elapsedTime == 50)
	{
		int dir = GetRand(1);
		double addAng = (GetRand(3) / 15.);
		
		if (dir == 0)
			shot->Fire(s_speed, ANGLE - addAng);
		else
			shot->Fire(s_speed, ANGLE + addAng);
	}

	if (elapsedTime == out_time && isUngry)
	{
		int dir = GetRand(1);
		double addAng = (GetRand(3) / 15);

		if (dir == 0)
		{
			shot->Fire(s_speed, (ANGLE + 0.3) - addAng);
			shot->Fire(s_speed, ANGLE - addAng);
			shot->Fire(s_speed, (ANGLE - 0.3) - addAng);
		}
		else
		{
			shot->Fire(s_speed, (ANGLE + 0.3) - addAng);
			shot->Fire(s_speed, ANGLE - addAng);
			shot->Fire(s_speed, (ANGLE - 0.3) - addAng);
		}
	}
}


void Enemy::Fire_1()
{
	const double& ANGLE = atan2(Game::GetPlayerPos().y - pos.y, Game::GetPlayerPos().x - pos.x);

	if (elapsedTime >= stop_time)
	{
		if (elapsedTime == stop_time + 10)	shot->Fire(s_speed, ANGLE);
		if (elapsedTime == stop_time + 20)	shot->Fire(s_speed, ANGLE);
	}
}


void Enemy::Fire_2()
{
}


void Enemy::Fire_3()
{
}


void Enemy::Fire_4()
{
	// ���@�_����������
	if (s_time == stop_time - 30)
	{
		vangle = atan2(Game::GetPlayerPos().y - pos.y, Game::GetPlayerPos().x - pos.x);
	}

	// 4WAY x 2
	if (s_time == stop_time ||
		s_time == stop_time + 20 ||
		s_time == stop_time + 40)
	{
		// �E��
		shot->Fire(pos.x + 70., pos.y - 30., s_speed, DX_PI / 8);
		shot->Fire(pos.x + 70., pos.y - 30., s_speed, DX_PI / 6);
		shot->Fire(pos.x + 50., pos.y, s_speed, DX_PI / 4);
		shot->Fire(pos.x + 50., pos.y, s_speed, DX_PI / 3);

		// ����
		shot->Fire(pos.x - 70., pos.y - 30., s_speed, DX_PI * 0.85);
		shot->Fire(pos.x - 70., pos.y - 30., s_speed, DX_PI * 0.8);
		shot->Fire(pos.x - 50., pos.y, s_speed, DX_PI * 0.7);
		shot->Fire(pos.x - 50., pos.y, s_speed, DX_PI * 0.6);
	}

	// ���@�_������
	if (s_time == stop_time + 20 ||
		s_time == stop_time + 30 ||
		s_time == stop_time + 40 ||
		s_time == stop_time + 50)
	{
		shot2->Fire(s_speed + 2, vangle);
	}

	// �V���b�g�^�C�����Z�b�g
	if (s_time == stop_time + 160)	s_time = 0;
}


void Enemy::Fire_5()
{
}


void Enemy::Fire_6()
{
}


void Enemy::Fire_7()
{
}



void Enemy::Damage(int damage)
{
	switch (type)
	{
	case 0:
		hp -= damage;
		isDamage = true;
		Score::AddScore(1);

		// ���C�Ȃ炱���ŕԂ�
		if (hp > 0)	return;

		ItemDrop();

		isExist = false;

		Score::AddScore(400);
		Game::PlayAnime(pos.x, pos.y, eExplosion_small);
		break;

	case 1:
		break;

	case 2:
		hp -= damage;
		isDamage = true;
		Score::AddScore(1);

		// ���C�Ȃ炱���ŕԂ�
		if (hp > 0)	return;

		ItemDrop();

		isExist = false;

		Score::AddScore(900);
		Game::PlayAnime(pos.x, pos.y, eExplosion_small);
		Game::PlaySpread(pos.x, pos.y, GetRand(100), eSpread_SmallAll);
		break;

	case 3:
		break;

	case 4:
		hp -= damage;
		isDamage = true;
		Score::AddScore(1);

		// ���C�Ȃ炱���ŕԂ�
		if (hp > 0)	return;

		isExist = false;
		
		PlaySoundMem(sh_voice, DX_PLAYTYPE_BACK);
		
		Score::AddScore(1500);
		Game::PlayAnime(pos.x, pos.y, eExplosion_normal);
		Game::PlaySpread(pos.x, pos.y, GetRand(100), eSpread_Bigs);
		Game::PlaySpread(pos.x, pos.y, GetRand(100), eSpread_SmallBlue);

		if (pos.y < 0)
		{
			Game::ItemDrop(pos.x, pos.y + 60., eItem_B);
			Game::ItemDrop(pos.x, pos.y + 60., eItem_P);
			Game::ItemDrop(pos.x, pos.y + 60., eItem_S);
		}
		else {
			Game::ItemDrop(pos.x, pos.y + 20., eItem_B);
			Game::ItemDrop(pos.x, pos.y + 20., eItem_P);
			Game::ItemDrop(pos.x, pos.y + 20., eItem_S);
		}
		break;

	case 5:
		break;

	case 6:
		break;

	case 7:
		break;

	default:
		break;
	}
}


void Enemy::ItemDrop()
{
	// 1 / 25�̊m���ŃA�C�e���������_���h���b�v
	int rand = GetRand(100);
	if (rand < DROP_RATE)	Game::ItemDrop(pos.x, pos.y, eItem_P);
}

// EOF