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
		m_Numbers[5] = (stage->AddGameObject<NumberUI>(Vec2(-520, 150), Vec3(30.0f, 30.0f, 1.0f), L"Tex_Number"));
		m_Numbers[4] = (stage->AddGameObject<NumberUI>(Vec2(-420, 150), Vec3(30.0f, 30.0f, 1.0f), L"Tex_Number"));
		m_Numbers[3] = (stage->AddGameObject<NumberUI>(Vec2(-470, 150), Vec3(30.0f, 30.0f, 1.0f), L"Tex_Number"));
		m_Numbers[2] = (stage->AddGameObject<NumberUI>(Vec2(-370, 150), Vec3(30.0f, 30.0f, 1.0f), L"Tex_Number"));
		m_Numbers[1] = (stage->AddGameObject<NumberUI>(Vec2(-320, 150), Vec3(30.0f, 30.0f, 1.0f), L"Tex_Number"));
		m_Numbers[0] = (stage->AddGameObject<NumberUI>(Vec2(-270, 150), Vec3(30.0f, 30.0f, 1.0f), L"Tex_Number"));

	}
	/// ----------------------------------------<summary>
	/// ゲームのUIの作成
	/// </summary>----------------------------------------
	void FlyMaster::Create_GameUI() {
		auto stage = App::GetApp()->GetScene<Scene>()->GetActiveStage();
		stage->AddGameObject<MeatUI>(Vec2(0), Vec3(670.0f, 400.0f, 0.0f), L"BG_Kitchen");
		stage->AddGameObject<MeatUI>(Vec2(-20, -17), Vec3(195.0f, 230.0f, 1.0f), L"BG_Flyer");
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
		Sales(m_meatsInstallationData);
		Clear_InstallationMeat();
	}

	/// ----------------------------------------<summary>
	/// 設置済み肉の初期化
	/// </summary>----------------------------------------
	void FlyMaster::Clear_InstallationMeat() {
		auto stage = App::GetApp()->GetScene<Scene>()->GetActiveStage();
		for (int i = 0; i < m_installationMeat.size(); i++) {
			stage->RemoveGameObject<GameObject>(m_installationMeat[i]);
		}
		m_installationMeat.clear();
		m_meatsInstallationData.Karage = 0;
		m_meatsInstallationData.Drum = 0;
		m_meatsInstallationData.Wing = 0;
		m_meatsInstallationData.Lib = 0;
		m_meatsInstallationData.Keel = 0;

	}

	/// ----------------------------------------<summary>
	/// 在庫肉の初期化
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
		Add_StockMeat();
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
		Set_Num(m_nowMoney);
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
			break;
		case ドラム:
			newMeat = stage->AddGameObject<Drum>(Vec3(1, 0, 1), Vec3(MAPCHIP_START_X, MAPCHIP_START_Y, 6), quat);
			Reset_PossessionMeat(newMeat);
			break;
		case キール:
			newMeat = stage->AddGameObject<Keel>(Vec3(1, 0, 1), Vec3(MAPCHIP_START_X, MAPCHIP_START_Y, 6), quat);
			Reset_PossessionMeat(newMeat);
			break;
		case リブ:
			newMeat = stage->AddGameObject<Rib>(Vec3(1, 0, 1), Vec3(MAPCHIP_START_X, MAPCHIP_START_Y, 6), quat);
			Reset_PossessionMeat(newMeat);
			break;
		case ウィング:
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
			shared_ptr<GameObject> newMeat;
			//所持肉IDで
			switch (m_possessionMeatID)
			{
			case 唐揚げ:
				newMeat = stage->AddGameObject<Karaage>(Vec3(1, 0, 1), Vec3(possessoionPos.x, possessoionPos.y, 0), newMeatRot);
				m_installationMeat.push_back(newMeat);
				m_meatsInstallationData.Karage++;
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


	void FlyMaster::Set_Num(int num) {
		//最大6桁かな…(100,000)
		//一桁ずつ取って格納
		m_NowNumber[0] = (num % 10); num /= 10;//1
		m_NowNumber[1] = (num % 10); num /= 10;//2
		m_NowNumber[2] = (num % 10); num /= 10;//3
		m_NowNumber[3] = (num % 10); num /= 10;//4
		m_NowNumber[4] = (num % 10); num /= 10;//5
		m_NowNumber[5] = (num % 10); num /= 10;//6
		Update_num();
	}
	void FlyMaster::Update_num() {
		auto nums = FlyMaster::GetInstans().GetNumbers();
		for (int i = 0; i < 6; i++) {
			Set_Rect(m_NowNumber[i], nums[i]);
		}
	}
	void FlyMaster::Set_Rect(int num, shared_ptr<GameObject> numobj) {
		vector<VertexPositionColorTexture> vertices;
		switch (num)
		{
		case 0:
			vertices.push_back(VertexPositionColorTexture(Vec3(-1.0f, 1.0f, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(m_numRects[0].left, 0.0f)));
			vertices.push_back(VertexPositionColorTexture(Vec3(1.0f, 1.0f, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(m_numRects[0].top, 0.0f)));
			vertices.push_back(VertexPositionColorTexture(Vec3(-1.0f, -1.0f, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(m_numRects[0].right, 1.0f)));
			vertices.push_back(VertexPositionColorTexture(Vec3(1.0f, -1.0f, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(m_numRects[0].bottom, 1.0f)));
			numobj->GetComponent<PCTSpriteDraw>()->UpdateVertices(vertices);
			break;
		case 1:
			vertices.push_back(VertexPositionColorTexture(Vec3(-1.0f, 1.0f, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(m_numRects[1].left, 0.0f)));
			vertices.push_back(VertexPositionColorTexture(Vec3(1.0f, 1.0f, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(m_numRects[1].top, 0.0f)));
			vertices.push_back(VertexPositionColorTexture(Vec3(-1.0f, -1.0f, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(m_numRects[1].right, 1.0f)));
			vertices.push_back(VertexPositionColorTexture(Vec3(1.0f, -1.0f, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(m_numRects[1].bottom, 1.0f)));
			numobj->GetComponent<PCTSpriteDraw>()->UpdateVertices(vertices);
			break;
		case 2:
			vertices.push_back(VertexPositionColorTexture(Vec3(-1.0f, 1.0f, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(m_numRects[2].left, 0.0f)));
			vertices.push_back(VertexPositionColorTexture(Vec3(1.0f, 1.0f, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(m_numRects[2].top, 0.0f)));
			vertices.push_back(VertexPositionColorTexture(Vec3(-1.0f, -1.0f, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(m_numRects[2].right, 1.0f)));
			vertices.push_back(VertexPositionColorTexture(Vec3(1.0f, -1.0f, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(m_numRects[2].bottom, 1.0f)));
			numobj->GetComponent<PCTSpriteDraw>()->UpdateVertices(vertices);
			break;
		case 3:
			vertices.push_back(VertexPositionColorTexture(Vec3(-1.0f, 1.0f, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(m_numRects[3].left, 0.0f)));
			vertices.push_back(VertexPositionColorTexture(Vec3(1.0f, 1.0f, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(m_numRects[3].top, 0.0f)));
			vertices.push_back(VertexPositionColorTexture(Vec3(-1.0f, -1.0f, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(m_numRects[3].right, 1.0f)));
			vertices.push_back(VertexPositionColorTexture(Vec3(1.0f, -1.0f, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(m_numRects[3].bottom, 1.0f)));
			numobj->GetComponent<PCTSpriteDraw>()->UpdateVertices(vertices);
			break;
		case 4:
			vertices.push_back(VertexPositionColorTexture(Vec3(-1.0f, 1.0f, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(m_numRects[4].left, 0.0f)));
			vertices.push_back(VertexPositionColorTexture(Vec3(1.0f, 1.0f, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(m_numRects[4].top, 0.0f)));
			vertices.push_back(VertexPositionColorTexture(Vec3(-1.0f, -1.0f, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(m_numRects[4].right, 1.0f)));
			vertices.push_back(VertexPositionColorTexture(Vec3(1.0f, -1.0f, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(m_numRects[4].bottom, 1.0f)));
			numobj->GetComponent<PCTSpriteDraw>()->UpdateVertices(vertices);
			break;
		case 5:
			vertices.push_back(VertexPositionColorTexture(Vec3(-1.0f, 1.0f, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(m_numRects[5].left, 0.0f)));
			vertices.push_back(VertexPositionColorTexture(Vec3(1.0f, 1.0f, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(m_numRects[5].top, 0.0f)));
			vertices.push_back(VertexPositionColorTexture(Vec3(-1.0f, -1.0f, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(m_numRects[5].right, 1.0f)));
			vertices.push_back(VertexPositionColorTexture(Vec3(1.0f, -1.0f, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(m_numRects[5].bottom, 1.0f)));
			numobj->GetComponent<PCTSpriteDraw>()->UpdateVertices(vertices);
			break;
		case 6:
			vertices.push_back(VertexPositionColorTexture(Vec3(-1.0f, 1.0f, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(m_numRects[6].left, 0.0f)));
			vertices.push_back(VertexPositionColorTexture(Vec3(1.0f, 1.0f, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(m_numRects[6].top, 0.0f)));
			vertices.push_back(VertexPositionColorTexture(Vec3(-1.0f, -1.0f, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(m_numRects[6].right, 1.0f)));
			vertices.push_back(VertexPositionColorTexture(Vec3(1.0f, -1.0f, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(m_numRects[6].bottom, 1.0f)));
			numobj->GetComponent<PCTSpriteDraw>()->UpdateVertices(vertices);
			break;
		case 7:
			vertices.push_back(VertexPositionColorTexture(Vec3(-1.0f, 1.0f, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(m_numRects[7].left, 0.0f)));
			vertices.push_back(VertexPositionColorTexture(Vec3(1.0f, 1.0f, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(m_numRects[7].top, 0.0f)));
			vertices.push_back(VertexPositionColorTexture(Vec3(-1.0f, -1.0f, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(m_numRects[7].right, 1.0f)));
			vertices.push_back(VertexPositionColorTexture(Vec3(1.0f, -1.0f, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(m_numRects[7].bottom, 1.0f)));
			numobj->GetComponent<PCTSpriteDraw>()->UpdateVertices(vertices);
			break;
		case 8:
			vertices.push_back(VertexPositionColorTexture(Vec3(-1.0f, 1.0f, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(m_numRects[8].left, 0.0f)));
			vertices.push_back(VertexPositionColorTexture(Vec3(1.0f, 1.0f, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(m_numRects[8].top, 0.0f)));
			vertices.push_back(VertexPositionColorTexture(Vec3(-1.0f, -1.0f, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(m_numRects[8].right, 1.0f)));
			vertices.push_back(VertexPositionColorTexture(Vec3(1.0f, -1.0f, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(m_numRects[8].bottom, 1.0f)));
			numobj->GetComponent<PCTSpriteDraw>()->UpdateVertices(vertices);
			break;
		case 9:
			vertices.push_back(VertexPositionColorTexture(Vec3(-1.0f, 1.0f, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(m_numRects[9].left, 0.0f)));
			vertices.push_back(VertexPositionColorTexture(Vec3(1.0f, 1.0f, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(m_numRects[9].top, 0.0f)));
			vertices.push_back(VertexPositionColorTexture(Vec3(-1.0f, -1.0f, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(m_numRects[9].right, 1.0f)));
			vertices.push_back(VertexPositionColorTexture(Vec3(1.0f, -1.0f, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(m_numRects[9].bottom, 1.0f)));
			numobj->GetComponent<PCTSpriteDraw>()->UpdateVertices(vertices);
			break;
		default:
			break;
		}
	}
}
//end basecross