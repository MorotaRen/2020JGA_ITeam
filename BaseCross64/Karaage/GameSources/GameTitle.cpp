/*!
@file GameTitel.cpp
@brief ゲームタイトル実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void GameTitel::CreateViewLight() {
		const Vec3 eye(0.0f, 5.0f, -5.0f);
		const Vec3 at(0.0f);
		auto PtrView = CreateView<SingleView>();

		auto PtrCamera = ObjectFactory::Create<Camera>();
		PtrView->SetCamera(PtrCamera);
		PtrCamera->SetEye(eye);
		PtrCamera->SetAt(at);

		auto PtrMultiLight = CreateLight<MultiLight>();

		PtrMultiLight->SetDefaultLighting();
	}



	void GameTitel::OnCreate() {
		try {
			CreateViewLight();

			auto WatchUI = AddGameObject<UIWatch>(Vec2(-64.0f, 800.0 * 0.5f));
		}

		catch (...) {
			throw;
		}
	}

}
//end basecross
