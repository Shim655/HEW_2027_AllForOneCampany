/*
* +-------------------------------------+
* File   : [JengaManager.cpp]
* Author : 沈揆賢
* Date   : 2026/11/02
*
*
* ジェンガ
* 建物を積み上げる処理
* 物理エンジンを実装
* +-------------------------------------+
*/
#include <box2d.h>
#include "JengaManager.h"
#include "main.h"
#include "sprite.h"
#include "texture.h"
#include "camera.h"
#include "keyboard.h"
#include "Building.h"
#include "GameObject.h"
using namespace DirectX;

static constexpr int MAX_BUILDINGS = 1000;


//b2World_OverlapShape()関数に渡す
//当たった物体を探した時の処理
bool OverlapCallback(b2ShapeId shapeID, void* context);


static GameObject g_ground({ (float)SCREEN_WIDTH / 2.0f, 720.0f }, { 2000.0f,300.0f }, 3.14f);
static Building* g_pBuildings[MAX_BUILDINGS]{ nullptr };

//Box2D
static b2WorldId g_worldID;
static b2BodyId g_groundID;

static bool g_isGroundShake{ false };
static float g_groundShakeTime{ 0.0f };
static float g_groundShakePower{ 0.0f };
static int g_groundShakeFrame{ 0 };

void InitializeJengaManager(void)
{
	//-------------------------------------
	//ここからBox2Dを使った物理エンジンの設定
	//Worldを作成
	b2WorldDef world;
	world = b2DefaultWorldDef();
	world.gravity = { 0.0f,100.0f };
	g_worldID = b2CreateWorld(&world);

	//地面を作成
	b2BodyDef ground = b2DefaultBodyDef();
	ground.type = b2_kinematicBody;
	ground.position = { (float)SCREEN_WIDTH / 2.0f, 720.0f };
	g_groundID = b2CreateBody(g_worldID, &ground);

	b2ShapeDef groundShape = b2DefaultShapeDef();
	groundShape.material.friction = 0.5f; //地面の摩擦
	b2Polygon groundBox = b2MakeBox(1000.0f, 150.0f);
	b2CreatePolygonShape(g_groundID, &groundShape, &groundBox);


	//ここまで
	//-------------------------------------


	g_ground.SetTextureID(LoadTexture(L"asset\\block.png"));
	g_isGroundShake = false;
	g_groundShakeTime = 0.0f;
	g_groundShakePower = 0.0f;
	g_groundShakeFrame = 0;
}

void FinalizeJengaManager(void)
{
	//物理エンジンのWorldを破壊
	b2DestroyWorld(g_worldID);


	for (int i = 0;i < MAX_BUILDINGS;i++)
	{
		if (g_pBuildings[i])
		{
			delete g_pBuildings[i];
			g_pBuildings[i] = nullptr;
		}
	}
}

void UpdateJengaManager(void)
{
	for (Building* building : g_pBuildings)
	{
		if (building == nullptr)
		{
			continue;
		}
		
		building->Update();
	}


	if (Keyboard_IsKeyTrigger(KK_SPACE))
	{
		//g_groundShakePower = 1000.0f;
	}

	g_groundShakeTime += 1.0f;
	if (g_groundShakeTime > 1000.0f)
	{
		g_groundShakeTime = 0.0f;
	}
	g_groundShakePower -= 10.0f;
	if (g_groundShakePower < 0.0f)
	{
		g_groundShakePower = 0.0f;
	}
	else
	{
		const b2Vec2 velocity = { sinf(g_groundShakeTime) * g_groundShakePower ,0.0f };
		b2Body_SetLinearVelocity(g_groundID, velocity);
	}



	//物理のシミュレーション
	//更新フレーム
	const float timeStep = 1.0f / 60.0f;//60fps

	//シミュレーションする回数
	//数字が高いほどリアルになるが、処理が重くなる
	const int subStepCount = 6;

	b2World_Step(g_worldID, timeStep, subStepCount);
}

void DrawJengaManager(void)
{
	//地面
	const b2Pos groundPosition = b2Body_GetPosition(g_groundID);

	DrawSpriteScroll(
		{ groundPosition.x,groundPosition.y }, g_ground.GetSize(), g_ground.GetRotation(),
		g_ground.GetTextureID(), g_ground.GetColor());

	//ビル
	for (int i = 0;i < MAX_BUILDINGS;i++)
	{
		if (g_pBuildings[i] == nullptr)
		{
			continue;
		}

		const RigidBody* rigidBody = g_pBuildings[i]->GetRigidBody();

		DrawSpriteScroll(
			rigidBody->GetPosition(), g_pBuildings[i]->GetSize(), rigidBody->GetRotation(),
			g_pBuildings[i]->GetTextureID(), g_pBuildings[i]->GetColor());
	}
}

void SetJenga(const Building* building)
{
	for (int i = 0;i < MAX_BUILDINGS;i++)
	{
		if (g_pBuildings[i])
		{
			continue;
		}


		const XMFLOAT2 setPosition = building->GetPosition();
		const float rotation = building->GetRotation();

		switch (building->GetBuildingType())
		{
		case BUILDING_TYPE::_0:
			g_pBuildings[i] = new Building(setPosition, 0.0f, BUILDING_TYPE::_0);
			g_pBuildings[i]->SetTextureID(LoadTexture(L"asset\\block.png"));
			g_pBuildings[i]->SetRigidBody(g_worldID, 1.0f, 0.5f, rotation);
			break;

		case BUILDING_TYPE::_1:
			break;

		case BUILDING_TYPE::_2:
			break;

		default:
			break;
		}

		break;
	}
}

const OverLapContext& CheckJengaOverlap(XMFLOAT2 position, XMFLOAT2 size, float rotation)
{
	//仮想の物体を作成
	b2Polygon box = b2MakeBox(size.x * 0.5f, size.y * 0.5f);
	b2ShapeProxy proxy = b2MakeOffsetProxy(
		box.vertices, box.count, box.radius,
		{ position.x,position.y }, b2MakeRot(rotation));

	//フィルター
	b2QueryFilter filter = b2DefaultQueryFilter();

	//当たり判定の結果
	OverLapContext result;

	//当たり判定を行う
	b2World_OverlapShape(
		g_worldID,
		{ 0.0f,0.0f },
		&proxy,
		filter,
		OverlapCallback,
		&result);


	return result;
}

bool OverlapCallback(b2ShapeId shapeID, void* context)
{
	//当たった物体を発見
	OverLapContext* result = static_cast<OverLapContext*>(context);
	result->hit = true;
	result->hitBodyID = b2Shape_GetBody(shapeID);

	//発見したら終了
	return false;
}

void SetJengaBusiness(b2BodyId bodyID, BUSINESS_TYPE type)
{
	for (Building* building : g_pBuildings)
	{
		if (building == nullptr)
		{
			continue;
		}
		if (building->GetRigidBody()->GetBodyID().index1 != bodyID.index1)
		{
			continue;
		}

		building->SetBusiness(type);

		break;
	}
}

void ShakeJenga(void)
{
	g_groundShakePower = 1000.0f;
}