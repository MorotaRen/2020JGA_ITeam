/*!
@file Character.h
@brief キャラクターなど
*/

#pragma once
#include "stdafx.h"
#include "Number.h"

namespace basecross{
	class UIWatch : public GameObject
	{
		float seconds; //秒
		std::vector<shared_ptr<Number>> numbers;//Numberオブジェクトの管理

		Vec3 position;

		void UpdateNumbersPos()
		{
			float offset = 0.0f;
			for(auto& number : numbers)
			{
				auto transComp = number->GetDynamicComponent<Transform>();
				transComp->SetPosition(position + Vec3(64.0f, 0.0f, 0.0f) * offset);
				offset += 1.0f;
			}
		}

	public :
		UIWatch(const shared_ptr<Stage>& stage, const Vec2& pos)
			: GameObject(stage), position(pos.x, pos.y, 0.0f),seconds(180.0f)
		{
		}

		void OnCreate() override;
		void OnUpdate2() override;
		void OnDraw() override;

		void SetPosition(const Vec2& pos)
		{
			position = pos;
			UpdateNumbersPos();
		}

		void SetPosition(float x, float y)
		{
			SetPosition(Vec2(x, y));
		}
	};
}
//end basecross
