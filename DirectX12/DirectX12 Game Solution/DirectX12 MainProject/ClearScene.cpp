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
    clearPosition.x = CLEAR_START_POSITION_X;
    clearPosition.y = CLEAR_START_POSITION_Y;
    clearPosition.z = CLEAR_START_POSITION_Z;

    jewelryPosition.x = JEWELRY_START_POSITION_X;
    jewelryPosition.y = JEWELRY_START_POSITION_Y;
    jewelryPosition.z = JEWELRY_START_POSITION_Z;

    //DontDestroy->jewelryCount = 3;

    clearSceneChangeState = NEXT_STAGE;

    pointerPosition.x = POINTER_START_POSITION_X;
    pointerPosition.y = POINTER_NEXT_POSITION_Y;
    pointerPosition.z = POINTER_START_POSITION_Z;

    pointerFlash = 0.0f;

    sePointer = XAudio::CreateSoundEffect(DXTK->AudioEngine, L"SE/pointer_se.wav");
    seDecision = XAudio::CreateSoundEffect(DXTK->AudioEngine, L"SE/decision_se.wav");

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
    //クリア画面
    clearSprite   = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Scene/c_bg.png"      );

    //宝
    jewelrySprite = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Scene/jewelry_bg.png");

    //ポインター
    pointerSprite = DX9::Sprite::CreateFromFile(DXTK->Device9, L"UI/pointer.png");

    //BGM
    mediaClearbgm= DX9::MediaRenderer::CreateFromFile(DXTK->Device9, L"BGM/clear_bgm.mp3");
    mediaClearbgm->Play();
    if (mediaClearbgm->isComplete()) {
        mediaClearbgm->Replay();
    }
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

    auto scene = ClearSceneUpdate(deltaTime);
    if (scene != NextScene::Continue)
        return scene;

    ClearPointerUpdate(deltaTime);

    return NextScene::Continue;
}

// Draws the scene.
void ClearScene::Render()
{
    // TODO: Add your rendering code here.
    DXTK->Direct3D9->Clear(DX9::Colors::White);// RGBA(0, 0, 0, 255));

    DXTK->Direct3D9->BeginScene();
    DX9::SpriteBatch->Begin();


    //クリア画面の描画
    DX9::SpriteBatch->DrawSimple(
        clearSprite.Get(),
        clearPosition);

    //宝石の描画
    if (DontDestroy->jewelryCount == 0) {
        DX9::SpriteBatch->DrawSimple(
            jewelrySprite.Get(),
            jewelryPosition,
            RectWH(0, 0, 0, JEWELRY_HEIGHT));
    }
    else if (DontDestroy->jewelryCount == 1) {
        DX9::SpriteBatch->DrawSimple(
            jewelrySprite.Get(),
            jewelryPosition,
            RectWH(0, 0, JEWELRY_WIDTH_1, JEWELRY_HEIGHT));
    }
    else if (DontDestroy->jewelryCount == 2) {
        DX9::SpriteBatch->DrawSimple(
            jewelrySprite.Get(),
            jewelryPosition,
            RectWH(0, 0, JEWELRY_WIDTH_2, JEWELRY_HEIGHT));
    }
    else {
        DX9::SpriteBatch->DrawSimple(
            jewelrySprite.Get(),
            jewelryPosition,
            RectWH(0, 0, JEWELRY_WIDTH_3, JEWELRY_HEIGHT));
    }
    
    //ポインターの描画
    if ((int)pointerFlash % 2 == 0) {
        DX9::SpriteBatch->DrawSimple(
            pointerSprite.Get(),
            pointerPosition);
    }
    else
    {

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

NextScene ClearScene::ClearSceneUpdate(const float deltaTime) {
    if (clearSceneChangeState < NEXT_STAGE) {
        clearSceneChangeState = NEXT_STAGE;
    }
    if (clearSceneChangeState > TITLE_SCENE) {
        clearSceneChangeState = TITLE_SCENE;
    }

    if (clearSceneChangeState == NEXT_STAGE) {
        pointerPosition.y = POINTER_NEXT_POSITION_Y;
        /*if (DXTK->KeyEvent->pressed.Enter ||
            DXTK->GamePadEvent[0].start == GamePad::ButtonStateTracker::PRESSED ||
            DXTK->GamePadEvent[0].a     == GamePad::ButtonStateTracker::PRESSED) {
            return NextScene::MainScene2;
        }*/
    }
     if (clearSceneChangeState == RETURN_SCENE) {
        pointerPosition.y = POINTER_RETURN_POSITION_Y;
        if (DXTK->KeyEvent->pressed.Enter ||
            DXTK->GamePadEvent[0].start == GamePad::ButtonStateTracker::PRESSED ||
            DXTK->GamePadEvent[0].a     == GamePad::ButtonStateTracker::PRESSED) {
            return NextScene::MainScene;
        }
    }
     if (clearSceneChangeState == TITLE_SCENE) {
        pointerPosition.y = POINTER_TITLE_POSITION_Y;
        if (DXTK->KeyEvent->pressed.Enter ||
            DXTK->GamePadEvent[0].start == GamePad::ButtonStateTracker::PRESSED ||
            DXTK->GamePadEvent[0].a     == GamePad::ButtonStateTracker::PRESSED) {
            return NextScene::TitleScene;
        }
    }
    return NextScene::Continue;
}

void ClearScene::ClearPointerUpdate(const float deltaTime) {
    if (DXTK->KeyEvent->pressed.Down ||
        DXTK->GamePadEvent[0].leftStickDown == GamePad::ButtonStateTracker::PRESSED) {
        clearSceneChangeState++;
    }

    if (DXTK->KeyEvent->pressed.Up ||
        DXTK->GamePadEvent[0].leftStickUp == GamePad::ButtonStateTracker::PRESSED) {
        clearSceneChangeState--;
    }

    pointerFlash += POINTER_FLASH_SPEED * deltaTime;
    if (pointerFlash >= POINTER_FLASH_LIMIT_COUNT) {
        pointerFlash = 0;
    }
}