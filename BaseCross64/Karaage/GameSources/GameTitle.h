/*!
@file GameTitle.h
@brief �Q�[���^�C�g��
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	�Q�[���^�C�g���N���X
	//--------------------------------------------------------------------------------------
	class GameTitle : public Stage {
		//�r���[�̍쐬
		void CreateViewLight();

		//�w�i�̃X�v���C�g�쐬
		void CreateBackgroundSprite();

		bool m_trigger = false;

	public:

		//�\�z�Ɣj��
		GameTitle() :Stage() {}
		virtual ~GameTitle() {}
		//������
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
	};


}
//end basecross

