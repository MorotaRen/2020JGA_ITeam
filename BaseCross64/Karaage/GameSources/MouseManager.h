/*
�}�E�X�Ǘ�

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
		//�}�E�X�|�C���^
		Point2D<int> m_mousePoint;
		//Near��Far
		perspective m_perspective;
		//�R���X�g���N�^
		MouseManager() : m_mousePoint(0,0) {};
		//�f�X�g���N�^
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