/*!
@file GameTitle.h
@brief ゲームタイトル
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	ゲームタイトルクラス
	//--------------------------------------------------------------------------------------
	class GameTitle : public Stage {
		//ビューの作成
		void CreateViewLight();

		//背景のスプライト作成
		void CreateBackgroundSprite();

		bool m_trigger = false;

	public:

		//構築と破棄
		GameTitle() :Stage() {}
		virtual ~GameTitle() {}
		//初期化
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
	};


}
//end basecross

