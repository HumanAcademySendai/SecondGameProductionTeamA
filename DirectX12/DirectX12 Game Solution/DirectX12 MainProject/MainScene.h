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

    // 変数の宣言

    //フォント
    DX9::SPRITEFONT font;

    //背景
    DX9::SPRITE bgSprite;
    SimpleMath::Vector3 bgScrollPosition;
    DX9::SPRITE collapseSprite;
    SimpleMath::Vector3 collapsePosition;
    DX9::SPRITE ceilingSprite;
    SimpleMath::Vector3 ceilingPosition;
    int bgLoopNumber;
    DX9::SPRITE blackSprite;
    SimpleMath::Vector3 blackPosition;
    int screenAlpha;

    //プレイヤー
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
        PLAYER_MOVE
    };
    float playerAnimeX;


    //障害物
    //扉
    enum { DOOR_MAX = 6 };
    DX9::SPRITE doorSprite;
    SimpleMath::Vector3 doorPosition[DOOR_MAX];

    //岩
    enum { ROCK_MAX = 4 };
    DX9::SPRITE rockSprite;
    SimpleMath::Vector3 rockPosition[ROCK_MAX];

    //矢
    enum{ ARROW_MAX = 3 };
    DX9::SPRITE arrowSprite;
    SimpleMath::Vector3 arrowPosition[ARROW_MAX];

    //コウモリ
    enum { BAT_MAX = 4 };
    DX9::SPRITE batSprite;
    SimpleMath::Vector3 batPosition[BAT_MAX];
    float theta;
    float batBaseY;
    float batDeathBaseY;
    float batAnimeX;
    DX9::SPRITE batDeathSprite;
    SimpleMath::Vector3 batDeathPosition[BAT_MAX];

    //足場
    DX9::SPRITE scaffoldSprite;
    SimpleMath::Vector3 scaffoldPosition;

    DX9::SPRITE scaffoldDeathSprite;
    SimpleMath::Vector3 scaffoldDeathPosition;

    DX9::SPRITE frontChainSprite;
    SimpleMath::Vector3 frontChainPosition;

    DX9::SPRITE backChainSprite;
    SimpleMath::Vector3 backChainPosition;

    //宝
    enum { JEWELRY_MAX = 3 };
    DX9::SPRITE jewelrySprite;
    SimpleMath::Vector3 jewelryPosition[JEWELRY_MAX];
    bool jewelryGetFlag[JEWELRY_MAX];
    

    //BGM
    XAudio::SOUNDEFFECT         bgmMain;
    XAudio::SOUNDEFFECTINSTANCE bgmInstance;

    //SE
    XAudio::SOUNDEFFECT         seCollapse;
    XAudio::SOUNDEFFECTINSTANCE seCollapseInstance;
    XAudio::SOUNDEFFECT         seArrow;
    XAudio::SOUNDEFFECT         seJewelry;
    XAudio::SOUNDEFFECT         sePlayerDamage;
    XAudio::SOUNDEFFECT         seRock;
    XAudio::SOUNDEFFECT         seDoor[DOOR_MAX];
    XAudio::SOUNDEFFECTINSTANCE seDoorInstance[DOOR_MAX];

    //定数
    //背景
    const float BG_START_POSITION_X = 0.0f;
    const float BG_START_POSITION_Y = 0.0f;
    const float BG_START_POSITION_Z = 15.0f;
    const float BLACK_START_POSITION_Z = -20.0f;
    const float BG_SCROLL_SPEED_X   = 600.0f;
    const float BG_RESET_POSITION_X = 1280.0f;

    //ブラックアウト
    const int SCREENALPHA_COUNT = 300;
    const int SCREENALPHA_LIMIT = 255;

    //崩壊
    const float COLLAPSE_START_POSITION_X = 0.0f;
    const float COLLAPSE_START_POSITION_Y = 0.0f;
    const float COLLAPSE_START_POSITION_Z = 9.0f;

    //天井
    const float CEILING_START_POSITION_X = 0.0f;
    const float CEILING_START_POSITION_Y = 0.0f;
    const float CEILING_START_POSITION_Z = 8.0f;

    //プレイヤー
    const float PLAYER_START_POSITION_X         = 300.0f;
    const float PLAYER_START_POSITION_Y         = 500.0f;
    const float PLAYER_START_POSITION_Z         = 10.0f;
    const float PLAYER_SLIDING_START_POSITION_X = 300.0f; 
    const float PLAYER_SLIDING_START_POSITION_Y = 572.0f;
    const float PLAYER_DAMAGE_LIMIT_COUNT       = 3.0f;
    const float PLAYER_MOVE_START_COUNT         = 25.0f;
    const float PLAYER_MOVE_SPEED               = 600.0f;
    const float PLAYER_SLIDING_START_COUNT      = 1.0f;
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

    //重力
    const float GRAVITY_POWER_ADD  = 2000.0f;
    const float GRAVITY_POWER_TAKE = 800.0f;

    //扉
    const float DOOR_START_POSITION_X_1    = 3440.0f;
    const float DOOR_START_POSITION_X_2    = 6000.0f;
    const float DOOR_START_POSITION_X_3    = 6700.0f;
    const float DOOR_START_POSITION_X_4    = 7940.0f;
    const float DOOR_START_POSITION_X_5    = 10440.0f;
    const float DOOR_START_POSITION_X_6    = 11440.0f;
    const float DOOR_START_POSITION_Y      = 500.0f;
    const float DOOR_START_POSITION_Z      = 10.0f;
    const float DOOR_MOVE_SPEED_X          = 600.0f;
    const float DOOR_DOWN_SPEED_Y          = 200.0f;
    const float DOOR_DOWN_START_POSITOIN_X = 1280.0f;
    const float DOOR_LIMIT_POSITION_Y      = 0.0f;
    const float DOOR_HIT_SIZE_X            = 10.0f;
    const float DOOR_HIT_SIZE_Y            = 719.0f;
    const float DOOR_SE_PLAY_POSITION_X    = 1400;

    //岩
    const float ROCK_START_POSITION_X_1 = 2000.0f;
    const float ROCK_START_POSITION_X_2 = 5440.0f;
    const float ROCK_START_POSITION_X_3 = 7440.0f;
    const float ROCK_START_POSITION_X_4 = 12440.0f;
    const float ROCK_START_POSITION_Y   = 82.0f;
    const float ROCK_START_POSITION_Z   = 10.0f;
    const float ROCK_MOVE_SPEED_X       = 600.0f;
    const float ROCK_MOVE_SPEED_Y       = 1400.0f;
    const float ROCK_DOWN_POSITION_X    = 1000.0f;
    const float ROCK_LIMIT_POSITION_Y   = 582.0f;
    const float ROCK_HIT_SIZE_X         = 104.0f;
    const float ROCK_HIT_SIZE_Y         = 82.0f;
    const float SE_ROCK_PLAY_POSITION_Y = 570.0f;

    //矢
    const float ARROW_START_POSITION_X_1 = 11800.0f;
    const float ARROW_START_POSITION_X_2 = 18000.0f;
    const float ARROW_START_POSITION_X_3 = 18600.0f;
    const float ARROW_START_POSITION_Y   = 600.0f;
    const float ARROW_START_POSITION_Z   = 10.0f;
    const float ARROW_MOVE_SPEED_X       = 800.0f;
    const float ARROW_HIT_SIZE_X         = 80.0f;
    const float ARROW_HIT_SIZE_Y         = 19.0f;

    //コウモリ
    const float BAT_START_POSITION_X_1 = 2500.0f;
    const float BAT_START_POSITION_X_2 = 4900.0f;
    const float BAT_START_POSITION_X_3 = 9500.0f;
    const float BAT_START_POSITION_X_4 = 12900.0f;
    const float BAT_START_POSITION_Y   = 450.0f;
    const float BAT_START_POSITION_Z   = 10.0f;
    const float BAT_DEATH_START_POSITION_X_1 = BAT_START_POSITION_X_1;
    const float BAT_DEATH_START_POSITION_X_2 = BAT_START_POSITION_X_2;
    const float BAT_DEATH_START_POSITION_X_3 = BAT_START_POSITION_X_3;
    const float BAT_DEATH_START_POSITION_X_4 = BAT_START_POSITION_X_4;
    const float BAT_DEATH_START_POSITION_Y = BAT_START_POSITION_Y + 80.0f;
    const float BAT_MOVE_SPPED_X       = 600.0f;
    const float BAT_MOVE_SPPED_Y       = 1.0f;
    const float BAT_MOVE_RANGE_Y       = 50.0f;
    const float BAT_HIT_SIZE_X         = 109.0f;
    const float BAT_HIT_SIZE_Y         = 38.0f;
    const float BAT_ANIME_SPEED_X      = 4.0f;
    const float BAT_ANIME_MAX_COUNT    = 4.0f;
    const float BAT_WIDTH              = 123.0f;
    const float BAT_HEIGHT             = 237.0f;

    //足場
    const float SCAFFOLD_START_POSITION_X       = 15040.0f;
    const float SCAFFOLD_START_POSITION_Y       = 480.0f;
    const float SCAFFOLD_START_POSITION_Z       = 10.0f;
    const float SCAFFOLD_DEATH_START_POSITION_X = SCAFFOLD_START_POSITION_X;
    const float SCAFFOLD_DEATH_START_POSITION_Y = SCAFFOLD_START_POSITION_Y + 20;
    const float SCAFFOLD_DEATH_START_POSITION_Z = 10.0f;
    const float SCAFFOLD_MOVE_SPPED_X           = 600.0f;
    const float SCAFFOLD_SIZE_X                 = 250.0f;
    const float SCAFFOLD_SIZE_Y                 = 50.0f;
    const float SCAFFOLD_DEATH_SIZE_X           = 249.0f;
    const float SCAFFOLD_DEATH_SIZE_Y           = 69.0f;

    //宝
    const float JEWELRY_START_POSITION_X_1 = 4040.0f;
    const float JEWELRY_START_POSITION_X_2 = 10940.0f;
    const float JEWELRY_START_POSITION_X_3 = 15490.0f;
    const float JEWELRY_START_POSITION_Y   = 300.0f;
    const float JEWELRY_START_POSITION_Y_3 = 230.0f;
    const float JEWELRY_START_POSITION_Z   = 10.0f;
    const float JEWELRY_MOVE_SPEED_X       = 600.0f;
    const float JEWELRY_HIT_SIZE_X         = 96.0f;
    const float JEWELRY_HIT_SIZE_Y         = 82.0f;

    bool isIntersect(Rect& rect1, Rect& rect2);

    //関数
private:
    void BGUpdate           (const float deltaTime );

    void PlayerUpdate       (const float deltaTime);
    void PlayerSlidingUpdate(const float deltaTime);
    void PlayerJumpUpdate   (const float deltaTime);
    void PlayerMoveUpdate   (const float deltaTime);
    void PlayerDamageUpdate (const float deltaTime);
    void PlayerRideUpdate   (const float deltaTime);

    void ObstacleUpdate(const float deltaTime);
    void DoorUpdate    (const float deltaTime);
    void RockUpdate    (const float deltaTime);
    void ArrowUpdate   (const float deltaTime);
    void BatUpdate     (const float deltaTime);
    void ScaffoldUpdate(const float deltaTime);
    void JewelryUpdate (const float deltaTime);

    void AnimationUpdate(const float deltaTime);

    NextScene SeneChangeUpdate(const float deltaTime);

};