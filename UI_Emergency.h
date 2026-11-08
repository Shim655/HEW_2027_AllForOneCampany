/*
* +-------------------------------------+
* File   : [UI_Emergency.h]
* Author : íæùÑå´
* Date   : 2026/11/07
*
*
* ãŸã}éñã∆ÇÃUI
* +-------------------------------------+
*/
#pragma once

#include"UI.h"
#include"GameObject.h"

class UI_Emergency : public UI, public GameObject
{
public:
	UI_Emergency(DirectX::XMFLOAT2 position, DirectX::XMFLOAT2 size, float rotation)
		: GameObject(position, size, rotation)
	{

	}

	void Initialize(void) override;
	void Finalize(void) override;
	void Update(void) override;
	void Draw(void) const override;

private:

};
