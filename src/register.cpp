// Copyright 2024 OMObuan

#include <player.h>
#include <register.h>

#include "godot_cpp/core/class_db.hpp"
#include "godot_cpp/core/defs.hpp"
#include "godot_cpp/godot.hpp"

void initialize_godot_module(godot::ModuleInitializationLevel p_level) {
    if (p_level != godot::MODULE_INITIALIZATION_LEVEL_SCENE) {
        return;
    }

    godot::ClassDB::register_class<godot::Player>();
}

void uninitialize_godot_module(godot::ModuleInitializationLevel p_level) {
    if (p_level != godot::MODULE_INITIALIZATION_LEVEL_SCENE) {
        return;
    }
}

extern "C" {
GDExtensionBool GDE_EXPORT
godot_library_init(GDExtensionInterfaceGetProcAddress p_get_proc_address,
                   GDExtensionClassLibraryPtr const p_library,
                   GDExtensionInitialization* r_initialization) {
    godot::GDExtensionBinding::InitObject init_obj(p_get_proc_address,
                                                   p_library, r_initialization);

    init_obj.register_initializer(initialize_godot_module);
    init_obj.register_terminator(uninitialize_godot_module);
    init_obj.set_minimum_library_initialization_level(
        godot::MODULE_INITIALIZATION_LEVEL_SCENE);

    return init_obj.init();
}
}
