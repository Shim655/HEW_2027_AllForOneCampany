/*
* +-------------------------------------+
* File   : ƒQ[ƒ€ƒV[ƒ“[game.cpp]
* Author : ’¾„Œ«
* Date   : 2026/10/11
*
*
*
* +-------------------------------------+
*/
#include "main.h"
#include "jenga_player.h"
#include "JengaManager.h"
#include "UIManager.h"
#include "EmergencyManager.h"
using namespace DirectX;



void InitializeGame(void)
{
	InitializeJengaManager();
	InitializeJengaPlayer();
	InitializeUIManager();
	InitializeEmergencyManager();
}

void FinalizeGame(void)
{
	FinalizeJengaManager();
	FinalizeJengaPlayer();
	FinalizeUIManager();
	FinalizeEmergencyManager();
}

void UpdateGame(void)
{
	UpdateJengaManager();
	UpdateJengaPlayer();
	UpdateUIManager();
	UpdateEmergencyManager();
}

void DrawGame(void)
{
	DrawJengaManager();
	DrawEmergencyManager();
	DrawUIManager();
	DrawJengaPlayer();
}
