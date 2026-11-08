/*==============================================

	ポリゴン描画[sprite.cpp]

	Author : Shim
	Date   : 2026/06/05





================================================*/
#include "sprite.h"
#include "renderer.h"
#include "texture.h"
#include "camera.h"
#include "color.h"
using namespace DirectX;

static constexpr unsigned int NUM_VERTEX = 4;

static ID3D11Buffer* g_pVertexBuffer = nullptr;//頂点バッファ


void InitSprite(void)
{
	// 頂点バッファ⽣成
	D3D11_BUFFER_DESC bd{};
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(VERTEX_3D) * NUM_VERTEX;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	GetDevice()->CreateBuffer(&bd, NULL, &g_pVertexBuffer);
}

void UninitSprite(void)
{
	if (g_pVertexBuffer)
	{
		g_pVertexBuffer->Release();
		g_pVertexBuffer = nullptr;
	}
}


void DrawSprite(XMFLOAT2 position, XMFLOAT2 size, float rotation, int textureID, XMFLOAT4 color)
{
	//テクスチャ設定
	SetTexture(textureID);

	//頂点設定
	// 頂点バッファをロックする 
	D3D11_MAPPED_SUBRESOURCE msr;
	GetDeviceContext()->Map(g_pVertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	// 頂点バッファへの仮想ポインタを取得 
	VERTEX_3D* v = (VERTEX_3D*)msr.pData;

	//頂点座標
	v[0].Position = { -0.5f, -0.5f,0.0f };
	v[1].Position = { 0.5f, -0.5f,0.0f };
	v[2].Position = { -0.5f, 0.5f,0.0f };
	v[3].Position = { 0.5f, 0.5f,0.0f };

	//テクスチャ座標
	v[0].TexCoord = { 0.0f ,0.0f };
	v[1].TexCoord = { 1.0f ,0.0f };
	v[2].TexCoord = { 0.0f ,1.0f };
	v[3].TexCoord = { 1.0f ,1.0f };

	v[0].Diffuse = color;
	v[1].Diffuse = color;
	v[2].Diffuse = color;
	v[3].Diffuse = color;

	// 頂点バッファのロックを解除 
	GetDeviceContext()->Unmap(g_pVertexBuffer, 0);

	//2Dマトリクス設定
	const XMMATRIX scaleMatrix = XMMatrixScaling(size.x, size.y, 1.0f);
	const XMMATRIX rotationMatrix = XMMatrixRotationZ(rotation);
	const XMMATRIX translationMatrix = XMMatrixTranslation(position.x, position.y, 0.0f);
	const XMMATRIX worldMatrix = scaleMatrix * rotationMatrix * translationMatrix;
	const XMMATRIX viewMatrix = XMMatrixIdentity();
	const XMMATRIX projectionMatrix = XMMatrixOrthographicOffCenterLH(0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.0f, 100.0f);
	//const XMMATRIX viewMatrix = GetViewMatrix();
	//const XMMATRIX projectionMatrix = GetProjectionMatrix();
	SetRendererMatrix(worldMatrix * viewMatrix * projectionMatrix);


	// 頂点バッファを描画パイプラインに設定 
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_pVertexBuffer, &stride, &offset);

	//プリミティブトポロジの設定
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// ポリゴン描画命令発⾏ 
	GetDeviceContext()->Draw(NUM_VERTEX, 0);
}

void DrawSpriteScroll(XMFLOAT2 position, XMFLOAT2 size, float rotation, int textureID, XMFLOAT4 color)
{
	//テクスチャ設定
	SetTexture(textureID);

	//頂点設定
	// 頂点バッファをロックする 
	D3D11_MAPPED_SUBRESOURCE msr;
	GetDeviceContext()->Map(g_pVertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	// 頂点バッファへの仮想ポインタを取得 
	VERTEX_3D* v = (VERTEX_3D*)msr.pData;

	//頂点座標
	v[0].Position = { -0.5f, -0.5f,0.0f };
	v[1].Position = { 0.5f, -0.5f,0.0f };
	v[2].Position = { -0.5f, 0.5f,0.0f };
	v[3].Position = { 0.5f, 0.5f,0.0f };

	//テクスチャ座標
	v[0].TexCoord = { 0.0f ,0.0f };
	v[1].TexCoord = { 1.0f ,0.0f };
	v[2].TexCoord = { 0.0f ,1.0f };
	v[3].TexCoord = { 1.0f ,1.0f };

	v[0].Diffuse = color;
	v[1].Diffuse = color;
	v[2].Diffuse = color;
	v[3].Diffuse = color;

	// 頂点バッファのロックを解除 
	GetDeviceContext()->Unmap(g_pVertexBuffer, 0);

	//カメラ
	const XMFLOAT3 camera = GetCameraOffset();
	const float centerX = SCREEN_WIDTH * 0.5f;
	const float centerY = SCREEN_HEIGHT * 0.5f;
	position.x += camera.x;
	position.y += camera.y;
	position.x = centerX + (position.x - centerX) * camera.z;
	position.y = centerY + (position.y - centerY) * camera.z;
	size.x *= camera.z;
	size.y *= camera.z;

	//2Dマトリクス設定
	const XMMATRIX scaleMatrix = XMMatrixScaling(size.x, size.y, 1.0f);
	const XMMATRIX rotationMatrix = XMMatrixRotationZ(rotation);
	const XMMATRIX translationMatrix = XMMatrixTranslation(position.x, position.y, 0.0f);
	const XMMATRIX worldMatrix = scaleMatrix * rotationMatrix * translationMatrix;
	const XMMATRIX viewMatrix = XMMatrixIdentity();
	const XMMATRIX projectionMatrix = XMMatrixOrthographicOffCenterLH(0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.0f, 100.0f);
	SetRendererMatrix(worldMatrix * viewMatrix * projectionMatrix);


	// 頂点バッファを描画パイプラインに設定 
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_pVertexBuffer, &stride, &offset);

	//プリミティブトポロジの設定
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// ポリゴン描画命令発⾏ 
	GetDeviceContext()->Draw(NUM_VERTEX, 0);
}

