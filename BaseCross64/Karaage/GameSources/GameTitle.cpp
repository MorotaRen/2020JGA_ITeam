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
		const Vec3 eye(0.0f, 20.0f, -0.5f);
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
			AddGameObject<UIBase>(Vec2(0),Vec3(670.0f,400.0f,0.0f),L"BG_Kitchen");
			AddGameObject<UIBase>(Vec2(-20,-60),Vec3(180.0f,370.0f,1.0f),L"BG_Flyer");
		}
		catch (...) {
			throw;
		}
	}
	void GameTitle::OnUpdate() {
		if (!m_trigger) {
			FlyMaster::GetInstans().Create_GameField();
			FlyMaster::GetInstans().Create_PossessionMeat(0);
			m_trigger = true;
		}

				//----PAD���擾----//
		auto pad = App::GetApp()->GetInputDevice().GetControlerVec();

		//------------------�㉺�ړ�------------------//
		if (pad[0].fThumbLX > 0.5f) {
			FlyMaster::GetInstans().Move_PossessionMeat(RIGHT);
		}else
		if (pad[0].fThumbLX < -0.5f) {
			FlyMaster::GetInstans().Move_PossessionMeat(LEFT);
		}else
		if (pad[0].fThumbLY > 0.5f) {
			FlyMaster::GetInstans().Move_PossessionMeat(UP);
		}else
		if (pad[0].fThumbLY < -0.5f) {
			FlyMaster::GetInstans().Move_PossessionMeat(DOWN);
		}
		//---------------------------------------------//

	}

	//�w�i�̃X�v���C�g�쐬
	void GameTitle::CreateBackgroundSprite() {
		AddGameObject<BackgroundSprite>(
			L"", false,
			Vec2(0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f));
	}
}
//end basecross
