using System;
using UnityEngine;

public class FruitsDestructor : MonoBehaviour
{
    public event Action<bool> FruitDestroyed;

    void OnTriggerEnter(Collider other)
    {
        if (other.CompareTag("Fruit"))
        {
            Destroy(other.gameObject);
            if (FruitDestroyed != null)
                FruitDestroyed.Invoke(false);
        }
    }
}
