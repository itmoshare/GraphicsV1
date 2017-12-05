using System;
using JetBrains.Annotations;
using UnityEngine;

public class MainController : MonoBehaviour
{
    [NotNull]
    public HitPointsController HitPointsController;

    [NotNull]
    public FruitsDestructor FruitsDestructor;

    [NotNull]
    public FruitsSpawner FruitsSpawner;

    public float SpawnHardLevelInc = 0.5f;
    public float GravityHardInc = 0.1f;
    public float StartSpawnHardLevel = 4.0f;
    public float StartGravityHardLevel = 4.0f;

    void OnLevelWasLoaded()
    {
        if (HitPointsController == null) throw new NullReferenceException("HitPointsController");
        if (FruitsDestructor == null) throw new NullReferenceException("FruitsDestructor");
        if (FruitsSpawner == null) throw new NullReferenceException("FruitsSpawner");
    }

    void Start ()
    {
        FruitsDestructor.FruitDestroyed += FruitDestroyed;

        Physics.gravity = new Vector3(0, -StartGravityHardLevel, 0);
        FruitsSpawner.SpawnRate = StartSpawnHardLevel;

        InvokeRepeating("IncHardLevel", 5, 5);
	}

    private void IncHardLevel()
    {
        Physics.gravity += new Vector3(0, -GravityHardInc, 0);
        FruitsSpawner.SpawnRate -= SpawnHardLevelInc;
    }

    private void FruitDestroyed(bool b)
    {
        if (!b)
        {
            HitPointsController.Dec();
            if (HitPointsController.CurValue == 0)
                Time.timeScale = 0;
        }
    }

    private static MainController _cached;

    public static MainController GetInstance()
    {
        if (_cached != null)
            return _cached;
        var res = GameObject.Find("MainController");
        if (res == null) throw new ArgumentNullException("Can't find main controller object");
        _cached = res.GetComponent<MainController>();
        if (_cached == null) throw new ArgumentNullException("Can't find main controller script");
        return _cached;
    }
}
