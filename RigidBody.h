/*
* +-------------------------------------+
* File   : [RigidBody.h]
* Author : 沈揆賢
* Date   : 2026/11/01
*
*
* Box2D用のオブジェクト
* +-------------------------------------+
*/
#pragma once

#include <box2d.h>
#include <DirectXMath.h>


class RigidBody
{
public:
	void SetBodyID(b2BodyId bodyID)
	{
		m_bodyID = bodyID;
	}

	b2BodyId GetBodyID(void) const
	{
		return m_bodyID;
	}
	DirectX::XMFLOAT2 GetPosition(void) const
	{
		const b2Vec2 position = b2Body_GetPosition(m_bodyID);
		return { position.x,position.y };
	}
	float GetRotation(void) const
	{
		const float rotation = b2Rot_GetAngle(b2Body_GetRotation(m_bodyID));
		return rotation;
	}

private:
	b2BodyId m_bodyID;
};