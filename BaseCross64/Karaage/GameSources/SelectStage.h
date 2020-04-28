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

		//�o�b�N�A�b�v���_�f�[�^
		vector<VertexPositionTexture> m_backupVertices;

	public:
		Pointer(const shared_ptr<Stage>& StagePtr, bool Trace,
			const Vec2& StartScale, const Vec3& StartPos, wstring TextureKey);
		virtual ~Pointer();
		virtual void OnCreate() override;
		virtual void OnUpdate() override;

	};
}
//end basecross

