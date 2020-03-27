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
	void FlyMaster::Create_PossessionMeat(int createMeatID) {
		auto stage = App::GetApp()->GetScene<Scene>()->GetActiveStage();
		shared_ptr<GameObject> newMeat;
		m_possessionMeatID = createMeatID;
		switch (createMeatID)
		{
		case 1:
			newMeat = stage->AddGameObject<Karaage>(Vec3(1, 0, 1), Vec3(MAPCHIP_START_X, MAPCHIP_START_Y, 6), Vec3(0));
			Reset_PossessionMeat(newMeat);
			break;
		case 2:
			newMeat = stage->AddGameObject<Drum>(Vec3(1, 0, 1), Vec3(MAPCHIP_START_X, MAPCHIP_START_Y, 6), Vec3(0));
			Reset_PossessionMeat(newMeat);
			break;
		case 3:
			newMeat = stage->AddGameObject<Keel>(Vec3(1, 0, 1), Vec3(MAPCHIP_START_X, MAPCHIP_START_Y, 6), Vec3(0));
			Reset_PossessionMeat(newMeat);
			break;
		case 4:
			newMeat = stage->AddGameObject<Rib>(Vec3(1, 0, 1), Vec3(MAPCHIP_START_X, MAPCHIP_START_Y, 6), Vec3(0));
			Reset_PossessionMeat(newMeat);
			break;
		case 5:
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
		Vec3 pos;
		if (!m_isMove) {
			switch (direction)
			{
			case RIGHT:
				pos = m_possessionMeat->GetComponent<Transform>()->GetPosition();
				pos.x += MAPCHIP_SIZE_X;
				m_possessionMeat->GetComponent<Transform>()->SetPosition(pos);
				m_isMove = true;
				break;
			case LEFT:
				pos = m_possessionMeat->GetComponent<Transform>()->GetPosition();
				pos.x -= MAPCHIP_SIZE_X;
				m_possessionMeat->GetComponent<Transform>()->SetPosition(pos);
				m_isMove = true;
				break;
			case UP:
				pos = m_possessionMeat->GetComponent<Transform>()->GetPosition();
				pos.y += MAPCHIP_SIZE_Y;
				m_possessionMeat->GetComponent<Transform>()->SetPosition(pos);
				m_isMove = true;
				break;
			case DOWN:
				pos = m_possessionMeat->GetComponent<Transform>()->GetPosition();
				pos.y -= MAPCHIP_SIZE_Y;
				m_possessionMeat->GetComponent<Transform>()->SetPosition(pos);
				m_isMove = true;
				break;
			default:
				break;
			}
		}
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
				m_possessionMeatID = 1;
			}
			else {
				m_possessionMeatID++;
			}
			FlyMaster::Create_PossessionMeat(m_possessionMeatID);
		}
	}
}
//end basecross