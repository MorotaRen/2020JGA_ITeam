/*!
@file Character.cpp
@brief キャラクターなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//スコアのスプライト
	ScoreSprite::ScoreSprite(const shared_ptr<Stage>& Stageptr, UINT Truss,
		const wstring& Texturekey, bool Trace,
		const Vec2& Startscale, const Vec3& Startpos) :
		GameObject(Stageptr),
		m_Truss(Truss),
		m_Texturekey(Texturekey),
		m_Trace(Trace),
		m_Startscale(Startscale),
		m_Startpos(Startpos),
		m_Score(0.0f)
	{}

	void ScoreSprite::OnCreate() {
		float Xpiecesize = 1.0f / (float)m_Truss;
		float Helfsize = 0.5f;

		vector<uint16_t> indices;
		for (UINT i = 0; i < m_Truss; i++) {
			float vertex0 = -Helfsize + Xpiecesize * (float)i;
			float vertex1 = vertex0 + Xpiecesize;

			//0
			m_Backupvertices.push_back(
				VertexPositionTexture(Vec3(vertex0, Helfsize, 0.0f), Vec2(0.0f, 0.0f))
			);
			//1
			m_Backupvertices.push_back(
				VertexPositionTexture(Vec3(vertex1, Helfsize, 0.0f), Vec2(0.1f, 0.0f))
			);
			//2
			m_Backupvertices.push_back(
				VertexPositionTexture(Vec3(vertex0, -Helfsize, 0.0f), Vec2(0.0f, 1.0f))
			);
			//3
			m_Backupvertices.push_back(
				VertexPositionTexture(Vec3(vertex1, -Helfsize, 0.0f), Vec2(0.1f, 1.0f))
			);

			indices.push_back(i * 4 + 0);
			indices.push_back(i * 4 + 1);
			indices.push_back(i * 4 + 2);
			indices.push_back(i * 4 + 1);
			indices.push_back(i * 4 + 3);
			indices.push_back(i * 4 + 2);
		}

		SetAlphaActive(m_Trace);
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_Startscale.x, m_Startscale.y, 1.0f);
		ptrTrans->SetRotation(0.0f, 0.0f, 0.0f);
		ptrTrans->SetPosition(m_Startpos.x, m_Startpos.y, 0.0f);

		auto ptrDraw = AddComponent<PTSpriteDraw>(m_Backupvertices, indices);
		ptrDraw->SetTextureResource(m_Texturekey);
		GetStage()->SetSharedGameObject(L"ScoreSprite", GetThis<ScoreSprite>());
	}

	void ScoreSprite::OnUpdate() {
		vector<VertexPositionTexture> newVertices;
		UINT Num;
		int Vernum = 0;
		for (UINT i = m_Truss; i > 0; i--) {
			UINT base = (UINT)pow(10, i);
			Num = ((UINT)m_Score) % base;
			Num = Num / (base / 10);
			Vec2 uv0 = m_Backupvertices[Vernum].textureCoordinate;
			uv0.x = (float)Num / 10.0f;
			auto v = VertexPositionTexture(
				m_Backupvertices[Vernum].position,
				uv0
			);
			newVertices.push_back(v);

			Vec2 uv1 = m_Backupvertices[Vernum + 1].textureCoordinate;
			uv1.x = uv0.x + 0.1f;
			v = VertexPositionTexture(
				m_Backupvertices[Vernum + 1].position,
				uv1
			);
			newVertices.push_back(v);

			Vec2 uv2 = m_Backupvertices[Vernum + 2].textureCoordinate;
			uv2.x = uv0.x;

			v = VertexPositionTexture(
				m_Backupvertices[Vernum + 2].position,
				uv2
			);
			newVertices.push_back(v);

			Vec2 uv3 = m_Backupvertices[Vernum + 3].textureCoordinate;
			uv3.x = uv0.x + 0.1f;

			v = VertexPositionTexture(
				m_Backupvertices[Vernum + 3].position,
				uv3
			);
			newVertices.push_back(v);

			Vernum += 4;
		}
		auto ptrDraw = GetComponent<PTSpriteDraw>();
		ptrDraw->UpdateVertices(newVertices);
	}

	//背景のスプライト
	BackgroundSprite::BackgroundSprite(const shared_ptr<Stage>& Stageptr, const wstring& Texturekey, bool Trace,
		const Vec2& Startscale, const Vec3& Startpos) :
		GameObject(Stageptr),
		m_Texturekey(Texturekey),
		m_Trace(Trace),
		m_Startscale(Startscale),
		m_Startpos(Startpos)
	{}

	BackgroundSprite::~BackgroundSprite() {}
	void BackgroundSprite::OnCreate() {
		float Helfsize = 0.5f;

		vector<VertexPositionColorTexture> vertices = {
			{VertexPositionColorTexture(Vec3( -Helfsize,  Helfsize, 0),Col4(1.0f,1.0f,1.0f,1.0f),Vec2(0.0f, 0.0f)) },
			{VertexPositionColorTexture(Vec3(  Helfsize,  Helfsize, 0),Col4(0.0f,1.0f,1.0f,1.0f),Vec2(5.0f, 0.0f)) },
			{VertexPositionColorTexture(Vec3( -Helfsize, -Helfsize, 0),Col4(1.0f,0.0f,1.0f,1.0f),Vec2(0.0f, 5.0f)) },
			{VertexPositionColorTexture(Vec3( -Helfsize, -Helfsize, 0),Col4(0.0f,0.0f,0.0f,1.0f),Vec2(5.0f, 5.0f)) }
		};

		vector<uint16_t> indices = { 0, 1, 2, 1, 3, 2 };
		SetAlphaActive(m_Trace);
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_Startscale.x, m_Startscale.y, 1.0f);
		ptrTrans->SetRotation(0, 0, 0);
		ptrTrans->SetPosition(m_Startpos);

		auto ptrDraw = AddComponent<PCTSpriteDraw>(vertices, indices);
		ptrDraw->SetSamplerState(SamplerState::LinearWrap);
		ptrDraw->SetTextureResource(m_Texturekey);
	}
}


//end basecross
