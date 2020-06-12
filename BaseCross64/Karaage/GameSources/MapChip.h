#pragma once
/// ----------------------------------------<summary>
/// マップチップ、これを認識しておけるか判断している
/// 管理者：諸田
/// </summary>----------------------------------------

#include "stdafx.h"
namespace basecross {
	class MapChip : public GameObject
	{
	private:
		//-------------------変数-----------------//
		//位置
		Vec2 m_pos;
		//テスト用、白黒の切り替え
		bool m_OnWhite;
		//設置状態
		bool m_isInstalled = false;
		//----------------------------------------//

	public:
		MapChip(const shared_ptr<Stage>& stage, const Vec2& pos,bool w)
			: GameObject(stage),m_pos(pos),m_OnWhite(w) {};
		~MapChip() {};
		virtual void OnCreate() override;

	};
}