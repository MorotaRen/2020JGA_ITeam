using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MouseController : MonoBehaviour
{
    //監視用
    [SerializeField] private GameObject m_SelectedObject;
    //MainCamera
    [SerializeField] private Camera m_Camera;
    //Rayのヒットしたヤツ格納用
    [SerializeField] private RaycastHit m_Hit;
    //生成したかをBool
    private bool m_IsGeneration = false;
    //複製オブジェクト
    private GameObject m_CopyObject;
    //ゲームマスター
    [SerializeField]private GameMaster m_GameMaster;
    //選択中のオブジェクト
    private void Update()
    {
        MouseRayCast();
    }
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
                        //そのマップマスの所に実際の配置生成物の生成をする
                        //作成POS
                        Vector3 CreatePos = new Vector3(m_Hit.collider.gameObject.transform.localPosition.x, m_Hit.collider.gameObject.transform.localPosition.y,-1);
                        if (Installation_Try(m_Hit.collider.gameObject))
                        {
                            Debug.Log("置けるよ");
                            //次に周りのブロックの置けるか検知
                            RaycastHit raycastHit;
                            //子供を全部取得
                            foreach (Transform childTransform in m_SelectedObject.transform)
                            {
                                int Distance = 100;
                                Ray Childray = new Ray(childTransform.gameObject.transform.position, new Vector3(0, 0, 100));
                                Debug.DrawLine(Childray.origin, Childray.direction * Distance, Color.red);

                                if (Physics.Raycast(Childray, out raycastHit))
                                {
                                    if (!Installation_Try(raycastHit.collider.gameObject))
                                    {
                                        Debug.Log("子供が被ってるんでダメです");
                                        return 0;
                                    }
                                }
                                //設置可能
                                if (raycastHit.collider) {
                                    Debug.Log("子供の前にあるのは" + raycastHit.collider.gameObject);
                                }

                            }




                            //選択中オブジェクトを生成
                            var obj = Instantiate(m_SelectedObject, CreatePos, m_SelectedObject.transform.rotation);
                            //後始末
                            Send_GameMaster(obj);
                            Destroy(obj.GetComponent<MeatController>());
                            Destroy(m_SelectedObject);
                            m_IsGeneration = false;
                            return 0;
                        }
                        Debug.Log("置けないよ");
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
                        foreach (Transform childTransform in parent.transform)
                        {
                            childTransform.gameObject.tag = "Meat_Installed";
                        }
                    }
                    else
                    {
                        m_CopyObject = m_Hit.collider.gameObject;
                    }
                    m_SelectedObject = Instantiate(m_CopyObject, mousepos, Quaternion.identity);
                    m_SelectedObject.AddComponent<MeatController>();
                    m_SelectedObject.layer = 2;
                    m_SelectedObject.tag = "Meat_Installed";
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
                mapchip.m_Installed = true;
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
                break;
        }
    }

}
