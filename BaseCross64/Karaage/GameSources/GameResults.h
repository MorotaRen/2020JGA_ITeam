/*!
@file GameResults.h
@brief �Q�[�����U���g
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	�Q�[�����U���g�N���X
	//--------------------------------------------------------------------------------------
	class GameResults : public Stage {
		//�r���[�̍쐬
		void CreateViewLight();

		bool m_trigger = false;

	public:

		//�\�z�Ɣj��
		GameResults() :Stage() {}
		virtual ~GameResults() {}
		//������
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
	};


}
//end basecross

