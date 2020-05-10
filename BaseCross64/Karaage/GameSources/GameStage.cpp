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
			AddGameObject<UIBase>(Vec2(0),Vec3(670.0f,400.0f,0.0f),L"BG_Kitchen");
			AddGameObject<UIBase>(Vec2(-20,-60),Vec3(210.0f,370.0f,1.0f),L"BG_Flyer");
			AddGameObject<UIBase>(Vec2(-20,-60),Vec3(180.0f,370.0f,1.0f),L"BG_Flyer");
			CreateGuest();
		}
		catch (...) {
			throw;
		}
	}
	void GameStage::OnUpdate() {
		if (!m_trigger) {
			FlyMaster::GetInstans().Create_GameField();
			FlyMaster::GetInstans().Create_PossessionMeat(0);
			m_trigger = true;
		}

				//----PAD情報取得----//
		auto pad = App::GetApp()->GetInputDevice().GetControlerVec();

		//------------------上下移動------------------//
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

		//-------------------肉の配置-------------------//
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

	void GameStage::CreateGuest()
	{
		AddGameObject<MultiSprite>(true, Vec2(300, 150), Vec3(400, 300, 0), L"Guest1_TX");
	}
}
//end basecross
