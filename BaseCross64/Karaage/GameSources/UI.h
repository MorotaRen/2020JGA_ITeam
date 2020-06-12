/*!
@file UI.h
@brief UI関連
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	///	通常スプライト
	//--------------------------------------------------------------------------------------
	class MultiSprite : public GameObject {
		bool m_trace;
		Vec2 m_startScale;
		Vec3 m_startPos;
		wstring m_textureKey;

		//バックアップ頂点データ
		vector<VertexPositionTexture> m_backupVertices;

	public:
		MultiSprite(const shared_ptr<Stage>& StagePtr, bool Trace,
			const Vec2& StartScale, const Vec3& StartPos, wstring TextureKey);
		virtual ~MultiSprite();
		virtual void OnCreate() override;
		virtual void OnUpdate() override {}
		void ChangeTexture(wstring Name) {
			GetComponent<PTSpriteDraw>()->SetTextureResource(Name);
		}

	};

	//--------------------------------------------------------------------------------------
	///	フェード
	//--------------------------------------------------------------------------------------

	//フェードイン
	class FadeInSprite :public MultiSprite {
		bool m_trace;
		Vec2 m_startScale;
		Vec3 m_startPos;
		wstring m_textureKey;
	public:
		FadeInSprite(const shared_ptr<Stage>& StagePtr, bool Trace,
			const Vec2& StartScale, const Vec3& StartPos, wstring TextureKey);
		void SetPostion(float x, float y)
		{
			auto transComp = GetComponent<Transform>();

			auto width = App::GetApp()->GetGameWidth();
			auto height = App::GetApp()->GetGameHeight();
			transComp->SetPosition(x - width / 2, -y + height / 2, 0);
		}
		virtual ~FadeInSprite();
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
	};

	//フェードアウト
	class FadeOutSprite : public MultiSprite {
		bool m_trace;
		Vec2 m_startScale;
		Vec3 m_startPos;
		wstring m_textureKey;
	public:
		FadeOutSprite(const shared_ptr<Stage>& StagePtr, bool Trace,
			const Vec2& StartScale, const Vec3& StartPos, wstring TextureKey);
		void SetPostion(float x, float y)
		{
			auto transComp = GetComponent<Transform>();

			auto width = App::GetApp()->GetGameWidth();
			auto height = App::GetApp()->GetGameHeight();
			transComp->SetPosition(x - width / 2, -y + height / 2, 0);
		}
		virtual~FadeOutSprite();
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
	};
	 

	struct FadeInOut
	{
		float InTime;
		float DrawTime;
		float OutTime;
		float frameCount = 0.0f;

		void FrameCountReset() {
			frameCount = 0.0f;
		}
		float GetInAlpha() {
			float alpha = (1.0f / InTime) / 60.0f;
			return alpha;
		}
		float GetOutAlpha() {
			float alpha = (1.0f / InTime) / 60.0f;
			return alpha;
		}
	};

	class FadeInAndOutSprite : public MultiSprite {
		Vec3 m_pos;
		Vec3 m_scale;
		wstring m_textureKey;
		bool m_isInEnd;
		bool m_isDrawEnd;
		bool m_isOutEnd;
		FadeInOut m_inOut;
		 
	public:
		// スケール, ポジション, フェードインの時間, 描画しておく時間 ,フェードアウトの時間
		FadeInAndOutSprite(const shared_ptr<Stage>& StagePtr,
			const Vec2& StartScale, const Vec3& StartPos, wstring TextureKey, float InTime, float DrawTime, float OutTime);
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		void FadeIn();
		void SpriteDraw();
		void FadeOut();
	};
	//--------------------------------------------------------------------------------------
	///	拡大縮小するスプライト
	//--------------------------------------------------------------------------------------
	class ScaleMoveSprite : public GameObject {
		bool m_trace;
		Vec2 m_startScale;
		Vec3 m_startPos;
		wstring m_textureKey;
		float m_speed;
		Vec3 m_maxScale;
		Vec3 m_onePer;
		float m_tmpPer;
	public:
		// 構築と破棄
		ScaleMoveSprite(const shared_ptr<Stage>& StagePtr,bool Trace,
			const Vec2& StartScale, const Vec2& StartPos, const wstring& TextureKey);
		virtual ~ScaleMoveSprite() {}

		//初期化
		virtual void OnCreate() override;
		//更新
		virtual void OnUpdate() override;

		void ScaleMoveProcess();

	};
}