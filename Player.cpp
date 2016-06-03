#pragma warning(disable:4244)

#include "DxLib.h"

#include "Player.hpp"
#include "Vector2D.hpp"
#include "DebugMode.hpp"
#include "Stage.hpp"
#include "Game.hpp"

#include <algorithm>
#include <cassert>

#define NOMINMAX


const int Player::MaxPowLevel = 4;
const int Player::MAX_RENSHA = 40;
const int Player::MIN_RENSHA = 0;
const int Player::HIT_RANGE = 8;

ePlayerState Player::state;
Vector2D Player::s_pos;
Vector2D Player::vec;
int Player::s_powlv;
int Player::s_bombNum;
int Player::s_life;
int Player::s_rensha;
int Player::hs_shiftUp;
int Player::hs_shiftDown;
int Player::hs_dead;
int Player::bombNum;
bool Player::s_isDead;
bool Player::s_isMuteki;
bool Player::s_isStart;
bool Player::isHit;


Player::Player()
	: SpeedForce(7.0)
	, Y_START(360.0)
	, LimitScreenXL(10.0)
	, LimitScreenXR(630.0)
	, LimitScreenYT(10.0)
	, LimitScreenYB(455.0)
	, graphic(new Graphic)
	, c_start(new Counter(150))
	, c_dead(new Counter(90))
	, elapsedTime(0)
	, keydir(InputDir::Neutral)
	, dead_ef(eSpread_SmallGrey)
	, isDead(false)
	, life(3)
	, isMuteki(false)
	, isShield(false)
{
	LoadDivGraph("GRAPH/GAME/player.png", 3, 3, 1, 20, 26, hg);	// �摜�̕����ǂݍ���
	hs_shiftUp = LoadSoundMem("SOUND/SE/shiftup.mp3");
	hs_shiftDown = LoadSoundMem("SOUND/SE/shiftdown.wav");
	hs_dead = LoadSoundMem("SOUND/SE/explosion02.wav");

	pos.SetVecor2D(320.0, 520.0);
	bombNum = 3;
	s_powlv		= 0;
	s_isStart	= false;
	isHit = false;
	s_isMuteki = true;
	state = ePlayerState_Start;
}


Player::~Player() {
	for (int h : hg)	DeleteGraph(h);
	DeleteSoundMem(hs_shiftUp);
	DeleteSoundMem(hs_shiftDown);
	DeleteSoundMem(hs_dead);
}


void Player::Update()
{
	elapsedTime++;

	switch (state)
	{
	case ePlayerState_Start: Update_Start();	break;
	case ePlayerState_Game: Update_Game();		break;
	case ePlayerState_Dead: Update_Dead();		break;
	default:	printfDx("Player.cpp:ERROR\n");	break;
	}

	// static�����o�ϐ��ɒl���R�s�[�i�A�z�j
	CopyStaticMem();

	isHit = false;

	// TEST------------------------------------------------------------------------------------
	if (DebugMode::isTest == false)	return;

	/*
	if (Keyboard_Get(KEY_INPUT_P) == 1)	{
		Shift(true);		// �V�t�g�A�b�v
	}
	if (Keyboard_Get(KEY_INPUT_O) == 1) {
		Shift(false);
	}
	*/
}


void Player::Draw()
{
	switch (state)
	{
	case ePlayerState_Start: Draw_Start();	break;
	case ePlayerState_Game: Draw_Game();	break;
	case ePlayerState_Dead: Draw_Dead();	break;
	default:	printfDx("Player.cpp:ERROR\n");	break;
	}

	// TEST------------------------------------------------------------------------------------
	if (DebugMode::isTest == false)	return;

	DrawCircle(pos.x, pos.y + 9, HIT_RANGE, GetColor(0, 255, 0), false);
//	DrawFormatString(100, 100, GetColor(0, 255, 0), "rensha = %d", s_rensha);
//	DrawFormatString(100, 100, GetColor(0, 255, 0), "D�Ŏ��ɂ܂�");
//	DrawFormatString(100, 120, GetColor(0, 255, 0), "P�ŃV�t�g�A�b�v");
//	DrawFormatString(100, 140, GetColor(0, 255, 0), "O�ŃV�t�g�_�E��");
}


