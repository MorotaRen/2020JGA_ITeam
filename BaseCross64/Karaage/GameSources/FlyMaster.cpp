#include "stdafx.h"
#include "Project.h"

namespace basecross {
	/// ----------------------------------------<summary>
	/// ゲームスタートの時の関数
	/// これを起動でゲームが始まる
	/// </summary>----------------------------------------
	void FlyMaster::GAMESTART(int TargetMoney) {
		//目標金額の設定
		m_targetMoney = TargetMoney;
	}
	/// ----------------------------------------<summary>
	/// 在庫数に追加する。追加した後は設置されている数はリセットされる
	/// </summary>----------------------------------------
	void FlyMaster::Add_StockMeat() {
		m_meatsStockData.Karage += m_meatsInstallationData.Karage;
		m_meatsStockData.Drum += m_meatsInstallationData.Drum;
		m_meatsStockData.Wing += m_meatsInstallationData.Wing;
		m_meatsStockData.Lib += m_meatsInstallationData.Lib;
		m_meatsStockData.Keel += m_meatsInstallationData.Keel;

		Clear_InstallationMeat();
	}

	/// ----------------------------------------<summary>
	/// 設置済み肉の初期化
	/// </summary>----------------------------------------
	void FlyMaster::Clear_InstallationMeat() {
		m_meatsInstallationData.Karage = 0;
		m_meatsInstallationData.Drum = 0;
		m_meatsInstallationData.Wing = 0;
		m_meatsInstallationData.Lib = 0;
		m_meatsInstallationData.Keel = 0;
	}

	/// ----------------------------------------<summary>
	/// 在庫肉の初期化0
	/// </summary>----------------------------------------
	void FlyMaster::Clear_StockMeat() {
		m_meatsStockData.Karage = 0;
		m_meatsStockData.Drum = 0;
		m_meatsStockData.Wing = 0;
		m_meatsStockData.Lib = 0;
		m_meatsStockData.Keel = 0;
	}

	/// ----------------------------------------<summary>
	/// ゲームフィールドの作成
	/// </summary>----------------------------------------
	void FlyMaster::Create_GameField() {
		//アクティブステージの取得
		auto stage = App::GetApp()->GetScene<Scene>()->GetActiveStage();
		//-----以下テストフィールドの作成なので後ほど削除予定------//
		for (int y = 0; y < GAMEFIELD_Y;y++) {
			for (int x = 0; x < GAMEFIELD_X;x++) {
				//stage->AddGameObject<MapChip>(Vec2(MAPCHIP_START_X + x * MAPCHIP_SIZE_X, 
				//								   MAPCHIP_START_Y + -y *MAPCHIP_SIZE_Y),
				//								   m_TEST_w);
				//if (m_TEST_w) {
				//	m_TEST_w = false;
				//}
				//else {
				//	m_TEST_w = true;
				//}
			}
		}

	}

	/// ----------------------------------------<summary>
	/// 揚げる処理
	/// </summary>----------------------------------------
	void FlyMaster::Fly() {
		Add_StockMeat();
		Clear_InstallationMeat();
		Sales(m_meatsInstallationData);
	}

