using System.Collections;
using System.Collections.Generic;
using UnityEngine;

/// -----------------------------------------------<summary>
/// オーダータイマー
/// </summary>-----------------------------------------------

using UnityEngine.UI;

public class OrderTimer : MonoBehaviour
{
    //妨害イラスト表示時間
    [SerializeField] private const float m_OrderNotAchievedImageTime = 10.0f;
    //制限時間
    [SerializeField] private float m_MaxTimer;

    //現在時間
    private float m_NowTimer;

    //アニメーションClip
    [SerializeField] private AnimationClip m_ImageAnimationClip;
    //タイマー表示テキスト
    [SerializeField] private Image m_TimerImage;

    //オーダー表示テキスト
    [SerializeField] private List<Text> m_OrderText;

    //オーダー達成状態
    [SerializeField] private bool m_OrderComplete;

    //リキャスト
    [SerializeField] private bool m_ReCast;

    //オーダー未達成時の妨害イラスト
    [SerializeField] private GameObject m_OrderNotAchievedImage;

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
        public float GetMax1x2()
        {
            return Max_1x2;
        }
        public float GetMax2x2()
        {
            return Max_2x2;
        }
        public float GetMax3x3()
        {
            return Max_3x3;
        }
        public float GetMaxL()
        {
            return Max_L;
        }
    }

    //現在の選要望数
    public class Now_DemandCount
    {
        public float Max_1x1;
        public float Max_1x2;
        public float Max_2x2;
        public float Max_3x3;
        public float Max_L;

    }

    //実態
    public Now_DemandCount m_Now_DemandCount = new Now_DemandCount();
    private Set_DemandCount m_Set_DemandCount = new Set_DemandCount();

    private void Start()
    {
        m_MaxTimer = 20;
        m_NowTimer = m_MaxTimer;
        Rand_SetDemandCount();
        Set_Order();
    }
    private void Update()
    {
        if (!m_ReCast)
        {
            TimerDown();
            //FILLの設定
            m_TimerImage.fillAmount = m_NowTimer / m_MaxTimer;
        }
        //0になったらタイマー初期化しようね！
        if (m_NowTimer <= 0)
        {
            m_NowTimer = m_MaxTimer;
            if (!m_OrderComplete)
            {
                m_OrderNotAchievedImage.SetActive(true);
                m_OrderNotAchievedImage.GetComponent<Animation>().clip = m_ImageAnimationClip;
                m_OrderNotAchievedImage.GetComponent<Animation>().Play();
                m_ReCast = true;
                Invoke("Stop_OrderNotAchievedImage", m_OrderNotAchievedImageTime);
            }
        }
    }
    //現在のオーダーをテキストに表示
    void Set_Order()
    {
        m_OrderText[0].text = ((int)m_Now_DemandCount.Max_1x1).ToString();
        m_OrderText[1].text = ((int)m_Now_DemandCount.Max_1x2).ToString();
        m_OrderText[2].text = ((int)m_Now_DemandCount.Max_2x2).ToString();
        m_OrderText[3].text = ((int)m_Now_DemandCount.Max_3x3).ToString();
        m_OrderText[4].text = ((int)m_Now_DemandCount.Max_L).ToString();
    }
    //ランダムに個数を設定
    void Rand_SetDemandCount()
    {
        m_Now_DemandCount.Max_1x1 = Random.Range(0, m_Set_DemandCount.GetMax1x1());
        m_Now_DemandCount.Max_1x2 = Random.Range(0, m_Set_DemandCount.GetMax1x2());
        m_Now_DemandCount.Max_2x2 = Random.Range(0, m_Set_DemandCount.GetMax2x2());
        m_Now_DemandCount.Max_3x3 = Random.Range(0, m_Set_DemandCount.GetMax3x3());
        m_Now_DemandCount.Max_L = Random.Range(0, m_Set_DemandCount.GetMaxL());
    }
    //制限時間ダウン
    void TimerDown()
    {
        m_NowTimer -= 1 * Time.deltaTime;
    }
    //妨害イラストの停止
    void Stop_OrderNotAchievedImage()
    {
        m_OrderNotAchievedImage.SetActive(false);
        m_ReCast = false;
        Set_Order();
    }
    //オーダーのゲッター
    public Now_DemandCount GetNowDemandCount()
    {
        return m_Now_DemandCount;
    }
}
