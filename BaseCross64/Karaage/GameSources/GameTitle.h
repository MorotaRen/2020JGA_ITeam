/*!
@file GameTitel.h
@brief ゲームタイトル
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class GameTitel : public Stage {
		void CreateViewLight();
		void CreateTraceSprite();


	public:
		GameTitel() :Stage() {}
		virtual ~GameTitel() {}
		virtual void OnCreate()override;
	};


}
//end basecross

