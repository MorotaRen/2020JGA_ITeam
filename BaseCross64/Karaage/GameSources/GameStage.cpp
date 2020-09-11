/*!
@file GameStage.cpp
@brief ゲームステージ実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス実体
	//--------------------------------------------------------------------------------------
	void GameStage::CreateViewLight() {
		const Vec3 eye(0.0f, 20.0f, -0.5f);
		const Vec3 at(0.0f);
		auto PtrView = CreateView<SingleView>();

		//ビューのカメラの設定
		auto PtrCamera = ObjectFactory::Create<Camera>();
		PtrView->SetCamera(PtrCamera);
		PtrCamera->SetEye(eye);
		PtrCamera->SetAt(at);
		//マルチライトの作成
		auto PtrMultiLight = CreateLight<MultiLight>();
		//デフォルトのライティングを指定
		PtrMultiLight->SetDefaultLighting();
	}

	void GameStage::OnCreate() {
		try {
			//ビューとライトの作成
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

		//----PAD情報取得----//
		auto pad = App::GetApp()->GetInputDevice().GetControlerVec();
		bool isRecast = FlyMaster::GetInstans().GetTimerForOil();
		if (FlyMaster::GetInstans().GetGameStautas()) {
			if (!isRecast) {

				//------------------上下移動------------------//
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

				//-------------------肉の配置-------------------//
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
				//---------------デバック用--------------------//
				auto keystate = App::GetApp()->GetInputDevice().GetKeyState();
				auto mode = BOOL_ISDEBUG;
				if (mode) {
					if (keystate.m_bPressedKeyTbl[VK_SPACE]) {
						FlyMaster::GetInstans().GAMESET();
					}
				}
				//---------------デバック用--------------------//

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
			//ゲーム時間
			FlyMaster::GetInstans().Update_Timer();
			//揚げ時間のタイマー
			bool isRecast = FlyMaster::GetInstans().GetTimerForOil();
			if (isRecast) {
				FlyMaster::GetInstans().Fly_Timer();
			}
		}
	}
}
//end basecross
