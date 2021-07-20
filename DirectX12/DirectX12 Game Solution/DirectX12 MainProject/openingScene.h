//
// openingScene.h
//

#pragma once

#include "Scene.h"
#include "cppcoro/generator.h"
#include "DontDestroyOnLoad.h"

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
    enum { TORCH_MAX = 2 };
    DX9::SPRITE torchSprite;
    SimpleMath::Vector3 torchPosition[TORCH_MAX];
    float torchAnimeX;
    float torchAnimeY;

    //崩壊
    enum { COLLAPSE_MAX = 7 };
    DX9::SPRITE collapseFrontSprite;
    SimpleMath::Vector3 collapseFrontPosition[COLLAPSE_MAX];
    //DX9::SPRITE collapseBackSprite;
    //SimpleMath::Vector3 collapseBackPosition;
    //float collapseWidth;

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
    DX9::SPRITE playerJewelrySprite;

    bool playerFlag;
    float playerMove;
    bool deltaFlag;
    float playerPauseCount;

    float playerAnimeX;
    float playerAnimeY;

    float delta_Time;
    float moveDelta;

    //SE
    int collapseVolume;


    //定数
    //ブラックアウト
    const float SCREEN_START_POSITION_Z = -20.0f;
    const float SCREEN_ALPHA_ADD_POSITION_X = 1280.0f;
    const int SCREEN_ALPHA_COUNT = 250;
    const int SCREEN_ALPHA_LIMIT = 255;


    //台座
    const float STAND_START_POSITION_X = 587.0f;
    const float STAND_START_POSITION_Y = 519.0f;
    const float STAND_JEWELRY_START_POSITION_Y = 525.0f;
    const float STAND_START_POSITION_Z = 11.0f;

    //松明
    const float TORCH_START_POSITION_X_1 = -25.0f;
    const float TORCH_START_POSITION_X_2 = 1255.0f;
    const float TORCH_START_POSITION_Y = 195.0f;
    const float TORCH_START_POSITION_Z = 14.0f;
    //アニメーション
    const float TORCH_ANIME_SPED = 15.0f;
    const float TORCH_ANIME_MAX_COUNT_X = 10.0f;
    const float TORCH_ANIME_MAX_COUNT_Y = 3.0f;
    const float TORCH_WIDTH = 54.0f;
    const float TORCH_HEIGHT = 181.0f;



    //崩壊
    const float COLLAPSE_START_POSITION_Y = -1440.0f;
    const float COLLAPSE_FRONT_START_POSITION_Z = 9.0f;
    const float COLLAPSE_BACK_START_POSITION_Z  = 10.0f;
    const float COLLAPSE_SCROLL_SPEED_Y      = 800.0f;
    const float COLLAPSE_BACK_SCROLL_SPEED_Y = 400.0f;
    const float COLLAPSE_WIDTH_LIMIT = 1280.0f;
    const float COLLAPSE_HEIGHT      = 1440.0f;
    const float COLLAPSE_WIDTH_ADD = 500.0f;
    const int   COLLAPSE_SE_VOLUME = -50;

    const float COLLAPSE_START_POSITION_X_1 = 0.0f;
    const float COLLAPSE_START_POSITION_X_2 = 177.0f;
    const float COLLAPSE_START_POSITION_X_3 = 354.0f;
    const float COLLAPSE_START_POSITION_X_4 = 531.0f;
    const float COLLAPSE_START_POSITION_X_5 = 708.0f;
    const float COLLAPSE_START_POSITION_X_6 = 885.0f;
    const float COLLAPSE_START_POSITION_X_7 = 1062.0f;


    //プレイヤー
    const float PLAYER_START_POSITION_X = 500.0f;
    const float PLAYER_START_POSITION_Y = 540.0f;
    const float PLAYER_START_POSITION_Z = -5.0f;
    const float PLAYER_MOVE_SPEED_X = 300.0f;
    const float PLAYER_MOVE_COUNT = 2.0f;
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
    NextScene OpeningSceneUpdate(const float deltaTime);

};