void DrawSpriteZoom(DirectX::XMFLOAT2 position, DirectX::XMFLOAT2 size, float rotation, int textureID, DirectX::XMFLOAT4 color)
{
	//テクスチャ設定
	SetTexture(textureID);

	//頂点設定
	// 頂点バッファをロックする 
	D3D11_MAPPED_SUBRESOURCE msr;
	GetDeviceContext()->Map(g_pVertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	// 頂点バッファへの仮想ポインタを取得 
	VERTEX_3D* v = (VERTEX_3D*)msr.pData;

	//頂点座標
	v[0].Position = { -0.5f, -0.5f,0.0f };
	v[1].Position = { 0.5f, -0.5f,0.0f };
	v[2].Position = { -0.5f, 0.5f,0.0f };
	v[3].Position = { 0.5f, 0.5f,0.0f };

	//テクスチャ座標
	v[0].TexCoord = { 0.0f ,0.0f };
	v[1].TexCoord = { 1.0f ,0.0f };
	v[2].TexCoord = { 0.0f ,1.0f };
	v[3].TexCoord = { 1.0f ,1.0f };

	v[0].Diffuse = color;
	v[1].Diffuse = color;
	v[2].Diffuse = color;
	v[3].Diffuse = color;

	// 頂点バッファのロックを解除 
	GetDeviceContext()->Unmap(g_pVertexBuffer, 0);

	//カメラ
	const XMFLOAT3 camera = GetCameraOffset();
	//const float centerX = SCREEN_WIDTH * 0.5f;
	//const float centerY = SCREEN_HEIGHT * 0.5f;
	//position.x = centerX + (position.x - centerX) * camera.z;
	//position.y = centerY + (position.y - centerY) * camera.z;
	size.x *= camera.z;
	size.y *= camera.z;

	//2Dマトリクス設定
	const XMMATRIX scaleMatrix = XMMatrixScaling(size.x, size.y, 1.0f);
	const XMMATRIX rotationMatrix = XMMatrixRotationZ(rotation);
	const XMMATRIX translationMatrix = XMMatrixTranslation(position.x, position.y, 0.0f);
	const XMMATRIX worldMatrix = scaleMatrix * rotationMatrix * translationMatrix;
	const XMMATRIX viewMatrix = XMMatrixIdentity();
	const XMMATRIX projectionMatrix = XMMatrixOrthographicOffCenterLH(0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.0f, 100.0f);
	SetRendererMatrix(worldMatrix * viewMatrix * projectionMatrix);


	// 頂点バッファを描画パイプラインに設定 
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_pVertexBuffer, &stride, &offset);

	//プリミティブトポロジの設定
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// ポリゴン描画命令発⾏ 
	GetDeviceContext()->Draw(NUM_VERTEX, 0);
}

