﻿using System.Collections;
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



    private int[,] map;
    private int num;
    private GameObject obj;
    private List<GameObject> maps　= new List<GameObject>();

    private void Start()
    {
        map = new int[XSize, YSize];
        GenerationPos = StartPos;
        MapCreate();
    }

    private void Update()
    {

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
        }
    }
}
