/*!
@file Character.cpp
@brief �L�����N�^�[�Ȃǎ���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{
	void Number::OnCreate()
	{
		float helfSize = 0.5f;
		//���_�̌��f�[�^
		//vertices = {
		//	{Vec3( -helfSize,  helfSize, 0),Vec2(0.0f, 0.0f)},
		//	{Vec3(  helfSize,  helfSize, 0),Vec2(0.0f, 0.0f)},
		//	{Vec3( -helfSize, -helfSize, 0),Vec2(0.0f, 1.0f)},
		//	{Vec3(  helfSize, -helfSize, 0),Vec2(0.0f, 1.0f)}
		//};

		vector<VertexPositionColorTexture> vertices = {
			{ VertexPositionColorTexture(Vec3( -helfSize,  helfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(0.0f, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(  helfSize,  helfSize, 0), Col4(0.0f, 1.0f, 1.0f, 1.0f), Vec2(5.0f, 0.0f)) },
			{ VertexPositionColorTexture(Vec3( -helfSize, -helfSize, 0), Col4(1.0f, 0.0f, 1.0f, 1.0f), Vec2(0.0f, 5.0f)) },
			{ VertexPositionColorTexture(Vec3(  helfSize, -helfSize, 0), Col4(0.0f, 0.0f, 0.0f, 1.0f), Vec2(5.0f, 5.0f)) },
		};
		//���_�C���f�b�N�X
		std::vector<uint16_t> indices = {
			0,1,2,
			2,1,3
		};

		//auto drawComp = AddComponent<PTSpriteDraw>(vertices, indices);
		//drawComp->SetTextureResource(L"Number");

		this->SetAlphaActive(true);

		auto PtrTrans = GetComponent<Transform>();
		PtrTrans->SetRotation(0, 0, 0);
		//���_�ƃC���f�b�N�X���w�肵�X�v���C�g�̍쐬
		AddComponent<PCSpriteDraw>(vertices, indices);

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
