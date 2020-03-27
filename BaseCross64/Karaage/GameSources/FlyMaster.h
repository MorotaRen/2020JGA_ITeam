#pragma once
/// ----------------------------------------<summary>
/// �g�����Ɋւ��Ă̊֐����܂Ƃ܂��Ă���Ƃ���
/// �ǂ�����ł��Ăяo����
/// ���F�V���O���g��
/// �Ǘ��ҁF���c
/// </summary>----------------------------------------

#include "stdafx.h"
//�Q�[���t�B�[���h�̏c��
#define GAMEFIELD_X 5
#define GAMEFIELD_Y 10
//�g������̃��L���X�g����
#define FLY_RECAST_TIME 20
//�}�b�v�`�b�v�̃T�C�Y
#define MAPCHIP_SIZE_X 70.0f
#define MAPCHIP_SIZE_Y 70.0f
//�}�b�v�`�b�v�̊J�n�n�_
#define MAPCHIP_START_X -100.0f
#define MAPCHIP_START_Y 300.0f
//���E
#define LEFT 4
#define RIGHT 6
#define UP 8
#define DOWN 2
//�f�t�H���g�ŉ������Ă���̎�ސ�
#define DEFAULT_RELEASE_MEATS 3
//���̎�ނ̍ő�l
#define MAX_MEATCOUNT 5

namespace basecross {
	//�e����̌����
	struct MeatsData
	{
		unsigned int Meat_1x1;
		unsigned int Meat_1x2;
		unsigned int Meat_2x2;
		unsigned int Meat_3x3;
		unsigned int Meat_L;
	};

	class FlyMaster	final{
	private:
		//�R���X�g���N�^
		FlyMaster() {};
		//�f�X�g���N�^
		~FlyMaster() {};
		//�V���O���g���p�R���X�g���N�^
		FlyMaster(const FlyMaster&);

		//-------------------�ϐ�-----------------//

		//�e����̍݌�
		MeatsData m_meatsStockData;
		//���ݒu����Ă�e���
		MeatsData m_meatsInstallationData;
		//�t�B�[���h�\����
		int m_gameField[GAMEFIELD_X][GAMEFIELD_Y] = {0};
		//�ڐG�}�b�v�`�b�v�ԍ�
		int *m_hittingMapChipNum[2];
		//�������̓�
		shared_ptr<GameObject> m_possessionMeat;
		//�e�X�g�p�̐��l
		bool m_TEST_w;
		//���݉�����̓���
		int m_releaseMeatCount = DEFAULT_RELEASE_MEATS;
		//���݂̏�������ID
		int m_possessionMeatID;
		//�ړ��̃��L���X�g���ς�ł邩
		bool m_isMove;
		//----------------------------------------//

	public:
		//�֐��ĂԂƂ��ɍŏ��ɌĂяo��
		static FlyMaster& GetInstans() {
			static FlyMaster inst;
			return inst;
		}
		//�݌ɂ̒ǉ�
		void Add_StockMeat();
		//�ݒu�ςݓ����̏�����
		void Clear_InstallationMeat();
		//�݌ɂ̃��Z�b�g
		void Clear_StockMeat();
		//�t�B�[���h�̐���
		void Create_GameField();
		//�g����
		void Fly();
		//�n���ꂽ���W����}�b�v�����Ƀ��C���΂��ڐG�����I�u�W�F�N�g�̃}�b�v�ԍ���Ԃ�
		int* Send_RayCastToMapChip(int *returnNum,Vec3 sendPos);
		//�������̃��Z�b�g
		void Reset_PossessionMeat(shared_ptr<GameObject> obj);
		//�������̐���
		void Create_PossessionMeat(int createMeatID);
		//�������̈ړ�
		void Move_PossessionMeat(int direction);
		//���L���X�g�^�C�}�[
		void Recast_Move();
		//�������̐؂�ւ�
		void Change_PossessionMeat();
		//------------�Q�b�^�[�Z�b�^�[--------------//
		void SetStockData(const MeatsData md) {
			m_meatsStockData = md;
		}
		MeatsData GetStockData() {
			return m_meatsStockData;
		}
		void SetMeatsInstallationData(const MeatsData md) {
			m_meatsInstallationData = md;
		}
		MeatsData GetMeatsInstallationData() {
			return m_meatsInstallationData;
		}
		void SetPossessionMeat(shared_ptr<GameObject> obj) {
			m_possessionMeat = obj;
		}
		shared_ptr<GameObject> GetPossessionMeat() {
			return m_possessionMeat;
		}
		//----------------------------------------//

	};
}