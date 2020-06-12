#include "stdafx.h"
#include "Project.h"

namespace basecross {
	/// ----------------------------------------<summary>
<<<<<<< HEAD
	/// �݌ɐ��ɒǉ�����B�ǉ�������͐ݒu����Ă��鐔�̓��Z�b�g�����
	/// </summary>----------------------------------------
	void FlyMaster::Add_StockMeat() {
		m_meatsStockData.Meat_1x1 += m_meatsInstallationData.Meat_1x1;
		m_meatsStockData.Meat_1x2 += m_meatsInstallationData.Meat_1x2;
		m_meatsStockData.Meat_2x2 += m_meatsInstallationData.Meat_2x2;
		m_meatsStockData.Meat_3x3 += m_meatsInstallationData.Meat_3x3;
		m_meatsStockData.Meat_L += m_meatsInstallationData.Meat_L;

=======
	/// �Q�[���X�^�[�g�̎��̊֐�
	/// ������N���ŃQ�[�����n�܂�
	/// </summary>----------------------------------------
	void FlyMaster::GAMESTART(int targetMoney,int time) {
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
		m_Numbers[0] = (stage->AddGameObject<NumberUI>(Vec2(550, 100), Vec3(30.0f, 30.0f, 1.0f), L"Tex_Number"));
		m_Numbers[1] = (stage->AddGameObject<NumberUI>(Vec2(500, 100), Vec3(30.0f, 30.0f, 1.0f), L"Tex_Number"));
		m_Numbers[2] = (stage->AddGameObject<NumberUI>(Vec2(450, 100), Vec3(30.0f, 30.0f, 1.0f), L"Tex_Number"));
		m_Numbers[3] = (stage->AddGameObject<NumberUI>(Vec2(400, 100), Vec3(30.0f, 30.0f, 1.0f), L"Tex_Number"));
		m_Numbers[4] = (stage->AddGameObject<NumberUI>(Vec2(350, 100), Vec3(30.0f, 30.0f, 1.0f), L"Tex_Number"));
		m_Numbers[5] = (stage->AddGameObject<NumberUI>(Vec2(300, 100), Vec3(30.0f, 30.0f, 1.0f), L"Tex_Number"));
		//�^�C�}�[�p����
		m_TimerNumbers[1] = (stage->AddGameObject<NumberUI>(Vec2(540, 220), Vec3(20.0f, 20.0f, 1.0f), L"Tex_Number"));
		m_TimerNumbers[2] = (stage->AddGameObject<NumberUI>(Vec2(510, 220), Vec3(20.0f, 20.0f, 1.0f), L"Tex_Number"));
		m_TimerNumbers[3] = (stage->AddGameObject<NumberUI>(Vec2(480, 220), Vec3(20.0f, 20.0f, 1.0f), L"Tex_Number"));
		m_TimerNumbers[4] = (stage->AddGameObject<NumberUI>(Vec2(450, 220), Vec3(20.0f, 20.0f, 1.0f), L"Tex_Number"));
		//�ڕW���z����
		m_targetMoneyNumbers[0] = (stage->AddGameObject<NumberUI>(Vec2(550, 30), Vec3(30.0f, 30.0f, 1.0f), L"Tex_Number"));
		m_targetMoneyNumbers[1] = (stage->AddGameObject<NumberUI>(Vec2(500, 30), Vec3(30.0f, 30.0f, 1.0f), L"Tex_Number"));
		m_targetMoneyNumbers[2] = (stage->AddGameObject<NumberUI>(Vec2(450, 30), Vec3(30.0f, 30.0f, 1.0f), L"Tex_Number"));
		m_targetMoneyNumbers[3] = (stage->AddGameObject<NumberUI>(Vec2(400, 30), Vec3(30.0f, 30.0f, 1.0f), L"Tex_Number"));
		m_targetMoneyNumbers[4] = (stage->AddGameObject<NumberUI>(Vec2(350, 30), Vec3(30.0f, 30.0f, 1.0f), L"Tex_Number"));
		m_targetMoneyNumbers[5] = (stage->AddGameObject<NumberUI>(Vec2(300, 30), Vec3(30.0f, 30.0f, 1.0f), L"Tex_Number"));
		
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
>>>>>>> Morota_ForHome
		Clear_InstallationMeat();
	}

	/// ----------------------------------------<summary>
	/// �ݒu�ςݓ��̏�����
	/// </summary>----------------------------------------
	void FlyMaster::Clear_InstallationMeat() {
<<<<<<< HEAD
		m_meatsInstallationData.Meat_1x1 = 0;
		m_meatsInstallationData.Meat_1x2 = 0;
		m_meatsInstallationData.Meat_2x2 = 0;
		m_meatsInstallationData.Meat_3x3 = 0;
		m_meatsInstallationData.Meat_L = 0;
=======
		auto stage = App::GetApp()->GetScene<Scene>()->GetActiveStage();
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
		m_meatsInstallationData.Karage = 0;
		m_meatsInstallationData.Drum = 0;
		m_meatsInstallationData.Wing = 0;
		m_meatsInstallationData.Lib = 0;
		m_meatsInstallationData.Keel = 0;

>>>>>>> Morota_ForHome
	}

	/// ----------------------------------------<summary>
	/// �݌ɓ��̏�����
	/// </summary>----------------------------------------
	void FlyMaster::Clear_StockMeat() {
		m_meatsStockData.Meat_1x1 = 0;
		m_meatsStockData.Meat_1x2 = 0;
		m_meatsStockData.Meat_2x2 = 0;
		m_meatsStockData.Meat_3x3 = 0;
		m_meatsStockData.Meat_L = 0;
	}

	/// ----------------------------------------<summary>
	/// �Q�[���t�B�[���h�̍쐬
	/// </summary>----------------------------------------
	void FlyMaster::Create_GameField() {
		//�A�N�e�B�u�X�e�[�W�̎擾
		auto stage = App::GetApp()->GetScene<Scene>()->GetActiveStage();
		//-----�ȉ��e�X�g�t�B�[���h�̍쐬�Ȃ̂Ō�قǍ폜�\��------//
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
	/// �g���鏈��
	/// </summary>----------------------------------------
	void FlyMaster::Fly() {

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
		m_possessionMeatID = createMeatID;
		switch (createMeatID)
		{
		case ���g��:
			newMeat = stage->AddGameObject<Karaage>(Vec3(1, 0, 1), Vec3(MAPCHIP_START_X, MAPCHIP_START_Y, 6), Vec3(0));
			Reset_PossessionMeat(newMeat);
			break;
		case �h����:
			newMeat = stage->AddGameObject<Drum>(Vec3(1, 0, 1), Vec3(MAPCHIP_START_X, MAPCHIP_START_Y, 6), Vec3(0));
			Reset_PossessionMeat(newMeat);
			break;
		case �L�[��:
			newMeat = stage->AddGameObject<Keel>(Vec3(1, 0, 1), Vec3(MAPCHIP_START_X, MAPCHIP_START_Y, 6), Vec3(0));
			Reset_PossessionMeat(newMeat);
			break;
		case ���u:
			newMeat = stage->AddGameObject<Rib>(Vec3(1, 0, 1), Vec3(MAPCHIP_START_X, MAPCHIP_START_Y, 6), Vec3(0));
			Reset_PossessionMeat(newMeat);
			break;
		case �E�B���O:
			newMeat = stage->AddGameObject<Wing>(Vec3(1, 0, 1), Vec3(MAPCHIP_START_X, MAPCHIP_START_Y, 6), Vec3(0));
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
			if (m_possessionMeatID > MAX_MEATCOUNT) {
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
		//���ɉ�]�p�x���Ă�������]�����񂵂Ă��Ă̂�ۑ����āA����݂Ď����̔���f�[�^��
		//�ƍ����Ă��邩�Ȃ������邩
		

		
		//�܂��͐ݒu���鏊���擾����
		Vec3 SetupPos = m_possessionMeat->GetComponent<Transform>()->GetPosition();
		//�u���Ȃ��Ƃ��Ȃ�������z�u
		if (Check_SetMeat()) {
			//�ݒu���Ă݂�(�e�X�g��)
			auto stage = App::GetApp()->GetScene<Scene>()->GetActiveStage();
			//�������̈ʒu
			Vec3 possessoionPos = m_possessionMeat->GetComponent<Transform>()->GetPosition();
			//������ID��
			switch (m_possessionMeatID)
			{
			case ���g��:
				stage->AddGameObject<Karaage>(Vec3(1, 0, 1), Vec3(possessoionPos.x, possessoionPos.y, 0), Vec3(1));
				break;
			case �h����:
				stage->AddGameObject<Drum>(Vec3(1, 0, 1), Vec3(possessoionPos.x - 30, possessoionPos.y + 30, 0), Vec3(1));
				break;
			case �L�[��:
				stage->AddGameObject<Keel>(Vec3(1, 0, 1), Vec3(possessoionPos.x - 60, possessoionPos.y + 60, 0), Vec3(1));
				break;
			case ���u:
				stage->AddGameObject<Rib>(Vec3(1, 0, 1), Vec3(possessoionPos.x - 40, possessoionPos.y + 40, 0), Vec3(1));
				break;
			case �E�B���O:
				stage->AddGameObject<Wing>(Vec3(1, 0, 1), Vec3(possessoionPos.x - 30, possessoionPos.y + 30, 0), Vec3(1));
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
<<<<<<< HEAD
=======
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
	/// ----------------------------------------<summary>
	///	�^�C�}�[�̐ݒ�
	/// </summary>----------------------------------------
	void FlyMaster::Set_Timer(int time, vector<shared_ptr<GameObject>> changenumobj) {
		m_time = (float)time;
		m_NowTime[0] = (time % 10); time /= 10;
		m_NowTime[1] = (time % 10); time /= 10;
		m_NowTime[2] = (time % 10); time /= 10;
		m_NowTime[3] = (time % 10); time /= 10;

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
		Set_Timer(m_time,m_TimerNumbers);
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
							m_guests[0] = stage->AddGameObject<Guest>(Vec3(-430, 50, 0));
						}
				}
			}
		}
	}
	/// ----------------------------------------<summary>
	///	�q�̗v���𖞂������̊Ǘ�
	/// </summary>----------------------------------------
	void FlyMaster::Customers_Request() {
		//�v�����ƍ݌ɐ��̌����
		//�v�����i�[�p
		int tempReqMeats[5] = { 0 };
		for (int i = 0; i < MAX_CUSTOMERS;i++) {
			//�܂��q�̗v����������Ă���
			m_guests[i]->GetRequestMeats(tempReqMeats);
			//�����ƂɊm�F
			if (tempReqMeats[0] <= m_meatsStockData.Karage) {
				if (tempReqMeats[1] <= m_meatsStockData.Drum) {
					if (tempReqMeats[2] <= m_meatsStockData.Wing) {
						if (tempReqMeats[3] <= m_meatsStockData.Lib) {
							if (tempReqMeats[4] <= m_meatsStockData.Keel) {
								//�����܂ŗ�����S���v���������Ă邩����z���v�Z���Ĕ���ɉ��Z���ĂƁc
								Sales(m_meatsInstallationData);

							}
						}
					}
				}
			}
		}
	}
	/*
	��
	��
	��
	��
	��
	�S
	��
	��
	r
	*/
>>>>>>> Morota_ForHome
}
//end basecross