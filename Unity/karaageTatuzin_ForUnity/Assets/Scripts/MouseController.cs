using System.Collections;
using System.Collections.Generic;
using UnityEngine;

/// -----------------------------------------------<summary>
/// マウス関連
/// </summary>-----------------------------------------------

public class MouseController : MonoBehaviour
{
    [Header("選択状態のオブジェクト(監視用)")]
    [SerializeField] private GameObject m_SelectedObject;

    [Header("メインカメラ")]
    [SerializeField] private Camera m_Camera;

    [Header("レイがヒットしたものの格納用(監視用)")]
    [SerializeField] private RaycastHit m_Hit;

    [Header("肉達")]
    [SerializeField] private List<GameObject> m_Meats;

    int m_MeatCount = 0;

    //生成したかをBool
    private bool m_IsGeneration = false;

    //複製オブジェクト
    private GameObject m_CopyObject;

    //ゲームマスター
    [SerializeField]private GameMaster m_GameMaster;

    private void Update()
    {

        MouseRayCast();
        if (Input.GetKeyDown(KeyCode.A))
        {
            Change_Meat();
        }
    }

    /// -----------------------------------------------<summary>
    /// キーで変わるように…
    /// </summary>-----------------------------------------------
    void Change_Meat()
    {
        Destroy(m_SelectedObject);
        //ヒットしたやつを複製してみる
        Vector3 mousepos = Input.mousePosition;
        mousepos.z = -5;

        m_CopyObject = m_Meats[m_MeatCount];

        //まず子供じゃないか検査
        GameObject parent = m_CopyObject;
        //親がいた場合は親を複製オブジェクトにする
        if (parent)
        {
            m_CopyObject = parent;
        }
        m_SelectedObject = Instantiate(m_CopyObject, mousepos, Quaternion.identity);
        m_SelectedObject.AddComponent<MeatController>();
        m_SelectedObject.layer = 2;
        m_GameMaster.SetSelectingObject(m_SelectedObject);
        m_IsGeneration = true;
        m_MeatCount++;
        if (m_MeatCount >= m_Meats.Count)
        {
            m_MeatCount = 0;
        }
    }

