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
		}
		catch (...) {
			throw;
		}
	}
	void GameResults::OnUpdate() {
	}

	//�X�R�A�̃X�v���C�g�쐬
	void GameResults::CreateSocoreSprite() {
		//AddGameObject<ScoreSprite>(4,
		//	L"", true,
		//	Vec2(0.0f, 0.0f),
		//	Vec3(0.0f, 0.0f, 0.0f));
	}

	//�w�i�̃X�v���C�g�쐬
	void GameResults::CreateBackgroundSprite() {
		//AddGameObject<BackgroundSprite>(
		//	L"", false,
		//	Vec2(0.0f, 0.0f),
		//	Vec3(0.0f, 0.0f, 0.0f));
	}
}
//end basecross
