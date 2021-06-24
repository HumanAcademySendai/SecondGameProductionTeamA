//
// ClearScene.cpp
//

#include "Base/pch.h"
#include "Base/dxtk.h"
#include "SceneFactory.h"
#include "DontDestroyOnLoad.h"

// Initialize member variables.
ClearScene::ClearScene() : dx9GpuDescriptor{}
{

}

// Initialize a variable and audio resources.
void ClearScene::Initialize()
{
    clearPositoin.x = CLEAR_START_POSITION_X;
    clearPositoin.y = CLEAR_START_POSITION_Y;
    clearPositoin.z = CLEAR_START_POSITION_Z;

    jewelryPositoin.x = JEWELRY_START_POSITION_X;
    jewelryPositoin.y = JEWELRY_START_POSITION_Y;
    jewelryPositoin.z = JEWELRY_START_POSITION_Z;

    DontDestroy->jewelryCount = 3;

}

// Allocate all memory the Direct3D and Direct2D resources.
void ClearScene::LoadAssets()
{
    descriptorHeap = DX12::CreateDescriptorHeap(DXTK->Device, 1);

    ResourceUploadBatch resourceUploadBatch(DXTK->Device);
    resourceUploadBatch.Begin();

    RenderTargetState rtState(DXGI_FORMAT_B8G8R8A8_UNORM, DXGI_FORMAT_D32_FLOAT);
    SpriteBatchPipelineStateDescription pd(rtState, &CommonStates::NonPremultiplied);
    D3D12_VIEWPORT viewport = {
        0.0f, 0.0f, 1280.0f, 720.0f,
        D3D12_MIN_DEPTH, D3D12_MAX_DEPTH
    };

    spriteBatch = DX12::CreateSpriteBatch(DXTK->Device, resourceUploadBatch, pd, &viewport);

    dx9GpuDescriptor = DXTK->Direct3D9->CreateShaderResourceView(descriptorHeap.get(), 0);

    auto uploadResourcesFinished = resourceUploadBatch.End(DXTK->CommandQueue);
    uploadResourcesFinished.wait();


    // グラフィックリソースの初期化処理

    clearSprite   = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Scene/c_bg.png"      );
    jewelrySprite = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Scene/jewelry_bg.png");

}

// Releasing resources required for termination.
void ClearScene::Terminate()
{
    DXTK->ResetAudioEngine();
    DXTK->WaitForGpu();

    // TODO: Add your Termination logic here.

}

// Direct3D resource cleanup.
void ClearScene::OnDeviceLost()
{

}

// Restart any looped sounds here
void ClearScene::OnRestartSound()
{

}

// Updates the scene.
NextScene ClearScene::Update(const float deltaTime)
{
    // If you use 'deltaTime', remove it.
    UNREFERENCED_PARAMETER(deltaTime);

    // TODO: Add your game logic here.

    JewelrySprite_Width_Update(deltaTime);

    return NextScene::Continue;
}

// Draws the scene.
void ClearScene::Render()
{
    // TODO: Add your rendering code here.
    DXTK->Direct3D9->Clear(DX9::Colors::RGBA(0, 0, 0, 255));

    DXTK->Direct3D9->BeginScene();
    DX9::SpriteBatch->Begin();


    //クリア画面の描画
    DX9::SpriteBatch->DrawSimple(
        clearSprite.Get(),
        clearPositoin);

    //宝石の描画
    if (DontDestroy->jewelryCount == 0) {
        DX9::SpriteBatch->DrawSimple(
            jewelrySprite.Get(),
            jewelryPositoin,
            RectWH(0, 0, 0, JEWELRY_HEIGHT));
    }
    else if (DontDestroy->jewelryCount == 1) {
        DX9::SpriteBatch->DrawSimple(
            jewelrySprite.Get(),
            jewelryPositoin,
            RectWH(0, 0, JEWELRY_WIDTH_1, JEWELRY_HEIGHT));
    }
    else if (DontDestroy->jewelryCount == 2) {
        DX9::SpriteBatch->DrawSimple(
            jewelrySprite.Get(),
            jewelryPositoin,
            RectWH(0, 0, JEWELRY_WIDTH_2, JEWELRY_HEIGHT));
    }
    else {
        DX9::SpriteBatch->DrawSimple(
            jewelrySprite.Get(),
            jewelryPositoin,
            RectWH(0, 0, JEWELRY_WIDTH_3, JEWELRY_HEIGHT));
    }
    

    DX9::SpriteBatch->End();
    DXTK->Direct3D9->EndScene();

    DXTK->Direct3D9->UpdateResource();

    DXTK->ResetCommand();
    DXTK->ClearRenderTarget(Colors::CornflowerBlue);

    const auto heapes = descriptorHeap->Heap();
    DXTK->CommandList->SetDescriptorHeaps(1, &heapes);

    spriteBatch->Begin(DXTK->CommandList);
    spriteBatch->Draw(
        dx9GpuDescriptor,
        XMUINT2(1280, 720),
        SimpleMath::Vector2(0.0f, 0.0f)
    );
    spriteBatch->End();

    DXTK->Direct3D9->WaitUpdate();
    DXTK->ExecuteCommandList();
}

void ClearScene::JewelrySprite_Width_Update(const float deltaTime) {
    

}