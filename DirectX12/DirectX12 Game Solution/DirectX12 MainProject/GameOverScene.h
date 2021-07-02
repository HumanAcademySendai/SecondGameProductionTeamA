//
// GameOverScene.h
//

#pragma once

#include "Scene.h"

using Microsoft::WRL::ComPtr;
using std::unique_ptr;
using std::make_unique;
using namespace DirectX;

class GameOverScene final : public Scene {
public:
	GameOverScene();
	virtual ~GameOverScene() { Terminate(); }

	GameOverScene(GameOverScene&&) = default;
	GameOverScene& operator= (GameOverScene&&) = default;

	GameOverScene(GameOverScene const&) = delete;
	GameOverScene& operator= (GameOverScene const&) = delete;

	// These are the functions you will implement.
	void Initialize() override;
	void LoadAssets() override;

	void Terminate() override;

	void OnDeviceLost() override;
	void OnRestartSound() override;

	NextScene Update(const float deltaTime) override;
	void Render() override;

private:
	DX12::DESCRIPTORHEAP descriptorHeap;
	DX12::SPRITEBATCH    spriteBatch;
	DX12::HGPUDESCRIPTOR dx9GpuDescriptor;

	// 変数の宣言
	
	//フォント
	DX9::SPRITEFONT font;

	//ゲームオーバー
	DX9::SPRITE gameoverSprite;
	SimpleMath::Vector3 gameoverPosition;
	int sceneChangeState;
	enum SCENECHANGE_STATE
	{
		RETURN_SCENE,
		TITLE_SCENE
	};
	
	//ポインター
	DX9::SPRITE pointerSprite;
	SimpleMath::Vector3 pointerPosition;
	float pointerFlash;

	//BGM
	DX9::MEDIARENDERER mediaGameoverbgm;

	//SE
	XAudio::SOUNDEFFECT sePointer;
	XAudio::SOUNDEFFECT seDecision;
	float seCount;
	bool sePlayFlagMain;
	bool sePlayFlagTitle;

	//定数
	//ゲームオーバー
	const float GAMEOVER_START_POSITION_X = 0.0f;
	const float GAMEOVER_START_POSITION_Y = 0.0f;
	const float GAMEOVER_START_POSITION_Z = 0.0f;

	//ポインター
	const float POINTER_START_POSITION_X   = 440.0f;
	const float POINTER_RETURN_POSITION_Y  = 458.0f;
	const float POINTER_TITLE_POSITION_Y   = 532.0f;
	const float POINTER_START_POSITION_Z   = 0.0f;
	const float POINTER_FLASH_SPEED        = 3.0f;
	const float POINTER_FLASH_LIMIT_COUNT  = 10.0f;

	const float SE_TIME = 0.4f;

	//関数
private:	
	NextScene GameOverSceneUpdate(const float deltaTime);

	void GameOverPointerUpdate           (const float deltaTime);
};