void Player::Update_Start()
{
	const bool isStartPosition = (pos.y == Y_START);

	c_start->Update();

	if (c_start->isEach(70, 149))
	{
		pos.y -= 2.0;						// ��ɏ㏸
		pos.y = std::max(pos.y, Y_START);	// �X�^�[�g�n�_�܂�
	}else{
		InputMng();
		Rensha_Update();
		Move();
	}

	if (c_start->isLast())
	{
		s_isMuteki = false;
		state = ePlayerState_Game;	// �X�^�[�g�n�_�Ȃ�X�^�[�g����
	}
}


void Player::Update_Game()
{
	InputMng();
	Rensha_Update();
	Move();
}


void Player::Update_Dead()
{
	c_dead->Update();

	const bool& IS_DIEING = (c_dead->Remainder(8) == 0 && c_dead->isEach(1, 40));

	if (IS_DIEING)
	{		
		if (c_dead->GetNowcount() == 40)
			Game::PlayAnime(pos.x + 19., pos.y - 23., eExplosion_small);
		if (c_dead->GetNowcount() == 32)
			Game::PlayAnime(pos.x - 3., pos.y + 68., eExplosion_small);
		if (c_dead->GetNowcount() == 24)
			Game::PlayAnime(pos.x - 12., pos.y - 3., eExplosion_small);
		if (c_dead->GetNowcount() == 16)
			Game::PlayAnime(pos.x + 52., pos.y - 56., eExplosion_small);
		if (c_dead->GetNowcount() == 8)
			Game::PlayAnime(pos.x - 39., pos.y + 27., eExplosion_small);
	}

	pos.x += vec.x;
	pos.y += vec.y;

	if(c_dead->isLast())
	{
		life--;
		if (life == 0) {
			/// ���S
			Game::GameOver();
		}

		// �X�^�[�g��Ԃɂ���
		state = ePlayerState_Start;

		// �X�^�[�g�n�_�ɖ߂�
		pos.SetVecor2D(320.0, 520.0);

		keydir = InputDir::Neutral;

		// �ď[�U
		bombNum = 3;
	}
}


void Player::Draw_Start()
{
	const bool& IS_STARTING = (c_start->Remainder(4) >= 3);

	if (IS_STARTING)
	{
		SetDrawBlendMode(DX_BLENDMODE_INVSRC, 200); //���]����
		
		//Draw�֐�
		switch (keydir)
		{
		case InputDir::Left:	DrawRotaGraph(pos.x, pos.y, 2.0, 0.0, hg[0], true);	break;
		case InputDir::Neutral:	DrawRotaGraph(pos.x, pos.y, 2.0, 0.0, hg[1], true);	break;
		case InputDir::Right:	DrawRotaGraph(pos.x, pos.y, 2.0, 0.0, hg[2], true);	break;
		}
		
		SetDrawBlendMode(DX_BLENDMODE_ADD, 200); //���Z����
												 
		//Draw�֐��ŏ�Ɠ��������d�˂�
		switch (keydir)
		{
		case InputDir::Left:	DrawRotaGraph(pos.x, pos.y, 2.0, 0.0, hg[0], true);	break;
		case InputDir::Neutral:	DrawRotaGraph(pos.x, pos.y, 2.0, 0.0, hg[1], true);	break;
		case InputDir::Right:	DrawRotaGraph(pos.x, pos.y, 2.0, 0.0, hg[2], true);	break;
		}
		
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	}
	else
	{
		switch (keydir)
		{
		case InputDir::Left:	DrawRotaGraph(pos.x, pos.y, 2.0, 0.0, hg[0], true);	break;
		case InputDir::Neutral:	DrawRotaGraph(pos.x, pos.y, 2.0, 0.0, hg[1], true);	break;
		case InputDir::Right:	DrawRotaGraph(pos.x, pos.y, 2.0, 0.0, hg[2], true);	break;
		}
	}
}


void Player::Draw_Game()
{
	switch (keydir)
	{
	case InputDir::Left:	DrawRotaGraph(pos.x, pos.y, 2.0, 0.0, hg[0], true);	break;
	case InputDir::Neutral:	DrawRotaGraph(pos.x, pos.y, 2.0, 0.0, hg[1], true);	break;
	case InputDir::Right:	DrawRotaGraph(pos.x, pos.y, 2.0, 0.0, hg[2], true);	break;
	}

	/// �������ɃV�[���h�A�j��
}


