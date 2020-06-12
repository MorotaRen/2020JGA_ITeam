/*!
@file GameResults.cpp
@brief ゲームステージ実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	ゲームリザルトクラス実体
	//--------------------------------------------------------------------------------------
	void GameResults::CreateViewLight() {
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

	void GameResults::OnCreate() {
		try {
			//ビューとライトの作成
			CreateViewLight();
		}
		catch (...) {
			throw;
		}
	}
	void GameResults::OnUpdate() {
	}

	//スコアのスプライト作成
	void GameResults::CreateSocoreSprite() {
		//AddGameObject<ScoreSprite>(4,
		//	L"", true,
		//	Vec2(0.0f, 0.0f),
		//	Vec3(0.0f, 0.0f, 0.0f));
	}

	//背景のスプライト作成
	void GameResults::CreateBackgroundSprite() {
		//AddGameObject<BackgroundSprite>(
		//	L"", false,
		//	Vec2(0.0f, 0.0f),
		//	Vec3(0.0f, 0.0f, 0.0f));
	}
}
//end basecross
