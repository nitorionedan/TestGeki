#pragma once

#include "ISceneChanger.hpp"
#include "BaseScene.hpp"


class SceneMng : public ISceneChanger, Task
{
public:
	SceneMng   ();
	~SceneMng();
	virtual void Update() override; // 更新
	virtual void Draw  () override; // 描画

	// 引数 nextScene にシーンを変更する
	void ChangeScene(eScene NextScene) override;

private:
	BaseScene* mScene;     // シーン管理変数 (※任意のタイミングでメモリの確保、解放をします)
	eScene     mNextScene; // 次のシーン管理変数
};