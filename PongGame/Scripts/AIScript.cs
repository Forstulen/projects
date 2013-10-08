using UnityEngine;
using System.Collections;

public class AIScript : MonoBehaviour {

    public float speed;
    private GameObject target;

	// Use this for initialization
	void Start () {
	
	}
	
	// Update is called once per frame
	void Update () {
        if (!target)
        {
            target = GameObject.Find("PongBall");
            if (!target)
                target = GameObject.Find("PongBall(Clone)");
        }
        else
        {
            float positionZ = target.transform.position.z;
            float positionX = target.transform.position.x;

            if (positionZ != this.gameObject.transform.position.z && positionX > 0.0f)
                this.transform.Translate(0, 0, (positionZ - this.gameObject.transform.position.z) * speed / 10.0f);
        }
	}

    void decreaseDifficulty()
    {
        if (this.speed >= 0.2f)
            this.speed -= 0.1f;
    }

    void increaseDifficulty()
    {
        if (this.speed <= 10.0f)
            this.speed += 0.1f;
    }
}
