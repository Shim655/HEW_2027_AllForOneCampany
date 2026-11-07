/*
* +-------------------------------------+
* File   : [EmergencyManager.cpp]
* Author : ’¾„Œ«
* Date   : 2026/11/07
*
*
* ‹Ù‹}–‹Æ‚ğŠÇ—
* +-------------------------------------+
*/


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
	g_isEmergency = false;
}

void FinalizeEmergencyManager(void)
{
}

void UpdateEmergencyManager(void)
{
	if (g_isEmergency == false)
	{
		return;
	}
}

void DrawEmergencyManager(void)
{
	if (g_isEmergency == false)
	{
		return;
	}
}
