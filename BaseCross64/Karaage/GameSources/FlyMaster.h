#pragma once
/// ----------------------------------------<summary>
/// 揚げ物に関しての関数がまとまっているところ
/// どこからでも呼び出せる
/// 注：シングルトン
/// 管理者：諸田
/// </summary>----------------------------------------

#include "stdafx.h"

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

		//----------------------------------------//

	public:
		//関数呼ぶときに最初に呼び出す
		static FlyMaster& GetInstans() {
			static FlyMaster inst;
			return inst;
		}
		//在庫の追加
		void AddStockMeat();

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