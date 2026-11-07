/*
* +-------------------------------------+
* File   : プレイヤー制御[jenga_player.cpp]
* Author : 沈揆賢
* Date   : 2026/11/02
*
*
*
* +-------------------------------------+
*/
#include "main.h"
#include "sprite.h"
#include "texture.h"
#include "mouse.h"
#include "keyboard.h"
#include "camera.h"
#include "color.h"
#include "JengaManager.h"
#include "text.h"
#include "jenga_player.h"
using namespace DirectX;

static constexpr float ROTATION_SPEED = 0.03f;

static XMFLOAT2 g_playerPosition{ 0.0f,0.0f };
static Building* g_pBuilding{ nullptr };

static GameObject g_businessIcon({ 0.0f,0.0f }, { 50.0f,50.0f }, 0.0f);
static BUSINESS_TYPE g_business{ BUSINESS_TYPE::NONE };

static int g_money{ 0 };
static int g_numEmployee{ 0 };

static b2BodyId g_debugID;

void InitializeJengaPlayer(void)
{
	g_playerPosition = { 0.0f,0.0f };
	g_money = 1000;
	g_numEmployee = 0;

	g_businessIcon.SetSize({ 50.0f,50.0f });
	g_businessIcon.SetColor(GetColorCode(COLOR::WHITE));
	g_businessIcon.SetTextureID(LoadTexture(L"asset\\UI_Heart_Full.png"));
	g_business = BUSINESS_TYPE::NONE;
}

void FinalizeJengaPlayer(void)
{
	if (g_pBuilding)
	{
		delete g_pBuilding;
		g_pBuilding = nullptr;
	}
}

void UpdateJengaPlayer(void)
{
	//マウスの座標をカメラに合わせて補正
	const XMINT2 mousePosition = GetMousePosition();
	const XMFLOAT3 cameraOffset = GetCameraOffset();
	const float centerX = SCREEN_WIDTH * 0.5f;
	const float centerY = SCREEN_HEIGHT * 0.5f;
	g_playerPosition.x = (float)mousePosition.x;
	g_playerPosition.y = (float)mousePosition.y;
	g_playerPosition.x = centerX + (g_playerPosition.x - centerX) / cameraOffset.z;
	g_playerPosition.y = centerY + (g_playerPosition.y - centerY) / cameraOffset.z;
	g_playerPosition.x -= cameraOffset.x;
	g_playerPosition.y -= cameraOffset.y;



	if (g_pBuilding != nullptr)
	{
		//回転
		if (Keyboard_IsKeyDown(KK_LEFT))
		{
			g_pBuilding->SetRotation(g_pBuilding->GetRotation() + ROTATION_SPEED);
		}
		if (Keyboard_IsKeyDown(KK_RIGHT))
		{
			g_pBuilding->SetRotation(g_pBuilding->GetRotation() - ROTATION_SPEED);
		}

		//配置
		if (CheckJengaOverlap(g_playerPosition, g_pBuilding->GetSize(), g_pBuilding->GetRotation()).hit)
		{
			g_pBuilding->SetColor(GetColorCode(COLOR::RED));
		}
		else
		{
			g_pBuilding->SetColor(GetColorCode(COLOR::WHITE));

			if (GetMouseState(MOUSE::BUTTON_LEFT_UP))
			{
				g_pBuilding->SetPosition(g_playerPosition);
				SetJenga(g_pBuilding);
				delete g_pBuilding;
				g_pBuilding = nullptr;
			}
		}
	}
	if (g_business != BUSINESS_TYPE::NONE)
	{
		const OverLapContext overlap = CheckJengaOverlap(g_playerPosition, g_businessIcon.GetSize(), g_businessIcon.GetRotation());
		g_debugID = overlap.hitBodyID;

		if (overlap.hit)
		{
			g_businessIcon.SetColor(GetColorCode(COLOR::WHITE, 0.5f));
			if (GetMouseState(MOUSE::BUTTON_LEFT_UP))
			{
				SetJengaBusiness(overlap.hitBodyID, g_business);
				g_business = BUSINESS_TYPE::NONE;
			}
		}
		else
		{
			g_businessIcon.SetColor(GetColorCode(COLOR::WHITE));
		}
	}
}

void DrawJengaPlayer(void)
{
	if (g_pBuilding != nullptr)
	{
		const XMINT2 mousePosition = GetMousePosition();
		const XMFLOAT2 drawPosition{ (float)mousePosition.x,(float)mousePosition.y };
		DrawSpriteZoom(drawPosition, g_pBuilding->GetSize(), g_pBuilding->GetRotation(), g_pBuilding->GetTextureID(), g_pBuilding->GetColor());
	}
	if (g_business != BUSINESS_TYPE::NONE)
	{
		const XMINT2 mousePosition = GetMousePosition();
		const XMFLOAT2 drawPosition{ (float)mousePosition.x,(float)mousePosition.y };
		DrawSpriteZoom(drawPosition, g_businessIcon.GetSize(), g_businessIcon.GetRotation(), g_businessIcon.GetTextureID(), g_businessIcon.GetColor());

		const std::wstring text = std::wstring{ L"bodyId : " } + std::to_wstring(g_debugID.index1);
		DrawSpriteText(text, drawPosition);
	}
}

void PlayerGetBuilding(BUILDING_TYPE type)
{
	if (g_pBuilding)
	{
		return;
	}

	switch (type)
	{
	case BUILDING_TYPE::_0:
		g_pBuilding = new Building(g_playerPosition, 0.0f, BUILDING_TYPE::_0);
		g_pBuilding->SetTextureID(LoadTexture(L"asset\\block.png"));
		break;

	case BUILDING_TYPE::_1:
		break;

	case BUILDING_TYPE::_2:
		break;

	default:
		break;
	}
}

void AddMoney(int moneyAdd)
{
	g_money += moneyAdd;
}

void AddEmployee(void)
{
	g_numEmployee++;
}

int GetMoney(void)
{
	return g_money;
}

int GetNumEmployee(void)
{
	return g_numEmployee;
}

void PlayerGetBusiness(BUSINESS_TYPE type)
{
	g_business = type;
}