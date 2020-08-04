#include "stdafx.h"
#include "Project.h"

namespace basecross {
	/// ----------------------------------------<summary>
	/// �Q�[���X�^�[�g�̎��̊֐�
	/// ������N���ŃQ�[�����n�܂�
	/// </summary>----------------------------------------
	void FlyMaster::GAMESTART(int targetMoney,int time) {
		//�Q�[�����n�߂邩��X�e�[�^�X��true��
		m_gameStatus = true;
		//�ڕW���z�̐ݒ�
		m_targetMoney = targetMoney;
		//����UI�͈̔�
		float Range = 0.1f;
		m_numRects.resize(10);
		for (int i = 0; i < 10; i++) {
			m_numRects[i] =
			{
				//����(left)
				static_cast<float> (0 + (Range * i)),
				//�E��(top)
				static_cast<float> (0.1f + (Range * i)),
				//�E��(right)
				static_cast<float> (0 + (Range * i)),
				//����(buttom)
				static_cast<float> (0.1f + (Range * i)),
			};
		}
		auto stage = App::GetApp()->GetScene<Scene>()->GetActiveStage();
		//���݋��z����
		Vec2 nowMoneyStartPos = Vec2(NOWMONEY_STARTPOS_X,NOWMONEY_STARTPOS_Y);
		for (int i = 0; i < m_Numbers.size(); i++)
		{
			m_Numbers[i] = (stage->AddGameObject<NumberUI>(Vec2(nowMoneyStartPos.x,nowMoneyStartPos.y), Vec3(30.0f, 30.0f, 1.0f), L"Tex_Number"));
			nowMoneyStartPos.x -= NOWMONEY_INTERVAL;
		}
		//�^�C�}�[�p����
		Vec2 timerStartPos = Vec2(TIMER_STARTPOS_X,TIMER_STARTPOS_Y);
		for (int i = 1; i < m_TimerNumbers.size();i++) {
			m_TimerNumbers[i] = (stage->AddGameObject<NumberUI>(Vec2(timerStartPos.x,timerStartPos.y), Vec3(20.0f, 20.0f, 1.0f), L"Tex_Number"));
			timerStartPos.x -= TIMER_INTERVAL;
		}
		//�ڕW���z����
		Vec2 targetMoneyStartPos = Vec2(TARGET_STARTPOS_X,TARGET_STARTPOS_Y);
		for (int i = 0; i < m_targetMoneyNumbers.size();i++) {
			m_targetMoneyNumbers[i] = (stage->AddGameObject<NumberUI>(Vec2(targetMoneyStartPos.x,targetMoneyStartPos.y), Vec3(30.0f, 30.0f, 1.0f), L"Tex_Number"));
			targetMoneyStartPos.x -= TARGET_INTERVAL;
		}
		//�^�C�}�[�Z�b�g
		Set_Timer(time, m_TimerNumbers);
		Set_Num(targetMoney,m_targetMoneyNumbers);

		//UI�̍쐬
		FlyMaster::GetInstans().Create_GameUI();
		FlyMaster::GetInstans().Create_GameField();
		FlyMaster::GetInstans().Create_PossessionMeat(0);

		//�I�[�o�[���C�p�̃X�v���C�g
		m_overSprite_Oil =  stage->AddGameObject<OverUI>(Vec2(-20, -20), Vec3(190.0f, 330.0f, 1.0f), L"Tex_Oil");
		m_overSprite_Oil->SetDrawActive(false);
	}
	/// ----------------------------------------<summary>
	/// �Q�[���Z�b�g
	/// </summary>----------------------------------------
	void FlyMaster::GAMESET() {
		//�I�����Ă��Ƃ�����X�e�[�^�X��false
		m_gameStatus = false;
		//����~�߂����炻���܂ł̉摜��\���A������X�N���[�������邩
		auto stage = App::GetApp()->GetScene<Scene>()->GetActiveStage();
		stage->AddGameObject<MultiSprite>(true, Vec2(640, 400), Vec3(0, 0, 0), L"Sokomade_TX");
		//�c�莞�Ԃ��i�[���Ă�������U���g�Ō��邩�c
		m_C_min = m_Nowmin;
		m_C_sec = m_Nowsec;
	}
	/// ----------------------------------------<summary>
	/// �Q�[����UI�̍쐬
	/// </summary>----------------------------------------
	void FlyMaster::Create_GameUI() {
		auto stage = App::GetApp()->GetScene<Scene>()->GetActiveStage();
		stage->AddGameObject<MeatUI>(Vec2(0), Vec3(670.0f, 400.0f, 0.0f), L"BG_Kitchen");
		stage->AddGameObject<MeatUI>(Vec2(-20, -17), Vec3(195.0f, 230.0f, 1.0f), L"BG_Flyer");
		stage->AddGameObject<MeatUI>(Vec2(500, 220), Vec3(100.0f, 100.0f, 1.0f), L"Tex_Timer");
		stage->AddGameObject<MeatUI>(Vec2(240, 100), Vec3(30.0f, 30.0f, 1.0f), L"Icon_RegisterMark");

	}
	/// ----------------------------------------<summary>
	/// �݌ɐ��ɒǉ�����B�ǉ�������͐ݒu����Ă��鐔�̓��Z�b�g�����
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
	/// �ݒu�ςݓ��̏�����
	/// </summary>----------------------------------------
	void FlyMaster::Clear_InstallationMeat() {
		auto stage = App::GetApp()->GetScene<Scene>()->GetActiveStage();
		//�X�e�[�W�ɐݒu����Ă���̍폜
		for (int i = 0; i < m_installationMeat.size(); i++) {
			stage->RemoveGameObject<GameObject>(m_installationMeat[i]);
		}
		m_installationMeat.clear();
		//�t�B�[���h�̏�����
		for (int i = 0; i < GAMEFIELD_Y;i++) {
			for (int t = 0; t < GAMEFIELD_X; t++) {
				m_gameField[i][t] = 0;
			}
		}
		m_meatsInstallationData = {};

	}
	/// ----------------------------------------<summary>
	/// �݌ɓ��̏�����
	/// </summary>----------------------------------------
	void FlyMaster::Clear_StockMeat() {
		m_meatsStockData = {};
	}
	/// ----------------------------------------<summary>
	/// �Q�[���t�B�[���h�̍쐬
	/// </summary>----------------------------------------
	void FlyMaster::Create_GameField() {
		//�A�N�e�B�u�X�e�[�W�̎擾
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
	/// �g���鏈��
	/// </summary>----------------------------------------
	void FlyMaster::Fly() {
		m_overSprite_Oil->SetDrawActive(true);
		m_timerForOil = true;
		m_possessionMeat->SetDrawActive(false);
		App::GetApp()->GetScene<Scene>()->MusicOnecStart(L"SE_Fly",1.0f);
	}
	/// ----------------------------------------<summary>
	/// ��v
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
	/// �ڕW���z�ƌ��݋��z�̔�r
	///	�B���Ȃ�TRUE
	/// </summary>----------------------------------------
	bool FlyMaster::Check_Comparison() {
		if (m_targetMoney <= m_nowMoney) {
			MessageBox(0,L"���[�ނ��肠",0,0);
			return true;
		}else {
			return false;
		}

	}
	/// ----------------------------------------<summary>
	/// �n���ꂽ���W����}�b�v�����Ƀ��C���΂��ڐG�����I�u�W�F�N�g�̃}�b�v�ԍ���Ԃ�
	/// </summary>----------------------------------------
	int* FlyMaster::Send_RayCastToMapChip(int *returnNum,Vec3 sendPos) {
		returnNum[0] = 1;
		returnNum[1] = 1;
		return returnNum;
	}
	/// ----------------------------------------<summary>
	/// �������̐���
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
	/// �������̃��Z�b�g
	/// </summary>----------------------------------------
	void FlyMaster::Reset_PossessionMeat(shared_ptr<GameObject> obj){
		auto possessionmeat = FlyMaster::GetInstans().GetPossessionMeat();
		if (possessionmeat) {
			//�܂������̂���폜
			App::GetApp()->GetScene<Scene>()->GetActiveStage()->RemoveGameObject<GameObject>(possessionmeat);
			possessionmeat->DestroyGameObject();
			//��������ݒ�
			FlyMaster::GetInstans().SetPossessionMeat(obj);
		}
		//�����Ȃ��̏ꍇ
		FlyMaster::GetInstans().SetPossessionMeat(obj);
	}
	/// ----------------------------------------<summary>
	/// �������̈ړ�
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
	/// �������̉�]
	/// </summary>----------------------------------------
	void FlyMaster::Rot_PossessionMeat(int angle) {
		m_possessionMeat->Rotation();
		Rot_Array();
	}
	/// ----------------------------------------<summary>
	/// �ړ����L���X�g
	/// </summary>----------------------------------------
	void FlyMaster::Recast_Move() {
		auto pad = App::GetApp()->GetInputDevice().GetControlerVec();
		if (pad[0].fThumbLX < 0.1f && pad[0].fThumbLX > -0.1f &&
			pad[0].fThumbLY < 0.1f && pad[0].fThumbLY > -0.1f) {
			m_isMove = false;
		}
	}
	/// ----------------------------------------<summary>
	/// �������̐؂�ւ�
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
	/// ���������X�e�[�W�ɐݒu����
	/// </summary>----------------------------------------
	void FlyMaster::Set_PossessionMeat() {
		//�܂��͐ݒu���鏊���擾����
		Vec3 SetupPos = m_possessionMeat->GetComponent<Transform>()->GetPosition();
		Quat newMeatRot;
		if (m_possessionMeat) {
			newMeatRot = m_possessionMeat->GetComponent<Transform>()->GetQuaternion();
		}
		//�u���Ȃ��Ƃ��Ȃ�������z�u
		if (Check_SetMeat()) {
			auto stage = App::GetApp()->GetScene<Scene>()->GetActiveStage();
			//�������̈ʒu
			Vec3 possessoionPos = m_possessionMeat->GetComponent<Transform>()->GetPosition();
			shared_ptr<GameObject> newMeat;
			Debug_Map();
			//������ID��
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
				MessageBox(0, L"������ID�̕s��v�ł��B�����Ɏ��s���܂����I", 0, 0);
				break;
			}
		}else {
			MessageBox(0,L"�ݒu�ł��Ȃ���I",0,0);
		}

	}
	/// ----------------------------------------<summary>
	/// �����ݒu�ł��邩�𒲂ׂ�
	/// </summary>----------------------------------------
	bool FlyMaster::Check_SetMeat() {
		//�Q�[���t�B�[���h�ňړ��Əd�����Ă��鏊������
		int SetGridPosition = m_gameField[m_moveDistance[0]][m_moveDistance[1]];
		//�S��(�ړ��Ƃ�������z�������)
		if (SetGridPosition != Setup_FALSE) {
			//�n�_
			auto StartPosX = m_moveDistance[1];
			auto StartPosY = m_moveDistance[0];
			unsigned int Counter = 0;
			//������ID��
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
				//��������ݒu�ς݂ɂ���
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
				//��������ݒu�ς݂ɂ���
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
				//��������ݒu�ς݂ɂ���
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
				//��������ݒu�ς݂ɂ���
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
				//��������ݒu�ς݂ɂ���
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
		////�P��(�ړ��Ō���)
		//if (SetGridPosition != Setup_FALSE) {
		//	//�ݒu���邩�炻�̃}�X��ݒu�s�ɂ���
		//	m_gameField[m_moveDistance[0]][m_moveDistance[1]] = Setup_FALSE;
		//	return true;
		//}
		return false;

	}
	/// ----------------------------------------<summary>
	/// �z���]
	/// </summary>----------------------------------------
	void FlyMaster::Rot_Array() {
		//�ꎞ�u����
		int temp3x3[3][3] = { 0 };
		int temp2x2[3][3] = { 0 };

		//������ID��
		switch (m_possessionMeatID)
		{
		case karaage:
			//��]���Ȃ��̂ŉ������Ȃ�
			break;

		case drum:
			//�ꎞ�u����ɃR�s�[
			for (int i = 0; i < 2; i++) {
				for (int k = 0; k < 2; k++) {
					temp2x2[i][k] = Hit_Drum[i][k];
				}
			}
			//�]�u��s���t�ɂ��ĉE���
			for (int i = 0; i < 2; i++) {
				for (int k = 0; k < 2; k++) {
					Hit_Drum[i][k] = temp2x2[k][2 - i];
				}
			}
			break;

		case keel:
			//�ꎞ�u����ɃR�s�[
			for (int i = 0; i < 3; i++) {
				for (int k = 0; k < 3; k++) {
					temp3x3[i][k] = Hit_Keel[i][k];
				}
			}
			//�]�u��s���t�ɂ��ĉE���
			for (int i = 0; i < 3; i++) {
				for (int k = 0; k < 3; k++) {
					Hit_Keel[i][k] = temp3x3[k][2 - i];
				}
			}
			break;

		case rib:
			//�ꎞ�u����ɃR�s�[
			for (int i = 0; i < 2; i++) {
				for (int k = 0; k < 2; k++) {
					temp2x2[i][k] = Hit_Rib[i][k];
				}
			}
			//�]�u��s���t�ɂ��ĉE���
			for (int i = 0; i < 2; i++) {
				for (int k = 0; k < 2; k++) {
					Hit_Rib[i][k] = temp2x2[k][2 - i];
				}
			}
			break;

		case wing:
			//�ꎞ�u����ɃR�s�[
			for (int i = 0; i < 2; i++) {
				for (int k = 0; k < 2; k++) {
					temp2x2[i][k] = Hit_Wing[i][k];
				}
			}
			//�]�u��s���t�ɂ��ĉE���
			for (int i = 0; i < 2; i++) {
				for (int k = 0; k < 2; k++) {
					Hit_Wing[i][k] = temp2x2[k][2 - i];
				}
			}
			break;
		default:
			MessageBox(0,L"�s���ȓ�ID������܂���(���̉�])",0,0);
			break;
		}
	}
	/// ----------------------------------------<summary>
	/// �X�v���C�g�ɕ\�����邽�߂Ɋe���𕪉�
	/// </summary>----------------------------------------
	void FlyMaster::Set_Num(int num,vector<shared_ptr<GameObject>> changennumobj) {
		//�ő�6�����ȁc(100,000)
		//�ꌅ������Ċi�[
		for (int i = 0; i < changennumobj.size();i++) {
			m_NowNumber[i] = (num % 10); num /= 10;//1
		}
		Update_num(changennumobj);
	}
	/// ----------------------------------------<summary>
	/// �X�v���C�g�̐����ύX
	/// </summary>----------------------------------------
	void FlyMaster::Update_num(vector<shared_ptr<GameObject>> objs) {
		for (int i = 0; i < objs.size(); i++) {
			Set_Rect(m_NowNumber[i], objs[i]);
		}
	}
	/// ----------------------------------------<summary>
	/// �X�v���C�g��Rect�ύX
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
	///	�^�C�}�[�̐ݒ�
	/// </summary>----------------------------------------
	void FlyMaster::Set_Timer(int time, vector<shared_ptr<GameObject>> changenumobj) {
		//�������ݒ�c
		if (time != 999) {
			m_Nowmin = time;
			m_time = 59;
		}
		m_NowTime[3] = m_Nowmin;
		m_NowTime[1] = (m_Nowsec % 10); m_Nowsec /= 10;
		m_NowTime[2] = (m_Nowsec % 10); m_Nowsec /= 10;
		if (m_Nowmin == 0 && m_time <= 1) {
			//�^�C�}�[���S�I���
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
	///	�^�C�}�[�̍X�V
	/// </summary>----------------------------------------
	void FlyMaster::Update_Timer() {
		auto deltatime = App::GetApp()->GetElapsedTime();
		m_time -=  1 * deltatime;

		m_Nowsec = m_time;
		Set_Timer(999,m_TimerNumbers);
	}
	/// ----------------------------------------<summary>
	///	�t���C���[�^�C�}�[
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
	///	�q�̑����Ǘ�
	/// </summary>----------------------------------------
	void FlyMaster::Master_Customers() {
		Customers_Count();
	}
	/// ----------------------------------------<summary>
	///	�q�̐l���Ǘ�
	/// </summary>----------------------------------------
	void FlyMaster::Customers_Count() {
		//�ő吔�ȉ��̏ꍇ�󂫂ɒǉ�
		if (m_nowCustomers < MAX_CUSTOMERS) {
			auto stage = App::GetApp()->GetScene<Scene>()->GetActiveStage();
			for (int i = 0; i < MAX_CUSTOMERS; i++)
			{
				//�q�����Ȃ����ɒǉ�
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
	///	�q�̗v���𖞂������̊Ǘ�
	/// </summary>----------------------------------------
	void FlyMaster::Customers_Request() {
		//�q�̖ړI���z�Ȃ̂Łc�R���t�B�O�ɐݒ���z���w�肵�Ă���Ŕ�r���邩
		switch (m_stageNumber)
		{
		case 1:
			if (m_nowMoney >= STAGE_MONEY_1) {
				//���ā[��1���肠�I
				m_cleared = true;
			}
			break;
		case 2:
			if (m_nowMoney >= STAGE_MONEY_2) {
				//���ā[��2���肠�I
				m_cleared = true;
			}
			break;
		case 3:
			if (m_nowMoney >= STAGE_MONEY_3) {
				//���ā[��3���肠�I
				m_cleared = true;
			}
			break;
		case 4:
			if (m_nowMoney >= STAGE_MONEY_4) {
				//���ā[��4���肠�I
				m_cleared = true;
			}
			break;
		case 5:
			if (m_nowMoney >= STAGE_MONEY_5) {
				//���ā[��5���肠�I
				m_cleared = true;
			}
			break;
		default:
			break;
		}
	}
	/// ----------------------------------------<summary>
	///	MAP�̏�ԕ\���̃f�o�b�N
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