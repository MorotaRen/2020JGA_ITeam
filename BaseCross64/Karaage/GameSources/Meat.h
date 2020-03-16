/*!
@file Meat.h
@brief ì˜ópÇ»Ç«
*/

#pragma once
#include "stdafx.h"
#define KaraagePrice 70; //ìÇógÇ∞
#define DrumPrice 100;   //ãr
#define WingPrice 130;   //éËâHêÊ
#define LibPrice 150;    //Ç†ÇŒÇÁ
#define KeelPrice 200;   //ãπ

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
		Vec3 m_Rotation;
	public:
		Karaage(const shared_ptr<Stage>& stagePtr,
			const Vec3& Scale,
			const Vec3& Position,
			const Vec3& Rotation);
		virtual ~Karaage() {}
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		virtual void OnUpdate2() override;
		void DrawString();
	};

	//ÉhÉâÉÄ
	class Drum :public GameObject {
		Vec3 m_Scale;
		Vec3 m_Position;
		Vec3 m_Rotation;

		float m_rad;
	public:
		Drum(const shared_ptr<Stage>& stagePtr,
			const Vec3& Scale,
			const Vec3& Position,
			const Vec3& Rotation);
		virtual ~Drum() {}
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		void Rotation();
	};

	// éËâHêÊ
	class Wing : public GameObject {
		Vec3 m_Scale;
		Vec3 m_Position;
		Vec3 m_Rotation;
	public:
		Wing(const shared_ptr<Stage>& stagePtr,
			const Vec3& Scale, 
			const Vec3& Position, 
			const Vec3& Rotation);
		virtual ~Wing() {}
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
	};

	// ÉäÉu
	class Lib : public GameObject {
		Vec3 m_Scale;
		Vec3 m_Position;
		Vec3 m_Rotation;
	public:
		Lib(const shared_ptr<Stage>& stagePtr,
			const Vec3& Scale,
			const Vec3& Position,
			const Vec3& Rotation);
		virtual ~Lib() {}
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
	};

	// ÉLÅ[Éã
	class Keel : public GameObject {
		Vec3 m_Scale;
		Vec3 m_Position;
		Vec3 m_Rotation;
	public:
		Keel(const shared_ptr<Stage>& stagePtr,
			const Vec3& Scale,
			const Vec3& Position,
			const Vec3& Rotation);
		virtual ~Keel() {}
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
	};
}
//end basecross
