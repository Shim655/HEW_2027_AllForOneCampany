/*
* +-------------------------------------+
* File   : テクスチャ管理[texture.h]
* Author : 沈揆賢
* Date   : 2026/10/10
*
*
*
* +-------------------------------------+
*/
#pragma once

#include <DirectXMath.h>
#include <d3d11.h>

static constexpr int TEXTURE_INVALID_ID = -1;

// 初期化と終了処理
void InitializeTexture(void);
void FinalizeTexture(void);

// テクスチャの読み込み
int LoadTexture(const wchar_t* fileName, bool mipMap = true);

// テクスチャの解放
void ReleaseTexture(int textureID);
void ReleaseAllTexture();

// 描画時のテクスチャ設定
void SetTexture(int textureID);

// テクスチャ情報の取得
DirectX::XMUINT2 GetTextureSize(int textureID);
unsigned int GetTextureWidth(int textureID);
unsigned int GetTextureHeight(int textureID);

