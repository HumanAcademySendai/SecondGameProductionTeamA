//
// MainScene.h
//

#pragma once

#include "Scene.h"
#include <random>

using Microsoft::WRL::ComPtr;
using std::unique_ptr;
using std::make_unique;
using namespace DirectX;

class MainScene final : public Scene {
public:
    MainScene();
    virtual ~MainScene() { Terminate(); }

    MainScene(MainScene&&) = default;
    MainScene& operator= (MainScene&&) = default;

    MainScene(MainScene const&) = delete;
    MainScene& operator= (MainScene const&) = delete;

    // These are the functions you will implement.
    void Initialize() override;
    void LoadAssets() override;

    void Terminate() override;

    void OnDeviceLost() override;
    void OnRestartSound() override;

    NextScene Update(const float deltaTime) override;
    void Render() override;

private:
    DX12::DESCRIPTORHEAP descriptorHeap;
    DX12::SPRITEBATCH    spriteBatch;
    DX12::HGPUDESCRIPTOR dx9GpuDescriptor;

    // �ϐ��̐錾

    //�t�H���g
    DX9::SPRITEFONT font;

    //�w�i
    DX9::SPRITE bgSprite;
    SimpleMath::Vector3 bgScrollPosition;
    int bgLoopNumber;

    //����
    enum { TORCH_MAX = 2 };
    DX9::SPRITE torchSprite;
    SimpleMath::Vector3 torchPosition[TORCH_MAX];
    float torchAnimeX;
    float torchAnimeY;

    //����
    DX9::SPRITE collapseFrontSprite;
    SimpleMath::Vector3 collapseFrontPosition;

    //�V��
    DX9::SPRITE ceilingSprite;
    SimpleMath::Vector3 ceilingPosition;

    //�u���b�N�A�E�g
    DX9::SPRITE blackSprite;
    SimpleMath::Vector3 blackPosition;
    int screenAlpha;

    //�v���C���[
    DX9::SPRITE playerSprite;
    DX9::SPRITE playerSlidingSprite;
    DX9::SPRITE playerJumpSprite;
    DX9::SPRITE playerPauseSprite;

    SimpleMath::Vector3 playerPosition;
    SimpleMath::Vector3 playerSlidingPosition;
    float playerDamageCount;
    float playerMoveCount;
    float playerSlidingCount;
    float gravity;
    int playerState;
    int playerPrevState;
    enum PLAYERSTATE {
        PLAYER_NORMAL,
        PLAYER_JUMP,
        PLAYER_SLIDING,
        PLAYER_DAMAGE,
        PLAYER_RIDE,
        PLAYER_MOVE,
        PLAYER_DROP,
        PLAYER_DROP_DEATH
    };
    float playerAnimeX;
    bool playerDeathFlag;

    //��Q��
    //��
    enum { DOOR_DOWN_MAX = 4 };
    DX9::SPRITE doorSprite;
    SimpleMath::Vector3 doorDownPosition[DOOR_DOWN_MAX];
    SimpleMath::Vector3 doorUpPosition;

    //��
    enum { ROCK_MAX = 5 };
    DX9::SPRITE rockSprite;
    SimpleMath::Vector3 rockPosition[ROCK_MAX];

    //��
    enum{ ARROW_MAX = 3 };
    DX9::SPRITE arrowSprite;
    SimpleMath::Vector3 arrowPosition[ARROW_MAX];

    //�R�E����
    enum { BAT_MAX = 5 };
    DX9::SPRITE batSprite;
    SimpleMath::Vector3 batPosition[BAT_MAX];
    float theta;
    float batBaseY;
    float batAnimeX;
    enum { FAKE_BAT_RIGHT_MAX = 3 };
    DX9::SPRITE fakeBatRightSprite;
    SimpleMath::Vector3 fakeBatRightPosition[FAKE_BAT_RIGHT_MAX];

    enum { FAKE_BAT_LEFT_MAX = 6 };
    DX9::SPRITE fakeBatLeftSprite;
    SimpleMath::Vector3 fakeBatLeftPosition[FAKE_BAT_LEFT_MAX];

    //����
    enum { SCAFFOLD_MAX = 2 };
    DX9::SPRITE scaffoldSprite;
    SimpleMath::Vector3 scaffoldPosition[SCAFFOLD_MAX];
    int scaffoldNumber;
    
