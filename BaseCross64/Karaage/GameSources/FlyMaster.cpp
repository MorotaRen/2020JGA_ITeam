#include "stdafx.h"
#include "Project.h"

namespace basecross {
	/// ----------------------------------------<summary>
	/// 在庫数に追加する。追加した後は設置されている数はリセットされる
	/// </summary>----------------------------------------
	void FlyMaster::Add_StockMeat() {
		m_meatsStockData.Meat_1x1 += m_meatsInstallationData.Meat_1x1;
		m_meatsStockData.Meat_1x2 += m_meatsInstallationData.Meat_1x2;
		m_meatsStockData.Meat_2x2 += m_meatsInstallationData.Meat_2x2;
		m_meatsStockData.Meat_3x3 += m_meatsInstallationData.Meat_3x3;
		m_meatsStockData.Meat_L += m_meatsInstallationData.Meat_L;

		Clear_InstallationMeat();
	}

	/// ----------------------------------------<summary>
	/// 設置済み肉の初期化
	/// </summary>----------------------------------------
	void FlyMaster::Clear_InstallationMeat() {
		m_meatsInstallationData.Meat_1x1 = 0;
		m_meatsInstallationData.Meat_1x2 = 0;
		m_meatsInstallationData.Meat_2x2 = 0;
		m_meatsInstallationData.Meat_3x3 = 0;
		m_meatsInstallationData.Meat_L = 0;
	}

	/// ----------------------------------------<summary>
	/// 在庫肉の初期化
	/// </summary>----------------------------------------
	void FlyMaster::Clear_StockMeat() {
		m_meatsStockData.Meat_1x1 = 0;
		m_meatsStockData.Meat_1x2 = 0;
		m_meatsStockData.Meat_2x2 = 0;
		m_meatsStockData.Meat_3x3 = 0;
		m_meatsStockData.Meat_L = 0;
	}
	/// ----------------------------------------<summary>
	/// ゲームフィールドの作成
	/// </summary>----------------------------------------
	void FlyMaster::Create_GameField() {
		//アクティブステージの取得
		auto stage = App::GetApp()->GetScene<Scene>()->GetActiveStage();
		for (int y = 0; y < GAMEFIELD_Y;y++) {
			for (int x = 0; x < GAMEFIELD_X;x++) {
				//マップチップを升目で配置して
				//肉に1マス分の当たり判定を追加してそこからレイキャスして選択されてるオブジェクトと
				//ステージのマス目を比較して当たってるところを1にする…？
				//つまりマップチップにはマップ番号と設置済みのフラグを持たせると
				stage->AddGameObject<MapChip>(Vec2(MAPCHIP_START_X + x * MAPCHIP_SIZE_X, 
												   MAPCHIP_START_Y + -y *MAPCHIP_SIZE_Y),
												   m_TEST_w);
				if (m_TEST_w) {
					m_TEST_w = false;
				}
				else {
					m_TEST_w = true;
				}
			}
		}

	}
	/// ----------------------------------------<summary>
	/// 揚げる処理
	/// </summary>----------------------------------------
	void FlyMaster::Fly() {

	}

	/// ----------------------------------------<summary>
	/// 渡された座標からマップ方向にレイを飛ばし接触したオブジェクトのマップ番号を返す
	/// </summary>----------------------------------------
	int* FlyMaster::Send_RayCastToMapChip(int *returnNum,Vec3 sendPos) {
		returnNum[0] = 1;
		returnNum[1] = 1;
		return returnNum;
	}

	/// ----------------------------------------<summary>
	/// 所持肉の生成
	/// </summary>----------------------------------------
	void FlyMaster::Create_PossessionMeat() {

	}

	/// ----------------------------------------<summary>
	/// 所持肉のリセット
	/// </summary>----------------------------------------
	void Create_PossessionMeat(shared_ptr<GameObject> obj){
		//既に所持していたらそれと交換
		auto possessionmeat = FlyMaster::GetInstans().GetPossessionMeat();
		if (possessionmeat) {
			//まず既存のやつを削除
			possessionmeat->DestroyGameObject();
			//所持肉を設定
			FlyMaster::GetInstans().SetPossessionMeat(obj);
		}
		//所持なしの場合
		FlyMaster::GetInstans().SetPossessionMeat(obj);
	}

}
//end basecross