//
// MainScene2.cpp
//

#include "Base/pch.h"
#include "Base/dxtk.h"
#include "SceneFactory.h"
#include "DontDestroyOnLoad.h"

// Initialize member variables.
MainScene2::MainScene2() : dx9GpuDescriptor{}
{

}

// Initialize a variable and audio resources.
void MainScene2::Initialize()
{
    //�w�i�X�N���[���̏�����
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

    blackPosition.x = BG_START_POSITION_X;
    blackPosition.y = BG_START_POSITION_Y;
    blackPosition.z = BLACK_START_POSITION_Z;
    screenAlpha = 0;

    //�v���C���[�̏�����
    playerState = PLAYER_NORMAL;
    playerPosition.x = PLAYER_START_POSITION_X;
    playerPosition.y = PLAYER_START_POSITION_Y;
    playerPosition.z = PLAYER_START_POSITION_Z;
    playerSlidingPosition.x = PLAYER_SLIDING_START_POSITION_X;
    playerSlidingPosition.y = PLAYER_SLIDING_START_POSITION_Y;
    playerSlidingPosition.z = PLAYER_START_POSITION_Z;
    playerSlidingCount = PLAYER_SLIDING_START_COUNT;
    playerDamageCount = 0;
    playerMoveCount = PLAYER_MOVE_START_COUNT;
    gravity = 0;
    playerAnimeX = 0;


    //��Q���̏�����
    //��
    doorPosition[0].x = DOOR_START_POSITION_X_1;
    doorPosition[0].y = -DOOR_START_POSITION_Y;
    doorPosition[0].z = DOOR_START_POSITION_Z;
    doorPosition[1].x = DOOR_START_POSITION_X_2;
    doorPosition[1].y = -DOOR_START_POSITION_Y;
    doorPosition[1].z = DOOR_START_POSITION_Z;
    doorPosition[2].x = DOOR_START_POSITION_X_3;
    doorPosition[2].y = -DOOR_START_POSITION_Y;
    doorPosition[2].z = DOOR_START_POSITION_Z;
    doorPosition[3].x = DOOR_START_POSITION_X_4;
    doorPosition[3].y = -DOOR_START_POSITION_Y;
    doorPosition[3].z = DOOR_START_POSITION_Z;
    doorPosition[4].x = DOOR_START_POSITION_X_5;
    doorPosition[4].y = -DOOR_START_POSITION_Y;
    doorPosition[4].z = DOOR_START_POSITION_Z;
    doorPosition[5].x = DOOR_START_POSITION_X_6;
    doorPosition[5].y = -DOOR_START_POSITION_Y;
    doorPosition[5].z = DOOR_START_POSITION_Z;

    //��
    rockPosition[0].x = ROCK_START_POSITION_X_1;
    rockPosition[0].y = -ROCK_START_POSITION_Y;
    rockPosition[0].z = ROCK_START_POSITION_Z;
    rockPosition[1].x = ROCK_START_POSITION_X_2;
    rockPosition[1].y = -ROCK_START_POSITION_Y;
    rockPosition[1].z = ROCK_START_POSITION_Z;
    rockPosition[2].x = ROCK_START_POSITION_X_2;
    rockPosition[2].y = -ROCK_START_POSITION_Y;
    rockPosition[2].z = ROCK_START_POSITION_Z;
    rockPosition[3].x = ROCK_START_POSITION_X_3;
    rockPosition[3].y = -ROCK_START_POSITION_Y;
    rockPosition[3].z = ROCK_START_POSITION_Z;

    //��
    arrowPosition[0].x = ARROW_START_POSITION_X_1;
    arrowPosition[0].y = ARROW_START_POSITION_Y;
    arrowPosition[0].z = ARROW_START_POSITION_Z;
    arrowPosition[1].x = ARROW_START_POSITION_X_2;
    arrowPosition[1].y = ARROW_START_POSITION_Y;
    arrowPosition[1].z = ARROW_START_POSITION_Z;
    arrowPosition[2].x = ARROW_START_POSITION_X_3;
    arrowPosition[2].y = ARROW_START_POSITION_Y;
    arrowPosition[2].z = ARROW_START_POSITION_Z;

    //�R�E����
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

    //����
    scaffoldPosition.x = SCAFFOLD_START_POSITION_X;
    scaffoldPosition.y = SCAFFOLD_START_POSITION_Y;
    scaffoldPosition.z = SCAFFOLD_START_POSITION_Z;

    scaffoldDeathPosition.x = SCAFFOLD_DEATH_START_POSITION_X;
    scaffoldDeathPosition.y = SCAFFOLD_DEATH_START_POSITION_Y;
    scaffoldDeathPosition.z = SCAFFOLD_DEATH_START_POSITION_Z;

    frontChainPosition.x = SCAFFOLD_START_POSITION_X;
    frontChainPosition.y = 0;
    frontChainPosition.z = SCAFFOLD_START_POSITION_Z;

    //��
    jewelryPosition[0].x = JEWELRY_START_POSITION_X_1;
    jewelryPosition[0].y = JEWELRY_START_POSITION_Y;
    jewelryPosition[0].z = JEWELRY_START_POSITION_Z;
    jewelryPosition[1].x = JEWELRY_START_POSITION_X_2;
    jewelryPosition[1].y = JEWELRY_START_POSITION_Y;
    jewelryPosition[1].z = JEWELRY_START_POSITION_Z;
    jewelryPosition[2].x = JEWELRY_START_POSITION_X_3;
    jewelryPosition[2].y = JEWELRY_START_POSITION_Y_3;
    jewelryPosition[2].z = JEWELRY_START_POSITION_Z;
    jewelryGetFlag[0]    = false;
    jewelryGetFlag[1]    = false;
    jewelryGetFlag[2]    = false;
    DontDestroy->jewelryCount = 0;

    //SE
    seCollapse     = XAudio::CreateSoundEffect(DXTK->AudioEngine, L"SE/collapse_se.wav");
    seCollapseInstance     = seCollapse->CreateInstance();
    seCollapseInstance->Play(true);
    seJewelry      = XAudio::CreateSoundEffect(DXTK->AudioEngine, L"SE/jewelry_se.wav" );
    sePlayerDamage = XAudio::CreateSoundEffect(DXTK->AudioEngine, L"SE/damage_se.wav"  );
    for (int i = 0; i < DOOR_MAX; ++i) {
        seDoor[i] = XAudio::CreateSoundEffect(DXTK->AudioEngine, L"SE/door_se.wav");
        seDoorInstance[i] = seDoor[i]->CreateInstance();
    }

}

