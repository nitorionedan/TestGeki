#include "DxLib.h"

#include "Stage.hpp"
#include "Keyboard.hpp"
#include "BossA.hpp"
#include "DebugMode.hpp"
#include "Game.hpp"

#include <algorithm>
#include <cmath>

#define NOMINMAX


const double Stage::SPEED_BACK		= 1.;
const double Stage::SPEED_MIDDLE	= 3.;
const double Stage::SPEED_FRONT		= 6.;

int Stage::s_time;
int Stage::s_rank;


Stage::Stage()
	: c_quake( new Counter(30) )
	, nowStage(eStage::stage1)
	, cycle(0.)
	, shake(0.)
	, f_quake(false)
{
	hs_bgm = NULL;
	hg.at(eBG_back) = NULL;
	hg.at(eBG_middle) = NULL;
	hg.at(eBG_front) = NULL;

	stage_back.at(0).SetVecor2D(320.0, 240.0);
	stage_back.at(1).SetVecor2D(320.0, -400.0); // pixサイズが例外的に 320 x 320　なので
	stage_mid.at(0).SetVecor2D(320.0, 240.0);
	stage_mid.at(1).SetVecor2D(320.0, -240.0);
	stage_fro.at(0).SetVecor2D(320.0, 240.0);
	stage_fro.at(1).SetVecor2D(320.0, -240.0);
	
	// LoadStage(*.dat);		// こういう風にロードしたい 

	StageSet(nowStage);			// 現在のステージを設定

	s_time = 0;
	s_rank = 0;
}


Stage::~Stage()
{
	for (int &Gr_Handle : hg)	DeleteGraph(Gr_Handle);
	
	if(hs_bgm != NULL)	DeleteSoundMem(hs_bgm);
}


void Stage::StageSet(eStage estage)
{
	// まず素材用のメモリを開放します
	for (int &Gr_Handle : hg)
	{
		if(Gr_Handle != NULL)	DeleteGraph(Gr_Handle);
	}

	if (hs_bgm != NULL)	DeleteSoundMem(hs_bgm);

	// ステージ用素材ロード
	switch (estage)
	{
	case eStage::stage1 :
		hs_bgm				= LoadSoundMem("SOUND/s0.mp3");
		hg.at(eBG_back)		= LoadGraph("GRAPH/GAME/BACKGROUND/RasterOnly/rbg00.png");
		hg.at(eBG_middle)	= LoadGraph("GRAPH/GAME/BACKGROUND/sumple_middle.png");
		hg.at(eBG_front)	= LoadGraph("GRAPH/GAME/BACKGROUND/RasterOnly/rbg01.png");
		break;
	case eStage::stage2 :
		break;
	case eStage::stage3 :
		break;
	case eStage::stage4 :
		break;
	case eStage::stage5 :
		break;
	case eStage::stage6 :
		break;
	case eStage::stage0 :
		break;
	}

	// 敵データを読み込む
	Game::LoadEnemy(estage);
	Game::StageCall();

	PlaySoundMem(hs_bgm, DX_PLAYTYPE_LOOP);
}


void Stage::Update()
{
	// 時間経過
	s_time++;
	if (s_time % 120 == 0)	s_rank++;
	SetVolumeSoundMem(255, hs_bgm);

	Move();

	if (Keyboard_Get(KEY_INPUT_6) == 1)	ChangeVolumeSoundMem(0, hs_bgm);

	// TEST-----------------------------------------------------------------
	if (DebugMode::isTest == false)	return;

	/// 時がくるまで封印
//	if (effect->getIsAnime() && !f_quake)	f_quake = true;
	if (Keyboard_Get(KEY_INPUT_W) >= 1) cycle += 0.1;
	if (Keyboard_Get(KEY_INPUT_S) >= 1) cycle -= 0.1;
	if (Keyboard_Get(KEY_INPUT_D) >= 1) shake += 0.1;
	if (Keyboard_Get(KEY_INPUT_A) >= 1) shake -= 0.1;
}


void Stage::Draw()
{
	for (auto &back : stage_back)	DrawRasterScroll(back.x, back.y, cycle, shake, hg[eBG_back], false);
	for (auto &front : stage_fro)	DrawRasterScroll(front.x, front.y, cycle, shake, hg[eBG_front], false);

	// TEST -------------------------------------------------------------------
	if (DebugMode::isTest == false)	return;

//	DrawFormatString(540, 20, GetColor(0, 255, 0), "TIME:%d sec", testTime);
	DrawFormatString(520, 20, GetColor(0, 255, 0), "TIME:%d", s_time);
//	DrawFormatString(520, 40, GetColor(0, 255, 0), "CYCLE:%lf", cycle);
//	DrawFormatString(520, 60, GetColor(0, 255, 0), "SHAKE:%lf", shake);
}


void Stage::Move()
{
	// スクロール
	for (auto &back : stage_back)
	{
		back.y += SPEED_BACK;
		back.y = static_cast<double>(WrapPos(static_cast<int>(back.y), 880, -400));
	}

	for (auto &middle : stage_mid)
	{
		middle.y += SPEED_MIDDLE;
		middle.y = static_cast<double>(WrapPos(static_cast<int>(middle.y), 720, -240));
	}

	for (auto &front : stage_fro)
	{
		front.y += SPEED_FRONT;
		front.y = static_cast<double>(WrapPos(static_cast<int>(front.y), 720, -240));
	}

	Quake();	// ぶるぶる
}


void Stage::NextStage()
{
	const bool NOT_STAGE0 = nowStage != eStage::stage0;

	StopSoundMem(hs_bgm); // NEXT STAGE のために音楽を停止
	
	if (NOT_STAGE0)
		nowStage = static_cast<eStage>(static_cast<int>(nowStage) + 1);
	else
		AllClear();
}


void Stage::Clear()
{

}


void Stage::AllClear()
{
	printfDx("全クリだよ。おめでとさん。\n");
	nowStage = eStage::stage1;
}


void Stage::PlayQuake(){
	f_quake = true;
}


void Stage::Quake()
{
	if (!f_quake)	return;	// 震えていなければスルー
	
	c_quake->Update();
	
	double offsetB, offsetF;

	offsetB = GetRand(2) + 2;
	offsetF = GetRand(2) + 2;
	
	if (c_quake->Remainder(4) >= 2)
	{
		for (auto &back : stage_back)
		{
			back.x -= offsetB;
			back.y += 2.;
		}
		
		for (auto &front : stage_fro)
		{
			front.x += offsetF;
			front.y -= 2.;
		}
	}
	if (c_quake->Remainder(4) <= 1)
	{
		for (auto &back : stage_back)
		{
			back.x += offsetB;
			back.y += 2.;
		}
	
		for (auto &front : stage_fro)
		{
			front.x -= offsetF;
			front.y -= 2.;
		}
	}

	if (!c_quake->isLast()) return;		// 振動停止

	for (auto &back : stage_back)
	{
		back.x = 320.;
	}
	
	for (auto &front : stage_fro)
	{
		front.x = 320.;
	}
	
	c_quake->Reset();
	f_quake = false;	// 振動をやめる
}


int Stage::WrapPos(int val, int max, int min)
{
	if (max <= min)
	{
		printfDx("ERROR : max < min");
		return -1;
	}
	const int offset = (val - min) % (max - min);
	return (offset >= 0) ? (offset + min) : (offset + max);
}


int Stage::GetTime(){
	return s_time;
}
