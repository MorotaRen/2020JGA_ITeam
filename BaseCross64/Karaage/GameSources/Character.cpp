/*!
@file Character.cpp
@brief キャラクターなど実体
*/

#include "stdafx.h"
#include "Project.h"
#include "BaseMath.h"

namespace basecross{
	Guest::Guest(shared_ptr<Stage>&Stage, Vec3 scale, Vec3 rotation, Vec3 position)
		: GameObject(Stage),
		m_scale(scale),
		m_rotation(rotation),
		m_position(position)
	{
		m_timer = 0;
		m_clear = false;
	}

	void Guest::OnCreate() 
	{
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_scale);
		ptrTrans->SetRotation(m_rotation);
		ptrTrans->SetPosition(m_position);

		int num = rand() % 5 + 1;

		m_timer = 5.0f * num;

		for (int i = 0; i < num; i++) {
			int meetNum = rand() % 5;

			m_meet[meetNum]++;
		}
	}

	void Guest::OnUpdate()
	{
		auto elapsed = App::GetApp()->GetElapsedTime();
		m_timer -= elapsed;
	}

	/*----------------------------------------------------------------*/
	// 客用タイマー
	/*----------------------------------------------------------------*/
	GuestTimerGauge::GuestTimerGauge(shared_ptr<Stage>& Stage, const Vec2 position, bool isFix)
		: GameObject(Stage),
		m_position(position),
		m_isFix(isFix)
		//m_guest(guest)
	{
		m_timer = 20.0f;
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
		ptrTrans->SetPosition(m_position.x, m_position.y, 0.0f);
		if (m_isFix == false) {
			ptrTrans->SetScale(250.0f, 15.0f, 1.0f);
			m_Per = 250.0f / 20.0f;
			ptrTrans->SetPivot(0.0f, 0.0f, 0.0f);
			ptrDraw->SetTextureResource(L"TimerGauge_TX");
			SetDrawLayer(150);
		}
		else {
			ptrTrans->SetScale(363.0f, 260.0f, 1.0f);
			ptrDraw->SetTextureResource(L"TimerGaugeFrame_TX");
			SetDrawLayer(149);
		}
		ptrTrans->SetRotation(0.0f, 0.0f, 0.0f);
	}

	void GuestTimerGauge::OnUpdate()
	{
		SetTime();
		ChangeScale();
	}

	void GuestTimerGauge::SetTime()
	{
		m_timer -= App::GetApp()->GetElapsedTime();
	}

	void GuestTimerGauge::ChangeScale()
	{
		if (m_timer > 0) {
			auto ptrTrans = GetComponent<Transform>();
			auto scale = ptrTrans->GetScale();
			scale.x = m_Per * m_timer;
			ptrTrans->SetScale(scale);
		}
	}
}
//end basecross
