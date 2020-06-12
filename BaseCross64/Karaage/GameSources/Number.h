/*!
@file Character.h
@brief キャラクターなど
*/

#pragma once
#include "stdafx.h"

namespace basecross{
	class Number : public GameObject 
	{
		int number;//画像の元となる数値
		std::vector<VertexPositionTexture> vertices;//頂点データ

	public :
		Number(const shared_ptr<Stage>& stage)
			: GameObject(stage)
		{
		}

		void OnCreate() override;

		//表示する数字を変更する時に使うセッター
		void SetNumber(int n) 
		{
			number = n;
		}

		void UpdateUV();
	};

}
//end basecross
