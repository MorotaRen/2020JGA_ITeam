/*!
@file Meat.h
@brief ���p�Ȃ�
*/

#pragma once
#include "stdafx.h"
#define KaraagePrice 70; //���g��
#define DrumPrice 100;   //�r
#define WingPrice 130;   //��H��
#define LibPrice 150;    //���΂�
#define KeelPrice 200;   //��

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

	//�h����
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

	// ��H��
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

	// ���u
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

	// �L�[��
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
