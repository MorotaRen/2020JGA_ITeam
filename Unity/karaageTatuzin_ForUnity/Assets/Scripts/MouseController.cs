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
    private bool IsGeneration = false;
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
                        Vector3 CreatePos = new Vector3(m_Hit.collider.gameObject.transform.localPosition.x, m_Hit.collider.gameObject.transform.localPosition.y,-5);
                        var obj = Instantiate(m_SelectedObject, CreatePos, Quaternion.identity);
                        Destroy(obj.GetComponent<MeatController>());
                        Destroy(m_SelectedObject);
                        IsGeneration = false;
                        return 0;
                    }
                    //選択中のIDと新規選択のIDの比較
                    if (m_SelectedObject.GetComponent<MeatID>().GetID() != m_Hit.collider.GetComponent<MeatID>().GetID())
                    {
                        //比較結果がFALSEなら新規選択なので選択状態を解除し前選択オブジェクトを消す
                        Destroy(m_SelectedObject);
                        IsGeneration = false;
                    }
                }
                if (!IsGeneration) {
                    //ヒットしたやつを複製してみる
                    Vector3 mousepos = Input.mousePosition;
                    m_SelectedObject = Instantiate(m_Hit.collider.gameObject, mousepos, Quaternion.identity);
                    m_SelectedObject.AddComponent<MeatController>();
                    m_SelectedObject.layer = 2;
                    IsGeneration = true;
                }
            }
        }
        return 0;
    }
}
