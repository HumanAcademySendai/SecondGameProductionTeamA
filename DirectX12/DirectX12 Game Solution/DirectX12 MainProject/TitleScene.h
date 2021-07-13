//
// TitleScene.h
//

#pragma once

#include "Scene.h"

using Microsoft::WRL::ComPtr;
using std::unique_ptr;
using std::make_unique;
using namespace DirectX;

class TitleScene final : public Scene {
public:
	TitleScene();
	virtual ~TitleScene() { Terminate(); }

	TitleScene(TitleScene&&) = default;
	TitleScene& operator= (TitleScene&&) = default;

	TitleScene(TitleScene const&) = delete;
	TitleScene& operator= (TitleScene const&) = delete;

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

	// ïœêîÇÃêÈåæ

	DX9::SPRITE titleSprite;
	SimpleMath::Vector3 titlePosition;
	bool sceneChangeFlag;

	DX9::SPRITE titleStartSprite;
	SimpleMath::Vector3 titleStartPosition;
	float startFlash;

	DX9::MEDIARENDERER mediaTitlebgm;

	XAudio::SOUNDEFFECT seDecision;
	float sceneCount;



	const float TITLE_START_POSITION_X = 0.0f;
	const float TITLE_START_POSITION_Y = 0.0f;
	const float TITLE_START_POSITION_Z = 0.0f;
	const float START_POSITION_Z = -1.0f;
	const float START_FLASH_SPEED = 10.0f;
	const float START_FLASH_LIMIT_COUNT = 10.0f;
	const float SCENECHANGE_LIMIT_TIME = 1.0f;

private:
	NextScene TitleSceneUpdate(const float deltaTime);
	void BgmUpdate(const float deltaTime);

};