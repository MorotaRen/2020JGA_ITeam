/*!
@file GameTitel.h
@brief �Q�[���^�C�g��
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class GameTitel : public Stage {
		void CreateViewLight();

	public:
		GameTitel() :Stage() {}
		virtual ~GameTitel() {}
		virtual void OnCreate()override;
	};


}
//end basecross

