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
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_Scale);
		ptrTrans->SetPosition(m_Position);
		ptrTrans->SetRotation(m_Rotation);

		auto ptrDraw = AddComponent<PNTStaticDraw>();
		ptrDraw->SetMeshResource(L"DEFAULT_SPHERE");
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
