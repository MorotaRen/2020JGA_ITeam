using System.Collections;
using System.Collections.Generic;
using UnityEngine;


/// -----------------------------------------------<summary>
/// 肉が選択状態で動く時に必要なスクリプト
/// </summary>-----------------------------------------------
public class MeatController : MonoBehaviour
{
    //移動用座標Zの定数
    const int m_MovePosToZ = -5;

    private void Update()
    {
        //マウスポジションをスクリーン座標からワールド座標に変換する
        Vector3 WorldPos = Camera.main.ScreenToWorldPoint(Input.mousePosition);
        //座標更新
        this.transform.position = new Vector3(WorldPos.x,WorldPos.y,m_MovePosToZ);
    }
}
