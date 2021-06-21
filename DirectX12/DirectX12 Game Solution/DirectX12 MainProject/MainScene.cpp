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
    //”wŒiƒXƒNƒ[ƒ‹‚Ì‰Šú‰»
    bgScrollPosition.x = BG_START_POSITION_X;
    bgScrollPosition.y = BG_START_POSITION_Y;
    bgScrollPosition.z = BG_START_POSITION_Z;

    collapsePosition.x = COLLAPSE_START_POSITION_X;
    collapsePosition.y = COLLAPSE_START_POSITION_Y;
    collapsePosition.z = COLLAPSE_START_POSITION_Z;

    ceilingPosition.x = CEILING_START_POSITION_X;
    ceilingPosition.y = CEILING_START_POSITION_Y;
    ceilingPosition.z = CEILING_START_POSITION_Z;

    bgLoopNumber = 0;

    //ƒvƒŒƒCƒ„[‚Ì‰Šú‰»
    playerState        = PLAYER_NORMAL;
    playerPosition.x = PLAYER_START_POSITION_X;
    playerPosition.y = PLAYER_START_POSITION_Y;
    playerPosition.z = PLAYER_START_POSITION_Z;
    playerSlidingPosition.x = PLAYER_SLIDING_START_POSITION_X;
    playerSlidingPosition.y = PLAYER_SLIDING_START_POSITION_Y;
    playerSlidingPosition.z = PLAYER_START_POSITION_Z;
    playerSlidingCount = PLAYER_SLIDING_START_COUNT;
    playerDamageCount  = 0;
    playerMoveCount    = PLAYER_MOVE_START_COUNT;
    gravity            = 0;
    
    
    //áŠQ•¨‚Ì‰Šú‰»
    doorPosition.x =  DOOR_START_POSITION_X;
    doorPosition.y = -DOOR_START_POSITION_Y;
    doorPosition.z =  DOOR_START_POSITION_Z;

    rockPosition[0].x =  ROCK_START_POSITION_X;
    rockPosition[0].y = -ROCK_START_POSITION_Y;
    rockPosition[0].z = ROCK_START_POSITION_Z;
    rockPosition[1].x =  ROCK_START_POSITION_X + 2000;
    rockPosition[1].y = -ROCK_START_POSITION_Y;
    rockPosition[1].z = ROCK_START_POSITION_Z;
    rockPosition[2].x =  ROCK_START_POSITION_X + 4000;
    rockPosition[2].y = -ROCK_START_POSITION_Y;
    rockPosition[2].z = ROCK_START_POSITION_Z;
    rockPosition[3].x =  ROCK_START_POSITION_X + 6000;
    rockPosition[3].y = -ROCK_START_POSITION_Y;
    rockPosition[3].z = ROCK_START_POSITION_Z;
    rockPosition[4].x =  ROCK_START_POSITION_X + 8000;
    rockPosition[4].y = -ROCK_START_POSITION_Y;
    rockPosition[4].z = ROCK_START_POSITION_Z;

    arrowPosition[0].x = ARROW_START_POSITION_X;
    arrowPosition[0].y = ARROW_START_POSITION_Y;
    arrowPosition[0].z = ARROW_START_POSITION_Z;
    arrowPosition[1].x = ARROW_START_POSITION_X;
    arrowPosition[1].y = ARROW_START_POSITION_Y;
    arrowPosition[1].z = ARROW_START_POSITION_Z;
    arrowPosition[2].x = ARROW_START_POSITION_X;
    arrowPosition[2].y = ARROW_START_POSITION_Y;
    arrowPosition[2].z = ARROW_START_POSITION_Z;

    batPosition.x = BAT_START_POSITION_X;
    batPosition.y = BAT_START_POSITION_Y;
    batPosition.z = BAT_START_POSITION_Z;

    scaffoldPosition.x = SCAFFOLD_START_POSITION_X;
    scaffoldPosition.y = SCAFFOLD_START_POSITION_Y;
    scaffoldPosition.z = SCAFFOLD_START_POSITION_Z;

    jewelryPosition[0].x = JEWELRY_START_POSITION_X;
    jewelryPosition[0].y = JEWELRY_START_POSITION_Y;
    jewelryPosition[0].z = JEWELRY_START_POSITION_Z;
    jewelryPosition[1].x = JEWELRY_START_POSITION_X+100;
    jewelryPosition[1].y = JEWELRY_START_POSITION_Y;
    jewelryPosition[1].z = JEWELRY_START_POSITION_Z;
    jewelryPosition[2].x = JEWELRY_START_POSITION_X+1000;
    jewelryPosition[2].y = JEWELRY_START_POSITION_Y;
    jewelryPosition[2].z = JEWELRY_START_POSITION_Z;
    jewelryGetCount = 0;
    jewelryGetFlag = false;
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
    

    // ƒOƒ‰ƒtƒBƒbƒNƒŠƒ\[ƒX‚Ì‰Šú‰»ˆ—
    
    // ƒtƒHƒ“ƒg
    font = DX9::SpriteFont::CreateDefaultFont(DXTK->Device9);
    //”wŒi
    bgSprite            = DX9::Sprite::CreateFromFile(DXTK->Device9, L"BG/main_bg.png" );
    collapseSprite      = DX9::Sprite::CreateFromFile(DXTK->Device9, L"BG/collapse.png");
    ceilingSprite       = DX9::Sprite::CreateFromFile(DXTK->Device9, L"BG/ceiling.png" );

    //ƒvƒŒƒCƒ„[
    playerSprite        = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Player/p_run.png"    );
    playerSlidingSprite = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Player/p_sliding.png");
    playerJumpSprite    = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Player/p_jump.png"   );
    playerPauseSprite   = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Player/p_pause.png"  );

    //áŠQ•¨
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
        L"”wŒiƒ‹[ƒv‚Ì‰ñ”  %d", bgLoopNumber
    );

    DX9::SpriteBatch->DrawString(
        font.Get(),
        SimpleMath::Vector2(0.0f, 90.0f),
        DX9::Colors::RGBA(500, 0, 0, 255),
        L"•ó‚ÌŠl“¾”  %d", jewelryGetCount
    );


    //”wŒi‚Ì•`‰æ
    DX9::SpriteBatch->DrawSimple(
        bgSprite.Get(),
        bgScrollPosition);

    DX9::SpriteBatch->DrawSimple(
        collapseSprite.Get(),
        collapsePosition);

    DX9::SpriteBatch->DrawSimple(
        ceilingSprite.Get(),
        ceilingPosition);

    //ƒvƒŒƒCƒ„[‚Ì•`‰æ
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

    //áŠQ•¨‚Ì•`‰æ
    DX9::SpriteBatch->DrawSimple(
        doorSprite.Get(),
        doorPosition);

    for (int i = 0; i < ROCK_MAX; i++) {
        DX9::SpriteBatch->DrawSimple(
            rockSprite.Get(),
            rockPosition[i]);
    }
    
    for (int i = 0; i < ARROW_MAX; ++i) {
        DX9::SpriteBatch->DrawSimple(
            arrowSprite.Get(),
            arrowPosition[i]);
    }
    

    DX9::SpriteBatch->DrawSimple(
        batSprite.Get(),
        batPosition);

    DX9::SpriteBatch->DrawSimple(
        scaffoldSprite.Get(),
        scaffoldPosition);

    for (int i = 0; i < JEWELRY_MAX; ++i) {
        DX9::SpriteBatch->DrawSimple(
            jewelrySprite.Get(),
            jewelryPosition[i]);
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

void MainScene::BGUpdate(const float deltaTime) {

    bgScrollPosition.x -= BG_SCROLL_SPEED_X * deltaTime;
    if (bgScrollPosition.x <= -BG_RESET_POSITION_X) {
        bgScrollPosition.x = BG_START_POSITION_X;
        bgLoopNumber++;
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
        if (DXTK->KeyEvent->pressed.S ||
            DXTK->KeyEvent->pressed.Down ||
            DXTK->GamePadState->IsDPadDownPressed()) {
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
    doorPosition.y += DOOR_DOWN_SPEED_Y * deltaTime;
    if (doorPosition.y >= DOOR_LIMIT_POSITION_Y) {
        doorPosition.y = DOOR_LIMIT_POSITION_Y;
    }

    doorPosition.x -= DOOR_MOVE_SPEED_X * deltaTime;
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
    }

    for (int i = 0; i < ROCK_MAX; ++i) {
        if (playerState == PLAYER_NORMAL  ||
            playerState == PLAYER_JUMP) {
            if (isIntersect(
                RectWH(playerPosition.x, playerPosition.y, PLAYER_HIT_SIZE_X, PLAYER_HIT_SIZE_Y),
                RectWH(rockPosition[i].x, rockPosition[i].y, ROCK_HIT_SIZE_X, ROCK_HIT_SIZE_Y))) {
                playerState = PLAYER_DAMAGE;
            }
            else {

            }
        }
    }

    for (int i = 0; i < ROCK_MAX; ++i) {
        if (playerState == PLAYER_SLIDING) {
            if (isIntersect(
                RectWH(playerSlidingPosition.x, playerSlidingPosition.y, PLAYER_SLIDING_HIT_SIZE_X, PLAYER_SLIDING_HIT_SIZE_Y),
                RectWH(rockPosition[i].x, rockPosition[i].y, ROCK_HIT_SIZE_X, ROCK_HIT_SIZE_Y))) {
                playerState = PLAYER_DAMAGE;
            }
            else {

            }
        }
    }
}
void MainScene::ArrowUpdate(const float deltaTime) {
    for (int i = 0; i < ARROW_MAX; ++i) {
        arrowPosition[i].x -= ARROW_MOVE_SPEED_X * deltaTime;
    }

    for (int i = 0; i < ARROW_MAX; ++i) {
        if (playerState == PLAYER_NORMAL ||
            playerState == PLAYER_SLIDING||
            playerState == PLAYER_JUMP) {
            if (isIntersect(
                RectWH(playerPosition.x, playerPosition.y, PLAYER_HIT_SIZE_X, PLAYER_HIT_SIZE_Y),
                RectWH(arrowPosition[i].x, arrowPosition[i].y, ARROW_HIT_SIZE_X, ARROW_HIT_SIZE_Y))){
                playerState = PLAYER_DAMAGE;
            }
            else {

            }
        }
    }

    for (int i = 0; i < ARROW_MAX; ++i) {
        if (playerState == PLAYER_SLIDING) {
            if (isIntersect(
                RectWH(playerSlidingPosition.x, playerSlidingPosition.y, PLAYER_SLIDING_HIT_SIZE_X, PLAYER_SLIDING_HIT_SIZE_Y),
                RectWH(arrowPosition[i].x, arrowPosition[i].y, ARROW_HIT_SIZE_X, ARROW_HIT_SIZE_Y))) {
                playerState = PLAYER_DAMAGE;
            }
            else {

            }
        }
    }
}
void MainScene::BatUpdate(const float deltaTime) {
    batPosition.x -= BAT_MOVE_SPPED_X * deltaTime;
}
void MainScene::ScaffoldUpdate(const float deltaTime) {
    scaffoldPosition.x -= SCAFFOLD_MOVE_SPPED_X * deltaTime;
}
void MainScene::JewelryUpdate(const float deltaTime) {
    for (int i = 0; i < JEWELRY_MAX; ++i) {
        jewelryPosition[i].x -= JEWELRY_MOVE_SPEED_X * deltaTime;
    }

    for (int i = 0; i < JEWELRY_MAX; ++i) {
        if (playerState == PLAYER_NORMAL  ||
            playerState == PLAYER_SLIDING ||
            playerState == PLAYER_JUMP) {
            if (jewelryGetFlag == false) {
                if (isIntersect(
                    RectWH(playerPosition.x, playerPosition.y, PLAYER_HIT_SIZE_X, PLAYER_HIT_SIZE_Y),
                    RectWH(jewelryPosition[i].x, jewelryPosition[i].y, JEWELRY_HIT_SIZE_X, JEWELRY_HIT_SIZE_Y))) {
                    jewelryGetFlag = true;
                }
                else
                {

                }
            }
        }
    }

    if (jewelryGetFlag == true) {
        jewelryGetCount++;
        jewelryGetFlag = false;
    }

}

bool MainScene::isIntersect(Rect& rect1, Rect& rect2) {
    if (rect1.left > rect2.right || rect1.right  < rect2.left ||
        rect1.top  > rect2.bottom || rect1.bottom < rect2.top) {
        return false;
    }

    return true;
}