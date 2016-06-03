#include "DxLib.h"

#include "DebugMode.hpp"
#include "Keyboard.hpp"
#include "Game.hpp"


double	DebugMode::enemySpeed		= 1.;
double	DebugMode::enemyShotSpeed	= 1.;
double	DebugMode::playerSpeed		= 1.;
double	DebugMode::playerShotSpeed	= 1.;
bool	DebugMode::isTest			= true;
bool	DebugMode::isSuperEnemy		= false;
bool	DebugMode::isSuperPlayer	= false;
bool	DebugMode::isConfig			= false;


void DebugMode::SwitchTest()
{
	isTest = !isTest;
	clsDx();
}


void DebugMode::Update()
{
	if (!isTest)	return;

	if (Keyboard_Get(KEY_INPUT_F2) == 1)
	{
		isConfig = !isConfig;
		Game::Pause();
	}

	if(isConfig){}
}


void DebugMode::Draw()
{
	if (!isTest)	return;

	DrawFormatString(0, 20, GetColor(255, 0, 0), "DEBUG_MODE_NOW : OPTION[F2]");
}
