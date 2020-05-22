//---------------------------------------------
//	�Q�[�����Ŏg��UI�֌W
//---------------------------------------------
#pragma once
#include "stdafx.h"

namespace basecross {
	class MeatUI : public GameObject
	{
	private:
		Vec3 m_pos,m_scale;
		wstring m_texkey;
	public:
		MeatUI(const shared_ptr<Stage>& stage, const Vec2& pos,const Vec3& scale,wstring texkey)
			: GameObject(stage), m_pos(pos.x, pos.y, 0.0f),m_scale(scale),m_texkey(texkey)
		{
		}
		void OnCreate() override;
	};
	class NumberUI : public GameObject
	{
	private:
		Vec3 m_pos,m_scale;
		wstring m_texkey;
	public:
		NumberUI(const shared_ptr<Stage>& stage, const Vec2& pos,const Vec3& scale,wstring texkey)
			: GameObject(stage), m_pos(pos.x, pos.y, 0.0f),m_scale(scale),m_texkey(texkey)
		{
		}

		void OnCreate() override;
	};
	class OverUI : public GameObject
	{
	private:
		Vec3 m_pos,m_scale;
		wstring m_texkey;
	public:
		OverUI(const shared_ptr<Stage>& stage, const Vec2& pos,const Vec3& scale,wstring texkey)
			: GameObject(stage), m_pos(pos.x, pos.y, 0.0f),m_scale(scale),m_texkey(texkey)
		{
		}

		void OnCreate() override;
	};
}