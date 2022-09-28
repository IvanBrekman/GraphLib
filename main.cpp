#include "baselib.hpp"
#include "GraphLib.hpp"

int main(void) {
    // ======================================== View 1 ========================================
    Button show_view2_button(0,  100, "Coordinate Systems", 30);
    Button show_view3_button(0,    0, "Sphere",             30);
    Button exit_button      (0, -100, "Exit",               30);

    Button nothing_button(-490, -290, "Nothing", 40);

    show_view2_button.set_centered();
    show_view3_button.set_centered();
    exit_button.      set_centered();

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
    system2.set_draw_status(true);
    system2.append_object(&vector);

    Button back_button(0, -250, "Back", 30, Button::Button_Type::ELLIPSE);
    back_button.set_centered();

    WindowView view2(4, &back_button, &system1, &system2, &vector);
    // ========================================================================================

    // ======================================== View 3 ========================================
    Circle sphere(0, 0, 100, true);
    sphere.set_fill_color(Color::Red);

    WindowView view3(2, &back_button, &sphere);
    // ========================================================================================

    Window window(1000, 600);
    window.set_coordinate_system_type(Window::Coordinate_System_Type::CENTER);
    window.extend_views({ &view1, &view2, &view3 });
    window.show_view(&view1);

    bool update_clock = true;
    Event::MouseEvent::Button_Type button_presed = Event::MouseEvent::Button_Type::NONE;

    Clock clock(15);
    while (window.is_open()) {
        // ==================== Window Events ====================
        bool wait_click = false;
        Event event;
        while (window.poll_event(&event)) {
            switch (event.type) {
                case Event::WINDOW_CLOSED:
                    window.close();
                    break;
                
                case Event::MOUSE_BUTTON_PRESSED: {
                    button_presed = event.mouse.button;

                    Point2D point = window.get_system()->pixel_to_point(event.mouse.pos);

                    if (back_button.      is_pressed(point, button_presed)) {
                        window.show_view(&view1);
                        window.color = Color::White;
                        wait_click   = true;
                    }

                    if (show_view2_button.is_pressed(point, button_presed)) {
                        window.show_view(&view2);
                        wait_click = true;
                    }

                    if (show_view3_button.is_pressed(point, button_presed)) {
                        window.show_view(&view3);
                        window.color = Color::Black;
                        wait_click   = true;
                    }

                    if (exit_button.is_pressed(point, button_presed)) window.close();

                    break;
                }
                
                case Event::MOUSE_BUTTON_RELEASED:
                    button_presed = Event::MouseEvent::Button_Type::NONE;
                    break;
            }

            if (!wait_click && button_presed == Event::MouseEvent::Button_Type::LEFT  && (event.type == Event::MOUSE_MOVED || event.type == Event::MOUSE_BUTTON_PRESSED)) {
                if (!vector.hidden) vector.end_point = system2.pixel_to_point(event.mouse.pos);
            }

            if (!wait_click && button_presed == Event::MouseEvent::Button_Type::RIGHT && (event.type == Event::MOUSE_MOVED || event.type == Event::MOUSE_BUTTON_PRESSED)) {
                vector.move_to_point(system2.pixel_to_point(event.mouse.pos));
            }
        }
        // =======================================================

        if (second_hand.hidden == false && update_clock && clock.get_elapsed_seconds() > 1) {
            second_hand.rotate(-360.0 / (60     ));
            minute_hand.rotate(-360.0 / (60 * 60));

            clock.restart();
        }

        // ==================== Drawing Objects ====================
        window.clear();

        system1.set_draw_status(!view2.hidden);
        system2.set_draw_status(!view2.hidden);
        if (!view2.hidden) window.draw_window_coordinate_system();

        window.draw_added_objects();

        window.display();
        // =========================================================
    }

    return 0;
}
