/*
マウス管理

*/

#pragma once
#include "stdafx.h"
#include "Project.h"

namespace basecross {

	struct perspective
	{
		Vec3 Near;
		Vec3 Far;
	};

	class MouseManager {
	private:
		//マウスポインタ
		Point2D<int> m_mousePoint;
		//NearとFar
		perspective m_perspective;
		//コンストラクタ
		MouseManager() : m_mousePoint(0,0) {};
		//デストラクタ
		~MouseManager() {};

	public:
		perspective GetMouseRay() {
			Mat4x4 world, view, proj;
			world.affineTransformation(
				Vec3(1.0f, 1.0f, 1.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(0.0f, 0.0f, 0.0f)
			);
			
			auto ptrStage = App::GetApp()->GetScene<Scene>()->GetActiveStage();
			auto ptrCamera = ptrStage->GetView()->GetTargetCamera();
			view = ptrCamera->GetViewMatrix();
			proj = ptrCamera->GetProjMatrix();
			auto viewport = ptrStage->GetView()->GetTargetViewport();

			m_perspective.Near = XMVector3Unproject(
				Vec3((float)m_mousePoint.x, (float)m_mousePoint.y, 0),
				viewport.TopLeftX,
				viewport.TopLeftY,
				viewport.Width,
				viewport.Height,
				viewport.MinDepth,
				viewport.MaxDepth,
				proj,
				view,
				world
			);
			m_perspective.Far = XMVector3Unproject(
				Vec3((float)m_mousePoint.x, (float)m_mousePoint.y, 1.0),
				viewport.TopLeftX,
				viewport.TopLeftY,
				viewport.Width,
				viewport.Height,
				viewport.MinDepth,
				viewport.MaxDepth,
				proj,
				view,
				world
			);

			return m_perspective;
		}
	};
}