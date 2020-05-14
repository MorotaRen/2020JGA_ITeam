/*!
@file Meat.h
@brief ì˜ópÇ»Ç«
*/

#pragma once
#include "stdafx.h"
#define PRICE_KARAAGE 70; //ìÇógÇ∞
#define PRICE_DRUM 100;   //ãr
#define PRICE_WING 130;   //éËâHêÊ
#define PRICE_LIB 150;    //Ç†ÇŒÇÁ
#define PRICE_KEEL 200;   //ãπ

#define KaraageOder 5;
#define DrumOder 5;
#define WingOder 5;
#define LibOder 5;
#define KeelOder 5;

namespace basecross{
	// ìÇógÇ∞
	class Karaage : public GameObject {
		Vec3 m_Scale;
		Vec3 m_Position;
		Quat m_Quat;
	public:
		Karaage(const shared_ptr<Stage>& stagePtr,
			const Vec3& Scale,
			const Vec3& Position,
			const Quat& quat);
		virtual ~Karaage() {}
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		virtual void OnUpdate2() override;
	};

	//ÉhÉâÉÄ
	class Drum :public GameObject {
		Vec3 m_Scale;
		Vec3 m_Position;
		Quat m_Quat;

		float m_rad;
	public:
		Drum(const shared_ptr<Stage>& stagePtr,
			const Vec3& Scale,
			const Vec3& Position,
			const Quat& quat);
		virtual ~Drum() {}
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
	};

	// éËâHêÊ
	class Wing : public GameObject {
		Vec3 m_Scale;
		Vec3 m_Position;
		Quat m_Quat;
	public:
		Wing(const shared_ptr<Stage>& stagePtr,
			const Vec3& Scale, 
			const Vec3& Position, 
			const Quat& quat);
		virtual ~Wing() {}
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
	};

	// ÉäÉu
	class Rib : public GameObject {
		Vec3 m_Scale;
		Vec3 m_Position;
		Quat m_Quat;
	public:
		Rib(const shared_ptr<Stage>& stagePtr,
			const Vec3& Scale,
			const Vec3& Position,
			const Quat& quat);
		virtual ~Rib() {}
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
	};

	// ÉLÅ[Éã
	class Keel : public GameObject {
		Vec3 m_Scale;
		Vec3 m_Position;
		Quat m_Quat;
	public:
		Keel(const shared_ptr<Stage>& stagePtr,
			const Vec3& Scale,
			const Vec3& Position,
			const Quat& quat);
		virtual ~Keel() {}
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
	};
}
//end basecross
