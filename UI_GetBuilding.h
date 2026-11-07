/*
* +-------------------------------------+
* File   : [UI_GetBuilding.h]
* Author : ’¾„Œ«
* Date   : 2026/11/01
*
*
* ‰Ÿ‚·‚ÆŒš•¨‚ªo‚éƒ{ƒ^ƒ“
* +-------------------------------------+
*/
#pragma once

#include"UI.h"
#include"GameObject.h"

class UI_GetBuilding : public UI, public GameObject
{
public:
	UI_GetBuilding(DirectX::XMFLOAT2 position, DirectX::XMFLOAT2 size, float rotation)
		: GameObject(position, size, rotation)
	{

	}

	void Initialize(void) override;
	void Finalize(void) override;
	void Update(void) override;
	void Draw(void) const override;

private:

};
