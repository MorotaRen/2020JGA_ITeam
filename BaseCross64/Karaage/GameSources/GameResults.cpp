/*!
@file GameResults.cpp
@brief �Q�[���X�e�[�W����
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	�Q�[�����U���g�N���X����
	//--------------------------------------------------------------------------------------
	void GameResults::CreateViewLight() {
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

	void GameResults::OnCreate() {
		try {
			//�r���[�ƃ��C�g�̍쐬
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

	//�X�R�A�̃X�v���C�g�쐬
	void GameResults::CreateScoreSprite() {
		//�N���A�t���O�Ƃ��Ă���
		bool clearFlag = FlyMaster::GetInstans().GetIsCleared();
		if (clearFlag) {
			//�N���A�̃e�L�X�g�����̕\��
			AddGameObject<MeatUI>(Vec2(0, 250), Vec3(150, 80, 1), L"Title_Success");
			AddGameObject<MeatUI>(Vec2(0, -250), Vec3(150, 0, 1), L"Text_Success");
		}
	}

	//�w�i�̃X�v���C�g�쐬
	void GameResults::CreateBackgroundSprite() {
		auto bg = AddGameObject<MultiSprite>(true, Vec2(1280, 800), Vec3(0, 0, 0), L"Select_BG");
		bg->SetDrawLayer(0);
	}
}
//end basecross
