using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Meat_1x2 : MonoBehaviour
{
    [SerializeField] private int[,] size =  {
                                            {1,1},
                                            {0,0}
                                            };

    private void Start()
    {
        Debug.Log(size);
    }

    //右90°回転
    void RightRotation90()
    {
        CenterRotation();
        RightDownRotation();
    }
    //中心横軸回転
    void CenterRotation()
    {
        var work = size.Clone() as int[,];
        int xLeng = work.GetLength(0);
        for (int x = 1;x < xLeng; x++)
        {
            for (int y = 0;y < work.GetLength(1);y++)
            {
                int temp = work[x, y];
                work[x, y] = work[xLeng - x - 1,y];
                work[xLeng - x - 1,y] = temp;
            }
        }
        size = work;
    }
    //右斜め下体格回転
    void RightDownRotation()
    {
        var work = size.Clone() as int[,];
        for (int y = 1; y < work.GetLength(1); y++)
        {
            for (int x = 0; x < y; x++)
            {
                int temp = work[x, y];
                work[x, y] = work[y, x];
                work[y, x] = temp;
            }
        }
        size = work;
    }
}
