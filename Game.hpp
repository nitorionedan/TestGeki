#pragma once


#include "BaseScene.hpp"
#include "ISceneChanger.hpp"

#include "Score.hpp"
#include "Graphic.hpp"
#include "Player.hpp"
#include "Graphic.hpp"
#include "Stage.hpp"
#include "Pshot.hpp"
#include "Character.hpp"
#include "StatusBoard.hpp"
#include "Vector2D.hpp"
#include "ItemMng.hpp"

// Enemy�֘A
#include "BossA.hpp"
#include "EshotMng.hpp"
#include "EnemyMng.hpp"
#include "BossChara.hpp"

// �G�t�F�N�g�֘A
#include "Effect.hpp"
#include "Explosion.hpp"
#include "ExplosionEffect.hpp"
#include "ExplosionS.hpp"
#include "PieceEffect.hpp"
#include "Piece.hpp"
#include "ChargeEffect.hpp"

#include <memory>
#include <array>

#define EX_NUM 4

#include "Graphics2D.hpp"


enum eColKind
{
	eCol_CirclePoint,
	eCol_Circle,
	eCol_RectanglePoint,
	eCol_Rectangle,
};


//�Q�[����ʃN���X
class Game : public BaseScene
{
public:
	Game::Game(ISceneChanger* changer);
	~Game();
	void Update() override;     //�X�V�������I�[�o�[���C�h
	void Draw() override;       //�`�揈�����I�[�o�[���C�h
	void GetPlayerPosition(double* x, double* y){}
	void GetEnemyPosition(int index, double *x, double *y){}

	static Vector2D& GetPlayerPos();
	static void AddScore(const int& point);
	static void AddBomb();
	static void PlayAnime(const double& PlayX, const double& PlayY, eExplosion_t type);
	static void PlaySpread(const double& PosX, const double& PosY, const double& ANGLE, eSpread_t type);
	static void PlayQuake();
	static void PlayCharge(double PosX, double PosY);
	static void LoadEnemy(eStage stage);
	static void Pause();
	static void ShiftReset();
	static void ItemDrop(double PosX, double PosY);
	static void ItemDrop(double PosX, double PosY, eItem_type type);
	static void Shift(bool isUp);
	static void StageCall();
	static void GameOver();
	static void DownBombNum();
	static int GetPlayerBomb();
	static bool IsPause();

	// @brief	���@�̉~�Ƒ��̓_�̓����蔻��
	static bool IsHitPlayer(const double& myX, const double& myY);

	// @brief	���@�̉~�Ƒ��̉~�̓����蔻��
	static bool IsHitPlayer(const double& Range1, const double& Range2,
		const double & X1, const double& Y1, const double& X2, const double& Y2);

	static bool IsHitBoss(const double& myX, const double& myY, int& dmgPoint);

private:
	void Update_Status();
	void Draw_StageMsg();
	void Draw_Status();

	std::unique_ptr<Graphic> graphic;
	std::unique_ptr<Counter> c_msg;
	Character* bossShot;	// Character�ɂ����
	Character* board;		// Character�ɂ����

	// static-------------------------------------------------
	static Player* player;
	static Pshot* pshot;
	static Effect* bomber;
	static PieceEffect* pieceef;
	static Effect** effect;
	static Score* score;
	static Stage* stage;
	static BossChara* boss;
	static EnemyMng* enemyMng;
	static ItemMng*	itemMng;
	static bool f_pause;
	static bool isMsg;
	static bool isDead;

	// TEST
};

// EOF