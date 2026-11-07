/*
* +-------------------------------------+
* File   : [jenga_player.cpp]
* Author : íæùÑå´
* Date   : 2026/11/02
*
*
* ãŸã}éñã∆ÇÃÉvÉåÉCÉÑÅ[êßå‰
* +-------------------------------------+
*/
#include "main.h"
#include "sprite.h"
#include "texture.h"
#include "camera.h"
#include "keyboard.h"
#include "color.h"
#include "GameObject.h"
#include "EmergencyManager.h"
using namespace DirectX;


static GameObject g_arrow{ {(float)SCREEN_WIDTH * 0.5f,680.0f},{50.0f,150.0f},0.0f };
static float g_rotateTime{ 0.0f };


float GetRadianDegree(float angle)
{
	return (3.14f / 180.0f) * angle;
}

void InitializeEmergencyPlayer(void)
{
	g_arrow.SetTextureID(LoadTexture(L"asset\\UI_Arrow.png"));
	g_arrow.SetColor(GetColorCode(COLOR::RED));

	g_rotateTime = 0.0f;
}

void FinalizeEmergencyPlayer(void)
{
	ReleaseTexture(g_arrow.GetTextureID());
}

void UpdateEmergencyPlayer(void)
{
	g_rotateTime += 0.03f;	

	const float angle = sinf(g_rotateTime) * 70.0f;
	g_arrow.SetRotation(GetRadianDegree(angle));


	if (Keyboard_IsKeyTrigger(KK_SPACE))
	{
		constexpr float POWER = 5.0f;

		const float degree = GetRadianDegree(angle);
		const float x = sinf(degree);
		const float y = cosf(degree);
		const XMFLOAT2 velocity = { x * POWER,-y * POWER };

		SetRocket(g_arrow.GetPosition(), velocity, g_arrow.GetRotation());
	}
}

void DrawEmergencyPlayer(void)
{
	DrawSprite(g_arrow.GetPosition(), g_arrow.GetSize(), g_arrow.GetRotation(), g_arrow.GetTextureID(), g_arrow.GetColor());
}
