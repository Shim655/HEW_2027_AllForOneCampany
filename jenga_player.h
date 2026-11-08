/*
* +-------------------------------------+
* File   : ÉvÉåÉCÉÑÅ[êßå‰[jenga_player.h]
* Author : íæùÑå´
* Date   : 2026/11/02
*
*
*
* +-------------------------------------+
*/
#pragma once

#include "Building.h"
#include "Business.h"

void InitializeJengaPlayer(void);
void FinalizeJengaPlayer(void);
void UpdateJengaPlayer(void);
void DrawJengaPlayer(void);

void PlayerGetBuilding(BUILDING_TYPE type);
void PlayerGetBusiness(BUSINESS_TYPE type);
void SetPlayerHasEmployee(bool hasOrNot);

void AddMoney(int moneyAdd);
void AddEmployee(void);
int GetMoney(void);
int GetNumEmployee(void);
bool GetPlayerHasEmployee(void);