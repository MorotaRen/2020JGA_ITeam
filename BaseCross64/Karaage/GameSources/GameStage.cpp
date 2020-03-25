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
			//AddGameObject<Karaage>(Vec3(1, 0, 1), Vec3(8, 0, 6), Vec3(0));
			//AddGameObject<Drum>(Vec3(1, 0, 2), Vec3(8, 0, 3), Vec3(0));
			//AddGameObject<Wing>(Vec3(2, 0, 1), Vec3(8, 0, 0), Vec3(0));
			//AddGameObject<Lib>(Vec3(2, 0, 2), Vec3(8, 0, -3), Vec3(0));
			//AddGameObject<Keel>(Vec3(2, 0, 2), Vec3(8, 0, -6), Vec3(0));

		}
		catch (...) {
			throw;
		}
	}
	void GameStage::OnUpdate() {
		if (!m_trigger) {
			FlyMaster::GetInstans().Create_GameField();
			m_trigger = true;
			
		}
	}
}
//end basecross
