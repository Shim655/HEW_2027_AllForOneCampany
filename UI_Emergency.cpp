/*
* +-------------------------------------+
* File   : [UI_Emergency.cpp]
* Author : íæùÑå´
* Date   : 2026/11/07
*
*
* ãŸã}éñã∆ÇÃUI
* +-------------------------------------+
*/
#include "UI_Emergency.h"
#include "text.h"
#include "EmergencyManager.h"
using namespace DirectX;

void UI_Emergency::Initialize(void)
{
}

void UI_Emergency::Finalize(void)
{
}

void UI_Emergency::Update(void)
{
}

void UI_Emergency::Draw(void) const
{
	if (GetIsEmergency() == false)
	{
		return;
	}

	const int timeLimit = EMERGENCY_LAST_FRAME / 60;
	const int timeSec = timeLimit - GetEmergencyTimeSec();

	const std::wstring text = std::wstring{ L"00 : " } + std::to_wstring(timeSec / 10) + std::to_wstring(timeSec % 10);
	DrawSpriteText(text, GameObject::GetPosition());
}
