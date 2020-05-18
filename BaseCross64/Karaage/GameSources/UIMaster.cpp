#include "stdafx.h"
#include "Project.h"
namespace basecross {
	void MeatUI::OnCreate() {
		float helfSize = 1.0f;
		//頂点配列(縦横5個ずつ表示)	
		vector<VertexPositionColorTexture> vertices = {
			{ VertexPositionColorTexture(Vec3(-helfSize, helfSize, 0),Col4(1.0f,1.0f,1.0f,1.0f), Vec2(0.0f, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(helfSize, helfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(1.0f, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(-helfSize, -helfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(0.0f, 1.0f)) },
			{ VertexPositionColorTexture(Vec3(helfSize, -helfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(1.0f, 1.0f)) },
		};
		//インデックス配列
		vector<uint16_t> indices = { 0, 1, 2, 1, 3, 2 };
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_scale.x, m_scale.y,m_scale.z);
		ptrTrans->SetRotation(0, 0, 0);
		ptrTrans->SetPosition(m_pos.x, m_pos.y, 0.0f);
		//頂点とインデックスを指定してスプライト作成
		auto ptrDraw = AddComponent<PCTSpriteDraw>(vertices, indices);
		ptrDraw->SetTextureResource(m_texkey);
		SetAlphaActive(true);
	}
	void NumberUI::OnCreate() {
		float Range = 0.1f;
		//数字の範囲の生成
		for (int i = 0; i < 10;i++) {
			m_numRects.push_back(
				{
					//左上(left)
					static_cast<float> (0 + (Range * i)),
					//右上(top)
					static_cast<float> (0.1 + (Range * i)),
					//右下(right)
					static_cast<float> (0 + (Range * i)),
					//左下(buttom)
					static_cast<float> (0.1 + (Range * i)),
				}
			);
		}
		//頂点配列(縦横5個ずつ表示)	
		float helfSize = 1.0f;
		vector<VertexPositionColorTexture> vertices = {
			{ VertexPositionColorTexture(Vec3(-helfSize, helfSize, 0),Col4(1.0f,1.0f,1.0f,1.0f), Vec2(m_numRects[0].left, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(helfSize, helfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(m_numRects[0].top, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(-helfSize, -helfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(m_numRects[0].right, 1.0f)) },
			{ VertexPositionColorTexture(Vec3(helfSize, -helfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(m_numRects[0].bottom, 1.0f)) },
		};
		vector<uint16_t> indices = { 0, 1, 2, 1, 3, 2 };
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_scale.x, m_scale.y, m_scale.z);
		ptrTrans->SetRotation(0, 0, 0);
		ptrTrans->SetPosition(m_pos.x, m_pos.y, 0.0f);
		//頂点とインデックスを指定してスプライト作成
		auto ptrDraw = AddComponent<PCTSpriteDraw>(vertices, indices);
		ptrDraw->SetTextureResource(m_texkey);
		SetAlphaActive(true);

	}
}