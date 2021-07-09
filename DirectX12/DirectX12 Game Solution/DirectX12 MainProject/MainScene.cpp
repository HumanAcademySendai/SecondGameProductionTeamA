//
// MainScene.cpp
//

#include "Base/pch.h"
#include "Base/dxtk.h"
#include "SceneFactory.h"
#include "DontDestroyOnLoad.h"

// Initialize member variables.
MainScene::MainScene() : dx9GpuDescriptor{}
{

}

// Initialize a variable and audio resources.
void MainScene::Initialize()
{
    //背景スクロールの初期化
    bgScrollPosition.x = BG_START_POSITION_X;
    bgScrollPosition.y = BG_START_POSITION_Y;
    bgScrollPosition.z = BG_START_POSITION_Z;
    bgLoopNumber = 0;

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
    collapseFrontPosition.x = COLLAPSE_START_POSITION_X;
    collapseFrontPosition.y = COLLAPSE_FRONT_START_POSITION_Y;
    collapseFrontPosition.z = COLLAPSE_START_POSITION_Z;

    //天井の初期化
    ceilingPosition.x = CEILING_START_POSITION_X;
    ceilingPosition.y = CEILING_START_POSITION_Y;
    ceilingPosition.z = CEILING_START_POSITION_Z;


    //ブラックアウトの初期化
    blackPosition.x = BG_START_POSITION_X;
    blackPosition.y = BG_START_POSITION_Y;
    blackPosition.z = BLACK_START_POSITION_Z;
    screenAlpha = 0;

    //プレイヤーの初期化
    playerState = PLAYER_NORMAL;
    playerPosition.x = PLAYER_START_POSITION_X;
    playerPosition.y = PLAYER_START_POSITION_Y;
    playerPosition.z = PLAYER_START_POSITION_Z;
    playerSlidingPosition.x = PLAYER_SLIDING_START_POSITION_X;
    playerSlidingPosition.y = PLAYER_SLIDING_START_POSITION_Y;
    playerSlidingPosition.z = PLAYER_START_POSITION_Z;
    playerSlidingCount = PLAYER_SLIDING_START_COUNT;
    playerMoveCount = PLAYER_MOVE_START_COUNT;
    playerDamageCount = 0;
    gravity = 0;
    playerAnimeX = 0;
    playerDeathFlag = false;

    //障害物の初期化
    //扉
    doorDownPosition[0].x = DOOR_DOWN_START_POSITION_X_1;
    doorDownPosition[0].y = DOOR_DOWN_START_POSITION_Y;
    doorDownPosition[0].z = DOOR_START_POSITION_Z;
    doorDownPosition[1].x = DOOR_DOWN_START_POSITION_X_2;
    doorDownPosition[1].y = DOOR_DOWN_START_POSITION_Y;
    doorDownPosition[1].z = DOOR_START_POSITION_Z;
    doorDownPosition[2].x = DOOR_DOWN_START_POSITION_X_3;
    doorDownPosition[2].y = DOOR_DOWN_START_POSITION_Y;
    doorDownPosition[2].z = DOOR_START_POSITION_Z;
    doorDownPosition[3].x = DOOR_DOWN_START_POSITION_X_4;
    doorDownPosition[3].y = DOOR_DOWN_START_POSITION_Y;
    doorDownPosition[3].z = DOOR_START_POSITION_Z;
    doorUpPosition.x = DOOR_UP_START_POSITION_X;
    doorUpPosition.y = DOOR_UP_START_POSITION_Y;
    doorUpPosition.z = DOOR_START_POSITION_Z;

    //岩
    rockPosition[0].x = ROCK_START_POSITION_X_1;
    rockPosition[0].y = ROCK_START_POSITION_Y;
    rockPosition[0].z = ROCK_START_POSITION_Z;
    rockPosition[1].x = ROCK_START_POSITION_X_2;
    rockPosition[1].y = ROCK_START_POSITION_Y;
    rockPosition[1].z = ROCK_START_POSITION_Z;
    rockPosition[2].x = ROCK_START_POSITION_X_3;
    rockPosition[2].y = ROCK_START_POSITION_Y;
    rockPosition[2].z = ROCK_START_POSITION_Z;
    rockPosition[3].x = ROCK_START_POSITION_X_4;
    rockPosition[3].y = ROCK_START_POSITION_Y;
    rockPosition[3].z = ROCK_START_POSITION_Z;
    rockPosition[4].x = ROCK_START_POSITION_X_5;
    rockPosition[4].y = ROCK_START_POSITION_Y;
    rockPosition[4].z = ROCK_START_POSITION_Z;

    //矢
    arrowPosition[0].x = ARROW_START_POSITION_X_1;
    arrowPosition[0].y = ARROW_START_POSITION_Y;
    arrowPosition[0].z = ARROW_START_POSITION_Z;
    arrowPosition[1].x = ARROW_START_POSITION_X_2;
    arrowPosition[1].y = ARROW_START_POSITION_Y;
    arrowPosition[1].z = ARROW_START_POSITION_Z;
    arrowPosition[2].x = ARROW_START_POSITION_X_3;
    arrowPosition[2].y = ARROW_START_POSITION_Y;
    arrowPosition[2].z = ARROW_START_POSITION_Z;

    //コウモリ
    batPosition[0].x = BAT_START_POSITION_X_1;
    batPosition[0].y = BAT_START_POSITION_Y;
    batPosition[0].z = BAT_START_POSITION_Z;
    batPosition[1].x = BAT_START_POSITION_X_2;
    batPosition[1].y = BAT_START_POSITION_Y;
    batPosition[1].z = BAT_START_POSITION_Z;
    batPosition[2].x = BAT_START_POSITION_X_3;
    batPosition[2].y = BAT_START_POSITION_Y;
    batPosition[2].z = BAT_START_POSITION_Z;
    batPosition[3].x = BAT_START_POSITION_X_4;
    batPosition[3].y = BAT_START_POSITION_Y;
    batPosition[3].z = BAT_START_POSITION_Z;
    batPosition[4].x = BAT_START_POSITION_X_5;
    batPosition[4].y = BAT_START_POSITION_Y;
    batPosition[4].z = BAT_START_POSITION_Z;

    theta = 0;
    batBaseY = batPosition[0].y;
    batAnimeX = 0;

    //演出コウモリ(右向き)
    fakeBatRightPosition[0].x = FAKE_BAT_RIGHT_START_POSITION_X_1;
    fakeBatRightPosition[0].y = FAKE_BAT_START_POSITION_Y;
    fakeBatRightPosition[0].z = FAKE_BAT_START_POSITION_Z;
    fakeBatRightPosition[1].x = FAKE_BAT_RIGHT_START_POSITION_X_2;
    fakeBatRightPosition[1].y = FAKE_BAT_START_POSITION_Y;
    fakeBatRightPosition[1].z = FAKE_BAT_START_POSITION_Z;
    fakeBatRightPosition[2].x = FAKE_BAT_RIGHT_START_POSITION_X_3;
    fakeBatRightPosition[2].y = FAKE_BAT_START_POSITION_Y;
    fakeBatRightPosition[2].z = FAKE_BAT_START_POSITION_Z;

    //演出コウモリ(左向き)
    fakeBatLeftPosition[0].x = FAKE_BAT_LEFT_START_POSITION_X_1;
    fakeBatLeftPosition[0].y = FAKE_BAT_START_POSITION_Y;
    fakeBatLeftPosition[0].z = FAKE_BAT_START_POSITION_Z;
    fakeBatLeftPosition[1].x = FAKE_BAT_LEFT_START_POSITION_X_2;
    fakeBatLeftPosition[1].y = FAKE_BAT_START_POSITION_Y;
    fakeBatLeftPosition[1].z = FAKE_BAT_START_POSITION_Z;
    fakeBatLeftPosition[2].x = FAKE_BAT_LEFT_START_POSITION_X_3;
    fakeBatLeftPosition[2].y = FAKE_BAT_START_POSITION_Y;
    fakeBatLeftPosition[2].z = FAKE_BAT_START_POSITION_Z;
    fakeBatLeftPosition[3].x = FAKE_BAT_LEFT_START_POSITION_X_4;
    fakeBatLeftPosition[3].y = FAKE_BAT_START_POSITION_Y;
    fakeBatLeftPosition[3].z = FAKE_BAT_START_POSITION_Z;
    fakeBatLeftPosition[4].x = FAKE_BAT_LEFT_START_POSITION_X_5;
    fakeBatLeftPosition[4].y = FAKE_BAT_START_POSITION_Y;
    fakeBatLeftPosition[4].z = FAKE_BAT_START_POSITION_Z;
    fakeBatLeftPosition[5].x = FAKE_BAT_LEFT_START_POSITION_X_6;
    fakeBatLeftPosition[5].y = FAKE_BAT_START_POSITION_Y;
    fakeBatLeftPosition[5].z = FAKE_BAT_START_POSITION_Z;

    //足場
    scaffoldPosition[0].x  = SCAFFOLD_START_POSITION_X_1;
    scaffoldPosition[0].y  = SCAFFOLD_START_POSITION_Y;
    scaffoldPosition[0].z  = SCAFFOLD_START_POSITION_Z;
    scaffoldPosition[1].x  = SCAFFOLD_START_POSITION_X_2;
    scaffoldPosition[1].y  = SCAFFOLD_START_POSITION_Y;
    scaffoldPosition[1].z  = SCAFFOLD_START_POSITION_Z;
    scaffoldPosition[2].x  = SCAFFOLD_START_POSITION_X_3;
    scaffoldPosition[2].y  = SCAFFOLD_START_POSITION_Y;
    scaffoldPosition[2].z  = SCAFFOLD_START_POSITION_Z;
    scaffoldPosition[3].x  = SCAFFOLD_START_POSITION_X_4;
    scaffoldPosition[3].y  = SCAFFOLD_START_POSITION_Y;
    scaffoldPosition[3].z  = SCAFFOLD_START_POSITION_Z;
    scaffoldPosition[4].x  = SCAFFOLD_START_POSITION_X_5;
    scaffoldPosition[4].y  = SCAFFOLD_START_POSITION_Y;
    scaffoldPosition[4].z  = SCAFFOLD_START_POSITION_Z;
    scaffoldPosition[5].x  = SCAFFOLD_START_POSITION_X_6;
    scaffoldPosition[5].y  = SCAFFOLD_START_POSITION_Y;
    scaffoldPosition[5].z  = SCAFFOLD_START_POSITION_Z;
    scaffoldPosition[6].x  = SCAFFOLD_START_POSITION_X_7;
    scaffoldPosition[6].y  = SCAFFOLD_START_POSITION_Y;
    scaffoldPosition[6].z  = SCAFFOLD_START_POSITION_Z;
    scaffoldPosition[7].x  = SCAFFOLD_START_POSITION_X_8;
    scaffoldPosition[7].y  = SCAFFOLD_START_POSITION_Y;
    scaffoldPosition[7].z  = SCAFFOLD_START_POSITION_Z;
    scaffoldPosition[8].x  = SCAFFOLD_START_POSITION_X_9;
    scaffoldPosition[8].y  = SCAFFOLD_START_POSITION_Y;
    scaffoldPosition[8].z  = SCAFFOLD_START_POSITION_Z;
    scaffoldPosition[9].x  = SCAFFOLD_START_POSITION_X_10;
    scaffoldPosition[9].y  = SCAFFOLD_START_POSITION_Y;
    scaffoldPosition[9].z  = SCAFFOLD_START_POSITION_Z;
    scaffoldPosition[10].x = SCAFFOLD_START_POSITION_X_11;
    scaffoldPosition[10].y = SCAFFOLD_START_POSITION_Y;
    scaffoldPosition[10].z = SCAFFOLD_START_POSITION_Z;
    scaffoldPosition[11].x = SCAFFOLD_START_POSITION_X_12;
    scaffoldPosition[11].y = SCAFFOLD_START_POSITION_Y;
    scaffoldPosition[11].z = SCAFFOLD_START_POSITION_Z;
    scaffoldPosition[12].x = SCAFFOLD_START_POSITION_X_13;
    scaffoldPosition[12].y = SCAFFOLD_START_POSITION_Y;
    scaffoldPosition[12].z = SCAFFOLD_START_POSITION_Z;

    scaffoldNumber = 0;

    //落とし穴(小)
    shortHolePosition[0].x = SHORT_HOLE_START_POSITION_X_1;
    shortHolePosition[0].y = HOLE_START_POSITION_Y;
    shortHolePosition[0].z = HOLE_START_POSITION_Z;
    shortHolePosition[1].x = SHORT_HOLE_START_POSITION_X_2;
    shortHolePosition[1].y = HOLE_START_POSITION_Y;
    shortHolePosition[1].z = HOLE_START_POSITION_Z;
    shortHolePosition[2].x = SHORT_HOLE_START_POSITION_X_3;
    shortHolePosition[2].y = HOLE_START_POSITION_Y;
    shortHolePosition[2].z = HOLE_START_POSITION_Z;

    //落とし穴(中)
    middleHolePosition.x = MIDDLE_HOLE_START_POSITION_X;
    middleHolePosition.y = HOLE_START_POSITION_Y;
    middleHolePosition.z = HOLE_START_POSITION_Z;

    //落とし穴(大)
    longHolePosition.x = LONG_HOLE_START_POSITION_X;
    longHolePosition.y = HOLE_START_POSITION_Y;
    longHolePosition.z = HOLE_START_POSITION_Z;

    //落とし穴(特大)
    doubleLongHolePosition.x = DOUBLE_LONG_HOLE_START_POSITION_X;
    doubleLongHolePosition.y = HOLE_START_POSITION_Y;
    doubleLongHolePosition.z = HOLE_START_POSITION_Z;


    //SE
    seCollapse         = XAudio::CreateSoundEffect(DXTK->AudioEngine, L"SE/collapse_se.wav");
    seCollapseInstance = seCollapse->CreateInstance();
    seCollapseInstance->Play(true);
    sePlayerDamage     = XAudio::CreateSoundEffect(DXTK->AudioEngine, L"SE/damage_se.wav"  );
    for (int i = 0; i < DOOR_DOWN_MAX; ++i) {
        seDoor[i] = XAudio::CreateSoundEffect(DXTK->AudioEngine, L"SE/door_se.wav");
        seDoorInstance[i] = seDoor[i]->CreateInstance();
    }

}

