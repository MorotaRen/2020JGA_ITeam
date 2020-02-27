using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MeatController : MonoBehaviour
{
    private void Update()
    {
        Vector3 WorldPos = Camera.main.ScreenToWorldPoint(Input.mousePosition);
        this.transform.position = new Vector3(WorldPos.x,WorldPos.y,0);
    }
}