    //��
    enum { SHORT_HOLE_MAX = 3 };
    DX9::SPRITE shortHoleSprite;
    SimpleMath::Vector3 shortHolePosition[SHORT_HOLE_MAX];

    DX9::SPRITE middleHoleSprite;
    SimpleMath::Vector3 middleHolePosition;


    //BGM
    DX9::MEDIARENDERER mediaMainbgm;

    //SE
    XAudio::SOUNDEFFECT         seCollapse;
    XAudio::SOUNDEFFECTINSTANCE seCollapseInstance;
    XAudio::SOUNDEFFECT         sePlayerDamage;
    XAudio::SOUNDEFFECT         seDoor[DOOR_DOWN_MAX];
    XAudio::SOUNDEFFECTINSTANCE seDoorInstance[DOOR_DOWN_MAX];

    //�萔
    //�w�i
    const float BG_START_POSITION_X = 0.0f;
    const float BG_START_POSITION_Y = 0.0f;
    const float BG_START_POSITION_Z = 15.0f;
    const float BG_SCROLL_SPEED_X   = -600.0f;
    const float BG_RESET_POSITION_X = -1280.0f;

    //����
    const float TORCH_START_POSITION_X_1 = 1251.0f;
    const float TORCH_START_POSITION_X_2 = 2535.0f;
    const float TORCH_START_POSITION_Y   = 195.0f;
    const float TORCH_START_POSITION_Z   = 14.0f;
    const float TORCH_RESET_POSITION_X   = 1280.0f;
    const float TORCH_SCROLL_SPEED_X     = -600.0f;
    const float TORCH_ANIME_SPED         = 15.0f;
    const float TORCH_ANIME_MAX_COUNT_X  = 10.0f;
    const float TORCH_ANIME_MAX_COUNT_Y  = 3.0f;
    const float TORCH_WIDTH              = 54.0f;
    const float TORCH_HEIGHT             = 181.0f;

    //�u���b�N�A�E�g
    const float BLACK_START_POSITION_Z = -20.0f;
    const int SCREENALPHA_COUNT = 300;
    const int SCREENALPHA_LIMIT = 255;

    //����
    const float COLLAPSE_START_POSITION_X       = -100.0f;
    const float COLLAPSE_FRONT_START_POSITION_Y = -720.0f;
    const float COLLAPSE_BACK_START_POSITION_Y  = -1440.0f;
    const float COLLAPSE_START_POSITION_Z       = 9.0f;
    const float COLLAPSE_BACK_START_POSITION_Z  = 10.0f;

    //�V��
    const float CEILING_START_POSITION_X = 0.0f;
    const float CEILING_START_POSITION_Y = 0.0f;
    const float CEILING_START_POSITION_Z = 8.0f;
    const float CEILING_SCROLL_SPEED_X   = -600.0f;
    const float CEILING_RESET_POSITION_X = -1280.0f;

    //�v���C���[
    const float PLAYER_START_POSITION_X         = 300.0f;
    const float PLAYER_START_POSITION_Y         = 540.0f;
    const float PLAYER_START_POSITION_Z         = 10.0f;
    const float PLAYER_SLIDING_START_POSITION_X = 300.0f; 
    const float PLAYER_SLIDING_START_POSITION_Y = 608.0f;
    const float PLAYER_DAMAGE_LIMIT_COUNT       = 1.0f;
    const float PLAYER_MOVE_START_COUNT         = 60.0f;
    const float PLAYER_MOVE_SPEED               = 600.0f;
    const float PLAYER_SLIDING_START_COUNT      = 0.7f;
    const float PLAYER_HIT_SIZE_X               = 100.0f;
    const float PLAYER_HIT_SIZE_Y               = 132.0f;
    const float PLAYER_SLIDING_HIT_SIZE_X       = 170.0f;
    const float PLAYER_SLIDING_HIT_SIZE_Y       = 76.0f;
    const float PLAYER_DROP_SPEED_Y             = 1000.0f;
    const float PLAYER_LIMIT_POSITION_X         = 1300.0f;
    const float PLAYER_ANIME_SPEED_X            = 5.5f;
    const float PLAYER_ANIME_MAX_COUNT          = 4.0f;
    const float PLAYER_WIDTH                    = 116.0f;
    const float PLAYER_HEIGHT                   = 132.0f;
    const float PLAYER_LEG_POSITION             = 132.0f;
    const float PLAYER_DAMAGE_POSITION          = 150.0f;

