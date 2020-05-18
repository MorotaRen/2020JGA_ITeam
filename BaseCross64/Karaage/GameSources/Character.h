/*!
@file Character.h
@brief キャラクターなど
*/

#pragma once
#include "stdafx.h"

namespace basecross{
	class BackgroundSprite : public GameObject {
		bool m_Trace;
		Vec2 m_Startscale;
		Vec3 m_Startpos;
		wstring m_Texturekey;
	public:
		BackgroundSprite(const shared_ptr<Stage>& Stageptr, const wstring& Texturekey, bool Trace,
			const Vec2& Startscale, const Vec3& Startpos);
		virtual ~BackgroundSprite();
		virtual void OnCreate() override;
		virtual void OnUpdate()override {}
	};

	class ScoreSprite : public GameObject {
		bool m_Trace;
		Vec2 m_Startscale;
		Vec3 m_Startpos;
		wstring m_Texturekey;
		float m_Score;

		UINT m_Digit;

		vector<VertexPositionTexture> m_BackupVertices;
	public:
		ScoreSprite(const shared_ptr<Stage>& Stageptr, UINT Digit,
			const wstring& Texturekey, bool Trace,
			const Vec2& Startscale, const Vec3& Startpos);
		virtual ~ScoreSprite() {}
		void SetScore(float f) {
			m_Score = f;
		}
		virtual void OnCreate() override;
		virtual void OnUpdate()override;
	};


}
//end basecross
