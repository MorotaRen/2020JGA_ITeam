
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
		//������̓��ǂݍ���
		void SetMeat_Line(wstring name,wstring filename) {
			strTexture = dataDir + L"Texture\\Meats\\IsLine\\" + filename;
			App::GetApp()->RegisterTexture(name, strTexture);
		}
		//�S���\�[�X�K�p
		void CreateResourses()
		{
			//�f�B���N�g���擾
			App::GetApp()->GetAssetsDirectory(dataDir);

			//�e�N�X�`��
			//SetTexture(L"RANK_UI", L"Rank2.png");
<<<<<<< HEAD
			SetTexture(L"Black_TEST",L"Black.png");
			SetTexture(L"White_TEST",L"White.png");
			SetTexture(L"BG_Kitchen", L"Kitchen2.png");
			SetTexture(L"BG_Flyer", L"Flyer.png");
			SetTexture(L"Select_BG", L"Select_Background.png");
			SetTexture(L"Select_Stage_TX", L"Select_StageTx.png");
			SetTexture(L"Pointer_TX", L"pointer.png");
			SetTexture(L"Guest1_TX", L"Guest.png");
=======
			//SetTexture(L"Black_TEST",L"Black.png");
			//SetTexture(L"White_TEST",L"White.png");
			SetTexture(L"BG_Kitchen", L"Texture\\GameUIs\\", L"Kitchen.png");
			SetTexture(L"BG_Flyer", L"Texture\\GameUIs\\", L"Flyer.png");
			SetTexture(L"BG_Mass", L"Texture\\GameUIs\\", L"Masu.png");
			SetTexture(L"BG_Title", L"Texture\\Titles\\", L"Title.png");
			SetTexture(L"BG_TitleBack", L"Texture\\Titles\\", L"TitleBack.png");
			SetTexture(L"BG_StartButton", L"Texture\\Titles\\", L"StartButton.png");
			SetTexture(L"Select_BG", L"Texture\\UIs\\", L"Select_Background.png");
			SetTexture(L"Select_Stage_TX", L"Texture\\UIs\\", L"Select_StageTx.png");
			SetTexture(L"Icon_RegisterMark", L"Texture\\UIs\\", L"RegisterMark.png");
			SetTexture(L"Pointer_TX", L"Texture\\UIs\\", L"pointer.png");

			SetTexture(L"Chara_Normal", L"Texture\\Characters\\", L"Guests1-0.png");
			//SetTexture(L"Chara_Hurry", L"Texture\\Characters\\", L"Guests1-1.png");
			//SetTexture(L"Chara_Anger", L"Texture\\Characters\\", L"Guests1-2.png");
			//SetTexture(L"Chara_Happy", L"Texture\\Characters\\", L"Guests1-3.png");

			SetTexture(L"Tex_Number", L"Texture\\UIs\\", L"Number.png");
			SetTexture(L"Tex_Timer", L"Texture\\GameUIs\\", L"Timer.png");
			SetTexture(L"Tex_Oil", L"Texture\\GameUIs\\", L"Oil.png");
			SetTexture(L"TimerGauge_TX", L"Texture\\GameUIs\\", L"TimerGauge.png");
			SetTexture(L"TimerGaugeFrame_TX", L"Texture\\GameUIs\\", L"TimerGaugeFrame.png");
			SetTexture(L"DecisionalButton_TX", L"Texture\\", L"DecisionalButton.png");
			SetTexture(L"BackButton_TX", L"Texture\\", L"BackButton.png");
>>>>>>> Morota_ForHome

			//��(������)
			SetMeat_Line(L"Meat_Drum_Line",L"Chicken_Drum3.png");
			SetMeat_Line(L"Meat_Keel_Line",L"Chicken_Keel3.png");
			SetMeat_Line(L"Meat_Rib_Line",L"Chicken_Rib3.png");
			SetMeat_Line(L"Meat_Wing_Line",L"Chicken_Wing3.png");
			SetMeat_Line(L"Meat_Chicken_Line",L"FriedChicken3.png");
			SetMeat_Line(L"RawMeat_Drum_Line",L"RawMeat_Drum3.png");
			SetMeat_Line(L"RawMeat_Chicken_Line",L"RawMeat_FridChikin3.png");
			SetMeat_Line(L"RawMeat_Keel_Line",L"RawMeat_Keel3 .png");
			SetMeat_Line(L"RawMeat_Rib_Line",L"RawMeat_Rib3.png");
			SetMeat_Line(L"RawMeat_Wing_Line",L"RawMeat_Wing3.png");

			//���y

		}
	};

	//--------------------------------------------------------------------------------------
	///	�Q�[���V�[��
	//--------------------------------------------------------------------------------------
	void Scene::OnCreate(){
		try {
			//���\�[�X�ݒ�
			CreateResourse resourse;
			resourse.CreateResourses();
			
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
		if (event->m_MsgStr == L"ToSelectStage") {
			ResetActiveStage<SelectStage>();
		}
	}

}
//end basecross
