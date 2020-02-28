using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class StockMeats : MonoBehaviour
{
    //各肉達の在庫数
    [SerializeField] List<int> MeatStock;
    //各肉達のUI
    [SerializeField] List<GameObject> MeatUI;
    //在庫追加
    public void AddMeatStock(int id,int num)
    {
        MeatStock[id] += num;
    }
    //UIに数値設定
    void SetMeatUI()
    {
        int num = 0;
        foreach (var obj in MeatUI)
        {
            obj.GetComponent<Text>().text = MeatStock[num].ToString();
            num++;
        }
    }
    //各配置オブジェクトからレイ飛ばして接触しなかったら置くって感じにしてみるか
}
