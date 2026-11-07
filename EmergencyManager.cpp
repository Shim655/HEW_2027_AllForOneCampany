/*
* +-------------------------------------+
* File   : [EmergencyManager.cpp]
* Author : ’¾„Œ«
* Date   : 2026/11/07
*
*
* ‹Ù‹}Ž–‹Æ‚ðŠÇ—
* +-------------------------------------+
*/
#include "main.h"
#include "sprite.h"
#include "texture.h"
#include "camera.h"
#include "keyboard.h"
#include "Inseki.h"
#include "Rocket.h"
#include "JengaManager.h"
#include "emergency_player.h"
using namespace DirectX;


enum class EMERGENCY_STATE
{
	NONE,
	READY,
	ACTION,
	END
};

static constexpr int MAX_INSEKI = 1;
static constexpr int MAX_ROCKET = 100;

void CreateRandomInseki(void);


static Inseki* g_insekis[MAX_INSEKI]{ nullptr };
static Rocket* g_rockets[MAX_ROCKET]{ nullptr };
static int g_insekiTexture{ -1 };
static int g_rocketTexture{ -1 };

static EMERGENCY_STATE g_state{ EMERGENCY_STATE::NONE };
static bool g_isEmergency{ false };

bool GetIsEmergency(void)
{
	return g_isEmergency;
}

void SetEmergencyTrue(void)
{
	g_isEmergency = true;
}

void InitializeEmergencyManager(void)
{
	g_state = EMERGENCY_STATE::NONE;
	g_isEmergency = false;

	g_insekiTexture = LoadTexture(L"asset\\Inseki.png");
	g_rocketTexture = LoadTexture(L"asset\\rocket.png");

	//Player
	InitializeEmergencyPlayer();
}

void FinalizeEmergencyManager(void)
{
	for (Inseki*& inseki : g_insekis)
	{
		if (inseki)
		{
			delete inseki;
			inseki = nullptr;
		}
	}
	for (Rocket*& rocket : g_rockets)
	{
		if (rocket)
		{
			delete rocket;
			rocket = nullptr;
		}
	}

	ReleaseTexture(g_insekiTexture);
	ReleaseTexture(g_rocketTexture);

	//Player
	FinalizeEmergencyPlayer();
}

void UpdateEmergencyManager(void)
{
#ifdef _DEBUG
	if (Keyboard_IsKeyTrigger(KK_E))
	{
		g_state = EMERGENCY_STATE::ACTION;
	}
#endif // DEBUG


	switch (g_state)
	{
	case EMERGENCY_STATE::NONE:
		break;

	case EMERGENCY_STATE::READY:
		break;

	case EMERGENCY_STATE::ACTION:
		UpdateEmergencyPlayer();
		CreateRandomInseki();
		//Rocket
		for (Rocket*& rocket : g_rockets)
		{
			if (rocket == nullptr)
			{
				continue;
			}
			if (rocket->GetPosition().y < -100.0f)
			{
				delete rocket;
				rocket = nullptr;
				continue;
			}

			//“–‚½‚è”»’è
			for (Inseki*& inseki : g_insekis)
			{
				if (inseki == nullptr)
				{
					continue;
				}

				const XMFLOAT2 rocketPosition = rocket->GetPosition();
				const XMFLOAT2 insekiPosition = inseki->GetPosition();
				const float distance =
					(rocketPosition.x - insekiPosition.x) * (rocketPosition.x - insekiPosition.x) +
					(rocketPosition.y - insekiPosition.y) * (rocketPosition.y - insekiPosition.y);

				const float c = rocket->GetRadius() + inseki->GetRadius();
				if (distance <= c * c)
				{
					delete rocket;
					rocket = nullptr;

					delete inseki;
					inseki = nullptr;

					break;
				}
			}

			if (rocket)
			{
				rocket->Move();
			}
		}

		//è¦Î
		for (Inseki*& inseki : g_insekis)
		{
			if (inseki == nullptr)
			{
				continue;
			}
			if (inseki->GetPosition().y > 700.0f)
			{
				ShakeJenga();

				delete inseki;
				inseki = nullptr;
				continue;
			}

			inseki->Move();
		}

		break;

	case EMERGENCY_STATE::END:
		break;

	default:
		break;
	}
}

void DrawEmergencyManager(void)
{
	switch (g_state)
	{
	case EMERGENCY_STATE::NONE:
		break;

	case EMERGENCY_STATE::READY:
		break;

	case EMERGENCY_STATE::ACTION:
		DrawEmergencyPlayer();

		//Rocket
		for (Rocket* rocket : g_rockets)
		{
			if (rocket == nullptr)
			{
				continue;
			}

			DrawSprite(rocket->GetPosition(), rocket->GetSize(), rocket->GetRotation(), g_rocketTexture);
		}
		//è¦Î
		for (Inseki* inseki : g_insekis)
		{
			if (inseki == nullptr)
			{
				continue;
			}

			DrawSprite(inseki->GetPosition(), inseki->GetSize(), inseki->GetRotation(), g_insekiTexture);
		}

		break;

	case EMERGENCY_STATE::END:
		break;

	default:
		break;
	}
}

void SetRocket(XMFLOAT2 position, XMFLOAT2 velocity, float rotation)
{
	for (Rocket*& rocket : g_rockets)
	{
		if (rocket)
		{
			continue;
		}

		rocket = new Rocket(position, { 100.0f,100.0f }, 40.0f);
		rocket->SetVelocity(velocity);
		rocket->SetRotation(rotation);

		break;
	}
}

void CreateRandomInseki(void)
{
	const int createPossibility = rand() % 500;
	if (createPossibility > 1)
	{
		//return;
	}

	const float randomPositionX = rand() % 701 + 300.0f;//300~1000
	const XMFLOAT2 position = { randomPositionX,0.0f };
	const XMFLOAT2 velocity = { 0.0f,2.0f };

	for (Inseki*& inseki : g_insekis)
	{
		if (inseki)
		{
			continue;
		}

		inseki = new Inseki(position, { 100.0f,100.0f }, 40.0f);
		inseki->SetVelocity(velocity);

		return;
	}
}