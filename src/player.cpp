// Copyright 2024 OMObuan

#include <player.h>

#include <algorithm>
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/variant/vector2.hpp>

#include "godot_cpp/classes/animated_sprite2d.hpp"
#include "godot_cpp/core/class_db.hpp"
#include "godot_cpp/core/object.hpp"

godot::Player::Player() {}

godot::Player::~Player() {}

void godot::Player::_process(f64 delta) {
    Vector2 velocity = Vector2();
    if (Input::get_singleton()->is_action_pressed("move_right")) {
        velocity.x += 1;
    }
    if (Input::get_singleton()->is_action_pressed("move_left")) {
        velocity.x -= 1;
    }
    if (Input::get_singleton()->is_action_pressed("move_down")) {
        velocity.y += 1;
    }
    if (Input::get_singleton()->is_action_pressed("move_up")) {
        velocity.y -= 1;
    }

    if (velocity.length() > 0) {
        velocity = velocity.normalized() * speed;
        get_node<AnimatedSprite2D>("AnimatedSprite2D")->play();
    } else {
        get_node<AnimatedSprite2D>("AnimatedSprite2D")
            ->stop();  // or stop_all>(const NodePath &p_path)
    }

    set_position((get_position() + velocity * delta)
                     .clamp(Vector2(), Vector2(screen_size.x, screen_size.y)));

    if (velocity.x != 0) {
        get_node<AnimatedSprite2D>("AnimatedSprite2D")
            ->set_flip_h(velocity.x < 0);
        get_node<AnimatedSprite2D>("AnimatedSprite2D")->set_flip_v(false);
        get_node<AnimatedSprite2D>("AnimatedSprite2D")->set_animation("walk");
    }
    if (velocity.y != 0) {
        get_node<AnimatedSprite2D>("AnimatedSprite2D")
            ->set_flip_v(velocity.y > 0);
        get_node<AnimatedSprite2D>("AnimatedSprite2D")->set_animation("up");
    }
}

void godot::Player::_bind_methods() {
    ClassDB::bind_method(D_METHOD("on_body_entered", "body"),
                         &godot::Player::on_body_entered);
    ADD_SIGNAL(MethodInfo("hit"));
}

void godot::Player::_ready() {
    this->connect("body_entered", Callable(this, "on_body_entered"));
    screen_size = get_viewport_rect().size;
    hide();
}

void godot::Player::on_body_entered(Node2DPointer body) {
    hide();
    emit_signal("hit");
    get_node<CollisionObject2D>("CollisionObject2D")
        ->set_deferred("disabled", true);
}

void godot::Player::start(Vector2ConstReference position) {
    set_position(position);
    show();
    get_node<CollisionObject2D>("CollisionObject2D")
        ->set_deferred("disabled", false);
}
