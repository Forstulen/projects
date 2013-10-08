using UnityEngine;
using System.Collections;

public class BallScript : MonoBehaviour {

    public float speed;
    public GameObject explosion;
    private bool newSpeed;
    private float savedTime;


	// Use this for initialization
	void Start () {
        this.newSpeed = false;
	}
	
	// Update is called once per frame
	void Update () {
        if (this.newSpeed && this.savedTime > 0.0f)
        {
            this.transform.Translate(new Vector3(0, 0, 1) * speed * 2.0f  * Time.deltaTime);
            this.savedTime -= Time.deltaTime;
        }
        else
        {
            this.newSpeed = false;
            this.savedTime = 0.0f;
            this.transform.Translate(new Vector3(0, 0, 1) * speed * Time.deltaTime);
        }
        //Debug.DrawRay(this.transform.position, this.transform.forward * 100, Color.cyan);
	}

    void OnTriggerEnter(Collider obj)
    {
        float angle = Vector3.Angle(this.transform.forward, new Vector3(-this.transform.forward.x, this.transform.forward.y, this.transform.forward.z));
        float coeff = (obj.transform.position.z - this.gameObject.transform.position.z) / (obj.gameObject.transform.localScale.z / 2.0f);

        if (obj.gameObject.layer == 8)
        {
            if (this.transform.forward.x > 0)
                this.transform.Rotate(0, 180 + angle, 0);
            else
                this.transform.Rotate(0, 180 - angle, 0);
            audio.Play();
        }
        else if (obj.gameObject.layer == 9)
        {
            if (this.transform.forward.x > 0)
                this.transform.Rotate(0, 180 - angle, 0);
            else
                this.transform.Rotate(0, 180 + angle, 0);
            audio.Play();
        }
        else if (obj.gameObject.layer == 14)
        {
            if (this.transform.forward.z > 0)
                this.transform.Rotate(0, angle + coeff * 20.0f, 0);
            else
                this.transform.Rotate(0, 360 - angle - coeff * 20.0f, 0);
            audio.Play();
        }
        else if (obj.gameObject.layer == 15)
        {
            if (this.transform.forward.z > 0)
                this.transform.Rotate(0, -angle + coeff * 20.0f, 0);
            else
                this.transform.Rotate(0, angle - coeff * 20.0f, 0);
            audio.Play();
        }
        else
        {
            if (obj.gameObject.layer == 11)
                GameObject.Find("Main Camera").GetComponent("GameEngine").SendMessage("updateScorePlayer");
            else
                GameObject.Find("Main Camera").GetComponent("GameEngine").SendMessage("updateScoreAI");

            Instantiate(explosion, this.gameObject.transform.position, this.gameObject.transform.rotation);
            Destroy(this.gameObject, 0.10f);
        }
    }

    void increaseSpeed()
    {
        this.newSpeed = true;
        this.savedTime = 3.0f;
    }
}
