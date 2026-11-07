/*
* +-------------------------------------+
* File   : [UI_GetEmployee.h]
* Author : ’¾„Œ«
* Date   : 2026/11/03
*
*
* ‰Ÿ‚·‚ÆĞˆõ‚ğŒÙ—p‚·‚é
* +-------------------------------------+
*/
#pragma once

#include"UI.h"
#include"GameObject.h"

class UI_GetEmployee : public UI, public GameObject
{
public:
	UI_GetEmployee(DirectX::XMFLOAT2 position, DirectX::XMFLOAT2 size, float rotation)
		: GameObject(position, size, rotation)
	{

	}

	void Initialize(void) override;
	void Finalize(void) override;
	void Update(void) override;
	void Draw(void) const override;

private:

};