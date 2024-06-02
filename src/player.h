// Copyright 2024 OMObuan

#pragma once

#include <rename_types.h>

#include <godot_cpp/classes/area2d.hpp>
#include <godot_cpp/classes/physics_body2d.hpp>

#include "godot_cpp/classes/node2d.hpp"
#include "godot_cpp/variant/vector2.hpp"

namespace godot {

class Player : public Area2D {
    GDCLASS(Player, Area2D)

    typedef Node2D *Node2DPointer;
    typedef Vector2 const &Vector2ConstReference;

 public:
    Player();
    ~Player();

    void _process(f64 delta) override;

    void _ready() override;

    void on_body_entered(Node2DPointer body);

    void start(Vector2ConstReference position);

 protected:
    static void _bind_methods();

 private:
    Vector2 screen_size{};
    f64 speed{400.};
};

}  // namespace godot
