
/*!
@file Scene.cpp
@brief シーン実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{

	//--------------------------------------------------------------------------------------
	///	素材読み込み
	//--------------------------------------------------------------------------------------
	struct CreateResourse
	{
		//アセットディレクトリ
		wstring dataDir;
		//テクスチャ
		wstring strTexture;
		//音楽
		wstring strSound;

	public:
		//テクスチャ読み込み
		void SetTexture(wstring name, wstring filename)
		{
			strTexture = dataDir + L"Texture\\" + filename;
			App::GetApp()->RegisterTexture(name, strTexture);
		}
		//音楽読み込み
		void SetSound(wstring name, wstring filename)
		{
			strSound = dataDir + L"Sound\\" + filename;
			App::GetApp()->RegisterWav(name, strSound);
		}
		//全リソース適用
		void CreateResourses()
		{
			//ディレクトリ取得
			App::GetApp()->GetAssetsDirectory(dataDir);

			//テクスチャ
			SetTexture(L"RANK_UI", L"Rank2.png");

			//音楽

		}
	};

	//--------------------------------------------------------------------------------------
	///	ゲームシーン
	//--------------------------------------------------------------------------------------
	void Scene::OnCreate(){
		try {
			//リソース設定
			//CreateResourse resourse;
			//resourse.CreateResourses();

			//クリアする色を設定
			Col4 Col;
			Col.set(31.0f / 255.0f, 30.0f / 255.0f, 71.0f / 255.0f, 255.0f / 255.0f);
			SetClearColor(Col);
			//自分自身にイベントを送る
			//これにより各ステージやオブジェクトがCreate時にシーンにアクセスできる
			PostEvent(0.0f, GetThis<ObjectInterface>(), GetThis<Scene>(), L"ToGameStage");
		}
		catch (...) {
			throw;
		}
	}

	Scene::~Scene() {
	}

	void Scene::OnEvent(const shared_ptr<Event>& event) {
		if (event->m_MsgStr == L"ToGameStage") {
			//最初のアクティブステージの設定
			ResetActiveStage<GameStage>();
		}
	}

}
//end basecross
