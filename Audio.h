/*
* +-------------------------------------+
* File   : ‰¹Ä¶ƒNƒ‰ƒX[Audio.h]
* Author : ’¾„Œ«
* Date   : 2026/10/11
*
*
*
* +-------------------------------------+
*/
#pragma once

class Audio
{
public:
	Audio() = default;
	Audio(const char* fileName);

	void Initialize(const char* fileName);
	void PlaySE(float volume) const;
	void PlayBGM(float volume) const;
	void StopBGM(void) const;

private:
	int m_soundID{ 0 };
};

void SetAllVolume(float volume);
