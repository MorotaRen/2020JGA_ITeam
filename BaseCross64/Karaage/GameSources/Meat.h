/*!
@file Meat.h
@brief ���p�Ȃ�
*/

#pragma once
#include "stdafx.h"


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