	/// ----------------------------------------<summary>
	/// 会計
	/// </summary>----------------------------------------
	void FlyMaster::Sales(MeatsData md) {
		int tempMoney = 0;
		tempMoney += md.Karage * PRICE_KARAAGE;
		tempMoney += md.Drum * PRICE_DRUM;
		tempMoney += md.Wing * PRICE_WING;
		tempMoney += md.Lib * PRICE_LIB;
		tempMoney += md.Keel * PRICE_KEEL;	

		m_nowMoney += tempMoney;
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
	void FlyMaster::Create_PossessionMeat(int createMeatID) {
		auto stage = App::GetApp()->GetScene<Scene>()->GetActiveStage();
		shared_ptr<GameObject> newMeat;
		Quat quat = Quat(Vec3(0,0,1),0);
		m_possessionMeatID = createMeatID;
	switch (createMeatID)
		{
		case 唐揚げ:
			newMeat = stage->AddGameObject<Karaage>(Vec3(1, 0, 1), Vec3(MAPCHIP_START_X, MAPCHIP_START_Y, 6), quat);
			Reset_PossessionMeat(newMeat);
			m_installationMeat.push_back(newMeat);
			m_meatsInstallationData.Karage++;
			break;
		case ドラム:
			newMeat = stage->AddGameObject<Drum>(Vec3(1, 0, 1), Vec3(MAPCHIP_START_X, MAPCHIP_START_Y, 6), quat);
			Reset_PossessionMeat(newMeat);
			m_meatsInstallationData.Drum++;
			break;
		case キール:
			newMeat = stage->AddGameObject<Keel>(Vec3(1, 0, 1), Vec3(MAPCHIP_START_X, MAPCHIP_START_Y, 6), quat);
			Reset_PossessionMeat(newMeat);
			m_meatsInstallationData.Keel++;
			break;
		case リブ:
			newMeat = stage->AddGameObject<Rib>(Vec3(1, 0, 1), Vec3(MAPCHIP_START_X, MAPCHIP_START_Y, 6), quat);
			Reset_PossessionMeat(newMeat);
			m_meatsInstallationData.Lib++;
			break;
		case ウィング:
			newMeat = stage->AddGameObject<Wing>(Vec3(1, 0, 1), Vec3(MAPCHIP_START_X, MAPCHIP_START_Y, 6), quat);
			Reset_PossessionMeat(newMeat);
			m_meatsInstallationData.Wing++;
			break;
		
		default:
			break;
		}

	}

	/// ----------------------------------------<summary>
	/// 所持肉のリセット
	/// </summary>----------------------------------------
	void FlyMaster::Reset_PossessionMeat(shared_ptr<GameObject> obj){
		auto possessionmeat = FlyMaster::GetInstans().GetPossessionMeat();
		if (possessionmeat) {
			//まず既存のやつを削除
			App::GetApp()->GetScene<Scene>()->GetActiveStage()->RemoveGameObject<GameObject>(possessionmeat);
			possessionmeat->DestroyGameObject();
			//所持肉を設定
			FlyMaster::GetInstans().SetPossessionMeat(obj);
		}
		//所持なしの場合
		FlyMaster::GetInstans().SetPossessionMeat(obj);
	}

	/// ----------------------------------------<summary>
	/// 所持肉の移動
	/// </summary>----------------------------------------
	void FlyMaster::Move_PossessionMeat(int direction) {
		Vec3 pos,possessionMeatPos;
		possessionMeatPos = m_possessionMeat->GetComponent<Transform>()->GetWorldPosition();
		if (!m_isMove) {
				switch (direction)
				{
				case RIGHT:
					if (possessionMeatPos.x < MOVELIMIT_MAX_X) {
						pos = m_possessionMeat->GetComponent<Transform>()->GetPosition();
						pos.x += MAPCHIP_SIZE_X;
						m_possessionMeat->GetComponent<Transform>()->SetPosition(pos);
						m_isMove = true;
						m_moveDistance[1]++;
					}
					break;
				case LEFT:
					if (possessionMeatPos.x > MOVELIMIT_MIN_X) {
						pos = m_possessionMeat->GetComponent<Transform>()->GetPosition();
						pos.x -= MAPCHIP_SIZE_X;
						m_possessionMeat->GetComponent<Transform>()->SetPosition(pos);
						m_isMove = true;
						m_moveDistance[1]--;
					}
					break;
				case UP:
					if (possessionMeatPos.y < MOVELIMIT_MAX_Y) {
						pos = m_possessionMeat->GetComponent<Transform>()->GetPosition();
						pos.y += MAPCHIP_SIZE_Y;
						m_possessionMeat->GetComponent<Transform>()->SetPosition(pos);
						m_isMove = true;
						m_moveDistance[0]--;
					}
					break;
				case DOWN:
					if (possessionMeatPos.y > MOVELIMIT_MIN_Y) {
						pos = m_possessionMeat->GetComponent<Transform>()->GetPosition();
						pos.y -= MAPCHIP_SIZE_Y;
						m_possessionMeat->GetComponent<Transform>()->SetPosition(pos);
						m_isMove = true;
						m_moveDistance[0]++;
					}
					break;
				default:
					break;
				}
		}
	}

	/// ----------------------------------------<summary>
	/// 所持肉の回転
	/// </summary>----------------------------------------
	void FlyMaster::Rot_PossessionMeat(int angle) {
		m_possessionMeat->Rotation();
		Rot_Array();
	}

	/// ----------------------------------------<summary>
	/// リキャストタイマー
	/// </summary>----------------------------------------
	void FlyMaster::Recast_Move() {
		auto pad = App::GetApp()->GetInputDevice().GetControlerVec();
		if (pad[0].fThumbLX < 0.1f && pad[0].fThumbLX > -0.1f &&
			pad[0].fThumbLY < 0.1f && pad[0].fThumbLY > -0.1f) {
			m_isMove = false;
		}
	}

	/// ----------------------------------------<summary>
	/// 所持肉の切り替え
	/// </summary>----------------------------------------
	void FlyMaster::Change_PossessionMeat() {
		auto pad = App::GetApp()->GetInputDevice().GetControlerVec();
		if (pad[0].wPressedButtons & XINPUT_GAMEPAD_LEFT_SHOULDER) {
			if (m_possessionMeatID >= MAX_MEATCOUNT) {
				m_possessionMeatID = 0;
			}
			else {
				m_possessionMeatID++;
			}
			FlyMaster::Create_PossessionMeat(m_possessionMeatID);
		}
	}

	/// ----------------------------------------<summary>
	/// 所持肉をステージに設置する
	/// </summary>----------------------------------------
	void FlyMaster::Set_PossessionMeat() {		
		//まずは設置する所を取得して
		Vec3 SetupPos = m_possessionMeat->GetComponent<Transform>()->GetPosition();
		Quat newMeatRot;
		if (m_possessionMeat) {
			newMeatRot = m_possessionMeat->GetComponent<Transform>()->GetQuaternion();
		}
		//置けないとかなかったら配置
		if (Check_SetMeat()) {
			auto stage = App::GetApp()->GetScene<Scene>()->GetActiveStage();
			//所持肉の位置
			Vec3 possessoionPos = m_possessionMeat->GetComponent<Transform>()->GetPosition();
			//所持肉IDで
			switch (m_possessionMeatID)
			{
			case 唐揚げ:
				stage->AddGameObject<Karaage>(Vec3(1, 0, 1), Vec3(possessoionPos.x, possessoionPos.y, 0), newMeatRot);
				break;
			case ドラム:
				stage->AddGameObject<Drum>(Vec3(1, 0, 1), Vec3(possessoionPos.x - 30, possessoionPos.y + 30, 0), newMeatRot);
				break;
			case キール:
				stage->AddGameObject<Keel>(Vec3(1, 0, 1), Vec3(possessoionPos.x - 60, possessoionPos.y + 60, 0), newMeatRot);
				break;
			case リブ:
				stage->AddGameObject<Rib>(Vec3(1, 0, 1), Vec3(possessoionPos.x - 40, possessoionPos.y + 40, 0), newMeatRot);
				break;
			case ウィング:
				stage->AddGameObject<Wing>(Vec3(1, 0, 1), Vec3(possessoionPos.x - 30, possessoionPos.y + 30, 0), newMeatRot);
				break;
			default:
				MessageBox(0, L"所持肉IDの不一致です。生成に失敗しました！", 0, 0);
				break;
			}
		}else {
			MessageBox(0,L"設置できないよ！",0,0);
		}

	}

	/// ----------------------------------------<summary>
	/// 肉が設置できるかを調べる
	/// </summary>----------------------------------------
	bool FlyMaster::Check_SetMeat() {
		//ゲームフィールドで移動と重複している所を見る
		int SetGridPosition = m_gameField[m_moveDistance[0]][m_moveDistance[1]];
		//全体(移動とそこから配列を見る)
		if (SetGridPosition != Setup_FALSE) {
			//始点
			auto StartPosX = m_moveDistance[1];
			auto StartPosY = m_moveDistance[0];

			//所持肉IDで
			switch (m_possessionMeatID)
			{
			case 唐揚げ:
				for (int y = 0; y < 3; y++) {
					for (int x = 0; x < 3; x++) {
						if (m_gameField[StartPosY + y][StartPosX + x] == Hit_Karaage[y][x]) {
							return false;
							break;
						}
					}
				}
				//おく所を設置済みにする
				for (int y = 0; y < 3; y++) {
					for (int x = 0; x < 3; x++) {
						if (m_gameField[StartPosY + y][StartPosX + x] == 0 && Hit_Karaage[y][x] == 9) {
							m_gameField[StartPosY + y][StartPosX + x] = 9;
							break;
						}
					}
				}
				return true;
				break;
			case ドラム:
				for (int y = 0; y < 3; y++) {
					for (int x = 0; x < 3; x++) {
						if (m_gameField[StartPosY + y][StartPosX + x] == Hit_Drum[y][x]) {
							return false;
							break;
						}
					}
				}
				//おく所を設置済みにする
				for (int y = 0; y < 3; y++) {
					for (int x = 0; x < 3; x++) {
						if (m_gameField[StartPosY + y][StartPosX + x] == 0 && Hit_Drum[y][x] == 9) {
							m_gameField[StartPosY + y][StartPosX + x] = 9;
						}
					}
				}
				return true;
				break;
			case キール:
				for (int y = 0; y < 3; y++) {
					for (int x = 0; x < 3; x++) {
						if (m_gameField[StartPosY + y][StartPosX + x] == Hit_Keel[y][x]) {
							return false;
							break;
						}
					}
				}
				//おく所を設置済みにする
				for (int y = 0; y < 3; y++) {
					for (int x = 0; x < 3; x++) {
						if (m_gameField[StartPosY + y][StartPosX + x] == 0 && Hit_Keel[y][x] == 9) {
							m_gameField[StartPosY + y][StartPosX + x] = 9;
						}
					}
				}
				return true;
				break;
			case リブ:
				for (int y = 0; y < 3; y++) {
					for (int x = 0; x < 3; x++) {
						if (m_gameField[StartPosY + y][StartPosX + x] == Hit_Rib[y][x]) {
							return false;
							break;
						}
					}
				}
				//おく所を設置済みにする
				for (int y = 0; y < 3; y++) {
					for (int x = 0; x < 3; x++) {
						if (m_gameField[StartPosY + y][StartPosX + x] == 0 && Hit_Rib[y][x] == 9) {
							m_gameField[StartPosY + y][StartPosX + x] = 9;
						}
					}
				}
				return true;
				break;
			case ウィング:
				for (int y = 0; y < 3; y++) {
					for (int x = 0; x < 3; x++) {
						if (m_gameField[StartPosY + y][StartPosX + x] == Hit_Wing[y][x]) {
							return false;
							break;
						}
					}
				}
				//おく所を設置済みにする
				for (int y = 0; y < 3; y++) {
					for (int x = 0; x < 3; x++) {
						if (m_gameField[StartPosY + y][StartPosX + x] == 0 && Hit_Wing[y][x] == 9) {
							m_gameField[StartPosY + y][StartPosX + x] = 9;
						}
					}
				}
				return true;
				break;
			default:
				break;
			}

		}
		////単体(移動で見る)
		//if (SetGridPosition != Setup_FALSE) {
		//	//設置するからそのマスを設置不可にする
		//	m_gameField[m_moveDistance[0]][m_moveDistance[1]] = Setup_FALSE;
		//	return true;
		//}
		return false;

	}

	/// ----------------------------------------<summary>
	/// 配列回転
	/// </summary>----------------------------------------
	void FlyMaster::Rot_Array() {
		//一時置き場
		int temp[3][3] = { 0 };

		//所持肉IDで
		switch (m_possessionMeatID)
		{
		case 唐揚げ:
			//回転しないので何もしない
			break;
		case ドラム:
			//一時置き場にコピー
			for (int i = 0; i < 3; i++) {
				for (int k = 0; k < 3; k++) {
					temp[i][k] = Hit_Drum[i][k];
				}
			}
			//転置後行を逆にして右回り
			for (int i = 0; i < 3; i++) {
				for (int k = 0; k < 3; k++) {
					Hit_Drum[i][k] = temp[k][2 - i];
				}
			}
			break;
		case キール:
			//一時置き場にコピー
			for (int i = 0; i < 3; i++) {
				for (int k = 0; k < 3; k++) {
					temp[i][k] = Hit_Keel[i][k];
				}
			}
			//転置後行を逆にして右回り
			for (int i = 0; i < 3; i++) {
				for (int k = 0; k < 3; k++) {
					Hit_Keel[i][k] = temp[k][2 - i];
				}
			}
			break;
		case リブ:
			//一時置き場にコピー
			for (int i = 0; i < 3; i++) {
				for (int k = 0; k < 3; k++) {
					temp[i][k] = Hit_Rib[i][k];
				}
			}
			//転置後行を逆にして右回り
			for (int i = 0; i < 3; i++) {
				for (int k = 0; k < 3; k++) {
					Hit_Rib[i][k] = temp[k][2 - i];
				}
			}
			break;
		case ウィング:
			//一時置き場にコピー
			for (int i = 0; i < 3; i++) {
				for (int k = 0; k < 3; k++) {
					temp[i][k] = Hit_Wing[i][k];
				}
			}
			//転置後行を逆にして右回り
			for (int i = 0; i < 3; i++) {
				for (int k = 0; k < 3; k++) {
					Hit_Wing[i][k] = temp[k][2 - i];
				}
			}
			break;
		default:
			MessageBox(0,L"不明な肉IDが入りました(肉の回転)",0,0);
			break;
		}
	}
}
//end basecross