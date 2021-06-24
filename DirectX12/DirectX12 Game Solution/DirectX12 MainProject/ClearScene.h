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

    // ïœêîÇÃêÈåæ

    DX9::SPRITE clearSprite;
    DX9::SPRITE jewelrySprite;
    DX9::SPRITE pointerSprite;

    SimpleMath::Vector3 clearPositoin;

    SimpleMath::Vector3 jewelryPositoin;
    float jewelryWidth;

    SimpleMath::Vector3 pointerPosition;

    
    int clearSceneChangeState;
    enum SCENESTATE
    {
        NEXT_STAGE,
        RETURN_SCENE,
        TITLE_SCENEN
    };


    const float CLEAR_START_POSITION_X = 0.0f;
    const float CLEAR_START_POSITION_Y = 0.0f;
    const float CLEAR_START_POSITION_Z = 0.0f;

    const float JEWELRY_START_POSITION_X = 0.0f;
    const float JEWELRY_START_POSITION_Y = 0.0f;
    const float JEWELRY_START_POSITION_Z = -1.0f;

    const float JEWELRY_WIDTH_1 = 490.0f;
    const float JEWELRY_WIDTH_2 = 790.0f;
    const float JEWELRY_WIDTH_3 = 1080.0f;
    const float JEWELRY_HEIGHT  = 720.0f;

    const float POINTER_START_POSITION_X = 453.0f;
    const float POINTER_START_POSITION_Y = 457.0f;

private:
   // NextScene ClearSceneUpdate(const float deltaTime);
};