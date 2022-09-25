#include "GraphLib.hpp"
#include "baselib.hpp"

void set_objects_hidden_status(std::vector <Drawable*> objects, bool hidden_status) {
    for (Drawable* object : objects) {
        if (hidden_status == true) object->hide();
        else                       object->show();
    }
}

int main(void) {
    Window window(1000, 600);
    window.set_coordinate_system_type(Window::Coordinate_System_Type::CENTER);

    // ======================================== View 1 ========================================
    Button show_view2_button(0,  100, "Coordinate Systems", 30);
    Button show_view3_button(0,    0, "Sphere",             30);
    Button exit_button      (0, -100, "Exit",               30);

    std::vector <Drawable*> view1 = {&show_view2_button, &show_view3_button, &exit_button };
    // ========================================================================================

    // ======================================== View 2 ========================================
    Vector second_hand(0, 0, 0, 100);
    second_hand.set_fill_color(Color::Red);

    Vector minute_hand(0, 0, 0, 75);
    minute_hand.set_fill_color(Color::Red);

    Vector vector(40, 40, 100, 100);

    CoordinateSystem system1(100, 300, CoordinateSystem::AxisY_Direction::UP, CoordinateSystem::AxisX_Direction::RIGHT);
    system1.set_draw_status(true);
    system1.extend_objects({&second_hand, &minute_hand});

    CoordinateSystem system2(900, 300, CoordinateSystem::AxisY_Direction::DOWN, CoordinateSystem::AxisX_Direction::LEFT);
    system2.set_draw_status(true);
    system2.append_object(&vector);

    Button back_button(0, -200, "Back", 30, Button::Button_Type::ELLIPSE);

    std::vector <Drawable*> view2 = { &back_button, &system1, &system2, &vector };
    // ========================================================================================

    // ======================================== View 3 ========================================
    std::vector <Drawable*> view3 = { &back_button };
    // ========================================================================================

    window.extend_objects(view1);
    window.extend_objects(view2);
    window.extend_objects(view3);

    set_objects_hidden_status(view2, true);
    set_objects_hidden_status(view3, true);

    bool update_clock = true;
    Event::MouseEvent::Button_Type button_presed = Event::MouseEvent::Button_Type::NONE;

    Clock clock(15);
    while (window.is_open()) {
        // ==================== Window Events ====================
        Event event;
        while (window.poll_event(&event)) {
            switch (event.type) {
                case Event::WINDOW_CLOSED:
                    window.close();
                    break;
                
                case Event::MOUSE_BUTTON_PRESSED: {
                    button_presed = event.mouse.button;

                    Point2D point = window.get_system()->pixel_to_point(event.mouse.pos);

                    if (show_view2_button.is_pressed(point)) {
                        set_objects_hidden_status(view1, true);
                        set_objects_hidden_status(view3, true);
                        set_objects_hidden_status(view2, false);
                    }

                    if (show_view3_button.is_pressed(point)) {
                        set_objects_hidden_status(view1, true);
                        set_objects_hidden_status(view2, true);
                        set_objects_hidden_status(view3, false);
                    }

                    if (exit_button.is_pressed(point)) {
                        window.close();
                    }

                    if (back_button.is_pressed(point)) {
                        set_objects_hidden_status(view2, true);
                        set_objects_hidden_status(view3, true);
                        set_objects_hidden_status(view1, false);
                    }

                    break;
                }
                
                case Event::MOUSE_BUTTON_RELEASED:
                    button_presed = Event::MouseEvent::Button_Type::NONE;
                    break;
            }

            if (button_presed == Event::MouseEvent::Button_Type::LEFT  && (event.type == Event::MOUSE_MOVED || event.type == Event::MOUSE_BUTTON_PRESSED)) {
                vector.end_point = system2.pixel_to_point(event.mouse.pos);
            }

            if (button_presed == Event::MouseEvent::Button_Type::RIGHT && (event.type == Event::MOUSE_MOVED || event.type == Event::MOUSE_BUTTON_PRESSED)) {
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

        window.draw_window_coordinate_system();
        window.draw_added_objects();

        window.display();
        // =========================================================
    }

    return 0;
}
