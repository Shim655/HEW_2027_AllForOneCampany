/*
* +-------------------------------------+
* File   : 全オブジェクトの基底クラス[GameObject.h]
* Author : 沈揆賢
* Date   : 2026/11/01
*
*
* 位置、サイズ、回転を持たせる
* +-------------------------------------+
*/
#pragma once

#include <DirectXMath.h>
#include <memory>
#include "RigidBody.h"

class GameObject
{
public:
	GameObject() = default;
	GameObject(DirectX::XMFLOAT2 position, DirectX::XMFLOAT2 size, float rotation)
		: m_position{ position }
		, m_size{ size }
		, m_rotation{ rotation }
	{

	}

	bool IsOnMouse(void);
	void Move(void);

	void SetPosition(DirectX::XMFLOAT2 position)
	{
		m_position = position;
	}
	void SetSize(DirectX::XMFLOAT2 size)
	{
		m_size = size;
	}
	void SetVelocity(DirectX::XMFLOAT2 velocity)
	{
		m_velocity = velocity;
	}
	void SetColor(DirectX::XMFLOAT4 color)
	{
		m_color = color;
	}
	void SetRotation(float rotation)
	{
		m_rotation = rotation;
	}
	void SetTextureID(int textureID)
	{
		m_textureID = textureID;
	}
	void SetRigidBody(b2WorldId worldID, float density, float friction, float rotation);

	DirectX::XMFLOAT2 GetPosition(void) const
	{
		return m_position;
	}
	DirectX::XMFLOAT2 GetSize(void) const
	{
		return m_size;
	}
	DirectX::XMFLOAT4 GetColor(void) const
	{
		return m_color;
	}
	float GetRotation(void) const
	{
		return m_rotation;
	}
	int GetTextureID(void) const
	{
		return m_textureID;
	}
	const RigidBody* GetRigidBody(void) const
	{
		return m_rigidBody.get();
	}

private:
	DirectX::XMFLOAT2 m_position{ 0.0f,0.0f };
	DirectX::XMFLOAT2 m_size{ 0.0f,0.0f };
	DirectX::XMFLOAT2 m_velocity{ 0.0f,0.0f };
	DirectX::XMFLOAT4 m_color{ 1.0f,1.0f,1.0f,1.0f };
	float m_rotation{ 0.0f };
	int m_textureID{ -1 };
	std::unique_ptr<RigidBody>m_rigidBody{ nullptr };
};