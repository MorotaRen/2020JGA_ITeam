using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GameMaster : MonoBehaviour
{
    //肉たち
    [SerializeField] private List<GameObject> m_Meats;
    //肉個別管理のスクリプト
    private Meat m_MeatScript;
    //ID
    private int m_Id = 0;

    private void Start()
    {
        SetID();
    }

    void SetID()
    {
        foreach(var obj in m_Meats)
        {
            m_MeatScript = obj.GetComponent<Meat>();
            if (m_MeatScript)
            {
                m_MeatScript.SetID(m_Id);
                m_Id++;
            }
            else
            {
                obj.AddComponent<Meat>();
                m_MeatScript = obj.GetComponent<Meat>();
                m_MeatScript.SetID(m_Id);
                m_Id++;
            }
            m_MeatScript = null;
        }
    }
}
