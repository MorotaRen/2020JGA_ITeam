using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Area : MonoBehaviour
{
    [SerializeField] private int XSize = 0;
    [SerializeField] private int YSize = 0;
    [SerializeField] private GameObject WObj = null;
    [SerializeField] private GameObject BObj = null;
    [SerializeField] private Vector2 StartPos;
    [SerializeField] private Vector2 IntervalPos;
    [SerializeField] private Vector2 GenerationPos;
    [SerializeField] private List<GameObject> m_Meats;
    [SerializeField] private GameMaster m_GM;



    private int[,] map;
    private int num;
    private GameObject obj;
    private List<GameObject> maps　= new List<GameObject>();

    private void Start()
    {
        map = new int[XSize, YSize];
        GenerationPos = StartPos;
        MapCreate();
        SetRandMeat(3);
    }

    private void MapCreate()
    {
        for (int i = 0; i < YSize; i++)
        {
            for (int k = 0; k < XSize; k++)
            {
                switch (num)
                {
                    case 0:
                        obj = Instantiate(WObj, new Vector3(GenerationPos.x, GenerationPos.y, 0), Quaternion.identity);
                        //obj.transform.parent = this.transform;
                        obj.tag = "Map";
                        obj.AddComponent<BoxCollider>();
                        obj.AddComponent<Mapchip>();
                        maps.Add(obj);
                        GenerationPos.x += 1;
                        num = 1;
                        break;
                    case 1:
                        obj = Instantiate(BObj, new Vector3(GenerationPos.x, GenerationPos.y, 0), Quaternion.identity);
                        //obj.transform.parent = this.transform;
                        obj.tag = "Map";
                        obj.AddComponent<BoxCollider>();
                        obj.AddComponent<Mapchip>();
                        maps.Add(obj);
                        GenerationPos.x += 1;
                        num = 0;
                        break;
                }
                if (k == 4 && num == 0)
                {
                    num = 1;
                }else
                if (k == 4 && num == 1)
                {
                    num = 0;
                }

            }
            GenerationPos.y -= 1;
            GenerationPos.x = StartPos.x;
            switch (num)
            {
                case 0:
                    num = 1;
                    break;
                case 1:
                    num = 0;
                    break;
            }
        }
    }

    public void ResetMaps()
    {
        foreach (var map in maps)
        {
            map.GetComponent<Mapchip>().m_Installed = false;
            map.GetComponent<SpriteRenderer>().color = Color.white;
        }
        SetRandMeat(3);
    }

    void Send_GameMaster(GameObject sendobj)
    {
        switch (sendobj.gameObject.tag)
        {
            case "Meat_1x1":
                m_GM.meats.Meat_1x1++;
                break;
            case "Meat_1x2":
                m_GM.meats.Meat_1x2++;
                break;
            case "Meat_2x2":
                m_GM.meats.Meat_2x2++;
                break;
            case "Meat_3x3":
                m_GM.meats.Meat_3x3++;
                break;
            case "Meat_L":
                m_GM.meats.Meat_L++;
                break;
            default:
                Debug.Log("タグが一致しません…Tagは" + sendobj.tag);
                break;
        }
    }

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

    //マップにデフォルトでランダムな肉を設置する
    private int SetRandMeat(int meatCount)
    {
        for (int i = 0; i < meatCount; i++)
        {
            int Randampnum = Random.Range(0, maps.Count);
            int RandamMeatNum = Random.Range(0, m_Meats.Count);
            var SetMapPos = maps[Randampnum].gameObject.transform.position;
            var obj = Instantiate(m_Meats[RandamMeatNum], new Vector3(SetMapPos.x, SetMapPos.y, -5), m_Meats[RandamMeatNum].gameObject.transform.rotation);
            bool IsGeneration = true;

            //------周りのブロックの置けるか検知------//

            //レイに接触したものが入る
            RaycastHit raycastHit;
            //子供を全部取得
            foreach (Transform childTransform in obj.transform)
            {
                //長さ
                int Distance = 100;
                //子供からレイを発射
                Ray Childray = new Ray(childTransform.gameObject.transform.position, new Vector3(0, 0, Distance));
                //レイを飛ばしてキャスト
                if (Physics.Raycast(Childray, out raycastHit))
                {
                    Debug.Log("子供の下にあるのは" + raycastHit.collider.gameObject);
                    //設置不可
                    if (!Installation_Try(raycastHit.collider.gameObject))
                    {
                        Debug.Log("！！！子供が被ってるんでダメです！！！");
                        IsGeneration = false;
                    }
                }
                else
                {
                    Debug.Log("！！！どっかがマップに重なってないよ！！！");
                    IsGeneration = false;
                }

                Debug.Log("！！！設置可能！！！");

                //-------------------------------------//
                if (IsGeneration) {
                    Send_GameMaster(obj);

                    obj.tag = "Meat_Installed";
                    Transform Children = obj.gameObject.transform;
                    foreach (Transform ctf in Children.transform)
                    {
                        ctf.gameObject.tag = "Meat_Installed";
                    }
                    //マウスでコントロールするためのスクリプトを削除
                    Destroy(obj.GetComponent<MeatController>());
                    maps[Randampnum].gameObject.GetComponent<Mapchip>().m_Installed = true;
                }
                else
                {
                    Destroy(obj);
                }
            }
        }
        return 0;
    }
    private bool CheckLocate()
    {
        return false;
    }
}
