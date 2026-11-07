/*
* +-------------------------------------+
* File   : [UI_Score.h]
* Author : 沈揆賢
* Date   : 2026/11/03
*
*
* スコア表示
* +-------------------------------------+
*/
#pragma once

#include"UI.h"
#include"GameObject.h"

class UI_Score : public UI, public GameObject
{
public:
	UI_Score(DirectX::XMFLOAT2 position, DirectX::XMFLOAT2 size, float rotation)
		: GameObject(position, size, rotation)
	{

	}

	void Initialize(void) override;
	void Finalize(void) override;
	void Update(void) override;
	void Draw(void) const override;

private:

};
