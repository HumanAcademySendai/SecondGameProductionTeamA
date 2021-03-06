//
// MainScene.cpp
//

#include "Base/pch.h"
#include "Base/dxtk.h"
#include "SceneFactory.h"

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

    collapsePosition.x = COLLAPSE_START_POSITION_X;
    collapsePosition.y = COLLAPSE_START_POSITION_Y;
    collapsePosition.z = COLLAPSE_START_POSITION_Z;

    ceilingPosition.x = CEILING_START_POSITION_X;
    ceilingPosition.y = CEILING_START_POSITION_Y;
    ceilingPosition.z = CEILING_START_POSITION_Z;

    //プレイヤーの初期化
    playerState        = PLAYER_NORMAL;
    playerPosition.x = PLAYER_START_POSITION_X;
    playerPosition.y = PLAYER_START_POSITION_Y;
    playerPosition.z = PLAYER_START_POSITION_Z;
    playerSlidingPosition.x = playerPosition.x;
    playerSlidingPosition.y = playerPosition.y + PLAYER_SLIDING_POSITION_Y;
    playerSlidingPosition.z = PLAYER_START_POSITION_Z;
    playerSlidingCount = PLAYER_SLIDING_START_COUNT;
    playerDamageCount  = 0;
    playerMoveCount    = PLAYER_MOVE_START_COUNT;
    gravity            = 0;
    
    //障害物の初期化
    doorX =  DOOR_START_POSITION_X;
    doorY = -DOOR_START_POSITION_Y;

    rockX[0] =  ROCK_START_POSITION_X;
    rockY[0] = -ROCK_START_POSITION_Y;
    rockX[1] =  ROCK_START_POSITION_X + 200;
    rockY[1] = -ROCK_START_POSITION_Y;
    rockX[2] =  ROCK_START_POSITION_X + 400;
    rockY[2] = -ROCK_START_POSITION_Y;
    rockX[3] =  ROCK_START_POSITION_X + 600;
    rockY[3] = -ROCK_START_POSITION_Y;
    rockX[4] =  ROCK_START_POSITION_X + 800;
    rockY[4] = -ROCK_START_POSITION_Y;

    arrowX = ARROW_START_POSITION_X;
    arrowY = ARROW_START_POSITION_Y;

    batX = BAT_START_POSITION_X;
    batY = BAT_START_POSITION_Y;

    scaffoldX = SCAFFOLD_START_POSITION_X;
    scaffoldY = 0;

    jewelryX = JEWELRY_START_POSITION_X;
    jewelryY = JEWELRY_START_POSITION_Y;
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
    bgSprite            = DX9::Sprite::CreateFromFile(DXTK->Device9, L"BG/main_bg.png" );
    collapseSprite      = DX9::Sprite::CreateFromFile(DXTK->Device9, L"BG/collapse.png");
    ceilingSprite       = DX9::Sprite::CreateFromFile(DXTK->Device9, L"BG/ceiling.png" );

    //プレイヤー
    playerSprite        = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Player/p_run.png"    );
    playerSlidingSprite = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Player/p_sliding.png");
    playerJumpSprite    = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Player/p_jump.png"   );
    playerPauseSprite   = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Player/p_pause.png"  );

    //障害物
    doorSprite     = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Obstacle/door.png"    );
    rockSprite     = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Obstacle/rock.png"    );
    arrowSprite    = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Obstacle/arrow.png"   );
    batSprite      = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Obstacle/bat.png"     );
    scaffoldSprite = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Obstacle/scaffold.png");
    jewelrySprite  = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Obstacle/jewelry.png" );
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

    return NextScene::Continue;
}

