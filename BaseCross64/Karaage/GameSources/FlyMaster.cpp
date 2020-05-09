#include "stdafx.h"
#include "Project.h"

namespace basecross {
	/// ----------------------------------------<summary>
	/// �݌ɐ��ɒǉ�����B�ǉ�������͐ݒu����Ă��鐔�̓��Z�b�g�����
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
	/// �ݒu�ςݓ��̏�����
	/// </summary>----------------------------------------
	void FlyMaster::Clear_InstallationMeat() {
		m_meatsInstallationData.Meat_1x1 = 0;
		m_meatsInstallationData.Meat_1x2 = 0;
		m_meatsInstallationData.Meat_2x2 = 0;
		m_meatsInstallationData.Meat_3x3 = 0;
		m_meatsInstallationData.Meat_L = 0;
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
				stage->AddGameObject<Keel>(Vec3(1, 0, 1), Vec3(possessoionPos.x - 30, possessoionPos.y + 30, 0), Vec3(1));
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
				break;
			case �L�[��:
				break;
			case ���u:
				break;
			case �E�B���O:
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
}
//end basecross