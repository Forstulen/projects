using UnityEngine;
using System.Collections;

public class GameEngine : MonoBehaviour {

    public GameObject ball;
    public Texture2D rules;
    private int p1Score;
    private int AIScore;
    private bool gameStart;
    private int power;

	// Use this for initialization
	void Start () {
        this.p1Score = 0;
        this.AIScore = 0;
        this.power = 1;
        this.gameStart = false;
	}
	
	// Update is called once per frame
	void Update () {
        if (this.gameStart && !GameObject.Find("PongBall") && !GameObject.Find("PongBall(Clone)"))
            Instantiate(this.ball);
        if (this.p1Score >= 7 || this.AIScore >= 7)
        {
            this.gameStart = false;
            this.p1Score = 0;
            this.AIScore = 0;
            this.power = 1;
            audio.Play();
        }
	}

    void updateScorePlayer()
    {
        ++this.p1Score;
        if (this.p1Score % 3 == 0)
            ++this.power;
    }

    void updateScoreAI()
    {
        ++this.AIScore;
    }

    void checkPower()
    {
        if (this.power > 0)
        {
            if (GameObject.Find("PongBall(Clone)"))
                GameObject.Find("PongBall(Clone)").GetComponent("BallScript").SendMessage("increaseSpeed");
            --this.power;
        }
    }

    void OnGUI()
    {
        if (GUI.Button(new Rect(10, 100, 150, 50), "Start Game"))
            this.gameStart = true;
        if (GUI.Button(new Rect(10, 160, 150, 50), "Quit Game"))
            Application.Quit();
        if (GUI.Button(new Rect(10, 220, 150, 50), "Easier ?"))
            if (GameObject.Find("Ennemy Racket"))
                GameObject.Find("Ennemy Racket").GetComponent("AIScript").SendMessage("decreaseDifficulty");
        if (GUI.Button(new Rect(10, 280, 150, 50), "Harder ?"))
            if (GameObject.Find("Ennemy Racket"))
                GameObject.Find("Ennemy Racket").GetComponent("AIScript").SendMessage("increaseDifficulty");

        GUI.TextField(new Rect(Screen.width / 4 * 1, Screen.height - 50, 100, 20), "Goals " + this.p1Score.ToString());
        GUI.TextField(new Rect(Screen.width / 4 * 1, Screen.height - 30, 200, 20), "Kinestesic Power " + this.power.ToString());
        GUI.TextField(new Rect(Screen.width / 4 * 3 - 100, Screen.height - 50, 100, 20), "Fails " + this.AIScore.ToString());

        /*if (!this.gameStart)
            GUI.Box(new Rect(Screen.width / 2 - 128 / 2, Screen.height / 2 - 128 / 2, 128, 128), this.gameOver);*/
        GUI.Box(new Rect(Screen.width / 4 * 3, 10, 256, 256), this.rules);
    }
}
