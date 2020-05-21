#include "stdafx.h"
#include "Project.h"

namespace basecross {
	/// ----------------------------------------<summary>
	/// �Q�[���X�^�[�g�̎��̊֐�
	/// ������N���ŃQ�[�����n�܂�
	/// </summary>----------------------------------------
	void FlyMaster::GAMESTART(int TargetMoney) {
		//�ڕW���z�̐ݒ�
		m_targetMoney = TargetMoney;
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
		m_Numbers[5] = (stage->AddGameObject<NumberUI>(Vec2(-520, 150), Vec3(30.0f, 30.0f, 1.0f), L"Tex_Number"));
		m_Numbers[4] = (stage->AddGameObject<NumberUI>(Vec2(-420, 150), Vec3(30.0f, 30.0f, 1.0f), L"Tex_Number"));
		m_Numbers[3] = (stage->AddGameObject<NumberUI>(Vec2(-470, 150), Vec3(30.0f, 30.0f, 1.0f), L"Tex_Number"));
		m_Numbers[2] = (stage->AddGameObject<NumberUI>(Vec2(-370, 150), Vec3(30.0f, 30.0f, 1.0f), L"Tex_Number"));
		m_Numbers[1] = (stage->AddGameObject<NumberUI>(Vec2(-320, 150), Vec3(30.0f, 30.0f, 1.0f), L"Tex_Number"));
		m_Numbers[0] = (stage->AddGameObject<NumberUI>(Vec2(-270, 150), Vec3(30.0f, 30.0f, 1.0f), L"Tex_Number"));

	}
	/// ----------------------------------------<summary>
	/// �Q�[����UI�̍쐬
	/// </summary>----------------------------------------
	void FlyMaster::Create_GameUI() {
		auto stage = App::GetApp()->GetScene<Scene>()->GetActiveStage();
		stage->AddGameObject<MeatUI>(Vec2(0), Vec3(670.0f, 400.0f, 0.0f), L"BG_Kitchen");
		stage->AddGameObject<MeatUI>(Vec2(-20, -17), Vec3(195.0f, 230.0f, 1.0f), L"BG_Flyer");
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
		Sales(m_meatsInstallationData);
		Clear_InstallationMeat();
	}

