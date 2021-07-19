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
    //�Q�[���I�[�o�[�̏�����
    gameoverPosition.x = 0.0f;
    gameoverPosition.y = 0.0f;
    gameoverPosition.z = 0.0f;

    //�V�[���؂�ւ��̏�����
    sceneChangeState = RETURN_SCENE;

    //�|�C���^�[�̏�����
    pointerPosition.x = POINTER_START_POSITION_X;
    pointerPosition.y = POINTER_RETURN_POSITION_Y;
    pointerPosition.z = POINTER_START_POSITION_Z;
    pointerFlash      = 0;

    //SE
    sePointer = XAudio::CreateSoundEffect(DXTK->AudioEngine, L"SE/pointer_se.wav");
    seDecision = XAudio::CreateSoundEffect(DXTK->AudioEngine, L"SE/decision_se.wav");
    seCount = 0.0f;
    sePlayFlagMain = false;
    sePlayFlagTitle = false;
    DontDestroy->collapseSEFlag = false;
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
    //�t�H���g
    font = DX9::SpriteFont::CreateFromFontName(DXTK->Device9, L"HG�ۺ޼��M-PRO", 20);

    //�Q�[���I�[�o�[
    gameoverSprite = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Scene/gameover_bg.png");

    //�|�C���^�[
    pointerSprite  = DX9::Sprite::CreateFromFile(DXTK->Device9, L"UI/pointer.png");

    //BGM
    mediaGameoverbgm = DX9::MediaRenderer::CreateFromFile(DXTK->Device9, L"BGM/gameover_bgm.mp3");
    mediaGameoverbgm->Play();
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

 //Restart any looped sounds here
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

    //�Q�[���I�[�o�[�̕`��
    DX9::SpriteBatch->DrawSimple(
        gameoverSprite.Get(),
        gameoverPosition);

    //�|�C���^�[�̕`��
    if ((int)pointerFlash % 2 == 0) {
        DX9::SpriteBatch->DrawSimple(
            pointerSprite.Get(),
            pointerPosition);
    }
    
    //�t�H���g
    /*DX9::SpriteBatch->DrawString(
        font.Get(),
        SimpleMath::Vector2(0.0f, 670.0f),
        DX9::Colors::Black,
        L" P�ړ� %f", pointerPosition.y
    );*/

    /*DX9::SpriteBatch->DrawString(
        font.Get(),
        SimpleMath::Vector2(0.0f, 670.0f),
        DX9::Colors::Black,
        L" �|�C���^�[�̓_�� %f", pointerFlash
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

    if (sceneChangeState == RETURN_SCENE && sePlayFlagMain == false) {
        if (DXTK->KeyEvent->pressed.Down ||
            DXTK->GamePadEvent->dpadDown      == GamePad::ButtonStateTracker::PRESSED ||
            DXTK->GamePadEvent->leftStickDown == GamePad::ButtonStateTracker::PRESSED) {
            sePointer->Play();
            sceneChangeState = TITLE_SCENE;
            pointerPosition.y = POINTER_TITLE_POSITION_Y;
        }
    }

    if (sceneChangeState == TITLE_SCENE && sePlayFlagTitle == false) {
        if (DXTK->KeyEvent->pressed.Up ||
            DXTK->GamePadEvent->dpadUp      == GamePad::ButtonStateTracker::PRESSED ||
            DXTK->GamePadEvent->leftStickUp == GamePad::ButtonStateTracker::PRESSED) {
            sePointer->Play();
            sceneChangeState = RETURN_SCENE;
            pointerPosition.y = POINTER_RETURN_POSITION_Y;
        }
    }


    if (sceneChangeState == RETURN_SCENE) {
        if (seCount >= SE_TIME) {
            return NextScene::MainScene;
        }
        if (DXTK->KeyEvent->pressed.Enter ||
            DXTK->GamePadEvent->a == GamePad::ButtonStateTracker::PRESSED) {
            sePlayFlagMain = true;
            seDecision->Play();
            DontDestroy->collapseSEFlag = true;
        }
    }

    if (sceneChangeState == TITLE_SCENE) {
        if (seCount >= SE_TIME) {
            return NextScene::TitleScene;
        }
        if (DXTK->KeyEvent->pressed.Enter ||
            DXTK->GamePadEvent->a == GamePad::ButtonStateTracker::PRESSED) {
            sePlayFlagTitle = true;
            seDecision->Play();
        }
    }

    if (sePlayFlagMain == true) {
        seCount += deltaTime;
    }
    if (sePlayFlagTitle == true) {
        seCount += deltaTime;
    }

    return NextScene::Continue;
}
void GameOverScene::GameOverPointerUpdate(const float deltaTime) {
    pointerFlash += POINTER_FLASH_SPEED * deltaTime;
    if (pointerFlash >= POINTER_FLASH_LIMIT_COUNT) {
        pointerFlash = 0;
    }
}