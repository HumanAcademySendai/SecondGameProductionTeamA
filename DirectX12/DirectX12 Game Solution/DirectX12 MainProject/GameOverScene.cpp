//
// GameOverScene.cpp
//

#include "Base/pch.h"
#include "Base/dxtk.h"
#include "SceneFactory.h"

// Initialize member variables.
GameOverScene::GameOverScene() : dx9GpuDescriptor{}
{

}

// Initialize a variable and audio resources.
void GameOverScene::Initialize()
{
    gameoverPosition.x = 0.0f;
    gameoverPosition.y = 0.0f;
    gameoverPosition.z = 0.0f;

    sceneChangeState = RETURN_SCENE;

}

// Allocate all memory the Direct3D and Direct2D resources.
void GameOverScene::LoadAssets()
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


    // �O���t�B�b�N���\�[�X�̏���������

    gameoverSprite = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Scene/gameover_bg.png");

}

// Releasing resources required for termination.
void GameOverScene::Terminate()
{
	DXTK->ResetAudioEngine();
	DXTK->WaitForGpu();

	// TODO: Add your Termination logic here.

}

// Direct3D resource cleanup.
void GameOverScene::OnDeviceLost()
{

}

// Restart any looped sounds here
void GameOverScene::OnRestartSound()
{

}

// Updates the scene.
NextScene GameOverScene::Update(const float deltaTime)
{
    // If you use 'deltaTime', remove it.
    UNREFERENCED_PARAMETER(deltaTime);

    // TODO: Add your game logic here.


    auto scene = GameOverSceneUpdate(deltaTime);
    if (scene != NextScene::Continue)
        return scene;

    return NextScene::Continue;
}

// Draws the scene.
void GameOverScene::Render()
{
    // TODO: Add your rendering code here.
    DXTK->Direct3D9->Clear(DX9::Colors::RGBA(0, 0, 0, 255));

    DXTK->Direct3D9->BeginScene();
    DX9::SpriteBatch->Begin();




    DX9::SpriteBatch->DrawSimple(
        gameoverSprite.Get(),
        gameoverPosition);


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

NextScene GameOverScene::GameOverSceneUpdate(const float deltaTime) {

    if(sceneChangeState == RETURN_SCENE)
        if (DXTK->KeyEvent->pressed.Down ||
            DXTK->GamePadEvent->dpadDown) {
            sceneChangeState = TITLE_SCENE;
        }

    if (sceneChangeState == TITLE_SCENE)
        if (DXTK->KeyEvent->pressed.Up ||
            DXTK->GamePadEvent->dpadUp) {
            sceneChangeState = RETURN_SCENE;
        }

    if (sceneChangeState == RETURN_SCENE) {
        if (DXTK->KeyEvent->pressed.Enter || DXTK->GamePadEvent->start) {
            return NextScene::MainScene;
        }
    }

    if (sceneChangeState == TITLE_SCENE) {
        if (DXTK->KeyEvent->pressed.Enter || DXTK->GamePadEvent->start) {
            return NextScene::TitleScene;
        }
    }

    return NextScene::Continue;
}