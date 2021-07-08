//
// ClearScene.h
//

#pragma once

#include "Scene.h"

using Microsoft::WRL::ComPtr;
using std::unique_ptr;
using std::make_unique;
using namespace DirectX;

class ClearScene final : public Scene {
public:
    ClearScene();
    virtual ~ClearScene() { Terminate(); }

    ClearScene(ClearScene&&) = default;
    ClearScene& operator= (ClearScene&&) = default;

    ClearScene(ClearScene const&) = delete;
    ClearScene& operator= (ClearScene const&) = delete;

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
    //クリア
    DX9::SPRITE clearSprite;
    SimpleMath::Vector3 clearPosition;
    int clearSceneChangeState;
    enum SCENESTATE
    {
        RETURN_SCENE,
        TITLE_SCENE
    };

    //ポインター
    DX9::SPRITE pointerSprite;
    SimpleMath::Vector3 pointerPosition;
    float pointerFlash;

    //BGM
    DX9::MEDIARENDERER mediaClearbgm;

    //SE
    XAudio::SOUNDEFFECT sePointer;
    XAudio::SOUNDEFFECT seDecision;
    bool sePlayFlagNext;
    bool sePlayFlagReturn;
    bool sePlayFlagTitle;
    float seCount;

    //定数
    //クリア
    const float CLEAR_START_POSITION_X = 0.0f;
    const float CLEAR_START_POSITION_Y = 0.0f;
    const float CLEAR_START_POSITION_Z = 0.0f;

    //ポインター
    const float POINTER_START_POSITION_X  = 453.0f;
    const float POINTER_NEXT_POSITION_Y   = 457.0f;
    const float POINTER_RETURN_POSITION_Y = 538.0f;
    const float POINTER_TITLE_POSITION_Y  = 614.0f;
    const float POINTER_START_POSITION_Z  = -1.0f;
    const float POINTER_FLASH_SPEED       = 3.0f;
    const float POINTER_FLASH_LIMIT_COUNT = 10.0f;

    const float SCENE_CHANGE_COUNT = 1.0f;

private:
    NextScene ClearSceneUpdate(const float deltaTime);

    void ClearPointerUpdate(const float deltaTime);
};