// Allocate all memory the Direct3D and Direct2D resources.
void MainScene2::LoadAssets()
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
    

    // �O���t�B�b�N���\�[�X�̏���������
    
    // �t�H���g
    font = DX9::SpriteFont::CreateDefaultFont(DXTK->Device9);
    //�w�i
    bgSprite       = DX9::Sprite::CreateFromFile(DXTK->Device9, L"BG/main_bg.png" );
    collapseSprite = DX9::Sprite::CreateFromFile(DXTK->Device9, L"BG/collapse.png");
    ceilingSprite  = DX9::Sprite::CreateFromFile(DXTK->Device9, L"BG/ceiling.png" );
    blackSprite = DX9::Sprite::CreateFromFile(DXTK->Device9, L"BG/Black.png");

    //�v���C���[
    playerSprite        = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Player/p_run.png"    );
    playerSlidingSprite = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Player/p_sliding.png");
    playerJumpSprite    = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Player/p_jump.png"   );
    playerPauseSprite   = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Player/p_pause.png"  );

    //��Q��
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
void MainScene2::Terminate()
{
    DXTK->ResetAudioEngine();
    DXTK->WaitForGpu();

    // TODO: Add your Termination logic here.

}

// Direct3D resource cleanup.
void MainScene2::OnDeviceLost()
{

}

// Restart any looped sounds here
void MainScene2::OnRestartSound()
{
    if (seCollapseInstance)
        seCollapseInstance->Play(true);

    for (int i = 0; i < DOOR_MAX; ++i) {
        if (seDoorInstance[i])
            seDoorInstance[i]->Play(true);
    }
}

