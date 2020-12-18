using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class RubyController : MonoBehaviour {
    public int maxHealth = 5;
    int currentHealth;
    public int health {
        get {
            return currentHealth;
        }
    }

    Rigidbody2D rigidbody2d;

    float horizontal, vertical;
    public float horizontalSpeed = 3f, verticalSpeed = 3f;

    public float timeInvincible = 2.0f;
    bool isInvincible;
    float invincibleTimer;

    // Start is called before the first frame update
    void Start() {
        rigidbody2d = GetComponent<Rigidbody2D>();

        currentHealth = maxHealth - 2;
    }

    // Update is called once per frame
    void Update() {

        horizontal = Input.GetAxis("Horizontal");
        vertical = Input.GetAxis("Vertical");

        if (isInvincible)
        {
            invincibleTimer -= Time.deltaTime;
            if (invincibleTimer < 0) {
                isInvincible = false;
            }
        }
    }

    void FixedUpdate() {
        float frameTime = Time.deltaTime;

        Vector2 position = rigidbody2d.position;
        position.x += horizontalSpeed * horizontal * frameTime;
        position.y += verticalSpeed * vertical * frameTime;

        rigidbody2d.MovePosition(position);
    }

    public void ChangeHealth(int amount) {
        if (amount < 0)
        {
            if (isInvincible)
                return;
            
            isInvincible = true;
            invincibleTimer = timeInvincible;
        }

        currentHealth = Mathf.Clamp(currentHealth + amount, 0, maxHealth);
        Debug.Log("Health: " + currentHealth + "/" + maxHealth);
    }
}
