/*!
@file GameStage.cpp
@brief �Q�[���X�e�[�W����
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	�Q�[���X�e�[�W�N���X����
	//--------------------------------------------------------------------------------------
	void SelectStage::CreateViewLight() {
		const Vec3 eye(0.0f, 5.0f, -5.0f);
		const Vec3 at(0.0f);
		auto PtrView = CreateView<SingleView>();
		//�r���[�̃J�����̐ݒ�
		auto PtrCamera = ObjectFactory::Create<Camera>();
		PtrView->SetCamera(PtrCamera);
		PtrCamera->SetEye(eye);
		PtrCamera->SetAt(at);
		//�}���`���C�g�̍쐬
		auto PtrMultiLight = CreateLight<MultiLight>();
		//�f�t�H���g�̃��C�e�B���O���w��
		PtrMultiLight->SetDefaultLighting();
	}

	void SelectStage::CreateSprite() {
		//�w�i
		AddGameObject<MultiSprite>(true, Vec2(1280, 800), Vec3(0, 0, 0), L"Select_BG");

		//�X�e�[�W
		float height = (float)App::GetApp()->GetGameHeight() / 3;
		float width = (float)App::GetApp()->GetGameWidth() / 3;

		float posX = -width, posY = -height;

		for (int i = 0; i < 3; i++) {
			posX = -width;
			for (int j = 0; j < 3; j++) {
				AddGameObject<MultiSprite>(true, Vec2(200, 100), Vec3(posX, posY, 0), L"Select_Stage_TX");
				posX += width;
			}
			posY += height;
		}

		AddGameObject<Pointer>(true, Vec2(68, 88), Vec3(-466, -266, 0), L"Pointer_TX");
	}


	void SelectStage::OnCreate() {
		try {
			//�r���[�ƃ��C�g�̍쐬
			CreateViewLight();
			CreateSprite();
		}
		catch (...) {
			throw;
		}
	}

	Pointer::Pointer(const shared_ptr<Stage>& StagePtr, bool Trace, const Vec2& StartScale, const Vec3& StartPos, wstring TextureKey) :
		GameObject(StagePtr),
		m_trace(Trace),
		m_startScale(StartScale),
		m_startPos(StartPos),
		m_textureKey(TextureKey)
	{}
	Pointer::~Pointer() {}

	void Pointer::OnCreate() {
		float halfSize = 0.5f;
		//���_�z��
		m_backupVertices = {
			{ VertexPositionTexture(Vec3(-halfSize, halfSize, 0), Vec2(0.0f, 0.0f)) },
			{ VertexPositionTexture(Vec3(halfSize, halfSize, 0), Vec2(1.0f, 0.0f)) },
			{ VertexPositionTexture(Vec3(-halfSize, -halfSize, 0), Vec2(0.0f, 1.0f)) },
			{ VertexPositionTexture(Vec3(halfSize, -halfSize, 0), Vec2(1.0f, 1.0f)) },
		};
		//�C���f�b�N�X�z��
		vector<uint16_t> indices = { 0,1,2,1,3,2 };
		SetAlphaActive(m_trace);
		auto ptrTransform = GetComponent<Transform>();
		ptrTransform->SetScale(m_startScale.x, m_startScale.y, 1.0f);
		ptrTransform->SetRotation(0, 0, 0);
		ptrTransform->SetPosition(m_startPos.x, m_startPos.y, 0.0f);
		//���_�ƃC���f�b�N�X���w�肵�ăX�v���C�g�쐬
		auto ptrDraw = AddComponent<PTSpriteDraw>(m_backupVertices, indices);
		ptrDraw->SetTextureResource(m_textureKey);
	}

	void Pointer::OnUpdate()
	{
		auto pad = GamePadManager::GetGamePad();

		if (pad[0].bConnected) {
			if (pad[0].wPressedButtons & XINPUT_GAMEPAD_A) {
				auto ptrScene = App::GetApp()->GetScene<Scene>();
				PostEvent(0.0f, GetThis<ObjectInterface>(), ptrScene, L"ToGameStage");
			}
		}
		
	}

}
//end basecross
