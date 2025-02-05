/*!
@file DrawComponents.h
@brief 描画コンポーネント
@copyright Copyright (c) 2017 WiZ Tamura Hiroki,Yamanoi Yasushi.
*/
#pragma once
#include "stdafx.h"

namespace basecross {

	//各シェーダ
	DECLARE_DX12SHADER(VSShadowmap)
	//スプライト
	DECLARE_DX12SHADER(VSPTSprite)
	DECLARE_DX12SHADER(PSPTSprite)


	DECLARE_DX12SHADER(VSPNStatic)
	DECLARE_DX12SHADER(PSPNStatic)

	DECLARE_DX12SHADER(VSPNTStatic)
	DECLARE_DX12SHADER(PSPNTStatic)

	DECLARE_DX12SHADER(VSPNTStaticShadow)
	DECLARE_DX12SHADER(PSPNTStaticShadow)
	DECLARE_DX12SHADER(PSPNTStaticShadow2)

	DECLARE_DX12SHADER(VSPCSprite)
	DECLARE_DX12SHADER(PSPCSprite)

	DECLARE_DX12SHADER(VSPCTSprite)
	DECLARE_DX12SHADER(PSPCTSprite)


	//--------------------------------------------------------------------------------------
	///	コンスタントバッファクラス
	//--------------------------------------------------------------------------------------
	template<typename ConstType>
	struct Dx12Constants {
		//コンスタントバッファ（C++側）
		ConstType m_ConstantBuffer;
		///コンスタントバッファアップロードヒープ
		ComPtr<ID3D12Resource> m_ConstantBufferUploadHeap;
		Dx12Constants() {}
		~Dx12Constants(){}
	};


	class GameObject;

	//--------------------------------------------------------------------------------------
	///	汎用描画用
	//--------------------------------------------------------------------------------------
	class GenericDraw :public ObjectInterface {
		void PCWireFrameDraw(const shared_ptr<GameObject>& GameObjectPtr, const shared_ptr<MeshResource>& MeshRes,
			const bsm::Col4& Emissive, const bsm::Col4& Diffuse, const bsm::Mat4x4& MeshToTransformMatrix);
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief	コンストラクタ
		*/
		//--------------------------------------------------------------------------------------
		GenericDraw();
		//--------------------------------------------------------------------------------------
		/*!
		@brief	デストラクタ
		*/
		//--------------------------------------------------------------------------------------
		virtual ~GenericDraw();
		//操作
		//--------------------------------------------------------------------------------------
		/*!
		@brief	OnCreate処理
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnCreate()override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	ワイアフレーム描画処理
		@param[in]	GameObj	ゲームオブジェクト
		@param[in]	Mesh	PCメッシュ
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void DrawWireFrame(const shared_ptr<GameObject>& GameObj,
			const shared_ptr<MeshResource>& Mesh, const bsm::Mat4x4& MeshToTransformMatrix = bsm::Mat4x4());
		void DrawWireFrameWithWorldMatrix(const shared_ptr<GameObject>& GameObj,
			const shared_ptr<MeshResource>& Mesh, const bsm::Mat4x4& worldMatrix) {

		}
	};


	//--------------------------------------------------------------------------------------
	///	アニメーションデータ構造体.
	//--------------------------------------------------------------------------------------
	struct	AnimationData
	{
		///	スタートサンプル
		UINT	m_StartSample;
		///	サンプルの長さ
		UINT	m_SampleLength;
		///	ループするかどうか
		bool	m_IsLoop;
		///	アニメが終了したかどうか
		bool	m_IsAnimeEnd;
		///	1秒当たりのフレーム
		float	m_SamplesParSecond;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	コンストラクタ.
		*/
		//--------------------------------------------------------------------------------------
		AnimationData()
		{
			ZeroMemory(this, sizeof(AnimationData));
		}
		//--------------------------------------------------------------------------------------
		/*!
		@brief	コンストラクタ.
		@param[in]	StartSample	スタートフレーム
		@param[in]	SampleLength	フレームの長さ
		@param[in]	bLoop	ループするかどうか
		@param[in]	SamplesParSecond = 30.0f	1秒あたりのフレーム数
		*/
		//--------------------------------------------------------------------------------------
		AnimationData(UINT StartSample, UINT SampleLength, bool bLoop,
			float SamplesParSecond = 30.0f) :
			m_StartSample{ StartSample },
			m_SampleLength{ SampleLength },
			m_IsLoop{ bLoop },
			m_IsAnimeEnd{ false },
			m_SamplesParSecond{ SamplesParSecond }
		{}
	};



