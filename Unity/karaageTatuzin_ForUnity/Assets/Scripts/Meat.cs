using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Meat : MonoBehaviour
{
    [SerializeField] private int ID;
    public void SetID(int id)
    {
        ID = id;
    }
    public int GetID()
    {
        return ID;
    }
}
