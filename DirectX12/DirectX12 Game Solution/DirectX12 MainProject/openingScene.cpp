//
// openingScene.cpp
//

#include "Base/pch.h"
#include "Base/dxtk.h"
#include "SceneFactory.h"

// Initialize member variables.
openingScene::openingScene() : dx9GpuDescriptor{}
{

}

// Initialize a variable and audio resources.
void openingScene::Initialize()
{
    //背景の初期化
    bgPosition.x = 0.0f;
    bgPosition.y = 0.0f;
    bgPosition.z = 100.0f;

    //ブラックアウト
    blackPosition.x = 0.0f;
    blackPosition.y = 0.0f;
    blackPosition.z = SCREEN_START_POSITION_Z;
    screenAlpha = 255;

    //松明の初期化
    torchPosition[0].x = TORCH_START_POSITION_X_1;
    torchPosition[0].y = TORCH_START_POSITION_Y;
    torchPosition[0].z = TORCH_START_POSITION_Z;
    torchPosition[1].x = TORCH_START_POSITION_X_2;
    torchPosition[1].y = TORCH_START_POSITION_Y;
    torchPosition[1].z = TORCH_START_POSITION_Z;
    torchAnimeX = 0.0f;
    torchAnimeY = 0.0f;


    //崩壊の初期化
    collapseFrontPosition.x = 0.0f;
    collapseFrontPosition.y = COLLAPSE_START_POSITION_Y;
    collapseFrontPosition.z = COLLAPSE_FRONT_START_POSITION_Z;

    collapseBackPosition.x = 0.0f;
    collapseBackPosition.y = COLLAPSE_START_POSITION_Y;
    collapseBackPosition.z = COLLAPSE_BACK_START_POSITION_Z;

    collapseWidth = 0.0f;

    //天井の初期化
    ceilingPosition.x = 0.0f;
    ceilingPosition.y = 0.0f;
    ceilingPosition.z = 0.0f;

    //台座の初期化
    standPosition.x = STAND_START_POSITION_X;
    standPosition.y = STAND_START_POSITION_Y;
    standPosition.z = STAND_START_POSITION_Z;

    standFlag = true;

    standJewelryPosition.x = STAND_START_POSITION_X;
    standJewelryPosition.y = STAND_START_POSITION_Y;
    standJewelryPosition.z = STAND_START_POSITION_Z;

    //プレイヤーの初期化
    playerPosition.x = PLAYER_START_POSITION_X;
    playerPosition.y = PLAYER_START_POSITION_Y;
    playerPosition.z = PLAYER_START_POSITION_Z;

    playerAnimeX = 0;
    playerAnimeY = 0;

    playerFlag = true;
    playerMove = 0.0f;
    deltaFlag  = false;
    playerPauseCount = 3.0f;

    //時間の初期化
    delta_Time = 0.0f;
    moveDelta  = 0.0f;

    //SE
    collapseVolume = COLLAPSE_SE_VOLUME;
    DontDestroy->collapseSEFlag = false;


    co_move = Move();        // コルーチンの生成
    co_move_it = co_move.begin();// コルーチンの実行開始

}

// Allocate all memory the Direct3D and Direct2D resources.
void openingScene::LoadAssets()
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
    //背景
    bgSprite            = DX9::Sprite::CreateFromFile(DXTK->Device9, L"BG/main_bg.png"      );
    collapseFrontSprite = DX9::Sprite::CreateFromFile(DXTK->Device9, L"BG/collapse_op_f.png");
    collapseBackSprite  = DX9::Sprite::CreateFromFile(DXTK->Device9, L"BG/collapse_op_b.png");
    ceilingSprite       = DX9::Sprite::CreateFromFile(DXTK->Device9, L"BG/ceiling.png"      );
    torchSprite         = DX9::Sprite::CreateFromFile(DXTK->Device9, L"BG/main_bg_torch.png");
    standSprite         = DX9::Sprite::CreateFromFile(DXTK->Device9, L"BG/stand.png"        );
    standJewelrySprite  = DX9::Sprite::CreateFromFile(DXTK->Device9, L"BG/stand_jewelry.png");


    //ブラックアウト
    blackSprite = DX9::Sprite::CreateFromFile(DXTK->Device9, L"BG/Black.png");

    //プレイヤー
    playerSprite        = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Player/p_run.png"    );
    playerJewelrySprite = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Player/p_jewelry.png");

    //SE
    DontDestroy->mediaCollapsese = DX9::MediaRenderer::CreateFromFile(DXTK->Device9, L"SE/collapse_se.mp3");
}

