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
    playerMoveCount    = PLAYER_MOVE_START_COUNT;
    playerDamageCount  = 0;
    gravity            = 0;
    playerAnimeX       = 0;


    //障害物の初期化
    //扉
    doorPosition[0].x = DOOR_START_POSITION_X_1;
    doorPosition[0].y = DOOR_START_POSITION_Y;
    doorPosition[0].z = DOOR_START_POSITION_Z;
    doorPosition[1].x = DOOR_START_POSITION_X_2;
    doorPosition[1].y = DOOR_START_POSITION_Y;
    doorPosition[1].z = DOOR_START_POSITION_Z;
    doorPosition[2].x = DOOR_START_POSITION_X_3;
    doorPosition[2].y = DOOR_START_POSITION_Y;
    doorPosition[2].z = DOOR_START_POSITION_Z;
    doorPosition[3].x = DOOR_START_POSITION_X_4;
    doorPosition[3].y = DOOR_START_POSITION_Y;
    doorPosition[3].z = DOOR_START_POSITION_Z;
    doorPosition[4].x = DOOR_START_POSITION_X_5;
    doorPosition[4].y = DOOR_START_POSITION_Y;
    doorPosition[4].z = DOOR_START_POSITION_Z;
    doorPosition[5].x = DOOR_START_POSITION_X_6;
    doorPosition[5].y = DOOR_START_POSITION_Y;
    doorPosition[5].z = DOOR_START_POSITION_Z;

    //岩
    rockPosition[0].x = ROCK_START_POSITION_X_1;
    rockPosition[0].y = ROCK_START_POSITION_Y;
    rockPosition[0].z = ROCK_START_POSITION_Z;
    rockPosition[1].x = ROCK_START_POSITION_X_2;
    rockPosition[1].y = ROCK_START_POSITION_Y;
    rockPosition[1].z = ROCK_START_POSITION_Z;
    rockPosition[2].x = ROCK_START_POSITION_X_2;
    rockPosition[2].y = ROCK_START_POSITION_Y;
    rockPosition[2].z = ROCK_START_POSITION_Z;
    rockPosition[3].x = ROCK_START_POSITION_X_3;
    rockPosition[3].y = ROCK_START_POSITION_Y;
    rockPosition[3].z = ROCK_START_POSITION_Z;

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

    theta = 0;
    batBaseY = batPosition[0].y;
    batAnimeX = 0;

    batDeathPosition[0].x = BAT_DEATH_START_POSITION_X_1;
    batDeathPosition[0].y = BAT_DEATH_START_POSITION_Y;
    batDeathPosition[1].x = BAT_DEATH_START_POSITION_X_2;
    batDeathPosition[1].y = BAT_DEATH_START_POSITION_Y;
    batDeathPosition[2].x = BAT_DEATH_START_POSITION_X_3;
    batDeathPosition[2].y = BAT_DEATH_START_POSITION_Y;
    batDeathPosition[3].x = BAT_DEATH_START_POSITION_X_4;
    batDeathPosition[3].y = BAT_DEATH_START_POSITION_Y;

    batDeathBaseY = batDeathPosition[0].y;

    //足場
    scaffoldPosition[0].x = SCAFFOLD_START_POSITION_X;
    scaffoldPosition[0].y = SCAFFOLD_START_POSITION_Y;
    scaffoldPosition[0].z = SCAFFOLD_START_POSITION_Z;

    scaffoldDeathPosition[0].x = SCAFFOLD_DEATH_START_POSITION_X;
    scaffoldDeathPosition[0].y = SCAFFOLD_DEATH_START_POSITION_Y;
    scaffoldDeathPosition[0].z = SCAFFOLD_DEATH_START_POSITION_Z;

    scaffoldPosition[1].x = SCAFFOLD_START_POSITION_X + 500;
    scaffoldPosition[1].y = SCAFFOLD_START_POSITION_Y - 50;
    scaffoldPosition[1].z = SCAFFOLD_START_POSITION_Z;

    scaffoldDeathPosition[1].x = SCAFFOLD_DEATH_START_POSITION_X + 500;
    scaffoldDeathPosition[1].y = SCAFFOLD_DEATH_START_POSITION_Y - 50;
    scaffoldDeathPosition[1].z = SCAFFOLD_DEATH_START_POSITION_Z;

    scaffoldNumber = 0;

    frontChainPosition.x = SCAFFOLD_START_POSITION_X;
    frontChainPosition.y = 0;
    frontChainPosition.z = SCAFFOLD_START_POSITION_Z;

    //宝
    jewelryPosition[0].x      = JEWELRY_START_POSITION_X_1;
    jewelryPosition[0].y      = JEWELRY_START_POSITION_Y;
    jewelryPosition[0].z      = JEWELRY_START_POSITION_Z;
    jewelryPosition[1].x      = JEWELRY_START_POSITION_X_2;
    jewelryPosition[1].y      = JEWELRY_START_POSITION_Y;
    jewelryPosition[1].z      = JEWELRY_START_POSITION_Z;
    jewelryPosition[2].x      = JEWELRY_START_POSITION_X_3;
    jewelryPosition[2].y      = JEWELRY_START_POSITION_Y_3;
    jewelryPosition[2].z      = JEWELRY_START_POSITION_Z;
    jewelryGetFlag[0]         = false;
    jewelryGetFlag[1]         = false;
    jewelryGetFlag[2]         = false;
    DontDestroy->jewelryCount = 0;

    //SE
    seCollapse         = XAudio::CreateSoundEffect(DXTK->AudioEngine, L"SE/collapse_se.wav");
    seCollapseInstance = seCollapse->CreateInstance();
    seCollapseInstance->Play(true);
    seJewelry          = XAudio::CreateSoundEffect(DXTK->AudioEngine, L"SE/jewelry_se.wav" );
    sePlayerDamage     = XAudio::CreateSoundEffect(DXTK->AudioEngine, L"SE/damage_se.wav"  );
    for (int i = 0; i < DOOR_MAX; ++i) {
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
    doorSprite          = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Obstacle/door.png"          );
    rockSprite          = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Obstacle/rock.png"          );
    arrowSprite         = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Obstacle/arrow.png"         );
    batSprite           = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Obstacle/bat.png"           );
    batDeathSprite      = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Obstacle/bat_death.png"     );
    scaffoldSprite      = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Obstacle/scaffold.png"      );
    scaffoldDeathSprite = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Obstacle/scaffold_death.png");
    frontChainSprite    = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Obstacle/chainF.png"        );
    backChainSprite     = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Obstacle/chainB.png"        );
    jewelrySprite       = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Obstacle/jewelry.png"       );

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

    for (int i = 0; i < DOOR_MAX; ++i) {
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

    BGUpdate      (deltaTime);
    PlayerUpdate  (deltaTime);
    ObstacleUpdate(deltaTime);
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
        playerState == PLAYER_MOVE   ||
        playerState == PLAYER_RIDE   ||
        playerState == PLAYER_DROP) {
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
    for (int i = 0; i < DOOR_MAX; ++i) {
        DX9::SpriteBatch->DrawSimple(
            doorSprite.Get(),
            doorPosition[i]);
    }
    
    //岩の描画
    for (int i = 0; i < ROCK_MAX; i++) {
        DX9::SpriteBatch->DrawSimple(
            rockSprite.Get(),
            rockPosition[i]);
    }
    
    //矢の描画
    for (int i = 0; i < ARROW_MAX; ++i) {
        DX9::SpriteBatch->DrawSimple(
            arrowSprite.Get(),
            arrowPosition[i]);
    }
    
    //コウモリの描画
    for (int i = 0; i < BAT_MAX; ++i) {
        DX9::SpriteBatch->DrawSimple(
            batSprite.Get(),
            batPosition[i],
            RectWH((int)batAnimeX * BAT_WIDTH, 0, BAT_WIDTH, BAT_HEIGHT));
    }
    
    //足場の描画
    for (int i = 0; i < SCAFFOLD_MAX; ++i) {
        DX9::SpriteBatch->DrawSimple(
            scaffoldSprite.Get(),
            scaffoldPosition[i]);
    }


    DX9::SpriteBatch->DrawSimple(
        frontChainSprite.Get(),
        frontChainPosition);


    //足場の当たり判定の描画
    for (int i = 0; i < SCAFFOLD_MAX; ++i) {
        DX9::SpriteBatch->DrawSimple(
            scaffoldDeathSprite.Get(),
            scaffoldDeathPosition[i]);
    }


    //宝の描画
    for (int i = 0; i < JEWELRY_MAX; ++i) {
        if (jewelryGetFlag[i] == false) {
            DX9::SpriteBatch->DrawSimple(
                jewelrySprite.Get(),
                jewelryPosition[i]);
        }
    }


    //フォント
    /*DX9::SpriteBatch->DrawString(
        font.Get(),
        SimpleMath::Vector2(0.0f, 0.0f),
        DX9::Colors::RGBA(500, 0, 0, 255),
        L"背景ループの回数  %d", bgLoopNumber
    );

    DX9::SpriteBatch->DrawString(
        font.Get(),
        SimpleMath::Vector2(0.0f, 90.0f),
        DX9::Colors::RGBA(500, 0, 0, 255),
        L"宝の獲得数  %d", jewelryGetFlag[0]
    );

    DX9::SpriteBatch->DrawString(
        font.Get(),
        SimpleMath::Vector2(0.0f, 120.0f),
        DX9::Colors::RGBA(500, 0, 0, 255),
        L"宝の獲得数  %d", jewelryGetFlag[1]
    );

    DX9::SpriteBatch->DrawString(
        font.Get(),
        SimpleMath::Vector2(0.0f, 150.0f),
        DX9::Colors::RGBA(500, 0, 0, 255),
        L"宝の獲得数  %d", jewelryGetFlag[2]
    );

    DX9::SpriteBatch->DrawString(
        font.Get(),
        SimpleMath::Vector2(0.0f, 30.0f),
        DX9::Colors::RGBA(500, 0, 0, 255),
        L" P移動 %f", playerMoveCount
    );

    DX9::SpriteBatch->DrawString(
        font.Get(),
        SimpleMath::Vector2(1000.0f, 30.0f),
        DX9::Colors::RGBA(500, 0, 0, 255),
        L" 宝の獲得数 %d", DontDestroy->jewelryCount
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
        torchPosition[i].x += TORCH_MOVE_SPEED_X * deltaTime;
        if (torchPosition[i].x < 0.0f) {
            torchPosition[i].x = TORCH_RESET_POSITION_X;
        }
    }
}

void MainScene::PlayerUpdate(const float deltaTime) {
    playerPrevState = playerState;
    PlayerSlidingUpdate(deltaTime);
    PlayerJumpUpdate   (deltaTime);
    PlayerDamageUpdate (deltaTime);
    PlayerMoveUpdate   (deltaTime);
    PlayerRideUpdate   (deltaTime);
    PlayerDropUpdate   (deltaTime);
}

void MainScene::PlayerSlidingUpdate(const float deltaTime) {
    if (playerState == PLAYER_NORMAL) {
        if (DXTK->KeyEvent->pressed.S ||
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
    if (playerState == PLAYER_DAMAGE) {
        playerDamageCount += deltaTime;
        if (playerDamageCount >= PLAYER_DAMAGE_LIMIT_COUNT) {
            playerState = PLAYER_NORMAL;
            playerDamageCount = 0;
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

    if (playerState == PLAYER_DAMAGE) {
        screenAlpha      += SCREENALPHA_COUNT * deltaTime;
        playerPosition.x -= PLAYER_MOVE_SPEED * deltaTime;
        playerPosition.y += PLAYER_MOVE_SPEED * deltaTime;
        if (playerPosition.y >= PLAYER_START_POSITION_Y) {
            playerPosition.y = PLAYER_START_POSITION_Y;
        }
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

void MainScene::ObstacleUpdate(const float deltaTime) {
    //DoorUpdate    (deltaTime);
    //RockUpdate    (deltaTime);
    //ArrowUpdate   (deltaTime);
    //BatUpdate     (deltaTime);
    //ScaffoldUpdate(deltaTime);
    //JewelryUpdate (deltaTime);
}

void MainScene::DoorUpdate(const float deltaTime) {
    for (int i = 0; i < DOOR_MAX; ++i) {
        if (doorPosition[i].x < DOOR_DOWN_START_POSITOIN_X) {
            doorPosition[i].y += DOOR_DOWN_SPEED_Y * deltaTime;
        }

        if (doorPosition[i].y > DOOR_LIMIT_POSITION_Y) {
            doorPosition[i].y = DOOR_LIMIT_POSITION_Y;
        }

        float doorOldPosition = doorPosition[i].x;
        doorPosition[i].x -= DOOR_MOVE_SPEED_X * deltaTime;
        if (doorPosition[i].x < DOOR_SE_PLAY_POSITION_X && doorOldPosition > DOOR_SE_PLAY_POSITION_X) {
            seDoorInstance[i]->Play(true);
        }
        if (doorPosition[i].x < 0 && doorOldPosition > 0) {
            seDoorInstance[i]->Stop(true);
        }

        if (playerPrevState == PLAYER_NORMAL ||
            playerPrevState == PLAYER_JUMP) {
            if (isIntersect(
                RectWH(playerPosition.x, playerPosition.y, PLAYER_HIT_SIZE_X, PLAYER_HIT_SIZE_Y),
                RectWH(doorPosition[i].x, doorPosition[i].y, DOOR_HIT_SIZE_X, DOOR_HIT_SIZE_Y))) {
                playerState = PLAYER_DAMAGE;
            }
        }
        else if (playerPrevState == PLAYER_SLIDING) {
            if (isIntersect(
                RectWH(playerSlidingPosition.x, playerSlidingPosition.y, PLAYER_SLIDING_HIT_SIZE_X, PLAYER_SLIDING_HIT_SIZE_Y),
                RectWH(doorPosition[i].x, doorPosition[i].y, DOOR_HIT_SIZE_X, DOOR_HIT_SIZE_Y))) {
                playerState = PLAYER_DAMAGE;
            }
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
            rockPosition[i].y = ROCK_LIMIT_POSITION_Y;
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

        batPosition[i].x -= BAT_MOVE_SPPED_X * deltaTime;
        batDeathPosition[i].x -= BAT_MOVE_SPPED_X * deltaTime;

        theta += BAT_MOVE_SPPED_Y * deltaTime;
        batPosition[i].y      = batBaseY + sinf(theta) * BAT_MOVE_RANGE_Y;
        batDeathPosition[i].y = batDeathBaseY + sinf(theta) * BAT_MOVE_RANGE_Y;

        if (playerPrevState == PLAYER_NORMAL ||
            playerPrevState == PLAYER_JUMP) {
            if (isIntersect(
                RectWH(playerPosition.x, playerPosition.y, PLAYER_HIT_SIZE_X, PLAYER_HIT_SIZE_Y),
                RectWH(batDeathPosition[i].x, batDeathPosition[i].y, BAT_HIT_SIZE_X, BAT_HIT_SIZE_Y))) {
                playerState = PLAYER_DAMAGE;
            }
        }
        else if (playerPrevState == PLAYER_SLIDING) {
            if (isIntersect(
                RectWH(playerSlidingPosition.x, playerSlidingPosition.y, PLAYER_SLIDING_HIT_SIZE_X, PLAYER_SLIDING_HIT_SIZE_Y),
                RectWH(batDeathPosition[i].x, batDeathPosition[i].y, BAT_HIT_SIZE_X, BAT_HIT_SIZE_Y))) {
                playerState = PLAYER_DAMAGE;
            }
        }
    }
}
void MainScene::ScaffoldUpdate(const float deltaTime) {
    for (int i = 0; i < SCAFFOLD_MAX; ++i) {
        scaffoldPosition[i].x      -= SCAFFOLD_MOVE_SPPED_X * deltaTime;
        scaffoldDeathPosition[i].x -= SCAFFOLD_MOVE_SPPED_X * deltaTime;

        if (playerPrevState == PLAYER_NORMAL ||
            playerPrevState == PLAYER_JUMP) {
            if (isIntersect(
                RectWH(playerPosition.x, playerPosition.y, PLAYER_HIT_SIZE_X, PLAYER_HIT_SIZE_Y),
                RectWH(scaffoldDeathPosition[i].x, scaffoldDeathPosition[i].y, SCAFFOLD_DEATH_HIT_SIZE_X, SCAFFOLD_DEATH_HIT_SIZE_Y))) {
                playerState = PLAYER_DAMAGE;
                break;
            }
        }
        else if (playerPrevState == PLAYER_SLIDING) {
            if (isIntersect(
                RectWH(playerSlidingPosition.x, playerSlidingPosition.y, PLAYER_SLIDING_HIT_SIZE_X, PLAYER_SLIDING_HIT_SIZE_Y),
                RectWH(scaffoldDeathPosition[i].x, scaffoldDeathPosition[i].y, SCAFFOLD_DEATH_HIT_SIZE_X, SCAFFOLD_DEATH_HIT_SIZE_Y))) {
                playerState = PLAYER_DAMAGE;
            }
        }
    }
}
void MainScene::JewelryUpdate(const float deltaTime) {
    for (int i = 0; i < JEWELRY_MAX; ++i) {
        jewelryPosition[i].x -= JEWELRY_MOVE_SPEED_X * deltaTime;
    }

    for (int i = 0; i < JEWELRY_MAX; ++i) {
        if (playerPrevState == PLAYER_NORMAL  ||
            playerPrevState == PLAYER_SLIDING ||
            playerPrevState == PLAYER_JUMP) {
            if (jewelryGetFlag[i] == false) {
                if (isIntersect(
                    RectWH(playerPosition.x, playerPosition.y, PLAYER_HIT_SIZE_X, PLAYER_HIT_SIZE_Y),
                    RectWH(jewelryPosition[i].x, jewelryPosition[i].y, JEWELRY_HIT_SIZE_X, JEWELRY_HIT_SIZE_Y))) {
                    jewelryGetFlag[i] = true;
                    DontDestroy->jewelryCount++;
                    seJewelry->Play();
                }
            }
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