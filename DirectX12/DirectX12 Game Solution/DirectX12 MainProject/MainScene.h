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
    int bgLoopNumber;

    //松明
    DX9::SPRITE torchSprite;
    SimpleMath::Vector3 torchPosition;
    float torchAnimeX;
    float torchAnimeY;

    //崩壊
    DX9::SPRITE collapseFrontSprite;
    SimpleMath::Vector3 collapseFrontPosition;
    DX9::SPRITE collapseBackSprite;
    SimpleMath::Vector3 collapseBackPosition;

    //天井
    DX9::SPRITE ceilingSprite;
    SimpleMath::Vector3 ceilingPosition;

    //ブラックアウト
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
        PLAYER_MOVE,
        PLAYER_DROP,
        PLAYER_DROP_DEATH
    };
    float playerAnimeX;
    bool playerDeathFlag;

    //障害物
    //扉
    enum { DOOR_DOWN_MAX = 4 };
    DX9::SPRITE doorSprite;
    SimpleMath::Vector3 doorDownPosition[DOOR_DOWN_MAX];
    SimpleMath::Vector3 doorUpPosition;

    //岩
    enum { ROCK_MAX = 6 };
    DX9::SPRITE rockSprite;
    SimpleMath::Vector3 rockPosition[ROCK_MAX];

    //矢(左)
    enum{ ARROW_LEFT_MAX = 4 };
    DX9::SPRITE arrowLeftSprite;
    SimpleMath::Vector3 arrowLeftPosition[ARROW_LEFT_MAX];

    //矢(下)
    enum { ARROW_DOWN_MAX = 5 };
    DX9::SPRITE arrowDownSprite;
    SimpleMath::Vector3 arrowDownPosition[ARROW_DOWN_MAX];

    //コウモリ
    enum { BAT_MAX = 5 };
    DX9::SPRITE batSprite;
    SimpleMath::Vector3 batPosition[BAT_MAX];
    float theta;
    float batBaseY[BAT_MAX];
    float batAnimeX;
    enum { FAKE_BAT_RIGHT_MAX = 3 };
    DX9::SPRITE fakeBatRightSprite;
    SimpleMath::Vector3 fakeBatRightPosition[FAKE_BAT_RIGHT_MAX];

    enum { FAKE_BAT_LEFT_MAX = 4 };
    DX9::SPRITE fakeBatLeftSprite;
    SimpleMath::Vector3 fakeBatLeftPosition[FAKE_BAT_LEFT_MAX];

    //足場
    enum { SCAFFOLD_MAX = 13 };
    DX9::SPRITE scaffoldSprite;
    SimpleMath::Vector3 scaffoldPosition[SCAFFOLD_MAX];
    int scaffoldNumber;
    
    //落とし穴
    enum { SHORT_HOLE_MAX = 3 };
    DX9::SPRITE shortHoleSprite;
    SimpleMath::Vector3 shortHolePosition[SHORT_HOLE_MAX];

    DX9::SPRITE middleHoleSprite;
    SimpleMath::Vector3 middleHolePosition;

    DX9::SPRITE longHoleSprite;
    SimpleMath::Vector3 longHolePosition;

    DX9::SPRITE doubleLongHoleSprite;
    SimpleMath::Vector3 doubleLongHolePosition;

    //UI
    DX9::SPRITE humanSprite;
    SimpleMath::Vector3 humanPosition;
    DX9::SPRITE distanceSprite;
    SimpleMath::Vector3 distancePosition;

    //BGM
    DX9::MEDIARENDERER mediaMainbgm;
    DX9::MEDIARENDERER mediaCollapsese;
    int collapseVolume;

    //SE
    XAudio::SOUNDEFFECT         sePlayerDamage;
    XAudio::SOUNDEFFECT         seDoor[DOOR_DOWN_MAX];
    XAudio::SOUNDEFFECTINSTANCE seDoorInstance[DOOR_DOWN_MAX];

    //定数
    //背景
    const float BG_START_POSITION_X = 0.0f;
    const float BG_START_POSITION_Y = 0.0f;
    const float BG_START_POSITION_Z = 15.0f;
    const float BG_SCROLL_SPEED_X   = -600.0f;
    const float BG_RESET_POSITION_X = -1279.0f;

    //UI
    const float HUMAN_START_POSITION_X = 295.0f;
    const float HUMAN_START_POSITION_Y = 36.0f;
    const float HUMAN_START_POSITION_Z = 6.0f;
    const float HUMAN_MOVE_SPEED = 11.0f;
    const float DISTANCE_START_POSITION_X = 295.0f;
    const float DISTANCE_START_POSITION_Y = 15.0f;
    const float DISTANCE_START_POSITION_Z = 7.0f;

    //松明
    const float TORCH_START_POSITION_X  = 1251.0f;
    const float TORCH_START_POSITION_Y  = 195.0f;
    const float TORCH_START_POSITION_Z  = 14.0f;
    const float TORCH_RESET_POSITION_X  = 1279.0f;
    const float TORCH_SCROLL_SPEED_X    = -600.0f;
    const float TORCH_ANIME_SPED        = 15.0f;
    const float TORCH_ANIME_MAX_COUNT_X = 10.0f;
    const float TORCH_ANIME_MAX_COUNT_Y = 3.0f;
    const float TORCH_WIDTH             = 54.0f;
    const float TORCH_HEIGHT            = 181.0f;

    //ブラックアウト
    const float BLACK_START_POSITION_Z = -20.0f;
    const int SCREENALPHA_COUNT = 300;
    const int SCREENALPHA_LIMIT = 255;

    //崩壊
    const float COLLAPSE_START_POSITION_X       = -50.0f;
    const float COLLAPSE_START_POSITION_Y = -720.0f;
    const float COLLAPSE_START_POSITION_Z       = 9.0f;
    const float COLLAPSE_BACK_START_POSITION_Z  = 10.0f;
    const float COLLAPSE_SCROLL_SPEED_Y         = 900.0f;
    const float COLLAPSE_BACK_SCROLL_SPEED_Y = 400.0f;
    const int   COLLAPSE_SE_VOLUME              = -50;

    //天井
    const float CEILING_START_POSITION_X = 0.0f;
    const float CEILING_START_POSITION_Y = 0.0f;
    const float CEILING_START_POSITION_Z = 8.0f;
    const float CEILING_SCROLL_SPEED_X   = -600.0f;
    const float CEILING_RESET_POSITION_X = -1280.0f;

    //プレイヤー
    const float PLAYER_START_POSITION_X         = 300.0f;
    const float PLAYER_START_POSITION_Y         = 540.0f;
    const float PLAYER_START_POSITION_Z         = 10.0f;
    const float PLAYER_SLIDING_START_POSITION_X = 300.0f; 
    const float PLAYER_SLIDING_START_POSITION_Y = 608.0f;
    const float PLAYER_DAMAGE_LIMIT_COUNT       = 1.0f;
    const float PLAYER_MOVE_START_COUNT         = 51.0f;
    const float PLAYER_MOVE_SPEED               = 600.0f;
    const float PLAYER_SLIDING_START_COUNT      = 0.7f;
    const float PLAYER_HIT_SIZE_X               = 100.0f;
    const float PLAYER_HIT_SIZE_Y               = 132.0f;
    const float PLAYER_SLIDING_HIT_SIZE_X       = 170.0f;
    const float PLAYER_SLIDING_HIT_SIZE_Y       = 76.0f;
    const float PLAYER_DROP_SPEED_Y             = 1000.0f;
    const float PLAYER_DROP_DEATH_POSITION_Y    = 600.0f;
    const float PLAYER_LIMIT_POSITION_X         = 1300.0f;
    const float PLAYER_ANIME_SPEED_X            = 5.5f;
    const float PLAYER_ANIME_MAX_COUNT          = 4.0f;
    const float PLAYER_WIDTH                    = 116.0f;
    const float PLAYER_HEIGHT                   = 132.0f;
    const float PLAYER_LEG_POSITION             = 132.0f;
    const float PLAYER_DAMAGE_POSITION          = 150.0f;

    //重力
    const float GRAVITY_POWER_ADD  = -2000.0f;
    const float GRAVITY_POWER_TAKE = 800.0f;

    //扉
    const float DOOR_DOWN_START_POSITION_X_1    = 5000.0f;
    const float DOOR_DOWN_START_POSITION_X_2    = 14600.0f;
    const float DOOR_DOWN_START_POSITION_X_3    = 26000.0f;
    const float DOOR_DOWN_START_POSITION_X_4    = 27000.0f;
    const float DOOR_DOWN_START_POSITION_Y      = -400.0f;
    const float DOOR_START_POSITION_Z           = 10.0f;
    const float DOOR_MOVE_SPEED_X               = -600.0f;
    const float DOOR_DOWN_SPEED_Y               = 300.0f;
    const float DOOR_SLOW_DOWN_SPEED_Y          = 80.0f;
    const float DOOR_SLOW_DOWN_START_POSITOIN_Y = -250.0f;
    const float DOOR_DOWN_START_POSITOIN_X      = 1280.0f;
    const float DOOR_DOWN_LIMIT_POSITION_Y      = 0.0f;
    const float DOOR_HIT_SIZE_X                 = 10.0f;
    const float DOOR_HIT_SIZE_Y                 = 719.0f;
    const float DOOR_SE_PLAY_POSITION_X         = 1400;

    const float DOOR_UP_START_POSITION_X = 23500.0f;
    const float DOOR_UP_START_POSITION_Y = 0.0f;
    const float DOOR_UP_SPEED_Y          = -200.0f;
    const float DOOR_UP_LIMIT_POSITION_Y = -720.0f;

    //岩
    const float ROCK_START_POSITION_X_1 = 3000.0f;
    const float ROCK_START_POSITION_X_2 = 4000.0f;
    const float ROCK_START_POSITION_X_3 = 11700.0f;
    const float ROCK_START_POSITION_X_4 = 13500.0f;
    const float ROCK_START_POSITION_X_5 = 14000.0f;
    const float ROCK_START_POSITION_X_6 = 26500.0f;
    const float ROCK_START_POSITION_Y   = -82.0f;
    const float ROCK_START_POSITION_Z   = 10.0f;
    const float ROCK_MOVE_SPEED_X       = -600.0f;
    const float ROCK_MOVE_SPEED_Y       = 1400.0f;
    const float ROCK_DOWN_POSITION_X    = 1000.0f;
    const float ROCK_LIMIT_POSITION_Y   = 622.0f;
    const float ROCK_HIT_SIZE_X         = 104.0f;
    const float ROCK_HIT_SIZE_Y         = 82.0f;

    //矢
    const float ARROW_START_POSITION_Z = 10.0f;
    const float ARROW_MOVE_POSITION_X  = 1280.0f;

    const float ARROW_LEFT_MOVE_SPEED_X = -800.0f;
    const float ARROW_LEFT_START_POSITION_X_1 = 10000.0f;
    const float ARROW_LEFT_START_POSITION_X_2 = 10100.0f;
    const float ARROW_LEFT_START_POSITION_X_3 = 23000.0f;
    const float ARROW_LEFT_START_POSITION_X_4 = 25000.0f;
    const float ARROW_LEFT_START_POSITION_Y_1 = 400.0f;
    const float ARROW_LEFT_START_POSITION_Y_2 = 430.0f;
    const float ARROW_LEFT_START_POSITION_Y_3 = 320.0f;
    const float ARROW_LEFT_START_POSITION_Y_4 = 400.0f;

    const float ARROW_DOWN_MOVE_SPEED_X = -600.0f;
    const float ARROW_DOWN_MOVE_SPEED_Y = 1600.0f;
    const float ARROW_DOWN_START_POSITION_X_1 = 5900.0f;
    const float ARROW_DOWN_START_POSITION_X_2 = 6100.0f;
    const float ARROW_DOWN_START_POSITION_X_3 = 10250.0f;
    const float ARROW_DOWN_START_POSITION_X_4 = 21100.0f;
    const float ARROW_DOWN_START_POSITION_X_5 = 21300.0f;
    const float ARROW_DOWN_START_POSITION_Y   = 0.0f;
    const float ARROW_DOWN_LIMIT_POSITION_Y   = 1300.0f;
    const float ARROW_DOWN_LIMIT_POSITION_Y_3 = 800.0f;


    //コウモリ
    const float BAT_START_POSITION_X_1 = 20700.0f;
    const float BAT_START_POSITION_X_2 = 20800.0f;
    const float BAT_START_POSITION_X_3 = 20900.0f;
    const float BAT_START_POSITION_X_4 = 37700.0f;
    const float BAT_START_POSITION_X_5 = 39200.0f;
    const float BAT_START_POSITION_Y_1 = 380.0f;
    const float BAT_START_POSITION_Y_2 = 410.0f;
    const float BAT_START_POSITION_Y_3 = 350.0f;
    const float BAT_START_POSITION_Y_4 = 410.0f;
    const float BAT_START_POSITION_Y_5 = 410.0f;
    const float BAT_START_POSITION_Z   = 10.0f;
    const float BAT_MOVE_SPPED_X       = -1000.0f;
    const float BAT_MOVE_SPPED_Y       = 5.0f;
    const float BAT_MOVE_RANGE_Y       = 15.0f;
    const float BAT_HIT_SIZE_X         = 109.0f;
    const float BAT_HIT_SIZE_Y         = 38.0f;
    const float BAT_HIT_POSITION_Y     = 115.0f;
    const float BAT_ANIME_SPEED_X      = 15.0f;
    const float BAT_ANIME_MAX_COUNT    = 4.0f;
    const float BAT_WIDTH              = 123.0f;
    const float BAT_HEIGHT             = 237.0f;
    const float BAT_SMALL_WIDTH = 67.0f;
    const float BAT_SMALL_HEIGHT = 139.0f;
    //演出コウモリ(右向き)
    const float FAKE_BAT_RIGHT_START_POSITION_X_1 = 300.0f;
    const float FAKE_BAT_RIGHT_START_POSITION_X_2 = 400.0f;
    const float FAKE_BAT_RIGHT_START_POSITION_X_3 = 500.0f;
    const float FAKE_BAT_RIGHT_START_POSITION_Y_1 = 75.0f;
    const float FAKE_BAT_RIGHT_START_POSITION_Y_2 = 150.0f;
    const float FAKE_BAT_RIGHT_START_POSITION_Y_3 = 35.0f;
    const float FAKE_BAT_START_POSITION_Z = 11.0f;
    const float FAKE_BAT_RIGHT_MOVE_SPEED_X = 500.0f;

    //演出コウモリ(左向き)
    const float FAKE_BAT_LEFT_START_POSITION_X_1 = 39110.0f;
    const float FAKE_BAT_LEFT_START_POSITION_X_2 = 39140.0f;
    const float FAKE_BAT_LEFT_START_POSITION_X_3 = 39330.0f;
    const float FAKE_BAT_LEFT_START_POSITION_X_4 = 39330.0f;
    const float FAKE_BAT_LEFT_START_POSITION_Y_1 = 490.0f;
    const float FAKE_BAT_LEFT_START_POSITION_Y_2 = 280.0f;
    const float FAKE_BAT_LEFT_START_POSITION_Y_3 = 360.0f;
    const float FAKE_BAT_LEFT_START_POSITION_Y_4 = 490.0f;

    //足場
    const float SCAFFOLD_START_POSITION_X_1  = 7300.0f;
    const float SCAFFOLD_START_POSITION_X_2  = 7980.0f;
    const float SCAFFOLD_START_POSITION_X_3  = 9750.0f;
    const float SCAFFOLD_START_POSITION_X_4  = 10400.0f;
    const float SCAFFOLD_START_POSITION_X_5  = 16250.0f;
    const float SCAFFOLD_START_POSITION_X_6  = 16850.0f;
    const float SCAFFOLD_START_POSITION_X_7  = 17450.0f;
    const float SCAFFOLD_START_POSITION_X_8  = 18250.0f;
    const float SCAFFOLD_START_POSITION_X_9  = 18900.0f;
    const float SCAFFOLD_START_POSITION_X_10 = 19500.0f;
    const float SCAFFOLD_START_POSITION_X_11 = 27800.0f;
    const float SCAFFOLD_START_POSITION_X_12 = 28400.0f;
    const float SCAFFOLD_START_POSITION_X_13 = 29000.0f;
    const float SCAFFOLD_START_POSITION_Y_1  = 500.0f;
    const float SCAFFOLD_START_POSITION_Y_2  = 500.0f;
    const float SCAFFOLD_START_POSITION_Y_3  = 500.0f;
    const float SCAFFOLD_START_POSITION_Y_4  = 500.0f;
    const float SCAFFOLD_START_POSITION_Y_5  = 500.0f;
    const float SCAFFOLD_START_POSITION_Y_6  = 430.0f;
    const float SCAFFOLD_START_POSITION_Y_7  = 360.0f;
    const float SCAFFOLD_START_POSITION_Y_8  = 550.0f;
    const float SCAFFOLD_START_POSITION_Y_9  = 470.0f;
    const float SCAFFOLD_START_POSITION_Y_10 = 400.0f;
    const float SCAFFOLD_START_POSITION_Y_11 = 500.0f;
    const float SCAFFOLD_START_POSITION_Y_12 = 430.0f;
    const float SCAFFOLD_START_POSITION_Y_13 = 360.0f;
    const float SCAFFOLD_START_POSITION_Z    = 10.0f;
    const float SCAFFOLD_MOVE_SPPED_X        = -600.0f;
    const float SCAFFOLD_HIT_SIZE_X          = 250.0f;
    const float SCAFFOLD_HIT_SIZE_Y          = 50.0f;
    const float SCAFFOLD_HIT_DEATH_SIZE_X    = 150.0f;
    const float SCAFFOLD_HIT_DEATH_SIZE_Y    = 58.5f;
    const float SCAFFOLD_HIT_POSITION_Y      = 30.5f;

    //落とし穴
    const float HOLE_START_POSITION_Y = 625.0f;
    const float HOLE_START_POSITION_Z = 11.0f;
    const float HOLE_MOVE_SPPED_X     = -600.0f;
    const float HOLE_HIT_SIZE_Y       = 50.0f;
    const float HOLE_HIT_POSITION_Y   = 30.0f;
    //落とし穴(小)
    const float SHORT_HOLE_START_POSITION_X_1 = 5800.0f;
    const float SHORT_HOLE_START_POSITION_X_2 = 21000.0f;
    const float SHORT_HOLE_START_POSITION_X_3 = 24800.0f;
    const float SHORT_HOLE_HIT_SIZE_X         = 200.0f;
    const float SHORT_HOLE_HIT_POSITION_X     = 60.0f;
    //落とし穴(中)
    const float MIDDLE_HOLE_START_POSITION_X = 9500.0f;
    const float MIDDLE_HOLE_HIT_SIZE_X       = 1380.0f;
    //落とし穴(大)
    const float LONG_HOLE_START_POSITION_X = 27500.0f;
    const float LONG_HOLE_HIT_SIZE_X       = 2380.0f;
    //落とし穴(特大)
    const float DOUBLE_LONG_HOLE_START_POSITION_X = 16000.0f;
    const float DOUBLE_LONG_HOLE_HIT_SIZE_X       = 3880.0f;
    


    bool isIntersect(Rect& rect1, Rect& rect2);

    //関数