// Releasing resources required for termination.
void openingScene::Terminate()
{
    DXTK->ResetAudioEngine();
    DXTK->WaitForGpu();

    // TODO: Add your Termination logic here.

}

// Direct3D resource cleanup.
void openingScene::OnDeviceLost()
{

}

// Restart any looped sounds here
void openingScene::OnRestartSound()
{

}

// Updates the scene.
NextScene openingScene::Update(const float deltaTime)
{
    // If you use 'deltaTime', remove it.
    UNREFERENCED_PARAMETER(deltaTime);

    // TODO: Add your game logic here.


    BGUpdate       (deltaTime);
    PlayerUpdate   (deltaTime);
    AnimationUpdate(deltaTime);

    auto scene = OpeningSceneUpdate(deltaTime);
    if (scene != NextScene::Continue)
        return scene;


    //コルーチン 一つの行動に対してループを作る

        //コルーチンに実行する
    //C++20では、コルーチンに引数(deltaTimeなど)を渡せないので、
    //変数をコピーしてコルーチンで使う
    if (deltaFlag == true) {
        moveDelta = deltaTime;
    }
    delta_Time = deltaTime;

    playerMove += delta_Time;

    if (co_move_it != co_move.end()) {//もし、コルーチンが終了してなければ、
        co_move_it++;                 //一時停止した場所から再開する
    }


    return NextScene::Continue;
}

