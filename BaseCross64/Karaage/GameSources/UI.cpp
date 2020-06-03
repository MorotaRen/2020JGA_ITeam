/*!
@file UI.cpp
@brief UI
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	///	通常のスプライト
	//--------------------------------------------------------------------------------------
	MultiSprite::MultiSprite(const shared_ptr<Stage>& StagePtr, bool Trace, const Vec2& StartScale, const Vec3& StartPos, wstring TextureKey) :
		GameObject(StagePtr),
		m_trace(Trace),
		m_startScale(StartScale),
		m_startPos(StartPos),
		m_textureKey(TextureKey)
	{}
	MultiSprite::~MultiSprite(){}

	void MultiSprite::OnCreate() {
		float halfSize = 0.5f;
		//頂点配列
		m_backupVertices = {
			{ VertexPositionTexture(Vec3(-halfSize, halfSize, 0), Vec2(0.0f, 0.0f)) },
			{ VertexPositionTexture(Vec3(halfSize, halfSize, 0), Vec2(1.0f, 0.0f)) },
			{ VertexPositionTexture(Vec3(-halfSize, -halfSize, 0), Vec2(0.0f, 1.0f)) },
			{ VertexPositionTexture(Vec3(halfSize, -halfSize, 0), Vec2(1.0f, 1.0f)) },
		};
		//インデックス配列
		vector<uint16_t> indices = { 0,1,2,1,3,2 };
		SetAlphaActive(m_trace);
		auto ptrTransform = GetComponent<Transform>();
		ptrTransform->SetScale(m_startScale.x, m_startScale.y, 1.0f);
		ptrTransform->SetRotation(0, 0, 0);
		ptrTransform->SetPosition(m_startPos.x, m_startPos.y, 0.0f);
		//頂点とインデックスを指定してスプライト作成
		auto ptrDraw = AddComponent<PTSpriteDraw>(m_backupVertices, indices);
		ptrDraw->SetTextureResource(m_textureKey);
		this->SetDrawLayer(1);
	}

	//--------------------------------------------------------------------------------------
	///	フェード
	//--------------------------------------------------------------------------------------

	//フェードイン

	FadeInSprite::FadeInSprite(const shared_ptr<Stage>& StagePtr,bool Trance,const Vec2& StageScale,const Vec3& StartPos,wstring TextureKey)
		:MultiSprite(StagePtr,Trance,StageScale,StartPos,TextureKey)
	{}
	FadeInSprite::~FadeInSprite() {}
	void FadeInSprite::OnCreate() {
		MultiSprite::OnCreate();
	}
	void FadeInSprite::OnUpdate() {
		auto ptrDraw = GetComponent<PTSpriteDraw>();
		auto diff = ptrDraw->GetDiffuse();
		ptrDraw->SetDiffuse(Col4(diff.x, diff.y, diff.z, diff.w - App::GetApp()->GetElapsedTime()/5));
	}

	//フェードアウト

	FadeOutSprite::FadeOutSprite(const shared_ptr<Stage>& StagePtr, bool Trance, const Vec2& StageScale, const Vec3& StartPos, wstring TextureKey)
		:MultiSprite(StagePtr, Trance, StageScale, StartPos, TextureKey)
	{}
	FadeOutSprite::~FadeOutSprite() {}
	/*bool fldFade() {
		GameManager::GetGM()->
	}*/
	void FadeOutSprite::OnCreate() {
		MultiSprite::OnCreate();
		auto ptrDraw = GetComponent<PTSpriteDraw>();
		ptrDraw->SetDiffuse(Col4(1.0f, 1.0f, 1.0f, 0.0f));

	}
	void FadeOutSprite::OnUpdate() {
		auto ptrDraw = GetComponent<PTSpriteDraw>();
		auto diff = ptrDraw->GetDiffuse();
		ptrDraw->SetDiffuse(Col4(diff.x, diff.y, diff.z, diff.w + App::GetApp()->GetElapsedTime()));
		if (diff.w > 1.0f) {
		}
	}


	//--------------------------------------------------------------------------------------
	/// フェードイン・アウトをするスプライト
	//--------------------------------------------------------------------------------------

	FadeInAndOutSprite::FadeInAndOutSprite(const shared_ptr<Stage>& StagePtr, const Vec2& StageScale, const Vec3& StartPos, wstring TextureKey, float FadeInTime, float DrawTime, float FadeOutTime)
		:MultiSprite(StagePtr, true, StageScale, StartPos, TextureKey)
	{
		m_inOut.InTime = FadeInTime;
		m_inOut.DrawTime = DrawTime;
		m_inOut.OutTime = FadeOutTime;

		m_isInEnd = false;
		m_isDrawEnd = false;
		m_isOutEnd = false;
	}

	void FadeInAndOutSprite::OnCreate() {
		MultiSprite::OnCreate();
		auto ptrDraw = GetComponent<PTSpriteDraw>();
		ptrDraw->SetDiffuse(Col4(1.0f, 1.0f, 1.0f, 0.0f));
	}

	void FadeInAndOutSprite::OnUpdate() {
		FadeIn();
		SpriteDraw();
		FadeOut();
		if (m_isDrawEnd == true && m_isInEnd == true && m_isOutEnd == true) {
			GetStage()->RemoveGameObject<FadeInAndOutSprite>(GetThis<FadeInAndOutSprite>());
		}
	}

	void FadeInAndOutSprite::FadeIn() {
		if (m_isInEnd == false) {
			auto alpha = m_inOut.GetInAlpha();
			auto ptrDraw = GetComponent<PTSpriteDraw>();
			auto Diff = ptrDraw->GetDiffuse();
			Diff.w += alpha;
			ptrDraw->SetDiffuse(Diff);
			if (Diff.w >= 1.0f) {
				m_isInEnd = true;
			}
		}
	}
	void FadeInAndOutSprite::SpriteDraw() {
		if (m_isDrawEnd == false && m_isInEnd == true) {
			if (m_inOut.frameCount < m_inOut.DrawTime) {
				m_inOut.frameCount += App::GetApp()->GetElapsedTime();
			}
			else {
				m_isDrawEnd = true;
			}
		}
	}

	void FadeInAndOutSprite::FadeOut() {
		if (m_isOutEnd == false && m_isDrawEnd == true && m_isInEnd == true) {
			auto alpha = m_inOut.GetOutAlpha();
			auto ptrDraw = GetComponent<PTSpriteDraw>();
			auto Diff = ptrDraw->GetDiffuse();
			Diff.w -= alpha;
			ptrDraw->SetDiffuse(Diff);
			if (Diff.w <= 0.0f) {
				m_isOutEnd = true;
			}
		}
	}
	//--------------------------------------------------------------------------------------
	///	拡大縮小するスプライト
	//--------------------------------------------------------------------------------------
	ScaleMoveSprite::ScaleMoveSprite(const shared_ptr<Stage>& StagePtr, bool Trace, const Vec2& StartScale, const Vec2& StartPos, const wstring& TextureKey) :
		GameObject(StagePtr),
		m_trace(Trace),
		m_startScale(StartScale),
		m_startPos(StartPos),
		m_textureKey(TextureKey)
	{
		m_speed = 1.0f;
		m_maxScale = Vec3(118.0f, 118.0f, 1.0f);
		m_onePer = m_maxScale / 100;
	}

	void ScaleMoveSprite::OnCreate() {
		float helfSize = 1.0f;
		//頂点配列(1個表示)
		vector<VertexPositionColorTexture> vertices = {
			{ VertexPositionColorTexture(Vec3(-helfSize, helfSize, 0),Col4(1.0f,1.0f,1.0f,1.0f), Vec2(0.0f, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(helfSize, helfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(1.0f, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(-helfSize, -helfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(0.0f, 1.0f)) },
			{ VertexPositionColorTexture(Vec3(helfSize, -helfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(1.0f, 1.0f)) },
		};
		//インデックス配列
		vector<uint16_t> indices = { 0, 1, 2, 1, 3, 2 };
		SetAlphaActive(m_trace);
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_startScale.x, m_startScale.y, 1.0f);
		ptrTrans->SetRotation(0, 0, 0);
		ptrTrans->SetPosition(m_startPos);
		//頂点とインデックスを指定してスプライト作成
		auto ptrDraw = AddComponent<PCTSpriteDraw>(vertices, indices);
		ptrDraw->SetSamplerState(SamplerState::LinearWrap);
		ptrDraw->SetTextureResource(m_textureKey);
		this->AddComponent<Action>();
	}

	void ScaleMoveSprite::OnUpdate() {
		ScaleMoveProcess();
	}

	void ScaleMoveSprite::ScaleMoveProcess() {
	}

}