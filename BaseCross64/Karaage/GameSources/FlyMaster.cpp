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
		m_possessionMeatID = createMeatID;
		switch (createMeatID)
		{
		case 唐揚げ:
			newMeat = stage->AddGameObject<Karaage>(Vec3(1, 0, 1), Vec3(MAPCHIP_START_X, MAPCHIP_START_Y, 6), Vec3(0));
			Reset_PossessionMeat(newMeat);
			break;
		case ドラム:
			newMeat = stage->AddGameObject<Drum>(Vec3(1, 0, 1), Vec3(MAPCHIP_START_X, MAPCHIP_START_Y, 6), Vec3(0));
			Reset_PossessionMeat(newMeat);
			break;
		case キール:
			newMeat = stage->AddGameObject<Keel>(Vec3(1, 0, 1), Vec3(MAPCHIP_START_X, MAPCHIP_START_Y, 6), Vec3(0));
			Reset_PossessionMeat(newMeat);
			break;
		case リブ:
			newMeat = stage->AddGameObject<Rib>(Vec3(1, 0, 1), Vec3(MAPCHIP_START_X, MAPCHIP_START_Y, 6), Vec3(0));
			Reset_PossessionMeat(newMeat);
			break;
		case ウィング:
			newMeat = stage->AddGameObject<Wing>(Vec3(1, 0, 1), Vec3(MAPCHIP_START_X, MAPCHIP_START_Y, 6), Vec3(0));
			Reset_PossessionMeat(newMeat);
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
		//肉に回転角度っていうか回転を何回してってのを保存して、それみて自分の判定データを
		//照合してあるかないか見るか
		

		
		//まずは設置する所を取得して
		Vec3 SetupPos = m_possessionMeat->GetComponent<Transform>()->GetPosition();
		//置けないとかなかったら配置
		if (Check_SetMeat()) {
			//設置してみる(テストで)
			auto stage = App::GetApp()->GetScene<Scene>()->GetActiveStage();
			//所持肉の位置
			Vec3 possessoionPos = m_possessionMeat->GetComponent<Transform>()->GetPosition();
			//所持肉IDで
			switch (m_possessionMeatID)
			{
			case 唐揚げ:
				stage->AddGameObject<Karaage>(Vec3(1, 0, 1), Vec3(possessoionPos.x, possessoionPos.y, 0), Vec3(1));
				break;
			case ドラム:
				stage->AddGameObject<Drum>(Vec3(1, 0, 1), Vec3(possessoionPos.x - 30, possessoionPos.y + 30, 0), Vec3(1));
				break;
			case キール:
				stage->AddGameObject<Keel>(Vec3(1, 0, 1), Vec3(possessoionPos.x - 30, possessoionPos.y + 30, 0), Vec3(1));
				break;
			case リブ:
				stage->AddGameObject<Rib>(Vec3(1, 0, 1), Vec3(possessoionPos.x - 40, possessoionPos.y + 40, 0), Vec3(1));
				break;
			case ウィング:
				stage->AddGameObject<Wing>(Vec3(1, 0, 1), Vec3(possessoionPos.x - 30, possessoionPos.y + 30, 0), Vec3(1));
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
				break;
			case キール:
				break;
			case リブ:
				break;
			case ウィング:
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
}
//end basecross