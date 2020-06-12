/*!
@file GameStage.h
@brief ゲームステージ
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス
	//--------------------------------------------------------------------------------------
	class GameStage : public Stage {
		//ビューの作成
		void CreateViewLight();

		////スコアのスプライト作成
		//void CreateSocoreSprite();

		////背景のスプライト作成
		//void CreateBackgroundSprite();

		bool m_trigger = false;

	public:

		//構築と破棄
		GameStage() :Stage() {}
		virtual ~GameStage() {}
		//初期化
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		virtual void OnUpdate2() override;

		void CreateGuest();
	};


}
//end basecross

