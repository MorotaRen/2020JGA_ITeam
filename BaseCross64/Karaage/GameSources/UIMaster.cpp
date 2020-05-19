#include "stdafx.h"
#include "Project.h"
namespace basecross {
	void MeatUI::OnCreate() {
		float helfSize = 1.0f;
		//���_�z��(�c��5���\��)	
		vector<VertexPositionColorTexture> vertices = {
			{ VertexPositionColorTexture(Vec3(-helfSize, helfSize, 0),Col4(1.0f,1.0f,1.0f,1.0f), Vec2(0.0f, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(helfSize, helfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(1.0f, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(-helfSize, -helfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(0.0f, 1.0f)) },
			{ VertexPositionColorTexture(Vec3(helfSize, -helfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(1.0f, 1.0f)) },
		};
		//�C���f�b�N�X�z��
		vector<uint16_t> indices = { 0, 1, 2, 1, 3, 2 };
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_scale.x, m_scale.y,m_scale.z);
		ptrTrans->SetRotation(0, 0, 0);
		ptrTrans->SetPosition(m_pos.x, m_pos.y, 0.0f);
		//���_�ƃC���f�b�N�X���w�肵�ăX�v���C�g�쐬
		auto ptrDraw = AddComponent<PCTSpriteDraw>(vertices, indices);
		ptrDraw->SetTextureResource(m_texkey);
		SetAlphaActive(true);
	}
	void NumberUI::OnCreate() {
		float Range = 0.1f;
		//�����͈̔͂̐���
		for (int i = 0; i < 10;i++) {
			m_numRects.push_back(
				{
					//����(left)
					static_cast<float> (0 + (Range * i)),
					//�E��(top)
					static_cast<float> (0.1f + (Range * i)),
					//�E��(right)
					static_cast<float> (0 + (Range * i)),
					//����(buttom)
					static_cast<float> (0.1f + (Range * i)),
				}
			);
		}
		//���_�z��(�c��5���\��)	
		float helfSize = 1.0f;
		vector<VertexPositionColorTexture> vertices = {
			{ VertexPositionColorTexture(Vec3(-helfSize, helfSize, 0),Col4(1.0f,1.0f,1.0f,1.0f), Vec2(m_numRects[1].left, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(helfSize, helfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(m_numRects[1].top, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(-helfSize, -helfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(m_numRects[1].right, 1.0f)) },
			{ VertexPositionColorTexture(Vec3(helfSize, -helfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(m_numRects[1].bottom, 1.0f)) },
		};
		vector<uint16_t> indices = { 0, 1, 2, 1, 3, 2 };
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_scale.x, m_scale.y, m_scale.z);
		ptrTrans->SetRotation(0, 0, 0);
		ptrTrans->SetPosition(m_pos.x, m_pos.y, 0.0f);
		//���_�ƃC���f�b�N�X���w�肵�ăX�v���C�g�쐬
		auto ptrDraw = AddComponent<PCTSpriteDraw>(vertices, indices);
		ptrDraw->SetTextureResource(m_texkey);
		SetAlphaActive(true);
	}
	
	void NumberUI::Set_Num(int num) {
		//�ő�6�����ȁc(100,000)
		int tempnum[6] = { 0 };
		//�ꌅ������Ċi�[
		tempnum[0] = (num % 10);num /= 10;//1
		tempnum[1] = (num % 10);num /= 10;//2
		tempnum[2] = (num % 10);num /= 10;//3
		tempnum[3] = (num % 10);num /= 10;//4
		tempnum[4] = (num % 10);num /= 10;//5
		tempnum[5] = (num % 10);num /= 10;//6
	}
	void NumberUI::Update_num() {
		for () {

		}
	}
}