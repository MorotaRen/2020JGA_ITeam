#pragma once
/// ----------------------------------------<summary>
/// 揚げ物に関しての関数がまとまっているところ
/// どこからでも呼び出せる
/// 注：シングルトン
/// 管理者：諸田
/// </summary>----------------------------------------

#include "stdafx.h"
//ゲームフィールドの縦横
#define GAMEFIELD_X 5
#define GAMEFIELD_Y 10
//揚げた後のリキャスト時間
#define FLY_RECAST_TIME 20
//マップチップのサイズ
#define MAPCHIP_SIZE_X 70.0f
#define MAPCHIP_SIZE_Y 70.0f
//マップチップの開始地点
#define MAPCHIP_START_X -100.0f
#define MAPCHIP_START_Y 300.0f
//左右
#define LEFT 4
#define RIGHT 6
#define UP 8
#define DOWN 2
//デフォルトで解放されてる肉の種類数
#define DEFAULT_RELEASE_MEATS 3
//肉の種類の最大値
#define MAX_MEATCOUNT 5

namespace basecross {
	//各種肉の個数情報
	struct MeatsData
	{
		unsigned int Meat_1x1;
		unsigned int Meat_1x2;
		unsigned int Meat_2x2;
		unsigned int Meat_3x3;
		unsigned int Meat_L;
	};

	class FlyMaster	final{
	private:
		//コンストラクタ
		FlyMaster() {};
		//デストラクタ
		~FlyMaster() {};
		//シングルトン用コンストラクタ
		FlyMaster(const FlyMaster&);

		//-------------------変数-----------------//

		//各種肉の在庫
		MeatsData m_meatsStockData;
		//今設置されてる各種肉
		MeatsData m_meatsInstallationData;
		//フィールド構造体
		int m_gameField[GAMEFIELD_X][GAMEFIELD_Y] = {0};
		//接触マップチップ番号
		int *m_hittingMapChipNum[2];
		//所持中の肉
		shared_ptr<GameObject> m_possessionMeat;
		//テスト用の数値
		bool m_TEST_w;
		//現在解放中の肉数
		int m_releaseMeatCount = DEFAULT_RELEASE_MEATS;
		//現在の所持肉のID
		int m_possessionMeatID;
		//移動のリキャストが済んでるか
		bool m_isMove;
		//----------------------------------------//

	public:
		//関数呼ぶときに最初に呼び出す
		static FlyMaster& GetInstans() {
			static FlyMaster inst;
			return inst;
		}
		//在庫の追加
		void Add_StockMeat();
		//設置済み肉数の初期化
		void Clear_InstallationMeat();
		//在庫のリセット
		void Clear_StockMeat();
		//フィールドの生成
		void Create_GameField();
		//揚げる
		void Fly();
		//渡された座標からマップ方向にレイを飛ばし接触したオブジェクトのマップ番号を返す
		int* Send_RayCastToMapChip(int *returnNum,Vec3 sendPos);
		//所持肉のリセット
		void Reset_PossessionMeat(shared_ptr<GameObject> obj);
		//所持肉の生成
		void Create_PossessionMeat(int createMeatID);
		//所持肉の移動
		void Move_PossessionMeat(int direction);
		//リキャストタイマー
		void Recast_Move();
		//所持肉の切り替え
		void Change_PossessionMeat();
		//------------ゲッターセッター--------------//
		void SetStockData(const MeatsData md) {
			m_meatsStockData = md;
		}
		MeatsData GetStockData() {
			return m_meatsStockData;
		}
		void SetMeatsInstallationData(const MeatsData md) {
			m_meatsInstallationData = md;
		}
		MeatsData GetMeatsInstallationData() {
			return m_meatsInstallationData;
		}
		void SetPossessionMeat(shared_ptr<GameObject> obj) {
			m_possessionMeat = obj;
		}
		shared_ptr<GameObject> GetPossessionMeat() {
			return m_possessionMeat;
		}
		//----------------------------------------//

	};
}