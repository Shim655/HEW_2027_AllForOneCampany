/*
* +-------------------------------------+
* File   : [EmergencyManager.h]
* Author : ’¾„Œ«
* Date   : 2026/11/07
*
*
* ‹Ù‹}–‹Æ‚ğŠÇ—
* +-------------------------------------+
*/
#pragma once

#include <DirectXMath.h>

void InitializeEmergencyManager(void);
void FinalizeEmergencyManager(void);
void UpdateEmergencyManager(void);
void DrawEmergencyManager(void);

void SetRocket(DirectX::XMFLOAT2 position, DirectX::XMFLOAT2 velocity, float rotation);