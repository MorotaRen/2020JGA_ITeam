#pragma once
#include "stdafx.h"

//------------------�N�ł��ύX�\------------------//

//�g������̃��L���X�g����
#define FLY_RECAST_TIME 20

//�f�t�H���g�ŉ������Ă���̎�ސ�
#define DEFAULT_RELEASE_MEATS 3

//���̎�ނ̍ő�l
#define MAX_MEATCOUNT 5

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
#define GAMEFIELD_Y 10	
//�}�b�v�`�b�v�̃T�C�Y(XY60)
#define MAPCHIP_SIZE_X 60.0f
#define MAPCHIP_SIZE_Y 60.0f
//�}�b�v�`�b�v�̊J�n�n�_(X-140Y250)
#define MAPCHIP_START_X -140.0f
#define MAPCHIP_START_Y 250.0f
//���E(4682)
#define LEFT	4
#define RIGHT	6
#define UP		8
#define DOWN	2
//�ړ����~�b�g(-140,-270,60,250)
#define MOVELIMIT_MIN_X -140
#define MOVELIMIT_MIN_Y -270
#define MOVELIMIT_MAX_X  60
#define MOVELIMIT_MAX_Y  250
//�z�u�󋵂̐��l(9)
#define Setup_FALSE 9

//-----------------------------------------------//