    //�d��
    const float GRAVITY_POWER_ADD  = -2000.0f;
    const float GRAVITY_POWER_TAKE = 800.0f;

    //��
    const float DOOR_DOWN_START_POSITION_X_1    = 2000.0f;
    const float DOOR_DOWN_START_POSITION_X_2    = 6000.0f;
    const float DOOR_DOWN_START_POSITION_X_3    = 6700.0f;
    const float DOOR_DOWN_START_POSITION_X_4    = 7940.0f;
    const float DOOR_DOWN_START_POSITION_Y      = -400.0f;
    const float DOOR_START_POSITION_Z           = 10.0f;
    const float DOOR_MOVE_SPEED_X               = -600.0f;
    const float DOOR_DOWN_SPEED_Y               = 300.0f;
    const float DOOR_SLOW_DOWN_SPEED_Y          = 80.0f;
    const float DOOR_SLOW_DOWN_START_POSITOIN_Y = -300;
    const float DOOR_DOWN_START_POSITOIN_X      = 1280.0f;
    const float DOOR_DOWN_LIMIT_POSITION_Y      = 0.0f;
    const float DOOR_HIT_SIZE_X                 = 10.0f;
    const float DOOR_HIT_SIZE_Y                 = 719.0f;
    const float DOOR_SE_PLAY_POSITION_X         = 1400;

    const float DOOR_UP_START_POSITION_X = 1300.0f;
    const float DOOR_UP_START_POSITION_Y = 0.0f;
    const float DOOR_UP_SPEED_Y          = -200.0f;
    const float DOOR_UP_LIMIT_POSITION_Y = -720.0f;

    //��
    const float ROCK_START_POSITION_X_1 = 3000.0f;
    const float ROCK_START_POSITION_X_2 = 4000.0f;
    const float ROCK_START_POSITION_X_3 = 13500.0f;
    const float ROCK_START_POSITION_X_4 = 14000.0f;
    const float ROCK_START_POSITION_X_5 = 26500.0f;
    const float ROCK_START_POSITION_Y   = -82.0f;
    const float ROCK_START_POSITION_Z   = 10.0f;
    const float ROCK_MOVE_SPEED_X       = 600.0f;
    const float ROCK_MOVE_SPEED_Y       = 1400.0f;
    const float ROCK_DOWN_POSITION_X    = 1000.0f;
    const float ROCK_LIMIT_POSITION_Y   = 622.0f;
    const float ROCK_HIT_SIZE_X         = 104.0f;
    const float ROCK_HIT_SIZE_Y         = 82.0f;

    //��
    const float ARROW_START_POSITION_X_1 = 11800.0f;
    const float ARROW_START_POSITION_X_2 = 18000.0f;
    const float ARROW_START_POSITION_X_3 = 18600.0f;
    const float ARROW_START_POSITION_Y   = 600.0f;
    const float ARROW_START_POSITION_Z   = 10.0f;
    const float ARROW_MOVE_SPEED_X       = 800.0f;
    const float ARROW_HIT_SIZE_X         = 80.0f;
    const float ARROW_HIT_SIZE_Y         = 19.0f;

    //�R�E����
    const float BAT_START_POSITION_X_1 = 12500.0f;
    const float BAT_START_POSITION_X_2 = 12550.0f;
    const float BAT_START_POSITION_X_3 = 12600.0f;
    const float BAT_START_POSITION_X_4 = 22500.0f;
    const float BAT_START_POSITION_X_5 = 23600.0f;
    const float BAT_START_POSITION_Y   = 450.0f;
    const float BAT_START_POSITION_Z   = 10.0f;
    const float BAT_MOVE_SPPED_X       = -600.0f;
    const float BAT_MOVE_SPPED_Y       = 5.0f;
    const float BAT_MOVE_RANGE_Y       = 15.0f;
    const float BAT_HIT_SIZE_X         = 109.0f;
    const float BAT_HIT_SIZE_Y         = 38.0f;
    const float BAT_HIT_POSITION_Y     = 115.0f;
    const float BAT_ANIME_SPEED_X      = 15.0f;
    const float BAT_ANIME_MAX_COUNT    = 4.0f;
    const float BAT_WIDTH              = 123.0f;
    const float BAT_HEIGHT             = 237.0f;

