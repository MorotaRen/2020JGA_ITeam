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
	class Customer : public GameObject
	{
		Vec3 m_scale;
		Vec3 m_rotation;
		Vec3 m_position;

		float m_timer;
		//�e���̗v����
		int m_meet[5] = { 0 };

		bool m_clear;

	public :
		Customer(shared_ptr<Stage>&Stage, Vec3 scale, Vec3 rotation, Vec3 position);
		~Customer() {};

		virtual void OnCreate() override;
		virtual void OnUpdate() override;
<<<<<<< HEAD
=======

		float GetTime()
		{
			return m_timer;
		}
		void ClearCheck();
		
		void Update_OrderCount();

		void DeleteGuest();

		void GetRequestMeats(int a[5]){
			a[0] = m_meet[0];//���炠��
			a[1] = m_meet[2];//�h����
			a[2] = m_meet[4];//�E�B���O
			a[3] = m_meet[1];//���u
			a[4] = m_meet[3];//�L�[��
		}
>>>>>>> Morota_ForHome
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