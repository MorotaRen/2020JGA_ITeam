using System.Collections;
using System.Collections.Generic;
using UnityEngine;

/// -----------------------------------------------<summary>
/// マップチップの制御
/// </summary>-----------------------------------------------
public class Mapchip : MonoBehaviour
{
    //既に設置済みか
    public bool m_Installed { get; set; }

    private void Start()
    {
        m_Installed = false;
    }
}
