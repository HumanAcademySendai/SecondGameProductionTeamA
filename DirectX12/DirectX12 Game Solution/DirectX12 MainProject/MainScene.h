//
// MainScene.h
//

#pragma once

#include "Scene.h"

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
    enum PLAYERSTATE {
        PLAYER_NORMAL,
        PLAYER_JUMP,
        PLAYER_SLIDING,
        PLAYER_DAMAGE,
        PLAYER_MOVE
    };



    //障害物
    //扉
    DX9::SPRITE doorSprite;
    SimpleMath::Vector3 doorPosition;

    //岩
    enum { ROCK_MAX = 5 };
    DX9::SPRITE rockSprite;
    SimpleMath::Vector3 rockPosition[ROCK_MAX];

    //矢
    DX9::SPRITE arrowSprite;
    SimpleMath::Vector3 arrowPosition;

    //コウモリ
    DX9::SPRITE batSprite;
    SimpleMath::Vector3 batPosition;

    //足場
    DX9::SPRITE scaffoldSprite;
    SimpleMath::Vector3 scaffoldPosition;

    //宝
    enum { JEWELRY_MAX = 3 };
    DX9::SPRITE jewelrySprite;
    SimpleMath::Vector3 jewelryPosition[JEWELRY_MAX];

    //定数
    //背景
    const float BG_START_POSITION_X = 0.0f;
    const float BG_START_POSITION_Y = 0.0f;
    const float BG_START_POSITION_Z = 10.0f;
    const float BG_SCROLL_SPEED_X   = 600.0f;
    const float BG_RESET_POSITION_X = 1280.0f;

    //崩壊
    const float COLLAPSE_START_POSITION_X = 0.0f;
    const float COLLAPSE_START_POSITION_Y = 0.0f;
    const float COLLAPSE_START_POSITION_Z = 9.0f;

    //天井
    const float CEILING_START_POSITION_X = 0.0f;
    const float CEILING_START_POSITION_Y = 0.0f;
    const float CEILING_START_POSITION_Z = 8.0f;

    //プレイヤー
    const float PLAYER_START_POSITION_X    = 300.0f;
    const float PLAYER_START_POSITION_Y    = 500.0f;
    const float PLAYER_START_POSITION_Z    = 0.0f;
    const float PLAYER_SLIDING_POSITION_Y  = 72.0f;
    const float PLAYER_DAMAGE_LIMIT_COUNT  = 0.5f;
    const float PLAYER_MOVE_START_COUNT    = 30.0f;
    const float PLAYER_MOVE_SPEED          = 500.0f;
    const float PLAYER_SLIDING_START_COUNT = 1.0f;
    const float PLAYER_HIT_SIZE_X          = 116.0f;
    const float PLAYER_HIT_SIZE_Y          = 132.0f;
    const float PLAYER_SLIDING_HIT_SIZE_X  = 193.0f;
    const float PLAYER_SLIDING_HIT_SIZE_Y  = 76.0f;

    //重力
    const float GRAVITY_POWER_ADD         = 2000.0f;
    const float GRAVITY_POWER_TAKE        = 800.0f;

    //扉
    const float DOOR_START_POSITION_X = 1000.0f;
    const float DOOR_START_POSITION_Y = 573.0f;
    const float DOOR_START_POSITION_Z = 0.0f;
    const float DOOR_MOVE_SPEED_X     = 600.0f;
    const float DOOR_DOWN_SPEED_Y     = 600.0f;
    const float DOOR_LIMIT_POSITION_Y = 147.0f;

    //岩
    const float ROCK_START_POSITION_X = 1280.0f;
    const float ROCK_START_POSITION_Y = 82.0f;
    const float ROCK_START_POSITION_Z = 0.0f;
    const float ROCK_MOVE_SPEED_X     = 600.0f;
    const float ROCK_MOVE_SPEED_Y     = 800.0f;
    const float ROCK_DOWN_POSITION_X  = 1000.0f;
    const float ROCK_LIMIT_POSITION_Y = 582.0f;
    const float ROCK_HIT_SIZE_X       = 104.0f;
    const float ROCK_HIT_SIZE_Y       = 82.0f;

    //矢
    const float ARROW_START_POSITION_X = 1400.0f;
    const float ARROW_START_POSITION_Y = 500.0f;
    const float ARROW_START_POSITION_Z = 0.0f;
    const float ARROW_MOVE_SPEED_X     = 800.0f;

    //コウモリ
    const float BAT_START_POSITION_X = 1280.0f;
    const float BAT_START_POSITION_Y = 500.0f;
    const float BAT_START_POSITION_Z = 0.0f;
    const float BAT_MOVE_SPPED_X     = 600.0f;

    //足場
    const float SCAFFOLD_START_POSITION_X = 1200.0f;
    const float SCAFFOLD_START_POSITION_Y = 0.0f;
    const float SCAFFOLD_START_POSITION_Z = 0.0f;
    const float SCAFFOLD_MOVE_SPPED_X     = 600.0f;

    //宝
    const float JEWELRY_START_POSITION_X = 1200.0f;
    const float JEWELRY_START_POSITION_Y = 300.0f;
    const float JEWELRY_START_POSITION_Z = 0.0f;
    const float JEWELRY_MOVE_SPEED_X     = 600.0f;
    const float JEWELRY_HIT_SIZE_X       = 96.0f;
    const float JEWELRY_HIT_SIZE_Y       = 82.0f;

    bool isIntersect(Rect& rect1, Rect& rect2);

    //関数
private:
    void BGUpdate           (const float deltaTime );

    void PlayerUpdate       (const float deltaTime);
    void PlayerSlidingUpdate(const float deltaTime);
    void PlayerJumpUpdate   (const float deltaTime);
    void PlayerMoveUpdate   (const float deltaTime);
    void PlayerDamageUpdate (const float deltaTime);

    void ObstacleUpdate(const float deltaTime);
    void DoorUpdate    (const float deltaTime);
    void RockUpdate    (const float deltaTime);
    void ArrowUpdate   (const float deltaTime);
    void BatUpdate     (const float deltaTime);
    void ScaffoldUpdate(const float deltaTime);
    void JewelryUpdate (const float deltaTime);

};