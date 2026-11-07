/*
* +-------------------------------------+
* File   : ƒJƒƒ‰§Œä[camera.cpp]
* Author : ’¾„Œ«
* Date   : 2026/11/01
*
*
*
* +-------------------------------------+
*/
#include <DirectXMath.h>
#include "renderer.h"
#include "keyboard.h"
#include "mouse.h"

using namespace DirectX;

static constexpr float SPEED_CAMERA = 10.0f;
static constexpr float ZOOM_SPEED_CAMERA = 0.1f;
static constexpr float ZOOM_MAX = 5.0f;
static constexpr float ZOOM_MIN = 0.1f;


static XMFLOAT3 g_cameraOffset{ 0.0f,0.0f,0.0f };


const XMFLOAT3& GetCameraOffset(void)
{
	return g_cameraOffset;
}

void InitializeCamera(void)
{
	g_cameraOffset = { 0.0f,0.0f,1.0f };
}

void UpdateCamera(void)
{
	if (Keyboard_IsKeyDown(KK_W))
	{
		g_cameraOffset.y += SPEED_CAMERA;
	}
	if (Keyboard_IsKeyDown(KK_S))
	{
		g_cameraOffset.y -= SPEED_CAMERA;
	}
	if (Keyboard_IsKeyDown(KK_A))
	{
		g_cameraOffset.x += SPEED_CAMERA;
	}
	if (Keyboard_IsKeyDown(KK_D))
	{
		g_cameraOffset.x -= SPEED_CAMERA;
	}
	if (GetMouseState(MOUSE::WHEEL_UP))
	{
		g_cameraOffset.z += ZOOM_SPEED_CAMERA;
		if (g_cameraOffset.z > ZOOM_MAX)
		{
			g_cameraOffset.z = ZOOM_MAX;
		}
	}
	if (GetMouseState(MOUSE::WHEEL_DOWN))
	{
		g_cameraOffset.z -= ZOOM_SPEED_CAMERA;
		if (g_cameraOffset.z < ZOOM_MIN)
		{
			g_cameraOffset.z = ZOOM_MIN;
		}
	}
}
