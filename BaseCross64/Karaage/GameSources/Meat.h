/*!
@file Meat.h
@brief ���p�Ȃ�
*/

#pragma once
#include "stdafx.h"
#define PRICE_KARAAGE 70; //���g��
#define PRICE_DRUM 100;   //�r
#define PRICE_WING 130;   //��H��
#define PRICE_LIB 150;    //���΂�
#define PRICE_KEEL 200;   //��

#define KaraageOder 5;
#define DrumOder 5;
#define WingOder 5;
#define LibOder 5;
#define KeelOder 5;

namespace basecross{
	// ���g��
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

	//�h����
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

	// ��H��
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

	// ���u
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

	// �L�[��
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
