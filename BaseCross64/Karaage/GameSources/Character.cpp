/*!
@file Character.cpp
@brief キャラクターなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
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
		float helfSize = 0.5f;
		//頂点配列(縦横5個ずつ表示)
		vector<VertexPositionColorTexture> vertices = {
			{ VertexPositionColorTexture(Vec3(-helfSize,  helfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(0.0f, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(helfSize,  helfSize, 0), Col4(0.0f, 1.0f, 1.0f, 1.0f), Vec2(5.0f, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(-helfSize, -helfSize, 0), Col4(1.0f, 0.0f, 1.0f, 1.0f), Vec2(0.0f, 5.0f)) },
			{ VertexPositionColorTexture(Vec3(helfSize, -helfSize, 0), Col4(0.0f, 0.0f, 0.0f, 1.0f), Vec2(5.0f, 5.0f)) },
		};
		//インデックス配列
		vector<uint16_t> indices = { 0, 1, 2, 1, 3, 2 };
		SetAlphaActive(m_Trace);
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_Startscale.x, m_Startscale.y, 1.0f);
		ptrTrans->SetRotation(0, 0, 0);
		ptrTrans->SetPosition(m_Startpos);
		//頂点とインデックスを指定してスプライト作成
		auto ptrDraw = AddComponent<PCTSpriteDraw>(vertices, indices);
		ptrDraw->SetSamplerState(SamplerState::LinearWrap);
		ptrDraw->SetTextureResource(m_Texturekey);
	}

	ScoreSprite::ScoreSprite(const shared_ptr<Stage>& Stageptr, UINT Digit,
		const wstring& Texturekey, bool Trace,
		const Vec2& Startscale, const Vec3& Startpos) :
		GameObject(Stageptr),
		m_Digit(Digit),
		m_Texturekey(Texturekey),
		m_Trace(Trace),
		m_Startscale(Startscale),
		m_Startpos(Startpos),
		m_Score(0.0f)
	{}

	void ScoreSprite::OnCreate() {
		float Xpiecesize = 1.0f / (float)m_Digit;
		float Helfsize = 0.5f;

		//インデックス配列
		vector<uint16_t> indices;
		for (UINT i = 0; i < m_Digit; i++) {
			float vertex0 = -Helfsize + Xpiecesize * (float)i;
			float vertex1 = vertex0 + Xpiecesize;
			//0
			m_BackupVertices.push_back(
				VertexPositionTexture(Vec3(vertex0, Helfsize, 0), Vec2(0.0f, 0.0f)));
			//1
			m_BackupVertices.push_back(
				VertexPositionTexture(Vec3(vertex1, Helfsize, 0), Vec2(0.1f, 0.0f)));
			//2
			m_BackupVertices.push_back(
				VertexPositionTexture(Vec3(vertex0, -Helfsize, 0), Vec2(0.0f, 1.0f)));
			//3
			m_BackupVertices.push_back(
				VertexPositionTexture(Vec3(vertex1, -Helfsize, 0), Vec2(0.1f, 1.0f)));
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
		ptrTrans->SetRotation(0, 0, 0);
		ptrTrans->SetPosition(m_Startpos.x, m_Startpos.y, 0.0f);

		auto ptrDraw = AddComponent<PTSpriteDraw>(m_BackupVertices, indices);
		ptrDraw->SetTextureResource(m_Texturekey);
		GetStage()->SetSharedGameObject(L"ScoreSprite", GetThis<ScoreSprite>());
	}

	void ScoreSprite::OnUpdate() {
		vector<VertexPositionTexture> newVertices;
		UINT num;
		int verNum = 0;
		for (UINT i = m_Digit; i > 0; i--) {
			UINT base = (UINT)pow(10, i);
			num = ((UINT)m_Score) % base;
			num = num / (base / 10);
			Vec2 uv0 = m_BackupVertices[verNum].textureCoordinate;
			uv0.x = (float)num / 10.0f;
			auto v = VertexPositionTexture(
				m_BackupVertices[verNum].position,
				uv0
			);
			newVertices.push_back(v);

			Vec2 uv1 = m_BackupVertices[verNum + 1].textureCoordinate;
			uv1.x = uv0.x + 0.1f;
			v = VertexPositionTexture(
				m_BackupVertices[verNum + 1].position,
				uv1
			);
			newVertices.push_back(v);

			Vec2 uv2 = m_BackupVertices[verNum + 2].textureCoordinate;
			uv2.x = uv0.x;

			v = VertexPositionTexture(
				m_BackupVertices[verNum + 2].position,
				uv2
			);
			newVertices.push_back(v);

			Vec2 uv3 = m_BackupVertices[verNum + 3].textureCoordinate;
			uv3.x = uv0.x + 0.1f;

			v = VertexPositionTexture(
				m_BackupVertices[verNum + 3].position,
				uv3
			);
			newVertices.push_back(v);

			verNum += 4;
		}
		auto ptrDraw = GetComponent<PTSpriteDraw>();
		ptrDraw->UpdateVertices(newVertices);
	}

}
//end basecross
