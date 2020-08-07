/*!
@file GameTitle.cpp
@brief ゲームタイトル実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス実体
	//--------------------------------------------------------------------------------------
	void GameTitle::CreateViewLight() {
		const Vec3 eye(0.0f, 5.0f, -5.0f);
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

	void GameTitle::OnCreate() {
		try {
			//ビューとライトの作成
			CreateViewLight();
			//背景用…
			AddGameObject<MeatUI>(Vec2(0,0),Vec3(700,400,1),L"BG_TitleBack");
			//ゲームタイトルスプライトを設置
			AddGameObject<MeatUI>(Vec2(0, 100), Vec3(300, 200, 1), L"BG_Title");
			//スタートボタンスプライト
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

	//背景のスプライト作成
	void GameTitle::CreateBackgroundSprite() {

	}
}
//end basecross