// Draws the scene.
void openingScene::Render()
{
    // TODO: Add your rendering code here.
    DXTK->Direct3D9->Clear(DX9::Colors::RGBA(0, 0, 0, 255));

    DXTK->Direct3D9->BeginScene();
    DX9::SpriteBatch->Begin();


    //背景の描画
    DX9::SpriteBatch->DrawSimple(
        bgSprite.Get(),
        bgPosition);

    //ブラックアウト
    DX9::SpriteBatch->DrawSimple(
        blackSprite.Get(),
        SimpleMath::Vector3(blackPosition),
        nullptr,
        DX9::Colors::Alpha(screenAlpha));

    //松明の描画
    for (int i = 0; i < TORCH_MAX; ++i) {
        DX9::SpriteBatch->DrawSimple(
            torchSprite.Get(),
            torchPosition[i],
            RectWH((int)torchAnimeX * TORCH_WIDTH, (int)torchAnimeY * TORCH_HEIGHT,
                TORCH_WIDTH, TORCH_HEIGHT));
    }



    //崩壊の描画
    //崩壊(手前)
    DX9::SpriteBatch->DrawSimple(
        collapseFrontSprite.Get(),
        collapseFrontPosition,
        RectWH(0, 0, collapseWidth, COLLAPSE_HEIGHT));

    //崩壊(奥)
    DX9::SpriteBatch->DrawSimple(
        collapseBackSprite.Get(),
        collapseBackPosition,
        RectWH(0, 0, collapseWidth, COLLAPSE_HEIGHT));

    //天井
    DX9::SpriteBatch->DrawSimple(
        ceilingSprite.Get(),
        ceilingPosition);

    //台座
    if (standFlag == false) {
        DX9::SpriteBatch->DrawSimple(
            standJewelrySprite.Get(),
            standJewelryPosition);
    }
    else
    {
        DX9::SpriteBatch->DrawSimple(
            standSprite.Get(),
            standPosition);
    }

    //プレイヤーの描画
    if (playerFlag == false) {
        DX9::SpriteBatch->DrawSimple(
            playerSprite.Get(),
            playerPosition,
            RectWH((int)playerAnimeX * PLAYER_WIDTH, (int)playerAnimeY * PLAYER_HEIGHT,
                PLAYER_WIDTH, PLAYER_HEIGHT));
    }
    else
    {
        DX9::SpriteBatch->DrawSimple(
            playerJewelrySprite.Get(),
            playerPosition);
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

void openingScene::BGUpdate(const float deltaTime) {
    //松明のアニメーション
    torchAnimeX += TORCH_ANIME_SPED * deltaTime;
    if (torchAnimeX > TORCH_ANIME_MAX_COUNT_X) {
        torchAnimeX = 0.0f;
        torchAnimeY++;
        if (torchAnimeY >= TORCH_ANIME_MAX_COUNT_Y) {
            torchAnimeY = 0.0f;
        }
    }

    //崩壊のスクロール
    collapseFrontPosition.y += COLLAPSE_SCROLL_SPEED_Y * deltaTime;
    if (collapseFrontPosition.y > 0.0f) {
        collapseFrontPosition.y = COLLAPSE_START_POSITION_Y;
    }
    collapseBackPosition.y += COLLAPSE_BACK_SCROLL_SPEED_Y * deltaTime;
    if (collapseBackPosition.y > 0.0f) {
        collapseBackPosition.y = COLLAPSE_START_POSITION_Y;
    }

    if (playerFlag == false) {
        DontDestroy->mediaCollapsese->Play();
        collapseWidth += COLLAPSE_WIDTH_ADD * deltaTime;
    }
    if (DontDestroy->mediaCollapsese->isComplete()) {
        DontDestroy->mediaCollapsese->Replay();
    }
    DontDestroy->mediaCollapsese->SetVolume(collapseVolume);
}

void openingScene::PlayerUpdate(const float deltaTime) {

    if (playerMove > PLAYER_MOVE_COUNT) {
        playerFlag = false;
        playerPosition.x += PLAYER_MOVE_SPEED_X * deltaTime;
    }
}

void openingScene::AnimationUpdate(const float deltaTime) {
    playerAnimeX += PLAYER_ANIME_SPEED_X * deltaTime;
    if (playerAnimeX > PLAYER_ANIME_MAX_COUNT_X) {
        playerAnimeX = 0.0f;
        playerAnimeY++;
        if (playerAnimeY >= PLAYER_ANIME_MAX_COUNT_Y) {
            playerAnimeY = 0.0f;
        }
    }

}

NextScene openingScene::OpeningSceneUpdate(const float deltaTime) {
    if (playerPosition.x > SCREEN_ALPHA_ADD_POSITION_X) {
        screenAlpha += SCREEN_ALPHA_COUNT * deltaTime;
        if (screenAlpha > SCREEN_ALPHA_LIMIT) {
            return NextScene::MainScene;
        }
    }
    else
    {
        screenAlpha += -SCREEN_ALPHA_COUNT * deltaTime;
        if (screenAlpha < 0) {
            screenAlpha = 0;
        }
    }

    if (DXTK->KeyEvent->pressed.Space ||
        DXTK->KeyEvent->pressed.Enter ||
        DXTK->GamePadEvent->a == GamePad::ButtonStateTracker::PRESSED ||
        DXTK->GamePadEvent->b == GamePad::ButtonStateTracker::PRESSED ||
        DXTK->GamePadEvent->start == GamePad::ButtonStateTracker::PRESSED) {
        DontDestroy->collapseSEFlag = true;
        return NextScene::MainScene;
    }

    return NextScene::Continue;
}

cppcoro::generator<int>openingScene::Move() {
    co_yield 0;//一時停止
    //右に移動する
    //while (playerPosition.x < 587.0f - 54.0f) {
    //    playerPosition.x += PLAYER_MOVE_SPEED_X * delta_Time;
    //    co_yield 1;//一時停止
    //}
    //playerPosition.x = 587.0f - 54.0f;
    //
    //float stop_time = 3.0f;
    //while (stop_time > 0.0f) {
    //    stop_time -= delta_Time;
    //    co_yield 2;//一時停止
    //}

    //playerFlag = true;
    //if (playerFlag == true) {
    //    deltaFlag = true;
    //    playerPauseCount -= moveDelta;
    //    if (moveDelta > 3.0f) {
    //        playerFlag = false;
    //        playerMove = true;
    //    }
    //}

    //右に移動する
    //while (playerPosition.x < 1280.0f) {
    //    playerPosition.x += PLAYER_MOVE_SPEED_X * delta_Time;
    //    co_yield 3;//一時停止
    //}
    //playerPosition.x = 1280.0f;
}