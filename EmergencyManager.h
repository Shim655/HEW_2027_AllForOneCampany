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

constexpr int EMERGENCY_LAST_FRAME = 60 * 30;//30•b

void InitializeEmergencyManager(void);
void FinalizeEmergencyManager(void);
void UpdateEmergencyManager(void);
void DrawEmergencyManager(void);

bool GetIsEmergency(void);
int GetEmergencyTimeSec(void);
void SetEmergencyTrue(void);
void SetRocket(DirectX::XMFLOAT2 position, DirectX::XMFLOAT2 velocity, float rotation);