/*
* +-------------------------------------+
* File   : main[main.h]
* Author : íæùÑå´
* Date   : 2026/10/10
*
*
*
* +-------------------------------------+
*/
#pragma once

#pragma warning(push)
#pragma warning(disable:4005)
#pragma warning(pop)

#define _CRT_SECURE_NO_WARNINGS	//scanfÇÃwarningñhé~
#define DIRECTINPUT_VERSION 0x0800	//åxçêëŒèà

#include <DirectXMath.h>
#include <d3d11.h>
#include <d3dcompiler.h>

#include "dinput.h"
#include "mmsystem.h"	//éûä‘Ç‚ÉTÉEÉìÉh



#define SCREEN_WIDTH	(1280)
#define SCREEN_HEIGHT	(720)

enum class SCENE
{
	NONE,
	TITLE,
	GAME,
	RESULT
};

DirectX::XMFLOAT2 GetWindowSize(void);
void SetScene(SCENE nextScene);
void Transition(SCENE nextScene);