/*!
@file Character.h
@brief �L�����N�^�[�Ȃ�
*/

#pragma once
#include "stdafx.h"

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