private:
    //背景・UI
    void BGUpdate(const float deltaTime);
    void UiUpdate(const float deltaTime);

    //プレイヤー
    void PlayerUpdate         (const float deltaTime);
    void PlayerSlidingUpdate  (const float deltaTime);
    void PlayerJumpUpdate     (const float deltaTime);
    void PlayerMoveUpdate     (const float deltaTime);
    void PlayerDamageUpdate   (const float deltaTime);
    void PlayerRideUpdate     (const float deltaTime);
    void PlayerDropUpdate     (const float deltaTime);
    void PlayerDropDeathUpdate(const float deltaTime);

    //障害物
    void ObstacleUpdate      (const float deltaTime);
    void DoorUpdate          (const float deltaTime);
    void RockUpdate          (const float deltaTime);
    void ArrowUpdate         (const float deltaTime);
    void BatUpdate           (const float deltaTime);
    void FakeBatUpdate       (const float deltaTime);
    void ScaffoldUpdate      (const float deltaTime);
    void HoleUpdate          (const float deltaTime);
    void ShrotHoleUpdate     (const float deltaTime);
    void MiddleHoleUpdate    (const float deltaTime);
    void LongHoleUpdate      (const float deltaTime);
    void DoubleLongHoleUpdate(const float deltaTime);

    //アニメーション
    void AnimationUpdate(const float deltaTime);

    //BGM
    void Bgm_SeUpdate(const float deltaTime);

    //シーン切り替え
    NextScene SeneChangeUpdate(const float deltaTime);

};