#include "baselib.hpp"
#include "GraphLib.hpp"

int main(void) {
    // ======================================== View 1 ========================================
    Button nothing_button(-490, -290, "Nothing", 40);

    Button show_view2_button(0,  100, "Coordinate Systems", 30);
    Button show_view3_button(0,    0, "Sphere",             30);
    Button exit_button      (0, -100, "Exit",               30);

    show_view2_button.set_centered(true);
    show_view3_button.set_centered(true);
    exit_button.      set_centered(true);

    WindowView view1(4, &show_view2_button, &show_view3_button, &exit_button, &nothing_button);
    // ========================================================================================

    // ======================================== View 2 ========================================
    Vector second_hand(0, 0, 0, 100);
    second_hand.set_fill_color(Color::Red);

    Vector minute_hand(0, 0, 0, 75);
    minute_hand.set_fill_color(Color::Red);

    Vector vector(40, 40, 100, 100);

    CoordinateSystem system1(100, 300, CoordinateSystem::AxisY_Direction::UP, CoordinateSystem::AxisX_Direction::RIGHT);
    system1.extend_objects({&second_hand, &minute_hand});

    CoordinateSystem system2(900, 300, CoordinateSystem::AxisY_Direction::DOWN, CoordinateSystem::AxisX_Direction::LEFT);
    system2.set_show_axis(true);
    system2.append_object(&vector);

    Button back_button(0, -250, "Back", 30, Button::Button_Type::ELLIPSE);
    back_button.set_centered(true);

    WindowView view2(4, &back_button, &system1, &system2, &vector);
    // ========================================================================================

    // ======================================== View 3 ========================================
    Scene scene (-500, -300, 1000, 600);

    scene.extend_spheres({
        new Sphere(Point3D(-3.0,  0.0, -16.0), 2, EMERALD),
        new Sphere(Point3D(-1.0, -1.5, -12.0), 2, MIRROR ),
        new Sphere(Point3D( 1.5, -0.5, -18.0), 3, RUBIN  ),
        new Sphere(Point3D( 7.0,  5.0, -18.0), 4, MIRROR )
    });
    scene.extend_lights({
        new Light (Point3D(-20, 20,  20), 1.5),
        new Light (Point3D( 30, 50, -25), 1.8),
        new Light (Point3D( 30, 20,  30), 1.7)
    });

    WindowView view3(2, &scene, &back_button);
    // ========================================================================================

    Window window(1000, 600);
    window.set_coordinate_system_type(CoordinateSystem::Type::CENTER);
    window.extend_views({ &view1, &view2, &view3 });
    window.show_view(&view1);

    bool update_clock  = true;
    auto button_presed = Event::MouseEvent::Button_Type::NONE;

    Clock clock(15);
    while (window.is_open()) {
        // ==================== Window Events ====================
        bool wait_click = false;
        Event event;
        while (window.poll_event(&event)) {
            switch (event.m_type) {
                case Event::WINDOW_CLOSED:
                    window.close();
                    break;
                
                case Event::MOUSE_BUTTON_PRESSED: {
                    button_presed = event.mouse.m_button;

                    Point2D point = window.get_system()->pixel_to_point(event.mouse.m_pos);

                    if (back_button.is_pressed(point, button_presed)) {
                        window.show_view(&view1);
                        wait_click = true;
                    }

                    if (show_view2_button.is_pressed(point, button_presed)) {
                        window.show_view(&view2);
                        wait_click = true;
                    }

                    if (show_view3_button.is_pressed(point, button_presed)) {
                        window.show_view(&view3);
                        wait_click = true;
                    }

                    if (exit_button.is_pressed(point, button_presed)) window.close();

                    break;
                }
                
                case Event::MOUSE_BUTTON_RELEASED:
                    button_presed = Event::MouseEvent::Button_Type::NONE;
                    break;
            }

            if (!wait_click && button_presed == Event::MouseEvent::Button_Type::LEFT  && (event.m_type == Event::MOUSE_MOVED || event.m_type == Event::MOUSE_BUTTON_PRESSED)) {
                if (!vector.m_hidden) vector.m_endPoint = system2.pixel_to_point(event.mouse.m_pos);
            }

            if (!wait_click && button_presed == Event::MouseEvent::Button_Type::RIGHT && (event.m_type == Event::MOUSE_MOVED || event.m_type == Event::MOUSE_BUTTON_PRESSED)) {
                vector.move_to_point(system2.pixel_to_point(event.mouse.m_pos));
            }
        }
        // =======================================================

        if (second_hand.m_hidden == false && update_clock && clock.get_elapsed_seconds() > 1) {
            second_hand.rotate(-360.0 / (60     ));
            minute_hand.rotate(-360.0 / (60 * 60));

            clock.restart();
        }

        // ==================== Drawing Objects ====================
        window.clear();

        system1.set_show_axis(!view2.m_hidden);
        system2.set_show_axis(!view2.m_hidden);
        if (!view2.m_hidden) window.draw_window_coordinate_system();

        window.draw_added_objects();

        window.display();
        // =========================================================
    }

    return 0;
}
