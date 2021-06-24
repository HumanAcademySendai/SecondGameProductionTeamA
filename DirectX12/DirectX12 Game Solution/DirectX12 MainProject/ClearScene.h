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

    SimpleMath::Vector3 clearPositoin;
    SimpleMath::Vector3 jewelryPositoin;
    float jewelryWidth;

    const float CLEAR_START_POSITION_X = 0;
    const float CLEAR_START_POSITION_Y = 0;
    const float CLEAR_START_POSITION_Z = 0;

    const float JEWELRY_START_POSITION_X = 0;
    const float JEWELRY_START_POSITION_Y = 0;
    const float JEWELRY_START_POSITION_Z = -1;

    const float JEWELRY_WIDTH_1 = 490;
    const float JEWELRY_WIDTH_2 = 790;
    const float JEWELRY_WIDTH_3 = 1080;
    const float JEWELRY_HEIGHT  = 720;

private:
    void JewelrySprite_Width_Update(const float deltaTime);

};