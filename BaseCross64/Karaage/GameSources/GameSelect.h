/*!
@file GameSelect.h
@brief ゲームセレクト
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class GameSelect : public Stage {
		void CreateViewLight();
		void CreateTraceSprite();


	public:
		GameSelect() :Stage() {}
		virtual ~GameSelect() {}

		virtual void OnCreate()override;
	};


}
//end basecross

