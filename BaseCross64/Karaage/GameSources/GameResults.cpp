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
			CreateBackgroundSprite();
			CreateScoreSprite();
		}
		catch (...) {
			throw;
		}
	}
	void GameResults::OnUpdate() {
	}

	//スコアのスプライト作成
	void GameResults::CreateScoreSprite() {
		//クリアフラグとってくる
		bool clearFlag = FlyMaster::GetInstans().GetIsCleared();
		if (clearFlag) {
			//クリアのテキストたちの表示
			AddGameObject<MeatUI>(Vec2(0, 250), Vec3(150, 80, 1), L"Title_Success");
			AddGameObject<MeatUI>(Vec2(0, -250), Vec3(150, 0, 1), L"Text_Success");
		}
	}

	//背景のスプライト作成
	void GameResults::CreateBackgroundSprite() {
		auto bg = AddGameObject<MultiSprite>(true, Vec2(1280, 800), Vec3(0, 0, 0), L"Select_BG");
		bg->SetDrawLayer(0);
	}
}
//end basecross
