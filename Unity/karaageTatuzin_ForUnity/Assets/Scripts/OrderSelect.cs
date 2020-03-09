using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
public class OrderSelect : MonoBehaviour
{
    //肉の在庫確認のためのゲームマスター
    [SerializeField] private GameMaster m_GameMaster;
    //オーダーの確認のためのオーダータイマー
    [SerializeField] private OrderTimer m_OrderTimer;


    //肉の在庫保存用クラス
    private class Meats
    {
        public int Meat_1x1;
        public int Meat_1x2;
        public int Meat_2x2;
        public int Meat_3x3;
        public int Meat_L;

        public static explicit operator Meats(GameMaster.Meats v)
        {
            throw new NotImplementedException();
        }
    }

    //現在の選要望数
    private class DemandCount
    {
        public float Max_1x1;
        public float Max_1x2;
        public float Max_2x2;
        public float Max_3x3;
        public float Max_L;

    }


    //在庫保管
    private Meats m_Meats = new Meats();
    //要望数実態
    private DemandCount m_demand = new DemandCount();

    //選択された時のイベント
    public void Selected()
    {
        GetStock();
        GetOrder();

        //比較して大丈夫だったらオーダー完了

    }

    //ゲームマスターから在庫をとってくる
    private void GetStock()
    {
        var MasterMeat = m_GameMaster.GetMeats();
        m_Meats.Meat_1x1 = MasterMeat.Meat_1x1;
        m_Meats.Meat_1x2 = MasterMeat.Meat_1x2;
        m_Meats.Meat_2x2 = MasterMeat.Meat_2x2;
        m_Meats.Meat_3x3 = MasterMeat.Meat_3x3;
        m_Meats.Meat_L = MasterMeat.Meat_L;
    }
    //オーダーの選択されたオーダーの確認
    private void GetOrder()
    {
        var Order = m_OrderTimer.GetNowDemandCount();
        m_demand.Max_1x1 = Order.Max_1x1;
        m_demand.Max_1x1 = Order.Max_1x2;
        m_demand.Max_1x1 = Order.Max_2x2;
        m_demand.Max_1x1 = Order.Max_3x3;
        m_demand.Max_1x1 = Order.Max_L;
    }
    //比較<返り値は大丈夫か>
    private bool Comparison()
    {
        return false;
    }
}
