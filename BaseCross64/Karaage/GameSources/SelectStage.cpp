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
		float height = 680 / 3;
		float width = 1200 / 3;
		
		Vec3 pointerPos[9];

		float posX = -width, posY = height;
		int num = 0;
		for (int i = 0; i < 3; i++) {
			posX = -width;
			for (int j = 0; j < 3; j++) {
				//�X�e�[�W�w�i
				AddGameObject<MultiSprite>(true, Vec2(300, 150), Vec3(posX, posY, 0), L"Select_Stage_TX");
				//�|�C���^�[�̃|�W�V�����L�^
				pointerPos[num] = Vec3(posX, posY, 0);
				//�X�e�[�W�̐����\��
				AddGameObject<StageNumUI>(Vec2(posX, posY), Vec3(30.0f, 30.0f, 1.0f), L"Tex_Number",num + 1);
				num++;
				posX += width;
			}
			posY -= height;
		}

		//FlyMaster::GetInstans().Set_Num(123456789, m_ptrNum);
		

		//�|�C���^�[
		AddGameObject<Pointer>(true, Vec2(68, 88), Vec3(-466, 266, 0), pointerPos);

		//����A�߂��UI
		AddGameObject<MultiSprite>(true, Vec2(180, 80), Vec3(-550, 360, 0), L"BackButton_TX");
		AddGameObject<MultiSprite>(true, Vec2(180, 80), Vec3(-350, 360, 0), L"DecisionalButton_TX");

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

	Pointer::Pointer(const shared_ptr<Stage>& Stage, bool trace, const Vec2& startScale, const Vec3& startPos, Vec3 posArray[9])
		: GameObject(Stage),
		m_trace(trace),
		m_startScale(startScale),
		m_startPos(startPos)
	{
		for (int i = 0; i < 9; i++) {
			m_posArray[i] = posArray[i];
		}

		m_selectNum = 0;
		m_frameCount = 0.0f;
	}
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
		ptrTransform->SetPosition(m_posArray[m_selectNum]);
		//���_�ƃC���f�b�N�X���w�肵�ăX�v���C�g�쐬
		auto ptrDraw = AddComponent<PTSpriteDraw>(m_backupVertices, indices);
		ptrDraw->SetTextureResource(L"Pointer_TX");
		this->SetDrawLayer(2);
	}

	void Pointer::OnUpdate()
	{
		m_frameCount += App::GetApp()->GetElapsedTime();
		auto pad = GamePadManager::GetGamePad();
		auto keystate = App::GetApp()->GetInputDevice().GetKeyState();


		//if (pad[0].bConnected) {
			//����
			if (pad[0].wPressedButtons & XINPUT_GAMEPAD_A || keystate.m_bPressedKeyTbl[VK_SPACE]) {
				auto ptrScene = App::GetApp()->GetScene<Scene>();
				PostEvent(0.0f, GetThis<ObjectInterface>(), ptrScene, L"ToGameStage");

				App::GetApp()->GetScene<Scene>()->MusicOnecStart(L"SE_Decision", 7.0f);
			}

			//�߂�
			if (pad[0].wPressedButtons & XINPUT_GAMEPAD_B) {
				auto ptrScene = App::GetApp()->GetScene<Scene>();
				PostEvent(0.0f, GetThis<ObjectInterface>(), ptrScene, L"ToTitleStage");

				App::GetApp()->GetScene<Scene>()->MusicOnecStart(L"SE_Back", 7.0f);
			}
		//}

		//�I��
		auto ptrTrans = GetComponent<Transform>();
		if (0.5f < m_frameCount) {
			if (pad[0].fThumbLX >= 0.8f || keystate.m_bPressedKeyTbl['D']) {
				m_selectNum++;
				if (m_selectNum > 8) {
					m_selectNum = 0;
				}
				ptrTrans->SetPosition(m_posArray[m_selectNum]);
				m_frameCount = 0.0f;
			}
			if (pad[0].fThumbLX <= -0.8 || keystate.m_bPressedKeyTbl['A']){
				m_selectNum--;
				if (m_selectNum < 0) {
					m_selectNum = 8;
				}
				ptrTrans->SetPosition(m_posArray[m_selectNum]);
				m_frameCount = 0.0f;
			}
		}
	}

	void StageNumUI::OnCreate() {		
		//���_�z��(�c��5���\��)	
		float helfSize = 1.0f;
		vector<VertexPositionColorTexture> vertices = {
			{ VertexPositionColorTexture(Vec3(-helfSize, helfSize, 0),Col4(1.0f,1.0f,1.0f,1.0f), Vec2(0.1f * m_num, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(helfSize, helfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(0.1f + 0.1f * m_num, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(-helfSize, -helfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(0.1f * m_num, 1.0f)) },
			{ VertexPositionColorTexture(Vec3(helfSize, -helfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(0.1f + 0.1f * m_num, 1.0f)) },
		};
		vector<uint16_t> indices = { 0, 1, 2, 1, 3, 2 };
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_scale.x, m_scale.y, m_scale.z);
		ptrTrans->SetRotation(0, 0, 0);
		ptrTrans->SetPosition(m_pos.x, m_pos.y, m_pos.z);
		//���_�ƃC���f�b�N�X���w�肵�ăX�v���C�g�쐬
		auto ptrDraw = AddComponent<PCTSpriteDraw>(vertices, indices);
		ptrDraw->SetTextureResource(m_texkey);
		this->SetDrawLayer(1);
		SetAlphaActive(true);
	}

}
//end basecross
