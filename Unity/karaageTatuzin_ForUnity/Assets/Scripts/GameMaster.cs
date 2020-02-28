using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GameMaster : MonoBehaviour
{

    [SerializeField] private GameObject m_SelectingObject;
    [SerializeField] private KeyCode m_RotateCode;

    private void Update()
    {
        if (m_SelectingObject)
        {
            if (Input.GetKeyDown(m_RotateCode))
            {
                RightRotation90(m_SelectingObject);
            }
        }
    }
    //配列の右90°回転
    public void RightRotation90(GameObject obj)
    {
        obj.transform.Rotate(new Vector3(0.0f, 0.0f, 90.0f));
    }

    public void SetSelectingObject(GameObject obj)
    {
        m_SelectingObject = obj;
    }
}