void Player::Draw_Dead()
{
	if (elapsedTime % 4 >= 2)						// 2fps���Ɍ��̐F�ɖ߂�
	{
		//SetDrawBlendMode(DX_BLENDMODE_INVSRC, 100);	// On-Damage-Effect
		//SetDrawBright(255, 0, 0);
		//SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
		//SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);

		SetDrawBright(255, 0, 0);	// �ԐF�ɐݒ�
	}

	switch (keydir)
	{
	case InputDir::Left:	DrawRotaGraph(pos.x, pos.y, 2.0, 0.0, hg[0], true);	break;
	case InputDir::Neutral:	DrawRotaGraph(pos.x, pos.y, 2.0, 0.0, hg[1], true);	break;
	case InputDir::Right:	DrawRotaGraph(pos.x, pos.y, 2.0, 0.0, hg[2], true);	break;
	}

	SetDrawBright(255, 255, 255);	// ���̐F����
}


void Player::SetStart()
{
	if (s_isStart)	return;

	const bool isStartPosition = (pos.y == Y_START);

	c_start->Update();
	pos.y -= 2.0;								// ��ɏ㏸
	pos.y = std::max(pos.y, Y_START);			// �X�^�[�g�n�_�܂�

	if (isStartPosition)	s_isStart = true;	// �X�^�[�g�n�_�Ȃ�X�^�[�g����
}


void Player::InputMng()
{
	const bool KEY_STAY_RIGHT = ( Keyboard_Get(KEY_INPUT_RIGHT) >= 30 );
	const bool KEY_STAY_LEFT  = ( Keyboard_Get(KEY_INPUT_LEFT) >= 30 );
	const bool PUSH_Z_KEY     = ( Keyboard_Get(KEY_INPUT_Z) == 1 );

	keydir = InputDir::Neutral;						// �L�[���j���[�g�����ɂ���
	
	if (KEY_STAY_RIGHT)	keydir = InputDir::Right;

	if (KEY_STAY_LEFT)	keydir = InputDir::Left;

	if (PUSH_Z_KEY && s_powlv == 0)	Shift(true);	// ���̏�Ԃŉ����Ɩ������łP�i�K�A�b�v
}


void Player::Move()
{
	const bool INPUT_HORIZONTAL  = Keyboard_Get(KEY_INPUT_RIGHT) >= 1 || Keyboard_Get(KEY_INPUT_LEFT) >= 1;
	const bool INPUT_VERTICAL    = Keyboard_Get(KEY_INPUT_UP)    >= 1 || Keyboard_Get(KEY_INPUT_DOWN) >= 1;
	const bool KEY_STAY_RIGHT    = Keyboard_Get(KEY_INPUT_RIGHT) >= 1;
	const bool KEY_STAY_LEFT     = Keyboard_Get(KEY_INPUT_LEFT)  >= 1;
	const bool KEY_STAY_UP       = Keyboard_Get(KEY_INPUT_UP)    >= 1;
	const bool KEY_STAY_DOWN     = Keyboard_Get(KEY_INPUT_DOWN)  >= 1;
	double speed;


	// �X�s�[�h�ݒ�
	if(INPUT_HORIZONTAL)
	{
		if (INPUT_VERTICAL)	speed = (1 / 1.41421356) * SpeedForce;	// (1 / ��2) * speed    // �΂߂̂Ƃ�
		else				speed = SpeedForce;						// �΂ߕ␳����
	}
	else if(INPUT_VERTICAL)	speed = SpeedForce;						// �㉺�݂̂̈ړ�

	// �ړ�������
	if (KEY_STAY_RIGHT)	pos.x += speed;
	if (KEY_STAY_LEFT)	pos.x -= speed;
	if (KEY_STAY_UP)	pos.y -= speed;
	if (KEY_STAY_DOWN)	pos.y += speed;

	// �ړ��\�͈͂�ݒ�
	Vector2D::BorderStop(&pos.x, LimitScreenXL, LimitScreenXR);
	Vector2D::BorderStop(&pos.y, LimitScreenYT, LimitScreenYB);
}


void Player::CopyStaticMem()
{
	s_pos		= pos;
	s_bombNum	= bombNum;
	s_life		= life;
	s_isDead	= isDead;
	s_isMuteki	= isMuteki;
}


