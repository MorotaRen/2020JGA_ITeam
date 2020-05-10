/*!
@file Character.h
@brief キャラクターなど
*/

#pragma once
#include "stdafx.h"

namespace basecross{
	class Customer : public GameObject
	{
		Vec3 m_scale;
		Vec3 m_rotation;
		Vec3 m_position;

		float m_timer;
		int m_meet[5] = { 0 };

		bool m_clear;

	public :
		Customer(shared_ptr<Stage>&Stage, Vec3 scale, Vec3 rotation, Vec3 position);
		~Customer() {};

		virtual void OnCreate() override;
		virtual void OnUpdate() override;
	};

}
//end basecross
