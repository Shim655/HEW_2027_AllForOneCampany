/*
* +-------------------------------------+
* File   : âπçƒê∂ÉNÉâÉX[Audio.cpp]
* Author : íæùÑå´
* Date   : 2026/10/11
*
*
*
* +-------------------------------------+
*/
#include "Audio.h"
#include "sound.h"

static float g_volume{ 1.0f };
static float g_volumeSE{ 1.0f };
static float g_volumeBGM{ 1.0f };

void SetAllVolume(float volume)
{
	g_volume = volume;
}

Audio::Audio(const char* fileName)
{
	m_soundID = LoadSound(fileName);
}

void Audio::Initialize(const char* fileName)
{
	m_soundID = LoadSound(fileName);
}

void Audio::PlaySE(float volume) const
{
	PlaySound(m_soundID, 0);
	SetVolume(m_soundID, volume * g_volume);
}

void Audio::PlayBGM(float volume) const
{
	PlaySound(m_soundID, -1);
	SetVolume(m_soundID, volume * g_volume);
}

void Audio::StopBGM(void) const
{
	StopSound(m_soundID);
}
