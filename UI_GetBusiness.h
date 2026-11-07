/*
* +-------------------------------------+
* File   : [UI_GetBusiness.h]
* Author : ’¾„Œ«
* Date   : 2026/11/05
*
*
* ‰Ÿ‚·‚Æ–‹Æ‚ğƒQƒbƒg‚·‚é
* +-------------------------------------+
*/
#pragma once

#include"UI.h"
#include"GameObject.h"

class UI_GetBusiness : public UI, public GameObject
{
public:
	UI_GetBusiness(DirectX::XMFLOAT2 position, DirectX::XMFLOAT2 size, float rotation)
		: GameObject(position, size, rotation)
	{

	}

	void Initialize(void) override;
	void Finalize(void) override;
	void Update(void) override;
	void Draw(void) const override;

private:

};