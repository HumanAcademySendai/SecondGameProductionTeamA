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
    bgPosition.x = 0.0f;
    bgPosition.y = 0.0f;
    bgPosition.z = 100.0f;

    collapseFrontPosition.x = 0.0f;
    collapseFrontPosition.y = COLLAPSE_START_POSITION_Y;
    collapseFrontPosition.z = COLLAPSE_FRONT_START_POSITION_Z;

    collapseBackPosition.x = 0.0f;
    collapseBackPosition.y = COLLAPSE_START_POSITION_Y;
    collapseBackPosition.z = COLLAPSE_BACK_START_POSITION_Z;

    collapseWidth = 0.0f;

    ceilingPosition.x = 0.0f;
    ceilingPosition.y = 0.0f;
    ceilingPosition.z = 0.0f;

    standPosition.x = STAND_START_POSITION_X;
    standPosition.y = STAND_START_POSITION_Y;
    standPosition.z = STAND_START_POSITION_Z;

    standFlag = false;

    standJewelryPosition.x = STAND_START_POSITION_X;
    standJewelryPosition.y = STAND_START_POSITION_Y;
    standJewelryPosition.z = STAND_START_POSITION_Z;

    playerPosition.x = PLAYER_START_POSITION_X;
    playerPosition.y = PLAYER_START_POSITION_Y;
    playerPosition.z = PLAYER_START_POSITION_Z;

    playerAnimeX = 0;
    playerAnimeY = 0;


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
    playerSprite = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Player/p_run.png");
    playerPauseSprite = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Player/p_pause.png");

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


    BGUpdate(deltaTime);
    PlayerUpdate(deltaTime);
    AnimationUpdate(deltaTime);

    //コルーチン 一つの行動に対してループを作る

        //コルーチンに実行する
    //C++20では、コルーチンに引数(deltaTimeなど)を渡せないので、
    //変数をコピーしてコルーチンで使う
    delta_Time = deltaTime;
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

    //崩壊の描画
    //崩壊(手前)
    DX9::SpriteBatch->DrawSimple(
        collapseFrontSprite.Get(),
        collapseFrontPosition),
        RectWH(0, 0, collapseWidth, COLLAPSE_HEIGHT);

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
    DX9::SpriteBatch->DrawSimple(
        playerSprite.Get(),
        playerPosition,
        RectWH((int)playerAnimeX * PLAYER_WIDTH, (int)playerAnimeY * PLAYER_HEIGHT,
            PLAYER_WIDTH, PLAYER_HEIGHT));



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
    //崩壊のスクロール
    collapseFrontPosition.y += COLLAPSE_SCROLL_SPEED_Y * deltaTime;
    if (collapseFrontPosition.y > 0.0f) {
        collapseFrontPosition.y = COLLAPSE_START_POSITION_Y;
    }
    collapseBackPosition.y += COLLAPSE_BACK_SCROLL_SPEED_Y * deltaTime;
    if (collapseBackPosition.y > 0.0f) {
        collapseBackPosition.y = COLLAPSE_START_POSITION_Y;
    }
}

void openingScene::PlayerUpdate(const float deltaTime) {

}

void openingScene::AnimationUpdate(const float deltaTime) {
    playerAnimeX += PLAYER_ANIME_SPEED_X * deltaTime;
    if (playerAnimeX > PLAYER_ANIME_MAX_COUNT_X) {
        playerAnimeX = 0.0f;
        playerAnimeY++;
        if (playerAnimeY >= 1.0f) {
            playerAnimeY = 0.0f;
        }
    }

}

cppcoro::generator<int>openingScene::Move() {
    co_yield 0;//一時停止
    //左に移動する
    while (playerPosition.x > 820.0f) {
        playerPosition.x += -PLAYER_MOVE_SPEED_X * delta_Time;
        co_yield 1;//一時停止
    }
    playerPosition.x = 820.0f;

    //左に移動する
    while (playerPosition.x > 295.0f) {
        playerPosition.x += -PLAYER_MOVE_SPEED_X * delta_Time;
        co_yield 1;//一時停止
    }
    playerPosition.x = 295.0f;

    //右に移動する
    while (playerPosition.x < 1280.0f) {
        playerPosition.x += PLAYER_MOVE_SPEED_X * delta_Time;
        co_yield 1;//一時停止
    }
    playerPosition.x = 1280.0f;
}