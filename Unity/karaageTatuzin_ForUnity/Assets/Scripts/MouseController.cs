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

    private void Update()
    {
        MouseRayCast();
    }
    void MouseRayCast()
    {
        //RayカメラからのRay
        Ray ray = m_Camera.ScreenPointToRay(Input.mousePosition);
        if (Input.GetMouseButtonDown(0)) {
            //m_Hitに入るよ
            if (Physics.Raycast(ray, out m_Hit))
            {
                if (!IsGeneration) {
                    //ヒットしたやつを複製してみる
                    Vector3 mousepos = Input.mousePosition;
                    var obj = Instantiate(m_Hit.collider.gameObject, mousepos, Quaternion.identity);
                    obj.AddComponent<MeatController>();
                    IsGeneration = true;
                }
            }
        }
    }
}
