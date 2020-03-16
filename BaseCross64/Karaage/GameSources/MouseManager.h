/*
マウス管理

*/

#pragma once
#include "stdafx.h";
#include "Project.h"

namespace basecross {

	struct perspective
	{
		Vec3 Near;
		Vec3 Far;
	};

	class MouseManager {
	private:
		//コンストラクタ
		MouseManager() {};
		//デストラクタ
		~MouseManager() {};

	public:
		Vec3 GetMousePosition()const {
		}

		void GetMouseRay(Vec3& Near, Vec3& Far) {
			Mat4x4 world, view, proj;
			world.affineTransformation(
				Vec3(1.0f, 1.0f, 1.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(0.0f, 0.0f, 0.0f)
			);

			auto stage = App::
			
		}
	};
}