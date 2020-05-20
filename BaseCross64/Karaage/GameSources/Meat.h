/*!
@file Meat.h
@brief 肉用など
*/

#pragma once
#include "stdafx.h"


namespace basecross{
	// 唐揚げ
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

	//ドラム
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

	// 手羽先
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

	// リブ
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

	// キール
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
