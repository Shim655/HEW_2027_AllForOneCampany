/*
* +-------------------------------------+
* File   : UIŠÇ—E§Œä[UIManager.cpp]
* Author : ’¾„Œ«
* Date   : 2026/11/01
*
*
*
* +-------------------------------------+
*/
#include "main.h"
#include "texture.h"
#include "sprite.h"
#include "color.h"
#include "GameObject.h"
#include "UI_GetBuilding.h"
#include "UI_GetEmployee.h"
#include "UI_GetBusiness.h"
#include "UI_Score.h"
using namespace DirectX;


static GameObject g_backgroundLeft;
static GameObject g_backgroundRight;

static UI* g_UIs[]
{
	new UI_GetEmployee{ XMFLOAT2(100.0f, 100.0f), XMFLOAT2(100.0f, 100.0f), 0.0f },
	new UI_GetBusiness{ XMFLOAT2(100.0f, 350.0f), XMFLOAT2(100.0f, 100.0f), 0.0f },
	new UI_GetBuilding{ XMFLOAT2(100.0f, 550.0f), XMFLOAT2(100.0f, 100.0f), 0.0f },
	new UI_Score{ XMFLOAT2(1050.0f, 30.0f), XMFLOAT2(100.0f, 100.0f), 0.0f },
};

void InitializeUIManager(void)
{
	const XMFLOAT2 backgroundSize = { (float)SCREEN_WIDTH * 0.2f,(float)SCREEN_HEIGHT };
	const XMFLOAT2 backgroundPosition = { backgroundSize.x * 0.5f,(float)SCREEN_HEIGHT * 0.5f };
	g_backgroundLeft.SetPosition({ backgroundPosition.x,backgroundPosition.y });
	g_backgroundRight.SetPosition({ backgroundPosition.x + backgroundSize.x * 4.0f,backgroundPosition.y });
	g_backgroundLeft.SetSize(backgroundSize);
	g_backgroundRight.SetSize(backgroundSize);
	g_backgroundLeft.SetTextureID(LoadTexture(L"asset\\Fade.png"));
	g_backgroundRight.SetTextureID(LoadTexture(L"asset\\Fade.png"));
	g_backgroundLeft.SetColor(GetColorCode(COLOR::BLACK));
	g_backgroundRight.SetColor(GetColorCode(COLOR::BLACK));

	for (UI* UI : g_UIs)
	{
		UI->Initialize();
	}
}

void FinalizeUIManager(void)
{
	for (UI*& UI : g_UIs)
	{
		if (UI)
		{
			UI->Finalize();
			delete UI;
			UI = nullptr;
		}
	}

	ReleaseTexture(g_backgroundLeft.GetTextureID());
	ReleaseTexture(g_backgroundRight.GetTextureID());
}

void UpdateUIManager(void)
{
	for (UI* UI : g_UIs)
	{
		UI->Update();
	}
}

void DrawUIManager(void)
{
	//UI”wŒi
	DrawSprite(g_backgroundLeft.GetPosition(), g_backgroundLeft.GetSize(), 0.0f, g_backgroundLeft.GetTextureID(), g_backgroundLeft.GetColor());
	DrawSprite(g_backgroundRight.GetPosition(), g_backgroundRight.GetSize(), 0.0f, g_backgroundRight.GetTextureID(), g_backgroundRight.GetColor());


	for (UI* UI : g_UIs)
	{
		UI->Draw();
	}
}