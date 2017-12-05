using System;
using System.Linq;
using JetBrains.Annotations;
using UnityEngine;

public class HitPointsController : MonoBehaviour
{
    public GameObject HitPointObject;

    public int MaxValue = 5;

    public float Delimiter = 10;

    [NotNull]
    private GameObject[] _objectsCollection = Enumerable.Empty<GameObject>().ToArray();

    public int CurValue { get; private set; }

	// Use this for initialization
    [ExecuteInEditMode]
	void Start ()
    {
        CurValue = MaxValue;
	    if (HitPointObject == null) throw new ArgumentNullException("HitPointObject");
	    _objectsCollection = 
            Enumerable.Range(0, MaxValue)
            .Select(x => Instantiate(HitPointObject, transform.position + new Vector3(Delimiter * x, 0, 0), Quaternion.identity, transform))
            .ToArray();
	}

    public bool Dec()
    {
        if (CurValue == 0)
            return false;
        CurValue--;
        Destroy(_objectsCollection[CurValue]);
        return true;
    }
}
