//
// openingScene.h
//

#pragma once

#include "Scene.h"
#include "cppcoro/generator.h"

using Microsoft::WRL::ComPtr;
using std::unique_ptr;
using std::make_unique;
using namespace DirectX;

class openingScene final : public Scene {
public:
    openingScene();
    virtual ~openingScene() { Terminate(); }

    openingScene(openingScene&&) = default;
    openingScene& operator= (openingScene&&) = default;

    openingScene(openingScene const&) = delete;
    openingScene& operator= (openingScene const&) = delete;

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
    //背景
    DX9::SPRITE bgSprite;
    SimpleMath::Vector3 bgPosition;

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
    float collapseWidth;

    //天井
    DX9::SPRITE ceilingSprite;
    SimpleMath::Vector3 ceilingPosition;

    //台座
    DX9::SPRITE standJewelrySprite;
    SimpleMath::Vector3 standJewelryPosition;

    DX9::SPRITE standSprite;
    SimpleMath::Vector3 standPosition;

    bool standFlag;
    //ブラックアウト
    DX9::SPRITE blackSprite;
    SimpleMath::Vector3 blackPosition;
    int screenAlpha;

    //プレイヤー
    DX9::SPRITE playerSprite;
    SimpleMath::Vector3 playerPosition;
    DX9::SPRITE playerPauseSprite;


    float playerAnimeX;
    float playerAnimeY;

    float delta_Time;

    //定数
    
    //台座
    const float STAND_START_POSITION_X = 166.0f;
    const float STAND_START_POSITION_Y = 519.0f;
    const float STAND_START_POSITION_Z = 0.0f;

    //崩壊
    const float COLLAPSE_START_POSITION_Y = -720.0f;
    const float COLLAPSE_FRONT_START_POSITION_Z = 9.0f;
    const float COLLAPSE_BACK_START_POSITION_Z = 10.0f;
    const float COLLAPSE_SCROLL_SPEED_Y = 800.0f;
    const float COLLAPSE_BACK_SCROLL_SPEED_Y = 400.0f;
    const float COLLAPSE_WIDTH_LIMIT = 1280.0f;
    const float COLLAPSE_HEIGHT = 1440.0f;
     
    //プレイヤー
    const float PLAYER_START_POSITION_X = 1290.0f;
    const float PLAYER_START_POSITION_Y = 540.0f;
    const float PLAYER_START_POSITION_Z = -5.0f;
    const float PLAYER_MOVE_SPEED_X = 500.0f;

    //プレイヤーのアニメーション
    const float PLAYER_ANIME_SPEED_X = 16.0f;
    const float PLAYER_ANIME_MAX_COUNT_X = 4.0f;
    const float PLAYER_ANIME_MAX_COUNT_Y = 2.0f;
    const float PLAYER_WIDTH  = 116.0f;
    const float PLAYER_HEIGHT = 132.0f;


    // コルーチンのプロトタイプ宣言
    cppcoro::generator<int> Move();                       //関数本体
    cppcoro::generator<int>                  co_move;     //コルーチン制御用
    cppcoro::detail::generator_iterator<int> co_move_it;  //コルーチン制御用


private:
    //関数
    void PlayerUpdate(const float deltaTime);
    void BGUpdate(const float deltaTime);
    void AnimationUpdate(const float deltaTime);

};