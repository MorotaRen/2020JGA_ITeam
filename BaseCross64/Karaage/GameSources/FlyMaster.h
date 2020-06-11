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
		unsigned int Karage;
		unsigned int Drum;
		unsigned int Wing;
		unsigned int Lib;
		unsigned int Keel;
	};
	//肉のID
	enum MeatID
	{
		karaage,drum,keel,rib,wing
	};

	class FlyMaster	final{
	private:
		//コンストラクタ
		FlyMaster() {};
		//デストラクタ
		~FlyMaster() {};
		//シングルトン用コンストラクタ
		FlyMaster(const FlyMaster&);

		//-------------------変数------------------//

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
		//現在時刻
		float m_time = 0;
		//フライヤータイマーの現在時間
		float m_flyTime = FLY_RECAST_TIME;
		//現在金額数字のポインタ
		vector<shared_ptr<GameObject>> m_Numbers = {0,0,0,0,0,0};
		//目標金額数字のポインタ
		vector<shared_ptr<GameObject>> m_targetMoneyNumbers = {0,0,0,0,0,0};
		//タイマー用数字
		vector<shared_ptr<GameObject>> m_TimerNumbers = {0,0,0,0,0};
		//適用する数字を分解したもの
		int m_NowNumber[6];
		//タイマー用の適用数字を分解したもの
		int m_NowTime[4];
		//ナンバーのUV座標達
		vector<Rect2D<float>> m_numRects = vector<Rect2D<float>>(10);
		//タイマー終了時の判定(油)
		bool m_timerForOil;
		//タイマー終了時の判定(Game)
		bool m_timerForGame;
		//オーバーレイ用のスプライトポインタ
		shared_ptr<GameObject> m_overSprite_Oil;	
		//お客達
		vector<shared_ptr<Guest>> m_guests = {0,0,0};
		//お客の数
		int m_nowCustomers = 0;
		//------------肉の各種判定------------//
		int Hit_Karaage[3][3] = {
								{9,1,1},
								{1,1,1},
								{1,1,1}
		};
		int Hit_Drum[2][2] = {
								{9,1},
								{9,1},
		};
		int Hit_Wing[2][2] = {
								{9,9},
								{9,1},
		};
		int Hit_Rib[2][2] = {
								{9,9},
								{9,9},
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
		//UIの作成
		void Create_GameUI();
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
		//移動リキャスト
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
		void GAMESTART(int targetMoney,int time);
		//ゲームセット
		void GAMESET();
		//表示用数値の分解
		void Set_Num(int num,vector<shared_ptr<GameObject>> changennumobj);
		//数字変更
		void Update_num(vector<shared_ptr<GameObject>> objs);
		//数字変更に伴うスプライトのUV座標の変更
		void Set_Rect(int num, shared_ptr<GameObject> numobj);
		//タイマーセット
		void Set_Timer(int time,vector<shared_ptr<GameObject>> changenumobj);
		//タイマーの更新		
		void Update_Timer();
		//目標と現在を比較する
		bool Check_Comparison();
		//フライヤータイマー
		void Fly_Timer();
		//客の総合管理
		void Master_Customers();
		//客の人数管理
		void Customers_Count();
		//客の要求を満たすかの管理
		void Customers_Request();
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
		vector<shared_ptr<GameObject>> GetNumbers() {
			return m_Numbers;
		}
		vector<Rect2D<float>> GetRects() {
			return m_numRects;
		}
		void SetTimeForOil(bool bl) {
			m_timerForOil = bl;
		}
		bool GetTimerForOil() {
			return m_timerForOil;
		}
		//----------------------------------------//

	};
}