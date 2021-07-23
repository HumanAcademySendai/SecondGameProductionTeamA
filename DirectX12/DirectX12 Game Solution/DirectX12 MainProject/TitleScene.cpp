//
// TitleScene.cpp
//

#include "Base/pch.h"
#include "Base/dxtk.h"
#include "SceneFactory.h"

// Initialize member variables.
TitleScene::TitleScene() : dx9GpuDescriptor{}
{

}

// Initialize a variable and audio resources.
void TitleScene::Initialize()
{
    //タイトルの初期化
    titlePosition.x = 0.0f;
    titlePosition.y = 0.0f;
    titlePosition.z = 0.0f;

    //スタートボタンの初期化
    startButtonPosition.x = 0.0f;
    startButtonPosition.y = 0.0f;
    startButtonPosition.z = START_BUTTON_POSITION_Z;
    startButtonFlash = 0.0f;

    //シーン切り替えの初期化
    sceneChangeFlag = false;

    //ブラックアウトの初期化
    blackPosition.x = 0.0f;
    blackPosition.y = 0.0f;
    blackPosition.z = SCREEN_START_POSITION_Z;
    screenAlpha = 0.0f;

    //SEの初期化
    seDecision = XAudio::CreateSoundEffect(DXTK->AudioEngine, L"SE/decision_se.wav");
    sceneCount = 0.0f;
}

// Allocate all memory the Direct3D and Direct2D resources.
void TitleScene::LoadAssets()
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
    //タイトル
    titleSprite       = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Scene/title_bg.png"   );
    startButtonSprite = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Scene/title_start.png");

    //ブラックアウト
    blackSprite = DX9::Sprite::CreateFromFile(DXTK->Device9, L"BG/Black.png");

    //BGM
    mediaTitlebgm = DX9::MediaRenderer::CreateFromFile(DXTK->Device9, L"BGM/title_bgm.mp3");
    mediaTitlebgm->Play();

}

// Releasing resources required for termination.
void TitleScene::Terminate()
{
	DXTK->ResetAudioEngine();
	DXTK->WaitForGpu();

	// TODO: Add your Termination logic here.

}

// Direct3D resource cleanup.
void TitleScene::OnDeviceLost()
{

}

// Restart any looped sounds here
void TitleScene::OnRestartSound()
{

}

// Updates the scene.
NextScene TitleScene::Update(const float deltaTime)
{
	// If you use 'deltaTime', remove it.
	UNREFERENCED_PARAMETER(deltaTime);

	// TODO: Add your game logic here.


   auto scene= TitleSceneUpdate(deltaTime);
   if (scene != NextScene::Continue)
       return scene;

   BgmUpdate(deltaTime);

	return NextScene::Continue;
}

// Draws the scene.
void TitleScene::Render()
{
    // TODO: Add your rendering code here.
    DXTK->Direct3D9->Clear(DX9::Colors::RGBA(0, 0, 0, 255));

    DXTK->Direct3D9->BeginScene();
    DX9::SpriteBatch->Begin();

    //タイトルの描画
    DX9::SpriteBatch->DrawSimple(
        titleSprite.Get(),
        titlePosition);

    //スタートボタンの描画
    if ((int)startButtonFlash % 2 == 0) {
        DX9::SpriteBatch->DrawSimple(
            startButtonSprite.Get(),
            startButtonPosition);
    }
   
    //ブラックアウトの描画
    DX9::SpriteBatch->DrawSimple(
        blackSprite.Get(),
        SimpleMath::Vector3(blackPosition),
        nullptr,
        DX9::Colors::Alpha(screenAlpha));


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

NextScene TitleScene::TitleSceneUpdate(const float deltaTime) {
    //シーン切り替え
    if (sceneChangeFlag == false) {
        if (DXTK->KeyEvent->pressed.Enter ||
            DXTK->KeyEvent->pressed.Space ||
            DXTK->GamePadEvent->a     == GamePad::ButtonStateTracker::PRESSED ||
            DXTK->GamePadEvent->start == GamePad::ButtonStateTracker::PRESSED) {
            sceneChangeFlag = true;
            seDecision->Play();
        }
    }

    if (sceneChangeFlag == true) {
        startButtonFlash  += START_BUTTON_FLASH_SPEED  * deltaTime;
        screenAlpha += SCREEN_ALPHA_COUNT * deltaTime;
        if (screenAlpha > SCREEN_ALPHA_LIMIT) {
            return NextScene::openingScene;
        }
        if (startButtonFlash > START_BUTTON_FLASH_LIMIT_COUNT) {
            startButtonFlash = 0.0f;
        }
    }

    return NextScene::Continue;
}

void TitleScene::BgmUpdate(const float deltaTime) {
    if (mediaTitlebgm->isComplete()) {
        mediaTitlebgm->Replay();
    }
}