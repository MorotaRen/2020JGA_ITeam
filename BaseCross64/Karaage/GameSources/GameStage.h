/*!
@file GameStage.h
@brief �Q�[���X�e�[�W
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	�Q�[���X�e�[�W�N���X
	//--------------------------------------------------------------------------------------
	class GameStage : public Stage {
		//�r���[�̍쐬
		void CreateViewLight();

		////�X�R�A�̃X�v���C�g�쐬
		//void CreateSocoreSprite();

		////�w�i�̃X�v���C�g�쐬
		//void CreateBackgroundSprite();

		bool m_trigger = false;

	public:

		//�\�z�Ɣj��
		GameStage() :Stage() {}
		virtual ~GameStage() {}
		//������
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		virtual void OnUpdate2() override;

		void CreateGuest();
	};


}
//end basecross

