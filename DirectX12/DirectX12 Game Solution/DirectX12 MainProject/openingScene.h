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

    // �ϐ��̐錾
    //�w�i
    DX9::SPRITE bgSprite;
    SimpleMath::Vector3 bgPosition;

    //����
    DX9::SPRITE torchSprite;
    SimpleMath::Vector3 torchPosition;
    float torchAnimeX;
    float torchAnimeY;

    //����
    DX9::SPRITE collapseFrontSprite;
    SimpleMath::Vector3 collapseFrontPosition;
    DX9::SPRITE collapseBackSprite;
    SimpleMath::Vector3 collapseBackPosition;
    float collapseWidth;

    //�V��
    DX9::SPRITE ceilingSprite;
    SimpleMath::Vector3 ceilingPosition;

    //���
    DX9::SPRITE standJewelrySprite;
    SimpleMath::Vector3 standJewelryPosition;

    DX9::SPRITE standSprite;
    SimpleMath::Vector3 standPosition;

    bool standFlag;
    //�u���b�N�A�E�g
    DX9::SPRITE blackSprite;
    SimpleMath::Vector3 blackPosition;
    int screenAlpha;

    //�v���C���[
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

    //�萔
    
    //���
    const float STAND_START_POSITION_X = 587.0f;
    const float STAND_START_POSITION_Y = 519.0f;
    const float STAND_JEWELRY_START_POSITION_Y = 525.0f;
    const float STAND_START_POSITION_Z = 1.0f;


    //����
    const float COLLAPSE_START_POSITION_Y = -720.0f;
    const float COLLAPSE_FRONT_START_POSITION_Z = 9.0f;
    const float COLLAPSE_BACK_START_POSITION_Z = 10.0f;
    const float COLLAPSE_SCROLL_SPEED_Y = 800.0f;
    const float COLLAPSE_BACK_SCROLL_SPEED_Y = 400.0f;
    const float COLLAPSE_WIDTH_LIMIT = 1280.0f;
    const float COLLAPSE_HEIGHT = 1440.0f;
     
    //�v���C���[
    const float PLAYER_START_POSITION_X = 500.0f;
    const float PLAYER_START_POSITION_Y = 540.0f;
    const float PLAYER_START_POSITION_Z = -5.0f;
    const float PLAYER_MOVE_SPEED_X = 300.0f;

    //�v���C���[�̃A�j���[�V����
    const float PLAYER_ANIME_SPEED_X = 16.0f;
    const float PLAYER_ANIME_MAX_COUNT_X = 4.0f;
    const float PLAYER_ANIME_MAX_COUNT_Y = 2.0f;
    const float PLAYER_WIDTH  = 116.0f;
    const float PLAYER_HEIGHT = 132.0f;


    // �R���[�`���̃v���g�^�C�v�錾
    cppcoro::generator<int> Move();                       //�֐��{��
    cppcoro::generator<int>                  co_move;     //�R���[�`������p
    cppcoro::detail::generator_iterator<int> co_move_it;  //�R���[�`������p


private:
    //�֐�
    void PlayerUpdate(const float deltaTime);
    void BGUpdate(const float deltaTime);
    void AnimationUpdate(const float deltaTime);

};