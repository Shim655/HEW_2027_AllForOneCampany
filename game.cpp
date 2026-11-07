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
#include "player.h"
#include "JengaManager.h"
#include "UIManager.h"
using namespace DirectX;



void InitializeGame(void)
{
	InitializeJengaManager();
	InitializePlayer();
	InitializeUIManager();
}

void FinalizeGame(void)
{
	FinalizeJengaManager();
	FinalizePlayer();
	FinalizeUIManager();
}

void UpdateGame(void)
{
	UpdateJengaManager();
	UpdatePlayer();
	UpdateUIManager();
}

void DrawGame(void)
{
	DrawJengaManager();
	DrawUIManager();
	DrawPlayer();
}