void Player::Rensha_Update()
{
	// �A�˃Q�[�W���Z-----------------------------------------------------
	if(Keyboard_Get(KEY_INPUT_Z) == 1 || Keyboard_Get(KEY_INPUT_A) == 1){
		if(s_rensha < 41)	s_rensha++;
	}

	// -------------------------------------------------------------------
	switch (s_powlv)
	{
	case 0:	s_rensha = 0;	break;
	case 1:	if (Stage::GetTime() % 17 == 0)	s_rensha--;	break;
	case 2:	if (Stage::GetTime() % 12 == 0)	s_rensha--;	break;
	case 3: if (Stage::GetTime() % 11 == 0)	s_rensha--;	break;
	case 4: if (Stage::GetTime() % 10 == 0)	s_rensha--;	break;

	default: assert(!"�s���ȏ��"); break;
	}

	// -------------------------------------------------------------------
	switch (s_rensha)
	{
	case 0:		
		if(s_powlv != 0) Shift(false);
		break;
	case 40:	if (s_powlv != 4)	Shift(true);
		break;
	}
}


void Player::Shift(const bool isUP)
{
	if (isUP) {
		s_powlv++;											// �e���x�����P�i�K�p���[�A�b�v
		if (s_powlv != 1)
		{
			s_rensha = 1 + (2 * s_powlv);	// �V�t�g�A�b�v�{�[�i�X�S������
			PlaySoundMem(hs_shiftUp, DX_PLAYTYPE_BACK);
		}
	}
	else {
		s_powlv--;
		s_rensha = MAX_RENSHA - 4;
		if (s_powlv == 0)	s_rensha = 0;
		if(s_powlv != 0)	PlaySoundMem(hs_shiftDown, DX_PLAYTYPE_BACK);
	}

	s_powlv = std::min(MaxPowLevel, std::max(0, s_powlv));	// ���x�������͈͓̔��ɂ���

//	effector->Shift(isUP, s_powlv);							// �V�t�g���x���ɉ��������o���J�n
}

void Player::AddBomb(){
	bombNum++;
}


void Player::ShiftReset()
{
	s_powlv = 0;
}

void Player::DownBombNum()
{
	if (bombNum == 0)	return;
	bombNum--;
}


void Player::GetPos(double* x, double* y)
{
	*x = this->pos.x;
	*y = this->pos.y;
}


Vector2D& Player::GetPos(){
	return pos;
}

// Static Methods ---------------------------------------------------------------------------------


int Player::GetShiftLevel(){
	return s_powlv;
}


int Player::GetBombNum(){
	return s_bombNum;
}


int Player::GetLife(){
	return s_life;
}


int Player::GetRensha(){
	return s_rensha;
}


bool Player::IsDead(){
	return s_isDead;
}


bool Player::IsMuteki(){
	return s_isMuteki;
}


bool Player::IsStart(){
	return s_isStart;
}


bool Player::HitCheckCircle(const double& ColX, const double& ColY)
{
	if (state == ePlayerState_Dead)	return false;

	const bool& IS_HIT = (Vector2D::CirclePointCollision(s_pos.x, s_pos.y + 9.0, ColX, ColY, HIT_RANGE));

	if(IS_HIT && state == ePlayerState_Game)
	{
		s_powlv = 0;
		state = ePlayerState_Dead;
		isHit = true;
		s_isMuteki = true;
		vec.SetVecor2D(std::cos(1.5 * GetRand(100)), 1.5 * std::cos(GetRand(100)));
		Game::PlaySpread(s_pos.x, s_pos.y, GetRand(100), dead_ef);
		PlaySoundMem(hs_dead, DX_PLAYTYPE_BACK);
	}

	return IS_HIT;
}


bool Player::HitCheckCircle(const double & Range1, const double & Range2, const double & X1, const double & Y1, const double & X2, const double & Y2)
{
	if (state == ePlayerState_Dead)	return false;

	const bool& IS_HIT = (Vector2D::CirclesCollision(Range1, Range2, X1, Y1, X2, Y2));

	if(IS_HIT && state == ePlayerState_Game)
	{
		s_powlv = 0;
		state = ePlayerState_Dead;
		isHit = true;
		s_isMuteki = true;
		vec.SetVecor2D(std::cos(1.5 * GetRand(100)), 1.5 * std::cos(GetRand(100)));
		Game::PlaySpread(s_pos.x, s_pos.y, GetRand(100), dead_ef);
		Game::PlayQuake();
		PlaySoundMem(hs_dead, DX_PLAYTYPE_BACK);
	}

	return IS_HIT;
}
