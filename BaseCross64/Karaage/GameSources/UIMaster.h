//---------------------------------------------
//	ÉQÅ[ÉÄì‡Ç≈égÇ§UIä÷åW
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
		void OnCreate() override;
		MeatUI(const shared_ptr<Stage>& stage, const Vec2& pos,const Vec3& scale,wstring texkey)
			: GameObject(stage), m_pos(pos.x, pos.y, 0.0f),m_scale(scale),m_texkey(texkey)
		{
		}
	};
	class NumberUI : public GameObject
	{
	private:
		Vec3 m_pos,m_scale;
		wstring m_texkey;
		int m_number;
		vector<Rect2D<float>> m_numRects;
	public:
		void OnCreate() override;
		NumberUI(const shared_ptr<Stage>& stage, const Vec2& pos,const Vec3& scale,wstring texkey)
			: GameObject(stage), m_pos(pos.x, pos.y, 1.0f),m_scale(scale),m_texkey(texkey)
		{
		}
	};
}