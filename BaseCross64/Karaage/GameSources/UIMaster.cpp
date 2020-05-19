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
					static_cast<float> (0.1f + (Range * i)),
					//右下(right)
					static_cast<float> (0 + (Range * i)),
					//左下(buttom)
					static_cast<float> (0.1f + (Range * i)),
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
	
	void NumberUI::Set_Num(int num) {
		//最大6桁かな…(100,000)
		int tempnum[6] = { 0 };
		//一桁ずつ取って格納
		tempnum[0] = (num % 10);num /= 10;//1
		tempnum[1] = (num % 10);num /= 10;//2
		tempnum[2] = (num % 10);num /= 10;//3
		tempnum[3] = (num % 10);num /= 10;//4
		tempnum[4] = (num % 10);num /= 10;//5
		tempnum[5] = (num % 10);num /= 10;//6
	}
	void NumberUI::Update_num() {
		for (int i = 0; i < 6;i++) {
			
		}
	}
	void NumberUI::Set_Rect(int num,shared_ptr<GameObject> numobj) {
		vector<VertexPositionColorTexture> vertices;
		switch (num)
		{
		case 0:
			vertices.push_back(VertexPositionColorTexture(Vec3(-1.0f, 1.0f, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(m_numRects[0].left, 0.0f)));
			vertices.push_back(VertexPositionColorTexture(Vec3(1.0f, 1.0f, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(m_numRects[0].top, 0.0f)));
			vertices.push_back(VertexPositionColorTexture(Vec3(-1.0f, -1.0f, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(m_numRects[0].right, 1.0f)));
			vertices.push_back(VertexPositionColorTexture(Vec3(1.0f, -1.0f, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(m_numRects[0].bottom, 1.0f)));
			numobj->GetComponent<PCTSpriteDraw>()->UpdateVertices(vertices);
			break;
		case 1:
			vertices.push_back(VertexPositionColorTexture(Vec3(-1.0f, 1.0f, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(m_numRects[1].left, 0.0f)));
			vertices.push_back(VertexPositionColorTexture(Vec3(1.0f, 1.0f, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(m_numRects[1].top, 0.0f)));
			vertices.push_back(VertexPositionColorTexture(Vec3(-1.0f, -1.0f, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(m_numRects[1].right, 1.0f)));
			vertices.push_back(VertexPositionColorTexture(Vec3(1.0f, -1.0f, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(m_numRects[1].bottom, 1.0f)));
			numobj->GetComponent<PCTSpriteDraw>()->UpdateVertices(vertices);
			break;
		case 2:
			vertices.push_back(VertexPositionColorTexture(Vec3(-1.0f, 1.0f, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(m_numRects[2].left, 0.0f)));
			vertices.push_back(VertexPositionColorTexture(Vec3(1.0f, 1.0f, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(m_numRects[2].top, 0.0f)));
			vertices.push_back(VertexPositionColorTexture(Vec3(-1.0f, -1.0f, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(m_numRects[2].right, 1.0f)));
			vertices.push_back(VertexPositionColorTexture(Vec3(1.0f, -1.0f, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(m_numRects[2].bottom, 1.0f)));
			numobj->GetComponent<PCTSpriteDraw>()->UpdateVertices(vertices);
			break;
		case 3:
			vertices.push_back(VertexPositionColorTexture(Vec3(-1.0f, 1.0f, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(m_numRects[3].left, 0.0f)));
			vertices.push_back(VertexPositionColorTexture(Vec3(1.0f, 1.0f, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(m_numRects[3].top, 0.0f)));
			vertices.push_back(VertexPositionColorTexture(Vec3(-1.0f, -1.0f, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(m_numRects[3].right, 1.0f)));
			vertices.push_back(VertexPositionColorTexture(Vec3(1.0f, -1.0f, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(m_numRects[3].bottom, 1.0f)));
			numobj->GetComponent<PCTSpriteDraw>()->UpdateVertices(vertices);
			break;
		case 4:
			vertices.push_back(VertexPositionColorTexture(Vec3(-1.0f, 1.0f, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(m_numRects[4].left, 0.0f)));
			vertices.push_back(VertexPositionColorTexture(Vec3(1.0f, 1.0f, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(m_numRects[4].top, 0.0f)));
			vertices.push_back(VertexPositionColorTexture(Vec3(-1.0f, -1.0f, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(m_numRects[4].right, 1.0f)));
			vertices.push_back(VertexPositionColorTexture(Vec3(1.0f, -1.0f, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(m_numRects[4].bottom, 1.0f)));
			numobj->GetComponent<PCTSpriteDraw>()->UpdateVertices(vertices);
			break;
		case 5:
			vertices.push_back(VertexPositionColorTexture(Vec3(-1.0f, 1.0f, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(m_numRects[5].left, 0.0f)));
			vertices.push_back(VertexPositionColorTexture(Vec3(1.0f, 1.0f, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(m_numRects[5].top, 0.0f)));
			vertices.push_back(VertexPositionColorTexture(Vec3(-1.0f, -1.0f, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(m_numRects[5].right, 1.0f)));
			vertices.push_back(VertexPositionColorTexture(Vec3(1.0f, -1.0f, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(m_numRects[5].bottom, 1.0f)));
			numobj->GetComponent<PCTSpriteDraw>()->UpdateVertices(vertices);
			break;
		case 6:
			vertices.push_back(VertexPositionColorTexture(Vec3(-1.0f, 1.0f, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(m_numRects[6].left, 0.0f)));
			vertices.push_back(VertexPositionColorTexture(Vec3(1.0f, 1.0f, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(m_numRects[6].top, 0.0f)));
			vertices.push_back(VertexPositionColorTexture(Vec3(-1.0f, -1.0f, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(m_numRects[6].right, 1.0f)));
			vertices.push_back(VertexPositionColorTexture(Vec3(1.0f, -1.0f, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(m_numRects[6].bottom, 1.0f)));
			numobj->GetComponent<PCTSpriteDraw>()->UpdateVertices(vertices);
			break;
		case 7:
			vertices.push_back(VertexPositionColorTexture(Vec3(-1.0f, 1.0f, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(m_numRects[7].left, 0.0f)));
			vertices.push_back(VertexPositionColorTexture(Vec3(1.0f, 1.0f, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(m_numRects[7].top, 0.0f)));
			vertices.push_back(VertexPositionColorTexture(Vec3(-1.0f, -1.0f, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(m_numRects[7].right, 1.0f)));
			vertices.push_back(VertexPositionColorTexture(Vec3(1.0f, -1.0f, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(m_numRects[7].bottom, 1.0f)));
			numobj->GetComponent<PCTSpriteDraw>()->UpdateVertices(vertices);
			break;
		case 8:
			vertices.push_back(VertexPositionColorTexture(Vec3(-1.0f, 1.0f, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(m_numRects[8].left, 0.0f)));
			vertices.push_back(VertexPositionColorTexture(Vec3(1.0f, 1.0f, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(m_numRects[8].top, 0.0f)));
			vertices.push_back(VertexPositionColorTexture(Vec3(-1.0f, -1.0f, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(m_numRects[8].right, 1.0f)));
			vertices.push_back(VertexPositionColorTexture(Vec3(1.0f, -1.0f, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(m_numRects[8].bottom, 1.0f)));
			numobj->GetComponent<PCTSpriteDraw>()->UpdateVertices(vertices);
			break;
		case 9:
			vertices.push_back(VertexPositionColorTexture(Vec3(-1.0f, 1.0f, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(m_numRects[9].left, 0.0f)));
			vertices.push_back(VertexPositionColorTexture(Vec3(1.0f, 1.0f, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(m_numRects[9].top, 0.0f)));
			vertices.push_back(VertexPositionColorTexture(Vec3(-1.0f, -1.0f, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(m_numRects[9].right, 1.0f)));
			vertices.push_back(VertexPositionColorTexture(Vec3(1.0f, -1.0f, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(m_numRects[9].bottom, 1.0f)));
			numobj->GetComponent<PCTSpriteDraw>()->UpdateVertices(vertices);
			break;
		default:
			break;
		}
	}
}