// Updates the scene.
NextScene MainScene2::Update(const float deltaTime)
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
void MainScene2::Render()
{
    // TODO: Add your rendering code here.
    DXTK->Direct3D9->Clear(DX9::Colors::RGBA(0, 0, 0, 255));

    DXTK->Direct3D9->BeginScene();

    //�����蔻��̎��o��

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


    //�w�i�̕`��
    DX9::SpriteBatch->DrawSimple(
        bgSprite.Get(),
        bgScrollPosition);

    //�u���b�N�A�E�g
    DX9::SpriteBatch->DrawSimple(
        blackSprite.Get(),
        SimpleMath::Vector3(blackPosition),
        nullptr,
        DX9::Colors::Alpha(screenAlpha));

    //����̕`��
    DX9::SpriteBatch->DrawSimple(
        collapseSprite.Get(),
        collapsePosition);

    //�V��̕`��
    DX9::SpriteBatch->DrawSimple(
        ceilingSprite.Get(),
        ceilingPosition);

    //�v���C���[�̕`��
    if (playerState == PLAYER_NORMAL || playerState == PLAYER_MOVE || playerState == PLAYER_RIDE) {
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

    //��Q���̕`��
    for (int i = 0; i < DOOR_MAX; ++i) {
        DX9::SpriteBatch->DrawSimple(
            doorSprite.Get(),
            doorPosition[i]);
    }
    
    //��̕`��
    for (int i = 0; i < ROCK_MAX; i++) {
        DX9::SpriteBatch->DrawSimple(
            rockSprite.Get(),
            rockPosition[i]);
    }
    
    //��̕`��
    for (int i = 0; i < ARROW_MAX; ++i) {
        DX9::SpriteBatch->DrawSimple(
            arrowSprite.Get(),
            arrowPosition[i]);
    }
    
    //�R�E�����̕`��
    for (int i = 0; i < BAT_MAX; ++i) {
        DX9::SpriteBatch->DrawSimple(
            batSprite.Get(),
            batPosition[i],
            RectWH((int)batAnimeX * BAT_WIDTH, 0, BAT_WIDTH, BAT_HEIGHT));
    }
    
    //����̕`��
    DX9::SpriteBatch->DrawSimple(
        scaffoldSprite.Get(),
        scaffoldPosition);

    DX9::SpriteBatch->DrawSimple(
        frontChainSprite.Get(),
        frontChainPosition);


    //����̓����蔻��̕`��
    DX9::SpriteBatch->DrawSimple(
        scaffoldDeathSprite.Get(),
        scaffoldDeathPosition);

    //��̕`��
    for (int i = 0; i < JEWELRY_MAX; ++i) {
        if (jewelryGetFlag[i] == false) {
            DX9::SpriteBatch->DrawSimple(
                jewelrySprite.Get(),
                jewelryPosition[i]);
        }
        else
        {

        }
    }


    //�t�H���g
    DX9::SpriteBatch->DrawString(
        font.Get(),
        SimpleMath::Vector2(0.0f, 0.0f),
        DX9::Colors::RGBA(500, 0, 0, 255),
        L"�w�i���[�v�̉�  %d", bgLoopNumber
    );

    DX9::SpriteBatch->DrawString(
        font.Get(),
        SimpleMath::Vector2(0.0f, 90.0f),
        DX9::Colors::RGBA(500, 0, 0, 255),
        L"��̊l����  %d", jewelryGetFlag[0]
    );

    DX9::SpriteBatch->DrawString(
        font.Get(),
        SimpleMath::Vector2(0.0f, 120.0f),
        DX9::Colors::RGBA(500, 0, 0, 255),
        L"��̊l����  %d", jewelryGetFlag[1]
    );

    DX9::SpriteBatch->DrawString(
        font.Get(),
        SimpleMath::Vector2(0.0f, 150.0f),
        DX9::Colors::RGBA(500, 0, 0, 255),
        L"��̊l����  %d", jewelryGetFlag[2]
    );

    DX9::SpriteBatch->DrawString(
        font.Get(),
        SimpleMath::Vector2(0.0f, 30.0f),
        DX9::Colors::RGBA(500, 0, 0, 255),
        L" P�ړ� %f", playerMoveCount
    );

    DX9::SpriteBatch->DrawString(
        font.Get(),
        SimpleMath::Vector2(1000.0f, 30.0f),
        DX9::Colors::RGBA(500, 0, 0, 255),
        L" ��̊l���� %d", DontDestroy->jewelryCount
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

void MainScene2::BGUpdate(const float deltaTime) {
    bgScrollPosition.x -= BG_SCROLL_SPEED_X * deltaTime;
    if (bgScrollPosition.x <= -BG_RESET_POSITION_X) {
        bgScrollPosition.x = BG_START_POSITION_X;
        bgLoopNumber++;
    }
}

void MainScene2::PlayerUpdate(const float deltaTime) {
    playerPrevState = playerState;
    PlayerSlidingUpdate(deltaTime);
    PlayerJumpUpdate   (deltaTime);
    PlayerDamageUpdate (deltaTime);
    PlayerMoveUpdate   (deltaTime);
    PlayerRideUpdate   (deltaTime);
}

void MainScene2::PlayerSlidingUpdate(const float deltaTime) {
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
void MainScene2::PlayerJumpUpdate(const float deltaTime) {

    if (playerState == PLAYER_NORMAL && playerPosition.y >= PLAYER_START_POSITION_Y || playerState == PLAYER_RIDE) {
        if (DXTK->KeyEvent->pressed.Space ||
            DXTK->GamePadEvent->a == GamePad::ButtonStateTracker::PRESSED) {
            playerState = PLAYER_JUMP;
            gravity = GRAVITY_POWER_TAKE;
        }
    }

    if (playerState == PLAYER_JUMP) {
        playerPosition.y -= gravity * deltaTime;
        gravity -= GRAVITY_POWER_ADD * deltaTime;
    }

    if (playerState == PLAYER_JUMP) {
        if (playerPosition.y > PLAYER_START_POSITION_Y) {
            playerPosition.y = PLAYER_START_POSITION_Y;
            playerState = PLAYER_NORMAL;
        }
    }
}
void MainScene2::PlayerDamageUpdate(const float deltaTime) {
    if (playerState == PLAYER_DAMAGE) {
        playerDamageCount += deltaTime;
        if (playerDamageCount >= PLAYER_DAMAGE_LIMIT_COUNT) {
            playerState = PLAYER_NORMAL;
            playerDamageCount = 0;
        }
    }
}
void MainScene2::PlayerMoveUpdate(const float deltaTime) {
    playerMoveCount -= deltaTime;
    if (playerMoveCount <= 0 && playerState == PLAYER_NORMAL) {
        playerState = PLAYER_MOVE;
    }

    if (playerState == PLAYER_MOVE) {
        playerPosition.x += PLAYER_MOVE_SPEED * deltaTime;
    }

    if (playerState == PLAYER_DAMAGE) {
        screenAlpha += SCREENALPHA_COUNT * deltaTime;
        playerPosition.x -= PLAYER_MOVE_SPEED * deltaTime;
        playerPosition.y += PLAYER_MOVE_SPEED * deltaTime;
        if (playerPosition.y >= PLAYER_START_POSITION_Y) {
            playerPosition.y = PLAYER_START_POSITION_Y;
        }
    }
}
void MainScene2::PlayerRideUpdate(const float deltaTime) {

    if (playerState == PLAYER_JUMP) {
        if (isIntersect(
            RectWH(playerPosition.x, playerPosition.y, PLAYER_HIT_SIZE_X, PLAYER_HIT_SIZE_Y),
            RectWH(scaffoldPosition.x, scaffoldPosition.y, SCAFFOLD_SIZE_X, SCAFFOLD_SIZE_Y))) {
            playerState = PLAYER_RIDE;
        }
        else {

        }
    }

    if (playerState == PLAYER_RIDE) {
        if (playerPosition.y >= SCAFFOLD_START_POSITION_Y) {
            playerPosition.y = SCAFFOLD_START_POSITION_Y;
        }

        if (isIntersect(
            RectWH(playerPosition.x, playerPosition.y, PLAYER_HIT_SIZE_X, PLAYER_HIT_SIZE_Y),
            RectWH(scaffoldPosition.x, scaffoldPosition.y, SCAFFOLD_SIZE_X, SCAFFOLD_SIZE_Y))) {
        }
        else {
            playerPosition.y += PLAYER_DROP_SPEED_Y * deltaTime;
        }
    }
}
void MainScene2::ObstacleUpdate(const float deltaTime) {
    DoorUpdate    (deltaTime);
    RockUpdate    (deltaTime);
    ArrowUpdate   (deltaTime);
    BatUpdate     (deltaTime);
    ScaffoldUpdate(deltaTime);
    JewelryUpdate (deltaTime);
}

void MainScene2::DoorUpdate(const float deltaTime) {
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
            else {

            }
        }

        if (playerPrevState == PLAYER_SLIDING) {
            if (isIntersect(
                RectWH(playerSlidingPosition.x, playerSlidingPosition.y, PLAYER_SLIDING_HIT_SIZE_X, PLAYER_SLIDING_HIT_SIZE_Y),
                RectWH(doorPosition[i].x, doorPosition[i].y, DOOR_HIT_SIZE_X, DOOR_HIT_SIZE_Y))) {
                playerState = PLAYER_DAMAGE;
            }
            else {

            }
        }
    }
}
void MainScene2::RockUpdate(const float deltaTime) {
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
            else {

            }
        }

        if (playerPrevState == PLAYER_SLIDING) {
            if (isIntersect(
                RectWH(playerSlidingPosition.x, playerSlidingPosition.y, PLAYER_SLIDING_HIT_SIZE_X, PLAYER_SLIDING_HIT_SIZE_Y),
                RectWH(rockPosition[i].x, rockPosition[i].y, ROCK_HIT_SIZE_X, ROCK_HIT_SIZE_Y))) {
                playerState = PLAYER_DAMAGE;
                sePlayerDamage->Play();
            }
            else {

            }
        }
    }
}
void MainScene2::ArrowUpdate(const float deltaTime) {
    for (int i = 0; i < ARROW_MAX; ++i) {
        arrowPosition[i].x -= ARROW_MOVE_SPEED_X * deltaTime;

        if (playerPrevState == PLAYER_NORMAL  ||
            playerPrevState == PLAYER_JUMP) {
            if (isIntersect(
                RectWH(playerPosition.x, playerPosition.y, PLAYER_HIT_SIZE_X, PLAYER_HIT_SIZE_Y),
                RectWH(arrowPosition[i].x, arrowPosition[i].y, ARROW_HIT_SIZE_X, ARROW_HIT_SIZE_Y))) {
                playerState = PLAYER_DAMAGE;
            }
            else {

            }
        }

        if (playerPrevState == PLAYER_SLIDING) {
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
void MainScene2::BatUpdate(const float deltaTime) {
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
            else {

            }
        }

        if (playerPrevState == PLAYER_SLIDING) {
            if (isIntersect(
                RectWH(playerSlidingPosition.x, playerSlidingPosition.y, PLAYER_SLIDING_HIT_SIZE_X, PLAYER_SLIDING_HIT_SIZE_Y),
                RectWH(batDeathPosition[i].x, batDeathPosition[i].y, BAT_HIT_SIZE_X, BAT_HIT_SIZE_Y))) {
                playerState = PLAYER_DAMAGE;
            }
            else {

            }
        }
    }
}
void MainScene2::ScaffoldUpdate(const float deltaTime) {
    scaffoldPosition.x      -= SCAFFOLD_MOVE_SPPED_X * deltaTime;
    scaffoldDeathPosition.x -= SCAFFOLD_MOVE_SPPED_X * deltaTime;

    if (playerPrevState == PLAYER_NORMAL ||
        playerPrevState == PLAYER_JUMP) {
        if (isIntersect(
            RectWH(playerPosition.x, playerPosition.y, PLAYER_HIT_SIZE_X, PLAYER_HIT_SIZE_Y),
            RectWH(scaffoldDeathPosition.x, scaffoldDeathPosition.y, SCAFFOLD_DEATH_SIZE_X, SCAFFOLD_DEATH_SIZE_Y))) {
            playerState = PLAYER_DAMAGE;
        }
        else
        {

        }
    }

    if (playerPrevState == PLAYER_SLIDING) {
        if (isIntersect(
            RectWH(playerSlidingPosition.x, playerSlidingPosition.y, PLAYER_SLIDING_HIT_SIZE_X, PLAYER_SLIDING_HIT_SIZE_Y),
            RectWH(scaffoldDeathPosition.x, scaffoldDeathPosition.y, SCAFFOLD_DEATH_SIZE_X, SCAFFOLD_DEATH_SIZE_Y))) {
            playerState = PLAYER_DAMAGE;
        }
        else {

        }
    }

}
void MainScene2::JewelryUpdate(const float deltaTime) {
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
                else
                {

                }
            }
        }
    }
}

NextScene MainScene2::SeneChangeUpdate(const float deltaTime) {
    if (screenAlpha >= SCREENALPHA_LIMIT) {
        return NextScene::GameOverScene;
        screenAlpha = SCREENALPHA_LIMIT;
    }

    if (playerPosition.x >= PLAYER_LIMIT_POSITION_X) {
        return NextScene::ClearScene;
    }

    return NextScene::Continue;
}

void MainScene2::AnimationUpdate(const float deltaTime) {
    batAnimeX += BAT_ANIME_SPEED_X * deltaTime;
    if (batAnimeX > BAT_ANIME_MAX_COUNT) {
        batAnimeX = 0.0f;
    }

    playerAnimeX += PLAYER_ANIME_SPEED_X * deltaTime;
    if (playerAnimeX > PLAYER_ANIME_MAX_COUNT) {
        playerAnimeX = 0.0f;
    }
}

bool MainScene2::isIntersect(Rect& rect1, Rect& rect2) {
    if (rect1.left > rect2.right || rect1.right  < rect2.left ||
        rect1.top  > rect2.bottom || rect1.bottom < rect2.top) {
        return false;
    }

    return true;
}