// Draws the scene.
void MainScene::Render()
{
    // TODO: Add your rendering code here.
    DXTK->Direct3D9->Clear(DX9::Colors::RGBA(0, 0, 0, 255));

    DXTK->Direct3D9->BeginScene();
    DX9::SpriteBatch->Begin();



    DX9::SpriteBatch->DrawString(
        font.Get(),
        SimpleMath::Vector2(0.0f, 0.0f),
        DX9::Colors::RGBA(500, 0, 0, 255),
        L"ループの回数  %d", number
    );


    //背景の描画
    DX9::SpriteBatch->DrawSimple(
        bgSprite.Get(),
        bgScrollPosition);

    DX9::SpriteBatch->DrawSimple(
        collapseSprite.Get(),
        collapsePosition);

    DX9::SpriteBatch->DrawSimple(
        ceilingSprite.Get(),
        ceilingPosition);

    //プレイヤーの描画
    if (playerState == PLAYER_NORMAL || playerState == PLAYER_MOVE) {
        DX9::SpriteBatch->DrawSimple(
            playerSprite.Get(),
            playerPosition);
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
    DX9::SpriteBatch->DrawSimple(
        doorSprite.Get(),
        SimpleMath::Vector3(doorX, doorY, 0.0f)
    );

    for (int i = 0; i < 5; i++) {
        DX9::SpriteBatch->DrawSimple(
            rockSprite.Get(),
            SimpleMath::Vector3(rockX[i], rockY[i], 0.0f)
        );
    }
    

    DX9::SpriteBatch->DrawSimple(
        arrowSprite.Get(),
        SimpleMath::Vector3(arrowX, arrowY, 0.0f)
    );

    DX9::SpriteBatch->DrawSimple(
        batSprite.Get(),
        SimpleMath::Vector3(batX, batY, 0.0f)
    );

    DX9::SpriteBatch->DrawSimple(
        scaffoldSprite.Get(),
        SimpleMath::Vector3(scaffoldX, scaffoldY, 0.0f)
    );

    DX9::SpriteBatch->DrawSimple(
        jewelrySprite.Get(),
        SimpleMath::Vector3(jewelryX, jewelryY, 0.0f)
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

    bgScrollPosition.x -= BG_SCROLL_SPEED_X * deltaTime;
    if (bgScrollPosition.x <= -BG_RESET_POSITION_X) {
        bgScrollPosition.x = BG_START_POSITION_X;
    }
}

void MainScene::PlayerUpdate(const float deltaTime) {

    PlayerSlidingUpdate(deltaTime);
    PlayerJumpUpdate   (deltaTime);
    PlayerDamageUpdate (deltaTime);
    PlayerMoveUpdate   (deltaTime);
}

void MainScene::PlayerSlidingUpdate(const float deltaTime) {
    if (playerState == PLAYER_NORMAL) {
        if (DXTK->KeyEvent->pressed.S || DXTK->KeyEvent->pressed.Down || DXTK->GamePadState->IsDPadDownPressed()) {
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

    if (playerState == PLAYER_NORMAL && playerPosition.y >= PLAYER_START_POSITION_Y) {
        if (DXTK->KeyEvent->pressed.Space || DXTK->GamePadEvent->a) {
            playerState = PLAYER_JUMP;
            gravity = GRAVITY_POWER_TAKE;
        }
    }

    if (playerState == PLAYER_JUMP) {
        playerPosition.y -= gravity * deltaTime;
        gravity -= GRAVITY_POWER_ADD * deltaTime;
    }

    if (playerPosition.y > PLAYER_START_POSITION_Y) {
        playerPosition.y = PLAYER_START_POSITION_Y;
        playerState = PLAYER_NORMAL;
    }
}
void MainScene::PlayerDamageUpdate(const float deltaTime) {
    for (int i = 0; i < 5; ++i) {
        if (playerState == PLAYER_NORMAL || playerState == PLAYER_SLIDING) {
            if (isIntersect(RectWH(playerPosition.x, playerPosition.y, 116, 132), RectWH(rockX[i], rockY[i], 104, 82))) {
                playerState = PLAYER_DAMAGE;
            }
            else {

            }
        }
    }
    
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
    if (playerMoveCount <= 0) {
        playerState = PLAYER_MOVE;
    }

    if (playerState == PLAYER_MOVE) {
        playerPosition.x += PLAYER_MOVE_SPEED * deltaTime;
    }
}

void MainScene::ObstacleUpdate(const float deltaTime) {
    //DoorUpdate (deltaTime);
    RockUpdate (deltaTime);
    //ArrowUpdate(deltaTime);
    //BatUpdate  (deltaTime);
    //ScaffoldUpdate(deltaTime);
    //JewelryUpdate(deltaTime);
}

void MainScene::DoorUpdate(const float deltaTime) {
    doorY += DOOR_DOWN_SPEED_Y * deltaTime;
    if (doorY >= DOOR_LIMIT_POSITION_Y) {
        doorY  = DOOR_LIMIT_POSITION_Y;
    }

    doorX -= DOOR_MOVE_SPEED_X * deltaTime;
}
void MainScene::RockUpdate(const float deltaTime) {
    for (int i = 0; i < 5; ++i) {
        rockX[i] -= ROCK_MOVE_SPEED_X * deltaTime;
        rockY[i] += ROCK_DOWN_SPEED_Y * deltaTime;
        if (rockY[i] >= ROCK_LIMIT_POSITION_Y) {
            rockY[i]  = ROCK_LIMIT_POSITION_Y;
        }
    }
    
}
void MainScene::ArrowUpdate(const float deltaTime) {
    arrowX -= ARROW_MOVE_SPEED_X * deltaTime;
}
void MainScene::BatUpdate(const float deltaTime) {
    batX -= BAT_MOVE_SPPED_X * deltaTime;
}
void MainScene::ScaffoldUpdate(const float deltaTime) {
    scaffoldX -= SCAFFOLD_MOVE_SPPED_X * deltaTime;
}
void MainScene::JewelryUpdate(const float deltaTime) {
    jewelryX -= JEWELRY_MOVE_SPEED_X * deltaTime;
}

bool MainScene::isIntersect(Rect& rect1, Rect& rect2) {
    if (rect1.left > rect2.right || rect1.right  < rect2.left ||
        rect1.top  > rect2.bottom || rect1.bottom < rect2.top) {
        return false;
    }

    return true;
}