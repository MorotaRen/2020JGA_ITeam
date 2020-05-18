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
#define MAPCHIP_SIZE_X 60.0f
#define MAPCHIP_SIZE_Y 60.0f
//�}�b�v�`�b�v�̊J�n�n�_
#define MAPCHIP_START_X -140.0f
#define MAPCHIP_START_Y 250.0f
//���E
#define LEFT	4
#define RIGHT	6
#define UP		8
#define DOWN	2
//�f�t�H���g�ŉ������Ă���̎�ސ�
#define DEFAULT_RELEASE_MEATS 3
//���̎�ނ̍ő�l
#define MAX_MEATCOUNT 5
//�ړ����~�b�g
#define MOVELIMIT_MIN_X -140
#define MOVELIMIT_MIN_Y -270
#define MOVELIMIT_MAX_X  60
#define MOVELIMIT_MAX_Y  250
//�z�u�󋵂̐��l
#define Setup_FALSE 9
//�e����̋��z
#define PRICE_KARAAGE	70; //���g��
#define PRICE_DRUM		100;   //�r
#define PRICE_WING		130;   //��H��
#define PRICE_LIB		150;    //���΂�
#define PRICE_KEEL		200;   //��
//�e����̃I�[�_�[�ő吔
#define LIMIT_ORDER_KARAAGE	5;
#define LIMIT_ORDER_DRUM	5;
#define LIMIT_ORDER_WING	5;
#define LIMIT_ORDER_LIB		5;
#define LIMIT_ORDER_KEEL	5;
namespace basecross {
	//�e����̌����
	struct MeatsData
	{
		unsigned int Karage;
		unsigned int Drum;
		unsigned int Wing;
		unsigned int Lib;
		unsigned int Keel;
	};
	//����ID
	enum MeatID
	{
		���g��,�h����,�L�[��,���u,�E�B���O
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
		int m_gameField[GAMEFIELD_Y][GAMEFIELD_X] = {0};
		//�ڐG�}�b�v�`�b�v�ԍ�
		int *m_hittingMapChipNum[2];
		//�������̓�
		shared_ptr<GameObject> m_possessionMeat;
		//�ݒu�������B
		vector<shared_ptr<GameObject>> m_installationMeat;
		//�e�X�g�p�̐��l
		bool m_TEST_w;
		//���݉�����̓���
		int m_releaseMeatCount = DEFAULT_RELEASE_MEATS;
		//���݂̏�������ID
		int m_possessionMeatID = 0;
		//�ړ��̃��L���X�g���ς�ł邩
		bool m_isMove;
		//���̈ړ����Ă��鋗��(0=x 1=y)
		int m_moveDistance[2]= { 0 };
		//�������̉�]���l
		int m_RotationNum = 0;
		//�ڕW���z
		int m_targetMoney = 0;
		//���݋��z
		int m_nowMoney = 0;
		//------------���̊e�픻��------------//
		int Hit_Karaage[3][3] = {
								{9,1,1},
								{1,1,1},
								{1,1,1}
		};
		int Hit_Drum[3][3] = {
								{9,1,1},
								{9,1,1},
								{1,1,1}
		};
		int Hit_Wing[3][3] = {
								{9,9,1},
								{9,1,1},
								{1,1,1}
		};
		int Hit_Rib[3][3] = {
								{9,9,1},
								{9,9,1},
								{1,1,1}
		};
		int Hit_Keel[3][3] = {
								{9,9,9},
								{9,9,9},
								{1,9,1}
		};
		//------------------------------------//
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
		//���̐ݒu
		void Set_PossessionMeat();
		//�����ݒu�ł��邩���ׂ�
		bool Check_SetMeat();
		//�������̉�]
		void Rot_PossessionMeat(int angle);
		//����v�Z
		void Sales(MeatsData md);
		//�z��̉�]
		void Rot_Array();
		//�Q�[�����n�߂鎞
		void GAMESTART(int TargetMoney);
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