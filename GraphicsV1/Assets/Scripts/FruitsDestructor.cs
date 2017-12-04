using UnityEngine;

public class FruitsDestructor : MonoBehaviour {

	// Use this for initialization
	void Start () {
		
	}
	
	// Update is called once per frame
	void Update () {
		
	}

    void OnTriggerEnter(Collider other)
    {
        if (other.CompareTag("Fruit"))
        {
            GameObject.Destroy(other.gameObject);
        }
    }
}
