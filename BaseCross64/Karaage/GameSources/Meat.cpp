/*!
@file Meat.cpp
@brief 肉用など実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	// 唐揚げ
	Karaage::Karaage(const shared_ptr<Stage>& stagePtr, const Vec3& Scale, const Vec3& Position, const Vec3& Rotation) :
		GameObject(stagePtr),
		m_Scale(Scale),
		m_Position(Position),
		m_Rotation(Rotation)
	{
	}

	void Karaage::OnCreate()
	{
		float helfSize = 0.5f;
		//頂点配列(縦横5個ずつ表示)
		vector<VertexPositionColorTexture> vertices = {
			{ VertexPositionColorTexture(Vec3(-helfSize, helfSize, 0),Col4(1.0f,1.0f,1.0f,1.0f), Vec2(0.0f, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(helfSize, helfSize, 0), Col4(0.0f, 1.0f, 1.0f, 1.0f), Vec2(5.0f, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(-helfSize, -helfSize, 0), Col4(1.0f, 0.0f, 1.0f, 1.0f), Vec2(0.0f, 5.0f)) },
			{ VertexPositionColorTexture(Vec3(helfSize, -helfSize, 0), Col4(0.0f, 0.0f, 0, 1.0f), Vec2(5.0f, 5.0f)) },
		};
		//インデックス配列
		vector<uint16_t> indices = { 0, 1, 2, 1, 3, 2 };
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(MAPCHIP_SIZE_X, MAPCHIP_SIZE_Y, 1.0f);
		ptrTrans->SetRotation(0, 0, 0);
		ptrTrans->SetPosition(m_Position.x, m_Position.y, 0.0f);
		//頂点とインデックスを指定してスプライト作成
		auto ptrDraw = AddComponent<PCTSpriteDraw>(vertices, indices);
		ptrDraw->SetSamplerState(SamplerState::LinearWrap);
		ptrDraw->SetTextureResource(L"RawMeat_Chicken_Line");
	}

	void Karaage::OnUpdate()
	{

	}

	void Karaage::OnUpdate2()
	{
		DrawString();
	}

	// ドラム
	Drum::Drum(const shared_ptr<Stage>& stagePtr, const Vec3& Scale, const Vec3& Position, const Vec3& Rotation) :
		GameObject(stagePtr),
		m_Scale(Scale),
		m_Position(Position),
		m_Rotation(Rotation),
		m_rad(1.57f)
	{
	}

	void Drum::OnCreate()
	{
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_Scale);
		ptrTrans->SetPosition(m_Position);
		ptrTrans->SetRotation(m_Rotation);

		auto ptrDraw = AddComponent<PNTStaticDraw>();
		ptrDraw->SetMeshResource(L"DEFAULT_SPHERE");
	}

	void Drum::OnUpdate()
	{
		Rotation();
	}

	void Drum::Rotation()
	{
		auto KeyState = App::GetApp()->GetInputDevice().GetKeyState();
		auto YRota = GetComponent<Transform>()->GetRotation();
		if (KeyState.m_bPressedKeyTbl['A']) {
			YRota.y = -m_rad;
		}
		else if (KeyState.m_bPressedKeyTbl['D']) {
			YRota.y = +m_rad;
		}
		GetComponent<Transform>()->SetRotation(YRota);

	}

	// 手羽先
	Wing::Wing(const shared_ptr<Stage>& stagePtr, const Vec3& Scale, const Vec3& Position, const Vec3& Rotation) :
		GameObject(stagePtr),
		m_Scale(Scale),
		m_Position(Position),
		m_Rotation(Rotation)
	{
	}

	void Wing::OnCreate()
	{
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_Scale);
		ptrTrans->SetPosition(m_Position);
		ptrTrans->SetRotation(m_Rotation);

		auto ptrDraw = AddComponent<PNTStaticDraw>();
		ptrDraw->SetMeshResource(L"DEFAULT_SPHERE");
	}

	void Wing::OnUpdate()
	{

	}

	// リブ
	Lib::Lib(const shared_ptr<Stage>& stagePtr, const Vec3& Scale, const Vec3& Position, const Vec3& Rotation) :
		GameObject(stagePtr),
		m_Scale(Scale),
		m_Position(Position),
		m_Rotation(Rotation)
	{
	}

	void Lib::OnCreate()
	{
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_Scale);
		ptrTrans->SetPosition(m_Position);
		ptrTrans->SetRotation(m_Rotation);

		auto ptrDraw = AddComponent<PNTStaticDraw>();
		ptrDraw->SetMeshResource(L"DEFAULT_CUBE");
	}

	void Lib::OnUpdate()
	{

	}

	// キール
	Keel::Keel(const shared_ptr<Stage>& stagePtr, const Vec3& Scale, const Vec3& Position, const Vec3& Rotation) :
		GameObject(stagePtr),
		m_Scale(Scale),
		m_Position(Position),
		m_Rotation(Rotation)
	{
	}

	void Keel::OnCreate()
	{
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_Scale);
		ptrTrans->SetPosition(m_Position);
		ptrTrans->SetRotation(m_Rotation);

		auto ptrDraw = AddComponent<PNTStaticDraw>();
		ptrDraw->SetMeshResource(L"DEFAULT_CUBE");
	}

	void Keel::OnUpdate()
	{

	}

	void Karaage::DrawString()
	{
		wstring strRandOder(L"Oder :");
		int Rand = rand() % KaraageOder;
		strRandOder += Util::IntToWStr(Rand);

		wstring str = strRandOder;
		auto ptrString = GetComponent<StringSprite>();
		ptrString->SetText(str);
	}
}
//end basecross
