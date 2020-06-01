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
			//ゲームタイトルスプライトを設置
			AddGameObject<MeatUI>(Vec2(0,0),Vec3(300,300,1),L"BG_Title");
		}
		catch (...) {
			throw;
		}
	}
	void GameTitle::OnUpdate() {

	}

	//背景のスプライト作成
	void GameTitle::CreateBackgroundSprite() {

	}
}
//end basecross
