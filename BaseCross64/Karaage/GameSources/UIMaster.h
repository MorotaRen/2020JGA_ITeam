//---------------------------------------------
//	ÉQÅ[ÉÄì‡Ç≈égÇ§UIä÷åW
//---------------------------------------------
#pragma once
#include "stdafx.h"

namespace basecross {
	class UIBase : public GameObject
	{
	private:
		Vec3 m_pos,m_scale;
		wstring m_texkey;
	public:
		void OnCreate() override;
		UIBase(const shared_ptr<Stage>& stage, const Vec2& pos,const Vec3& scale,wstring texkey)
			: GameObject(stage), m_pos(pos.x, pos.y, 0.0f),m_scale(scale),m_texkey(texkey)
		{
		}
	};
}