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

		m_numberPos[0] = Vec2(position.x - 65.0f, position.y + 55.0f);
		m_numberPos[1] = Vec2(position.x - 65.0f, position.y + 20.0f);
		m_numberPos[2] = Vec2(position.x - 65.0f, position.y - 15.0f);
		m_numberPos[3] = Vec2(position.x + 40.0f, position.y + 55.0f);
		m_numberPos[4] = Vec2(position.x + 40.0f, position.y + 20.0f);

		m_active = true;
	}

	void Guest::OnCreate() 
	{
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetPosition(m_position);

		int num = rand() % 5 + 1;

		m_timer = 5.0f * num;

		for (int i = 0; i < num; i++) {
			int meetNum = rand() % 5;

			m_meet[meetNum]++;
		}

		auto ptrStage = App::GetApp()->GetScene<Scene>()->GetActiveStage();

		m_CharaImage[0] = ptrStage->AddGameObject<MultiSprite>(true, Vec2(300, 150), m_position, L"Guest1_TX");
		m_TimerPtr[0] = ptrStage->AddGameObject<GuestTimerGauge>(m_position, false);
		m_TimerPtr[1] = ptrStage->AddGameObject<GuestTimerGauge>(m_position, true);

		for (int i = 0; i < m_MeetCount.size(); i++) {
			m_MeetCount[i] = ptrStage->AddGameObject<NumberUI>(m_numberPos[i], Vec3(15.0f, 15.0f, 1.0f), L"Tex_Number");
		}

		int countNum = 0;
		for (int i = 0; i < 5; i++) {
			countNum += m_meet[i];
			if(i != 5)
			countNum *= 10;
		}
		FlyMaster::GetInstans().Set_Num(countNum, m_MeetCount);
	}

	void Guest::OnUpdate()
	{
		SetTimer();
		Update_OrderCount();
		ClearCheck();
	}

	void Guest::ClearCheck()
	{
		for (int i = 0; i < 5; i++) {
			if (m_meet[i] == 0) {
				if (i == 4) {
					m_clear = true;
					DeleteGuest();
				}
			}
			else {
				break;
			}
		}
	}

	void Guest::Update_OrderCount() {
		int countNum = 0;
		for (int i = 0; i < 5; i++) {
			countNum += m_meet[i];
			if (i != 5)
				countNum *= 10;
		}
		FlyMaster::GetInstans().Set_Num(countNum, m_MeetCount);
	}

	void Guest::DeleteGuest()
	{
		auto stage = App::GetApp()->GetScene<Scene>()->GetActiveStage();

		stage->RemoveGameObject<Guest>(GetThis<Guest>());
		stage->RemoveGameObject<MultiSprite>(m_CharaImage[0]);
		stage->RemoveGameObject<GuestTimerGauge>(m_TimerPtr[0]);
		stage->RemoveGameObject<GuestTimerGauge>(m_TimerPtr[1]);
		for (int i = 0; i < m_MeetCount.size(); i++) {
			stage->RemoveGameObject<NumberUI>(m_MeetCount[i]);
		}

		m_active = false;
	}

	void Guest::SetTimer()
	{
		auto elapsed = App::GetApp()->GetElapsedTime();
		m_timer -= elapsed;

		if (m_timer < 0) {
			DeleteGuest();
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
			//SetTime();
			ChangeScale();
		}
	}

	void GuestTimerGauge::SetTime(float time)
	{
		m_timer = time;
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
