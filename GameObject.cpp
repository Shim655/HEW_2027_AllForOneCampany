/*
* +-------------------------------------+
* File   : 全オブジェクトの基底クラス[GameObject.cpp]
* Author : 沈揆賢
* Date   : 2026/11/01
*
*
* 位置、サイズ、回転を持たせる
* +-------------------------------------+
*/
#include "GameObject.h"
#include "mouse.h"
using namespace DirectX;


bool GameObject::IsOnMouse(void)
{
	const float top = m_position.y - m_size.y;
	const float bottom = m_position.y + m_size.y;
	const float left = m_position.x - m_size.x;
	const float right = m_position.x + m_size.x;

	const XMINT2 mousePosition = GetMousePosition();
	const float x = (float)mousePosition.x;
	const float y = (float)mousePosition.y;

	if (y<top || y>bottom)
	{
		return false;
	}
	if (x<left || x>right)
	{
		return false;
	}
	return true;
}

void GameObject::Move(void)
{
	m_position = { m_position.x + m_velocity.x,m_position.y + m_velocity.y };
}

void GameObject::SetRigidBody(b2WorldId worldID, float density, float friction, float rotation)
{
	m_rigidBody = std::make_unique<RigidBody>();

	b2BodyDef rigidBody = b2DefaultBodyDef();
	rigidBody.type = b2_dynamicBody;
	rigidBody.position = { m_position.x,m_position.y };
	rigidBody.rotation = b2MakeRot(rotation);
	m_rigidBody->SetBodyID(b2CreateBody(worldID, &rigidBody));

	b2ShapeDef shape = b2DefaultShapeDef();
	shape.density = density;
	shape.material.friction = friction;

	b2Polygon boxPolygon = b2MakeBox(m_size.x * 0.5f, m_size.y * 0.5f);

	b2CreatePolygonShape(m_rigidBody->GetBodyID(), &shape, &boxPolygon);
}
