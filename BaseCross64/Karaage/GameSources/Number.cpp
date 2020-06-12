/*!
@file Character.cpp
@brief �L�����N�^�[�Ȃǎ���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{
	void Number::OnCreate()
	{
		//���_�̌��f�[�^
		vertices = {
			{Vec3( 0,   0, 0),Vec2(0.0f, 0.0f)},
			{Vec3(50,   0, 0),Vec2(0.0f, 0.0f)},
			{Vec3( 0,-100, 0),Vec2(0.0f, 1.0f)},
			{Vec3(50,-100, 0),Vec2(0.0f, 1.0f)}
		};

		//���_�C���f�b�N�X
		std::vector<uint16_t> indices = {
			0,1,2,
			2,1,3
		};

		auto drawComp = AddComponent<PTSpriteDraw>(vertices, indices);
		drawComp->SetTextureResource(L"Number");

		this->SetAlphaActive(true);
	}
	
	void Number::UpdateUV()
	{
		float w = 64.0f / 640.0f;

		// UV���W���X�V����
		vertices[0].textureCoordinate.x = (number + 0) * w;
		vertices[1].textureCoordinate.x = (number + 1) * w;
		vertices[2].textureCoordinate.x = (number + 0) * w;
		vertices[3].textureCoordinate.x = (number + 1) * w;

		auto darwComp = GetComponent<PTSpriteDraw>();
		darwComp->UpdateVertices(vertices);
	}
}
//end basecross
