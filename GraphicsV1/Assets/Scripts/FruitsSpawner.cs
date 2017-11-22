using System;
using System.Threading;
using UnityEngine;
using Random = System.Random;
using UnityRandom = UnityEngine.Random;

public class FruitsSpawner : MonoBehaviour
{
    public GameObject[] Fruits;
    public BoxCollider SpawnArea;

    private Timer _timer;
    private Random _random = new Random();

	// Use this for initialization
	void Start () {
        //_timer = new Timer(TimerCallback, null, TimeSpan.FromSeconds(2), TimeSpan.FromSeconds(5));
	    Invoke("TimerCallback", 5);
        if (SpawnArea == null)
            throw new ArgumentException("SpawnArea is null");
    }

    void TimerCallback()
    {
        var x = SpawnArea.bounds.min.x + UnityRandom.value * SpawnArea.size.x;
        var y = SpawnArea.bounds.min.y + UnityRandom.value * SpawnArea.size.y;
        var z = SpawnArea.bounds.min.z + UnityRandom.value * SpawnArea.size.z;
        Instantiate(Fruits[_random.Next(Fruits.Length)], new Vector3(x, y, z), UnityRandom.rotation);
        Invoke("TimerCallback", 5);
    }

    // Update is called once per frame
	void Update () {
		
	}
}
