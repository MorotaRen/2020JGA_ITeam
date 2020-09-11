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
		}
		catch (...) {
			throw;
		}
	}
	void GameStage::OnUpdate() {
		if (!m_trigger) {
			FlyMaster::GetInstans().GAMESTART(STAGE_MONEY_1,STAGE_TIME_1);
			FlyMaster::GetInstans().Master_Customers();
			m_trigger = true;
		}

		//----PAD���擾----//
		auto pad = App::GetApp()->GetInputDevice().GetControlerVec();
		bool isRecast = FlyMaster::GetInstans().GetTimerForOil();
		if (FlyMaster::GetInstans().GetGameStautas()) {
			if (!isRecast) {

				//------------------�㉺�ړ�------------------//
				if (pad[0].fThumbLX > 0.5f) {
					FlyMaster::GetInstans().Move_PossessionMeat(RIGHT);
				}
				else
					if (pad[0].fThumbLX < -0.5f) {
						FlyMaster::GetInstans().Move_PossessionMeat(LEFT);
					}
					else
						if (pad[0].fThumbLY > 0.5f) {
							FlyMaster::GetInstans().Move_PossessionMeat(UP);
						}
						else
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
				if (pad[0].wPressedButtons & XINPUT_GAMEPAD_Y) {
					auto md = FlyMaster::GetInstans().GetMeatsInstallationData();
					FlyMaster::GetInstans().Fly();
				}
				//---------------------------------------------//
				//---------------�f�o�b�N�p--------------------//
				auto keystate = App::GetApp()->GetInputDevice().GetKeyState();
				auto mode = BOOL_ISDEBUG;
				if (mode) {
					if (keystate.m_bPressedKeyTbl[VK_SPACE]) {
						FlyMaster::GetInstans().GAMESET();
					}
				}
				//---------------�f�o�b�N�p--------------------//

				FlyMaster::GetInstans().Change_PossessionMeat();
				FlyMaster::GetInstans().Recast_Move();
			}
		}
	}

	void GameStage::CreateGuest()
	{
	}

	void GameStage::OnUpdate2() {
		if (FlyMaster::GetInstans().GetGameStautas()) {
			//�Q�[������
			FlyMaster::GetInstans().Update_Timer();
			//�g�����Ԃ̃^�C�}�[
			bool isRecast = FlyMaster::GetInstans().GetTimerForOil();
			if (isRecast) {
				FlyMaster::GetInstans().Fly_Timer();
			}
		}
	}
}
//end basecross
