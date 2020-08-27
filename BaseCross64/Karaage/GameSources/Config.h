#pragma once
#include "stdafx.h"

//------------------�N�ł��ύX�\------------------//

//�g������̃��L���X�g����
#define FLY_RECAST_TIME 2

//�f�t�H���g�ŉ������Ă���̎�ސ�
#define DEFAULT_RELEASE_MEATS 3

//���̎�ނ̍ő�l
#define MAX_MEATCOUNT 5
//�f�o�b�N���[�h�ؑ�
#define BOOL_ISDEBUG true;

//�e����̋��z
#define PRICE_KARAAGE	70;		//���g��	(70)
#define PRICE_DRUM		100;	//�r		(100)
#define PRICE_WING		130;	//��H��	(130)
#define PRICE_LIB		150;	//���΂�	(150)
#define PRICE_KEEL		200;	//��		(200)

//�e����̃I�[�_�[�ő吔
#define LIMIT_ORDER_KARAAGE	5;	//5
#define LIMIT_ORDER_DRUM	5;	//5
#define LIMIT_ORDER_WING	5;	//5
#define LIMIT_ORDER_LIB		5;	//5
#define LIMIT_ORDER_KEEL	5;	//5

//-----------------------------------------------//


//>>>>�ȉ�����ɕύX���Ȃ��悤�ɁA�ύX����ꍇ���c�ɘA�����邱�ƁI<<<<//
//------------------�����V�X�e���p------------------//

//�Q�[���t�B�[���h�̏c��(X5Y10)
#define GAMEFIELD_X 5
#define GAMEFIELD_Y 4
//�}�b�v�`�b�v�̃T�C�Y(XY60)
#define MAPCHIP_SIZE_X 60.0f
#define MAPCHIP_SIZE_Y 60.0f
//�}�b�v�`�b�v�̊J�n�n�_(X-140Y250)
#define MAPCHIP_START_X -140.0f
#define MAPCHIP_START_Y 125.0f
//���E(4682)
#define LEFT	4
#define RIGHT	6
#define UP		8
#define DOWN	2

//�z�u�󋵂̐��l(9)
#define Setup_FALSE 9
//�q�̍ő吔
#define MAX_CUSTOMERS 3
//���݋��z�\�����W�̊J�n�_�Ɛ����Ԋu
#define NOWMONEY_STARTPOS_X 550
#define NOWMONEY_STARTPOS_Y 100
#define NOWMONEY_INTERVAL 50;
//�^�C�}�[�\�����W�̊J�n�_�Ɛ����Ԋu
#define TIMER_STARTPOS_X 540
#define TIMER_STARTPOS_Y 220
#define TIMER_INTERVAL 30;
//�ڕW���z�\�����W�̊J�n�_�Ɛ����Ԋu
#define TARGET_STARTPOS_X 550
#define TARGET_STARTPOS_Y 30
#define TARGET_INTERVAL 50;

//-----------------------------------------------//


//------------------�Q�[���Ǘ��p------------------//
//�Q�[���X�e�[�W�̐������ԁF��(+59�b)
#define STAGE_TIME_1 5
#define STAGE_TIME_2 4
#define STAGE_TIME_3 3
#define STAGE_TIME_4 2
#define STAGE_TIME_5 1
//�Q�[���X�e�[�W�̖ڕW���z
#define STAGE_MONEY_1 500
#define STAGE_MONEY_2 700
#define STAGE_MONEY_3 500
#define STAGE_MONEY_4 800
#define STAGE_MONEY_5 1000