    //���o�R�E����(�E����)
    const float FAKE_BAT_RIGHT_START_POSITION_X_1 = 300.0f;
    const float FAKE_BAT_RIGHT_START_POSITION_X_2 = 400.0f;
    const float FAKE_BAT_RIGHT_START_POSITION_X_3 = 500.0f;
    const float FAKE_BAT_START_POSITION_Y = 200.0f;
    const float FAKE_BAT_START_POSITION_Z = 10.0f;
    const float FAKE_BAT_RIGHT_MOVE_SPEED_X = 500.0f;

    //���o�R�E����(������)
    const float FAKE_BAT_LEFT_START_POSITION_X_1 = 18500.0f;
    const float FAKE_BAT_LEFT_START_POSITION_X_2 = 18550.0f;
    const float FAKE_BAT_LEFT_START_POSITION_X_3 = 23550.0f;
    const float FAKE_BAT_LEFT_START_POSITION_X_4 = 23530.0f;
    const float FAKE_BAT_LEFT_START_POSITION_X_5 = 23560.0f;
    const float FAKE_BAT_LEFT_START_POSITION_X_6 = 23580.0f;

    //����
    const float SCAFFOLD_START_POSITION_X       = 1300.0f;
    const float SCAFFOLD_START_POSITION_Y       = 480.0f;
    const float SCAFFOLD_START_POSITION_Z       = 10.0f;
    const float SCAFFOLD_MOVE_SPPED_X           = 600.0f;
    const float SCAFFOLD_HIT_SIZE_X             = 250.0f;
    const float SCAFFOLD_HIT_SIZE_Y             = 50.0f;
    const float SCAFFOLD_HIT_DEATH_SIZE_X = 250.0f;
    const float SCAFFOLD_HIT_DEATH_SIZE_Y = 58.5f;
    const float SCAFFOLD_HIT_POSITION_Y   = 58.5f;

    //��
    const float SHORT_HOLE_START_POSITION_X_1 = 5800.0f;
    const float SHORT_HOLE_START_POSITION_X_2 = 21000.0f;
    const float SHORT_HOLE_START_POSITION_X_3 = 24800.0f;
    const float HOLE_START_POSITION_Y = 614.0f;
    const float HOLE_START_POSITION_Z = 11.0f;
    const float HOLE_MOVE_SPPED_X = -600.0f;
    const float SHORT_HOLE_HIT_SIZE_X = 200.0f;
    const float HOLE_HIT_SIZE_Y = 105.0f;
    const float SHORT_HOLE_HIT_POSITION_X = 60.0f;

    const float MIDDLE_HOLE_START_POSITION_X = 1000.0f;
    const float MIDDLE_HOLE_HIT_SIZE_X       = 10500.0f;

    bool isIntersect(Rect& rect1, Rect& rect2);

    //�֐�
private:
    void BGUpdate(const float deltaTime);

    void PlayerUpdate         (const float deltaTime);
    void PlayerSlidingUpdate  (const float deltaTime);
    void PlayerJumpUpdate     (const float deltaTime);
    void PlayerMoveUpdate     (const float deltaTime);
    void PlayerDamageUpdate   (const float deltaTime);
    void PlayerRideUpdate     (const float deltaTime);
    void PlayerDropUpdate     (const float deltaTime);
    void PlayerDropDeathUpdate(const float deltaTime);

    void ObstacleUpdate(const float deltaTime);
    void DoorUpdate    (const float deltaTime);
    void RockUpdate    (const float deltaTime);
    void ArrowUpdate   (const float deltaTime);
    void BatUpdate     (const float deltaTime);
    void FakeBatUpdate (const float deltaTime);
    void ScaffoldUpdate(const float deltaTime);
    void HoleUpdate    (const float deltaTime);

    void AnimationUpdate(const float deltaTime);

    NextScene SeneChangeUpdate(const float deltaTime);

};