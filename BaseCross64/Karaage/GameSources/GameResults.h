/*!
@file GameResults.h
@brief ゲームリザルト
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	ゲームリザルトクラス
	//--------------------------------------------------------------------------------------
	class GameResults : public Stage {
		//ビューの作成
		void CreateViewLight();

		//スコアのスプライト作成
		void CreateSocoreSprite();

		//背景のスプライト作成
		void CreateBackgroundSprite();

	public:

		//構築と破棄
		GameResults() :Stage() {}
		virtual ~GameResults() {}
		//初期化
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
	};


}
//end basecross

