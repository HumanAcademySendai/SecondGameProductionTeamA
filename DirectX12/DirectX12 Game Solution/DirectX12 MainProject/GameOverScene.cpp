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
    //ゲームオーバーの初期化
    gameoverPosition.x = 0.0f;
    gameoverPosition.y = 0.0f;
    gameoverPosition.z = 0.0f;

    //シーン切り替えの初期化
    sceneChangeState = RETURN_SCENE;

    //ポインターの初期化
    pointerPosition.x = POINTER_START_POSITION_X;
    pointerPosition.y = POINTER_RETURN_POSITION_Y;
    pointerPosition.z = POINTER_START_POSITION_Z;
    pointerFlash      = 0;
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


    // グラフィックリソースの初期化処理
    //フォント
    font = DX9::SpriteFont::CreateFromFontName(DXTK->Device9, L"HG丸ｺﾞｼｯｸM-PRO", 20);

    //ゲームオーバー
    gameoverSprite = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Scene/gameover_bg.png");

    //ポインター
    pointerSprite  = DX9::Sprite::CreateFromFile(DXTK->Device9, L"UI/pointer.png");

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

    GameOverPointerUpdate(deltaTime);

    return NextScene::Continue;
}

// Draws the scene.
void GameOverScene::Render()
{
    // TODO: Add your rendering code here.
    DXTK->Direct3D9->Clear(DX9::Colors::RGBA(0, 0, 0, 255));

    DXTK->Direct3D9->BeginScene();
    DX9::SpriteBatch->Begin();

    //ゲームオーバーの描画
    DX9::SpriteBatch->DrawSimple(
        gameoverSprite.Get(),
        gameoverPosition);

    //ポインターの描画
    if ((int)pointerFlash % 2 == 0) {
        DX9::SpriteBatch->DrawSimple(
            pointerSprite.Get(),
            pointerPosition);
    }
    else
    {

    }
    
    //フォント
    /*DX9::SpriteBatch->DrawString(
        font.Get(),
        SimpleMath::Vector2(0.0f, 670.0f),
        DX9::Colors::Black,
        L" P移動 %f", pointerPosition.y
    );*/

    /*DX9::SpriteBatch->DrawString(
        font.Get(),
        SimpleMath::Vector2(0.0f, 670.0f),
        DX9::Colors::Black,
        L" ポインターの点滅 %f", pointerFlash
    );*/

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
            DXTK->GamePadEvent->dpadDown == GamePad::ButtonStateTracker::PRESSED) {
            sceneChangeState  = TITLE_SCENE;
            pointerPosition.y = POINTER_TITLE_POSITION_Y;
        }

    if (sceneChangeState == TITLE_SCENE)
        if (DXTK->KeyEvent->pressed.Up ||
            DXTK->GamePadEvent->dpadUp == GamePad::ButtonStateTracker::PRESSED) {
            sceneChangeState  = RETURN_SCENE;
            pointerPosition.y = POINTER_RETURN_POSITION_Y;
        }

    if (sceneChangeState == RETURN_SCENE) {
        if (DXTK->KeyEvent->pressed.Enter ||
            DXTK->GamePadEvent->start == GamePad::ButtonStateTracker::PRESSED) {
            return NextScene::MainScene;
        }
    }

    if (sceneChangeState == TITLE_SCENE) {
        if (DXTK->KeyEvent->pressed.Enter ||
            DXTK->GamePadEvent->start == GamePad::ButtonStateTracker::PRESSED) {
            return NextScene::TitleScene;
        }
    }

    return NextScene::Continue;
}
void GameOverScene::GameOverPointerUpdate(const float deltaTime) {
    pointerFlash += POINTER_FLASH_SPEED * deltaTime;
    if (pointerFlash >= POINTER_FLASH_LIMIT_COUNT) {
        pointerFlash = 0;
    }
}