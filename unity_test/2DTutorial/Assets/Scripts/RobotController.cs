﻿using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class RobotController : MonoBehaviour {
    public float horizontalSpeed = 3f, verticalSpeed = 3f;
    public bool horizontal, vertical;
    public float changeTime = 3.0f;

    public ParticleSystem smoke;

    Rigidbody2D rigidbody2D;
    float timer;
    int direction = 1;

    bool broken = true;

    Animator animator;

    // Start is called before the first frame update
    void Start() {
        rigidbody2D = GetComponent<Rigidbody2D>();
        timer = changeTime;
        animator = GetComponent<Animator>();
    }

    private void Update() {
        if(!broken) {
            return;
        }

        timer -= Time.deltaTime;

        if (timer < 0) {
            direction *= -1;
            timer = changeTime;
        }
    }

    void FixedUpdate() {
        if(!broken) {
            return;
        }

        Vector2 position = rigidbody2D.position;

        if (vertical) {
            position.y += Time.deltaTime * verticalSpeed * direction;
            animator.SetFloat("Move X", 0);
            animator.SetFloat("Move Y", direction);
        } else {
            position.x += Time.deltaTime * horizontalSpeed * direction;
            animator.SetFloat("Move X", direction);
            animator.SetFloat("Move Y", 0);
        }
        
        rigidbody2D.MovePosition(position);
    }

    private void OnCollisionEnter2D(Collision2D collision) { 
        RubyController player = collision.gameObject.GetComponent<RubyController>();

        if (player != null) {
            player.ChangeHealth(-1);
        }
    }

    public void Fix() {
        broken = false;
        rigidbody2D.simulated = false;
        animator.SetTrigger("Fixed");
        smoke.Stop();
    }
}
