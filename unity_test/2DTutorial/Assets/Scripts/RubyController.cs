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

    Animator animator;
    Vector2 lookDirection = new Vector2(1,0);

    public GameObject projectilePrefab;
    public float force = 300;

    // Start is called before the first frame update
    void Start() {
        animator = GetComponent<Animator>();

        rigidbody2d = GetComponent<Rigidbody2D>();

        currentHealth = maxHealth - 2;
    }

    // Update is called once per frame
    void Update() {

        if(transform.position.magnitude > 1000.0f) {
            Destroy(gameObject);
        }

        horizontal = Input.GetAxis("Horizontal");
        vertical = Input.GetAxis("Vertical");

        Vector2 move = new Vector2(horizontal, vertical);
        
        if(!Mathf.Approximately(move.x, 0.0f) || !Mathf.Approximately(move.y, 0.0f))
        {
            lookDirection.Set(move.x, move.y);
            lookDirection.Normalize();
        }
                
        animator.SetFloat("Look X", lookDirection.x);
        animator.SetFloat("Look Y", lookDirection.y);
        animator.SetFloat("Speed", move.magnitude);

        if (isInvincible)
        {
            invincibleTimer -= Time.deltaTime;
            if (invincibleTimer < 0) {
                isInvincible = false;
            }
        }

        if(Input.GetKeyDown(KeyCode.C)) {
            Launch();
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
        UIHealthBar.instance.SetValue(currentHealth / (float)maxHealth);
    }

    void Launch() {
        GameObject projectileObject = Instantiate(projectilePrefab,
        rigidbody2d.position + Vector2.up * 0.5f, Quaternion.identity);

        Projectile projectile = projectileObject.GetComponent<Projectile>();
        projectile.Launch(lookDirection, force);

        animator.SetTrigger("Launch");
    }
}