	//--------------------------------------------------------------------------------------
	///	描画に使用する構造体(親)
	//--------------------------------------------------------------------------------------
	struct DrawObjectBase {
		//メッシュリソース
		weak_ptr<MeshResource> m_MeshResource;
		//三角形衝突判定等に使うテンポラリ配列（static）
		static vector<bsm::Vec3> m_TempPositions;
		//マルチメッシュリソース
		weak_ptr<MultiMeshResource> m_MultiMeshResource;
		//以下、ボーンモデル用
		//ローカルボーン行列の配列
		vector<bsm::Mat4x4> m_LocalBonesMatrix;
		//ローカルボーン行列の配列(マルチメッシュ用)
		vector<vector<bsm::Mat4x4>> m_MultiLocalBonesMatrix;
		//アニメーション定義のマップ
		map<wstring, AnimationData> m_AnimationMap;
		//現在のアニメーション名
		wstring m_CurrentAnimeName;
		//カレントアニメーション
		float m_CurrentAnimeTime;
		//--------------------------------------------------------------------------------------
		/*!
		@brief コンストラクタ
		*/
		//--------------------------------------------------------------------------------------
		DrawObjectBase() :
			m_CurrentAnimeName(L""),
			m_CurrentAnimeTime(0)
		{}
		//--------------------------------------------------------------------------------------
		/*!
		@brief ボーンの初期化
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void BoneInit() {
/*
			auto MeshRes = m_MeshResource.lock();
			if (MeshRes && MeshRes->IsSkining() && MeshRes->GetBoneCount() > 0 && MeshRes->GetSampleCount() > 0) {
				//先頭のボーン数の行列で初期化
				m_LocalBonesMatrix.resize(MeshRes->GetBoneCount());
				auto& SampleMatrixVec = MeshRes->GetSampleMatrixVec();
				for (UINT i = 0; i < m_LocalBonesMatrix.size(); i++) {
					m_LocalBonesMatrix[i] = SampleMatrixVec[i];
				}
			}
			//マルチメッシュ用
			auto MultiMeshRes = m_MultiMeshResource.lock();
			if (MultiMeshRes && MultiMeshRes->IsSkining(0) && MultiMeshRes->GetBoneCount(0) > 0 && MultiMeshRes->GetSampleCount(0) > 0) {
				m_MultiLocalBonesMatrix.resize(MultiMeshRes->GetMeshVecCount());
				for (size_t i = 0; i < MultiMeshRes->GetMeshVecCount(); i++) {
					m_MultiLocalBonesMatrix[i].resize(MultiMeshRes->GetBoneCount(i));
					auto& SampleMatrixVec = MultiMeshRes->GetSampleMatrixVec(i);
					for (UINT j = 0; j < m_MultiLocalBonesMatrix[i].size(); j++) {
						m_MultiLocalBonesMatrix[i][j] = SampleMatrixVec[j];
					}
				}
			}
*/

		}
		//--------------------------------------------------------------------------------------
		/*!
		@brief	現在のアニメーションを変更する
		@param[in]	AnemationName	アニメーション名（すでに追加されているもの）
		@param[in]	StartTime = 0.0f	開始からの秒数
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void ChangeCurrentAnimation(const wstring& AnemationName, float StartTime = 0.0f) {
/*
			auto MeshRes = m_MeshResource.lock();
			bool MeshResFlg = MeshRes && MeshRes->IsSkining() && MeshRes->GetBoneCount() > 0 && MeshRes->GetSampleCount() > 0;
			//マルチメッシュ用
			auto MultiMeshRes = m_MultiMeshResource.lock();
			bool MultiMeshResFlg = MultiMeshRes && MultiMeshRes->IsSkining(0) && MultiMeshRes->GetBoneCount(0) > 0 && MultiMeshRes->GetSampleCount(0) > 0;
			if (MeshResFlg || MultiMeshResFlg) {
				if (AnemationName == L"") {
					throw BaseException(
						L"アニメーション名が空白です",
						L"if (AnemationName == L\"\")",
						L"DrawObjectBase::SetCurrentAnimation()"
					);
				}
				auto it = m_AnimationMap.find(AnemationName);
				if (it != m_AnimationMap.end()) {
					//指定の名前が見つかった
					m_CurrentAnimeName = AnemationName;
					m_CurrentAnimeTime = StartTime;
					//アニメーションは終了していない
					it->second.m_IsAnimeEnd = false;
				}
				else {
					//見つからない
					throw BaseException(
						L"指定のアニメーションは登録されてません",
						AnemationName,
						L"DrawObjectBase::SetCurrentAnimation()"
					);
				}
			}
*/
		}
		//--------------------------------------------------------------------------------------
		/*!
		@brief	アニメーションを追加する
		@param[in]	Name	アニメーション名
		@param[in]	StartSample	開始サンプル
		@param[in]	SampleLength	サンプルの長さ
		@param[in]	Loop	ループするかどうか
		@param[in]	SamplesParSecond = 30.0f	1秒あたりのサンプル数
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void AddAnimation(const wstring& Name, int StartSample, int SampleLength, bool Loop,
			float SamplesParSecond = 30.0f) {
/*
			auto MeshRes = m_MeshResource.lock();
			bool MeshResFlg = MeshRes && MeshRes->IsSkining() && MeshRes->GetBoneCount() > 0 && MeshRes->GetSampleCount() > 0;
			//マルチメッシュ用
			auto MultiMeshRes = m_MultiMeshResource.lock();
			bool MultiMeshResFlg = MultiMeshRes && MultiMeshRes->IsSkining(0) && MultiMeshRes->GetBoneCount(0) > 0 && MultiMeshRes->GetSampleCount(0) > 0;
			if (MeshResFlg || MultiMeshResFlg) {
				if (Name == L"") {
					throw BaseException(
						L"アニメーション名が空白です",
						L"if (Name == L\"\")",
						L"DrawObjectBase::AddAnimation()"
					);
				}
				if (StartSample < 0 || SampleLength < 0) {
					throw BaseException(
						L"開始サンプルかサンプル数が0未満です",
						L"if (StartSample < 0 || SampleLength < 0)",
						L"DrawObjectBase::AddAnimation()"
					);
				}
				if (SamplesParSecond <= 0.0f) {
					throw BaseException(
						L"サンプル毎秒が0以下です",
						L"if (SamplesParSecond <= 0.0f)",
						L"DrawObjectBase::AddAnimation()"
					);
				}
				//重複キーがあれば差し替える
				AnimationData Data((UINT)StartSample, (UINT)SampleLength, Loop, SamplesParSecond);
				m_AnimationMap[Name] = Data;
				if (m_AnimationMap.size() == 1) {
					//1つしか登録がなかったら、カレントアニメは該当アニメとなる
					ChangeCurrentAnimation(Name, 0);
				}
			}
*/
		}
		//--------------------------------------------------------------------------------------
		/*!
		@brief	開始行列から終了行列の間のt時間時の行列を返す
		@param[in]	m1	開始の行列
		@param[in]	m2	終了の行列
		@param[in]	t	時間（0から1.0f）
		@param[out]	out	結果を受け取る行列
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void InterpolationMatrix(const bsm::Mat4x4& m1, const bsm::Mat4x4& m2, float t, bsm::Mat4x4& out) {
			bsm::Vec3 Scale1, Pos1;
			bsm::Quat Qt1;
			m1.decompose(Scale1, Qt1, Pos1);
			Qt1.normalize();

			bsm::Vec3 Scale2, Pos2;
			bsm::Quat Qt2;

			m2.decompose(Scale2, Qt2, Pos2);
			Qt2.normalize();

			bsm::Vec3 ScaleOut, PosOut;
			bsm::Quat QtOut;

			ScaleOut = Lerp::CalculateLerp(Scale1, Scale2, 0.0f, 1.0f, t, Lerp::Linear);
			PosOut = Lerp::CalculateLerp(Pos1, Pos2, 0.0f, 1.0f, t, Lerp::Linear);
			QtOut = XMQuaternionSlerp(Qt1, Qt2, t);
			out.affineTransformation(ScaleOut, bsm::Vec3(0, 0, 0), QtOut, PosOut);
		}
		//--------------------------------------------------------------------------------------
		/*!
		@brief	現在のアニメーションデータを得る
		@return	現在のアニメーションデータ
		*/
		//--------------------------------------------------------------------------------------
		AnimationData& GetAnimationData() {
/*
			auto MeshRes = m_MeshResource.lock();
			bool MeshResFlg = MeshRes && MeshRes->IsSkining() && MeshRes->GetBoneCount() > 0 && MeshRes->GetSampleCount() > 0;
			//マルチメッシュ用
			auto MultiMeshRes = m_MultiMeshResource.lock();
			bool MultiMeshResFlg = MultiMeshRes && MultiMeshRes->IsSkining(0) && MultiMeshRes->GetBoneCount(0) > 0 && MultiMeshRes->GetSampleCount(0) > 0;
			if (MeshResFlg || MultiMeshResFlg) {
				if (m_CurrentAnimeName == L"") {
					//見つからない
					throw BaseException(
						L"カレントアニメーションが設定されてません",
						L"if (m_CurrentAnimeName == L\"\")",
						L"DrawObjectBase::GetAnimationData()"
					);
				}
				return m_AnimationMap[m_CurrentAnimeName];
			}
*/
			//ボーンデータではない
			throw BaseException(
				L"ボーン付きのメッシュではありません",
				L"!MeshRes->IsSkining()",
				L"DrawObjectBase::GetAnimationData()"
			);
		}
		//--------------------------------------------------------------------------------------
		/*!
		@brief	現在のアニメーションを進める
		@param[in]	ElapsedTime	経過時間
		@return	アニメーションが終了すればtrue
		*/
		//--------------------------------------------------------------------------------------
		bool UpdateAnimation(float ElapsedTime) {
			return false;
/*
			auto MeshRes = m_MeshResource.lock();
			bool MeshResFlg = MeshRes && MeshRes->IsSkining() && MeshRes->GetBoneCount() > 0 && MeshRes->GetSampleCount() > 0;
			//マルチメッシュ用
			auto MultiMeshRes = m_MultiMeshResource.lock();
			bool MultiMeshResFlg = MultiMeshRes && MultiMeshRes->IsSkining(0) && MultiMeshRes->GetBoneCount(0) > 0 && MultiMeshRes->GetSampleCount(0) > 0;
			if (MeshResFlg || MultiMeshResFlg) {
				if (ElapsedTime < 0.0f) {
					throw BaseException(
						L"アニメーション更新にマイナスは設定できません",
						L"if (ElapsedTime < 0.0f)",
						L"DrawObjectBase::UpdateAnimation()"
					);
				}
				if (m_CurrentAnimeName == L"") {
					//見つからない
					throw BaseException(
						L"カレントアニメーションが設定されてません",
						L"if (m_CurrentAnimeName == L\"\")",
						L"DrawObjectBase::UpdateAnimation()"
					);
				}
				if (MeshResFlg) {
					auto PtrMesh = MeshRes;
					UINT SampleCount = PtrMesh->GetSampleCount();
					auto& SampleMatrixVec = PtrMesh->GetSampleMatrixVec();
					UINT BoneCount = PtrMesh->GetBoneCount();
					auto& TgtAnimeData = m_AnimationMap[m_CurrentAnimeName];
					if (TgtAnimeData.m_StartSample >= SampleCount) {
						//スタートのサンプルが最後のサンプル以降だった
						TgtAnimeData.m_StartSample = SampleCount - 1;
						TgtAnimeData.m_SampleLength = 0;
						UINT UITgtSample = TgtAnimeData.m_StartSample;
						//最後のサンプルを表示
						for (UINT i = 0; i < m_LocalBonesMatrix.size(); i++) {
							m_LocalBonesMatrix[i] = SampleMatrixVec[BoneCount * UITgtSample + i];
						}
						m_CurrentAnimeTime = 0;
						if (TgtAnimeData.m_IsLoop) {
							TgtAnimeData.m_IsAnimeEnd = false;
							return false;
						}
						else {
							TgtAnimeData.m_IsAnimeEnd = true;
							return true;
						}
					}
					//すでにアニメが終了している
					if (TgtAnimeData.m_IsAnimeEnd) {
						//現在のローカル行列を使用
						return true;
					}
					//カレントタイムを更新
					m_CurrentAnimeTime += ElapsedTime;
					//スタート位置を計算
					auto FLOATTgtSample = (float)TgtAnimeData.m_StartSample + m_CurrentAnimeTime * TgtAnimeData.m_SamplesParSecond;
					UINT UITgtSample = (UINT)FLOATTgtSample;
					UINT UILastSample = TgtAnimeData.m_StartSample + TgtAnimeData.m_SampleLength;
					if (UILastSample >= SampleCount) {
						UILastSample = SampleCount - 1;
					}
					if (UITgtSample >= UILastSample) {
						UITgtSample = UILastSample - 1;
						//最後のサンプルを表示
						for (UINT i = 0; i < m_LocalBonesMatrix.size(); i++) {
							m_LocalBonesMatrix[i] = SampleMatrixVec[BoneCount * UITgtSample + i];
						}
						if (TgtAnimeData.m_IsLoop) {
							TgtAnimeData.m_IsAnimeEnd = false;
							//ループするのでカレントタイムを0にする
							m_CurrentAnimeTime = 0;
							return false;
						}
						else {
							m_CurrentAnimeTime = TgtAnimeData.m_SampleLength / TgtAnimeData.m_SamplesParSecond;
							TgtAnimeData.m_IsAnimeEnd = true;
							return true;
						}
					}
					else {
						//サンプルとサンプルの間の割合を計算
						FLOATTgtSample -= (float)UITgtSample;
						UINT UINextSample = UITgtSample + 1;
						for (UINT i = 0; i < m_LocalBonesMatrix.size(); i++) {
							InterpolationMatrix(
								SampleMatrixVec[BoneCount * UITgtSample + i],
								SampleMatrixVec[BoneCount * UINextSample + i],
								FLOATTgtSample, m_LocalBonesMatrix[i]);
						}
						//アニメは終わってない
						return false;
					}
					return true;
				}
				else if (MultiMeshResFlg) {
					//サンプル数は最初のメッシュのを使用
					UINT SampleCount = MultiMeshRes->GetSampleCount(0);
					auto& TgtAnimeData = m_AnimationMap[m_CurrentAnimeName];
					if (TgtAnimeData.m_StartSample >= SampleCount) {
						//スタートのサンプルが最後のサンプル以降だった
						TgtAnimeData.m_StartSample = SampleCount - 1;
						TgtAnimeData.m_SampleLength = 0;
						UINT UITgtSample = TgtAnimeData.m_StartSample;
						//最後のサンプルを表示
						for (size_t mc = 0; mc < MultiMeshRes->GetMeshVecCount(); mc++) {
							auto& SampleMatrixVec = MultiMeshRes->GetSampleMatrixVec(mc);
							UINT BoneCount = MultiMeshRes->GetBoneCount(mc);
							for (UINT i = 0; i < m_MultiLocalBonesMatrix[mc].size(); i++) {
								m_MultiLocalBonesMatrix[mc][i] = SampleMatrixVec[BoneCount * UITgtSample + i];
							}
						}
						m_CurrentAnimeTime = 0;
						if (TgtAnimeData.m_IsLoop) {
							TgtAnimeData.m_IsAnimeEnd = false;
							return false;
						}
						else {
							TgtAnimeData.m_IsAnimeEnd = true;
							return true;
						}
					}
					//すでにアニメが終了している
					if (TgtAnimeData.m_IsAnimeEnd) {
						//現在のローカル行列を使用
						return true;
					}
					//カレントタイムを更新
					m_CurrentAnimeTime += ElapsedTime;
					//スタート位置を計算
					auto FLOATTgtSample = (float)TgtAnimeData.m_StartSample + m_CurrentAnimeTime * TgtAnimeData.m_SamplesParSecond;
					UINT UITgtSample = (UINT)FLOATTgtSample;
					UINT UILastSample = TgtAnimeData.m_StartSample + TgtAnimeData.m_SampleLength;
					if (UILastSample >= SampleCount) {
						UILastSample = SampleCount - 1;
					}
					if (UITgtSample >= UILastSample) {
						UITgtSample = UILastSample - 1;
						//最後のサンプルを表示
						for (size_t mc = 0; mc < MultiMeshRes->GetMeshVecCount(); mc++) {
							auto& SampleMatrixVec = MultiMeshRes->GetSampleMatrixVec(mc);
							UINT BoneCount = MultiMeshRes->GetBoneCount(mc);
							for (UINT i = 0; i < m_MultiLocalBonesMatrix[mc].size(); i++) {
								m_MultiLocalBonesMatrix[mc][i] = SampleMatrixVec[BoneCount * UITgtSample + i];
							}
						}
						if (TgtAnimeData.m_IsLoop) {
							TgtAnimeData.m_IsAnimeEnd = false;
							//ループするのでカレントタイムを0にする
							m_CurrentAnimeTime = 0;
							return false;
						}
						else {
							m_CurrentAnimeTime = TgtAnimeData.m_SampleLength / TgtAnimeData.m_SamplesParSecond;
							TgtAnimeData.m_IsAnimeEnd = true;
							return true;
						}
					}
					else {
						//サンプルとサンプルの間の割合を計算
						FLOATTgtSample -= (float)UITgtSample;
						UINT UINextSample = UITgtSample + 1;
						for (size_t mc = 0; mc < MultiMeshRes->GetMeshVecCount(); mc++) {
							auto& SampleMatrixVec = MultiMeshRes->GetSampleMatrixVec(mc);
							UINT BoneCount = MultiMeshRes->GetBoneCount(mc);

							for (UINT i = 0; i < m_MultiLocalBonesMatrix[mc].size(); i++) {
								InterpolationMatrix(
									SampleMatrixVec[BoneCount * UITgtSample + i],
									SampleMatrixVec[BoneCount * UINextSample + i],
									FLOATTgtSample, m_MultiLocalBonesMatrix[mc][i]);
							}
						}
						//アニメは終わってない
						return false;
					}
					return true;
				}
			}
			return true;
*/
		}
	};


	//--------------------------------------------------------------------------------------
	///	描画コンポーネントの親クラス
	//--------------------------------------------------------------------------------------
	class DrawComponent : public Component {
	protected:
		//--------------------------------------------------------------------------------------
		/*!
		@brief	プロテクトコンストラクタ
		@param[in]	GameObjectPtr	ゲームオブジェクト
		*/
		//--------------------------------------------------------------------------------------
		DrawComponent(const shared_ptr<GameObject>& GameObjectPtr);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	プロテクトデストラクタ
		*/
		//--------------------------------------------------------------------------------------
		virtual ~DrawComponent();
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief	ブレンドステートの取得
		@return	ブレンドステート
		*/
		//--------------------------------------------------------------------------------------
		BlendState GetBlendState() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	デプスステンシルステートの取得
		@return	デプスステンシルステート
		*/
		//--------------------------------------------------------------------------------------
		DepthStencilState GetDepthStencilState() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	ラスタライザステートの取得
		@return	ラスタライザステート
		*/
		//--------------------------------------------------------------------------------------
		RasterizerState GetRasterizerState() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	サンプラーステートの取得
		@return	サンプラーステート
		*/
		//--------------------------------------------------------------------------------------
		SamplerState GetSamplerState() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	ブレンドステートの設定
		@param[in]	state	ブレンドステート
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void SetBlendState(const BlendState state);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	ブレンドステートのデバイスへの設定。
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void SetDeviceBlendState();
		//--------------------------------------------------------------------------------------
		/*!
		@brief	デプスステンシルステートの設定
		@param[in]	state	デプスステンシルステート
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void SetDepthStencilState(const DepthStencilState state);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	デプスステンシルステートのデバイスへの設定
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void SetDeviceDepthStencilState();
		//--------------------------------------------------------------------------------------
		/*!
		@brief	ラスタライザステートの設定
		@param[in]	state	ラスタライザステート
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void SetRasterizerState(const RasterizerState state);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	ラスタライザステートのデバイスへの設定
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void SetDeviceRasterizerState();
		//--------------------------------------------------------------------------------------
		/*!
		@brief	サンプラーステートの設定
		@param[in]	state	サンプラーステート
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void SetSamplerState(const SamplerState state);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	サンプラーステートのデバイスへの設定
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void SetDeviceSamplerState();
		//--------------------------------------------------------------------------------------
		/*!
		@brief	メッシュとワールド行列の間を補完する行列の取得<br />
		メッシュのサイズや向き、中心の位置がゲームオブジェクトのワールド行列と差異がある場合、<br />
		その間を補完する行列を設定できる。
		@return	メッシュとワールド行列の間を補完する行列
		*/
		//--------------------------------------------------------------------------------------
		const bsm::Mat4x4& GetMeshToTransformMatrix() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	メッシュとワールド行列の間を補完する行列の取得<br />
		メッシュのサイズや向き、中心の位置がゲームオブジェクトのワールド行列と差異がある場合、<br />
		その間を補完する行列を設定できる。
		@param[in]	Mat	設定する行列
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void SetMeshToTransformMatrix(const bsm::Mat4x4& Mat);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	各オブジェクトごとにボーンを所持しておくポインタ<br />
		シャドウマップなどから参照できるように仮想関数にする<br />
		派生クラスでボーンを所持する場合は多重定義する
		@return	ボーン行列の配列のポインタ
		*/
		//--------------------------------------------------------------------------------------
		virtual const vector< bsm::Mat4x4 >* GetVecLocalBonesPtr() const { return nullptr; }
		//--------------------------------------------------------------------------------------
		/*!
		@brief	各オブジェクトごとにボーンを所持しておくポインタ（マルチメッシュ版）<br />
		シャドウマップなどから参照できるように仮想関数にする<br />
		派生クラスでボーンを所持する場合は多重定義する
		@return	ボーン行列の配列のポインタ
		*/
		//--------------------------------------------------------------------------------------
		virtual const vector< bsm::Mat4x4 >* GetVecMultiLocalBonesPtr(size_t index) const { return nullptr; }
	private:
		// pImplイディオム
		struct Impl;
		unique_ptr<Impl> pImpl;
	};




	//--------------------------------------------------------------------------------------
	///	PCTParticle描画コンポーネント(パーティクル描画)
	//--------------------------------------------------------------------------------------
	class PCTParticleDraw : public DrawComponent {
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief	コンストラクタ
		@param[in]	GameObjectPtr	ゲームオブジェクト
		@param[in]	MaxInstance	パーティクル数上限
		@param[in]	AddType	加算処理するかどうか
		*/
		//--------------------------------------------------------------------------------------
		explicit PCTParticleDraw(const shared_ptr<GameObject>& GameObjectPtr, size_t MaxInstance, bool AddType = false);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	デストラクタ
		*/
		//--------------------------------------------------------------------------------------
		virtual ~PCTParticleDraw();
		//操作
		//--------------------------------------------------------------------------------------
		/*!
		@brief	描画用パーティクルを登録する
		@param[in]	ToCaneraLength	カメラまでの距離
		@param[in]	WorldMatrix	ワールド行列
		@param[in]	TextureRes	テクスチャ
		@param[in]	TextureRes	テクスチャ
		@param[in]	Diffuse   Diffuseカラー
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void AddParticle(float ToCaneraLength, const bsm::Mat4x4& WorldMatrix,
			const shared_ptr<TextureResource>& TextureRes, const bsm::Col4& Diffuse = bsm::Col4(1, 1, 1, 1));
		//--------------------------------------------------------------------------------------
		/*!
		@brief	OnCreate処理
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnCreate()override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	OnUpdate処理（空関数）
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnUpdate()override {}
		//--------------------------------------------------------------------------------------
		/*!
		@brief	OnDraw処理
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnDraw()override;
	private:
		// pImplイディオム
		struct Impl;
		unique_ptr<Impl> pImpl;
	};


	//--------------------------------------------------------------------------------------
	///	Dx12描画リソースクラス
	//--------------------------------------------------------------------------------------
	template<typename ContType>
	struct Dx12DrawResources {
		///ルートシグネチャ
		ComPtr<ID3D12RootSignature> m_RootSignature;
		///デスクプリタハンドルのインクリメントサイズ
		UINT m_DescriptorHandleIncrementSize{ 0 };
		///Samplerのデスクプリタハンドルのインクリメントサイズ
		UINT m_SamplerDescriptorHandleIncrementSize{ 0 };
		///デスクプリタヒープ
		ComPtr<ID3D12DescriptorHeap> m_DescriptorHeap;
		ComPtr<ID3D12DescriptorHeap> m_SamplerDescriptorHeap;
		///GPU側デスクプリタのハンドルの配列
		vector<CD3DX12_GPU_DESCRIPTOR_HANDLE> m_GPUDescriptorHandleVec;
		///コンスタントバッファ
		Dx12Constants<ContType> m_Dx12Constants;
		///コンスタントバッファのGPU側変数
		void* m_pConstantBuffer{ nullptr };
		void* m_pConstantBufferWithShadow{ nullptr };
		///パイプラインステート
		D3D12_GRAPHICS_PIPELINE_STATE_DESC m_PineLineDesc;
		//一般用
		ComPtr<ID3D12PipelineState> m_PipelineState;
		//正面のみ
		ComPtr<ID3D12PipelineState> m_CullBackPipelineState;
		//背面のみ
		ComPtr<ID3D12PipelineState> m_CullFrontPipelineState;
		///コマンドリスト
		ComPtr<ID3D12GraphicsCommandList> m_CommandList;
	};
	//--------------------------------------------------------------------------------------
	///	スプライト用コンスタントバッファ構造体
	//--------------------------------------------------------------------------------------
	struct SpriteConstants
	{
		/// ワールド行列
		bsm::Mat4x4 World;
		/// エミッシブ色
		bsm::Col4 Emissive;
		/// デフューズ色
		bsm::Col4 Diffuse;
		SpriteConstants() {
			memset(this, 0, sizeof(SpriteConstants));
			Diffuse = bsm::Col4(1.0f, 1.0f, 1.0f, 1.0f);
		};
	};



	//--------------------------------------------------------------------------------------
	///	Sprite描画オブジェクトの親
	//--------------------------------------------------------------------------------------
	class SpriteBaseDraw : public DrawComponent {
		///Dx12描画リソースの取得
		Dx12DrawResources<SpriteConstants>& GetDx12DrawResources();
		///シェーダーリソースビュー作成
		void CreateShaderResourceView();
		//コンスタントバッファ更新
		void UpdateConstantBuffer();
		///プロパティ変更
		void RefreshTrace();
		///描画処理
		template<typename VertexType>
		void DrawObject() {
			auto ShMesh = GetMeshResource();
			auto ShTex = GetTextureResource();
			if (!ShMesh) {
				return;
			}
			//透明処理
			RefreshTrace();
			//コマンドリストのリセット
			if (GetGameObject()->IsAlphaActive()) {
				CommandList::Reset(GetDx12DrawResources().m_CullFrontPipelineState, GetDx12DrawResources().m_CommandList);
			}
			else {
				CommandList::Reset(GetDx12DrawResources().m_CullBackPipelineState, GetDx12DrawResources().m_CommandList);
			}
			ShMesh->UpdateResources<VertexType>(GetDx12DrawResources().m_CommandList);
			if (ShTex) {
				ShTex->UpdateResources(GetDx12DrawResources().m_CommandList);
			}
			//描画
			GetDx12DrawResources().m_CommandList->SetGraphicsRootSignature(GetDx12DrawResources().m_RootSignature.Get());
			ID3D12DescriptorHeap* ppHeaps[] = { GetDx12DrawResources().m_DescriptorHeap.Get(), GetDx12DrawResources().m_SamplerDescriptorHeap.Get() };
			GetDx12DrawResources().m_CommandList->SetDescriptorHeaps(_countof(ppHeaps), ppHeaps);

			for (size_t i = 0; i < GetDx12DrawResources().m_GPUDescriptorHandleVec.size(); i++) {
				GetDx12DrawResources().m_CommandList->SetGraphicsRootDescriptorTable((UINT)i, GetDx12DrawResources().m_GPUDescriptorHandleVec[i]);
			}
			auto Dev = App::GetApp()->GetDeviceResources();
			GetDx12DrawResources().m_CommandList->RSSetViewports(1, &Dev->GetViewport());
			GetDx12DrawResources().m_CommandList->RSSetScissorRects(1, &Dev->GetScissorRect());
			CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle(
				Dev->GetRtvHeap()->GetCPUDescriptorHandleForHeapStart(),
				Dev->GetFrameIndex(),
				Dev->GetRtvDescriptorSize());
			CD3DX12_CPU_DESCRIPTOR_HANDLE dsvHandle(
				Dev->GetDsvHeap()->GetCPUDescriptorHandleForHeapStart()
			);
			GetDx12DrawResources().m_CommandList->OMSetRenderTargets(1, &rtvHandle, FALSE, &dsvHandle);

			GetDx12DrawResources().m_CommandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
			GetDx12DrawResources().m_CommandList->IASetIndexBuffer(&ShMesh->GetIndexBufferView());
			GetDx12DrawResources().m_CommandList->IASetVertexBuffers(0, 1, &ShMesh->GetVertexBufferView());


			GetDx12DrawResources().m_CommandList->DrawIndexedInstanced(ShMesh->GetNumIndicis(), 1, 0, 0, 0);
			if (GetGameObject()->IsAlphaActive()) {
				GetDx12DrawResources().m_CommandList->SetPipelineState(GetDx12DrawResources().m_CullBackPipelineState.Get());
				GetDx12DrawResources().m_CommandList->DrawIndexedInstanced(ShMesh->GetNumIndicis(), 1, 0, 0, 0);
			}
			//コマンドリストのクローズ
			CommandList::Close(GetDx12DrawResources().m_CommandList);
			//デバイスにコマンドリストを送る
			Dev->InsertDrawCommandLists(GetDx12DrawResources().m_CommandList.Get());
		}
	protected:
		//--------------------------------------------------------------------------------------
		/*!
		@brief コンストラクタ
		@param[in]	StagePtr	ステージのポインタ
		*/
		//--------------------------------------------------------------------------------------
		explicit SpriteBaseDraw(const shared_ptr<GameObject>& GameObjectPtr);
		//--------------------------------------------------------------------------------------
		/*!
		@brief デストラクタ
		*/
		//--------------------------------------------------------------------------------------
		virtual ~SpriteBaseDraw();
		//--------------------------------------------------------------------------------------
		/*!
		@brief	コンスタントバッファの設定
		@param[out]	SmCb	設定するコンスタントバッファ構造体
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void SetConstants(Dx12Constants<SpriteConstants>& SpCb);
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief	頂点変更できるスプライトメッシュを作成する（すでにある場合は差し替える）
		@param[in]	Vertices	頂点の配列
		@param[in]	indices		インデックスの配列
		*/
		//--------------------------------------------------------------------------------------
		template<typename T>
		void CreateMesh(vector<T>& Vertices, vector<uint16_t>& indices) {
			try {
				//メッシュの作成（変更できる）
				auto SpriteMesh = MeshResource::CreateMeshResource(Vertices, indices, true);
				SetMeshResource(SpriteMesh);
			}
			catch (...) {
				throw;
			}
		}
		//--------------------------------------------------------------------------------------
		/*!
		@brief	頂点バッファの更新
		@param[in]	Vertices	頂点配列
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		template<typename T>
		void UpdateVertices(const vector<T>& Vertices) {
			auto SpriteMesh = GetMeshResource();
			if (!SpriteMesh) {
				throw BaseException(
					L"メッシュが作成されていません",
					L"if (!GetMeshResource())",
					L"SpriteBaseDraw::UpdateVertices()"
				);

			}
			if (Vertices.size() > SpriteMesh->GetNumVertices()) {
				throw BaseException(
					L"更新する頂点が大きすぎます",
					L"if (Vertices.size() > SpriteMesh->GetNumVertices())",
					L"SpriteBaseDraw::UpdateVertices()"
				);
			}
			SpriteMesh->UpdateVirtex(Vertices);
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief	スプライトメッシュの描画
		@tparam[in]	T_VShader	使用する頂点シェーダ
		@tparam[in]	T_PShader	使用するピクセルシェーダ
		@param[in]	data	メッシュのデータ
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		template<typename T_VShader, typename T_PShader>
		void DrawSprite(const MeshPrimData& data) {
/*
			auto Dev = App::GetApp()->GetDeviceResources();
			auto pD3D11DeviceContext = Dev->GetD3DDeviceContext();
			auto RenderState = Dev->GetRenderState();
			//NULLのシェーダリソースの準備
			ID3D11ShaderResourceView* pNull[D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT] = { nullptr };
			//サンプラーの準備
			ID3D11SamplerState* pNullSR[D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT] = { nullptr };
			//各オブジェクト共通処理
			//シェーダの設定
			//頂点シェーダ
			pD3D11DeviceContext->VSSetShader(T_VShader::GetPtr()->GetShader(), nullptr, 0);
			//インプットレイアウトの設定
			pD3D11DeviceContext->IASetInputLayout(T_VShader::GetPtr()->GetInputLayout());
			//ピクセルシェーダ
			pD3D11DeviceContext->PSSetShader(T_PShader::GetPtr()->GetShader(), nullptr, 0);
			//個別処理
			SpriteConstants sb;
			//コンスタントバッファの作成
			SetConstants(sb);
			//テクスチャ
			auto shTex = GetTextureResource();
			//コンスタントバッファの更新
			pD3D11DeviceContext->UpdateSubresource(CBSprite::GetPtr()->GetBuffer(), 0, nullptr, &sb, 0, 0);
			//コンスタントバッファの設定
			ID3D11Buffer* pConstantBuffer = CBSprite::GetPtr()->GetBuffer();
			ID3D11Buffer* pNullConstantBuffer = nullptr;
			//頂点シェーダに渡す
			pD3D11DeviceContext->VSSetConstantBuffers(0, 1, &pConstantBuffer);
			//ピクセルシェーダに渡す
			pD3D11DeviceContext->PSSetConstantBuffers(0, 1, &pConstantBuffer);
			//ストライドとオフセット
			UINT stride = data.m_NumStride;
			UINT offset = 0;
			//描画方法のセット
			pD3D11DeviceContext->IASetPrimitiveTopology(data.m_PrimitiveTopology);
			//頂点バッファのセット
			pD3D11DeviceContext->IASetVertexBuffers(0, 1, data.m_VertexBuffer.GetAddressOf(), &stride, &offset);
			//インデックスバッファのセット
			pD3D11DeviceContext->IASetIndexBuffer(data.m_IndexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0);
			//各レンダリングステートの設定
			//ブレンドステート
			RenderState->SetBlendState(pD3D11DeviceContext, GetBlendState());
			//デプスステンシルステート
			RenderState->SetDepthStencilState(pD3D11DeviceContext, GetDepthStencilState());
			//テクスチャとサンプラー
			if (shTex) {
				pD3D11DeviceContext->PSSetShaderResources(0, 1, shTex->GetShaderResourceView().GetAddressOf());
				//サンプラーを設定
				RenderState->SetSamplerState(pD3D11DeviceContext, GetSamplerState(), 0);
			}
			else {
				//シェーダーリソースもクリア
				pD3D11DeviceContext->PSSetShaderResources(0, D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT, pNull);
				//サンプラーもクリア
				RenderState->SetSamplerAllClear(pD3D11DeviceContext);
			}
			//ラスタライザステートと描画
			RenderState->SetRasterizerState(pD3D11DeviceContext, GetRasterizerState());
			//描画
			pD3D11DeviceContext->DrawIndexed(data.m_NumIndicis, 0, 0);
*/
		}
		//--------------------------------------------------------------------------------------
		/*!
		@brief	メッシュリソースの取得
		@return	メッシュリソース
		*/
		//--------------------------------------------------------------------------------------
		shared_ptr<MeshResource> GetMeshResource() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	メッシュリソースの設定
		@param[in]	MeshRes	メッシュリソース
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void SetMeshResource(const shared_ptr<MeshResource>& MeshRes);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	テクスチャリソースの設定
		@param[in]	TextureRes	テクスチャリソース
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void SetTextureResource(const shared_ptr<TextureResource>& TextureRes);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	テクスチャリソースの設定
		@param[in]	TextureKey	登録されているテクスチャキー
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void SetTextureResource(const wstring& TextureKey);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	テクスチャリソースの取得
		@return	テクスチャリソース
		*/
		//--------------------------------------------------------------------------------------
		shared_ptr<TextureResource> GetTextureResource() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	エミッシブ色の取得
		@return	エミッシブ色
		*/
		//--------------------------------------------------------------------------------------
		bsm::Col4 GetEmissive() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	エミッシブ色の設定
		@param[in]	col	エミッシブ色
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void SetEmissive(const bsm::Col4& col);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	デフューズ色の取得
		@return	デフューズ色
		*/
		//--------------------------------------------------------------------------------------
		bsm::Col4 GetDiffuse() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	デフューズ色の設定
		@param[in]	col	デフューズ色
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void SetDiffuse(const bsm::Col4& col);
		//描画コンポーネント個別処理
		//--------------------------------------------------------------------------------------
		/*!
		@brief	PC描画リソースの作成
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void CreatePC();
		//--------------------------------------------------------------------------------------
		/*!
		@brief	PC描画
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void DrawPC();

		//--------------------------------------------------------------------------------------
		/*!
		@brief	PT描画リソースの作成
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void CreatePT();
		//--------------------------------------------------------------------------------------
		/*!
		@brief	PT描画
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void DrawPT();

		//--------------------------------------------------------------------------------------
		/*!
		@brief	PCT描画リソースの作成
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void CreatePCT();
		//--------------------------------------------------------------------------------------
		/*!
		@brief	PCT描画
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void DrawPCT();
	private:
		// pImplイディオム
		struct Impl;
		unique_ptr<Impl> pImpl;
	};

	//--------------------------------------------------------------------------------------
	///	PCSprite描画コンポーネント
	//--------------------------------------------------------------------------------------
	class PCSpriteDraw : public SpriteBaseDraw {
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief	コンストラクタ
		@param[in]	GameObjectPtr	ゲームオブジェクト
		*/
		//--------------------------------------------------------------------------------------
		explicit PCSpriteDraw(const shared_ptr<GameObject>& GameObjectPtr);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	コンストラクタ
		@param[in]	GameObjectPtr	ゲームオブジェクト
		@param[in]	Vertices	初期頂点の配列
		@param[in]	indices		初期インデックスの配列
		*/
		//--------------------------------------------------------------------------------------
		explicit PCSpriteDraw(const shared_ptr<GameObject>& GameObjectPtr,
			vector<VertexPositionColor>& Vertices, vector<uint16_t>& indices);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	デストラクタ
		*/
		//--------------------------------------------------------------------------------------
		virtual ~PCSpriteDraw();
		//--------------------------------------------------------------------------------------
		/*!
		@brief	OnCreate処理
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnCreate()override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	OnUpdate処理（空関数）
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnUpdate()override {}
		//--------------------------------------------------------------------------------------
		/*!
		@brief	OnDraw処理
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnDraw()override;
	};

	//--------------------------------------------------------------------------------------
	///	PTSprite描画コンポーネント
	//--------------------------------------------------------------------------------------
	class PTSpriteDraw : public SpriteBaseDraw {
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief	コンストラクタ
		@param[in]	GameObjectPtr	ゲームオブジェクト
		*/
		//--------------------------------------------------------------------------------------
		explicit PTSpriteDraw(const shared_ptr<GameObject>& GameObjectPtr);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	コンストラクタ
		@param[in]	GameObjectPtr	ゲームオブジェクト
		@param[in]	Vertices	初期頂点の配列
		@param[in]	indices		初期インデックスの配列
		*/
		//--------------------------------------------------------------------------------------
		explicit PTSpriteDraw(const shared_ptr<GameObject>& GameObjectPtr,
			vector<VertexPositionTexture>& Vertices, vector<uint16_t>& indices);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	デストラクタ
		*/
		//--------------------------------------------------------------------------------------
		virtual ~PTSpriteDraw();
		//--------------------------------------------------------------------------------------
		/*!
		@brief	OnCreate処理
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnCreate()override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	OnUpdate処理（空関数）
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnUpdate()override {}
		//--------------------------------------------------------------------------------------
		/*!
		@brief	OnDraw処理
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnDraw()override;
	};


	//--------------------------------------------------------------------------------------
	///	PCTSprite描画コンポーネント
	//--------------------------------------------------------------------------------------
	class PCTSpriteDraw : public SpriteBaseDraw {
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief	コンストラクタ
		@param[in]	GameObjectPtr	ゲームオブジェクト
		*/
		//--------------------------------------------------------------------------------------
		explicit PCTSpriteDraw(const shared_ptr<GameObject>& GameObjectPtr);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	コンストラクタ
		@param[in]	GameObjectPtr	ゲームオブジェクト
		@param[in]	Vertices	初期頂点の配列
		@param[in]	indices		初期インデックスの配列
		*/
		//--------------------------------------------------------------------------------------
		explicit PCTSpriteDraw(const shared_ptr<GameObject>& GameObjectPtr,
			vector<VertexPositionColorTexture>& Vertices, vector<uint16_t>& indices);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	デストラクタ
		*/
		//--------------------------------------------------------------------------------------
		virtual ~PCTSpriteDraw();
		//--------------------------------------------------------------------------------------
		/*!
		@brief	OnCreate処理
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnCreate()override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	OnUpdate処理（空関数）
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnUpdate()override {}
		//--------------------------------------------------------------------------------------
		/*!
		@brief	OnDraw処理
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnDraw()override;
	};

	//--------------------------------------------------------------------------------------
	///	Shadowコンスタントバッファ構造体
	//--------------------------------------------------------------------------------------
	struct ShadowConstants
	{
		/// ワールド行列
		bsm::Mat4x4 mWorld;
		/// ビュー行列
		bsm::Mat4x4 mView;
		/// 射影行列
		bsm::Mat4x4 mProj;
		/// Bone用
		bsm::Vec4 Bones[3 * 72];
		ShadowConstants() {
			memset(this, 0, sizeof(ShadowConstants));
		};
	};


	//--------------------------------------------------------------------------------------
	///	シャドウマップコンポーネント（前処理用）
	//--------------------------------------------------------------------------------------
	class Shadowmap : public DrawComponent {
		//コンスタントバッファ更新
		void UpdateConstantBuffer();
		void DrawObject();
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief	コンストラクタ
		@param[in]	GameObjectPtr	ゲームオブジェクト
		*/
		//--------------------------------------------------------------------------------------
		explicit Shadowmap(const shared_ptr<GameObject>& GameObjectPtr);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	デストラクタ
		*/
		//--------------------------------------------------------------------------------------
		virtual ~Shadowmap();
		//アクセサ
		//--------------------------------------------------------------------------------------
		/*!
		@brief	ライトの高さを得る
		@return	ライトの高さ
		*/
		//--------------------------------------------------------------------------------------
		static float GetLightHeight();
		//--------------------------------------------------------------------------------------
		/*!
		@brief	ライトのNear値を得る
		@return	ライトのNear値
		*/
		//--------------------------------------------------------------------------------------
		static float GetLightNear();
		//--------------------------------------------------------------------------------------
		/*!
		@brief	ライトのFar値を得る
		@return	ライトのFar値
		*/
		//--------------------------------------------------------------------------------------
		static float GetLightFar();
		//--------------------------------------------------------------------------------------
		/*!
		@brief	ビューの幅を得る
		@return	ビューの幅
		*/
		//--------------------------------------------------------------------------------------
		static float GetViewWidth();
		//--------------------------------------------------------------------------------------
		/*!
		@brief	ビューの高さを得る
		@return	ビューの高さ
		*/
		//--------------------------------------------------------------------------------------
		static float GetViewHeight();
		//--------------------------------------------------------------------------------------
		/*!
		@brief	ライトの高さを設定する
		@param[in]	f	高さ
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		static void SetLightHeight(float f);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	ライトのNear値を設定する
		@param[in]	f	Near値
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		static void SetLightNear(float f);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	ライトのFar値を設定する
		@param[in]	f	Far値
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		static void SetLightFar(float f);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	ビューの幅を設定する
		@param[in]	f	ビューの幅
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		static void SetViewWidth(float f);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	ビューの高さを設定する
		@param[in]	f	ビューの高さ
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		static void SetViewHeight(float f);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	ビューの幅及び高さを同じ値に設定する
		@param[in]	f	ビューの幅及び高さ（同値）
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		static void SetViewSize(float f);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	メッシュリソースを得る
		@param[in]	ExceptionActive	エラー時に例外が発生するかどうか
		@return	メッシュリソース
		*/
		//--------------------------------------------------------------------------------------
		shared_ptr<MeshResource> GetMeshResource(bool ExceptionActive = true) const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	メッシュリソースを設定する
		@param[in]	ResKey	メッシュリソースのキー
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void SetMeshResource(const wstring& ResKey);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	メッシュリソースを設定する
		@param[in]	MeshResourcePtr	メッシュリソース
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void SetMeshResource(const shared_ptr<MeshResource>& MeshResourcePtr);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	マルチメッシュリソースを得る
		@param[in]	ExceptionActive	エラー時に例外が発生するかどうか
		@return	メッシュリソース
		*/
		//--------------------------------------------------------------------------------------
		shared_ptr<MultiMeshResource> GetMultiMeshResource(bool ExceptionActive = true) const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	マルチメッシュリソースを設定する
		@param[in]	ResKey	メッシュリソースのキー
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void SetMultiMeshResource(const wstring& ResKey);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	マルチメッシュリソースを設定する
		@param[in]	MeshResourcePtr	メッシュリソース
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void SetMultiMeshResource(const shared_ptr<MultiMeshResource>& MeshResourcePtr);
		//操作
		//--------------------------------------------------------------------------------------
		/*!
		@brief	OnCreate処理
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnCreate()override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	更新処理。（空関数）
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnUpdate()override {}
		//--------------------------------------------------------------------------------------
		/*!
		@brief	描画処理。
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnDraw()override;
	private:
		// pImplイディオム
		struct Impl;
		unique_ptr<Impl> pImpl;
	};



	//--------------------------------------------------------------------------------------
	///	SimpleConstantsコンスタントバッファ構造体
	//--------------------------------------------------------------------------------------
	struct SimpleConstants
	{
		/// ワールド行列
		bsm::Mat4x4 World;
		/// ビュー行列
		bsm::Mat4x4 View;
		/// 射影行列
		bsm::Mat4x4 Projection;
		/// エミッシブ色
		bsm::Col4 Emissive;
		/// デフューズ色
		bsm::Col4 Diffuse;
		/// スペキュラー
		bsm::Col4 Specular;
		/// テクスチャ=xがアクティブかどうか
		XMUINT4 ActiveFlg;
		/// ライイト方向
		bsm::Vec4 LightDir;
		/// ライト位置
		bsm::Vec4 LightPos;
		/// Eyeの位置
		bsm::Vec4 EyePos;
		/// ライトビュー行列
		bsm::Mat4x4 LightView;
		/// ライト射影行列
		bsm::Mat4x4 LightProjection;
		/// Bone配列
		bsm::Vec4 Bones[3 * 72];
		SimpleConstants() {
			memset(this, 0, sizeof(SimpleConstants));
			Diffuse = bsm::Col4(1.0f, 1.0f, 1.0f, 1.0f);
		};
	};


	//--------------------------------------------------------------------------------------
	///	Simple描画オブジェクトの親
	//--------------------------------------------------------------------------------------
	class SmBaseDraw : public DrawComponent {
		///シェーダーリソースビュー作成
		void CreateShaderResourceView();
		//コンスタントバッファ更新
		void UpdateConstantBuffer();
		///描画処理
		void DrawObject();
		///プロパティ変更
		void RefreshTrace();
	protected:
		//--------------------------------------------------------------------------------------
		/*!
		@brief コンストラクタ
		@param[in]	StagePtr	ステージのポインタ
		*/
		//--------------------------------------------------------------------------------------
		explicit SmBaseDraw(const shared_ptr<GameObject>& GameObjectPtr);
		//--------------------------------------------------------------------------------------
		/*!
		@brief デストラクタ
		*/
		//--------------------------------------------------------------------------------------
		virtual ~SmBaseDraw();
		//--------------------------------------------------------------------------------------
		/*!
		@brief	コンスタントバッファの設定
		@param[out]	SmCb	設定するコンスタントバッファ構造体
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void SetConstants(Dx12Constants<SimpleConstants>& SmCb);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	行列バッファの作成(インスタンス描画用)
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void CreateMatrixBuffer();
		//--------------------------------------------------------------------------------------
		/*!
		@brief	行列バッファのマップ(インスタンス描画用)
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void MapMatrixBuffer();
		//--------------------------------------------------------------------------------------
		/*!
		@brief	スタティックメッシュの描画
		@tparam[in]	T_VShader	使用する頂点シェーダ
		@tparam[in]	T_PShader	使用するピクセルシェーダ
		@param[in]	data	メッシュのデータ
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		template<typename T_VShader, typename T_PShader>
		void DrawStatic(const MeshPrimData& data) {
		}
		//--------------------------------------------------------------------------------------
		/*!
		@brief	スタティックメッシュのインスタンス描画
		@tparam[in]	T_VShader	使用する頂点シェーダ
		@tparam[in]	T_PShader	使用するピクセルシェーダ
		@param[in]	data	メッシュのデータ
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		template<typename T_VShader, typename T_PShader>
		void DrawStaticInstance(const MeshPrimData& data) {
		}
		//--------------------------------------------------------------------------------------
		/*!
		@brief	モデルメッシュの描画
		@tparam[in]	T_VShader	使用する頂点シェーダ
		@tparam[in]	T_PShader	使用するピクセルシェーダ
		@param[in]	data	メッシュのデータ
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		template<typename T_VShader, typename T_PShader>
		void DrawModel(const MeshPrimData& data) {
		}
		//描画コンポーネント個別処理
		//--------------------------------------------------------------------------------------
		/*!
		@brief	PN影無し描画リソースの作成
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void CreatePNNotShadow();
		//--------------------------------------------------------------------------------------
		/*!
		@brief	PNT影無し描画リソースの作成
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void CreatePNTNotShadow();
		//--------------------------------------------------------------------------------------
		/*!
		@brief	PNT影付描画リソースの作成
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void CreatePNTWithShadow();
		//--------------------------------------------------------------------------------------
		/*!
		@brief	PN描画（影付き影無し共通）
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void DrawPN();
		//--------------------------------------------------------------------------------------
		/*!
		@brief	PNT描画（影付き影無し共通）
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void DrawPNT();
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief	オリジナルメッシュを使うかどうか
		@return	使う場合はtrue
		*/
		//--------------------------------------------------------------------------------------
		bool IsOriginalMeshUse() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	オリジナルメッシュを使うかどうかを設定
		@param[in]	b	オリジナルメッシュを使うかどうか
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void SetOriginalMeshUse(bool b);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	オリジナルなメッシュリソースの取得
		@return	オリジナルなメッシュリソース
		*/
		//--------------------------------------------------------------------------------------
		shared_ptr<MeshResource> GetOriginalMeshResource() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	オリジナルなメッシュリソースの設定
		@param[in]	MeshRes	メッシュリソース
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void SetOriginalMeshResource(const shared_ptr<MeshResource>& MeshRes);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	オリジナルメッシュを作成する
		@param[in]	Vertices	頂点の配列
		@param[in]	indices		インデックスの配列
		*/
		//--------------------------------------------------------------------------------------
		template <typename T>
		void CreateOriginalMesh(vector<T>& Vertices, vector<uint16_t>& indices) {
			try {
				auto MeshRes = MeshResource::CreateMeshResource(Vertices, indices, true);
				SetOriginalMeshResource(MeshRes);
			}
			catch (...) {
				throw;
			}
		}
		//--------------------------------------------------------------------------------------
		/*!
		@brief	オリジナルメッシュの頂点バッファを変更する
		@param[in]	Vertices	頂点配列
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		template <typename T>
		void UpdateVertices(const vector<T>& Vertices) {
			auto MeshRes = GetOriginalMeshResource();
			if (!MeshRes) {
				throw BaseException(
					L"オリジナルメッシュが作成されていません",
					L"if (!GetOriginalMeshResource())",
					L"StaticBaseDraw::UpdateVertices()"
				);

			}
			MeshRes->UpdateVirtexBuffer(Vertices);
		}
		//--------------------------------------------------------------------------------------
		/*!
		@brief	メッシュリソースの取得(オリジナルかどうかは内部で処理される)
		@return	メッシュリソース
		*/
		//--------------------------------------------------------------------------------------
		shared_ptr<MeshResource> GetMeshResource() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	オリジナルではないメッシュリソースの設定(仮想関数)
		@param[in]	MeshRes	メッシュリソース
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void SetMeshResource(const shared_ptr<MeshResource>& MeshRes);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	オリジナルではないメッシュリソースの設定
		@param[in]	MeshKey	メッシュキー
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void SetMeshResource(const wstring& MeshKey);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	テクスチャリソースの設定
		@param[in]	TextureRes	テクスチャリソース
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void SetTextureResource(const shared_ptr<TextureResource>& TextureRes);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	テクスチャリソースの設定
		@param[in]	TextureKey	登録されているテクスチャキー
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void SetTextureResource(const wstring& TextureKey);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	テクスチャリソースの取得
		@return	テクスチャリソース
		*/
		//--------------------------------------------------------------------------------------
		shared_ptr<TextureResource> GetTextureResource() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	マルチメッシュリソースを得る
		@param[in]	ExceptionActive	エラー時に例外が発生するかどうか
		@return	メッシュリソース
		*/
		//--------------------------------------------------------------------------------------
		shared_ptr<MultiMeshResource> GetMultiMeshResource() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	マルチメッシュリソースを設定する
		@param[in]	MeshResourcePtr	メッシュリソース
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void SetMultiMeshResource(const shared_ptr<MultiMeshResource>& MeshResourcePtr);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	マルチメッシュリソースを設定する
		@param[in]	ResKey	メッシュリソースのキー
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void SetMultiMeshResource(const wstring& ResKey);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	エミッシブ色の取得
		@return	エミッシブ色
		*/
		//--------------------------------------------------------------------------------------
		bsm::Col4 GetEmissive() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	エミッシブ色の設定
		@param[in]	col	エミッシブ色
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void SetEmissive(const bsm::Col4& col);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	デフューズ色の取得
		@return	デフューズ色
		*/
		//--------------------------------------------------------------------------------------
		bsm::Col4 GetDiffuse() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	デフューズ色の設定
		@param[in]	col	デフューズ色
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void SetDiffuse(const bsm::Col4& col);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	スペキュラー色の取得
		@return	スペキュラー色
		*/
		//--------------------------------------------------------------------------------------
		bsm::Col4 GetSpecular() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	スペキュラー色の設定
		@param[in]	col	スペキュラー色
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void SetSpecular(const bsm::Col4& col);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	影を描画するかどうか得る
		@return	影を描画すればtrue
		*/
		//--------------------------------------------------------------------------------------
		bool GetOwnShadowActive() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	影を描画するかどうか得る
		@return	影を描画すればtrue
		*/
		//--------------------------------------------------------------------------------------
		bool IsOwnShadowActive() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	影を描画するかどうか設定する
		@param[in]	b		影を描画するかどうか
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void SetOwnShadowActive(bool b);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	デフィーズ色をモデル設定優先かどうか得る
		@return	デフィーズ色をモデル設定優先ならtrue
		*/
		//--------------------------------------------------------------------------------------
		bool GetModelDiffusePriority() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	デフィーズ色をモデル設定優先かどうか得る
		@return	デフィーズ色をモデル設定優先ならtrue
		*/
		//--------------------------------------------------------------------------------------
		bool IsModelDiffusePriority() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	デフィーズ色をモデル設定優先かどうか設定する
		@param[in]	b	デフィーズ色をモデル設定優先かどうか
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void SetModelDiffusePriority(bool b);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	エミッシブ色をモデル設定優先かどうか得る
		@return	エミッシブ色をモデル設定優先ならtrue
		*/
		//--------------------------------------------------------------------------------------
		bool GetModelEmissivePriority() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	エミッシブ色をモデル設定優先かどうか得る
		@return	エミッシブ色をモデル設定優先ならtrue
		*/
		//--------------------------------------------------------------------------------------
		bool IsModelEmissivePriority() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	エミッシブ色をモデル設定優先かどうか設定する
		@param[in]	b	エミッシブ色をモデル設定優先かどうか
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void SetModelEmissivePriority(bool b);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	モデルのテクスチャを有効にするかどうか得る
		@return	モデルのテクスチャを有効ならtrue
		*/
		//--------------------------------------------------------------------------------------
		bool GetModelTextureEnabled() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	モデルのテクスチャを有効にするかどうか得る
		@return	モデルのテクスチャを有効ならtrue
		*/
		//--------------------------------------------------------------------------------------
		bool IsModelTextureEnabled() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	モデルのテクスチャを有効にするかどうか設定する
		@param[in]	b	モデルのテクスチャを有効にするかどうか
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void SetModelTextureEnabled(bool b);
		//Bone描画用
		//--------------------------------------------------------------------------------------
		/*!
		@brief ボーンの初期化
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void BoneInit();
		//--------------------------------------------------------------------------------------
		/*!
		@brief	開始行列から終了行列の間のt時間時の行列を返す
		@param[in]	m1	開始の行列
		@param[in]	m2	終了の行列
		@param[in]	t	時間（0から1.0f）
		@param[out]	out	結果を受け取る行列
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void InterpolationMatrix(const bsm::Mat4x4& m1, const bsm::Mat4x4& m2, float t, bsm::Mat4x4& out);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	アニメーションを追加する
		@param[in]	Name	アニメーション名
		@param[in]	StartSample	開始サンプル
		@param[in]	SampleLength	サンプルの長さ
		@param[in]	Loop	ループするかどうか
		@param[in]	SamplesParSecond = 30.0f	1秒あたりのサンプル数
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void AddAnimation(const wstring& Name, int StartSample, int SampleLength, bool Loop,
			float SamplesParSecond = 30.0f);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	現在のアニメーションを変更する
		@param[in]	AnemationName	アニメーション名（すでに追加されているもの）
		@param[in]	StartTime = 0.0f	開始からの秒数
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void ChangeCurrentAnimation(const wstring& AnemationName, float StartTime = 0.0f);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	現在のアニメーション名を得る
		@return	アニメーション名（文字列）
		*/
		//--------------------------------------------------------------------------------------
		const wstring& GetCurrentAnimation() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	現在のアニメーションタイムを得る
		@return	アニメーションタイム
		*/
		//--------------------------------------------------------------------------------------
		float GetCurrentAnimationTime() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	現在のアニメーションが終了しているかどうか
		@return	修了していればtrue
		*/
		//--------------------------------------------------------------------------------------
		bool IsTargetAnimeEnd() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	現在のアニメーションを進める
		@param[in]	ElapsedTime	経過時間
		@return	アニメーションが終了すればtrue
		*/
		//--------------------------------------------------------------------------------------
		bool UpdateAnimation(float ElapsedTime);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	ローカルボーン行列配列を得る
		@return	ローカルボーン行列配列の先頭ポインタ
		*/
		//--------------------------------------------------------------------------------------
		virtual const vector< bsm::Mat4x4 >* GetVecLocalBonesPtr() const override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	ローカルボーン行列配列の参照を得る(書き換え可能)
		@return	ローカルボーン行列配列の参照
		*/
		//--------------------------------------------------------------------------------------
		vector< bsm::Mat4x4 >& GetVecLocalBones();
		//--------------------------------------------------------------------------------------
		/*!
		@brief	ローカルボーン行列配列を得る（マルチメッシュ版）
		@return	ローカルボーン行列配列の先頭ポインタ
		*/
		//--------------------------------------------------------------------------------------
		virtual const vector< bsm::Mat4x4 >* GetVecMultiLocalBonesPtr(size_t index) const override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	ローカルボーン行列配列の参照を得る(マルチメッシュ版版、書き換え可能)
		@return	ローカルボーン行列配列の参照（範囲外なら例外）
		*/
		//--------------------------------------------------------------------------------------
		vector< bsm::Mat4x4 >& GetVecMultiLocalBones(size_t index);
		//インスタンス描画用
		//--------------------------------------------------------------------------------------
		/*!
		@brief	行列の上限を得る
		@return	行列の上限を
		*/
		//--------------------------------------------------------------------------------------
		size_t GetMaxInstance() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	行列の上限を変更する
		@param[in]	NewSize		新しい上限
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void ResizeMaxInstance(size_t NewSize);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	同時描画の行列を追加する
		@param[in]	NewMatVec		新しい行列
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void AddMatrix(const bsm::Mat4x4& NewMat);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	同時描画の行列を完全に更新する
		@param[in]	NewMatVec		新しい行列
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void UpdateMultiMatrix(const vector<bsm::Mat4x4>& NewMatVec);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	同時描画の行列の配列を取得する
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		vector<bsm::Mat4x4>& GetMatrixVec() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	同時描画の行列をクリアする
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void ClearMatrixVec();
		//--------------------------------------------------------------------------------------
		/*!
		@brief	描画後行列配列を自動クリアするかどうか
		@return	クリアするはtrue
		*/
		//--------------------------------------------------------------------------------------
		bool IsAutoClearMatrixVec() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	描画後行列配列を自動クリアするかどうかを設定
		@param[in]	b	描画後行列配列を自動クリアするかどうか
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void SetAutoClearMatrixVec(bool b);
		//--------------------------------------------------------------------------------------
		/*!
		@brief　行列のバッファを取得する
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
//		ComPtr<ID3D11Buffer>& GetMatrixBuffer() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	メッシュのローカル頂点配列を得る
		@param[out]	vertices	受け取る頂点の配列
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void GetStaticMeshLocalPositions(vector<bsm::Vec3>& vertices);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	メッシュのワールド頂点配列を得る
		@param[out]	vertices	受け取る頂点の配列
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void GetStaticMeshWorldPositions(vector<bsm::Vec3>& vertices);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	線分とメッシュのワールド頂点の衝突判定
		@param[in]	StartPos	線分の開始点
		@param[in]	EndPos	線分の終了点
		@param[out]	HitPoint	衝突していた場合の衝突点
		@param[out]	RetTri	衝突していた場合の三角形
		@param[out]	RetIndex	衝突していた場合の三角形の位置
		@return	衝突していたらtrue
		*/
		//--------------------------------------------------------------------------------------
		bool HitTestStaticMeshSegmentTriangles(const bsm::Vec3& StartPos, const bsm::Vec3& EndPos, bsm::Vec3& HitPoint, TRIANGLE& RetTri,size_t& RetIndex);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	スキン処理済みのメッシュのローカル頂点配列を得る
		@param[out]	vertices	受け取る頂点の配列
		@return	なし（ボーンがなければ例外）
		*/
		//--------------------------------------------------------------------------------------
		void GetSkinedMeshLocalPositions(vector<bsm::Vec3>& vertices);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	スキン処理済みのメッシュのワールド頂点配列を得る
		@param[out]	vertices	受け取る頂点の配列
		@return	なし（ボーンがなければ例外）
		*/
		//--------------------------------------------------------------------------------------
		void GetSkinedMeshWorldPositions(vector<bsm::Vec3>& vertices);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	線分とスキンメッシュのワールド頂点の衝突判定
		@param[in]	StartPos	線分の開始点
		@param[in]	EndPos	線分の終了点
		@param[out]	HitPoint	衝突していた場合の衝突点
		@param[out]	RetTri	衝突していた場合の三角形
		@param[out]	RetIndex	衝突していた場合の三角形の位置
		@return	衝突していたらtrue
		*/
		//--------------------------------------------------------------------------------------
		bool HitTestSkinedMeshSegmentTriangles(const bsm::Vec3& StartPos, const bsm::Vec3& EndPos, bsm::Vec3& HitPoint, TRIANGLE& RetTri, size_t& RetIndex);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	Dx12描画リソース群の取得（const）
		@return	Dx12描画リソース群構造体
		*/
		//--------------------------------------------------------------------------------------
		const Dx12DrawResources<SimpleConstants>& GetSimpleDrawResources() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	Dx12描画リソース群の取得
		@return	Dx12描画リソース群構造体
		*/
		//--------------------------------------------------------------------------------------
		Dx12DrawResources<SimpleConstants>& GetSimpleDrawResources();
	private:
		// pImplイディオム
		struct Impl;
		unique_ptr<Impl> pImpl;
	};


	//--------------------------------------------------------------------------------------
	///	PNStatic描画コンポーネント
	//--------------------------------------------------------------------------------------
	class PNStaticDraw : public SmBaseDraw {
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief	コンストラクタ
		@param[in]	GameObjectPtr	ゲームオブジェクト
		*/
		//--------------------------------------------------------------------------------------
		explicit PNStaticDraw(const shared_ptr<GameObject>& GameObjectPtr);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	デストラクタ
		*/
		//--------------------------------------------------------------------------------------
		virtual ~PNStaticDraw();
		//--------------------------------------------------------------------------------------
		/*!
		@brief	OnCreate処理
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnCreate()override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	OnUpdate処理（空関数）
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnUpdate()override {}
		//--------------------------------------------------------------------------------------
		/*!
		@brief	OnDraw処理
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnDraw()override;
	};

	//--------------------------------------------------------------------------------------
	///	PCTStatic描画コンポーネント
	//--------------------------------------------------------------------------------------
	class PCTStaticDraw : public SmBaseDraw {
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief	コンストラクタ
		@param[in]	GameObjectPtr	ゲームオブジェクト
		*/
		//--------------------------------------------------------------------------------------
		explicit PCTStaticDraw(const shared_ptr<GameObject>& GameObjectPtr);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	デストラクタ
		*/
		//--------------------------------------------------------------------------------------
		virtual ~PCTStaticDraw();
		//--------------------------------------------------------------------------------------
		/*!
		@brief	OnCreate処理
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnCreate()override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	OnUpdate処理（空関数）
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnUpdate()override {}
		//--------------------------------------------------------------------------------------
		/*!
		@brief	OnDraw処理
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnDraw()override;
	};



	//--------------------------------------------------------------------------------------
	///	PNTStatic描画コンポーネント
	//--------------------------------------------------------------------------------------
	class PNTStaticDraw : public SmBaseDraw {
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief	コンストラクタ
		@param[in]	GameObjectPtr	ゲームオブジェクト
		*/
		//--------------------------------------------------------------------------------------
		explicit PNTStaticDraw(const shared_ptr<GameObject>& GameObjectPtr);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	デストラクタ
		*/
		//--------------------------------------------------------------------------------------
		virtual ~PNTStaticDraw();
		//--------------------------------------------------------------------------------------
		/*!
		@brief	影を描画するかどうか設定する
		@param[in]	b		影を描画するかどうか
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void SetOwnShadowActive(bool b) override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	OnCreate処理
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnCreate()override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	OnUpdate処理（空関数）
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnUpdate()override {}
		//--------------------------------------------------------------------------------------
		/*!
		@brief	OnDraw処理
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnDraw()override;
	};

}
//end basecross
