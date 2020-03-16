#pragma once
/// ----------------------------------------<summary>
/// �g�����Ɋւ��Ă̊֐����܂Ƃ܂��Ă���Ƃ���
/// �ǂ�����ł��Ăяo����
/// ���F�V���O���g��
/// �Ǘ��ҁF���c
/// </summary>----------------------------------------

#include "stdafx.h"
//�Q�[���t�B�[���h�̏c
#define GAMEFIELD_X 10
//�Q�[���t�B�[���h�̉�
#define GAMEFIELD_Y 5
//�g������̃��L���X�g����
#define FLY_RECAST_TIME 20

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
		//

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
		//----------------------------------------//

	};
}