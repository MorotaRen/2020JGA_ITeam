/*!
@file GameTitle.cpp
@brief �Q�[���^�C�g������
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	�Q�[���X�e�[�W�N���X����
	//--------------------------------------------------------------------------------------
	void GameTitle::CreateViewLight() {
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

	void GameTitle::OnCreate() {
		try {
			//�r���[�ƃ��C�g�̍쐬
			CreateViewLight();
			//�w�i�p�c
			AddGameObject<MeatUI>(Vec2(0,0),Vec3(700,400,1),L"BG_TitleBack");
			//�Q�[���^�C�g���X�v���C�g��ݒu
			AddGameObject<MeatUI>(Vec2(0, 100), Vec3(300, 200, 1), L"BG_Title");
			//�X�^�[�g�{�^���X�v���C�g
			AddGameObject<MeatUI>(Vec2(0, -250), Vec3(150, 80, 1), L"BG_StartButton");
			App::GetApp()->GetScene<Scene>()->MusicRoopsStart(L"BGM_Title",0.1f);

		}
		catch (...) {
			throw;
		}
	}
	void GameTitle::OnUpdate() {
		auto pad = GamePadManager::GetGamePad();
		if (pad[0].bConnected) {
			if (pad[0].wPressedButtons & XINPUT_GAMEPAD_A) {
				auto ptrScene = App::GetApp()->GetScene<Scene>();
				PostEvent(0.0f,GetThis<ObjectInterface>(),ptrScene,L"ToSelectStage");

				App::GetApp()->GetScene<Scene>()->MusicOnecStart(L"SE_Decision", 7.0f);
			}
		}
	}

	//�w�i�̃X�v���C�g�쐬
	void GameTitle::CreateBackgroundSprite() {

	}
}
//end basecross
