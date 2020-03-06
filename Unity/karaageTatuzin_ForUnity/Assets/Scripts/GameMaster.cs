using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class GameMaster : MonoBehaviour
{

    [SerializeField] private GameObject m_SelectingObject;
    [SerializeField] private KeyCode m_RotateCode;

    [SerializeField] private List<Text> m_Meattexts;


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

    //揚げ処理
    void Fry()
    {

    }
}