    /// -----------------------------------------------<summary>
    /// マウスのレイキャスト
    /// </summary>-----------------------------------------------
    int MouseRayCast()
    {
        //RayカメラからのRay
        Ray ray = m_Camera.ScreenPointToRay(Input.mousePosition);
        if (Input.GetMouseButtonDown(0)) {
            //m_Hitに入るよ
            if (Physics.Raycast(ray, out m_Hit))
            {
                //選択オブジェクトが生成されていたら
                if (m_SelectedObject) {
                    //マップが選択されていたら
                    if (m_Hit.collider.gameObject.tag == "Map")
                    {
                        //作成場所
                        Vector3 CreatePos = new Vector3(m_Hit.collider.gameObject.transform.localPosition.x, m_Hit.collider.gameObject.transform.localPosition.y, -1);
                        GenerationSet_Object(CreatePos);
                        return 0;
                    }
                    //選択中のIDと新規選択のIDの比較
                    if (m_SelectedObject.GetComponent<MeatID>().GetID() != m_Hit.collider.GetComponent<MeatID>().GetID())
                    {
                        //比較結果がFALSEなら新規選択なので選択状態を解除し前選択オブジェクトを消す
                        Destroy(m_SelectedObject);
                        m_IsGeneration = false;
                    }
                }else
                if (!m_IsGeneration
                    && m_Hit.collider.gameObject.tag != "Map"
                    && m_Hit.collider.gameObject.tag != "Meat_Installed"
                    && !m_SelectedObject) {
                    //ヒットしたやつを複製してみる
                    Vector3 mousepos = Input.mousePosition;
                    mousepos.z = -5;

                    //まず子供じゃないか検査
                    GameObject parent = m_Hit.collider.gameObject.transform.root.gameObject;
                    //親がいた場合は親を複製オブジェクトにする
                    if (parent)
                    {
                        m_CopyObject = parent;
                    }
                    else
                    {
                        m_CopyObject = m_Hit.collider.gameObject;
                    }
                    m_SelectedObject = Instantiate(m_CopyObject, mousepos, Quaternion.identity);
                    m_SelectedObject.AddComponent<MeatController>();
                    m_SelectedObject.layer = 2;
                    m_GameMaster.SetSelectingObject(m_SelectedObject);
                    m_IsGeneration = true;
                }
            }
        }
        return 0;
    }
    //設置できるか確認する<判定したいマスを渡す>
    bool Installation_Try(GameObject obj)
    {
        var mapchip = obj.GetComponent<Mapchip>();
        if (mapchip)
        {
            if (!mapchip.m_Installed)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        return false;
    }
    //設置したものをマスターに送る
    void Send_GameMaster(GameObject sendobj)
    {
        switch (sendobj.gameObject.tag)
        {
            case "Meat_1x1":
                m_GameMaster.meats.Meat_1x1++;
                Debug.Log("1x1の肉設置");
                break;
            case "Meat_1x2":
                m_GameMaster.meats.Meat_1x2++;
                Debug.Log("1x2の肉設置");
                break;
            case "Meat_2x2":
                m_GameMaster.meats.Meat_2x2++;
                Debug.Log("2x2の肉設置");
                break;
            case "Meat_3x3":
                m_GameMaster.meats.Meat_3x3++;
                Debug.Log("3x3の肉設置");
                break;
            case "Meat_L":
                m_GameMaster.meats.Meat_L++;
                Debug.Log("Lの肉設置");
                break;
            default:
                Debug.Log("タグが一致しません…Tagは"+ sendobj.tag);
                break;
        }
    }
    //送られてきた所に設置する
    int GenerationSet_Object(Vector3 createPos)
    {

        if (Installation_Try(m_Hit.collider.gameObject))
        {
            Debug.Log("！！！設置可能！！！");

            //------次に周りのブロックの置けるか検知------//

            //レイに接触したものが入る
            RaycastHit raycastHit;
            //子供を全部取得
            foreach (Transform childTransform in m_SelectedObject.transform)
            {
                //長さ
                int Distance = 100;
                //子供からレイを発射
                Ray Childray = new Ray(childTransform.gameObject.transform.position, new Vector3(0, 0, Distance));
                //レイを飛ばしてキャスト
                if (Physics.Raycast(Childray, out raycastHit))
                {
                    //設置不可
                    if (!Installation_Try(raycastHit.collider.gameObject))
                    {
                        Debug.Log("！！！子供が被ってるんでダメです！！！");
                        return 0;
                    }
                }
            }
            //-------------------------------------------//


            //------実際に生成して設置------//
            //選択中オブジェクトを生成
            var obj = Instantiate(m_SelectedObject, createPos, m_SelectedObject.transform.rotation);
            //ゲームマスターに設置した肉を送る
            Send_GameMaster(obj);
            //タグをもう設置済みにする
            obj.tag = "Meat_Installed";
            Transform Children = obj.gameObject.transform;
            foreach (Transform childTransform in Children.transform)
            {
                childTransform.gameObject.tag = "Meat_Installed";
            }
            //マウスでコントロールするためのスクリプトを削除
            Destroy(obj.GetComponent<MeatController>());
            //今選択していた肉を消す
            //Destroy(m_SelectedObject);
            //選択状態を解除
            m_IsGeneration = false;
            //キーボード選択用の数字の初期化
            //m_MeatCount = 0;
            //設置したから置けないように
            m_Hit.collider.GetComponent<Mapchip>().m_Installed = true;
            m_Hit.collider.GetComponent<SpriteRenderer>().color = Color.red;

            return 0;
        }
        Debug.Log("！！！置けないよ！！！");
        return 0;
    }

}
