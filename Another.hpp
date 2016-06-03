#pragma once

#include "BaseScene.hpp"
#include "ISceneChanger.hpp"
#include "Graphics2D.hpp"
#include "Particle.hpp"
#include "Counter.hpp"
#include <memory>
#include <array>


class Another : public BaseScene, public Graphics2D
{
private:
	const int MOVE_TIME;
	const double FIRST_POS_X;
	const double FIRST_POS_Y;
	const double FIRST_EXRATE;
	std::unique_ptr<Particle> testPTCL;
	std::unique_ptr<Counter>  c_start, c_candle;
	std::array<double, 6> x_candle;				// �낤�������W
	std::array<double, 3> y_candle, ert_candle;	// �낤�����̑傫��
	std::array<double, 6> x_tgt, y_tgt;			// �ړI�n
	std::array<double, 3> ert_tgt;				// �ړI�{��
	int		gh_myface;
	int		gh_ptcl;
	int		gh_candle;
	int		gh_doll;
	int		sh_bgm, sh_namu;
	bool	isMove;
	bool	isPause;
	bool	isStart;
	
	// TEST
	int test_c;

private:
	void PlayBGM();

public:
	Another::Another(ISceneChanger* changer);
	~Another();
	void Update() override;     //�X�V�������I�[�o�[���C�h�B
	void Draw() override;       //�`�揈�����I�[�o�[���C�h�B
};