// Allocate all memory the Direct3D and Direct2D resources.
void MainScene::LoadAssets()
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

    spriteBatch      = DX12::CreateSpriteBatch(DXTK->Device, resourceUploadBatch, pd, &viewport);

    dx9GpuDescriptor = DXTK->Direct3D9->CreateShaderResourceView(descriptorHeap.get(), 0);

    auto uploadResourcesFinished = resourceUploadBatch.End(DXTK->CommandQueue);
    uploadResourcesFinished.wait();
    

    // グラフィックリソースの初期化処理
    
    // フォント
    font = DX9::SpriteFont::CreateDefaultFont(DXTK->Device9);

    //背景
    bgSprite            = DX9::Sprite::CreateFromFile(DXTK->Device9, L"BG/main_bg.png"       );
    collapseFrontSprite = DX9::Sprite::CreateFromFile(DXTK->Device9, L"BG/collapse_front.png");
    ceilingSprite       = DX9::Sprite::CreateFromFile(DXTK->Device9, L"BG/ceiling.png"       );
    torchSprite         = DX9::Sprite::CreateFromFile(DXTK->Device9, L"BG/main_bg_torch.png" );

    //ブラックアウト
    blackSprite = DX9::Sprite::CreateFromFile(DXTK->Device9, L"BG/Black.png");

    //プレイヤー
    playerSprite        = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Player/p_run.png"    );
    playerSlidingSprite = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Player/p_sliding.png");
    playerJumpSprite    = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Player/p_jump.png"   );
    playerPauseSprite   = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Player/p_pause.png"  );

    //障害物
    doorSprite         = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Obstacle/door.png"     );
    rockSprite         = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Obstacle/rock.png"     );
    arrowSprite        = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Obstacle/arrow.png"    );
    batSprite          = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Obstacle/bat.png"      );
    fakeBatRightSprite = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Obstacle/fakebat_r.png");
    scaffoldSprite     = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Obstacle/scaffold.png" );
    shortHoleSprite    = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Obstacle/hole_s.png"   );
    middleHoleSprite   = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Obstacle/hole_m.png"   );
    longHoleSprite     = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Obstacle/hole_l.png"   );
    doubleLongHoleSprite = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Obstacle/hole_LL.png");

    //BGM
    mediaMainbgm = DX9::MediaRenderer::CreateFromFile(DXTK->Device9, L"BGM/main_bgm.mp3");
    mediaMainbgm->Play();
    if (mediaMainbgm->isComplete()) {
        mediaMainbgm->Replay();
    }
}

