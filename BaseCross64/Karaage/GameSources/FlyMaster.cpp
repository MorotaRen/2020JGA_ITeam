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
		for (int y = 0; y < GAMEFIELD_Y;y++) {
			for (int x = 0; x < GAMEFIELD_X;x++) {
				//�}�b�v�`�b�v�����ڂŔz�u����
				//����1�}�X���̓����蔻���ǉ����Ă������烌�C�L���X���đI������Ă�I�u�W�F�N�g��
				//�X�e�[�W�̃}�X�ڂ��r���ē������Ă�Ƃ����1�ɂ���c�H
				//�܂�}�b�v�`�b�v�ɂ̓}�b�v�ԍ��Ɛݒu�ς݂̃t���O�����������
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
	void FlyMaster::Create_PossessionMeat() {

	}

	/// ----------------------------------------<summary>
	/// �������̃��Z�b�g
	/// </summary>----------------------------------------
	void Create_PossessionMeat(shared_ptr<GameObject> obj){
		//���ɏ������Ă����炻��ƌ���
		auto possessionmeat = FlyMaster::GetInstans().GetPossessionMeat();
		if (possessionmeat) {
			//�܂������̂���폜
			possessionmeat->DestroyGameObject();
			//��������ݒ�
			FlyMaster::GetInstans().SetPossessionMeat(obj);
		}
		//�����Ȃ��̏ꍇ
		FlyMaster::GetInstans().SetPossessionMeat(obj);
	}

}
//end basecross