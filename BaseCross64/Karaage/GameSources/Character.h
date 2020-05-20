/*!
@file Character.h
@brief �L�����N�^�[�Ȃ�
*/

#pragma once
#include "stdafx.h"

<<<<<<< HEAD
namespace basecross {

	//�X�R�A�̃X�v���C�g
	class ScoreSprite : public GameObject {
		bool m_Trace;
		Vec2 m_Startscale;
		Vec3 m_Startpos;
		wstring m_Texturekey;
		float m_Score;
		UINT m_Truss;//���̐�
		vector<VertexPositionTexture> m_Backupvertices;
	public:
		ScoreSprite(const shared_ptr<Stage>& Stageptr, UINT Truss,
			const wstring& Texturekey, bool Trace,
			const Vec2& Startscale, const Vec3& Startpos);
=======
namespace basecross{
	//--------------------------------------------------------------------------------------
	///	�q�̖{��
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
	///	�q�̃^�C�}�[
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
	///	�q�̒���
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

	//�w�i�̃X�v���C�g
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