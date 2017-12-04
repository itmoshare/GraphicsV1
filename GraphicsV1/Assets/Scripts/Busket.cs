using UnityEngine;
using UnityEngine.Tilemaps;

public class Busket : MonoBehaviour
{
    public float MoveSpeed = 10.0f;

    private Rigidbody rb;

    // Use this for initialization
    void Start () {
        rb = GetComponent<Rigidbody>();
    }
	
	// Update is called once per frame
	void Update () {
	    var x = Input.GetAxis("Horizontal") * Time.deltaTime * MoveSpeed;

        rb.MovePosition(rb.position + new Vector3(x, 0, 0));
    }

    void OnTriggerEnter(Collider other)
    {
        if (other.CompareTag("Fruit"))
        {
            GameObject.Destroy(other.gameObject);
        }
    }
}
