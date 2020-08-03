/*!
@file GameStage.h
@brief �Q�[���X�e�[�W
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	�Q�[���X�e�[�W�N���X
	//--------------------------------------------------------------------------------------
	class SelectStage : public Stage {
		//�r���[�̍쐬
		void CreateViewLight();
		//vector<shared_ptr<GameObject>> m_ptrNum = {0,0,0,0,0,0,0,0,0};
	public:
		//�\�z�Ɣj��
		SelectStage() :Stage() {}
		virtual ~SelectStage() {}
		//������
		virtual void OnCreate()override;

		void CreateSprite();
	};

	//--------------------------------------------------------------------------------------
	//	�|�C���^�[
	//--------------------------------------------------------------------------------------
	class Pointer : public GameObject
	{
		bool m_trace;
		Vec2 m_startScale;
		Vec3 m_startPos;
		wstring m_textureKey;

		Vec3 m_posArray[9];
		int m_selectNum;

		float m_frameCount;

		//�o�b�N�A�b�v���_�f�[�^
		vector<VertexPositionTexture> m_backupVertices;

	public:
		Pointer(const shared_ptr<Stage>& stagePtr, bool trace,
			const Vec2& startScale, const Vec3& startPos,Vec3 posArray[9]);
		virtual ~Pointer();
		virtual void OnCreate() override;
		virtual void OnUpdate() override;

	};

	class StageNumUI : public GameObject
	{
	private:
		Vec3 m_pos, m_scale;
		wstring m_texkey;
		int m_num;
	public:
		StageNumUI(const shared_ptr<Stage>& stagePtr, const Vec2& pos, const Vec3& scale, wstring texkey,int num)
			: GameObject(stagePtr), m_pos(pos.x, pos.y, 0.0f), m_scale(scale), m_texkey(texkey), m_num(num)
		{
		}

		void OnCreate() override;
	};
}
//end basecross

