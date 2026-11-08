/*
* +-------------------------------------+
* File   : ƒJƒƒ‰§Œä[camera.cpp]
* Author : ’¾„Œ«
* Date   : 2026/11/01
*
*
*
* +-------------------------------------+
*/
#pragma once
#include <DirectXMath.h>


void InitializeCamera(void);
void UpdateCamera(void);

const DirectX::XMFLOAT3& GetCameraOffset(void);
void SetCameraOffset(DirectX::XMFLOAT3 cameraOffset);