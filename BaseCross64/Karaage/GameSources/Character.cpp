/*!
@file Character.cpp
@brief キャラクターなど実体
*/

#include "stdafx.h"
#include "Project.h"
#include "BaseMath.h"

namespace basecross{
	//--------------------------------------------------------------------------------------
	///	客の本体
	//--------------------------------------------------------------------------------------
	Guest::Guest(shared_ptr<Stage>&Stage, Vec3 position)
		: GameObject(Stage),
		m_position(position)
	{
		m_timer = 0;
		m_clear = false;
	}

	void Guest::OnCreate()
	{
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetPosition(m_position);

		auto ptrStage = App::GetApp()->GetScene<Scene>()->GetActiveStage();

		ptrStage->AddGameObject<MultiSprite>(true, Vec2(50, 50), m_position, L"Chara_Normal");
	}

	void Guest::OnUpdate()
	{
		Update_OrderCount();
		ClearCheck();
	}

	void Guest::ClearCheck()
	{
	}

	void Guest::Update_OrderCount() {
	}

	void Guest::DeleteGuest()
	{
		auto stage = App::GetApp()->GetScene<Scene>()->GetActiveStage();

		stage->RemoveGameObject<Guest>(GetThis<Guest>());
		for (int i = 0; i < m_MeetCount.size(); i++) {
			stage->RemoveGameObject<NumberUI>(m_MeetCount[i]);
		}
	}

	//--------------------------------------------------------------------------------------
	///	客のタイマー
	//--------------------------------------------------------------------------------------
	GuestTimerGauge::GuestTimerGauge(shared_ptr<Stage>& Stage, const Vec3 position, bool isFix)
		: GameObject(Stage),
		m_isFix(isFix)
		//m_guest(guest)
	{
		m_timer = 20.0f;

		m_guestPos = position;
	}
	void GuestTimerGauge::OnCreate()
	{
		float HelfSize = 0.5f;
		vector<VertexPositionColorTexture> vertices = {
			{VertexPositionColorTexture(Vec3(-0,HelfSize,0),Col4(1.0f,1.0f,1.0f,1.0f),Vec2(0.0f,0.0f)) },
			{VertexPositionColorTexture(Vec3(HelfSize*2.0f,HelfSize,0),Col4(1.0f,1.0f,1.0f,1.0f),Vec2(1.0f,0.0f))},
			{VertexPositionColorTexture(Vec3(-0,-HelfSize,0),Col4(1.0f,1.0f,1.0f,1.0f),Vec2(0.0f,1.0f)) },
			{VertexPositionColorTexture(Vec3(HelfSize*2.0f,-HelfSize,0),Col4(1.0f,1.0f,1.0f,1.0f),Vec2(1.0f,1.0f))}
		};
		vector<uint16_t> indices = { 0,1,2,1,3,2 };
		auto ptrDraw = AddComponent<PCTSpriteDraw>(vertices, indices);
		ptrDraw->SetSamplerState(SamplerState::LinearWrap);
		SetAlphaActive(true);
		auto ptrTrans = GetComponent<Transform>();
		//ptrTrans->SetPosition(m_position.x, m_position.y, 0.0f);
		SetPosition(m_guestPos);
		if (m_isFix == false) {
			ptrTrans->SetScale(250.0f, 30.0f, 1.0f);
			m_Per = 250.0f / m_timer;
			ptrTrans->SetPivot(0.0f, 0.0f, 0.0f);
			ptrDraw->SetTextureResource(L"TimerGauge_TX");
			SetDrawLayer(149);
		}
		else {
			ptrTrans->SetScale(250.0f, 30.0f, 1.0f);
			ptrDraw->SetTextureResource(L"TimerGaugeFrame_TX");
			SetDrawLayer(150);
		}
		ptrTrans->SetRotation(0.0f, 0.0f, 0.0f);
	}

	void GuestTimerGauge::OnUpdate()
	{
		if (!m_isFix) {
			SetTime();
			ChangeScale();
		}
	}

	void GuestTimerGauge::SetTime()
	{
		m_timer -= App::GetApp()->GetElapsedTime();
		if (m_timer < 0) {
			GetStage()->RemoveGameObject<GuestTimerGauge>(GetThis<GuestTimerGauge>());
		}
	}

	void GuestTimerGauge::ChangeScale()
	{
		//if (m_timer > 0) {
			auto ptrTrans = GetComponent<Transform>();
			auto scale = ptrTrans->GetScale();
			scale.x = m_Per * m_timer;
			ptrTrans->SetScale(scale);
		//}
	}

	void GuestTimerGauge::SetPosition(Vec3 guestPos)
	{
		auto ptrTrans = GetComponent<Transform>();
		Vec3 position = guestPos + Vec3(-125.0f, -50.0f, 0.0f);
		ptrTrans->SetPosition(position);
	}

	//--------------------------------------------------------------------------------------
	///	客の注文
	//--------------------------------------------------------------------------------------
	GuestOrder::GuestOrder(shared_ptr<Stage>&Stage, Vec3 position)
		: GameObject(Stage),
		m_position(position)
	{

	}

	void GuestOrder::OnCreate()
	{

	}

	void GuestOrder::OnUpdate()
	{

	}
}


//end basecross
