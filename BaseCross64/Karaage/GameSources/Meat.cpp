/*!
@file Meat.cpp
@brief 肉用など実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//--------------------------唐揚げ--------------------------//
	Karaage::Karaage(const shared_ptr<Stage>& stagePtr, const Vec3& Scale, const Vec3& Position, const Quat& quat) :
		GameObject(stagePtr),
		m_Scale(Scale),
		m_Position(Position),
		m_Quat(quat)
	{
	}

	void Karaage::OnCreate()
	{
		float helfSize = 0.5f;
		//頂点配列(縦横5個ずつ表示)	
		vector<VertexPositionColorTexture> vertices = {
			{ VertexPositionColorTexture(Vec3(-helfSize, helfSize, 0),Col4(1.0f,1.0f,1.0f,1.0f), Vec2(0.0f, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(helfSize, helfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(0.35f, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(-helfSize, -helfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(0.0f, 0.35f)) },
			{ VertexPositionColorTexture(Vec3(helfSize, -helfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(0.35f, 0.35f)) },
		};
		//インデックス配列
		vector<uint16_t> indices = { 0, 1, 2, 1, 3, 2 };
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(MAPCHIP_SIZE_X , MAPCHIP_SIZE_Y, 1.0f);
		ptrTrans->SetQuaternion(m_Quat);
		ptrTrans->SetPosition(m_Position.x, m_Position.y, 0.0f);
		//頂点とインデックスを指定してスプライト作成
		auto ptrDraw = AddComponent<PCTSpriteDraw>(vertices, indices);
		ptrDraw->SetTextureResource(L"RawMeat_Chicken_Line");
		SetAlphaActive(true);
		
	}

	void Karaage::OnUpdate()
	{

	}

	void Karaage::OnUpdate2()
	{
	}

	//------------------------------------------------------------------------------//

	//--------------------------ドラム--------------------------//
	Drum::Drum(const shared_ptr<Stage>& stagePtr, const Vec3& Scale, const Vec3& Position, const Quat& quat) :
		GameObject(stagePtr),
		m_Scale(Scale),
		m_Position(Position),
		m_Quat(quat),
		m_rad(1.57f)
	{
	}

	void Drum::OnCreate()
	{
		float helfSize = 0.5f;
		//頂点配列(縦横5個ずつ表示)
		vector<VertexPositionColorTexture> vertices = {
			{ VertexPositionColorTexture(Vec3(-helfSize, helfSize, 0),Col4(1.0f,1.0f,1.0f,1.0f), Vec2(0.0f, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(helfSize, helfSize , 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(1.0f, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(-helfSize, -helfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(0.0f, 1.0f)) },
			{ VertexPositionColorTexture(Vec3(helfSize, -helfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(1.0f, 1.0f)) },
		};
		//インデックス配列
		vector<uint16_t> indices = { 0, 1, 2, 1, 3, 2 };
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(MAPCHIP_SIZE_X * 2, MAPCHIP_SIZE_Y * 2, 1.0f);
		ptrTrans->SetQuaternion(m_Quat);
		ptrTrans->SetPosition(m_Position.x + 30, m_Position.y - 30, 0.0f);
		//頂点とインデックスを指定してスプライト作成
		auto ptrDraw = AddComponent<PCTSpriteDraw>(vertices, indices);
		ptrDraw->SetTextureResource(L"RawMeat_Drum_Line");

		SetAlphaActive(true);
	}

	void Drum::OnUpdate()
	{
	}

	//------------------------------------------------------------------------------//

	//--------------------------手羽先--------------------------//
	Wing::Wing(const shared_ptr<Stage>& stagePtr, const Vec3& Scale, const Vec3& Position, const Quat& quat) :
		GameObject(stagePtr),
		m_Scale(Scale),
		m_Position(Position),
		m_Quat(quat)
	{
	}

	void Wing::OnCreate()
	{
		float helfSize = 0.5f;
		//頂点配列(縦横5個ずつ表示)
		vector<VertexPositionColorTexture> vertices = {
			{ VertexPositionColorTexture(Vec3(-helfSize, helfSize, 0),Col4(1.0f,1.0f,1.0f,1.0f), Vec2(0.0f, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(helfSize, helfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(1.0f, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(-helfSize, -helfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(0.0f, 1.0f)) },
			{ VertexPositionColorTexture(Vec3(helfSize, -helfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(1.0f, 1.0f)) },
		};
		//インデックス配列
		vector<uint16_t> indices = { 0, 1, 2, 1, 3, 2 };
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(MAPCHIP_SIZE_X * 2, MAPCHIP_SIZE_Y * 2, 1.0f);
		ptrTrans->SetQuaternion(m_Quat);
		ptrTrans->SetPosition(m_Position.x + 30, m_Position.y - 30, 0.0f);
		//頂点とインデックスを指定してスプライト作成
		auto ptrDraw = AddComponent<PCTSpriteDraw>(vertices, indices);
		ptrDraw->SetTextureResource(L"RawMeat_Wing_Line");
		SetAlphaActive(true);
	}

	void Wing::OnUpdate()
	{

	}
	//------------------------------------------------------------------------------//

	//--------------------------リブ--------------------------//
	Rib::Rib(const shared_ptr<Stage>& stagePtr, const Vec3& Scale, const Vec3& Position, const Quat& quat) :
		GameObject(stagePtr),
		m_Scale(Scale),
		m_Position(Position),
		m_Quat(quat)
	{
	}

	void Rib::OnCreate()
	{
		float helfSize = 0.5f;
		//頂点配列(縦横5個ずつ表示)
		vector<VertexPositionColorTexture> vertices = {
			{ VertexPositionColorTexture(Vec3(-helfSize, helfSize, 0),Col4(1.0f,1.0f,1.0f,1.0f), Vec2(0.0f, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(helfSize, helfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(1.0f, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(-helfSize, -helfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(0.0f, 1.0f)) },
			{ VertexPositionColorTexture(Vec3(helfSize, -helfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(1.0f, 1.0f)) },
		};
		//インデックス配列
		vector<uint16_t> indices = { 0, 1, 2, 1, 3, 2 };
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(MAPCHIP_SIZE_X * 2, MAPCHIP_SIZE_Y * 2, 1.0f);
		ptrTrans->SetQuaternion(m_Quat);
		ptrTrans->SetPosition(m_Position.x + 40, m_Position.y - 40, 0.0f);
		//頂点とインデックスを指定してスプライト作成
		auto ptrDraw = AddComponent<PCTSpriteDraw>(vertices, indices);
		ptrDraw->SetTextureResource(L"RawMeat_Rib_Line");
		SetAlphaActive(true);
	}

	void Rib::OnUpdate()
	{

	}
	//------------------------------------------------------------------------------//

	//--------------------------キール--------------------------//
	Keel::Keel(const shared_ptr<Stage>& stagePtr, const Vec3& Scale, const Vec3& Position, const Quat& quat) :
		GameObject(stagePtr),
		m_Scale(Scale),
		m_Position(Position),
		m_Quat(quat)
	{
	}

	void Keel::OnCreate()
	{
		float helfSize = 0.5f;
		//頂点配列(縦横5個ずつ表示)
		vector<VertexPositionColorTexture> vertices = {
			{ VertexPositionColorTexture(Vec3(-helfSize, helfSize, 0),Col4(1.0f,1.0f,1.0f,1.0f), Vec2(0.0f, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(helfSize, helfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(1.0f, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(-helfSize, -helfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(0.0f, 1.0f)) },
			{ VertexPositionColorTexture(Vec3(helfSize, -helfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(1.0f, 1.0f)) },
		};
		//インデックス配列
		vector<uint16_t> indices = { 0, 1, 2, 1, 3, 2 };
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(MAPCHIP_SIZE_X * 3, MAPCHIP_SIZE_Y * 3, 1.0f);
		ptrTrans->SetQuaternion(m_Quat);
		ptrTrans->SetPosition(m_Position.x + 60, m_Position.y - 60, 0.0f);
		//頂点とインデックスを指定してスプライト作成
		auto ptrDraw = AddComponent<PCTSpriteDraw>(vertices, indices);
		ptrDraw->SetTextureResource(L"RawMeat_Keel_Line");

		SetAlphaActive(true);
	}
	
	void Keel::OnUpdate()
	{

	}
	
}
//end basecross
