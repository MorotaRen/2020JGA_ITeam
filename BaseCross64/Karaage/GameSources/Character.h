/*!
@file Character.h
@brief キャラクターなど
*/

#pragma once
#include "stdafx.h"

namespace basecross{
	class Customer : public GameObject
	{
		Vec3 m_scale;
		Vec3 m_rotation;
		Vec3 m_position;

		float m_timer;
		//各肉の要求数
		int m_meet[5] = { 0 };

		bool m_clear;

	public :
		Customer(shared_ptr<Stage>&Stage, Vec3 scale, Vec3 rotation, Vec3 position);
		~Customer() {};

		virtual void OnCreate() override;
		virtual void OnUpdate() override;

		float GetTime()
		{
			return m_timer;
		}
		void ClearCheck();
		
		void Update_OrderCount();

		void DeleteGuest();

		void GetRequestMeats(int a[5]){
			a[0] = m_meet[0];//からあげ
			a[1] = m_meet[2];//ドラム
			a[2] = m_meet[4];//ウィング
			a[3] = m_meet[1];//リブ
			a[4] = m_meet[3];//キール
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