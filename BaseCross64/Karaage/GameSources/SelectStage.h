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

		Vec3 m_posArray[9];
		int m_selectNum;

		float m_frameCount;

		//バックアップ頂点データ
		vector<VertexPositionTexture> m_backupVertices;

	public:
		Pointer(const shared_ptr<Stage>& stagePtr, bool trace,
			const Vec2& startScale, const Vec3& startPos,Vec3 posArray[9]);
		virtual ~Pointer();
		virtual void OnCreate() override;
		virtual void OnUpdate() override;

	};
}
//end basecross

