/*
* +-------------------------------------+
* File   : ÉvÉåÉCÉÑÅ[êßå‰[player.h]
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

void InitializePlayer(void);
void FinalizePlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);

void PlayerGetBuilding(BUILDING_TYPE type);
void PlayerGetBusiness(BUSINESS_TYPE type);

void AddMoney(int moneyAdd);
void AddEmployee(void);
int GetMoney(void);
int GetNumEmployee(void);