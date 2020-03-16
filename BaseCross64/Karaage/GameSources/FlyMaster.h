#pragma once
/// ----------------------------------------<summary>
/// 揚げ物に関しての関数がまとまっているところ
/// どこからでも呼び出せる
/// 注：シングルトン
/// 管理者：諸田
/// </summary>----------------------------------------

#include "stdafx.h"
//ゲームフィールドの縦
#define GAMEFIELD_X 10
//ゲームフィールドの横
#define GAMEFIELD_Y 5
//揚げた後のリキャスト時間
#define FLY_RECAST_TIME 20

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
		//

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
		//----------------------------------------//

	};
}