/*!
@file Character.h
@brief キャラクターなど
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	///	客の本体
	//--------------------------------------------------------------------------------------
	class Guest : public GameObject
	{
		Vec3 m_position;

		float m_timer;
		vector<shared_ptr<GameObject>> m_TimerPtr = { 0,0 };

		vector<shared_ptr<GameObject>> m_CharaImage = { 0 };

		int m_meet[5] = { 0 };

		bool m_clear;

		Vec2 m_numberPos[5];
		vector<shared_ptr<GameObject>> m_MeetCount = { 0,0,0,0,0 };
		vector<Rect2D<float>> m_numRects = vector<Rect2D<float>>(10);

		bool m_active;

	public :
		Guest(shared_ptr<Stage>&Stage, Vec3 position);
		~Guest() {};

		virtual void OnCreate() override;
		virtual void OnUpdate() override;

		float GetTime()
		{
			return m_timer;
		}
		void ClearCheck();
		
		void Update_OrderCount();

		void DeleteGuest();

		void SetTimer();

		bool GetActive() {
			return m_active;
		}
	};

	//--------------------------------------------------------------------------------------
	///	客のタイマー
	//--------------------------------------------------------------------------------------
	class GuestTimerGauge : public GameObject
	{
		Vec3 m_guestPos;
		Vec2 m_scale;
		bool m_isFix;
		float m_timer;
		float m_Per;

		//Guest m_guest;
	public:
		GuestTimerGauge(shared_ptr<Stage>& Stage, const Vec3 position, bool isFix);
		GuestTimerGauge(shared_ptr<Stage>& Stage, const Vec3 position, bool isFix, float time);
		virtual ~GuestTimerGauge() {};
		virtual void OnCreate()override;
		virtual void OnUpdate() override;
		//void Damage();
		void SetTime();
		void ChangeScale();
		void SetPosition(Vec3 guestPos);
	};

	//--------------------------------------------------------------------------------------
	///	客の注文
	//--------------------------------------------------------------------------------------
	class GuestOrder : public GameObject
	{
		Vec2 m_position;
		Vec2 m_scale;
		
	public :
		GuestOrder(shared_ptr<Stage>&Stage, Vec3 position);
		~GuestOrder() {};
		virtual void OnCreate()override;
		virtual void OnUpdate()override;

	};
}

//end basecross