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
	void SelectStage::CreateViewLight() {
		const Vec3 eye(0.0f, 5.0f, -5.0f);
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



	void SelectStage::OnCreate() {
		try {
			//�r���[�ƃ��C�g�̍쐬
			CreateViewLight();
			CreateSprite();
		}
		catch (...) {
			throw;
		}
	}

	void SelectStage::CreateSprite() {
		//�w�i
		AddGameObject<MultiSprite>(true, Vec2(1280, 800), Vec3(0, 0, 0), L"Select_BG");

		//�X�e�[�W
		float height = (float)App::GetApp()->GetGameHeight() / 3;
		float width = (float)App::GetApp()->GetGameWidth() / 3;

		float posX = -width, posY = -height;

		for (int i = 0; i < 3; i++) {
			posX = -width;
			for (int j = 0; j < 3; j++) {
				AddGameObject<MultiSprite>(true, Vec2(200, 100), Vec3(posX, posY, 0), L"Select_Stage_TX");
				posX += width;
			}
			posY += height;
		}
	}
}
//end basecross
