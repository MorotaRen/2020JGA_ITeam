/*!
@file GameStage.h
@brief ゲームステージ
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス
	//--------------------------------------------------------------------------------------
	class SelectStage : public Stage {
		//ビューの作成
		void CreateViewLight();
	public:
		//構築と破棄
		SelectStage() :Stage() {}
		virtual ~SelectStage() {}
		//初期化
		virtual void OnCreate()override;

		void CreateSprite();
	};

	//--------------------------------------------------------------------------------------
	//	ポインター
	//--------------------------------------------------------------------------------------
	class Pointer : public GameObject
	{
		bool m_trace;
		Vec2 m_startScale;
		Vec3 m_startPos;
		wstring m_textureKey;

		//バックアップ頂点データ
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

