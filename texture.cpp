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
#include <cassert>
#include <string>

#include "texture.h"
#include "renderer.h"
#include "WICTextureLoader11.h"

using namespace DirectX;

// 管理できるテクスチャの最大数
static constexpr int TEXTURE_MAX = 1024;

// 1つのテクスチャが持つ情報
struct Texture
{
	std::wstring fileName;	// ファイル名（重複チェック用）
	unsigned int width;		// 幅
	unsigned int height;	// 高さ
	ID3D11Resource* texture = nullptr;	// テクスチャリソース
	ID3D11ShaderResourceView* textureView = nullptr;	 // シェーダーリソースビュー
};

// テクスチャ管理用の配列
static Texture g_textures[TEXTURE_MAX];

// デバイスとコンテキストの保存用ポインタ
static ID3D11Device* g_device = nullptr;
static ID3D11DeviceContext* g_context = nullptr;

void InitializeTexture()
{
	// デバイスとデバイスコンテキストを保存
	g_device = GetDevice();
	g_context = GetDeviceContext();
}

void FinalizeTexture()
{
	ReleaseAllTexture();
}

int LoadTexture(const wchar_t* fileName, bool mipMap)
{
	if (!g_device || !g_context)
	{
		return TEXTURE_INVALID_ID;
	}
	if (!fileName || fileName[0] == L'\0')
	{
		return TEXTURE_INVALID_ID;
	}
	// すでに読み込まれているファイルかチェック
	for (int id = 0;id < TEXTURE_MAX; id++)
	{
		if (!g_textures[id].texture)
		{
			continue;
		}

		if (g_textures[id].fileName == fileName)
		{
			return id;
		}
	}
	// 新しく読み込む処理
	for (int id = 0;id < TEXTURE_MAX; id++)
	{
		// 空いている場所を探す
		if (g_textures[id].texture)
		{
			continue;
		}

		// ミップマップの有無で読み込み関数を分ける
		HRESULT hr;
		if (mipMap)
		{
			hr = CreateWICTextureFromFile(g_device, g_context, fileName,
				&g_textures[id].texture, &g_textures[id].textureView);
		}
		else
		{
			hr = CreateWICTextureFromFile(g_device, fileName,
				&g_textures[id].texture, &g_textures[id].textureView);
		}
		if (FAILED(hr))
		{
			MessageBoxW(nullptr, L"テクスチャの読み込みに失敗しました", fileName, MB_OK | MB_ICONERROR);
			break;
		}

		// 画像のサイズ（幅と高さ）を取得して保存
		ID3D11Texture2D* texture = (ID3D11Texture2D*)g_textures[id].texture;
		D3D11_TEXTURE2D_DESC t2desc;
		texture->GetDesc(&t2desc);
		g_textures[id].width = t2desc.Width;
		g_textures[id].height = t2desc.Height;
		g_textures[id].fileName = fileName;

		// 登録したID（配列のインデックス）を返す
		return id;
	}

	return TEXTURE_INVALID_ID;
}

void SetTexture(int textureID)
{
	assert(textureID >= 0 && textureID < TEXTURE_MAX);
	
	g_context->PSSetShaderResources(0, 1, &g_textures[textureID].textureView);
}

XMUINT2 GetTextureSize(int textureID)
{
	if (textureID < 0 || textureID >= TEXTURE_MAX)
	{
		return { 0,0 };
	}

	return { g_textures[textureID].width, g_textures[textureID].height };
}

unsigned int GetTextureWidth(int textureID)
{
	if (textureID < 0 || textureID >= TEXTURE_MAX)
	{
		return 0;
	}

	return g_textures[textureID].width;
}

unsigned int GetTextureHeight(int textureID)
{
	if (textureID < 0 || textureID >= TEXTURE_MAX)
	{
		return 0;
	}

	return g_textures[textureID].height;
}

void ReleaseTexture(int textureID)
{
	assert(textureID >= 0 && textureID < TEXTURE_MAX);


	Texture& textureReleasing = g_textures[textureID];
	if (textureReleasing.textureView)
	{
		textureReleasing.textureView->Release();
		textureReleasing.textureView = nullptr;
	}
	if (textureReleasing.texture)
	{
		textureReleasing.texture->Release();
		textureReleasing.texture = nullptr;
	}
	textureReleasing.fileName.clear();
	textureReleasing.width = 0;
	textureReleasing.height = 0;
}
// 複数のIDをまとめて解放するオーバーロード
void ReleaseTexture(const int* textureIDs, int count)
{
	if (!textureIDs || count <= 0)
	{
		assert(!textureIDs || count <= 0);
		return;
	}

	for (int id = 0;id < count;id++)
	{
		if (textureIDs[id] < 0 || textureIDs[id] >= TEXTURE_MAX)
		{
			continue;
		}
		ReleaseTexture(textureIDs[id]);
	}
}

void ReleaseAllTexture()
{
	for (int textureID = 0;textureID < TEXTURE_MAX;textureID++)
	{
		ReleaseTexture(textureID);
	}
}