	/// ----------------------------------------<summary>
	/// �ݒu�ςݓ��̏�����
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
	/// �݌ɓ��̏�����
	/// </summary>----------------------------------------
	void FlyMaster::Clear_StockMeat() {
		m_meatsStockData.Karage = 0;
		m_meatsStockData.Drum = 0;
		m_meatsStockData.Wing = 0;
		m_meatsStockData.Lib = 0;
		m_meatsStockData.Keel = 0;
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
		Add_StockMeat();
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
		Set_Num(m_nowMoney);
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
		case ���g��:
			newMeat = stage->AddGameObject<Karaage>(Vec3(1, 0, 1), Vec3(MAPCHIP_START_X, MAPCHIP_START_Y, 6), quat);
			Reset_PossessionMeat(newMeat);
			break;
		case �h����:
			newMeat = stage->AddGameObject<Drum>(Vec3(1, 0, 1), Vec3(MAPCHIP_START_X, MAPCHIP_START_Y, 6), quat);
			Reset_PossessionMeat(newMeat);
			break;
		case �L�[��:
			newMeat = stage->AddGameObject<Keel>(Vec3(1, 0, 1), Vec3(MAPCHIP_START_X, MAPCHIP_START_Y, 6), quat);
			Reset_PossessionMeat(newMeat);
			break;
		case ���u:
			newMeat = stage->AddGameObject<Rib>(Vec3(1, 0, 1), Vec3(MAPCHIP_START_X, MAPCHIP_START_Y, 6), quat);
			Reset_PossessionMeat(newMeat);
			break;
		case �E�B���O:
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
	/// �������̉�]
	/// </summary>----------------------------------------
	void FlyMaster::Rot_PossessionMeat(int angle) {
		m_possessionMeat->Rotation();
		Rot_Array();
	}

	/// ----------------------------------------<summary>
	/// ���L���X�g�^�C�}�[
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
			//������ID��
			switch (m_possessionMeatID)
			{
			case ���g��:
				newMeat = stage->AddGameObject<Karaage>(Vec3(1, 0, 1), Vec3(possessoionPos.x, possessoionPos.y, 0), newMeatRot);
				m_installationMeat.push_back(newMeat);
				m_meatsInstallationData.Karage++;
				break;
			case �h����:
				stage->AddGameObject<Drum>(Vec3(1, 0, 1), Vec3(possessoionPos.x - 30, possessoionPos.y + 30, 0), newMeatRot);
				break;
			case �L�[��:
				stage->AddGameObject<Keel>(Vec3(1, 0, 1), Vec3(possessoionPos.x - 60, possessoionPos.y + 60, 0), newMeatRot);
				break;
			case ���u:
				stage->AddGameObject<Rib>(Vec3(1, 0, 1), Vec3(possessoionPos.x - 40, possessoionPos.y + 40, 0), newMeatRot);
				break;
			case �E�B���O:
				stage->AddGameObject<Wing>(Vec3(1, 0, 1), Vec3(possessoionPos.x - 30, possessoionPos.y + 30, 0), newMeatRot);
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

			//������ID��
			switch (m_possessionMeatID)
			{
			case ���g��:
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
			case �h����:
				for (int y = 0; y < 3; y++) {
					for (int x = 0; x < 3; x++) {
						if (m_gameField[StartPosY + y][StartPosX + x] == Hit_Drum[y][x]) {
							return false;
							break;
						}
					}
				}
				//��������ݒu�ς݂ɂ���
				for (int y = 0; y < 3; y++) {
					for (int x = 0; x < 3; x++) {
						if (m_gameField[StartPosY + y][StartPosX + x] == 0 && Hit_Drum[y][x] == 9) {
							m_gameField[StartPosY + y][StartPosX + x] = 9;
						}
					}
				}
				return true;
				break;
			case �L�[��:
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
						}
					}
				}
				return true;
				break;
			case ���u:
				for (int y = 0; y < 3; y++) {
					for (int x = 0; x < 3; x++) {
						if (m_gameField[StartPosY + y][StartPosX + x] == Hit_Rib[y][x]) {
							return false;
							break;
						}
					}
				}
				//��������ݒu�ς݂ɂ���
				for (int y = 0; y < 3; y++) {
					for (int x = 0; x < 3; x++) {
						if (m_gameField[StartPosY + y][StartPosX + x] == 0 && Hit_Rib[y][x] == 9) {
							m_gameField[StartPosY + y][StartPosX + x] = 9;
						}
					}
				}
				return true;
				break;
			case �E�B���O:
				for (int y = 0; y < 3; y++) {
					for (int x = 0; x < 3; x++) {
						if (m_gameField[StartPosY + y][StartPosX + x] == Hit_Wing[y][x]) {
							return false;
							break;
						}
					}
				}
				//��������ݒu�ς݂ɂ���
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
		int temp[3][3] = { 0 };

		//������ID��
		switch (m_possessionMeatID)
		{
		case ���g��:
			//��]���Ȃ��̂ŉ������Ȃ�
			break;
		case �h����:
			//�ꎞ�u����ɃR�s�[
			for (int i = 0; i < 3; i++) {
				for (int k = 0; k < 3; k++) {
					temp[i][k] = Hit_Drum[i][k];
				}
			}
			//�]�u��s���t�ɂ��ĉE���
			for (int i = 0; i < 3; i++) {
				for (int k = 0; k < 3; k++) {
					Hit_Drum[i][k] = temp[k][2 - i];
				}
			}
			break;
		case �L�[��:
			//�ꎞ�u����ɃR�s�[
			for (int i = 0; i < 3; i++) {
				for (int k = 0; k < 3; k++) {
					temp[i][k] = Hit_Keel[i][k];
				}
			}
			//�]�u��s���t�ɂ��ĉE���
			for (int i = 0; i < 3; i++) {
				for (int k = 0; k < 3; k++) {
					Hit_Keel[i][k] = temp[k][2 - i];
				}
			}
			break;
		case ���u:
			//�ꎞ�u����ɃR�s�[
			for (int i = 0; i < 3; i++) {
				for (int k = 0; k < 3; k++) {
					temp[i][k] = Hit_Rib[i][k];
				}
			}
			//�]�u��s���t�ɂ��ĉE���
			for (int i = 0; i < 3; i++) {
				for (int k = 0; k < 3; k++) {
					Hit_Rib[i][k] = temp[k][2 - i];
				}
			}
			break;
		case �E�B���O:
			//�ꎞ�u����ɃR�s�[
			for (int i = 0; i < 3; i++) {
				for (int k = 0; k < 3; k++) {
					temp[i][k] = Hit_Wing[i][k];
				}
			}
			//�]�u��s���t�ɂ��ĉE���
			for (int i = 0; i < 3; i++) {
				for (int k = 0; k < 3; k++) {
					Hit_Wing[i][k] = temp[k][2 - i];
				}
			}
			break;
		default:
			MessageBox(0,L"�s���ȓ�ID������܂���(���̉�])",0,0);
			break;
		}
	}


	void FlyMaster::Set_Num(int num) {
		//�ő�6�����ȁc(100,000)
		//�ꌅ������Ċi�[
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