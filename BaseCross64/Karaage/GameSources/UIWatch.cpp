/*!
@file Character.cpp
@brief キャラクターなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{
	void UIWatch::OnCreate()
	{
		//数字を並べる
		for (int i = 0; i < 3; i++) {
			auto number = ObjectFactory::Create<Number>(GetStage());
			auto transComp = number->GetComponent<Transform>();
			transComp->SetPosition(position + Vec3(64, 0, 0)*float(i));

			numbers.push_back(number);
		}
	}

	void UIWatch::OnUpdate2()
	{
		//
		seconds -= App::GetApp()->GetElapsedTime();
		if (seconds <= 0.0f) {
			seconds = (false);
		}
	}

	void UIWatch::OnDraw()
	{
		int sec = static_cast<int>(seconds);

		int place = 10;
		for (auto number : numbers) {
			int n = sec / place % 10;
			place /= 10;

			number->SetNumber(n);
			number->UpdateUV();
			number->OnDraw();
		}
	}
}
//end basecross
