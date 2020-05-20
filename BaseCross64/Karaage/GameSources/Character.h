/*!
@file Character.h
@brief キャラクターなど
*/

#pragma once
#include "stdafx.h"

<<<<<<< HEAD
namespace basecross {

	//スコアのスプライト
	class ScoreSprite : public GameObject {
		bool m_Trace;
		Vec2 m_Startscale;
		Vec3 m_Startpos;
		wstring m_Texturekey;
		float m_Score;
		UINT m_Truss;//桁の数
		vector<VertexPositionTexture> m_Backupvertices;
	public:
		ScoreSprite(const shared_ptr<Stage>& Stageptr, UINT Truss,
			const wstring& Texturekey, bool Trace,
			const Vec2& Startscale, const Vec3& Startpos);
=======
namespace basecross{
	//--------------------------------------------------------------------------------------
	///	客の本体
	//--------------------------------------------------------------------------------------
	class Guest : public GameObject
	{
		Vec3 m_position;

		float m_timer;
		int m_meet[5] = { 0 };

		bool m_clear;

	public :
		Guest(shared_ptr<Stage>&Stage, Vec3 position);
		~Guest() {};

		virtual void OnCreate() override;
		virtual void OnUpdate() override;

		float GetTime()
		{
			return m_timer;
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
		wstring m_meetName;
		
	public :
		GuestOrder(shared_ptr<Stage>&Stage, Vec3 position, wstring meetName);
		~GuestOrder() {};
		virtual void OnCreate()override;
		virtual void OnUpdate()override;

	};
>>>>>>> 2895b5c7c1f47d7f320016e98c96fb843d98e27d

		virtual ~ScoreSprite() {}

		void SetScore(float f) {
			m_Score = f;
		}

		virtual void OnCreate() override;
		virtual void OnUpdate() override;

	};

	//背景のスプライト
	class BackgroundSprite : public GameObject {
		bool m_Trace;
		Vec2 m_Startscale;
		Vec3 m_Startpos;
		wstring m_Texturekey;
	public:
		BackgroundSprite(const shared_ptr<Stage>& Stageptr, const wstring& Texturekey, bool Trace,
			const Vec2& Startscale, const Vec3& Startpos);

		virtual ~BackgroundSprite();

		virtual void OnCreate()override;
		virtual void OnUpdate()override;
	};
}

//end basecross