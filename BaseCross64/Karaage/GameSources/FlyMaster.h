#pragma once
/// ----------------------------------------<summary>
/// �g�����Ɋւ��Ă̊֐����܂Ƃ܂��Ă���Ƃ���
/// �ǂ�����ł��Ăяo����
/// ���F�V���O���g��
/// �Ǘ��ҁF���c
/// </summary>----------------------------------------

#include "stdafx.h"
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
		karaage,drum,keel,rib,wing
	};

	class FlyMaster	final{
	private:
		//�R���X�g���N�^
		FlyMaster() {};
		//�f�X�g���N�^
		~FlyMaster() {};
		//�V���O���g���p�R���X�g���N�^
		FlyMaster(const FlyMaster&);

		//-------------------�ϐ�------------------//

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
		//���ݎ���
		float m_time = 0;
		//�t���C���[�^�C�}�[�̌��ݎ���
		float m_flyTime = FLY_RECAST_TIME;
		//���݋��z�����̃|�C���^
		vector<shared_ptr<GameObject>> m_Numbers = {0,0,0,0,0,0};
		//�ڕW���z�����̃|�C���^
		vector<shared_ptr<GameObject>> m_targetMoneyNumbers = {0,0,0,0,0,0};
		//�^�C�}�[�p����
		vector<shared_ptr<GameObject>> m_TimerNumbers = {0,0,0,0,0};
		//�K�p���鐔���𕪉���������
		int m_NowNumber[6];
		//�^�C�}�[�p�̓K�p�����𕪉���������
		int m_NowTime[4];
		//�i���o�[��UV���W�B
		vector<Rect2D<float>> m_numRects = vector<Rect2D<float>>(10);
		//�^�C�}�[�I�����̔���(��)
		bool m_timerForOil;
		//�^�C�}�[�I�����̔���(Game)
		bool m_timerForGame;
		//�I�[�o�[���C�p�̃X�v���C�g�|�C���^
		shared_ptr<GameObject> m_overSprite_Oil;	
		//���q�B
		vector<shared_ptr<Guest>> m_guests = {0,0,0};
		//���q�̐�
		int m_nowCustomers = 0;
		//------------���̊e�픻��------------//
		int Hit_Karaage[3][3] = {
								{9,1,1},
								{1,1,1},
								{1,1,1}
		};
		int Hit_Drum[2][2] = {
								{9,1},
								{9,1},
		};
		int Hit_Wing[2][2] = {
								{9,9},
								{9,1},
		};
		int Hit_Rib[2][2] = {
								{9,9},
								{9,9},
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
		//UI�̍쐬
		void Create_GameUI();
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
		//�ړ����L���X�g
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
		void GAMESTART(int targetMoney,int time);
		//�Q�[���Z�b�g
		void GAMESET();
		//�\���p���l�̕���
		void Set_Num(int num,vector<shared_ptr<GameObject>> changennumobj);
		//�����ύX
		void Update_num(vector<shared_ptr<GameObject>> objs);
		//�����ύX�ɔ����X�v���C�g��UV���W�̕ύX
		void Set_Rect(int num, shared_ptr<GameObject> numobj);
		//�^�C�}�[�Z�b�g
		void Set_Timer(int time,vector<shared_ptr<GameObject>> changenumobj);
		//�^�C�}�[�̍X�V		
		void Update_Timer();
		//�ڕW�ƌ��݂��r����
		bool Check_Comparison();
		//�t���C���[�^�C�}�[
		void Fly_Timer();
		//�q�̑����Ǘ�
		void Master_Customers();
		//�q�̐l���Ǘ�
		void Customers_Count();
		//�q�̗v���𖞂������̊Ǘ�
		void Customers_Request();
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
		vector<shared_ptr<GameObject>> GetNumbers() {
			return m_Numbers;
		}
		vector<Rect2D<float>> GetRects() {
			return m_numRects;
		}
		void SetTimeForOil(bool bl) {
			m_timerForOil = bl;
		}
		bool GetTimerForOil() {
			return m_timerForOil;
		}
		//----------------------------------------//

	};
}