#include "baselib.hpp"
#include "GraphLib.hpp"

int main(void) {
    Window     window(1000, 600);
    WindowView view1, view2;

    // ======================================== View 1 ========================================
    Button nothing_button(-490, -290, "Nothing", 40);
    nothing_button.set_name("Nothing");

    Button show_view2_button(0,  0, "Sphere", 30);
    Button exit_button      (0, -50, "Exit",   30);

    show_view2_button.set_name("Sphere").set_centered(false);
    show_view2_button.set_on_click_func([&window, &view2] (const Event&, const Eventable&) -> void { window.show_view(&view2); });

    exit_button.set_name("Exit").set_centered(true);
    exit_button.set_on_click_func([&window] (const Event&, const Eventable&) -> void { window.close(); });
    // exit_button.set_on_click_func(ON_EVENT_FUNC(&window, window.close();));

    view1.set_objects({&show_view2_button, &exit_button, &nothing_button});
    // ========================================================================================

    // ======================================== View 2 ========================================
    Scene scene(-500, -300, 1000, 600, "src/images/back.jpg");

    scene.extend_scene_objects({
        new Sphere(Vec3f(-3.0,  0.0, -16.0), 2, EMERALD),
        new Sphere(Vec3f(-1.0, -1.5, -12.0), 2, MIRROR ),
        new Sphere(Vec3f( 2.5, -0.5, -18.0), 3, RUBIN  ),
        new Sphere(Vec3f( 7.0,  5.0, -18.0), 4, MIRROR ),
        new Plane (Vec3f(0, 1, 0), -4,  RUBIN,   Vec2f(-10, 10),      Vec2f(D_MIN, D_MAX),  Vec2f(-30, -10)),
        new Plane (Vec3f(1, 0, 0), -10, EMERALD, Vec2f(D_MIN, D_MAX), Vec2f(-10, 20),       Vec2f(-30, 10)),
        new Plane (Vec3f(0, 0, 1), -40, RUBIN,   Vec2f(0, 30),        Vec2f(-10, 10),       Vec2f(D_MIN, D_MAX)),
    });
    scene.extend_lights({
        new Light (Vec3f(-20, 20,  20), 1.5),
        new Light (Vec3f( 30, 50, -25), 1.8),
        new Light (Vec3f( 30, 20,  30), 1.7)
    });

    Button back_button(0, -250, "Back", 30, Button::Button_Type::ELLIPSE);
    back_button.set_centered(true);
    back_button.set_on_click_func([&window, &view1] (const Event&, const Eventable&) -> void { window.show_view(&view1); });

    view2.set_objects({&scene, &back_button});
    // ========================================================================================

    window.set_coordinate_system_type(CoordinateSystem::Type::CENTER);
    window.set_coordinate_system(CoordinateSystem(500, 300, CoordinateSystem::AxisY_Direction::UP, CoordinateSystem::AxisX_Direction::LEFT));
    window.extend_views({ &view1, &view2 });
    window.show_view(&view1);

    while (window.is_open()) {
        while (window.poll_event()) {}

        window.clear();
        window.draw_window_coordinate_system();
        window.display();
    }

    return 0;
}
