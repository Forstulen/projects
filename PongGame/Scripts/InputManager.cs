using UnityEngine;
using System.Collections;

public class InputManager : MonoBehaviour {

    public float speed;
    private bool up;
    private bool down;


	// Use this for initialization
	void Start () {
        this.up = true;
        this.down = true;
	}
	
	// Update is called once per frame
	void Update () {

        float value = 0;

        value = Input.GetAxis("Vertical");


        Vector3 move = new Vector3(0, 0, value * speed);

        if ((this.up && value > 0.0f) || (this.down && value < 0.0f))
            this.transform.Translate(move * Time.deltaTime);
	}

    void OnTriggerEnter(Collider obj)
    {
        if (obj.gameObject.layer == 9)
            this.up = false;
        if (obj.gameObject.layer == 8)
            this.down = false;
        else
        {
            if (Input.GetButton("Jump"))
                GameObject.Find("Main Camera").GetComponent("GameEngine").SendMessage("checkPower");
        }

    }

    void OnTriggerExit(Collider obj)
    {
        if (obj.gameObject.layer == 9)
            this.up = true;
        if (obj.gameObject.layer == 8)
            this.down = true;
    }
}
