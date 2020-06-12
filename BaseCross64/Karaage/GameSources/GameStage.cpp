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
	void GameStage::CreateViewLight() {
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

	void GameStage::OnCreate() {
		try {
			//�r���[�ƃ��C�g�̍쐬
			CreateViewLight();
			AddGameObject<UIBase>(Vec2(0),Vec3(670.0f,400.0f,0.0f),L"BG_Kitchen");
			AddGameObject<UIBase>(Vec2(-20,-60),Vec3(210.0f,370.0f,1.0f),L"BG_Flyer");
			//AddGameObject<UIBase>(Vec2(-20,-60),Vec3(180.0f,370.0f,1.0f),L"BG_Flyer");
			CreateGuest();
		}
		catch (...) {
			throw;
		}
	}
	void GameStage::OnUpdate() {
		if (!m_trigger) {
<<<<<<< HEAD
			FlyMaster::GetInstans().Create_GameField();
			FlyMaster::GetInstans().Create_PossessionMeat(0);
=======
			FlyMaster::GetInstans().GAMESTART(700,7000);
			FlyMaster::GetInstans().Master_Customers();
>>>>>>> Morota_ForHome
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

		//-------------------���̔z�u-------------------//
		if (pad[0].wPressedButtons & XINPUT_GAMEPAD_A) {
			FlyMaster::GetInstans().Set_PossessionMeat();
		}
		if (pad[0].wPressedButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) {
			FlyMaster::GetInstans().Rot_PossessionMeat(90);
		}
		//---------------------------------------------//

		FlyMaster::GetInstans(). Change_PossessionMeat();
		FlyMaster::GetInstans().Recast_Move();
	}

<<<<<<< HEAD
<<<<<<< HEAD
	//�X�R�A�̃X�v���C�g�쐬
	void GameStage::CreateSocoreSprite() {
		AddGameObject<ScoreSprite>(4,
			L"", true,
			Vec2(0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f));
=======
	void GameStage::CreateGuest()
	{
>>>>>>> Morota_ForHome
	}

	//�w�i�̃X�v���C�g�쐬
	void GameStage::CreateBackgroundSprite() {
		AddGameObject<BackgroundSprite>(
			L"", false,
			Vec2(0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f));
=======
	void GameStage::CreateGuest()
	{
		AddGameObject<MultiSprite>(true, Vec2(300, 150), Vec3(400, 300, 0), L"Guest1_TX");
>>>>>>> 2895b5c7c1f47d7f320016e98c96fb843d98e27d
	}
}
//end basecross
