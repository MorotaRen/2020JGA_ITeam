
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
		void SetTexture(wstring name, wstring filepass, wstring filename)
		{
			strTexture = dataDir + filepass + filename;
			App::GetApp()->RegisterTexture(name, strTexture);
		}
		//音楽読み込み
		void SetSound(wstring name, wstring filename)
		{
			strSound = dataDir + L"Sound\\" + filename;
			App::GetApp()->RegisterWav(name, strSound);
		}
		//線ありの肉読み込み
		void SetMeat_Line(wstring name, wstring filename) {
			strTexture = dataDir + L"Texture\\Meats\\IsLine\\" + filename;
			App::GetApp()->RegisterTexture(name, strTexture);
		}
		//全リソース適用
		void CreateResourses()
		{
			//ディレクトリ取得
			App::GetApp()->GetAssetsDirectory(dataDir);

			//テクスチャ
			//SetTexture(L"RANK_UI", L"Rank2.png");
			//SetTexture(L"Black_TEST",L"Black.png");
			//SetTexture(L"White_TEST",L"White.png");
			SetTexture(L"BG_Kitchen", L"Texture\\GameUIs\\", L"Kitchen.png");
			SetTexture(L"BG_Flyer", L"Texture\\GameUIs\\", L"Flyer.png");
			SetTexture(L"BG_Mass", L"Texture\\GameUIs\\", L"Masu.png");
			SetTexture(L"Select_BG", L"Texture\\UIs\\", L"Select_Background.png");
			SetTexture(L"Select_Stage_TX", L"Texture\\UIs\\", L"Select_StageTx.png");
			SetTexture(L"Pointer_TX", L"Texture\\UIs\\", L"pointer.png");
			SetTexture(L"Guest1_TX", L"Texture\\Characters\\", L"Guest1.png");
			SetTexture(L"Tex_Number", L"Texture\\UIs\\", L"Number.png");
			SetTexture(L"Tex_Timer", L"Texture\\GameUIs\\", L"Timer.png");


			//肉(線あり)
			SetMeat_Line(L"Meat_Drum_Line",L"Chicken_Drum3.png");
			SetMeat_Line(L"Meat_Keel_Line",L"Chicken_Keel3.png");
			SetMeat_Line(L"Meat_Rib_Line",L"Chicken_Rib3.png");
			SetMeat_Line(L"Meat_Wing_Line",L"Chicken_Wing3.png");
			SetMeat_Line(L"Meat_Chicken_Line",L"FriedChicken3.png");
			SetMeat_Line(L"RawMeat_Drum_Line",L"RawMeat_Drum3.png");
			SetMeat_Line(L"RawMeat_Chicken_Line",L"RawMeat_FridChikin3.png");
			SetMeat_Line(L"RawMeat_Keel_Line",L"RawMeat_Keel3 .png");
			SetMeat_Line(L"RawMeat_Rib_Line",L"RawMeat_Rib3.png");
			SetMeat_Line(L"RawMeat_Wing_Line",L"RawMeat_Wing3.png");

			//音楽

		}
	};

	//--------------------------------------------------------------------------------------
	///	ゲームシーン
	//--------------------------------------------------------------------------------------
	void Scene::OnCreate(){
		try {
			//リソース設定
			CreateResourse resourse;
			resourse.CreateResourses();
			
			//クリアする色を設定
			Col4 Col;
			Col.set(31.0f / 255.0f, 30.0f / 255.0f, 71.0f / 255.0f, 255.0f / 255.0f);
			SetClearColor(Col);
			//自分自身にイベントを送る
			//これにより各ステージやオブジェクトがCreate時にシーンにアクセスできる
			PostEvent(0.0f, GetThis<ObjectInterface>(), GetThis<Scene>(), L"ToSelectStage");
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
		if (event->m_MsgStr == L"ToSelectStage") {
			ResetActiveStage<SelectStage>();
		}
		if (event->m_MsgStr == L"ToTitleStage") {
			//ResetActiveStage<TitleStage>();
		}
		if (event->m_MsgStr == L"ToResultStage") {
			//ResetActiveStage<ResultStage>();
		}
	}

}
//end basecross
