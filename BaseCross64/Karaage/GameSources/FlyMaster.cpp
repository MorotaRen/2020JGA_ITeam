#include "stdafx.h"
#include "Project.h"

namespace basecross {
	/// ----------------------------------------<summary>
	/// ゲームスタートの時の関数
	/// これを起動でゲームが始まる
	/// </summary>----------------------------------------
	void FlyMaster::GAMESTART(int targetMoney,int time) {
		//ゲームを始めるからステータスをtrueに
		m_gameStatus = true;
		//目標金額の設定
		m_targetMoney = targetMoney;
		//数字UIの範囲
		float Range = 0.1f;
		m_numRects.resize(10);
		for (int i = 0; i < 10; i++) {
			m_numRects[i] =
			{
				//左上(left)
				static_cast<float> (0 + (Range * i)),
				//右上(top)
				static_cast<float> (0.1f + (Range * i)),
				//右下(right)
				static_cast<float> (0 + (Range * i)),
				//左下(buttom)
				static_cast<float> (0.1f + (Range * i)),
			};
		}
		auto stage = App::GetApp()->GetScene<Scene>()->GetActiveStage();
		//現在金額数字
		Vec2 nowMoneyStartPos = Vec2(NOWMONEY_STARTPOS_X,NOWMONEY_STARTPOS_Y);
		for (int i = 0; i < m_Numbers.size(); i++)
		{
			m_Numbers[i] = (stage->AddGameObject<NumberUI>(Vec2(nowMoneyStartPos.x,nowMoneyStartPos.y), Vec3(30.0f, 30.0f, 1.0f), L"Tex_Number"));
			nowMoneyStartPos.x -= NOWMONEY_INTERVAL;
		}
		//タイマー用数字
		Vec2 timerStartPos = Vec2(TIMER_STARTPOS_X,TIMER_STARTPOS_Y);
		for (int i = 1; i < m_TimerNumbers.size();i++) {
			m_TimerNumbers[i] = (stage->AddGameObject<NumberUI>(Vec2(timerStartPos.x,timerStartPos.y), Vec3(20.0f, 20.0f, 1.0f), L"Tex_Number"));
			timerStartPos.x -= TIMER_INTERVAL;
		}
		//目標金額数字
		Vec2 targetMoneyStartPos = Vec2(TARGET_STARTPOS_X,TARGET_STARTPOS_Y);
		for (int i = 0; i < m_targetMoneyNumbers.size();i++) {
			m_targetMoneyNumbers[i] = (stage->AddGameObject<NumberUI>(Vec2(targetMoneyStartPos.x,targetMoneyStartPos.y), Vec3(30.0f, 30.0f, 1.0f), L"Tex_Number"));
			targetMoneyStartPos.x -= TARGET_INTERVAL;
		}
		//タイマーセット
		Set_Timer(time, m_TimerNumbers);
		Set_Num(targetMoney,m_targetMoneyNumbers);

		//UIの作成
		FlyMaster::GetInstans().Create_GameUI();
		FlyMaster::GetInstans().Create_GameField();
		FlyMaster::GetInstans().Create_PossessionMeat(0);

		//オーバーレイ用のスプライト
		m_overSprite_Oil =  stage->AddGameObject<OverUI>(Vec2(-20, -20), Vec3(190.0f, 330.0f, 1.0f), L"Tex_Oil");
		m_overSprite_Oil->SetDrawActive(false);
	}
	/// ----------------------------------------<summary>
	/// ゲームセット
	/// </summary>----------------------------------------
	void FlyMaster::GAMESET() {
		//終わりってことだからステータスをfalse
		m_gameStatus = false;
		//操作止めたからそこまでの画像を表示、横からスクロールさせるか
		auto stage = App::GetApp()->GetScene<Scene>()->GetActiveStage();
		stage->AddGameObject<MultiSprite>(true, Vec2(640, 400), Vec3(0, 0, 0), L"Sokomade_TX");
		//残り時間を格納してそれをリザルトで見るか…
		m_C_min = m_Nowmin;
		m_C_sec = m_Nowsec;
	}
	/// ----------------------------------------<summary>
	/// ゲームのUIの作成
	/// </summary>----------------------------------------
	void FlyMaster::Create_GameUI() {
		auto stage = App::GetApp()->GetScene<Scene>()->GetActiveStage();
		stage->AddGameObject<MeatUI>(Vec2(0), Vec3(670.0f, 400.0f, 0.0f), L"BG_Kitchen");
		stage->AddGameObject<MeatUI>(Vec2(-20, -17), Vec3(195.0f, 230.0f, 1.0f), L"BG_Flyer");
		stage->AddGameObject<MeatUI>(Vec2(500, 220), Vec3(100.0f, 100.0f, 1.0f), L"Tex_Timer");
		stage->AddGameObject<MeatUI>(Vec2(240, 100), Vec3(30.0f, 30.0f, 1.0f), L"Icon_RegisterMark");

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
		auto stage = App::GetApp()->GetScene<Scene>()->GetActiveStage();
		//ステージに設置されてる肉の削除
		for (int i = 0; i < m_installationMeat.size(); i++) {
			stage->RemoveGameObject<GameObject>(m_installationMeat[i]);
		}
		m_installationMeat.clear();
		//フィールドの初期化
		for (int i = 0; i < GAMEFIELD_Y;i++) {
			for (int t = 0; t < GAMEFIELD_X; t++) {
				m_gameField[i][t] = 0;
			}
		}
		m_meatsInstallationData = {};

	}
	/// ----------------------------------------<summary>
	/// 在庫肉の初期化
	/// </summary>----------------------------------------
	void FlyMaster::Clear_StockMeat() {
		m_meatsStockData = {};
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
												   0);
			}
		}

	}
	/// ----------------------------------------<summary>
	/// 揚げる処理
	/// </summary>----------------------------------------
	void FlyMaster::Fly() {
		m_overSprite_Oil->SetDrawActive(true);
		m_timerForOil = true;
		m_possessionMeat->SetDrawActive(false);
		App::GetApp()->GetScene<Scene>()->MusicOnecStart(L"SE_Fly",1.0f);
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
		Set_Num(m_nowMoney,m_Numbers);
		Check_Comparison();
	}
	/// ----------------------------------------<summary>
	/// 目標金額と現在金額の比較
	///	達成ならTRUE
	/// </summary>----------------------------------------
	bool FlyMaster::Check_Comparison() {
		if (m_targetMoney <= m_nowMoney) {
			MessageBox(0,L"げーむくりあ",0,0);
			return true;
		}else {
			return false;
		}

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
		case karaage:
			newMeat = stage->AddGameObject<Karaage>(Vec3(1, 0, 1), Vec3(MAPCHIP_START_X, MAPCHIP_START_Y, 6), quat);
			Reset_PossessionMeat(newMeat);
			break;
		case drum:
			newMeat = stage->AddGameObject<Drum>(Vec3(1, 0, 1), Vec3(MAPCHIP_START_X, MAPCHIP_START_Y, 6), quat);
			Reset_PossessionMeat(newMeat);
			break;
		case keel:
			newMeat = stage->AddGameObject<Keel>(Vec3(1, 0, 1), Vec3(MAPCHIP_START_X, MAPCHIP_START_Y, 6), quat);
			Reset_PossessionMeat(newMeat);
			break;
		case rib:
			newMeat = stage->AddGameObject<Rib>(Vec3(1, 0, 1), Vec3(MAPCHIP_START_X, MAPCHIP_START_Y, 6), quat);
			Reset_PossessionMeat(newMeat);
			break;
		case wing:
			newMeat = stage->AddGameObject<Wing>(Vec3(1, 0, 1), Vec3(MAPCHIP_START_X, MAPCHIP_START_Y, 6), quat);
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
					if (m_moveDistance[1] <= (GAMEFIELD_X-2)) {
						pos = m_possessionMeat->GetComponent<Transform>()->GetPosition();
						pos.x += MAPCHIP_SIZE_X;
						m_possessionMeat->GetComponent<Transform>()->SetPosition(pos);
						m_isMove = true;
						m_moveDistance[1]++;
					}
					break;
				case LEFT:
					if (m_moveDistance[1] > 0) {
						pos = m_possessionMeat->GetComponent<Transform>()->GetPosition();
						pos.x -= MAPCHIP_SIZE_X;
						m_possessionMeat->GetComponent<Transform>()->SetPosition(pos);
						m_isMove = true;
						m_moveDistance[1]--;
					}
					break;
				case UP:
					if (m_moveDistance[0] > 0) {
						pos = m_possessionMeat->GetComponent<Transform>()->GetPosition();
						pos.y += MAPCHIP_SIZE_Y;
						m_possessionMeat->GetComponent<Transform>()->SetPosition(pos);
						m_isMove = true;
						m_moveDistance[0]--;
					}
					break;
				case DOWN:
					if (m_moveDistance[0] <= (GAMEFIELD_Y-2)) {
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
	/// 移動リキャスト
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
			if (m_possessionMeatID > MAX_MEATCOUNT) {
				m_possessionMeatID = 0;
			}
			else {
				m_possessionMeatID++;
			}
			m_moveDistance[0] = 0;
			m_moveDistance[1] = 0;
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
			shared_ptr<GameObject> newMeat;
			Debug_Map();
			//所持肉IDで
			switch (m_possessionMeatID)
			{
			case karaage:
				newMeat = stage->AddGameObject<Karaage>(Vec3(1, 0, 1), Vec3(possessoionPos.x, possessoionPos.y, 0), newMeatRot);
				m_installationMeat.push_back(newMeat);
				m_meatsInstallationData.Karage++;
				break;
			case drum:
				newMeat = stage->AddGameObject<Drum>(Vec3(1, 0, 1), Vec3(possessoionPos.x - 30, possessoionPos.y + 30, 0), newMeatRot);
				m_installationMeat.push_back(newMeat);
				m_meatsInstallationData.Drum++;
				break;
			case keel:
				newMeat = stage->AddGameObject<Keel>(Vec3(1, 0, 1), Vec3(possessoionPos.x - 60, possessoionPos.y + 60, 0), newMeatRot);
				m_installationMeat.push_back(newMeat);
				m_meatsInstallationData.Keel++;
				break;
			case rib:
				newMeat = stage->AddGameObject<Rib>(Vec3(1, 0, 1), Vec3(possessoionPos.x - 40, possessoionPos.y + 40, 0), newMeatRot);
				m_installationMeat.push_back(newMeat);
				m_meatsInstallationData.Lib++;
				break;
			case wing:
				newMeat = stage->AddGameObject<Wing>(Vec3(1, 0, 1), Vec3(possessoionPos.x - 30, possessoionPos.y + 30, 0), newMeatRot);
				m_installationMeat.push_back(newMeat);
				m_meatsInstallationData.Wing++;
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
			unsigned int Counter = 0;
			//所持肉IDで
			switch (m_possessionMeatID)
			{
			case karaage:
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

			case drum:
				for (int y = 0; y < 2; y++) {
					for (int x = 0; x < 2; x++) {
						if (m_gameField[StartPosY + y][StartPosX + x] == Hit_Drum[y][x]) {
							return false;
							break;
						}
					}
				}
				//おく所を設置済みにする
				for (int y = 0; y < 2; y++) {
					for (int x = 0; x < 2; x++) {
						if (m_gameField[StartPosY + y][StartPosX + x] == 0 && Hit_Drum[y][x] == 9) {
							m_gameField[StartPosY + y][StartPosX + x] = 9;
							Counter++;
						}
					}
					if (Counter >= Drum_SetCount) {
						break;
					}
				}
				return true;
				break;
			case keel:
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
							Counter++;
						}
					}
					if (Counter >= Keel_SetCount) {
						break;
					}
				}
				return true;
				break;
			case rib:
				for (int y = 0; y < 2; y++) {
					for (int x = 0; x < 2; x++) {
						if (m_gameField[StartPosY + y][StartPosX + x] == Hit_Rib[y][x]) {
							return false;
							break;
						}
					}
				}
				//おく所を設置済みにする
				for (int y = 0; y < 2; y++) {
					for (int x = 0; x < 2; x++) {
						if (m_gameField[StartPosY + y][StartPosX + x] == 0 && Hit_Rib[y][x] == 9) {
							m_gameField[StartPosY + y][StartPosX + x] = 9;
							Counter++;
						}
					}
					if (Counter >= Rib_SetCount) {
						break;
					}
				}
				return true;
				break;
			case wing:
				for (int y = 0; y < 2; y++) {
					for (int x = 0; x < 2; x++) {
						if (m_gameField[StartPosY + y][StartPosX + x] == Hit_Wing[y][x]) {
							return false;
							break;
						}
					}
				}
				//おく所を設置済みにする
				for (int y = 0; y < 2; y++) {
					for (int x = 0; x < 2; x++) {
						if (m_gameField[StartPosY + y][StartPosX + x] == 0 && Hit_Wing[y][x] == 9) {
							m_gameField[StartPosY + y][StartPosX + x] = 9;
							Counter++;
						}
					}
					if (Counter >= Wing_SetCount) {
						break;
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
		int temp3x3[3][3] = { 0 };
		int temp2x2[3][3] = { 0 };

		//所持肉IDで
		switch (m_possessionMeatID)
		{
		case karaage:
			//回転しないので何もしない
			break;

		case drum:
			//一時置き場にコピー
			for (int i = 0; i < 2; i++) {
				for (int k = 0; k < 2; k++) {
					temp2x2[i][k] = Hit_Drum[i][k];
				}
			}
			//転置後行を逆にして右回り
			for (int i = 0; i < 2; i++) {
				for (int k = 0; k < 2; k++) {
					Hit_Drum[i][k] = temp2x2[k][2 - i];
				}
			}
			break;

		case keel:
			//一時置き場にコピー
			for (int i = 0; i < 3; i++) {
				for (int k = 0; k < 3; k++) {
					temp3x3[i][k] = Hit_Keel[i][k];
				}
			}
			//転置後行を逆にして右回り
			for (int i = 0; i < 3; i++) {
				for (int k = 0; k < 3; k++) {
					Hit_Keel[i][k] = temp3x3[k][2 - i];
				}
			}
			break;

		case rib:
			//一時置き場にコピー
			for (int i = 0; i < 2; i++) {
				for (int k = 0; k < 2; k++) {
					temp2x2[i][k] = Hit_Rib[i][k];
				}
			}
			//転置後行を逆にして右回り
			for (int i = 0; i < 2; i++) {
				for (int k = 0; k < 2; k++) {
					Hit_Rib[i][k] = temp2x2[k][2 - i];
				}
			}
			break;

		case wing:
			//一時置き場にコピー
			for (int i = 0; i < 2; i++) {
				for (int k = 0; k < 2; k++) {
					temp2x2[i][k] = Hit_Wing[i][k];
				}
			}
			//転置後行を逆にして右回り
			for (int i = 0; i < 2; i++) {
				for (int k = 0; k < 2; k++) {
					Hit_Wing[i][k] = temp2x2[k][2 - i];
				}
			}
			break;
		default:
			MessageBox(0,L"不明な肉IDが入りました(肉の回転)",0,0);
			break;
		}
	}
	/// ----------------------------------------<summary>
	/// スプライトに表示するために各桁を分解
	/// </summary>----------------------------------------
	void FlyMaster::Set_Num(int num,vector<shared_ptr<GameObject>> changennumobj) {
		//最大6桁かな…(100,000)
		//一桁ずつ取って格納
		for (int i = 0; i < changennumobj.size();i++) {
			m_NowNumber[i] = (num % 10); num /= 10;//1
		}
		Update_num(changennumobj);
	}
	/// ----------------------------------------<summary>
	/// スプライトの数字変更
	/// </summary>----------------------------------------
	void FlyMaster::Update_num(vector<shared_ptr<GameObject>> objs) {
		for (int i = 0; i < objs.size(); i++) {
			Set_Rect(m_NowNumber[i], objs[i]);
		}
	}
	/// ----------------------------------------<summary>
	/// スプライトのRect変更
	/// </summary>----------------------------------------
	void FlyMaster::Set_Rect(int num, shared_ptr<GameObject> numobj) {
		vector<VertexPositionColorTexture> vertices;
		if (num < 0 || num > 9) {
			return;
		}
		vertices.push_back(VertexPositionColorTexture(Vec3(-1.0f, 1.0f, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(m_numRects[num].left, 0.0f)));
		vertices.push_back(VertexPositionColorTexture(Vec3(1.0f, 1.0f, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(m_numRects[num].top, 0.0f)));
		vertices.push_back(VertexPositionColorTexture(Vec3(-1.0f, -1.0f, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(m_numRects[num].right, 1.0f)));
		vertices.push_back(VertexPositionColorTexture(Vec3(1.0f, -1.0f, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(m_numRects[num].bottom, 1.0f)));
		numobj->GetComponent<PCTSpriteDraw>()->UpdateVertices(vertices);

	}
	/// ----------------------------------------<summary>
	///	タイマーの設定
	/// </summary>----------------------------------------
	void FlyMaster::Set_Timer(int time, vector<shared_ptr<GameObject>> changenumobj) {
		//初期分設定…
		if (time != 999) {
			m_Nowmin = time;
			m_time = 59;
		}
		m_NowTime[3] = m_Nowmin;
		m_NowTime[1] = (m_Nowsec % 10); m_Nowsec /= 10;
		m_NowTime[2] = (m_Nowsec % 10); m_Nowsec /= 10;
		if (m_Nowmin == 0 && m_time <= 1) {
			//タイマー完全終わり
			MessageBox(0, 0, 0, 0);
		}
		if (m_NowTime[1] == 0 && m_time <= 1) {
			m_Nowmin--;
			m_time = 59;
		}

 		for (int i = 1; i < changenumobj.size();i++) {
			Set_Rect(m_NowTime[i],changenumobj[i]);
		}
	}
	/// ----------------------------------------<summary>
	///	タイマーの更新
	/// </summary>----------------------------------------
	void FlyMaster::Update_Timer() {
		auto deltatime = App::GetApp()->GetElapsedTime();
		m_time -=  1 * deltatime;

		m_Nowsec = m_time;
		Set_Timer(999,m_TimerNumbers);
	}
	/// ----------------------------------------<summary>
	///	フライヤータイマー
	/// </summary>----------------------------------------
	void FlyMaster::Fly_Timer() {
		auto deltatime = App::GetApp()->GetElapsedTime();
		m_flyTime -= 1 * deltatime;
		if (m_flyTime <= 0) {
			m_flyTime = FLY_RECAST_TIME;
			App::GetApp()->GetScene<Scene>()->MusicStop();
			Add_StockMeat();
			m_overSprite_Oil->SetDrawActive(false);
			m_possessionMeat->SetDrawActive(true);
			m_timerForOil = false;
		}
		else {
			m_timerForOil = true;
		}
	}
	/// ----------------------------------------<summary>
	///	客の総合管理
	/// </summary>----------------------------------------
	void FlyMaster::Master_Customers() {
		Customers_Count();
	}
	/// ----------------------------------------<summary>
	///	客の人数管理
	/// </summary>----------------------------------------
	void FlyMaster::Customers_Count() {
		//最大数以下の場合空きに追加
		if (m_nowCustomers < MAX_CUSTOMERS) {
			auto stage = App::GetApp()->GetScene<Scene>()->GetActiveStage();
			for (int i = 0; i < MAX_CUSTOMERS; i++)
			{
				//客がいない所に追加
				if (m_guests[i] == nullptr) {
						switch (i)
						{
						case 0 :
							m_guests[0] = stage->AddGameObject<Guest>(Vec3(240, 30,0.0f));
						}
				}
			}
		}
	}
	/// ----------------------------------------<summary>
	///	客の要求を満たすかの管理
	/// </summary>----------------------------------------
	void FlyMaster::Customers_Request() {
		//客の目的金額なので…コンフィグに設定金額を指定してそれで比較するか
		switch (m_stageNumber)
		{
		case 1:
			if (m_nowMoney >= STAGE_MONEY_1) {
				//すてーじ1くりあ！
				m_cleared = true;
			}
			break;
		case 2:
			if (m_nowMoney >= STAGE_MONEY_2) {
				//すてーじ2くりあ！
				m_cleared = true;
			}
			break;
		case 3:
			if (m_nowMoney >= STAGE_MONEY_3) {
				//すてーじ3くりあ！
				m_cleared = true;
			}
			break;
		case 4:
			if (m_nowMoney >= STAGE_MONEY_4) {
				//すてーじ4くりあ！
				m_cleared = true;
			}
			break;
		case 5:
			if (m_nowMoney >= STAGE_MONEY_5) {
				//すてーじ5くりあ！
				m_cleared = true;
			}
			break;
		default:
			break;
		}
	}
	/// ----------------------------------------<summary>
	///	MAPの状態表示のデバック
	/// </summary>----------------------------------------
	void FlyMaster::Debug_Map() {
		wstring str;
		for (int i = 0; i < GAMEFIELD_Y;i++) {
			for (int t = 0; t < GAMEFIELD_X; t++) {
				str += Util::FloatToWStr(m_gameField[i][t]) += L",";
			}
			str += L"\n";
		}
		auto ptrString = m_Numbers[0]->AddComponent<StringSprite>();
		ptrString->SetText(str);
	}
}
//end basecross