#pragma once
/// ----------------------------------------<summary>
/// �}�b�v�`�b�v�A�����F�����Ă����邩���f���Ă���
/// �Ǘ��ҁF���c
/// </summary>----------------------------------------

#include "stdafx.h"
namespace basecross {
	class MapChip : public GameObject
	{
	private:
		//-------------------�ϐ�-----------------//
		//�ʒu
		Vec2 m_pos;
		//�e�X�g�p�A�����̐؂�ւ�
		bool m_OnWhite;
		//�ݒu���
		bool m_isInstalled = false;
		//----------------------------------------//

	public:
		MapChip(const shared_ptr<Stage>& stage, const Vec2& pos,bool w)
			: GameObject(stage),m_pos(pos),m_OnWhite(w) {};
		~MapChip() {};
		virtual void OnCreate() override;

	};
}