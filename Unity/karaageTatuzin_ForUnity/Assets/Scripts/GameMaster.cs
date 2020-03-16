using System.Collections;
using System.Collections.Generic;
using UnityEngine;

/// -----------------------------------------------<summary>
/// 肉が選択状態で動く時に必要なスクリプト
/// </summary>-----------------------------------------------

//UI編集用の必須インクルード
using UnityEngine.UI;

public class GameMaster : MonoBehaviour
{
    [Header("選択状態オブジェクト確認用")]
    [SerializeField] private GameObject m_SelectingObject;

    [Header("回転するボタン")]
    [SerializeField] private KeyCode m_RotateCode;

    [Header("揚げるボタン")]
    [SerializeField] private KeyCode m_FryCode;

    [Header("Area管理スクリプト")]
    [SerializeField] private Area m_area;

    [Header("肉在庫表示用テキスト")]
    [SerializeField] private List<Text> m_Meattexts;



    //肉の在庫保存用クラス
    public class Meats{
        public int Meat_1x1;
        public int Meat_1x2;
        public int Meat_2x2;
        public int Meat_3x3;
        public int Meat_L;
    }

    public Meats meats = new Meats();


    private void Update()
    {
        if (m_SelectingObject)
        {
            float Scroll = Input.GetAxis("Mouse ScrollWheel");
            if (Scroll > 0)
            {
                RightRotation90(m_SelectingObject);
            }
            if (Scroll < 0)
            {
                LeftRotation90(m_SelectingObject);
            }
        }
        if (Input.GetKeyDown(m_FryCode))
        {
            Fry();
        }
    }

    /// -----------------------------------------------<summary>
    /// 90度回転する
    /// </summary>-----------------------------------------------
    /// <param name="obj">回転するオブジェクト</param>
    public void RightRotation90(GameObject obj)
    {
        obj.transform.Rotate(new Vector3(0.0f, 0.0f, 90.0f));
    }

    /// -----------------------------------------------<summary>
    /// 90度回転する
    /// </summary>-----------------------------------------------
    /// <param name="obj">回転するオブジェクト</param>
    public void LeftRotation90(GameObject obj)
    {
        obj.transform.Rotate(new Vector3(0.0f, 0.0f, -90.0f));
    }

    /// -----------------------------------------------<summary>
    /// 選択状態のオブジェクトの設定
    /// </summary>-----------------------------------------------
    /// <param name="obj">選択状態のオブジェクト</param>
    public void SetSelectingObject(GameObject obj)
    {
        m_SelectingObject = obj;
    }

    /// -----------------------------------------------<summary>
    /// 揚げる
    /// </summary>-----------------------------------------------
    private void Fry()
    {
        m_Meattexts[0].text = meats.Meat_1x1.ToString();
        m_Meattexts[1].text = meats.Meat_1x2.ToString();
        m_Meattexts[2].text = meats.Meat_2x2.ToString();
        m_Meattexts[3].text = meats.Meat_3x3.ToString();
        m_Meattexts[4].text = meats.Meat_L.ToString();
        //設置されてる肉を全部削除
        GameObject[] gameObjects = GameObject.FindGameObjectsWithTag("Meat_Installed");
        foreach (var obj in gameObjects)
        {
            Destroy(obj.gameObject);
        }
        //マップのリセット
        m_area.ResetMaps();

    }

    public Meats GetMeats()
    {
        return meats;
    }
}