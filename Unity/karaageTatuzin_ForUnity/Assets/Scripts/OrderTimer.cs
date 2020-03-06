using System.Collections;
using System.Collections.Generic;
using UnityEngine;

/// -----------------------------------------------<summary>
/// オーダータイマー
/// </summary>-----------------------------------------------

using UnityEngine.UI;

public class OrderTimer : MonoBehaviour
{
    //制限時間
    public float m_MaxTimer { get; set; }

    //現在時間
    private float m_NowTimer;

    //タイマー表示テキスト
    [SerializeField] private Image m_TimerImage;

    //要望数(設定)
    class Set_DemandCount
    {
        public const float Max_1x1 = 5;
        public const float Max_1x2 = 5;
        public const float Max_2x2 = 5;
        public const float Max_3x3 = 5;
        public const float Max_L = 5;

        public float GetMax1x1()
        {
            return Max_1x1;
        }

    }

    //現在の選要望数
    class Now_DemandCount
    {
        public float Max_1x1;
        public float Max_1x2;
        public float Max_2x2;
        public float Max_3x3;
        public float Max_L;

    }




    //要望数
    private Now_DemandCount m_Now_DemandCount = new Now_DemandCount();
    private Set_DemandCount m_Set_DemandCount = new Set_DemandCount();

    private void Start()
    {
        m_MaxTimer = 25;
        m_NowTimer = m_MaxTimer;
    }
    private void Update()
    {
        TimerDown();
        m_TimerImage.fillAmount = m_NowTimer / m_MaxTimer;
    }

    //ランダムに個数を設定
    void Rand_SetDemandCount()
    {
        m_Now_DemandCount.Max_1x1 = Random.Range(0, m_Set_DemandCount.GetMax1x1());
    }
    //制限時間ダウン
    void TimerDown()
    {
        m_NowTimer -= 1 * Time.deltaTime;
    }

}
