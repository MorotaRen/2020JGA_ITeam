
/*!
@file Scene.cpp
@brief �V�[������
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{

	//--------------------------------------------------------------------------------------
	///	�f�ޓǂݍ���
	//--------------------------------------------------------------------------------------
	struct CreateResourse
	{
		//�A�Z�b�g�f�B���N�g��
		wstring dataDir;
		//�e�N�X�`��
		wstring strTexture;
		//���y
		wstring strSound;

	public:
		//�e�N�X�`���ǂݍ���
		void SetTexture(wstring name, wstring filename)
		{
			strTexture = dataDir + L"Texture\\" + filename;
			App::GetApp()->RegisterTexture(name, strTexture);
		}
		//���y�ǂݍ���
		void SetSound(wstring name, wstring filename)
		{
			strSound = dataDir + L"Sound\\" + filename;
			App::GetApp()->RegisterWav(name, strSound);
		}
		//�S���\�[�X�K�p
		void CreateResourses()
		{
			//�f�B���N�g���擾
			App::GetApp()->GetAssetsDirectory(dataDir);

			//�e�N�X�`��
			SetTexture(L"RANK_UI", L"Rank2.png");

			//���y

		}
	};

	//--------------------------------------------------------------------------------------
	///	�Q�[���V�[��
	//--------------------------------------------------------------------------------------
	void Scene::OnCreate(){
		try {
			//���\�[�X�ݒ�
			//CreateResourse resourse;
			//resourse.CreateResourses();

			//�N���A����F��ݒ�
			Col4 Col;
			Col.set(31.0f / 255.0f, 30.0f / 255.0f, 71.0f / 255.0f, 255.0f / 255.0f);
			SetClearColor(Col);
			//�������g�ɃC�x���g�𑗂�
			//����ɂ��e�X�e�[�W��I�u�W�F�N�g��Create���ɃV�[���ɃA�N�Z�X�ł���
			PostEvent(0.0f, GetThis<ObjectInterface>(), GetThis<Scene>(), L"ToGameStage");
		}
		catch (...) {
			throw;
		}
	}

	Scene::~Scene() {
	}

	void Scene::OnEvent(const shared_ptr<Event>& event) {
		if (event->m_MsgStr == L"ToGameStage") {
			//�ŏ��̃A�N�e�B�u�X�e�[�W�̐ݒ�
			ResetActiveStage<GameStage>();
		}
	}

}
//end basecross
