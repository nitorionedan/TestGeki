#pragma once

#include "DxLib.h"


class DebugMode
{
public:
	static void SwitchTest();
	static void Update();
	static void Draw();

	static double enemySpeed;		// �G���x�̊���
	static double enemyShotSpeed;	// �G�e���x�̊���
	static double playerSpeed;		// ���@���x�̊���
	static double playerShotSpeed;	// ���@�e���x�̊���
	static bool isTest;				// �f�o�b�O���[�h�����H
	static bool isSuperEnemy;		// ���G���H
	static bool isSuperPlayer;		// ���G���H

private:
	DebugMode() {}
	~DebugMode() {}

	static bool isConfig;					// �f�o�b�O�p�̐ݒ胂�[�h�����H
};