// Releasing resources required for termination.
void MainScene::Terminate()
{
    DXTK->ResetAudioEngine();
    DXTK->WaitForGpu();

    // TODO: Add your Termination logic here.

}

// Direct3D resource cleanup.
void MainScene::OnDeviceLost()
{

}

// Restart any looped sounds here
void MainScene::OnRestartSound()
{
    if (seCollapseInstance)
        seCollapseInstance->Play(true);

    for (int i = 0; i < DOOR_DOWN_MAX; ++i) {
        if (seDoorInstance[i])
            seDoorInstance[i]->Play(true);
    }
}

// Updates the scene.
NextScene MainScene::Update(const float deltaTime)
{
    // If you use 'deltaTime', remove it.
    UNREFERENCED_PARAMETER(deltaTime);

    // TODO: Add your game logic here.

    BGUpdate       (deltaTime);
    PlayerUpdate   (deltaTime);
    ObstacleUpdate (deltaTime);
    AnimationUpdate(deltaTime);

    auto scene = SeneChangeUpdate(deltaTime);
    if (scene != NextScene::Continue)
        return scene;

    return NextScene::Continue;
}

// Draws the scene.
void MainScene::Render()
{
    // TODO: Add your rendering code here.
    DXTK->Direct3D9->Clear(DX9::Colors::RGBA(0, 0, 0, 255));

    DXTK->Direct3D9->BeginScene();

    //当たり判定の視覚化

   /* DX9::VertexScreen v[4];
    v[0].position = SimpleMath::Vector3(playerSlidingPosition.x, playerSlidingPosition.y, -0.5f);
    v[0].color = DX9::Colors::RGBA(255, 0, 0, 255);
    v[1].position = SimpleMath::Vector3(playerSlidingPosition.x + 193, playerSlidingPosition.y, -0.5f);
    v[1].color = DX9::Colors::RGBA(255, 0, 0, 255);
    v[2].position = SimpleMath::Vector3(playerSlidingPosition.x + 193, playerSlidingPosition.y + 76, -0.5f);
    v[2].color = DX9::Colors::RGBA(255, 0, 0, 255);
    v[3].position = SimpleMath::Vector3(playerSlidingPosition.x, playerSlidingPosition.y + 76, -0.5f);
    v[3].color = DX9::Colors::RGBA(255, 0, 0, 255);
    DXTK->Direct3D9->DrawInstanced(D3DPT_TRIANGLEFAN, 2, v, DX9::VertexScreen::FVF);

    for (int i = 0; i < DOOR_MAX; ++i) {
        v[0].position = SimpleMath::Vector3(doorPosition[i].x, doorPosition[i].y, -0.5f);
        v[0].color = DX9::Colors::RGBA(255, 255, 0, 255);
        v[1].position = SimpleMath::Vector3(doorPosition[i].x + 80, doorPosition[i].y, -0.5f);
        v[1].color = DX9::Colors::RGBA(255, 255, 0, 255);
        v[2].position = SimpleMath::Vector3(doorPosition[i].x + 80, doorPosition[i].y + 719, -0.5f);
        v[2].color = DX9::Colors::RGBA(255, 255, 0, 255);
        v[3].position = SimpleMath::Vector3(doorPosition[i].x, doorPosition[i].y + 719, -0.5f);
        v[3].color = DX9::Colors::RGBA(255, 255, 0, 255);
        DXTK->Direct3D9->DrawInstanced(D3DPT_TRIANGLEFAN, 2, v, DX9::VertexScreen::FVF);
    }*/

    DX9::SpriteBatch->Begin();


    //背景の描画
    DX9::SpriteBatch->DrawSimple(
        bgSprite.Get(),
        bgScrollPosition);

    //松明の描画
    for (int i = 0; i < TORCH_MAX; ++i) {
        DX9::SpriteBatch->DrawSimple(
            torchSprite.Get(),
            torchPosition[i],
            RectWH((int)torchAnimeX * TORCH_WIDTH, (int)torchAnimeY * TORCH_HEIGHT, TORCH_WIDTH, TORCH_HEIGHT));
    }

    //ブラックアウト
    DX9::SpriteBatch->DrawSimple(
        blackSprite.Get(),
        SimpleMath::Vector3(blackPosition),
        nullptr,
        DX9::Colors::Alpha(screenAlpha));

    //崩壊の描画
    DX9::SpriteBatch->DrawSimple(
        collapseFrontSprite.Get(),
        collapseFrontPosition);

    //天井の描画
    DX9::SpriteBatch->DrawSimple(
        ceilingSprite.Get(),
        ceilingPosition);


    //プレイヤーの描画
    if (playerState == PLAYER_NORMAL ||
        playerState == PLAYER_MOVE ||
        playerState == PLAYER_RIDE ||
        playerState == PLAYER_DROP ||
        playerState == PLAYER_DROP_DEATH) {
        DX9::SpriteBatch->DrawSimple(
            playerSprite.Get(),
            playerPosition,
            RectWH((int)playerAnimeX * PLAYER_WIDTH, 0, PLAYER_WIDTH, PLAYER_HEIGHT));
    }

    if (playerState == PLAYER_SLIDING) {
        DX9::SpriteBatch->DrawSimple(
            playerSlidingSprite.Get(),
            playerSlidingPosition);
    }

    if (playerState == PLAYER_JUMP) {
        DX9::SpriteBatch->DrawSimple(
            playerJumpSprite.Get(),
            playerPosition);
    }

    if (playerState == PLAYER_DAMAGE) {
        DX9::SpriteBatch->DrawSimple(
            playerPauseSprite.Get(),
            playerPosition);
    }

    //障害物の描画
    //扉(降下)
    for (int i = 0; i < DOOR_DOWN_MAX; ++i) {
        DX9::SpriteBatch->DrawSimple(
            doorSprite.Get(),
            doorDownPosition[i]);
    }
    
    //扉(上昇)
    DX9::SpriteBatch->DrawSimple(
        doorSprite.Get(),
        doorUpPosition
    );

    //岩
    for (int i = 0; i < ROCK_MAX; i++) {
        DX9::SpriteBatch->DrawSimple(
            rockSprite.Get(),
            rockPosition[i]);
    }
    
    //矢
    for (int i = 0; i < ARROW_MAX; ++i) {
        DX9::SpriteBatch->DrawSimple(
            arrowSprite.Get(),
            arrowPosition[i]);
    }
    
    //コウモリ
    for (int i = 0; i < BAT_MAX; ++i) {
        DX9::SpriteBatch->DrawSimple(
            batSprite.Get(),
            batPosition[i],
            RectWH((int)batAnimeX * BAT_WIDTH, 0, BAT_WIDTH, BAT_HEIGHT));
    }
    
    //演出コウモリ(右向き)
    for (int i = 0; i < FAKE_BAT_RIGHT_MAX; ++i) {
        DX9::SpriteBatch->DrawSimple(
            fakeBatRightSprite.Get(),
            fakeBatRightPosition[i],
            RectWH((int)batAnimeX * BAT_WIDTH, 0, BAT_WIDTH, BAT_HEIGHT));
    }

    //演出コウモリ(左向き)
    for (int i = 0; i < FAKE_BAT_LEFT_MAX; ++i) {
        DX9::SpriteBatch->DrawSimple(
            batSprite.Get(),
            fakeBatLeftPosition[i],
            RectWH((int)batAnimeX * BAT_WIDTH, 0, BAT_WIDTH, BAT_HEIGHT));
    }



    //足場
    for (int i = 0; i < SCAFFOLD_MAX; ++i) {
        DX9::SpriteBatch->DrawSimple(
            scaffoldSprite.Get(),
            scaffoldPosition[i]);
    }


    //落とし穴(小)
    for (int i = 0; i < SHORT_HOLE_MAX; ++i) {
        DX9::SpriteBatch->DrawSimple(
            shortHoleSprite.Get(),
            shortHolePosition[i]);
    }

    //落とし穴(中)
    DX9::SpriteBatch->DrawSimple(
        middleHoleSprite.Get(),
        middleHolePosition);

    //落とし穴(大)
    DX9::SpriteBatch->DrawSimple(
        longHoleSprite.Get(),
        longHolePosition);

    //落とし穴(特大)
    DX9::SpriteBatch->DrawSimple(
        doubleLongHoleSprite.Get(),
        doubleLongHolePosition);

    //フォント
    DX9::SpriteBatch->DrawString(
        font.Get(),
        SimpleMath::Vector2(0.0f, 0.0f),
        DX9::Colors::RGBA(500, 0, 0, 255),
        L"背景ループの回数  %d", bgLoopNumber
    );

    DX9::SpriteBatch->DrawString(
        font.Get(),
        SimpleMath::Vector2(0.0f, 30.0f),
        DX9::Colors::RGBA(500, 0, 0, 255),
        L" P移動 %f", playerMoveCount
    );



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

void MainScene::BGUpdate(const float deltaTime) {
    bgScrollPosition.x += BG_SCROLL_SPEED_X * deltaTime;
    if (bgScrollPosition.x <= BG_RESET_POSITION_X) {
        bgScrollPosition.x  = BG_START_POSITION_X;
        bgLoopNumber++;
    }

    collapseFrontPosition.y += 800.0f * deltaTime;
    if (collapseFrontPosition.y > 0.0f) {
        collapseFrontPosition.y = COLLAPSE_FRONT_START_POSITION_Y;
    }

    for (int i = 0; i < TORCH_MAX; ++i) {
        torchPosition[i].x += TORCH_SCROLL_SPEED_X * deltaTime;
        if (torchPosition[i].x < 0.0f) {
            torchPosition[i].x = TORCH_RESET_POSITION_X;
        }
    }

    ceilingPosition.x += CEILING_SCROLL_SPEED_X * deltaTime;
    if (ceilingPosition.x <= CEILING_RESET_POSITION_X) {
        ceilingPosition.x  = CEILING_START_POSITION_X;
    }
}

void MainScene::PlayerUpdate(const float deltaTime) {
    playerPrevState = playerState;
    PlayerSlidingUpdate  (deltaTime);
    PlayerJumpUpdate     (deltaTime);
    PlayerDamageUpdate   (deltaTime);
    PlayerMoveUpdate     (deltaTime);
    PlayerRideUpdate     (deltaTime);
    PlayerDropUpdate     (deltaTime);
    PlayerDropDeathUpdate(deltaTime);
}

void MainScene::PlayerSlidingUpdate(const float deltaTime) {
    if (playerState == PLAYER_NORMAL) {
        if (DXTK->KeyEvent->pressed.S    ||
            DXTK->KeyEvent->pressed.Down ||
            DXTK->GamePadEvent->leftStickDown == GamePad::ButtonStateTracker::PRESSED) {
            playerState = PLAYER_SLIDING;
            playerSlidingCount = PLAYER_SLIDING_START_COUNT;
        }
    }

    if (playerState == PLAYER_SLIDING) {
        playerSlidingCount -= deltaTime;
        if (playerSlidingCount < 0) {
            playerState = PLAYER_NORMAL;
        }
    }
}
void MainScene::PlayerJumpUpdate(const float deltaTime) {

    if (playerState == PLAYER_NORMAL && playerPosition.y >= PLAYER_START_POSITION_Y ||
        playerState == PLAYER_RIDE) {
        if (DXTK->KeyEvent->pressed.Space ||
            DXTK->GamePadEvent->a == GamePad::ButtonStateTracker::PRESSED) {
            playerState = PLAYER_JUMP;
            gravity = GRAVITY_POWER_TAKE;
        }
    }

    if (playerState == PLAYER_JUMP) {
        playerPosition.y  -= gravity * deltaTime;
        gravity += GRAVITY_POWER_ADD * deltaTime;

        if (playerPosition.y > PLAYER_START_POSITION_Y) {
            playerPosition.y = PLAYER_START_POSITION_Y;
            playerState = PLAYER_NORMAL;
        }
    }
}
void MainScene::PlayerDamageUpdate(const float deltaTime) {
    if (playerDeathFlag == true && playerState == PLAYER_DAMAGE) {
        playerPosition.x        -= PLAYER_MOVE_SPEED * deltaTime;
        playerSlidingPosition.x -= PLAYER_MOVE_SPEED * deltaTime;
        playerPosition.y        += PLAYER_MOVE_SPEED * deltaTime;
        screenAlpha             += SCREENALPHA_COUNT * deltaTime;
        if (playerPosition.y >= PLAYER_START_POSITION_Y) {
            playerPosition.y  = PLAYER_START_POSITION_Y;
        }
    }

    if (playerDeathFlag == false) {
        if (playerState == PLAYER_DAMAGE) {
            playerPosition.x        -= PLAYER_MOVE_SPEED * deltaTime;
            playerSlidingPosition.x -= PLAYER_MOVE_SPEED * deltaTime;
            playerPosition.y        += PLAYER_MOVE_SPEED * deltaTime;
            if (playerPosition.x < PLAYER_DAMAGE_POSITION) {
                playerPosition.x        = PLAYER_DAMAGE_POSITION;
                playerSlidingPosition.x = PLAYER_DAMAGE_POSITION;
            }
            if (playerPosition.y >= PLAYER_START_POSITION_Y) {
                playerPosition.y  = PLAYER_START_POSITION_Y;
            }
        }
    }

    if (playerState == PLAYER_DAMAGE) {
        playerDamageCount += deltaTime;
        if (playerDamageCount >= PLAYER_DAMAGE_LIMIT_COUNT) {
            playerState       = PLAYER_NORMAL;
            playerDamageCount = 0;
            playerDeathFlag   = true;
        }
    }
}
void MainScene::PlayerMoveUpdate(const float deltaTime) {
    playerMoveCount -= deltaTime;
    if (playerMoveCount <= 0 && playerState == PLAYER_NORMAL ||
        playerMoveCount <= 0 && playerState == PLAYER_RIDE   ||
        playerMoveCount <= 0 && playerState == PLAYER_SLIDING) {
        playerState = PLAYER_MOVE;
    }

    if (playerState == PLAYER_MOVE) {
        playerPosition.x += PLAYER_MOVE_SPEED * deltaTime;
    }
}
void MainScene::PlayerRideUpdate(const float deltaTime) {
    if (playerState == PLAYER_JUMP) {
        for (int i = 0; i < SCAFFOLD_MAX; ++i) {
            if (isIntersect(
                RectWH(playerPosition.x, playerPosition.y, PLAYER_HIT_SIZE_X, PLAYER_HIT_SIZE_Y),
                RectWH(scaffoldPosition[i].x, scaffoldPosition[i].y, SCAFFOLD_HIT_SIZE_X, SCAFFOLD_HIT_SIZE_Y))) {
                playerState = PLAYER_RIDE;
                scaffoldNumber = i;
                break;
            }
        }
    }
    else if (playerState == PLAYER_RIDE) {
        if (isIntersect(
            RectWH(playerPosition.x, playerPosition.y + PLAYER_LEG_POSITION, PLAYER_HIT_SIZE_X, 1),
            RectWH(scaffoldPosition[scaffoldNumber].x, scaffoldPosition[scaffoldNumber].y, SCAFFOLD_HIT_SIZE_X, SCAFFOLD_HIT_SIZE_Y))
            ) {
            playerPosition.y = scaffoldPosition[scaffoldNumber].y - PLAYER_LEG_POSITION;
        } else {
            playerState = PLAYER_DROP;
        }
    }
    //1ドットでも離れたら空中

    //    if (playerState == PLAYER_RIDE) {
    //        if(isIntersect(
    //            RectWH(playerPosition.x, playerPosition.y, PLAYER_HIT_SIZE_X, PLAYER_HIT_SIZE_Y),
    //            RectWH(scaffoldPosition[i].x, scaffoldPosition[i].y, SCAFFOLD_HIT_SIZE_X, SCAFFOLD_HIT_SIZE_Y))) {
    //        }

    //        playerState = PLAYER_DROP;
    //        if (isIntersect(
    //            RectWH(playerPosition.x, playerPosition.y, PLAYER_HIT_SIZE_X, PLAYER_HIT_SIZE_Y),
    //            RectWH(scaffoldPosition[i].x, scaffoldPosition[i].y, SCAFFOLD_HIT_SIZE_X, SCAFFOLD_HIT_SIZE_Y))) {
    //            playerState = PLAYER_RIDE;
    //            scaffoldNumber = i;
    //            break;
    //        }

    //        if (playerState == PLAYER_RIDE) {
    //            if (playerPosition.y >= scaffoldPosition[scaffoldNumber].y) {
    //                playerPosition.y = scaffoldPosition[scaffoldNumber].y - 100;
    //            }
    //        }
    //        else {
    //            // 落ちてる
    //            playerState = PLAYER_DROP;
    //        }
    //    }
    //}
}
void MainScene::PlayerDropUpdate(const float deltaTime) {
    if (playerState == PLAYER_DROP) {
        playerPosition.y += PLAYER_DROP_SPEED_Y * deltaTime;
        if (playerPosition.y >= PLAYER_START_POSITION_Y) {
            playerPosition.y  = PLAYER_START_POSITION_Y;
            playerState       = PLAYER_NORMAL;
        }
    }
}
void MainScene::PlayerDropDeathUpdate(const float deltaTiem) {
    if (playerState == PLAYER_DROP_DEATH) {
        playerPosition.y        += PLAYER_DROP_SPEED_Y * deltaTiem;
        playerSlidingPosition.y += PLAYER_DROP_SPEED_Y * deltaTiem;
        screenAlpha             += SCREENALPHA_COUNT   * deltaTiem;
    }
}

void MainScene::ObstacleUpdate(const float deltaTime) {
    DoorUpdate    (deltaTime);
    //RockUpdate    (deltaTime);
    //ArrowUpdate   (deltaTime);
    //BatUpdate     (deltaTime);
    //FakeBatUpdate(deltaTime);
    //ScaffoldUpdate(deltaTime);
    //HoleUpdate    (deltaTime);
}

void MainScene::DoorUpdate(const float deltaTime) {
    for (int i = 0; i < DOOR_DOWN_MAX; ++i) {
        if (doorDownPosition[i].x < DOOR_DOWN_START_POSITOIN_X &&
            doorDownPosition[i].y < DOOR_SLOW_DOWN_START_POSITOIN_Y) {
            doorDownPosition[i].y += DOOR_DOWN_SPEED_Y * deltaTime;
        }
        
        if (doorDownPosition[i].y > DOOR_SLOW_DOWN_START_POSITOIN_Y) {
            doorDownPosition[i].y += DOOR_SLOW_DOWN_SPEED_Y * deltaTime;
        }

        if (doorDownPosition[i].y > DOOR_DOWN_LIMIT_POSITION_Y) {
            doorDownPosition[i].y = DOOR_DOWN_LIMIT_POSITION_Y;
        }

        float doorOldPosition = doorDownPosition[i].x;
        doorDownPosition[i].x += DOOR_MOVE_SPEED_X * deltaTime;

        if (doorDownPosition[i].x < DOOR_SE_PLAY_POSITION_X && doorOldPosition > DOOR_SE_PLAY_POSITION_X) {
            seDoorInstance[i]->Play(true);
        }
        if (doorDownPosition[i].x < 0 && doorOldPosition > 0) {
            seDoorInstance[i]->Stop(true);
        }

        if (playerPrevState == PLAYER_NORMAL ||
            playerPrevState == PLAYER_JUMP) {
            if (isIntersect(
                RectWH(playerPosition.x, playerPosition.y, PLAYER_HIT_SIZE_X, PLAYER_HIT_SIZE_Y),
                RectWH(doorDownPosition[i].x, doorDownPosition[i].y, DOOR_HIT_SIZE_X, DOOR_HIT_SIZE_Y))) {
                playerState = PLAYER_DAMAGE;
            }
        }
        else if (playerPrevState == PLAYER_SLIDING) {
            if (isIntersect(
                RectWH(playerSlidingPosition.x, playerSlidingPosition.y, PLAYER_SLIDING_HIT_SIZE_X, PLAYER_SLIDING_HIT_SIZE_Y),
                RectWH(doorDownPosition[i].x, doorDownPosition[i].y, DOOR_HIT_SIZE_X, DOOR_HIT_SIZE_Y))) {
                playerState = PLAYER_DAMAGE;
            }
        }
    }

    doorUpPosition.x += DOOR_MOVE_SPEED_X * deltaTime;
    if (doorUpPosition.x < DOOR_DOWN_START_POSITOIN_X) {
        doorUpPosition.y += DOOR_UP_SPEED_Y * deltaTime;
    }
    if (doorUpPosition.y < DOOR_UP_LIMIT_POSITION_Y) {
        doorUpPosition.y = DOOR_UP_LIMIT_POSITION_Y;
    }

    if (playerPrevState == PLAYER_NORMAL ||
        playerPrevState == PLAYER_JUMP) {
        if (isIntersect(
            RectWH(playerPosition.x, playerPosition.y, PLAYER_HIT_SIZE_X, PLAYER_HIT_SIZE_Y),
            RectWH(doorUpPosition.x, doorUpPosition.y, DOOR_HIT_SIZE_X, DOOR_HIT_SIZE_Y))) {
            playerState = PLAYER_DAMAGE;
        }
    }
    else if (playerPrevState == PLAYER_SLIDING) {
        if (isIntersect(
            RectWH(playerSlidingPosition.x, playerSlidingPosition.y, PLAYER_SLIDING_HIT_SIZE_X, PLAYER_SLIDING_HIT_SIZE_Y),
            RectWH(doorUpPosition.x, doorUpPosition.y, DOOR_HIT_SIZE_X, DOOR_HIT_SIZE_Y))) {
            playerState = PLAYER_DAMAGE;
        }
    }
}
void MainScene::RockUpdate(const float deltaTime) {
    for (int i = 0; i < ROCK_MAX; ++i) {
        rockPosition[i].x -= ROCK_MOVE_SPEED_X * deltaTime;

        if (rockPosition[i].x < ROCK_DOWN_POSITION_X) {
            rockPosition[i].y += ROCK_MOVE_SPEED_Y * deltaTime;
        }

        if (rockPosition[i].y >= ROCK_LIMIT_POSITION_Y) {
            rockPosition[i].y  = ROCK_LIMIT_POSITION_Y;
        }

        if (playerPrevState == PLAYER_NORMAL ||
            playerPrevState == PLAYER_JUMP) {
            if (isIntersect(
                RectWH(playerPosition.x, playerPosition.y, PLAYER_HIT_SIZE_X, PLAYER_HIT_SIZE_Y),
                RectWH(rockPosition[i].x, rockPosition[i].y, ROCK_HIT_SIZE_X, ROCK_HIT_SIZE_Y))) {
                playerState = PLAYER_DAMAGE;
                sePlayerDamage->Play();
            }
        }
        else if (playerPrevState == PLAYER_SLIDING) {
            if (isIntersect(
                RectWH(playerSlidingPosition.x, playerSlidingPosition.y, PLAYER_SLIDING_HIT_SIZE_X, PLAYER_SLIDING_HIT_SIZE_Y),
                RectWH(rockPosition[i].x, rockPosition[i].y, ROCK_HIT_SIZE_X, ROCK_HIT_SIZE_Y))) {
                playerState = PLAYER_DAMAGE;
                sePlayerDamage->Play();
            }
        }
    }
}
void MainScene::ArrowUpdate(const float deltaTime) {
    for (int i = 0; i < ARROW_MAX; ++i) {
        arrowPosition[i].x -= ARROW_MOVE_SPEED_X * deltaTime;

        if (playerPrevState == PLAYER_NORMAL ||
            playerPrevState == PLAYER_JUMP) {
            if (isIntersect(
                RectWH(playerPosition.x, playerPosition.y, PLAYER_HIT_SIZE_X, PLAYER_HIT_SIZE_Y),
                RectWH(arrowPosition[i].x, arrowPosition[i].y, ARROW_HIT_SIZE_X, ARROW_HIT_SIZE_Y))) {
                playerState = PLAYER_DAMAGE;
            }
        }
        else if (playerPrevState == PLAYER_SLIDING) {
            if (isIntersect(
                RectWH(playerSlidingPosition.x, playerSlidingPosition.y, PLAYER_SLIDING_HIT_SIZE_X, PLAYER_SLIDING_HIT_SIZE_Y),
                RectWH(arrowPosition[i].x, arrowPosition[i].y, ARROW_HIT_SIZE_X, ARROW_HIT_SIZE_Y))) {
                playerState = PLAYER_DAMAGE;
            }
        }
    }
}
void MainScene::BatUpdate(const float deltaTime) {
    for (int i = 0; i < BAT_MAX; ++i) {
        batPosition[i].x += BAT_MOVE_SPPED_X * deltaTime;

        theta += BAT_MOVE_SPPED_Y * deltaTime;
        batPosition[i].y      = batBaseY + sinf(theta) * BAT_MOVE_RANGE_Y;

        if (playerPrevState == PLAYER_NORMAL ||
            playerPrevState == PLAYER_JUMP) {
            if (isIntersect(
                RectWH(playerPosition.x, playerPosition.y, PLAYER_HIT_SIZE_X, PLAYER_HIT_SIZE_Y),
                RectWH(batPosition[i].x, batPosition[i].y+BAT_HIT_POSITION_Y, BAT_HIT_SIZE_X, BAT_HIT_SIZE_Y))) {
                playerState = PLAYER_DAMAGE;
            }
        }
        else if (playerPrevState == PLAYER_SLIDING) {
            if (isIntersect(
                RectWH(playerSlidingPosition.x, playerSlidingPosition.y, PLAYER_SLIDING_HIT_SIZE_X, PLAYER_SLIDING_HIT_SIZE_Y),
                RectWH(batPosition[i].x, batPosition[i].y+ BAT_HIT_POSITION_Y, BAT_HIT_SIZE_X, BAT_HIT_SIZE_Y))) {
                playerState = PLAYER_DAMAGE;
            }
        }
    }
}
void MainScene::FakeBatUpdate(const float deltaTime) {
    for (int i = 0; i < FAKE_BAT_RIGHT_MAX; ++i) {
        fakeBatRightPosition[i].x += FAKE_BAT_RIGHT_MOVE_SPEED_X * deltaTime;
    }

    for (int i = 0; i < FAKE_BAT_LEFT_MAX; ++i) {
        fakeBatLeftPosition[i].x += BAT_MOVE_SPPED_X * deltaTime;
    }

}
void MainScene::ScaffoldUpdate(const float deltaTime) {
    for (int i = 0; i < SCAFFOLD_MAX; ++i) {
        scaffoldPosition[i].x -= SCAFFOLD_MOVE_SPPED_X * deltaTime;

        if (playerPrevState == PLAYER_NORMAL ||
            playerPrevState == PLAYER_JUMP) {
            if (isIntersect(
                RectWH(playerPosition.x, playerPosition.y, PLAYER_HIT_SIZE_X, PLAYER_HIT_SIZE_Y),
                RectWH(scaffoldPosition[i].x, scaffoldPosition[i].y + SCAFFOLD_HIT_POSITION_Y, SCAFFOLD_HIT_DEATH_SIZE_X, SCAFFOLD_HIT_DEATH_SIZE_Y))) {
                playerState = PLAYER_DAMAGE;
                break;
            }
        }
        else if (playerPrevState == PLAYER_SLIDING) {
            if (isIntersect(
                RectWH(playerSlidingPosition.x, playerSlidingPosition.y, PLAYER_SLIDING_HIT_SIZE_X, PLAYER_SLIDING_HIT_SIZE_Y),
                RectWH(scaffoldPosition[i].x, scaffoldPosition[i].y + SCAFFOLD_HIT_POSITION_Y, SCAFFOLD_HIT_DEATH_SIZE_X, SCAFFOLD_HIT_DEATH_SIZE_Y))) {
                playerState = PLAYER_DAMAGE;
            }
        }
    }
}
void MainScene::HoleUpdate(const float deltaTime) {
    ShrotHoleUpdate     (deltaTime);
    MiddleHoleUpdate    (deltaTime);
    LongHoleUpdate      (deltaTime);
    DoubleLongHoleUpdate(deltaTime);
}
void MainScene::ShrotHoleUpdate(const float deltaTime) {
    for (int i = 0; i < SHORT_HOLE_MAX; ++i) {
        shortHolePosition[i].x += HOLE_MOVE_SPPED_X * deltaTime;

        if (playerPrevState == PLAYER_NORMAL ||
            playerPrevState == PLAYER_JUMP ||
            playerPrevState == PLAYER_DAMAGE) {
            if (isIntersect(
                RectWH(playerPosition.x, playerPosition.y, PLAYER_HIT_SIZE_X, PLAYER_HIT_SIZE_Y),
                RectWH(shortHolePosition[i].x + SHORT_HOLE_HIT_POSITION_X, shortHolePosition[i].y, SHORT_HOLE_HIT_SIZE_X, HOLE_HIT_SIZE_Y))) {
                playerState = PLAYER_DROP_DEATH;
            }
        }
        else if (playerPrevState == PLAYER_SLIDING) {
            if (isIntersect(
                RectWH(playerSlidingPosition.x, playerSlidingPosition.y, PLAYER_SLIDING_HIT_SIZE_X, PLAYER_SLIDING_HIT_SIZE_Y),
                RectWH(shortHolePosition[i].x + SHORT_HOLE_HIT_POSITION_X, shortHolePosition[i].y, SHORT_HOLE_HIT_SIZE_X, HOLE_HIT_SIZE_Y))) {
                playerState = PLAYER_DROP_DEATH;
            }
        }
    }
}
void MainScene::MiddleHoleUpdate(const float deltaTime) {
    middleHolePosition.x += HOLE_MOVE_SPPED_X * deltaTime;
    if (playerPrevState == PLAYER_NORMAL ||
        playerPrevState == PLAYER_JUMP ||
        playerPrevState == PLAYER_DAMAGE) {
        if (isIntersect(
            RectWH(playerPosition.x, playerPosition.y, PLAYER_HIT_SIZE_X, PLAYER_HIT_SIZE_Y),
            RectWH(middleHolePosition.x, middleHolePosition.y, MIDDLE_HOLE_HIT_SIZE_X, HOLE_HIT_SIZE_Y))) {
            playerState = PLAYER_DROP_DEATH;
        }
    }
    else if (playerPrevState == PLAYER_SLIDING) {
        if (isIntersect(
            RectWH(playerSlidingPosition.x, playerSlidingPosition.y, PLAYER_SLIDING_HIT_SIZE_X, PLAYER_SLIDING_HIT_SIZE_Y),
            RectWH(middleHolePosition.x, middleHolePosition.y, MIDDLE_HOLE_HIT_SIZE_X, HOLE_HIT_SIZE_Y))) {
            playerState = PLAYER_DROP_DEATH;
        }
    }
}
void MainScene::LongHoleUpdate(const float deltaTime) {
    longHolePosition.x += HOLE_MOVE_SPPED_X * deltaTime;
    if (playerPrevState == PLAYER_NORMAL ||
        playerPrevState == PLAYER_JUMP ||
        playerPrevState == PLAYER_DAMAGE) {
        if (isIntersect(
            RectWH(playerPosition.x, playerPosition.y, PLAYER_HIT_SIZE_X, PLAYER_HIT_SIZE_Y),
            RectWH(longHolePosition.x, longHolePosition.y, LONG_HOLE_HIT_SIZE_X, HOLE_HIT_SIZE_Y))) {
            playerState = PLAYER_DROP_DEATH;
        }
    }
    else if (playerPrevState == PLAYER_SLIDING) {
        if (isIntersect(
            RectWH(playerSlidingPosition.x, playerSlidingPosition.y, PLAYER_SLIDING_HIT_SIZE_X, PLAYER_SLIDING_HIT_SIZE_Y),
            RectWH(longHolePosition.x, longHolePosition.y, LONG_HOLE_HIT_SIZE_X, HOLE_HIT_SIZE_Y))) {
            playerState = PLAYER_DROP_DEATH;
        }
    }
}
void MainScene::DoubleLongHoleUpdate(const float deltaTime) {
    doubleLongHolePosition.x += HOLE_MOVE_SPPED_X * deltaTime;
    if (playerPrevState == PLAYER_NORMAL ||
        playerPrevState == PLAYER_JUMP ||
        playerPrevState == PLAYER_DAMAGE) {
        if (isIntersect(
            RectWH(playerPosition.x, playerPosition.y, PLAYER_HIT_SIZE_X, PLAYER_HIT_SIZE_Y),
            RectWH(doubleLongHolePosition.x, doubleLongHolePosition.y, DOUBLE_LONG_HOLE_HIT_SIZE_X, HOLE_HIT_SIZE_Y))) {
            playerState = PLAYER_DROP_DEATH;
        }
    }
    else if (playerPrevState == PLAYER_SLIDING) {
        if (isIntersect(
            RectWH(playerSlidingPosition.x, playerSlidingPosition.y, PLAYER_SLIDING_HIT_SIZE_X, PLAYER_SLIDING_HIT_SIZE_Y),
            RectWH(doubleLongHolePosition.x, doubleLongHolePosition.y, DOUBLE_LONG_HOLE_HIT_SIZE_X, HOLE_HIT_SIZE_Y))) {
            playerState = PLAYER_DROP_DEATH;
        }
    }
}

NextScene MainScene::SeneChangeUpdate(const float deltaTime) {
    if (screenAlpha >= SCREENALPHA_LIMIT) {
        return NextScene::GameOverScene;
        screenAlpha = SCREENALPHA_LIMIT;
    }

    if (playerPosition.x >= PLAYER_LIMIT_POSITION_X) {
        return NextScene::ClearScene;
    }

    return NextScene::Continue;
}

void MainScene::AnimationUpdate(const float deltaTime) {
    batAnimeX += BAT_ANIME_SPEED_X * deltaTime;
    if (batAnimeX > BAT_ANIME_MAX_COUNT) {
        batAnimeX = 0.0f;
    }

    playerAnimeX += PLAYER_ANIME_SPEED_X * deltaTime;
    if (playerAnimeX > PLAYER_ANIME_MAX_COUNT) {
        playerAnimeX = 0.0f;
    }

    torchAnimeX += TORCH_ANIME_SPED * deltaTime;
    if (torchAnimeX > TORCH_ANIME_MAX_COUNT_X) {
        torchAnimeX = 0.0f;
        torchAnimeY++;
        if (torchAnimeY >= TORCH_ANIME_MAX_COUNT_Y) {
            torchAnimeY = 0.0f;
        }
    }
}

bool MainScene::isIntersect(Rect& rect1, Rect& rect2) {
    if (rect1.left > rect2.right || rect1.right  < rect2.left ||
        rect1.top  > rect2.bottom || rect1.bottom < rect2.top) {
        return false;
    }

    return true;
}