//Box2Dライブラリーライセンス
/*
MIT License

Copyright (c) 2022 Erin Catto

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

*/

/*
* +-------------------------------------+
* File   : [JengaManager.h]
* Author : 沈揆賢
* Date   : 2026/11/02
*
*
* ジェンガ
* 建物を積み上げる処理
* 物理エンジンを実装
* +-------------------------------------+
*/
#pragma once

#include <DirectXMath.h>
#include "Building.h"

//Box2DのWorldの外でWorld内の物体との
//当たり判定の結果を保存する構造体
struct OverLapContext
{
	bool hit{ false };
	b2BodyId hitBodyID{};
};

void InitializeJengaManager(void);
void FinalizeJengaManager(void);
void UpdateJengaManager(void);
void DrawJengaManager(void);

void SetJenga(const Building* building);
void SetJengaBusiness(b2BodyId bodyID, BUSINESS_TYPE type);
const OverLapContext& CheckJengaOverlap(DirectX::XMFLOAT2 position, DirectX::XMFLOAT2 size, float rotation);

void ShakeJenga(void);