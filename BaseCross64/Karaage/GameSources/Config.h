#pragma once
#include "stdafx.h"

//------------------誰でも変更可能------------------//

//揚げた後のリキャスト時間
#define FLY_RECAST_TIME 2

//デフォルトで解放されてる肉の種類数
#define DEFAULT_RELEASE_MEATS 3

//肉の種類の最大値
#define MAX_MEATCOUNT 5


//各種肉の金額
#define PRICE_KARAAGE	70;		//唐揚げ	(70)
#define PRICE_DRUM		100;	//脚		(100)
#define PRICE_WING		130;	//手羽先	(130)
#define PRICE_LIB		150;	//あばら	(150)
#define PRICE_KEEL		200;	//胸		(200)

//各種肉のオーダー最大数
#define LIMIT_ORDER_KARAAGE	5;	//5
#define LIMIT_ORDER_DRUM	5;	//5
#define LIMIT_ORDER_WING	5;	//5
#define LIMIT_ORDER_LIB		5;	//5
#define LIMIT_ORDER_KEEL	5;	//5

//-----------------------------------------------//


//>>>>以下勝手に変更しないように、変更する場合諸田に連絡すること！<<<<//
//------------------内部システム用------------------//

//ゲームフィールドの縦横(X5Y10)
#define GAMEFIELD_X 5
#define GAMEFIELD_Y 4
//マップチップのサイズ(XY60)
#define MAPCHIP_SIZE_X 60.0f
#define MAPCHIP_SIZE_Y 60.0f
//マップチップの開始地点(X-140Y250)
#define MAPCHIP_START_X -140.0f
#define MAPCHIP_START_Y 125.0f
//左右(4682)
#define LEFT	4
#define RIGHT	6
#define UP		8
#define DOWN	2

//配置状況の数値(9)
#define Setup_FALSE 9
//客の最大数
#define MAX_CUSTOMERS 3
//現在金額表示座標の開始点と数字間隔
#define NOWMONEY_STARTPOS_X 550
#define NOWMONEY_STARTPOS_Y 100
#define NOWMONEY_INTERVAL 50;
//タイマー表示座標の開始点と数字間隔
#define TIMER_STARTPOS_X 540
#define TIMER_STARTPOS_Y 220
#define TIMER_INTERVAL 30;
//目標金額表示座標の開始点と数字間隔
#define TARGET_STARTPOS_X 550
#define TARGET_STARTPOS_Y 30
#define TARGET_INTERVAL 50;

//-----------------------------------------------//