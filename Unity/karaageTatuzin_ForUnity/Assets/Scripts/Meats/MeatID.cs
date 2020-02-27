using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MeatID : MonoBehaviour
{
    [SerializeField] private int m_Id;
    public void SetID(int id)
    {
        m_Id = id;
    }
    public int GetID()
    {
        return m_Id;
    }

}
