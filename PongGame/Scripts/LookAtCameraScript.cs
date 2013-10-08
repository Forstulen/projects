using UnityEngine;
using System.Collections;

public class LookAtCameraScript : MonoBehaviour {

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
            Vector3 seekVector = new Vector3(target.transform.position.x + Random.Range(0.1f, 0.8f), target.transform.position.y + Random.Range(0.1f, 0.8f), target.transform.position.z + Random.Range(0.1f, 0.8f));

            this.transform.LookAt(seekVector);
        }
	}
}