void DrawSpriteCirclePercentScroll(XMFLOAT2 position, float radius, int percent, int textureID)
{
	//テクスチャ設定
	SetTexture(textureID);

	//カメラ
	const XMFLOAT3 camera = GetCameraOffset();
	const float centerX = SCREEN_WIDTH * 0.5f;
	const float centerY = SCREEN_HEIGHT * 0.5f;
	position.x += camera.x;
	position.y += camera.y;
	position.x = centerX + (position.x - centerX) * camera.z;
	position.y = centerY + (position.y - centerY) * camera.z;
	radius *= camera.z * 0.5f;

	//2Dマトリクス設定
	const XMMATRIX worldMatrix = XMMatrixIdentity();
	const XMMATRIX viewMatrix = XMMatrixIdentity();
	const XMMATRIX projectionMatrix = XMMatrixOrthographicOffCenterLH(0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.0f, 100.0f);
	SetRendererMatrix(worldMatrix * viewMatrix * projectionMatrix);


	D3D11_MAPPED_SUBRESOURCE msr;
	XMFLOAT2 vertexPosition{ 0.0f,0.0f };
	XMFLOAT2 prevVertexPosition{ position.x + radius,position.y };
	float angle;

	for (int i = 0;i <= 100;i++)
	{
		GetDeviceContext()->Map(g_pVertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

		VERTEX_3D* v = (VERTEX_3D*)msr.pData;


		angle = (360.0f / 100) * i * (3.14f / 180.0f);
		vertexPosition.x = radius * cosf(angle) + position.x;
		vertexPosition.y = radius * -sinf(angle) + position.y;

		v[0].Position = { position.x,  position.y, 0.0f };
		v[1].Position = { vertexPosition.x, vertexPosition.y, 0.0f };
		v[2].Position = { prevVertexPosition.x,prevVertexPosition.y,0.0f };

		XMFLOAT4 color;
		if (i < percent)
		{
			color = GetColorCode(COLOR::YELLOW);
		}
		else
		{
			color = GetColorCode(COLOR::BLACK);
		}
		v[0].Diffuse = color;
		v[1].Diffuse = color;
		v[2].Diffuse = color;

		prevVertexPosition = vertexPosition;

		GetDeviceContext()->Unmap(g_pVertexBuffer, 0);

		// 頂点バッファを描画パイプラインに設定 
		UINT stride = sizeof(VERTEX_3D);
		UINT offset = 0;
		GetDeviceContext()->IASetVertexBuffers(0, 1, &g_pVertexBuffer, &stride, &offset);

		//プリミティブトポロジの設定
		GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

		// ポリゴン描画命令発⾏ 
		GetDeviceContext()->Draw(3, 0);
	}
}

void DrawSpriteAnime(
	XMFLOAT2 position, XMFLOAT2 size, XMFLOAT2 textureCoordinate, XMFLOAT2 textureSize,
	int textureID, bool flip, XMFLOAT4 color)
{
	SetTexture(textureID);

	//position.x += g_offset.x;
	//position.y += g_offset.y;

	// 頂点バッファをロックする 
	D3D11_MAPPED_SUBRESOURCE msr;
	GetDeviceContext()->Map(g_pVertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	// 頂点バッファへの仮想ポインタを取得 
	VERTEX_3D* v = (VERTEX_3D*)msr.pData;

	//頂点座標
	v[0].Position = { position.x - size.x * 0.5f,position.y - size.y * 0.5f,0.0f };
	v[1].Position = { position.x + size.x * 0.5f,position.y - size.y * 0.5f,0.0f };
	v[2].Position = { position.x - size.x * 0.5f,position.y + size.y * 0.5f,0.0f };
	v[3].Position = { position.x + size.x * 0.5f,position.y + size.y * 0.5f,0.0f };

	//テクスチャ座標
	if (flip)
	{
		v[0].TexCoord = { -textureCoordinate.x,						+textureCoordinate.y };
		v[1].TexCoord = { -(textureCoordinate.x + textureSize.x) ,	+textureCoordinate.y };
		v[2].TexCoord = { -textureCoordinate.x ,					+(textureCoordinate.y + textureSize.y) };
		v[3].TexCoord = { -(textureCoordinate.x + textureSize.x) ,	+(textureCoordinate.y + textureSize.y) };
	}
	else
	{
		v[0].TexCoord = { textureCoordinate.x,					textureCoordinate.y };
		v[1].TexCoord = { textureCoordinate.x + textureSize.x ,	textureCoordinate.y };
		v[2].TexCoord = { textureCoordinate.x ,					textureCoordinate.y + textureSize.y };
		v[3].TexCoord = { textureCoordinate.x + textureSize.x ,	textureCoordinate.y + textureSize.y };
	}

	//頂点色
	v[0].Diffuse = color;
	v[1].Diffuse = color;
	v[2].Diffuse = color;
	v[3].Diffuse = color;

	// 頂点バッファのロックを解除 
	GetDeviceContext()->Unmap(g_pVertexBuffer, 0);

	//2Dマトリクス設定
	//SetWorldViewProjection2D();

	// 頂点バッファを描画パイプラインに設定 
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_pVertexBuffer, &stride, &offset);

	//プリミティブトポロジの設定
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// ポリゴン描画命令発⾏ 
	GetDeviceContext()->Draw(4, 0);
}

