#ifndef LOBUTIL_H
#define LOBUTIL_H

struct lobster_options 
{
    std::string root_src = "main.lobster";
    std::vector<std::string> program_args = {};
};

// Tags for wicked objects we may keep references to.
enum WOKIND {
    WK_SCENE, WK_ENTITY, WK_NAME_COMP, WK_CAMERA_COMP, WK_TRANSFORM_COMP, WK_RENDERPATH3,
    WK_TIMER, WK_SPRITE_FONT, WK_FONT_PARAMS, WK_HUMANOID, WK_LAYER, WK_COLLIDER, 
    WK_MATRIX, WK_ANIMATION_COMP, WK_SPHERE, WK_SPHEREINTERSECTION, WK_CAPSULE,
    WK_RIGIDBODY, WK_OBJECT_COMP, WK_HIER_COMP, WK_LIGHT_COMP

};

// A handle for a wicked object that can be passed in and out of lobster as an int2.
struct wo_handle
{
    int kind;       // WOKIND, or -WOKIND if it is an invalid handle of that kind.
    int64_t name;   // Unique id or array index for the object.
};

// A handle for a wicked object iterator.  Only valid for WOKINDS that have iterators.
struct wo_iterator
{
    int32_t kind;
    int32_t ix;   // Index (not the same as wo_handle.name)
};

// Initializes lobster, compiling the main source file if necessary, and making
// it ready to call into.
std::string run_lobster(lobster_options &args, std::function<void()> main);

// Dumps a lobster stack to stdout.
void dump_lobster_stack();

// Called at Application::FixedUpdate
void lobster_fixed_update();

void lobster_variable_update(float dt);

bool app_wants_to_quit();

// Should be called from the main loop to set whether the application is
// active and has focus.
void app_is_active(bool v);

#endif
