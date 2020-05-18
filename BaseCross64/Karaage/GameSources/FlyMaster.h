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
#define MAPCHIP_SIZE_X 60.0f
#define MAPCHIP_SIZE_Y 60.0f
//マップチップの開始地点
#define MAPCHIP_START_X -140.0f
#define MAPCHIP_START_Y 250.0f
//左右
#define LEFT	4
#define RIGHT	6
#define UP		8
#define DOWN	2
//デフォルトで解放されてる肉の種類数
#define DEFAULT_RELEASE_MEATS 3
//肉の種類の最大値
#define MAX_MEATCOUNT 5
//移動リミット
#define MOVELIMIT_MIN_X -140
#define MOVELIMIT_MIN_Y -270
#define MOVELIMIT_MAX_X  60
#define MOVELIMIT_MAX_Y  250
//配置状況の数値
#define Setup_FALSE 9
//各種肉の金額
#define PRICE_KARAAGE	70; //唐揚げ
#define PRICE_DRUM		100;   //脚
#define PRICE_WING		130;   //手羽先
#define PRICE_LIB		150;    //あばら
#define PRICE_KEEL		200;   //胸
//各種肉のオーダー最大数
#define LIMIT_ORDER_KARAAGE	5;
#define LIMIT_ORDER_DRUM	5;
#define LIMIT_ORDER_WING	5;
#define LIMIT_ORDER_LIB		5;
#define LIMIT_ORDER_KEEL	5;
namespace basecross {
	//各種肉の個数情報
	struct MeatsData
	{
		unsigned int Karage;
		unsigned int Drum;
		unsigned int Wing;
		unsigned int Lib;
		unsigned int Keel;
	};
	//肉のID
	enum MeatID
	{
		唐揚げ,ドラム,キール,リブ,ウィング
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
		int m_gameField[GAMEFIELD_Y][GAMEFIELD_X] = {0};
		//接触マップチップ番号
		int *m_hittingMapChipNum[2];
		//所持中の肉
		shared_ptr<GameObject> m_possessionMeat;
		//設置した肉達
		vector<shared_ptr<GameObject>> m_installationMeat;
		//テスト用の数値
		bool m_TEST_w;
		//現在解放中の肉数
		int m_releaseMeatCount = DEFAULT_RELEASE_MEATS;
		//現在の所持肉のID
		int m_possessionMeatID = 0;
		//移動のリキャストが済んでるか
		bool m_isMove;
		//今の移動している距離(0=x 1=y)
		int m_moveDistance[2]= { 0 };
		//所持肉の回転数値
		int m_RotationNum = 0;
		//目標金額
		int m_targetMoney = 0;
		//現在金額
		int m_nowMoney = 0;
		//------------肉の各種判定------------//
		int Hit_Karaage[3][3] = {
								{9,1,1},
								{1,1,1},
								{1,1,1}
		};
		int Hit_Drum[3][3] = {
								{9,1,1},
								{9,1,1},
								{1,1,1}
		};
		int Hit_Wing[3][3] = {
								{9,9,1},
								{9,1,1},
								{1,1,1}
		};
		int Hit_Rib[3][3] = {
								{9,9,1},
								{9,9,1},
								{1,1,1}
		};
		int Hit_Keel[3][3] = {
								{9,9,9},
								{9,9,9},
								{1,9,1}
		};
		//------------------------------------//
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
		//肉の設置
		void Set_PossessionMeat();
		//肉が設置できるか調べる
		bool Check_SetMeat();
		//所持肉の回転
		void Rot_PossessionMeat(int angle);
		//売上計算
		void Sales(MeatsData md);
		//配列の回転
		void Rot_Array();
		//ゲームを始める時
		void GAMESTART(int TargetMoney);
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