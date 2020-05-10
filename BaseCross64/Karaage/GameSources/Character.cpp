/*!
@file Character.cpp
@brief キャラクターなど実体
*/

#include "stdafx.h"
#include "Project.h"
#include "BaseMath.h"

namespace basecross{
	Customer::Customer(shared_ptr<Stage>&Stage, Vec3 scale, Vec3 rotation, Vec3 position)
		: GameObject(Stage),
		m_scale(scale),
		m_rotation(rotation),
		m_position(position)
	{
		m_timer = 0;
		m_clear = false;
	}

	void Customer::OnCreate() 
	{
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_scale);
		ptrTrans->SetRotation(m_rotation);
		ptrTrans->SetPosition(m_position);

		int num = rand() % 5 + 1;

		m_timer = 5.0f * num;

		for (int i = 0; i < num; i++) {
			int meetNum = rand() % 5;

			m_meet[meetNum]++;
		}
	}

	void Customer::OnUpdate()
	{

	}

}
//end basecross
