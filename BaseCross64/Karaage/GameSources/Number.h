/*!
@file Character.h
@brief �L�����N�^�[�Ȃ�
*/

#pragma once
#include "stdafx.h"

namespace basecross{
	class Number : public GameObject 
	{
		int number;//�摜�̌��ƂȂ鐔�l
		std::vector<VertexPositionTexture> vertices;//���_�f�[�^

	public :
		Number(const shared_ptr<Stage>& stage)
			: GameObject(stage)
		{
		}

		void OnCreate() override;

		//�\�����鐔����ύX���鎞�Ɏg���Z�b�^�[
		void SetNumber(int n) 
		{
			number = n;
		}

		void UpdateUV();
	};

}
//end basecross
